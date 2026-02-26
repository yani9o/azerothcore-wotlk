#include "ScriptMgr.h"
#include "Player.h"
#include "Unit.h"
#include "Map.h"
#include "Chat.h"
#include "Config.h"

#include <cmath>
#include <unordered_map>
#include <set>
#include <sstream>

namespace SimpleBalance
{
    bool Enable = true;
    bool Announce = true;
	bool NormalizeXP = true;
    float DungeonFactor = 0.5f;
    float Raid10Factor  = 0.5f;
	float Raid20Factor  = 0.5f;
	float Raid25Factor  = 0.5f;
	float Raid40Factor  = 0.5f;
	float GeneralFactor = 0.5f;

    struct ScaleState
    {
        uint32 Players = 0;
        float Outgoing = 0.0f;
        float Incoming = 0.0f;
    };

    static std::unordered_map<uint32, ScaleState> InstanceState;
    std::set<uint32> ForcedNPCs;

    void LoadConfig()
    {
        Enable        = sConfigMgr->GetOption<bool>("SimpleBalance.Enable", true);
        Announce      = sConfigMgr->GetOption<bool>("SimpleBalance.Announce", true);
		NormalizeXP   = sConfigMgr->GetOption<bool>("SimpleBalance.NormalizeXP", true);
        DungeonFactor = sConfigMgr->GetOption<float>("SimpleBalance.Dungeon", 0.5f);
        Raid10Factor  = sConfigMgr->GetOption<float>("SimpleBalance.Raid10", 0.5f);
        Raid20Factor  = sConfigMgr->GetOption<float>("SimpleBalance.Raid20", 0.5f);
        Raid25Factor  = sConfigMgr->GetOption<float>("SimpleBalance.Raid25", 0.5f);
        Raid40Factor  = sConfigMgr->GetOption<float>("SimpleBalance.Raid40", 0.5f);
        GeneralFactor = sConfigMgr->GetOption<float>("SimpleBalance.General", 0.5f);

        std::string token;

        ForcedNPCs.clear();
        std::string list = sConfigMgr->GetOption<std::string>("SimpleBalance.ForcedNPCs", "");
        std::stringstream ss(list);
        while (std::getline(ss, token, ','))
            ForcedNPCs.insert(uint32(std::stoul(token)));
		
    }

    uint32 GetPlayersInInstance(Map* map)
    {
        uint32 count = 0;
        for (auto const& itr : map->GetPlayers())
            if (itr.GetSource())
                ++count;
        return count > 0 ? count : 1;
    }

    uint32 GetMaxPlayers(Map* map)
    {
        if (InstanceMap* imap = map->ToInstanceMap())
            return imap->GetMaxPlayers();
        return 1;
    }

    float GetFactor(Map* map)
	{
		if (!map || !map->IsDungeon())
			return 1.0f;

		if (!map->IsRaid())
			return DungeonFactor;

		switch (GetMaxPlayers(map))
		{
			case 10:
				return Raid10Factor;
			case 20:
				return Raid20Factor;
			case 25:
				return Raid25Factor;
			case 40:
				return Raid40Factor;
			default:
				return GeneralFactor;
		}
	}

    float ClampScale(float v, bool outgoing)
    {
        return outgoing ? v : std::clamp(v, 0.01f, 100.0f);
    }

    float ScaleOutgoing(float P, float M, float factor)
    {
        return ClampScale(100.0f / (((std::tanh((P-(M*factor))/(M/5*1.5))+1)/2)*(1/(((std::tanh((M-(M*factor))/(M/5*1.5))+1)/2)))), true);
    }

    float ScaleIncoming(float P, float M, float factor)
    {
        return ClampScale(100.0f * (((std::tanh((P-(M*factor))/(M/5*1.5))+1)/2)*(1/(((std::tanh((M-(M*factor))/(M/5*1.5))+1)/2)))), false);
    }

    bool IsPlayerOrPlayerPet(Unit* unit)
    {
        if (!unit) return false;
        if (unit->IsPlayer()) return true;
        if (unit->IsPet() && unit->GetOwner())
            return unit->GetOwner()->IsPlayer();
        return false;
    }

    uint32 GetInstanceKey(Map* map)
    {
        return (map->GetId() << 16) | map->GetInstanceId();
    }

