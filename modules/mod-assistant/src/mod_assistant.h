#ifndef MOD_ASSISTANT_H
#define MOD_ASSISTANT_H

#include "Chat.h"
#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "SpellMgr.h"

enum
{
    ASSISTANT_GOSSIP_HEIRLOOM        = 100,
    ASSISTANT_GOSSIP_GLYPH           = 200,
    ASSISTANT_GOSSIP_GEM             = 400,
    ASSISTANT_GOSSIP_ELIXIRS         = 500,
    ASSISTANT_GOSSIP_FOOD            = 600,
    ASSISTANT_GOSSIP_ENCHANTS        = 700,
    ASSISTANT_GOSSIP_CONTAINER       = 800,
    ASSISTANT_GOSSIP_FLIGHT_PATHS    = 900,
    ASSISTANT_GOSSIP_UTILITIES       = 1000,
    ASSISTANT_GOSSIP_PROFESSIONS     = 1100,
    ASSISTANT_GOSSIP_INSTANCES       = 1200,
    ASSISTANT_GOSSIP_RAIDBUFF        = 1300,

    ASSISTANT_GOSSIP_TEXT            = 48,

    ASSISTANT_VENDOR_HEIRLOOM_WEAPON = 9000000,
    ASSISTANT_VENDOR_HEIRLOOM_ARMOR  = 9000001,
    ASSISTANT_VENDOR_HEIRLOOM_OTHER  = 9000002,
    ASSISTANT_VENDOR_GLYPH           = 9000003,
    ASSISTANT_VENDOR_GEM             = 9000023,
    ASSISTANT_VENDOR_ELIXIR          = 9000030,
    ASSISTANT_VENDOR_FOOD            = 9000033,
    ASSISTANT_VENDOR_ENCHANT         = 9000034,
    ASSISTANT_VENDOR_CONTAINER       = 9000045,

    PROFESSION_LEVEL_APPRENTICE      = 75,
    PROFESSION_LEVEL_JOURNEYMAN      = 150,
    PROFESSION_LEVEL_EXPERT          = 225,
    PROFESSION_LEVEL_ARTISAN         = 300,
    PROFESSION_LEVEL_MASTER          = 375,
    PROFESSION_LEVEL_GRAND_MASTER    = 450,

    INSTANCE_TYPE_HEROIC             = 0,
    INSTANCE_TYPE_RAID               = 1,

    GLYPH_WARRIOR                    = 0,
    GLYPH_PALADIN                    = 1,
    GLYPH_HUNTER                     = 2,
    GLYPH_ROGUE                      = 3,
    GLYPH_PRIEST                     = 4,
    GLYPH_DEATH_KNIGHT               = 5,
    GLYPH_SHAMAN                     = 6,
    GLYPH_MAGE                       = 7,
    GLYPH_WARLOCK                    = 8,
    GLYPH_DRUID                      = 9
};

#define GOSSIP_HEIRLOOMS "Erbstücke"
#define GOSSIP_HEIRLOOMS_WEAPONS "Erbstück-Waffen"
#define GOSSIP_HEIRLOOMS_ARMOR "Erbstück-Rüstungen"
#define GOSSIP_HEIRLOOMS_OTHER "Sonstige Erbstücke"

#define GOSSIP_GLYPHS "Glyphen"
#define GOSSIP_GLYPHS_MAJOR "Große Glyphen"
#define GOSSIP_GLYPHS_MINOR "Kleine Glyphen"

#define GOSSIP_GEMS "Edelsteine"
#define GOSSIP_GEMS_META "Meta-Edelsteine"
#define GOSSIP_GEMS_RED "Rote Edelsteine"
#define GOSSIP_GEMS_BLUE "Blaue Edelsteine"
#define GOSSIP_GEMS_YELLOW "Gelbe Edelsteine"
#define GOSSIP_GEMS_PURPLE "Violette Edelsteine"
#define GOSSIP_GEMS_GREEN "Grüne Edelsteine"
#define GOSSIP_GEMS_ORANGE "Orangefarbene Edelsteine"

