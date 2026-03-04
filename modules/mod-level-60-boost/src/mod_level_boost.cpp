	#include "mod_level_boost.h"

	void LevelBoost::LoadTalentContainer()
	{
		QueryResult result = WorldDatabase.Query("SELECT `player_class`, `player_spec`, `talent_id` FROM `mod_boost_talents`");

		if (!result)
		{
			LOG_WARN("server.loading", ">> Loaded 0 talent templates");
			return;
		}

		talentTemplateList.clear();

		uint32 oldTime = getMSTime();
		uint32 count = 0;
		do
		{
			Field* fields = result->Fetch();
			TalentTemplate talent;
			talent.player_class = fields[0].Get<std::string>();
			talent.player_spec = fields[1].Get<std::string>();
			talent.talent_id = fields[2].Get<uint32>();
			talentTemplateList.push_back(talent);

			++count;
		} while (result->NextRow());

		LOG_INFO("module", ">> Loaded {} talent templates in {} ms.", count, GetMSTimeDiffToNow(oldTime));
	}

	void LevelBoost::LoadGlyphContainer()
	{
		QueryResult result = WorldDatabase.Query("SELECT `player_class`, `player_spec`, `glyph_slot`, `glyph_id` FROM `mod_boost_glyphs`");

		if (!result)
		{
			LOG_WARN("server.loading", ">> Loaded 0 glyph templates");
			return;
		}

		glyphTemplateList.clear();

		uint32 oldTime = getMSTime();
		uint32 count = 0;
		do
		{
			Field* fields = result->Fetch();
			GlyphTemplate glyph;
			glyph.player_class = fields[0].Get<std::string>();
			glyph.player_spec = fields[1].Get<std::string>();
			glyph.glyph_slot = fields[2].Get<uint8>();
			glyph.glyph_id = fields[3].Get<uint32>();
			glyphTemplateList.push_back(glyph);

			++count;
		} while (result->NextRow());

		LOG_INFO("module", ">> Loaded {} glyph templates in {} ms.", count, GetMSTimeDiffToNow(oldTime));
	}

	void LevelBoost::LoadGearContainer()
	{
		QueryResult result = WorldDatabase.Query("SELECT `player_class`, `player_spec`, `equipment_slot`, `item_entry` FROM `mod_boost_gear`");

		if (!result)
		{
			LOG_WARN("server.loading", ">> Loaded 0 gear templates");
			return;
		}

		gearTemplateList.clear();

		uint32 oldTime = getMSTime();
		uint32 count = 0;
		do
		{
			Field* fields = result->Fetch();
			GearTemplate gear;
			gear.player_class = fields[0].Get<std::string>();
			gear.player_spec = fields[1].Get<std::string>();
			gear.equipment_slot = fields[2].Get<uint8>();
			gear.item_entry = fields[3].Get<uint32>();
			gearTemplateList.push_back(gear);

			++count;
		} while (result->NextRow());

		LOG_INFO("module", ">> Loaded {} gear templates in {} ms.", count, GetMSTimeDiffToNow(oldTime));
	}

	void LevelBoost::LoadSpellContainer()
	{
		QueryResult result = WorldDatabase.Query("SELECT `class_id`, `spell_id`, `required_level`, `required_spell_id` FROM `mod_boost_class_spells` ORDER BY `class_id`, `required_level`");

		if (!result)
		{
			LOG_WARN("server.loading", ">> Loaded 0 spell templates");
			return;
		}

		classSpellsList.clear();

		uint32 oldTime = getMSTime();
		uint32 count = 0;
		do
		{
			Field* fields = result->Fetch();
			ClassSpells spell;
			spell.class_id = fields[0].Get<uint8>();
			spell.spell_id = fields[1].Get<uint32>();
			spell.required_level = fields[2].Get<uint32>();
			spell.required_spell = fields[3].Get<uint32>();
			classSpellsList.push_back(spell);

			++count;
		} while (result->NextRow());

		LOG_INFO("module", ">> Loaded {} spell templates in {} ms.", count, GetMSTimeDiffToNow(oldTime));
	}

	void LevelBoost::LoadProficiencyContainer()
	{
		QueryResult result = WorldDatabase.Query("SELECT `class_id`, `spell_id`, `required_level` FROM `mod_boost_class_proficiencies` ORDER BY `class_id`");

		if (!result)
		{
			LOG_WARN("server.loading", ">> Loaded 0 proficiency templates");
			return;
		}

		classProficienciesList.clear();

		uint32 oldTime = getMSTime();
		uint32 count = 0;
		do
		{
			Field* fields = result->Fetch();
			ClassProficiencies proficiencies;
			proficiencies.class_id = fields[0].Get<uint8>();
			proficiencies.spell_id = fields[1].Get<uint32>();
			proficiencies.required_level = fields[2].Get<uint32>();
			classProficienciesList.push_back(proficiencies);

			++count;
		} while (result->NextRow());

		LOG_INFO("module", ">> Loaded {} proficiency templates in {} ms.", count, GetMSTimeDiffToNow(oldTime));
	}

	void LevelBoost::LearnDualSpec(Player* player)
	{
		if (!dualSpec)
			return;

		player->CastSpell(player, TALENT_SPECIALIZATION_SWITCHES, player->GetGUID());
		player->CastSpell(player, SECOND_TALENT_SPECIALIZATION, player->GetGUID());
	}

	void LevelBoost::DestroyGear(Player* player)
	{
		if (!destroyGear)
			return;

		for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
		{
			if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			{
				player->DestroyItemCount(item->GetEntry(), 1, true, true);

				if (item)
				{
					player->DestroyItemCount(item->GetEntry(), 1, true, true);

					if (item->IsInWorld())
					{
						item->RemoveFromWorld();
						item->DestroyForPlayer(player);
					}

					item->SetUInt32Value(ITEM_FIELD_CONTAINED, 0);
					item->SetSlot(NULL_SLOT);
					item->SetState(ITEM_REMOVED, player);

				}
			}
		}
	}

	void LevelBoost::AddClassItems(Player* player)
	{
		std::string playerClass = GetClassString(player);

		for (auto& gearTemplate : gearTemplateList)
		{
			if (gearTemplate.player_class == playerClass &&
				gearTemplate.player_spec == "All")
			{
				uint32 count = (gearTemplate.equipment_slot > 0) ? gearTemplate.equipment_slot : 1;
				player->AddItem(gearTemplate.item_entry, count);
			}
		}
	}

	void LevelBoost::LearnSpellsForLevel(Player* player)
	{
		if (!learnSpells)
			return;

		for (auto& classSpell : classSpellsList)
		{
			if (player->getClass() == classSpell.class_id && player->GetLevel() >= classSpell.required_level)
			{
				if (classSpell.required_spell == 0 || player->HasSpell(classSpell.required_spell))
				{
					if (!player->HasSpell(classSpell.spell_id))
					{
						player->learnSpell(classSpell.spell_id);
					}
				}
			}
		}
	}

	void LevelBoost::LearnProficienciesForLevel(Player* player)
	{
		if (!learnProficiencies)
			return;

		for (auto& classProficiency : classProficienciesList)
		{
			if (player->getClass() == classProficiency.class_id && player->GetLevel() >= classProficiency.required_level)
			{
				if (!player->HasSpell(classProficiency.spell_id))
				{
					player->learnSpell(classProficiency.spell_id);
				}
			}
		}
	}

	void LevelBoost::CreateHunterPet(Player* player, Creature* creature, uint32 entry)
	{
		if (player->getClass() != CLASS_HUNTER)
			return;

		if (player->GetPet())
			return;

		Creature* tempCreature = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 500);

		if (!tempCreature)
			return;

		Pet* hunterPet = player->CreateTamedPetFrom(tempCreature, 0);

		if (!hunterPet)
			return;

		tempCreature->setDeathState(DeathState::JustDied);
		tempCreature->RemoveCorpse();
		tempCreature->SetHealth(0);

		hunterPet->SetPower(POWER_HAPPINESS, 1048000);

		if (!hunterPet->InitStatsForLevel(player->GetLevel()))
		{
			LOG_ERROR("server", "Pet Create fail: No init stats for pet with entry {}", entry);
			delete hunterPet;
			return;
		}

		hunterPet->GetMap()->AddToMap(hunterPet->ToCreature());
		hunterPet->UpdateAllStats();
		hunterPet->SetLevel(player->GetLevel() - 1);

		player->SetMinion(hunterPet, true);

		hunterPet->SavePetToDB(PET_SAVE_AS_CURRENT);
		player->PetSpellInitialize();

	}

	void LevelBoost::HandleBoost(Player* player, Creature* creature, const std::string& player_spec)
	{
		if (!ApplyFullTemplate(player, player_spec))
			return;

		switch (player->getRace())
		{
		case RACE_NIGHTELF:
			CreateHunterPet(player, creature, 2031);
			break;
		case RACE_HUMAN:
			CreateHunterPet(player, creature, 525);
			break;
		case RACE_DWARF:
		case RACE_GNOME:
			CreateHunterPet(player, creature, 705);
			break;
		case RACE_DRAENEI:
			CreateHunterPet(player, creature, 16520);
			break;
		case RACE_ORC:
			CreateHunterPet(player, creature, 3098);
			break;
		case RACE_TROLL:
			CreateHunterPet(player, creature, 3098);
			break;
		case RACE_TAUREN:
			CreateHunterPet(player, creature, 2955);
			break;
		case RACE_UNDEAD_PLAYER:
			CreateHunterPet(player, creature, 1508);
			break;
		case RACE_BLOODELF:
			CreateHunterPet(player, creature, 15366);
			break;
		}

		LearnDualSpec(player);
		LearnSpellsForLevel(player);
		LearnProficienciesForLevel(player);
		AddClassItems(player);
		
		player->UpdateSkillsToMaxSkillsForLevel();
		CloseGossipMenuFor(player);
		player->SendTalentsInfoData(false);
	}

	std::string LevelBoost::GetClassString(Player* player)
	{
		switch (player->getClass())
		{
		case CLASS_WARRIOR:
			return "Warrior";
			break;
		case CLASS_ROGUE:
			return "Rogue";
			break;
		case CLASS_SHAMAN:
			return "Shaman";
			break;
		case CLASS_HUNTER:
			return "Hunter";
			break;
		case CLASS_MAGE:
			return "Mage";
			break;
		case CLASS_WARLOCK:
			return "Warlock";
			break;
		case CLASS_PALADIN:
			return "Paladin";
			break;
		case CLASS_DRUID:
			return "Druid";
			break;
		case CLASS_PRIEST:
			return "Priest";
			break;
		case CLASS_DEATH_KNIGHT:
			return "Deathknight";
			break;
		}
		return "Unknown";
	}

	bool LevelBoost::TemplateExists(Player* player, const std::string& player_spec)
	{
		std::string playerClass = GetClassString(player);

		for (auto& gearTemplate : gearTemplateList)
		{
			if (gearTemplate.player_class != playerClass)
				continue;

			if (gearTemplate.player_spec == player_spec ||
				gearTemplate.player_spec == "All")
			{
				return true;
			}
		}

		return false;
	}
	
	void LevelBoost::ApplyGearTemplate(Player* player, const std::string& player_spec)
	{
		std::string playerClass = GetClassString(player);

		for (auto& gearTemplate : gearTemplateList)
		{
			if (gearTemplate.player_class == playerClass &&
				gearTemplate.player_spec == player_spec)
			{
				player->EquipNewItem(
					gearTemplate.equipment_slot,
					gearTemplate.item_entry,
					true);
			}
		}
	}

	void LevelBoost::DestroyProjectiles(Player* player)
	{
		if (player->getClass() != CLASS_HUNTER)
		{
			if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR)
			{
				player->AddItem(ITEM_BOOST_ARROWS, ARROW_COUNT);
				player->SetAmmo(ITEM_BOOST_ARROWS);
			}
			return;
		}

		if (player->HasItemCount(ITEM_DEFAULT_ARROWS))
		{
			player->DestroyItemCount(ITEM_DEFAULT_ARROWS, player->GetItemCount(ITEM_DEFAULT_ARROWS), true, true);
			player->AddItem(ITEM_BOOST_ARROWS, ARROW_COUNT);
			player->SetAmmo(ITEM_BOOST_ARROWS);
		}
		else
		{
			player->DestroyItemCount(ITEM_DEFAULT_BULLETS, player->GetItemCount(ITEM_DEFAULT_BULLETS), true, true);
			player->AddItem(ITEM_BOOST_BULLETS, BULLET_COUNT);
			player->SetAmmo(ITEM_BOOST_BULLETS);
		}
	}

	void LevelBoost::ApplyGlyphTemplate(Player* player, const std::string& player_spec)
	{
		if (!learnGlyphs)
			return;

		std::string playerClass = GetClassString(player);

		for (auto& glyphTemplate : glyphTemplateList)
		{
			if (glyphTemplate.player_class == playerClass &&
				glyphTemplate.player_spec == player_spec)
			{
				player->CastSpell(player, glyphTemplate.glyph_id, true);
				player->SetGlyph(
					glyphTemplate.glyph_slot,
					glyphTemplate.glyph_id,
					true);
			}
		}
	}

	void LevelBoost::ApplyTalentTemplate(Player* player, const std::string& player_spec)
	{
		if (!learnTalents)
			return;

		std::string playerClass = GetClassString(player);

		for (auto& talentTemplate : talentTemplateList)
		{
			if (talentTemplate.player_class == playerClass &&
				talentTemplate.player_spec == player_spec)
			{
				player->addTalent(
					talentTemplate.talent_id,
					player->GetActiveSpecMask(),
					0);
			}
		}

		player->SetFreeTalentPoints(0);
	}
	
	void LevelBoost::HandleDeathKnight(Player* player)
	{
		int STARTER_QUESTS[33] = { 12593, 12619, 12842, 12848, 12636, 12641, 12657, 12678, 12679, 12680, 12687, 12698, 12701, 12706, 12716, 12719, 12720, 12722, 12724, 12725, 12727, 12733, -1, 12751, 12754, 12755, 12756, 12757, 12779, 12801, 13165, 13166 };

		int specialSurpriseQuestId = -1;
		switch (player->getRace())
		{
		case RACE_TAUREN:
			specialSurpriseQuestId = 12739;
			break;
		case RACE_HUMAN:
			specialSurpriseQuestId = 12742;
			break;
		case RACE_NIGHTELF:
			specialSurpriseQuestId = 12743;
			break;
		case RACE_DWARF:
			specialSurpriseQuestId = 12744;
			break;
		case RACE_GNOME:
			specialSurpriseQuestId = 12745;
			break;
		case RACE_DRAENEI:
			specialSurpriseQuestId = 12746;
			break;
		case RACE_BLOODELF:
			specialSurpriseQuestId = 12747;
			break;
		case RACE_ORC:
			specialSurpriseQuestId = 12748;
			break;
		case RACE_TROLL:
			specialSurpriseQuestId = 12749;
			break;
		case RACE_UNDEAD_PLAYER:
			specialSurpriseQuestId = 12750;
			break;
		}

		STARTER_QUESTS[22] = specialSurpriseQuestId;
		STARTER_QUESTS[32] = player->GetTeamId() == TEAM_ALLIANCE ? 13188 : 13189;

		for (int questId : STARTER_QUESTS)
		{
			if (player->GetQuestStatus(questId) == QUEST_STATUS_NONE)
			{
				player->AddQuest(sObjectMgr->GetQuestTemplate(questId), nullptr);
				player->RewardQuest(sObjectMgr->GetQuestTemplate(questId), 0, player, false);
			}
		}
		
		for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
		{
			if (Bag* bag = player->GetBagByPos(i))
			{
				for (uint32 j = 0; j < bag->GetBagSize(); ++j)
				{
					player->DestroyItem(i, j, true);
				}
			}
		}

		for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
		{
			player->DestroyItem(INVENTORY_SLOT_BAG_0, i, true);
		}

		for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
		{
			player->DestroyItem(INVENTORY_SLOT_BAG_0, i, true);
		}
		
	}

	bool LevelBoost::ApplyFullTemplate(Player* player, const std::string& player_spec)
	{
		if (!TemplateExists(player, player_spec))
		{
			player->GetSession()->SendAreaTriggerMessage(
				"There's no template for %s specialization yet.",
				player_spec.c_str());
			return false;
		}
		
		if (player->getClass() == CLASS_DEATH_KNIGHT)
		{
			int32 playerMoney = player->GetMoney();
			HandleDeathKnight(player);
			player->SetMoney(playerMoney);
		}

		player->GiveLevel(60);

		if (player->GetMoney() < 100000)
			player->ModifyMoney(100000 - player->GetMoney());

		DestroyGear(player);
		DestroyProjectiles(player);
		ApplyGearTemplate(player, player_spec);
		ApplyGlyphTemplate(player, player_spec);
		ApplyTalentTemplate(player, player_spec);

		if (player->getPowerType() == POWER_MANA)
			player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

		player->SetHealth(player->GetMaxHealth());
		
		WorldLocation Aloc = WorldLocation(0, -8866.55f, 671.39f, 97.90f, 5.27f); // Stormwind
		WorldLocation Hloc = WorldLocation(1, 1637.62f, -4440.22f, 15.78f, 2.42f); // Orgrimmar

		if (player->GetTeamId() == TEAM_ALLIANCE)
		{
			player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f); //Stormwind
			player->SetHomebind(Aloc, 1637);
		}
		else
		{
			player->TeleportTo(1, 1569.59f, -4397.63f, 7.70f, 0.54f); //Orgrimmar
			player->SetHomebind(Hloc, 1653);
		}
		
		player->SaveToDB(false, false);

		return true;
	}

	void LevelBoost::ExtractGearTemplate(Player* player, const std::string& player_spec)
	{
		std::string playerClass = GetClassString(player);
		
		WorldDatabase.Query("DELETE FROM mod_boost_gear WHERE player_class = '{}' AND player_spec = '{}'", playerClass, player_spec);

		for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
		{
			if (i != EQUIPMENT_SLOT_BODY)
			{
				if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					WorldDatabase.Execute("INSERT INTO mod_boost_gear (player_class, player_spec, equipment_slot, item_entry) VALUES ('{}', '{}', '{}', '{}')", playerClass, player_spec, i, item->GetEntry());
				}
			}
		}
	}

	void LevelBoost::ExtractTalentTemplate(Player* player, const std::string& player_spec)
	{
		std::string playerClass = GetClassString(player);
		
		WorldDatabase.Query("DELETE FROM mod_boost_talents WHERE player_class = '{}' AND player_spec = '{}'", playerClass, player_spec);

		QueryResult result = CharacterDatabase.Query("SELECT spell FROM character_talent WHERE guid = '{}' AND specMask = '{}'", player->GetGUID().GetCounter(), player->GetActiveSpecMask());

		if (!result)
		{
			return;
		}
		else if (player->GetFreeTalentPoints() > 0)
		{
			return;
		}
		else
		{
			uint32 oldTime = getMSTime();
			uint32 count = 0;
			do
			{
				Field* fields = result->Fetch();
				uint32 spell = fields[0].Get<uint32>();
				WorldDatabase.Execute("INSERT INTO `mod_boost_talents` (`player_class`, `player_spec`, `talent_id`) VALUES ('{}', '{}', {})", playerClass, player_spec, spell);
				++count;
			} while (result->NextRow());

			LOG_INFO("module", ">> Extracted {} talent templates in {} ms.", count, GetMSTimeDiffToNow(oldTime));
		}
	}

	void LevelBoost::ExtractGlyphTemplate(Player* player, const std::string& player_spec)
	{
		std::string playerClass = GetClassString(player);
		
		WorldDatabase.Query("DELETE FROM mod_boost_glyphs WHERE player_class = '{}' AND player_spec = '{}'", playerClass, player_spec);

		QueryResult result = CharacterDatabase.Query("SELECT `glyph1`, `glyph2` FROM `character_glyphs` WHERE `guid`={} AND `talentGroup`={}", player->GetGUID().GetCounter(), player->GetActiveSpec());

		if (!result)
			return;

		for (uint8 slot = 0; slot < 2; ++slot)
		{
			if (!result)
				return;

			Field *fields = result->Fetch();
			uint32 glyph1 = fields[0].Get<uint32>();
			uint32 glyph2 = fields[1].Get<uint32>();

			uint32 storedGlyph;

			switch (slot)
			{
			case 0:
				storedGlyph = glyph1;
				break;
			case 1:
				storedGlyph = glyph2;
				break;
			default:
				break;
			}

			WorldDatabase.Execute("INSERT INTO `mod_boost_glyphs` (`player_class`, `player_spec`, `glyph_slot`, `glyph_id`) VALUES ('{}', '{}', {}, {});", playerClass, player_spec, slot, storedGlyph);
		}
	}

	void LevelBoost::ExtractTemplates(Player* player, const std::string& player_spec)
	{
		LOG_INFO("module", ">> Level 60 Boost: Extracting gear template for {} {}...", GetClassString(player), player_spec);

		ExtractGearTemplate(player, player_spec);
		ExtractTalentTemplate(player, player_spec);
		ExtractGlyphTemplate(player, player_spec);
	}

	class BoostNPC_Template : public CreatureScript
	{
	public:
		BoostNPC_Template() : CreatureScript("BoostNPC_Template") { }

		bool OnGossipHello(Player* player, Creature* creature)
		{
			ClearGossipMenuFor(player);

			if ((player->getClass() != CLASS_DEATH_KNIGHT && player->GetLevel() != 1) || (player->getClass() == CLASS_DEATH_KNIGHT && player->GetLevel() != 55) )
				return false;

			if (creature->IsQuestGiver())
				player->PrepareQuestMenu(creature->GetGUID());

			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Erzähl mir mehr über den Charakterboost auf Stufe 60.", GOSSIP_SENDER_MAIN, GOSSIP_LEVEL_60_BOOST);

			switch (player->getRace())
			{
			case RACE_HUMAN:
				SendGossipMenuFor(player, 50016, creature->GetGUID());
				break;
			case RACE_NIGHTELF:
				SendGossipMenuFor(player, 4936, creature->GetGUID());
				break;
			case RACE_DWARF:
				SendGossipMenuFor(player, 4937, creature->GetGUID());
				break;
			case RACE_GNOME:
				SendGossipMenuFor(player, 4937, creature->GetGUID());
				break;
			case RACE_DRAENEI:
				SendGossipMenuFor(player, 8667, creature->GetGUID());
				break;
			case RACE_ORC:
				SendGossipMenuFor(player, 3583, creature->GetGUID());
				break;
			case RACE_TROLL:
				SendGossipMenuFor(player, 3583, creature->GetGUID());
				break;
			case RACE_TAUREN:
				SendGossipMenuFor(player, 4935, creature->GetGUID());
				break;
			case RACE_BLOODELF:
				SendGossipMenuFor(player, 16703, creature->GetGUID());
				break;
			case RACE_UNDEAD_PLAYER:
				SendGossipMenuFor(player, 938, creature->GetGUID());
				break;
			}

			return true;
		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
		{
			if (sender != GOSSIP_SENDER_MAIN)
				return false;

			if (action == GOSSIP_MAIN_MENU)
			{
				OnGossipHello(player, creature);
			}
			else if (action == GOSSIP_LEVEL_60_BOOST)
			{
				LOG_INFO("server.worldserver", ">> Level 60 Boost: GOSSIP_LEVEL_60_BOOST selected.");
				ClearGossipMenuFor(player);
				AddOptionsForClass(player);
				SendGossipMenuFor(player, BOOST_TEXT, creature->GetGUID());
			}

			switch (action)
			{
				case GOSSIP_GEAR + 1:
					sLevelBoost->HandleBoost(player, creature, "Arms");
					break;

				case GOSSIP_GEAR + 2:
					sLevelBoost->HandleBoost(player, creature, "Fury");
					break;

				case GOSSIP_GEAR + 3:
					sLevelBoost->HandleBoost(player, creature, "Protection");
					break;

				case GOSSIP_GEAR + 4:
					sLevelBoost->HandleBoost(player, creature, "Assassination");
					break;

				case GOSSIP_GEAR + 5:
					sLevelBoost->HandleBoost(player, creature, "Combat");
					break;

				case GOSSIP_GEAR + 6:
					sLevelBoost->HandleBoost(player, creature, "Subtlety");
					break;

				case GOSSIP_GEAR + 7:
					sLevelBoost->HandleBoost(player, creature, "Elemental");
					break;

				case GOSSIP_GEAR + 8:
					sLevelBoost->HandleBoost(player, creature, "Enhancement");
					break;

				case GOSSIP_GEAR + 9:
					sLevelBoost->HandleBoost(player, creature, "Restoration");
					break;

				case GOSSIP_GEAR + 10:
					sLevelBoost->HandleBoost(player, creature, "Beast Mastery");
					break;

				case GOSSIP_GEAR + 11:
					sLevelBoost->HandleBoost(player, creature, "Marksmanship");
					break;

				case GOSSIP_GEAR + 12:
					sLevelBoost->HandleBoost(player, creature, "Survival");
					break;

				case GOSSIP_GEAR + 13:
					sLevelBoost->HandleBoost(player, creature, "Arcane");
					break;

				case GOSSIP_GEAR + 14:
					sLevelBoost->HandleBoost(player, creature, "Fire");
					break;

				case GOSSIP_GEAR + 15:
					sLevelBoost->HandleBoost(player, creature, "Frost");
					break;

				case GOSSIP_GEAR + 16:
					sLevelBoost->HandleBoost(player, creature, "Affliction");
					break;

				case GOSSIP_GEAR + 17:
					sLevelBoost->HandleBoost(player, creature, "Demonology");
					break;

				case GOSSIP_GEAR + 18:
					sLevelBoost->HandleBoost(player, creature, "Destruction");
					break;

				case GOSSIP_GEAR + 19:
					sLevelBoost->HandleBoost(player, creature, "Holy");
					break;

				case GOSSIP_GEAR + 20:
					sLevelBoost->HandleBoost(player, creature, "Protection");
					break;

				case GOSSIP_GEAR + 21:
					sLevelBoost->HandleBoost(player, creature, "Retribution");
					break;

				case GOSSIP_GEAR + 22:
					sLevelBoost->HandleBoost(player, creature, "Balance");
					break;

				case GOSSIP_GEAR + 23:
					sLevelBoost->HandleBoost(player, creature, "Feral");
					break;

				case GOSSIP_GEAR + 24:
					sLevelBoost->HandleBoost(player, creature, "Restoration");
					break;

				case GOSSIP_GEAR + 25:
					sLevelBoost->HandleBoost(player, creature, "Discipline");
					break;

				case GOSSIP_GEAR + 26:
					sLevelBoost->HandleBoost(player, creature, "Holy");
					break;

				case GOSSIP_GEAR + 27:
					sLevelBoost->HandleBoost(player, creature, "Shadow");
					break;

				case GOSSIP_GEAR + 28:
					sLevelBoost->HandleBoost(player, creature, "Blood");
					break;

				case GOSSIP_GEAR + 29:
					sLevelBoost->HandleBoost(player, creature, "Frost");
					break;

				case GOSSIP_GEAR + 30:
					sLevelBoost->HandleBoost(player, creature, "Unholy");
					break;
			}

			return true;
		}

		void AddOptionsForClass(Player* player)
		{
			switch (player->getClass())
			{
				case CLASS_WARRIOR:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Waffen", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 1);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Furor", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 2);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Schutz", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 3);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_ROGUE:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Meucheln", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 4);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Kampf", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 5);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Täuschung", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 6);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_SHAMAN:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Elementar", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 7);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Verstärkung", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 8);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Wiederherstellung", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 9);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_HUNTER:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Tierherrschaft", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 10);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Treffsicherheit", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 11);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Überleben", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 12);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_MAGE:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Arkan", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 13);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Feuer", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 14);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Frost", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 15);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_WARLOCK:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Gebrechen", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 16);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Dämonologie", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 17);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zerstörung", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 18);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_PALADIN:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Heilig", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 19);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Schutz", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 20);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Vergeltung", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 21);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_DRUID:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Gleichgewicht", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 22);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Wildheit", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 23);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Wiederherstellung", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 24);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_PRIEST:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Disziplin", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 25);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Heilig", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 26);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Schatten", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 27);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;

				case CLASS_DEATH_KNIGHT:
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Blut", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 28);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Frost", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 29);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Unheilig", GOSSIP_SENDER_MAIN, GOSSIP_GEAR + 30);
					AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Zurück", GOSSIP_SENDER_MAIN, GOSSIP_MAIN_MENU);
					break;
			}
		}
	};

	class BoostNPC_World : public WorldScript
	{
	public:
		BoostNPC_World(): WorldScript("BoostNPC_World") { }

		void OnBeforeConfigLoad(bool /*reload*/) override
		{
			LoadConfig();
		}

		void OnStartup() override
		{
			LOG_INFO("module", ">> Loading Spell Container...");
			sLevelBoost->LoadSpellContainer();

			LOG_INFO("module", ">> Loading Proficiency Container...");
			sLevelBoost->LoadProficiencyContainer();

			LOG_INFO("module", ">> Loading Gear Container...");
			sLevelBoost->LoadGearContainer();

			LOG_INFO("module", ">> Loading Talent Container...");
			sLevelBoost->LoadTalentContainer();

			LOG_INFO("module", ">> Loading Glyph Container...");
			sLevelBoost->LoadGlyphContainer();

		}

		static void LoadConfig()
		{
			uint32 oldTime = getMSTime();

			sLevelBoost->levelBoost = sConfigMgr->GetOption<bool>("LevelBoost.Enable", true);
			sLevelBoost->dualSpec = sConfigMgr->GetOption<bool>("DualSpec.Enable", true);
			sLevelBoost->learnSpells = sConfigMgr->GetOption<bool>("LearnSpells.Enable", true);
			sLevelBoost->learnProficiencies = sConfigMgr->GetOption<bool>("LearnProficiencies.Enable", true);
			sLevelBoost->learnTalents = sConfigMgr->GetOption<bool>("LearnTalents.Enable", true);
			sLevelBoost->learnGlyphs = sConfigMgr->GetOption<bool>("LearnGlyphs.Enable", true);
			sLevelBoost->destroyGear = sConfigMgr->GetOption<bool>("DestroyGear.Enable", true);

			LOG_INFO("module", ">> Loaded Level 60 Boost Config in {} ms.", GetMSTimeDiffToNow(oldTime));
		}
	};

	using namespace Acore::ChatCommands;

	class BoostNPC_Command : public CommandScript
	{
	public:
		BoostNPC_Command() : CommandScript("BoostNPC_Command") { }

		ChatCommandTable GetCommands() const override
		{
			static ChatCommandTable LevelBoostTable =
			{
				{ "reload", HandleTableReload, SEC_ADMINISTRATOR, Console::No },
				{ "extract", HandleExtractTemplate, SEC_ADMINISTRATOR, Console::No },
			};

			static ChatCommandTable commandTable =
			{
				{ "levelboost", LevelBoostTable }
			};

			return commandTable;
		}

		static bool HandleTableReload(ChatHandler* handler)
		{
			LOG_INFO("module", ">> Reloading templates for Level 60 Boost...");
			sLevelBoost->LoadSpellContainer();
			sLevelBoost->LoadProficiencyContainer();
			sLevelBoost->LoadGearContainer();
			sLevelBoost->LoadTalentContainer();
			sLevelBoost->LoadGlyphContainer();
			handler->SendGlobalSysMessage("Level 60 Boost templates reloaded.");
			return true;
		}

		static bool HandleExtractTemplate(ChatHandler* handler, std::string player_spec)
		{
			Player* player = handler->GetSession()->GetPlayer();

			if (!player)
			{
				LOG_INFO("module", ">> Level 60 Boost: No player selected.");
				return false;
			}

			CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
			player->SaveToDB(trans, false, false);
			CharacterDatabase.CommitTransaction(trans);

			sLevelBoost->player_spec = player_spec;
			sLevelBoost->ExtractTemplates(player, sLevelBoost->player_spec);
			handler->SendSysMessage("Successfully extracted template.");

			return true;
		}
	};

	void AddSC_BoostNPC()
	{
		new BoostNPC_Template();
		new BoostNPC_World();
		new BoostNPC_Command();
	}
