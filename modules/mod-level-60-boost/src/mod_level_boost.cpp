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
			player->DestroyItem(INVENTORY_SLOT_BAG_0, i, true);
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

void LevelBoost::AddClassItems(Player* player)
{
	std::string playerClass = GetClassString(player);
	
	player->AddItem(6948, 1); // Hearthstone
	
	player->AddItem(2901, 1); // Pickaxe
	player->AddItem(7005, 1); // Skinning Knife
	player->AddItem(45120, 1); // Fishing Pole
	
	if (playerClass == "Deathknight")
		player->AddItem(41751, 20); // Food
	else
		player->AddItem(27854, 20); // Food
	
	if (player->getPowerType() == POWER_MANA)
		player->AddItem(28399, 20); // Drink
	
	player->AddItem(14530, 20); // Bandages
	
	if ( playerClass == "Hunter" || playerClass == "Rogue" || playerClass == "Warrior" )
	{
		player->AddItem(28053, 1000);
		player->SetAmmo(28053);
	}

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
	
	if (player->getClass() == CLASS_MAGE)
	{
		std::vector<uint32> teleportSpells;
		if (player->GetTeamId() == TEAM_ALLIANCE)
		{
			teleportSpells = {3561,3562,3565,32271,49359,10059,11416,11419,32266,49360};
		}
		else
		{
			teleportSpells = {3567,3566,3563,32272,49358,11417,11420,11418,32267,49361};
		}
		
		for (uint32 spellId : teleportSpells)
		{
			player->learnSpell(spellId, false);
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

	std::vector<uint32> teacherSpells = {
		3273, 2366, 2368, 2539, 2541, 2544, 2546, 2550, 2575, 2576, 2658, 2659, 3102,
		3274, 3276, 3277, 3278, 3304, 3307, 3308, 3413, 3564, 3569, 
		3570, 6499, 6500, 7620, 7731, 7732, 7924, 7928, 7929, 7934, 8613, 
		8617, 8618, 10097, 10098, 10248, 10768, 10840, 10841, 10846, 11993, 
		16153, 18248, 18260, 18629, 18630, 21175, 37836, 70524
	};

	for (uint32 spellId : teacherSpells)
	{
		player->learnSpell(spellId, false);
	}
	
	player->SetSkill(186, 0, 300, 300);
	player->SetSkill(182, 0, 300, 300);
	player->SetSkill(393, 0, 300, 300);
	player->SetSkill(129, 0, 300, 300);
	player->SetSkill(185, 0, 300, 300);
	player->SetSkill(356, 0, 300, 300);
	
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

std::vector<int> LevelBoost::GetAvailableFlightPaths(Player* player)
{
	std::vector<int> flightpaths;

	flightpaths.push_back(79); // Marshal's Refuge, Un'Goro Crater
	flightpaths.push_back(80); // Ratchet, The Barrens
	flightpaths.push_back(166); // Emerald Sanctuary, Felwood
	flightpaths.push_back(179); // Mudsprocket, Dustwallow Marsh
	flightpaths.push_back(205); // Hatchet Hills, Ghostlands
	flightpaths.push_back(383); // Thondoril River, Western Plaguelands

	if (player->GetTeamId() == TEAM_ALLIANCE)
	{
		flightpaths.push_back(2); // Stormwind City
		flightpaths.push_back(4); // Sentinel Hill, Westfall
		flightpaths.push_back(5); // Lakeshire, Redridge Mountains
		flightpaths.push_back(6); // Ironforge, Dun Morogh
		flightpaths.push_back(7); // Menethil Harbor, Wetlands
		flightpaths.push_back(8); // Thelsamar, Loch Modan
		flightpaths.push_back(12); // Darkshire, Duskwood
		flightpaths.push_back(14); // Southshore, Hillsbrad Foothills
		flightpaths.push_back(16); // Refuge Pointe, Arathi Highlands
		flightpaths.push_back(19); // Booty Bay, Stranglethorn Vale
		flightpaths.push_back(26); // Auberdine, Darkshore
		flightpaths.push_back(27); // Rut'theran Village, Teldrassil
		flightpaths.push_back(28); // Astranaar, Ashenvale
		flightpaths.push_back(31); // Thalanaar, Feralas
		flightpaths.push_back(32); // Theramore Isle, Dustwallow Marsh
		flightpaths.push_back(33); // Stonetalon Peak, Stonetalon Mountains
		flightpaths.push_back(37); // Nijel's Point, Desolace
		flightpaths.push_back(38); // Shadowprey Village, Desolace
		flightpaths.push_back(39); // Gadgetzan, Tanaris
		flightpaths.push_back(41); // Feathermoon Stronghold, Feralas
		flightpaths.push_back(43); // Aerie Peak, The Hinterlands
		flightpaths.push_back(45); // Nethergarde Keep, Blasted Lands
		flightpaths.push_back(49); // Moonglade
		flightpaths.push_back(52); // Everlook, Winterspring
		flightpaths.push_back(62); // Nighthaven, Moonglade
		flightpaths.push_back(64); // Talrendis Point, Azshara
		flightpaths.push_back(65); // Talonbranch Glade, Felwood
		flightpaths.push_back(66); // Chillwind Camp, Western Plaguelands
		flightpaths.push_back(67); // Light's Hope Chapel, Eastern Plaguelands
		flightpaths.push_back(71); // Morgan's Vigil, Burning Steppes
		flightpaths.push_back(73); // Cenarion Hold, Silithus
		flightpaths.push_back(74); // Thorium Point, Searing Gorge
		flightpaths.push_back(93); // Blood Watch, Bloodmyst Isle
		flightpaths.push_back(94); // The Exodar
		flightpaths.push_back(167); // Forest Song, Ashenvale
		flightpaths.push_back(195); // Rebel Camp, Stranglethorn Vale
	}
	else if (player->GetTeamId() == TEAM_HORDE)
	{
		flightpaths.push_back(10); // The Sepulcher, Silverpine Forest
		flightpaths.push_back(11); // Undercity
		flightpaths.push_back(13); // Tarren Mill, Hillsbrad Foothills
		flightpaths.push_back(17); // Hammerfall, Arathi Highlands
		flightpaths.push_back(18); // Booty Bay, Stranglethorn Vale
		flightpaths.push_back(20); // Grom'gol, Stranglethorn Vale
		flightpaths.push_back(21); // Kargath, Badlands
		flightpaths.push_back(22); // Thunder Bluff
		flightpaths.push_back(23); // Orgrimmar
		flightpaths.push_back(25); // The Crossroads, The Barrens
		flightpaths.push_back(29); // Sun Rock Retreat, Stonetalon Mountains
		flightpaths.push_back(30); // Freewind Post, Thousand Needles
		flightpaths.push_back(38); // Shadowprey Village, Desolace
		flightpaths.push_back(40); // Gadgetzan, Tanaris
		flightpaths.push_back(42); // Camp Mojache, Feralas
		flightpaths.push_back(44); // Valormok, Azshara
		flightpaths.push_back(48); // Bloodvenom Post, Felwood
		flightpaths.push_back(53); // Everlook, Winterspring
		flightpaths.push_back(55); // Brackenwall Village, Dustwallow Marsh
		flightpaths.push_back(56); // Stonard, Swamp of Sorrows
		flightpaths.push_back(58); // Zoram'gar Outpost, Ashenvale
		flightpaths.push_back(61); // Splintertree Post, Ashenvale
		flightpaths.push_back(63); // Nighthaven, Moonglade
		flightpaths.push_back(68); // Light's Hope Chapel, Eastern Plaguelands
		flightpaths.push_back(69); // Moonglade
		flightpaths.push_back(70); // Flame Crest, Burning Steppes
		flightpaths.push_back(72); // Cenarion Hold, Silithus
		flightpaths.push_back(75); // Thorium Point, Searing Gorge
		flightpaths.push_back(76); // Revantusk Village, The Hinterlands
		flightpaths.push_back(77); // Camp Taurajo, The Barrens
		flightpaths.push_back(82); // Silvermoon City
		flightpaths.push_back(83); // Tranquillien, Ghostlands
		flightpaths.push_back(384); // The Bulwark, Tirisfal Glades
	}
	
	return flightpaths;
	
}

void LevelBoost::UnlockFlightPaths(Player* player)
{
    std::vector<int> flightpaths = GetAvailableFlightPaths(player);
    if (flightpaths.empty())
		return;
	
	for (auto& flightpath : flightpaths)
    {
        player->GetSession()->SendDiscoverNewTaxiNode(flightpath);
    }
}

void LevelBoost::HandleBoost(Player* player, Creature* creature, const std::string& player_spec)
{
	if (!ApplyFullTemplate(player, player_spec))
		return;

	switch (player->getRace())
	{
		case RACE_NIGHTELF:
		case RACE_DRAENEI:
			CreateHunterPet(player, creature, 2031);
			break;
		case RACE_HUMAN:
			CreateHunterPet(player, creature, 525);
			break;
		case RACE_DWARF:
		case RACE_GNOME:
			CreateHunterPet(player, creature, 705);
			break;
		case RACE_ORC:
		case RACE_TROLL:
			CreateHunterPet(player, creature, 3121);
			break;
		case RACE_TAUREN:
			CreateHunterPet(player, creature, 3035);
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
	GetMount(player);
	LearnProficienciesForLevel(player);
	AddClassItems(player);
	
	UnlockFlightPaths(player);
	
	player->UpdateSkillsToMaxSkillsForLevel();
	CloseGossipMenuFor(player);
	player->SendTalentsInfoData(false);
	
	WorldLocation Aloc = WorldLocation(0, -8866.55f, 671.39f, 97.90f, 5.27f); // Stormwind
	WorldLocation Hloc = WorldLocation(1, 1637.62f, -4440.22f, 15.78f, 2.42f); // Orgrimmar

	if (player->GetTeamId() == TEAM_ALLIANCE)
	{
		player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f); //Stormwind
		player->SetHomebind(Aloc, 1519);
	}
	else
	{
		player->TeleportTo(1, 1569.59f, -4397.63f, 7.70f, 0.54f); //Orgrimmar
		player->SetHomebind(Hloc, 1653);
	}
	
	player->SaveToDB(false, false);
	
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
	
}

void LevelBoost::GetMount(Player* player)
{

	if (!player->HasSpell(75614))
	{
		if (!player->HasSpell(33388))
			player->learnSpell(33388);
		player->learnSpell(75614);
	}
	
	if (!player->HasSpell(33391) && learnEpicMount)
	{
		player->learnSpell(33391);
	}
	
	uint32 classMountN = 0;
	uint32 classMountE = 0;
	
	if (player->getClass() == CLASS_PALADIN)
	{
		
		classMountN = 1661;
		classMountE = 7647;
			
		if (player->GetTeamId() == TEAM_HORDE)
		{
			classMountN = 9712;
			classMountE = 9737;
		}
		
	}
	
	if ( player->getClass() == CLASS_WARLOCK)
	{
		classMountN = 4490;
		classMountE = 7631;
	}
	
	int32 playerMoney = player->GetMoney();
		
	if (!player->HasSpell(classMountN) && classMountN > 0)
	{
		player->AddQuest(sObjectMgr->GetQuestTemplate(classMountN), nullptr);
		player->RewardQuest(sObjectMgr->GetQuestTemplate(classMountN), 0, player, false);
	}
	
	if (!player->HasSpell(classMountE) && classMountE > 0 && learnEpicMount)
	{
		player->AddQuest(sObjectMgr->GetQuestTemplate(classMountE), nullptr);
		player->RewardQuest(sObjectMgr->GetQuestTemplate(classMountE), 0, player, false);
	}
	
	player->SetMoney(playerMoney);
	
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
	player->SetUInt32Value(PLAYER_XP, 0);

	if (player->GetMoney() < 100000)
		player->ModifyMoney(100000 - player->GetMoney());

	DestroyGear(player);
	ApplyGearTemplate(player, player_spec);
	ApplyGlyphTemplate(player, player_spec);
	ApplyTalentTemplate(player, player_spec);

	if (player->getPowerType() == POWER_MANA)
		player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

	player->SetHealth(player->GetMaxHealth());

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
		
		uint32 noQuests = (player->GetRewardedQuestCount() == 0);
		uint32 noKills = true;
		if (AchievementCriteriaEntry const* CriteriaEntry = sAchievementCriteriaStore.LookupEntry(4944))
		if (player->GetAchievementMgr()->GetCriteriaProgress(CriteriaEntry))
			noKills = false;

		if (!noQuests || !noKills ||
			(player->getClass() != CLASS_DEATH_KNIGHT && player->GetLevel() != 1) || 
			(player->getClass() == CLASS_DEATH_KNIGHT && player->GetLevel() != 55))
		{
			return false;
		}

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
		sLevelBoost->learnEpicMount = sConfigMgr->GetOption<bool>("LearnEpicMount.Enable", true);
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
