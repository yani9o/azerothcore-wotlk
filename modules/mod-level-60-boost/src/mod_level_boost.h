#ifndef DEF_LEVELBOOST_H
#define DEF_LEVELBOOST_H

#include "Player.h"
#include "Log.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Creature.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "Pet.h"
#include "Config.h"
#include "World.h"

#define ITEM_DEFAULT_ARROWS 2512
#define ITEM_DEFAULT_BULLETS 2516
#define ITEM_BOOST_ARROWS 28053
#define ITEM_BOOST_BULLETS 28060
#define ITEM_SHAMAN_TOTEM_1 5175
#define ITEM_SHAMAN_TOTEM_2 5176

const int ARROW_COUNT = 1000;
const int BULLET_COUNT = 1000;
const int BOOST_TEXT = 70000;

enum GossipId
{
    GOSSIP_MAIN_MENU = 0,
    GOSSIP_LEVEL_15_BOOST = 1,
    GOSSIP_GEAR = 100,
    GOSSIP_RESET_TALENTS = 999
};

enum Spells
{
    TALENT_SPECIALIZATION_SWITCHES = 63680,
    SECOND_TALENT_SPECIALIZATION = 63624
};

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

struct GearTemplate
{
    std::string player_class;
    std::string player_spec;
    std::string player_race;
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

class LevelBoost
{
public:
    static LevelBoost* instance()
    {
        static LevelBoost instance;
        return &instance;
    }

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

    bool levelBoost, dualSpec, learnSpells, LearnProficiencies, learnTalents, learnGlyphs, destroyGear;
    std::string player_spec;

    void LoadTalentContainer();
    void LoadGlyphContainer();
    void LoadGearContainer();
    void LoadSpellContainer();
    void LoadProficiencyContainer();
    void LearnDualSpec(Player* player);
    void DestroyGear(Player* player);
    void DestroyProjectiles(Player* player);
    void AddClassItems(Player* player);
    void LearnSpellsForLevel(Player* player);
    void LearnProficienciesForLevel(Player* Player);
    void HandleBoost(Player* player, Creature* creature);
    void CreateHunterPet(Player* player, Creature* creature, uint32 entry);
    bool TemplateExists(Player* player);
    bool ApplyFullTemplate(Player* player, std::string player_spec);
    void ApplyGearTemplate(Player* player);
    void ApplyTalentTemplate(Player* player);
    void ApplyGlyphTemplate(Player* player);
    void ExtractTemplates(Player* player, std::string player_spec);
    void ExtractGearTemplate(Player* player, std::string player_spec);
    void ExtractTalentTemplate(Player* player, std::string player_spec);
    void ExtractGlyphTemplate(Player* player, std::string player_spec);
    std::string GetClassString(Player* player);
    std::string GetRaceString(Player* player);
};

#define sLevelBoost LevelBoost::instance()

#endif
