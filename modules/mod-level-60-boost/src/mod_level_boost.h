#ifndef DEF_LEVELBOOST_H
#define DEF_LEVELBOOST_H

#include "Player.h"
#include "AchievementMgr.h"
#include "Log.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Creature.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "Pet.h"
#include "Config.h"
#include "World.h"
#include <vector>
#include <string>

const int BOOST_TEXT = 70000;

enum GossipId
{
    GOSSIP_MAIN_MENU = 0,
    GOSSIP_LEVEL_60_BOOST = 1,
    GOSSIP_GEAR = 100,
    GOSSIP_RESET_TALENTS = 999
};

enum Spells
{
    TALENT_SPECIALIZATION_SWITCHES = 63680,
    SECOND_TALENT_SPECIALIZATION = 63624
};

// Spell and proficiency templates
struct ClassSpells
{
    uint8 class_id;
    uint32 spell_id;
    uint32 required_level;
    uint32 required_spell;
};

struct ClassProficiencies
{
    uint8 class_id;
    uint32 spell_id;
    uint32 required_level;
};

// Spec-aware templates
struct GearTemplate
{
    std::string player_class;
    std::string player_spec;
    uint8 equipment_slot;
    uint32 item_entry;
};

struct TalentTemplate
{
    std::string player_class;
    std::string player_spec;
    uint32 talent_id;
};

struct GlyphTemplate
{
    std::string player_class;
    std::string player_spec;
    uint8 glyph_slot;
    uint32 glyph_id;
};

// Main LevelBoost singleton
class LevelBoost
{
public:
    static LevelBoost* instance()
    {
        static LevelBoost instance;
        return &instance;
    }

    // Containers
    typedef std::vector<ClassSpells> ClassSpellsContainer;
    typedef std::vector<ClassProficiencies> ClassProficienciesContainer;
    typedef std::vector<GearTemplate> GearTemplateContainer;
    typedef std::vector<TalentTemplate> TalentTemplateContainer;
    typedef std::vector<GlyphTemplate> GlyphTemplateContainer;

    ClassSpellsContainer classSpellsList;
    ClassProficienciesContainer classProficienciesList;
    GearTemplateContainer gearTemplateList;
    TalentTemplateContainer talentTemplateList;
    GlyphTemplateContainer glyphTemplateList;

    // Config options
    bool levelBoost = true;
    bool dualSpec = true;
    bool learnSpells = true;
    bool learnProficiencies = true;
    bool learnTalents = true;
    bool learnGlyphs = true;
    bool destroyGear = true;

    std::string player_spec;

    // Load templates from DB
    void LoadTalentContainer();
    void LoadGlyphContainer();
    void LoadGearContainer();
    void LoadSpellContainer();
    void LoadProficiencyContainer();

    // Boost methods
    void LearnDualSpec(Player* player);
    void DestroyGear(Player* player);
    void AddClassItems(Player* player);
    void LearnSpellsForLevel(Player* player);
    void LearnProficienciesForLevel(Player* player);
    void HandleBoost(Player* player, Creature* creature, const std::string& spec);
	void HandleDeathKnight(Player* player);
	void GetRaceMount(Player* player);
    void CreateHunterPet(Player* player, Creature* creature, uint32 entry);

    // Apply templates
    bool TemplateExists(Player* player, const std::string& spec);
    bool ApplyFullTemplate(Player* player, const std::string& spec);
    void ApplyGearTemplate(Player* player, const std::string& spec);
    void ApplyTalentTemplate(Player* player, const std::string& spec);
    void ApplyGlyphTemplate(Player* player, const std::string& spec);

    // Extract templates
    void ExtractTemplates(Player* player, const std::string& spec);
    void ExtractGearTemplate(Player* player, const std::string& spec);
    void ExtractTalentTemplate(Player* player, const std::string& spec);
    void ExtractGlyphTemplate(Player* player, const std::string& spec);

    // Helpers
    std::string GetClassString(Player* player);
};

#define sLevelBoost LevelBoost::instance()

#endif