#define GOSSIP_ELIXIRS "Elixiere"
#define GOSSIP_ELIXIRS_BATTLE "Kampf-Elixiere"
#define GOSSIP_ELIXIRS_GUARDIAN "Wächter-Elixiere"
#define GOSSIP_ELIXIRS_FLASK "Fläschchen"

#define GOSSIP_FOOD "Essen & Bufffood"

#define GOSSIP_ENCHANTS "Verzauberungen"
#define GOSSIP_ENCHANTS_WEAPON "Waffenverzauberungen"
#define GOSSIP_ENCHANTS_HEAD "Kopfverzauberungen"
#define GOSSIP_ENCHANTS_SHOULDER "Schulterverzauberungen"
#define GOSSIP_ENCHANTS_CHEST "Brustverzauberungen"
#define GOSSIP_ENCHANTS_BRACER "Armschienenverzauberungen"
#define GOSSIP_ENCHANTS_GLOVES "Handschuhverzauberungen"
#define GOSSIP_ENCHANTS_WAIST "Gürtelverzauberungen"
#define GOSSIP_ENCHANTS_LEGS "Beinverzauberungen"
#define GOSSIP_ENCHANTS_FEET "Stiefelverzauberungen"
#define GOSSIP_ENCHANTS_CLOAK "Umhangverzauberungen"
#define GOSSIP_ENCHANTS_SHIELD "Schildverzauberungen"

#define GOSSIP_CONTAINERS "Taschen & Behälter"

#define GOSSIP_UTILITIES "Charakterdienste"
#define GOSSIP_UTILITIES_NAME "Name ändern"
#define GOSSIP_UTILITIES_APPEARANCE "Aussehen ändern"
#define GOSSIP_UTILITIES_RACE "Rasse ändern"
#define GOSSIP_UTILITIES_FACTION "Fraktion wechseln"
#define GOSSIP_UTILITIES_IN_PROGRESS "Du musst den aktuellen Dienst zuerst abschließen, bevor du einen weiteren nutzen kannst."
#define GOSSIP_UTILITIES_DONE "Logge dich aus, um den aktivierten Dienst abzuschließen."

#define GOSSIP_FLIGHT_PATHS "Flugrouten freischalten"
#define GOSSIP_FLIGHT_PATHS_KALIMDOR_EASTERN_KINGDOMS "Kalimdor & Östliche Königreiche"
#define GOSSIP_FLIGHT_PATHS_OUTLAND "Scherbenwelt"
#define GOSSIP_FLIGHT_PATHS_NORTHREND "Nordend"

#define GOSSIP_PROFESSIONS "Berufe steigern"
#define GOSSIP_PROFESSIONS_CHOOSE "Fertigkeit auswählen"
#define GOSSIP_PROFESSIONS_FIRST_AID "Erste Hilfe"
#define GOSSIP_PROFESSIONS_BLACKSMITHING "Schmiedekunst"
#define GOSSIP_PROFESSIONS_LEATHERWORKING "Lederverarbeitung"
#define GOSSIP_PROFESSIONS_ALCHEMY "Alchemie"
#define GOSSIP_PROFESSIONS_HERBALISM "Kräuterkunde"
#define GOSSIP_PROFESSIONS_COOKING "Kochkunst"
#define GOSSIP_PROFESSIONS_MINING "Bergbau"
#define GOSSIP_PROFESSIONS_TAILORING "Schneiderei"
#define GOSSIP_PROFESSIONS_ENGINEERING "Ingenieurskunst"
#define GOSSIP_PROFESSIONS_ENCHANTING "Verzauberkunst"
#define GOSSIP_PROFESSIONS_FISHING "Angeln"
#define GOSSIP_PROFESSIONS_SKINNING "Kürschnerei"
#define GOSSIP_PROFESSIONS_INSCRIPTION "Inschriftenkunde"
#define GOSSIP_PROFESSIONS_JEWELCRAFTING "Juwelenschleifen"

