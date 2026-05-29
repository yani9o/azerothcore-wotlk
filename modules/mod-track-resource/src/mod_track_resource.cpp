#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"

namespace TrackResourceConfig
{
    bool Enable    = true;
    uint32 TrackId = 190006;

    void Load()
    {
        Enable  = sConfigMgr->GetOption<bool>("TrackResource.Enable", true);
        TrackId = sConfigMgr->GetOption<uint32>("TrackResource.TrackId", 190006);
    }
}

class TrackResource_PlayerScript : public PlayerScript
{
public:
    TrackResource_PlayerScript() : PlayerScript("TrackResource_PlayerScript") {}

    void CheckTrackingResource(Player* player)
    {
        if (!TrackResourceConfig::Enable)
            return;

        uint32 trackId = TrackResourceConfig::TrackId;
        if (!trackId)
            return;

        bool hasHerb = player->HasSkill(182);
        bool hasMining = player->HasSkill(186);

        if (hasHerb && hasMining)
        {
            if (!player->HasSpell(trackId))
                player->learnSpell(trackId, false);
			return;
        }
        else
        {
            if (player->HasSpell(trackId))
                player->removeSpell(trackId, SPEC_MASK_ALL, false);
        }
    }

    void OnPlayerLogin(Player* player) override { CheckTrackingResource(player); }
	
	void OnPlayerSetSkill(Player* player, uint32 skillId, uint32 value, uint32 max, uint32 step, uint32 newValue) override
    {
        if (skillId == 182 || skillId == 186)
            CheckTrackingResource(player);
    }

};

// ------------------- WorldScript -------------------
class TrackResource_WorldScript : public WorldScript
{
public:
    TrackResource_WorldScript() : WorldScript("TrackResource_WorldScript") {}

    void OnStartup() override
    {
        TrackResourceConfig::Load();
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        TrackResourceConfig::Load();
    }
};

// ---------- SCRIPT LOADER ----------
void Addmod_track_resourceScripts()
{
	new TrackResource_PlayerScript();
	new TrackResource_WorldScript();
}
