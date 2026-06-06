/*
 * Credits: silviu20092
 */

#include "Player.h"
#include "Tokenize.h"
#include "StringConvert.h"
#include "BattlefieldMgr.h"
#include "GameGraveyard.h"
#include "easy_respawn_mgr.h"
#include "LFGMgr.h"
#include "Group.h"

EasyRespawnMgr::EasyRespawnMgr()
{
    resurrectMapMask = MAP_MASK_ALL;
    resurrectHealthPct = 1.0f;
    instanceRespawnLocation = RESPAWN_OUTSIDE;
    openWorldRespawnLocation = RESPAWN_AT_GRAVEYARD;
}

EasyRespawnMgr::~EasyRespawnMgr()
{
}

EasyRespawnMgr* EasyRespawnMgr::instance()
{
    static EasyRespawnMgr instance;
    return &instance;
}

void EasyRespawnMgr::CreateResurrectMapMask(const std::string& activeStr)
{
    int32 mask = 0;
    std::vector<std::string_view> tokenized = Acore::Tokenize(activeStr, ',', false);
    for (const auto& t : tokenized)
        mask |= *Acore::StringTo<int32>(t);

    if ((mask & ~MAP_MASK_ALL) == 0)
        resurrectMapMask = mask;
    else
        resurrectMapMask = MAP_MASK_ALL;
}

bool EasyRespawnMgr::IsValidResurrectMapMask(const Player* player) const
{
    Map* map = player->GetMap();

    if (map->IsBattlegroundOrArena())
        return false;

    if (sBattlefieldMgr->GetBattlefieldToZoneId(player->GetZoneId()))
        return false;

    if (IsDisabledMapId(map->GetId()))
        return false;

    if ((resurrectMapMask & MAP_MASK_DUNGEON) && map->IsNonRaidDungeon())
        return true;

    if ((resurrectMapMask & MAP_MASK_RAID) && map->IsRaid())
        return true;

    if ((resurrectMapMask & MAP_MASK_OPEN_WORLD) && map->IsWorldMap())
        return true;

    return false;
}

void EasyRespawnMgr::Resurrect(Player* player) const
{
    player->CombatStop();
    player->GetThreatMgr().RemoveMeFromThreatLists();

    player->ResurrectPlayer(resurrectHealthPct);
    player->SpawnCorpseBones();

    player->RemovePlayerFlag(PLAYER_FLAGS_IS_OUT_OF_BOUNDS);
}

bool EasyRespawnMgr::IsDisabledMapId(uint32 mapId) const
{
    return disabledMapIds.find(mapId) != disabledMapIds.end();
}

bool EasyRespawnMgr::RespawnAndTeleport(Player* player) const
{
    if (!player || !player->GetMap() || !player->IsInWorld())
        return false;

    if (player->IsAlive())
        return false;

    if (!IsValidResurrectMapMask(player))
        return false;

    Map* map = player->GetMap();
    bool resurrect = false;

    // 1. Keep configuration override functionality intact
    const WorldLocation* overrideLocation = ChooseOverrideLocation(map->GetId());
    if (overrideLocation != nullptr)
    {
        player->TeleportTo(overrideLocation->GetMapId(), overrideLocation->GetPositionX(), overrideLocation->GetPositionY(), overrideLocation->GetPositionZ(), overrideLocation->GetOrientation());
        resurrect = true;
    }
    else
    {
        if (map->IsDungeon())
        {
            bool coordsFound = false;
            float x = 0.0f, y = 0.0f, z = 0.0f, o = 0.0f;

            // 2. PATH A: LFG Logic (Executes if the player is in an active LFG group)
            if (player->GetGroup())
            {
                uint32 dungeonId = sLFGMgr->GetDungeon(player->GetGroup()->GetGUID());
                if (dungeonId > 0)
                {
                    QueryResult lfgResult = WorldDatabase.Query("SELECT position_x, position_y, position_z, orientation FROM lfg_dungeon_template WHERE dungeonId = " + std::to_string(dungeonId));
                    if (lfgResult)
                    {
                        Field* fields = lfgResult->Fetch();
                        x = fields[0].Get<float>();
                        y = fields[1].Get<float>();
                        z = fields[2].Get<float>();
                        o = fields[3].Get<float>();
                        coordsFound = true;
                    }
                }
            }

            // 3. PATH B: Walk-In Logic (Fallback proximity check if not in LFG or LFG data is missing)
            if (!coordsFound)
            {
                QueryResult walkInResult = WorldDatabase.Query("SELECT target_position_x, target_position_y, target_position_z, target_orientation FROM areatrigger_teleport WHERE target_map = " + std::to_string(map->GetId()) + 
                    " ORDER BY (POW(target_position_x - " + std::to_string(player->GetPositionX()) + ", 2) + POW(target_position_y - " + std::to_string(player->GetPositionY()) + ", 2) + POW(target_position_z - " + std::to_string(player->GetPositionZ()) + ", 2)) ASC LIMIT 1");
                
                if (walkInResult)
                {
                    Field* fields = walkInResult->Fetch();
                    x = fields[0].Get<float>();
                    y = fields[1].Get<float>();
                    z = fields[2].Get<float>();
                    o = fields[3].Get<float>();
                    coordsFound = true;
                }
            }

            // 4. Execution: Teleport the dead player if coordinates were found via either path
            if (coordsFound)
            {
                player->TeleportTo(map->GetId(), x, y, z, o);
                resurrect = true;
            }
            else
            {
                // Absolute fallback to default module behavior if both database lookups fail
                AreaTriggerTeleport const* chosenTrigger = nullptr;
                if (instanceRespawnLocation == RESPAWN_INSIDE)
                    chosenTrigger = sObjectMgr->GetMapEntranceTrigger(map->GetId());
                else
                {
                    chosenTrigger = sObjectMgr->GetGoBackTrigger(map->GetId());
                    if (chosenTrigger == nullptr)
                        chosenTrigger = sObjectMgr->GetMapEntranceTrigger(map->GetId());
                }

                if (chosenTrigger != nullptr)
                {
                    player->TeleportTo(chosenTrigger->target_mapId, chosenTrigger->target_X, chosenTrigger->target_Y, chosenTrigger->target_Z, chosenTrigger->target_Orientation);
                    resurrect = true;
                }
            }
        }
    }

    // 5. Resurrect the player safely at their new destination coordinates
    if (resurrect)
        Resurrect(player);

    return resurrect;
}

