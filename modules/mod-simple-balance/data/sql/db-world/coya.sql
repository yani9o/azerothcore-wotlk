-- ##########################################
-- ## CoYa QOL Changes                      #
-- ##########################################

-- Riding Turtle for all new Characters
REPLACE INTO `playercreateinfo_spell_custom` (`racemask`, `classmask`, `Spell`, `Note`) 
VALUES (0, 0, 30174, 'Custom - Riding Turtle');

-- Set Hearthstone Cooldown to 10 Minutes
REPLACE INTO `spell_cooldown_overrides` (`Id`, `RecoveryTime`, `CategoryRecoveryTime`, `StartRecoveryTime`, `StartRecoveryCategory`, `COMMENT`) VALUES 
(8690, 600000, 600000, 0, 0, 'Custom - Hearthstone'),
(75136, 600000, 600000, 0, 0, 'Custom - Ethereal Portal');

-- Mailboxes in Starting Zones
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`, `Comment`) VALUES 
(2135588, 142109, 1, 0, 0, 1, 1, 10400.9, 742.073, 1319.55, 3.70602, 0, 0, -0.960441, 0.278484, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135589, 142102, 0, 0, 0, 1, 1, -6167.81, 375.605, 399.023, 3.14031, 0, 0, -1, -0.000638918, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135590, 142075, 0, 0, 0, 1, 1, -8923.91, -136.852, 80.9728, 1.93871, 0, 0, -0.82452, -0.565832, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135591, 183857, 530, 0, 0, 1, 1, -4050.34, -13779.9, 75.1525, 5.91793, 0, 0, -0.181616, 0.983369, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135592, 143981, 1, 0, 0, 1, 1, -598.741, -4201.12, 39.7726, 4.70437, 0, 0, -0.709936, 0.704266, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135593, 143984, 1, 0, 0, 1, 1, -2885.89, -227.09, 53.9161, 3.88913, 0, 0, -0.930958, 0.365127, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135594, 143984, 0, 0, 0, 1, 1, 1863.97, 1579.76, 93.4618, 1.51944, 0, 0, -0.688718, -0.725029, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135595, 182359, 530, 0, 0, 1, 1, 10340.4, -6374.57, 35.5764, 1.84933, 0, 0, -0.798421, -0.6021, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox');

-- Set DualSpec to 10g
UPDATE gossip_menu_option SET `BoxMoney` = 100000 WHERE BoxText LIKE "%Dual Talent%";

-- Itemstacks to 200
UPDATE item_template SET stackable = 200 WHERE stackable > 1 AND stackable < 200;

-- Echeyakee for Alliance
REPLACE INTO `creature_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
(3241, 10327, 0, 1, 0, 1, 0, 1, 1, 'Custom - Savannah Patriarch, Horn of Echeyakee'),
(3416, 10327, 0, 1, 0, 1, 0, 1, 1, 'Custom - Savannah Matriarch, Horn of Echeyakee');



-- ##########################################
-- ## Class/Spell Changes                   #
-- ##########################################

-- Remove Custom Spells
DELETE FROM `trainer_spell` WHERE `SpellId` IN (190001,190002,190003,190004);

-- DEATHKNIGHT
-- Rime for FrostStrike and Deathstrike
UPDATE `spell_proc` 
SET 
    `SpellFamilyMask0` = 16, -- Deathstrike (16)
    `SpellFamilyMask1` = 131076   -- Obliterate (131072) + FrostStrike (4)
WHERE `SpellId` = -49188;

-- DRUID
 -- Swipe for cat at level 20
UPDATE `trainer_spell` SET `ReqLevel` = 20, `MoneyCost` = 2000 WHERE `SpellId` = 62078;

-- HUNTER
-- Customspell: Exhilaration at level 20
INSERT INTO `trainer_spell` (`TrainerId`, `SpellId`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqAbility1`, `ReqAbility2`, `ReqAbility3`, `ReqLevel`, `VerifiedBuild`) VALUES 
(7, 190002, 2200, 0, 0, 0, 0, 0, 20, 0);

-- Kill Command at level 20
UPDATE `trainer_spell` SET `ReqLevel` = 20, `MoneyCost` = 2200 WHERE `SpellId` = 34026;

-- Misdirection at level 40
UPDATE `trainer_spell` SET `ReqLevel` = 40, `MoneyCost` = 18000 WHERE `SpellId` = 34477;

-- MAGE
-- Customspell: Revert Time at level 20
INSERT INTO `trainer_spell` (`TrainerId`, `SpellId`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqAbility1`, `ReqAbility2`, `ReqAbility3`, `ReqLevel`, `VerifiedBuild`) VALUES 
(16, 190004, 2000, 0, 0, 0, 0, 0, 20, 0);

