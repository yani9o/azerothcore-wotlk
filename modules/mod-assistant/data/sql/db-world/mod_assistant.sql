SET
@Entry      := 9000000,
@Model      := 28306,
@Name       := "Arthur",
@Title      := "Dienstleistungen",
@Icon       := "Speak",
@MinLevel   := 30,
@MaxLevel   := 30,
@Faction    := 35,
@NPCFlag    := 129,
@Type       := 7,
@FlagsExtra := 16777218,
@Script     := "npc_assistant";

DELETE FROM `creature_template` WHERE `entry`=@Entry;
INSERT INTO `creature_template` (`entry`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `unit_class`, `unit_flags`, `type`, `flags_extra`, `ScriptName`) VALUES
(@Entry, @Name, @Title, @Icon, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 2, @Type, @FlagsExtra, @Script);

DELETE FROM `creature_template_model` WHERE `CreatureID`=@Entry;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`) VALUES
(@Entry, 0, @Model, 1, 1);

DELETE FROM `creature` WHERE `id1`=@Entry;
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES
(@Entry, 0, -8824.65, 649.467, 94.5585, 4.47955), -- Stormwind City
(@Entry, 0, -4956.91, -932.369, 501.66, 4.77523), -- City of Ironforge
(@Entry, 0, 1590.66, 272.521, -55.3428, 0.361283), -- Undercity
(@Entry, 1, 9929.71, 2507.59, 1318.17, 4.78701), -- Darnassus
(@Entry, 1, 1619.08, -4443.65, 10.869, 1.73804), -- Orgrimmar
(@Entry, 1, -1292.12, 116.913, 131.175, 5.78446), -- Thunder Bluff
(@Entry, 530, -3955.07, -11670, -138.757, 3.29082), -- The Exodar
(@Entry, 530, 9469.83, -7294.44, 14.3078, 0.105431), -- Silvermoon City
(@Entry, 530, -1825.39, 5396.21, -12.4278, 2.44332), -- Shattrath City
(@Entry, 571, 5790.9, 560.993, 650.693, 1.62429); -- Dalaran

-- DELETE FROM `conditions` WHERE `SourceEntry` = 24425 AND `ConditionTypeOrReference` = 27; -- Remove Max-Level for Zandalar Buff

-- Container
DELETE FROM `item_template` WHERE (`entry` = 60000);
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(60000, 1, 0, -1, 'Lagerbox', 67129, 5, 0, 0, 1, 100000000, 0, 18, -1, -1, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 2, '', 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1784, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 12340);


DELETE FROM `npc_vendor` WHERE `entry` BETWEEN @Entry AND @Entry+45;
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES
(@Entry+45, 60000); -- Resource Container

UPDATE item_template SET stackable = 200 WHERE stackable > 1 AND stackable < 200;