#define GOSSIP_INSTANCES "Instanzen zurücksetzen"
#define GOSSIP_INSTANCES_HEROIC "Heroische Dungeons zurücksetzen"
#define GOSSIP_INSTANCES_RAID "Schlachtzüge zurücksetzen"
#define GOSSIP_INSTANCES_PLAYER "Nur für dich"
#define GOSSIP_INSTANCES_GROUP "Für die gesamte Gruppe"
#define GOSSIP_INSTANCES_HEROIC_RESET "Alle heroischen Dungeons wurden zurückgesetzt."
#define GOSSIP_INSTANCES_HEROIC_GROUP_RESET "Alle heroischen Dungeons deiner Gruppe wurden zurückgesetzt."
#define GOSSIP_INSTANCES_RAID_RESET "Alle Schlachtzüge wurden zurückgesetzt."
#define GOSSIP_INSTANCES_RAID_GROUP_RESET "Alle Schlachtzüge deiner Gruppe wurden zurückgesetzt."

#define GOSSIP_RAIDBUFF "Segen erhalten"

#define GOSSIP_CONTINUE_TRANSACTION "Möchtest du fortfahren?"
#define GOSSIP_PREVIOUS_PAGE "Zurück"

class Assistant : public CreatureScript, WorldScript
{
public:
    Assistant();

    // CreatureScript
    bool OnGossipHello(Player* /*player*/, Creature* /*creature*/) override;
    bool OnGossipSelect(Player* /*player*/, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/) override;

    // WorldScript
    void OnAfterConfigLoad(bool /*reload*/) override;

private:
    bool HeirloomsEnabled;
    bool GlyphsEnabled;
    bool GemsEnabled;
    bool ElixirsEnabled;
    bool FoodEnabled;
    bool EnchantsEnabled;
    bool ContainersEnabled;

    uint32 GetGlyphId(uint32 /*id*/, bool /*major*/);

    // Utilities
    bool UtilitiesEnabled;
    uint32 NameChangeCost;
    uint32 CustomizeCost;
    uint32 RaceChangeCost;
    uint32 FactionChangeCost;

    bool HasLoginFlag(Player* /*player*/);
    void SetLoginFlag(Player* /*player*/, AtLoginFlags /*flag*/, uint32 /*cost*/);

    // Flight Paths
    bool FlightPathsEnabled[EXPANSION_WRATH_OF_THE_LICH_KING + 1];
    uint32 FlightPathsRequiredLevel[EXPANSION_WRATH_OF_THE_LICH_KING + 1];
    uint32 FlightPathsCost[EXPANSION_WRATH_OF_THE_LICH_KING + 1];

    bool CanUnlockFlightPaths(Player* /*player*/);
    std::vector<int> GetAvailableFlightPaths(Player* /*player*/, uint8 /*expansion*/);
    bool HasAvailableFlightPaths(Player* /*player*/, uint8 /*expansion*/);
    void UnlockFlightPaths(Player* /*player*/, uint8 /*expansion*/);

    // Professions
    bool ApprenticeProfessionEnabled;
    uint32 ApprenticeProfessionCost;
    bool JourneymanProfessionEnabled;
    uint32 JourneymanProfessionCost;
    bool ExpertProfessionEnabled;
    uint32 ExpertProfessionCost;
    bool ArtisanProfessionEnabled;
    uint32 ArtisanProfessionCost;
    bool MasterProfessionEnabled;
    uint32 MasterProfessionCost;
    bool GrandMasterProfessionEnabled;
    uint32 GrandMasterProfessionCost;

    void ListProfession(Player* /*player*/, uint32 /*id*/);
    void SetProfession(Player* /*player*/, uint32 /*id*/);
    bool HasValidProfession(Player* /*player*/);
    bool IsValidProfession(Player* /*player*/, uint32 /*id*/);
    uint32 GetProfessionCost(Player* /*player*/, uint32 /*id*/);

    // Instances
    bool HeroicInstanceEnabled;
    uint32 HeroicInstanceCost;
    bool RaidInstanceEnabled;
    uint32 RaidInstanceCost;
	
	// Raidbuff
	bool RaidbuffEnabled;
	uint32 RaidbuffCost;

    bool CanResetInstances(Player* /*player*/);
    bool HasSavedInstances(Player* /*player*/, uint8 /*type*/);
    void ResetInstances(Player* /*player*/, uint8 /*type*/);
};

#endif