void EasyRespawnMgr::HandleConfigSettings(const std::string& activeStr, float resurrectHealthPct, const std::string& disabledMapIdsStr, int32 instanceRespawnLocation, int32 openWorldRespawnLocation,
    const std::vector<std::string>& overrides)
{
    CreateResurrectMapMask(activeStr);

    if (resurrectHealthPct >= 0.1f && resurrectHealthPct <= 1.0f)
        this->resurrectHealthPct = resurrectHealthPct;
    else
        this->resurrectHealthPct = 1.0f;

    if (instanceRespawnLocation >= RESPAWN_INSIDE && instanceRespawnLocation <= RESPAWN_OUTSIDE)
        this->instanceRespawnLocation = (InstanceRespawnLocation)instanceRespawnLocation;
    else
        this->instanceRespawnLocation = RESPAWN_OUTSIDE;

    if (openWorldRespawnLocation >= RESPAWN_IMMEDIATE && openWorldRespawnLocation <= RESPAWN_AT_CORPSE)
        this->openWorldRespawnLocation = (OpenWorldRespawnLocation)openWorldRespawnLocation;
    else
        this->openWorldRespawnLocation = RESPAWN_AT_GRAVEYARD;

    CreateDisabledMapIdSet(disabledMapIdsStr);
    CreateOverrideLocations(overrides);
}

void EasyRespawnMgr::CreateDisabledMapIdSet(const std::string& disabledMapIdsStr)
{
    disabledMapIds.clear();
    std::vector<std::string_view> tokenized = Acore::Tokenize(disabledMapIdsStr, ',', false);
    std::transform(
        tokenized.begin(),
        tokenized.end(),
        std::inserter(disabledMapIds, disabledMapIds.end()),
        [](const std::string_view& str) { return *Acore::StringTo<int32>(str); }
    );
}

void EasyRespawnMgr::CreateOverrideLocations(const std::vector<std::string>& overrides)
{
    overrideLocations.clear();
    for (const std::string& o : overrides)
    {
        std::string overrideLocationStr = sConfigMgr->GetOption<std::string>(o, "");
        if (!overrideLocationStr.empty())
        {
            std::string::size_type lastDotIndex = o.find_last_of('.');
            if (lastDotIndex == o.length() - 1)
                continue;

            std::vector<std::string_view> tokenized = Acore::Tokenize(overrideLocationStr, ',', false);
            if (tokenized.size() != 5) // must match map_id,x,y,z,o
                continue;

            WorldLocation location;
            location.WorldRelocate(
                *Acore::StringTo<uint32>(tokenized[0]),
                *Acore::StringTo<float> (tokenized[1]),
                *Acore::StringTo<float> (tokenized[2]),
                *Acore::StringTo<float> (tokenized[3]),
                *Acore::StringTo<float> (tokenized[4])
            );

            overrideLocations[*Acore::StringTo<uint32>(o.substr(lastDotIndex + 1))] = location;
        }
    }
}

const WorldLocation* EasyRespawnMgr::ChooseOverrideLocation(uint32 mapId) const
{
    if (overrideLocations.find(mapId) != overrideLocations.end())
        return &overrideLocations.at(mapId);

    return nullptr;
}
