#include "ScriptMgr.h"
#include "SpellScript.h"
#include "Player.h"
#include "Pet.h"

enum Spells
{
    SPELL_EXHILARATION_PET = 90005
};

class spell_hunter_exhilaration : public SpellScript
{
    PrepareSpellScript(spell_hunter_exhilaration);

    void HandleAfterCast()
	{
		Player* caster = GetCaster()->ToPlayer();
		if (!caster)
			return;

		Pet* pet = caster->GetPet();
		if (!pet || !pet->IsAlive())
			return;

		caster->CastSpell(pet, SPELL_EXHILARATION_PET, true);
	}

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hunter_exhilaration::HandleAfterCast);
    }
};

class spell_hunter_exhilaration_loader : public SpellScriptLoader
{
public:
    spell_hunter_exhilaration_loader() : SpellScriptLoader("spell_hunter_exhilaration") { }

    SpellScript* GetSpellScript() const override
    {
        return new spell_hunter_exhilaration();
    }
};

void Addmod_hunter_exhilarationScripts()
{
    new spell_hunter_exhilaration_loader();
}