-- PALADIN
-- Customspell: Holy Strike at level 2
INSERT INTO `trainer_spell` (`TrainerId`, `SpellId`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqAbility1`, `ReqAbility2`, `ReqAbility3`, `ReqLevel`, `VerifiedBuild`) VALUES 
(3, 190001, 10, 0, 0, 0, 0, 0, 2, 0),
(4, 190001, 10, 0, 0, 0, 0, 0, 2, 0),
(5, 190001, 10, 0, 0, 0, 0, 0, 2, 0),
(6, 190001, 10, 0, 0, 0, 0, 0, 2, 0);

-- PRIEST
-- Mind Sear at level 40
UPDATE `trainer_spell` SET `ReqLevel` = 40, `MoneyCost` = 18000 WHERE `SpellId` = 48045;

-- ROGUE
-- Customspell: Crimson Vial at level 20
INSERT INTO `trainer_spell` (`TrainerId`, `SpellId`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqAbility1`, `ReqAbility2`, `ReqAbility3`, `ReqLevel`, `VerifiedBuild`) VALUES 
(9, 190003, 3000, 0, 0, 0, 0, 0, 20, 0);

-- Fan of Knives at level 20
UPDATE `trainer_spell` SET `ReqLevel` = 20, `MoneyCost` = 3000 WHERE `SpellId` = 51723;



-- ##########################################
-- ## City Portals                          #
-- ##########################################

-- Remove Level Restriction from Shattrath/Dalaran Portals
DELETE FROM `conditions` WHERE `SourceEntry` IN (65728, 65729) AND `ErrorTextId` = 66;

-- Remove default TB/DARNA/IF Portal to Blasted Lands
DELETE FROM `gameobject` WHERE `guid` IN (151160,151157,151159);

