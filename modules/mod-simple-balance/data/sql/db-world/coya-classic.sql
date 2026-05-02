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

-- Disable Master Professions
UPDATE `trainer_spell` SET `ReqLevel` = 61 WHERE `SpellId` IN (28597,29845,28030,30351,28696,45379,28901,32550,29355,32679,26791,54084,54256,34090);
UPDATE `npc_trainer` SET `ReqLevel` = 61 WHERE `SpellID` IN (28597,29845,28030,30351,28696,45379,28901,32550,29355,32679,26791,54084,54256,34090);
-- Restore
-- UPDATE `trainer_spell` SET `ReqLevel` = 0 WHERE `SpellID` IN (29355,54256);
-- UPDATE `trainer_spell` SET `ReqLevel` = 10 WHERE `SpellID` IN (54084);
-- UPDATE `trainer_spell` SET `ReqLevel` = 50 WHERE `SpellID` IN (28696);
-- UPDATE `trainer_spell` SET `ReqLevel` = 40 WHERE `SpellID` IN (32679);
-- UPDATE `trainer_spell` SET `ReqLevel` = 50 WHERE `SpellID` IN (28597,29845,28030,30351,45379,28901,32550,26791);
-- UPDATE `trainer_spell` SET `ReqLevel` = 60 WHERE `SpellID` IN (34090);
-- Restore
-- UPDATE `npc_trainer` SET `ReqLevel` = 10 WHERE `SpellID` IN (54084);
-- UPDATE `npc_trainer` SET `ReqLevel` = 40 WHERE `SpellID` IN (28696,29355,32679);
-- UPDATE `npc_trainer` SET `ReqLevel` = 50 WHERE `SpellID` IN (28597,29845,28030,30351,45379,28901,32550,26791,54256);
-- UPDATE `npc_trainer` SET `ReqLevel` = 60 WHERE `SpellID` IN (34090);