-- Convert Server to Azeroth only

-- Remove Portals to Shattrath and Dalaran
DELETE FROM `gameobject` WHERE `id` IN (192786,201797) AND `Comment` = 'Custom - City Portal';

-- Prevent Dark Portal
DELETE FROM `areatrigger_teleport` WHERE `ID` IN (4352,4354);
-- Restore
-- INSERT IGNORE INTO `areatrigger_teleport` (`ID`, `Name`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES (4352, 'Outland To Dark Portal', 0, -11877.7, -3204.49, -18.49, 0.23);
-- INSERT IGNORE INTO `areatrigger_teleport` (`ID`, `Name`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES (4354, 'Dark Portal To Outland', 530, -248.149, 921.875, 84.3885, 1.58415);

-- Disable Dark Portal Quest
INSERT IGNORE INTO `disables` (`sourceType`, `entry`, `flags`, `comment`) VALUES 
(1, 9407, 0, 'Custom - Deactivate Dark Portal Quest'),
(1, 10119, 0, 'Custom - Deactivate Dark Portal Quest');

-- Disable Nordend Transport
DELETE FROM `transports` WHERE `entry` IN (181688,181689,186238,190536);
-- Restore
-- INSERT IGNORE INTO `transports` (`guid`, `entry`, `name`, `ScriptName`) VALUES (10, 181688, 'Menethil Harbor, Wetlands and Valgarde, Howling Fjord (Boat, Alliance ("Northspear"))', '');
-- INSERT IGNORE INTO `transports` (`guid`, `entry`, `name`, `ScriptName`) VALUES (11, 181689, 'Undercity, Tirisfal Glades and Vengeance Landing, Howling Fjord (Zeppelin, Horde ("Cloudkisser"))', '');
-- INSERT IGNORE INTO `transports` (`guid`, `entry`, `name`, `ScriptName`) VALUES (12, 186238, 'Orgrimmar, Durotar and Warsong Hold, Borean Tundra (Zeppelin, Horde ("The Mighty Wind"))', '');
-- INSERT IGNORE INTO `transports` (`guid`, `entry`, `name`, `ScriptName`) VALUES (17, 190536, 'Valiance Keep, Borean Tundra and Stormwind Harbor (Boat, Alliance ("The Kraken"))', '');


-- SPELLS --
-- BACKUP trainer_spell before using! --

-- Disable Master Professions and Riding
UPDATE `trainer_spell` SET `ReqLevel` = 61 WHERE `SpellId` IN (28597,29845,28030,30351,28696,45379,28901,32550,29355,32679,26791,54084,54256,34090,33943);
-- UPDATE `npc_trainer` SET `ReqLevel` = 61 WHERE `SpellID` IN (28597,29845,28030,30351,28696,45379,28901,32550,29355,32679,26791,54084,54256,34090);


-- Change level of important spells
-- DeathKnight
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (49020,3714,48792,45529,56222,57330,48743,56815,48707,48265,61999,47568,42650,53323,54446,53344,70164,62158);

-- Druid
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (22570,33763,33745,33786,52610,50464);

-- Hunter
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (34600,53351,62757,60192);
UPDATE `trainer_spell` SET `ReqLevel` = 14 WHERE `SpellId` IN (34026);
UPDATE `trainer_spell` SET `ReqLevel` = 40 WHERE `SpellId` IN (34477);

-- Mage
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (25306,30482,30451,30455,66,43987,30449,44614,55342);

-- Paladin
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (32223,31884,54428,53600,53601,31801,53736);
UPDATE `trainer_spell` SET `MoneyCost` = 100000 WHERE `SpellId` = 31801;

-- Priest
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (32379,32546,34433,33076,32375,64843,64901);
UPDATE `trainer_spell` SET `ReqLevel` = 40 WHERE `SpellId` IN (48045);

-- Rogue
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (32645,26679,31224,57934);

-- Shaman
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (3738,2062,2894,2825,51505,51514,32182);

-- Warlock
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (28176,29722,29858,29893,27243,47897,48018,48020);

-- Warrior
UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellId` IN (23920,469,3411,64382,55694,57755);