-- Add Portals
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`, `Comment`)
VALUES

-- Portal to Maincity of that Startingzone
(2000001, 500001, 1, 0, 0, 1, 1, 10346.445, 816.778, 1325.1594, 2.37538, 0, 0, -0.927507, -0.373806, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Darnassus
(2000002, 500002, 530, 0, 0, 1, 1, -3959.54, -13914.1, 101.237, 3.13684, 0, 0, -0.999997, -0.00237603, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Exodar
(2000003, 500003, 0, 0, 0, 1, 1, -6216.96, 345.677, 384.037, 3.49515, 0, 0, -0.984416, 0.175858, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Ironforge
(2000004, 500000, 0, 0, 0, 1, 1, -8925.1, -146.099, 81.4466, 2.72017, 0, 0, -0.977883, -0.209155, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Stormwind
(2000005, 500004, 1, 0, 0, 1, 1, -597.911, -4250.77, 38.9562, 0.00231743, 0, 0, -0.00115741, -0.999999, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Orgrimmar
(2000006, 500006, 1, 0, 0, 1, 1, -2902.79, -231.388, 53.8569, 4.8701, 0, 0, -0.649209, 0.76061, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Thunderbluff
(2000007, 500005, 530, 0, 0, 1, 1, 10362.3, -6373.8, 36.7516, 0.906878, 0, 0, -0.43806, -0.898946, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Silvermoon
(2000008, 500007, 0, 0, 0, 1, 1, 1660.23, 1668.81, 141.851, 4.71759, 0, 0, -0.705267, 0.708942, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Undercity

-- Ironforge
(2000009, 500001, 0, 0, 0, 1, 1, -4606.44, -928.997, 501.07, 3.05297, -0, -0, -0.999018, -0.0442966, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Darnassus
(2000010, 500002, 0, 0, 0, 1, 1, -4610.43, -931.21, 501.068, 1.7335, -0, -0, -0.76223, -0.647307, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Exodar
(2000011, 500000, 0, 0, 0, 1, 1, -4603.77, -925.467, 501.071, 2.7663, -0, -0, -0.982446, -0.186547, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Stormwind
(2000056, 195141, 0, 0, 0, 1, 1, -4605.71, -918.564, 501.07, 3.05297, -0, -0, -0.999018, -0.0442966, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Blasted Lands

-- Exodar
(2000012, 500003, 530, 0, 0, 1, 1, -4044.65, -11577.1, -138.484, 1.0649, -0, -0, -0.507644, -0.861567, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Ironforge
(2000013, 500001, 530, 0, 0, 1, 1, -4038.96, -11580.8, -138.431, 1.63038, -0, -0, -0.727858, -0.685728, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Darnassus
(2000014, 500000, 530, 0, 0, 1, 1, -4047.49, -11569.3, -138.49, 6.10779, -0, -0, -0.0875875, 0.996157, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Stormwind

-- Darnassus
(2000015, 500003, 1, 0, 0, 1, 1, 9663.6, 2513.8164, 1331.6659, 1.18996, -0, -0, -0.560493, -0.828159, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Ironforge
(2000016, 500002, 1, 0, 0, 1, 1, 9661.603, 2509.7744, 1331.6339, 2.06333, -0, -0, -0.858154, -0.513392, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Exodar
(2000017, 500000, 1, 0, 0, 1, 1, 9662.968, 2518.472, 1331.6616, 0.135276, -0, -0, -0.0675867, -0.997713, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Stormwind
(2000055, 195141, 1, 0, 0, 1, 1, 9654.981, 2506.1672, 1331.5874, 3.22499, 0, 0, -0.999131, 0.0416858, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Blasted Lands

-- Stormwind
(2000018, 500003, 0, 0, 0, 1, 1, -8983.95, 856.786, 29.6206, 3.72043, -0, -0, -0.958409, 0.285397, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Ironforge
(2000019, 500001, 0, 0, 0, 1, 1, -8983.28, 852.043, 29.6206, 2.97923, -0, -0, -0.996707, -0.0810928, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Darnassus
(2000020, 500002, 0, 0, 0, 1, 1, -8994.92, 846.253, 29.6206, 1.30609, -0, -0, -0.607609, -0.794236, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Exodar

-- Undercity
(2000021, 500004, 0, 0, 0, 1, 1, 1773.91, 70.543, -46.3191, 4.90662, -0, -0, -0.635213, 0.772337, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Orgrimmar
(2000022, 500006, 0, 0, 0, 1, 1, 1768.73, 69.0272, -46.3206, 5.49978, -0, -0, -0.38176, 0.924261, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Thunderbluff
(2000023, 500005, 0, 0, 0, 1, 1, 1763.72, 62.1829, -46.3206, 6.13989, -0, -0, -0.0715876, 0.997434, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Silvermoon

-- Thunderbluff
(2000024, 500005, 1, 0, 0, 1, 1, -958.541, 294.523, 109.79, 4.55545, 0, 0, -0.76036, 0.649502, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Silvermoon
(2000025, 500007, 1, 0, 0, 1, 1, -965.9, 295.335, 109.796, 4.4023, 0, 0, -0.80782, 0.58943, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Undercity
(2000026, 500004, 1, 0, 0, 1, 1, -972.592, 296.286, 109.817, 4.72368, -0, -0, -0.703102, 0.711089, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Orgrimmar
(2000027, 195142, 1, 0, 0, 1, 1, -941.253, 281.588, 110.507, 3.22499, 0, 0, -0.999131, 0.0416858, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Blasted Lands

-- Silvermoon
(2000028, 500007, 530, 0, 0, 1, 1, 10008.74, -7099.715, 47.70568, 0.79852, -0, -0, -0.388737, -0.921349, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Undercity
(2000029, 500006, 530, 0, 0, 1, 1, 10009.986, -7104.8154, 47.70568, 5.05381, -0, -0, -0.576705, 0.816953, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Thunderbluff
(2000030, 500004, 530, 0, 0, 1, 1, 10004.875, -7095.6763, 47.70568, 5.19517, -0, -0, -0.517567, 0.855642, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Orgrimmar

-- Orgrimmar
(2000031, 500005, 1, 0, 0, 1, 1, 1468.88, -4214.92, 58.9939, 4.66052, -0, -0, -0.725205, 0.688534, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Silvermoon
(2000032, 500006, 1, 0, 0, 1, 1, 1464.81, -4215.45, 58.9939, 5.36738, -0, -0, -0.442067, 0.896982, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Thunderbluff
(2000033, 500007, 1, 0, 0, 1, 1, 1462.06, -4218.48, 58.9939, 5.74045, -0, -0, -0.268048, 0.963406, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Undercity

-- Portal from Blasted Lands to Faction City
(2000034, 500000, 0, 0, 0, 1, 1, -11814.1, -3206.94, -29.6735, 1.84699, 0, 0, -0.797715, -0.603035, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Stormwind
(2000035, 500004, 0, 0, 0, 1, 1, -11813.1, -3174.79, -29.4765, 4.90611, 0, 0, -0.635408, 0.772177, 300, 0, 1, '', 0, 'Custom - City Portal'), -- To Orgrimmar

-- To Shattrath
(2000036, 500008, 0, 0, 0, 1, 1, -9004.19, 855.131, 29.6211, 0.607119, 0, 0, -0.298919, -0.954278, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Stormwind
(2000037, 500008, 1, 0, 0, 1, 1, 9646.232, 2513.3135, 1331.4601, 3.0011, 0, 0, -0.997534, -0.0701908, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Darnassus
(2000038, 500008, 530, 0, 0, 1, 1, -4034.07, -11551.9, -138.266, 5.65799, 0, 0, -0.307533, 0.951537, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Exodar
(2000039, 500008, 0, 0, 0, 1, 1, -4610.5, -895.838, 502.767, 5.45079, 0, 0, -0.404286, 0.914633, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Ironforge
(2000040, 500009, 0, 0, 0, 1, 1, 1773.67, 56.0922, -46.3228, 2.37783, 0, 0, -0.927966, -0.372665, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Undercity
(2000041, 500009, 1, 0, 0, 1, 1, 1475.8, -4218.49, 58.9939, 3.90655, 0, 0, -0.927743, 0.37322, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Orgrimmar
(2000042, 500009, 1, 0, 0, 1, 1, -942.698, 274.766, 111.515, 2.3689, 0, 0, -0.926293, -0.376805, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Thunderbluff
(2000043, 500009, 530, 0, 0, 1, 1, 10000.1, -7120.21, 47.7058, 1.68995, 0, 0, -0.747955, -0.66375, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Silvermoon

-- To Dalaran
(2000044, 201797, 530, 0, 0, 1, 1, 10008.8, -7114.88, 47.7058, 2.49891, 0, 0, -0.948812, -0.315841, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Silvermoon
(2000045, 201797, 530, 0, 0, 1, 1, -1887.6, 5359.4, -12.4273, 1.18501, 0, 0, -0.558439, -0.829546, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Shattrath
(2000046, 201797, 530, 0, 0, 1, 1, -4018.87, -11552.5, -138.092, 4.57413, 0, 0, -0.75426, 0.656576, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Exodar
(2000047, 201797, 0, 0, 0, 1, 1, -8987.54, 848.393, 29.6206, 2.16611, 0, 0, -0.883394, -0.46863, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Stormwind
(2000048, 201797, 0, 0, 0, 1, 1, -4605.8, -891.769, 502.767, 4.9285, 0, 0, -0.626723, 0.779242, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Ironforge
(2000049, 201797, 1, 0, 0, 1, 1, 9643.038, 2509.031, 1331.3363, 3.34274, 0, 0, -0.994947, 0.100406, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Darnassus
(2000050, 201797, 1, 0, 0, 1, 1, 1467.74, -4226.2, 58.9939, 1.27153, 0, 0, -0.593795, -0.804616, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Orgrimmar
(2000051, 201797, 1, 0, 0, 1, 1, -951.096, 287.918, 109.831, 4.11564, 0, 0, -0.88373, 0.467997, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Thunderbluff
(2000052, 201797, 0, 0, 0, 1, 1, 1777.84, 60.4878, -46.3223, 2.31893, 0, 0, -0.916589, -0.39983, 300, 0, 1, '', 0, 'Custom - City Portal'), -- Undercity

-- Deathknight City Portals (after Intro)
(2000053, 500000, 0, 0, 0, 1, 1, 2338.7202, -5663.7563, 382.24185, 2.31893, 0, 0, -0.916589, -0.39983, 300, 0, 1, '', 0, 'Custom - DK City Portal'), -- To Stormwind
(2000054, 500004, 0, 0, 0, 1, 1, 2350.1926, -5680.502, 382.24185, 2.31893, 0, 0, -0.916589, -0.39983, 300, 0, 1, '', 0, 'Custom - DK City Portal'); -- To Orgrimmar



-- ##########################################
-- ## Classic-Mode                          #
-- ## With Individual Progress Module       #
-- ##########################################

-- Remove Portals to Shattrath and Dalaran
DELETE FROM `gameobject` WHERE `id` IN (500008,500009,201797) AND `Comment` = 'Custom - City Portal';

-- Disable Dark Portal
DELETE FROM `areatrigger_teleport` WHERE `ID` IN (4352,4354);

-- Disable Dark Portal Quest
REPLACE INTO `disables` (`sourceType`, `entry`, `flags`, `comment`) VALUES 
(1, 9407, 0, 'Custom - Deactivate Dark Portal Quest'),
(1, 10119, 0, 'Custom - Deactivate Dark Portal Quest');

-- Disable Nordend Transport
DELETE FROM `transports` WHERE `entry` IN (181688,181689,186238,190536);

-- Disable Master Professions and Riding/Flightform
UPDATE `trainer_spell` SET `ReqLevel` = 61 WHERE `SpellId` IN (28597,29845,28030,30351,28696,45379,28901,32550,29355,32679,26791,54084,54256,34090);

-- Set all Glyphs >60 to 60
UPDATE `item_template` SET `RequiredLevel` = 60 WHERE `class` = 16 AND `RequiredLevel` > 60;
UPDATE `item_template` SET `RequiredLevel` = 60 WHERE `entry` = 34062;

-- SPELLS (Set important spells to level 60 and cost to 100g)
-- DeathKnight
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (49020,3714,48792,45529,56222,57330,48743,56815,48707,48265,61999,47568,42650,53323,54446,53344,70164,62158);

-- Druid
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (22570,33763,33745,33786,52610,50464);

-- Hunter
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (34600,53351,62757,60192);

-- Mage
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (30482,30451,30455,66,43987,30449,44614,55342);
UPDATE `gameobject_template` SET `Data0` = 1 WHERE `entry`= 186811; -- Ritual of Refreshment: Solo possible

-- Paladin
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (32223,31884,54428,53600,53601,31801,53736);

-- Priest
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (32379,32546,34433,33076,32375,64843,64901);

-- Rogue
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (32645,26679,31224,57934);

-- Shaman
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (3738,2062,2894,2825,51505,51514,32182);

-- Warlock
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (28176,29722,29858,29893,27243,47897,48018,48020);
UPDATE `gameobject_template` SET `Data0` = 1 WHERE `entry`= 194108; -- Ritual of Summoning: Solo possible
UPDATE `gameobject_template` SET `Data0` = 2 WHERE `entry` = 181622; -- Ritual of Souls: Possible with another player
UPDATE `gameobject_template` SET `Data0` = 11730 WHERE `entry` = 181621; -- Reduce Rank of Soulstone provided by Ritual of Souls

-- Warrior
UPDATE `trainer_spell` SET `ReqLevel` = 60, `MoneyCost` = 1000000 WHERE `SpellId` IN (23920,469,3411,64382,55694,57755);



-- ##########################################
-- ## Dungeon/Raid Changes                  #
-- ## These are optional for soloing        #
-- ##########################################

-- BWL Eggs
DELETE FROM `gameobject` WHERE `id` = 177807;
INSERT IGNORE INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`, `Comment`) VALUES 
(2135620, 177807, 469, 0, 0, 1, 1, -7594.99, -1047.13, 408.157, 5.28851, 0, 0, 0.477087, -0.878856, 300, 0, 1, '', NULL, NULL),
(2135621, 177807, 469, 0, 0, 1, 1, -7602.37, -1052.37, 408.157, 3.74128, 0, 0, 0.955383, -0.295371, 300, 0, 1, '', NULL, NULL),
(2135622, 177807, 469, 0, 0, 1, 1, -7597.13, -1059.38, 408.157, 5.26888, 0, 0, 0.48569, -0.874131, 300, 0, 1, '', NULL, NULL),
(2135623, 177807, 469, 0, 0, 1, 1, -7590.17, -1054.82, 408.157, 0.556487, 0, 0, 0.274667, 0.961539, 300, 0, 1, '', NULL, NULL),
(2135624, 177807, 469, 0, 0, 1, 1, -7577.32, -1057.09, 408.157, 5.3317, 0, 0, 0.457999, -0.888953, 300, 0, 1, '', NULL, NULL),
(2135625, 177807, 469, 0, 0, 1, 1, -7598.66, -1072.21, 408.157, 3.74913, 0, 0, 0.954216, -0.299118, 300, 0, 1, '', NULL, NULL),
(2135626, 177807, 469, 0, 0, 1, 1, -7614.41, -1049.89, 408.157, 2.15084, 0, 0, 0.87979, 0.475363, 300, 0, 1, '', NULL, NULL),
(2135627, 177807, 469, 0, 0, 1, 1, -7592.96, -1034.79, 408.157, 0.638949, 0, 0, 0.314068, 0.949401, 300, 0, 1, '', NULL, NULL);



