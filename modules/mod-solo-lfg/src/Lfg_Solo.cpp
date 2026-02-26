/*
** Made by Traesh https://github.com
** AzerothCore 2019 http://www.azerothcore.org
** Conan513 https://github.com
** Made into a module by Micrah https://github.com
** CriteriaCheck by yani9o https://github.com
*/

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "Group.h"
#include "LFGMgr.h"
#include "AchievementMgr.h"
#include <sstream>

// ----------------- ANNOUNCE / XP -----------------
class lfg_solo_announce : public PlayerScript
{
public:
    lfg_solo_announce() : PlayerScript("lfg_solo_announce") {}

    void OnPlayerLogin(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("SoloLFG.Announce", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage(
                "This server is running the |cff4CFF00Solo Dungeon Finder |rmodule."
            );
        }
    }

    void OnPlayerRewardKillRewarder(Player* /*player*/, KillRewarder* /*rewarder*/, bool isDungeon, float& rate) override
    {
        if (!isDungeon || !sConfigMgr->GetOption<bool>("SoloLFG.Enable", true) || !sConfigMgr->GetOption<bool>("SoloLFG.FixedXP", true))
            return;

        rate = sConfigMgr->GetOption<float>("SoloLFG.FixedXPRate", 0.2f);
    }
};

// ----------------- CRITERIA LOCK -----------------
class lfg_criteria_lock : public PlayerScript
{
public:
    lfg_criteria_lock() : PlayerScript("lfg_criteria_lock") {}

    bool IsDungeonLocked(Player* player, Group* group, uint32 dungeonId, std::string& missingBossName)
    {
		
		bool isSolo = !group || group->GetMembersCount() <= 1;
		
		if (isSolo)
		{
			if (player->GetTeamId() == TEAM_ALLIANCE && dungeonId == 4)
				return false;
			if (player->GetTeamId() == TEAM_HORDE && dungeonId == 12)
				return false;
			
			LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(dungeonId);
			if (dungeon && player->GetLevel() > (dungeon->MinLevel + 10))
				return false;
		}
		
        std::string configKey = "SoloLFG.DungeonCriteria." + std::to_string(dungeonId);
        std::string value = sConfigMgr->GetOption<std::string>(configKey, "");

        if (value.empty())
            return false;

        std::stringstream ss(value);
        std::string token;
        bool anyoneHasIt = false;

        while (std::getline(ss, token, ','))
        {
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);

            if (token.empty()) continue;

            size_t colonPos = token.find(':');
            uint32 criteriaId = 0;
            std::string bossNameFromConfig = "Boss-Kill";

            try {
                if (colonPos != std::string::npos) {
                    criteriaId = std::stoul(token.substr(0, colonPos));
                    bossNameFromConfig = token.substr(colonPos + 1);
                } else {
                    criteriaId = std::stoul(token);
                }
            } catch (...) { continue; }

            AchievementCriteriaEntry const* ce = sAchievementCriteriaStore.LookupEntry(criteriaId);
            if (!ce) continue;

            missingBossName = bossNameFromConfig;

            auto CheckPlayer = [&](Player* p) -> bool {
                if (!p) return false;
                if (AchievementMgr* achMgr = p->GetAchievementMgr())
                    if (CriteriaProgress const* progress = achMgr->GetCriteriaProgress(ce))
                        if (progress->counter >= 1) return true;
                
                return p->HasAchieved(ce->referredAchievement);
            };

            if (group) {
                for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
                    if (Player* m = ref->GetSource())
                        if (CheckPlayer(m)) { anyoneHasIt = true; break; }
            } else {
                if (CheckPlayer(player)) anyoneHasIt = true;
            }

            if (anyoneHasIt) break;
        }
        return !anyoneHasIt;
    }

    bool OnPlayerCanJoinLfg(Player* player, uint8 /*roles*/, std::set<uint32>& dungeons, const std::string& /*comment*/) override
    {
        if (!sConfigMgr->GetOption<bool>("SoloLFG.Enable", true) || !sConfigMgr->GetOption<bool>("SoloLFG.CriteriaCheck", true))
            return true;

        Group* group = player->GetGroup();
		
		if (group && group->IsFull())
            return true;
		
        uint8 pLevel = player->GetLevel();

        for (uint32 dungeonId : dungeons)
        {
            std::string missingBoss = "Unbekannter Boss";

            // --- POOL CHECK (Random Dungeons 258-262) ---
            if (dungeonId >= 258 && dungeonId <= 262)
            {
                for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
                {
                    LFGDungeonEntry const* innerEntry = sLFGDungeonStore.LookupEntry(i);
                    if (!innerEntry || (innerEntry->ID >= 258 && innerEntry->ID <= 262))
                        continue;

                    if (pLevel >= innerEntry->MinLevel && pLevel <= innerEntry->MaxLevel)
                    {
                        bool matchesExpansion = false;
                        if (dungeonId == 258 && innerEntry->ID < 100) matchesExpansion = true;
						if (dungeonId == 259 && (innerEntry->ID >= 135 && innerEntry->ID <= 175)) matchesExpansion = true;
                        if (dungeonId == 260 && innerEntry->ID > 200) matchesExpansion = true;

                        if (matchesExpansion || dungeonId == 261)
                        {
                            if (IsDungeonLocked(player, group, innerEntry->ID, missingBoss))
                            {
                                std::string msg = "Fortschritt für Zufällige Dungeons fehlt: |cffff0000" + missingBoss + "|r";
                                ChatHandler(player->GetSession()).SendSysMessage(msg.c_str());
                                return false;
                            }
                        }
                    }
                }
            }
            // --- SPECIFIC CHECK ---
            else if (IsDungeonLocked(player, group, dungeonId, missingBoss))
            {
                std::string msg = "Fortschritt fehlt: |cffff0000" + missingBoss + "|r";
                ChatHandler(player->GetSession()).SendSysMessage(msg.c_str());
                return false;
            }
        }
        return true;
    }
};

// ----------------- WORLDSCRIPT -----------------
class lfg_solo : public WorldScript
{
public:
    lfg_solo() : WorldScript("lfg_solo") {}

    void OnAfterConfigLoad(bool reload) override
    {
        if (sConfigMgr->GetOption<bool>("SoloLFG.Enable", true) != sLFGMgr->IsTesting())
            sLFGMgr->ToggleTesting();
    }
};

// ----------------- REGISTER -----------------
void AddLfgSoloScripts()
{
    new lfg_solo_announce();
    new lfg_solo();
    new lfg_criteria_lock();
}