    bool IsForcedNPC(Unit* unit)
    {
        return unit && unit->IsCreature() && ForcedNPCs.count(unit->GetEntry()) > 0;
    }

    void CheckAndAnnounce(Map* map, uint32 playersOverride = 0)
    {
        if (!map) return;

        uint32 P = playersOverride ? playersOverride : GetPlayersInInstance(map);
        uint32 M = GetMaxPlayers(map);
        uint32 key = GetInstanceKey(map);

        if (P == 0)
        {
            InstanceState.erase(key);
            return;
        }

        if (P >= M) return;

        float factor = GetFactor(map);
        float outgoing = std::round(ScaleOutgoing(float(P), float(M), factor));
        float incoming = std::round(ScaleIncoming(float(P), float(M), factor));

        ScaleState& state = InstanceState[key];
        if (state.Players == P &&
            std::abs(state.Outgoing - outgoing) < 0.01f &&
            std::abs(state.Incoming - incoming) < 0.01f)
            return;

        state.Players  = P;
        state.Outgoing = outgoing;
        state.Incoming = incoming;

        for (auto const& itr : map->GetPlayers())
        {
            if (Player* player = itr.GetSource())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("[SimpleBalance]");
                ChatHandler(player->GetSession()).PSendSysMessage("{} ({}/{} Spieler)", map->GetMapName(), P, M);
                ChatHandler(player->GetSession()).PSendSysMessage("Config: {}", factor);
                ChatHandler(player->GetSession()).PSendSysMessage("Verursachter Schaden: {}%", outgoing);
                ChatHandler(player->GetSession()).PSendSysMessage("Erlittener Schaden: {}%", incoming);
            }
        }
    }
}

// ------------------- UnitScript -------------------

class SimpleBalance_UnitScript : public UnitScript
{
public:
    SimpleBalance_UnitScript() : UnitScript("SimpleBalance_UnitScript") {}

    void OnDamage(Unit* attacker, Unit* victim, uint32& damage) override
    {
        if (!SimpleBalance::Enable || !attacker || !victim || attacker == victim || damage == 0)
            return;

        Map* map = attacker->GetMap();
        if (!map) return;

        uint32 P = SimpleBalance::GetPlayersInInstance(map);
        uint32 M = SimpleBalance::GetMaxPlayers(map);
        if (P >= M) return;

        float factor = SimpleBalance::GetFactor(map);
        bool attackerIsPlayerSide = SimpleBalance::IsPlayerOrPlayerPet(attacker);
        bool victimIsPlayerSide   = SimpleBalance::IsPlayerOrPlayerPet(victim);

        if ((attackerIsPlayerSide && !victimIsPlayerSide) || SimpleBalance::IsForcedNPC(victim))
        {
            float scale = SimpleBalance::ScaleOutgoing(float(P), float(M), factor) / 100.0f;
            damage = uint32(damage * scale);
        }

        if (!attackerIsPlayerSide && victimIsPlayerSide)
        {
            float scale = SimpleBalance::ScaleIncoming(float(P), float(M), factor) / 100.0f;
            damage = uint32(damage * scale);
        }
    }
	
	void AfterDamage(Unit* attacker, Unit* victim, uint32& damage) override
    {
        if (!SimpleBalance::Enable || !attacker || !victim || attacker == victim || damage == 0)
            return;

        Map* map = attacker->GetMap();
        if (!map) return;

        uint32 P = SimpleBalance::GetPlayersInInstance(map);
        uint32 M = SimpleBalance::GetMaxPlayers(map);
        if (P >= M) return;

        float factor = SimpleBalance::GetFactor(map);
        bool attackerIsPlayerSide = SimpleBalance::IsPlayerOrPlayerPet(attacker);
        bool victimIsPlayerSide   = SimpleBalance::IsPlayerOrPlayerPet(victim);

        if (attackerIsPlayerSide && !victimIsPlayerSide)
        {
            float scale = SimpleBalance::ScaleOutgoing(float(P), float(M), factor) / 100.0f;
			float scaledamage = damage - (damage / scale);
			victim->AddThreat(attacker, -scaledamage);
        }
    }