-- ##########################################
-- ## Fixes                                 #
-- ##########################################

-- POSITION FIXES
-- Human First Questgiver
UPDATE `creature` SET `position_x` = -8939.38, `position_y` = -132.20045, `position_z` = 83.6312 WHERE `guid` = 79942;

-- Nightelf First Questgiver
UPDATE `creature` SET `position_x` = 10326.058, `position_y` = 821.76495, `position_z` = 1326.4227, `orientation` = 2.54818 WHERE `guid` = 46205;

-- Dwarf/Gnome First Questgiver
UPDATE `creature` SET `position_x` = -6218.099, `position_y` = 329.7403, `position_z` = 383.22458 WHERE `guid` = 351;

-- Humar
UPDATE `creature` SET `position_x` = -636.4117, `position_y` = -3665.8228, `position_z` = 94.95956, `orientation` = 4.937 WHERE `guid` = 65607;



-- ##########################################
-- ## Other                                 #
-- ##########################################

REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(500000, 22, 4396, 'Portal to Stormwind', '', '', '', 1, 17334, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500001, 22, 4393, 'Portal to Darnassus', '', '', '', 1, 17608, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500002, 22, 6955, 'Portal to Exodar', '', '', '', 1, 32268, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500003, 22, 4394, 'Portal to Ironforge', '', '', '', 1, 17607, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500004, 22, 4395, 'Portal to Orgrimmar', '', '', '', 1, 17609, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500005, 22, 6956, 'Portal to Silvermoon', '', '', '', 1, 32270, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500006, 22, 4397, 'Portal to Thunderbluff', '', '', '', 1, 17610, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500007, 22, 4398, 'Portal to Undercity', '', '', '', 1, 17611, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500008, 22, 7146, 'Portal to Shattrath', '', '', '', 1, 33728, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(500009, 22, 7146, 'Portal to Shattrath', '', '', '', 1, 35718, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0);

REPLACE INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `mingold`, `maxgold`) VALUES
-- Alliance
(500000, 1732, 0, 0, 0),
(500001, 1732, 0, 0, 0),
(500002, 1732, 0, 0, 0),
(500003, 1732, 0, 0, 0),
(500008, 1732, 0, 0, 0),
-- Horde
(500004, 1735, 0, 0, 0),
(500005, 1735, 0, 0, 0),
(500006, 1735, 0, 0, 0),
(500007, 1735, 0, 0, 0),
(500009, 1735, 0, 0, 0);

REPLACE INTO `gameobject_template_locale` (`entry`, `locale`, `name`, `castBarCaption`, `VerifiedBuild`)
SELECT 500000, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176296  #Portal to Stormwind
UNION
SELECT 500001, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176498  #Portal to Darnassus
UNION
SELECT 500002, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 182351  #Portal to Exodar
UNION
SELECT 500003, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176497  #Portal to Ironforge
UNION
SELECT 500004, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176499  #Portal to Orgrimmar
UNION
SELECT 500005, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 182352  #Portal to Silvermoon
UNION
SELECT 500006, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176500  #Portal to Thunder Bluff
UNION
SELECT 500007, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176501 #Portal to Undercity
UNION
SELECT 500008, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 183384 #Portal to Shattrath
UNION
SELECT 500009, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 183384 #Portal to Shattrath;
