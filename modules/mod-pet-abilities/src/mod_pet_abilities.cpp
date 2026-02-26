#include "ScriptMgr.h"
#include "PetScript.h"
#include "Pet.h"
#include "Config.h"
#include "SpellMgr.h"
#include "SpellInfo.h"
#include "EventMap.h"

namespace PetAbilitiesConfig
{
    bool Enable = true;
    bool BearRavage = true;
    bool OtherSwipe = true;

    void Load()
    {
        Enable       = sConfigMgr->GetOption<bool>("PetAbilities.Enable", true);
        BearRavage   = sConfigMgr->GetOption<bool>("PetAbilities.BearRavage", true);
        OtherSwipe   = sConfigMgr->GetOption<bool>("PetAbilities.OtherSwipe", true);
    }
}

class mod_pet_abilities : public PetScript
{
public:
    mod_pet_abilities() : PetScript("mod_pet_abilities") { }

    void OnInitStatsForLevel(Guardian* guardian, uint8) override
    {
        if (!PetAbilitiesConfig::Enable)
			return;

        Pet* pet = guardian->ToPet();
        if (!pet || pet->getPetType() != HUNTER_PET)
            return;

        pet->m_Events.AddEvent(
            new ApplyAbilitiesEvent(pet),
            pet->m_Events.CalculateTime(100) // 1 tick delay
        );
    }

private:
    class ApplyAbilitiesEvent : public BasicEvent
    {
    public:
        ApplyAbilitiesEvent(Pet* pet) : _pet(pet) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/) override
        {
            if (!_pet || !_pet->IsInWorld())
                return true;

            ApplyAbilities(_pet);
            return true; // one-shot
        }

    private:
        Pet* _pet;

        static void ApplyAbilities(Pet* pet)
        {
            CreatureTemplate const* cInfo = pet->GetCreatureTemplate();
            if (!cInfo)
                return;

            uint8 level = pet->GetLevel();

            // ===== BEARS → RAVAGE =====
            if (cInfo->family == CREATURE_FAMILY_BEAR && PetAbilitiesConfig::BearRavage)
            {
                static uint32 const RavageRanks[] = {50518, 53558, 53559, 53560, 53561, 53562};
                LearnRankForLevel(pet, RavageRanks, level);
            }
            // ===== OTHERS → SWIPE =====
            else if (cInfo->family != CREATURE_FAMILY_BEAR && PetAbilitiesConfig::OtherSwipe)
            {
                static uint32 const SwipeRanks[] = {50256, 53526, 53528, 53529, 53532, 53533};
                LearnRankForLevel(pet, SwipeRanks, level);
            }
        }

        static void LearnRankForLevel(Pet* pet, uint32 const* spells, uint8 level)
        {
            uint32 chosenSpell = 0;

            for (uint8 i = 0; i < 6; ++i)
            {
                if (SpellInfo const* info = sSpellMgr->GetSpellInfo(spells[i]))
                    if (info->SpellLevel <= level)
                        chosenSpell = spells[i];
            }

            if (chosenSpell && !pet->HasSpell(chosenSpell))
                pet->learnSpell(chosenSpell);
        }
    };
};

// ------------------- WorldScript -------------------
class PetAbilities_WorldScript : public WorldScript
{
public:
    PetAbilities_WorldScript() : WorldScript("PetAbilities_WorldScript") {}

    void OnStartup() override
    {
        PetAbilitiesConfig::Load();
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        PetAbilitiesConfig::Load();
    }
};

// ---------- SCRIPT LOADER ----------
void Addmod_pet_abilitiesScripts()
{
    new mod_pet_abilities();
    new PetAbilities_WorldScript();
}