    void AfterHeal(Unit* healer, Unit* target, uint32& heal) override
    {
        if (!SimpleBalance::Enable || !healer || !target || heal == 0)
            return;

        bool healerIsPlayerSide = SimpleBalance::IsPlayerOrPlayerPet(healer);
        bool targetIsPlayerSide = SimpleBalance::IsPlayerOrPlayerPet(target);
        if (!healerIsPlayerSide) return;

        Map* map = healer->GetMap();
        if (!map) return;

        uint32 P = SimpleBalance::GetPlayersInInstance(map);
        uint32 M = SimpleBalance::GetMaxPlayers(map);
        if (P >= M) return;

        float factor = SimpleBalance::GetFactor(map);
        if (healerIsPlayerSide && !targetIsPlayerSide)
        {
            float scale = SimpleBalance::ScaleOutgoing(float(P), float(M), factor) / 100.0f;
            float scaleheal = (heal * scale) - heal;
			target->ModifyHealth(uint32(scaleheal));
        }
    }
};

// ------------------- PlayerScript (XP Normalization) -------------------

class SimpleBalance_PlayerScript : public PlayerScript
{
public:
    SimpleBalance_PlayerScript() : PlayerScript("SimpleBalance_PlayerScript") {}

    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        if (!SimpleBalance::Enable || !SimpleBalance::NormalizeXP || !player || amount == 0)
            return;

        // Only scale mob kill XP
        if (xpSource != XPSOURCE_KILL)
            return;

        Map* map = player->GetMap();
        if (!map || !map->IsDungeon())
            return;

        uint32 P = SimpleBalance::GetPlayersInInstance(map);
        uint32 M = SimpleBalance::GetMaxPlayers(map);

        if (P >= M)
            return;
		
		float grpfactor = 1.0f;
		
		if ( M == 5 ) 
		{
			switch (P)
			{
				case 1: grpfactor = 1.4f; break;
				case 2: grpfactor = 1.4f; break;
				case 3: grpfactor = 1.200686106f; break;
				case 4: grpfactor = 1.076923077f; break;
				default: break;
			}
		}
		
        float scale = float(P) / float(M);
        amount = uint32(amount * grpfactor * scale);
    }
};

// ------------------- AllMapScript für Announce -------------------

class SimpleBalance_AllMapScript : public AllMapScript
{
public:
    SimpleBalance_AllMapScript() : AllMapScript("SimpleBalance_AllMapScript") {}

    void OnPlayerEnterAll(Map* map, Player* player) override
    {
        if (!SimpleBalance::Announce || !map || !player) return;
        uint32 key = SimpleBalance::GetInstanceKey(map);
        SimpleBalance::InstanceState.erase(key);
        SimpleBalance::CheckAndAnnounce(map);
    }

    void OnPlayerLeaveAll(Map* map, Player* player) override
    {
        if (!SimpleBalance::Announce || !map || !player) return;
        uint32 P = SimpleBalance::GetPlayersInInstance(map);
        if (P > 0) --P;
        SimpleBalance::CheckAndAnnounce(map, P);
    }
};

// ------------------- ChatCommand Script -------------------

class SimpleBalance_CommandScript : public CommandScript
{
public:
    SimpleBalance_CommandScript() : CommandScript("SimpleBalance_CommandScript") {}

    Acore::ChatCommands::ChatCommandTable GetCommands() const override
    {
        using namespace Acore::ChatCommands;
        ChatCommandTable table;

        table.push_back(ChatCommandBuilder(
            "sb",
            HandleSimpleBalanceCommand,
            SEC_PLAYER,
            Console::No
        ));

        return table;
    }

    static bool HandleSimpleBalanceCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetPlayer();
        if (!player) return false;
        Map* map = player->GetMap();
        if (!map) return false;

        uint32 key = SimpleBalance::GetInstanceKey(map);
        SimpleBalance::InstanceState.erase(key);
        SimpleBalance::CheckAndAnnounce(map);
        return true;
    }
};

// ------------------- WorldScript -------------------
class SimpleBalance_WorldScript : public WorldScript
{
public:
    SimpleBalance_WorldScript() : WorldScript("SimpleBalance_WorldScript") {}

    void OnStartup() override
    {
        SimpleBalance::LoadConfig();
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        SimpleBalance::LoadConfig();
    }
};

// ------------------- Add all Scripts -------------------

void Addmod_simple_balanceScripts()
{
    new SimpleBalance_UnitScript();
	new SimpleBalance_PlayerScript();
    new SimpleBalance_AllMapScript();
    new SimpleBalance_CommandScript();
    new SimpleBalance_WorldScript();
}
