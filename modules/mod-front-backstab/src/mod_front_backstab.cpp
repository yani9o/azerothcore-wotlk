#include "ScriptMgr.h"
#include "SpellScript.h"
#include "Unit.h"
#include "Config.h"
#include <unordered_map>
#include <sstream>
#include <vector>

// ------------------------------------------------------
// Data per spell
// ------------------------------------------------------
struct FrontBackstabData
{
    bool AllowFront;   // true = front allowed, false = forbidden
    float FrontFactor; // damage factor if front attack (>1 = reduced damage)
};

static std::unordered_map<uint32 /*spellId*/, FrontBackstabData> FrontBackstabSpells;

// ------------------------------------------------------
// Load spell groups from config
// ------------------------------------------------------
static void LoadSpellGroup(const std::string& enableKey,
                           const std::string& idsKey,
                           const std::string& factorKey)
{
    bool allowFront = sConfigMgr->GetOption<bool>(enableKey, true);
    float factor    = sConfigMgr->GetOption<float>(factorKey, 1.0f);
    std::string ids = sConfigMgr->GetOption<std::string>(idsKey, "");

    std::stringstream ss(ids);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        if (token.empty())
            continue;

        uint32 spellId = std::stoul(token);
        if (!spellId)
            continue;

        FrontBackstabSpells[spellId] = { allowFront, factor };
    }
}

// ------------------------------------------------------
// Load entire config
// ------------------------------------------------------
static void LoadFrontBackstabConfig()
{
    FrontBackstabSpells.clear();

    if (!sConfigMgr->GetOption<bool>("FrontBackstab.Enable", true))
        return;

    LoadSpellGroup("FrontBackstab.Backstab",
                   "FrontBackstab.BackstabIDs",
                   "FrontBackstab.BackstabFactor");

    LoadSpellGroup("FrontBackstab.Ambush",
                   "FrontBackstab.AmbushIDs",
                   "FrontBackstab.AmbushFactor");

    LoadSpellGroup("FrontBackstab.Garrote",
                   "FrontBackstab.GarroteIDs",
                   "FrontBackstab.GarroteFactor");

    LoadSpellGroup("FrontBackstab.Shred",
                   "FrontBackstab.ShredIDs",
                   "FrontBackstab.ShredFactor");

    LoadSpellGroup("FrontBackstab.Ravage",
                   "FrontBackstab.RavageIDs",
                   "FrontBackstab.RavageFactor");
}

// ------------------------------------------------------
// SpellScript
// ------------------------------------------------------
class spell_front_backstab : public SpellScript
{
    PrepareSpellScript(spell_front_backstab);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        SpellInfo const* spell = GetSpellInfo();

        if (!caster || !target || !spell)
            return SPELL_CAST_OK;

        auto it = FrontBackstabSpells.find(spell->Id);
        if (it == FrontBackstabSpells.end())
            return SPELL_CAST_OK;

        // Front attack forbidden → fail cast
        if (!it->second.AllowFront && !target->isInBack(caster))
            return SPELL_FAILED_NOT_BEHIND;

        return SPELL_CAST_OK;
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        SpellInfo const* spell = GetSpellInfo();

        if (!caster || !target || !spell)
            return;

        auto it = FrontBackstabSpells.find(spell->Id);
        if (it == FrontBackstabSpells.end())
            return;

        // Front attack → reduce damage if factor > 1
        if (it->second.AllowFront && !target->isInBack(caster) && it->second.FrontFactor > 1.0f)
        {
            int32 dmg = GetHitDamage();
            dmg = int32(dmg / it->second.FrontFactor);
            SetHitDamage(dmg);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_front_backstab::CheckCast);
        OnHit       += SpellHitFn(spell_front_backstab::HandleOnHit);
    }
};

// ------------------------------------------------------
// WorldScript to load config
// ------------------------------------------------------
class FrontBackstabWorld : public WorldScript
{
public:
    FrontBackstabWorld() : WorldScript("FrontBackstabWorld") { }

    void OnStartup() override
    {
        LoadFrontBackstabConfig();
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        LoadFrontBackstabConfig();
    }
};

// ------------------------------------------------------
// Loader
// ------------------------------------------------------
class spell_front_backstab_loader : public SpellScriptLoader
{
public:
    spell_front_backstab_loader() : SpellScriptLoader("spell_front_backstab") { }

    SpellScript* GetSpellScript() const override
    {
        return new spell_front_backstab();
    }
};

// ------------------------------------------------------
// AddSC
// ------------------------------------------------------
void Addmod_front_backstabScripts()
{
    new FrontBackstabWorld();
    new spell_front_backstab_loader();
}
