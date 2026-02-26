INSERT IGNORE INTO `acore_world`.`creature_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
(10440, 22691, 0, 1, 0, 1, 0, 1, 1, 'Custom - Baron Rivendare - Corrupted Ashbringer'),
(11583, 22727, 0, 3, 0, 1, 0, 1, 1, 'Custom - Nefarian - Atiesh Quest Item'),
(15339, 22733, 0, 100, 1, 1, 0, 1, 1, 'Custom - Ossirian - Atiesh Head'),
(5828, 10327, 0, 20, 0, 1, 0, 1, 1, 'Custom -  Humar, Horn of Echeyakee'),
(5831, 10327, 0, 100, 0, 1, 0, 1, 1, 'Custom - Swiftmane, Horn of Echeyakee'),
(3241, 10327, 0, 1, 0, 1, 0, 1, 1, 'Custom - Savannah Patriarch, Horn of Echeyakee'),
(3416, 10327, 0, 1, 0, 1, 0, 1, 1, 'Custom - Savannah Matriarch, Horn of Echeyakee');

DELETE FROM `creature` WHERE (`id1` = 5828) AND (`guid` IN (65607));
INSERT INTO `creature` (`guid`, `id1`, `id2`, `id3`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `Comment`, `VerifiedBuild`) VALUES
(65607, 5828, 0, 0, 1, 0, 0, 1, 1, 0, -636.4117, -3665.8228, 94.95956, 4.937, 39600, 0, 0, 1815, 0, 0, 0, 0, 0, '', NULL, 0);