UPDATE `creature` SET `guid`=46205, `id1`=2079, `id2`=0, `id3`=0, `map`=1, `zoneId`=0, `areaId`=0, `spawnMask`=1, `phaseMask`=1, `equipment_id`=1, `position_x`=10326.058, `position_y`=821.76495, `position_z`=1326.4227, `orientation`=2.54818, `spawntimesecs`=300, `wander_distance`=0, `currentwaypoint`=0, `curhealth`=86, `curmana`=0, `MovementType`=0, `npcflag`=0, `unit_flags`=0, `dynamicflags`=0, `ScriptName`='', `VerifiedBuild`=0, `CreateObject`=0, `Comment`=NULL WHERE `guid`=46205;

INSERT IGNORE INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`, `Comment`) VALUES 
(2135588, 142109, 1, 0, 0, 1, 1, 10400.9, 742.073, 1319.55, 3.70602, 0, 0, -0.960441, 0.278484, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135589, 142102, 0, 0, 0, 1, 1, -6167.81, 375.605, 399.023, 3.14031, 0, 0, -1, -0.000638918, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135590, 142075, 0, 0, 0, 1, 1, -8923.91, -136.852, 80.9728, 1.93871, 0, 0, -0.82452, -0.565832, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135591, 183857, 530, 0, 0, 1, 1, -4050.34, -13779.9, 75.1525, 5.91793, 0, 0, -0.181616, 0.983369, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135592, 143981, 1, 0, 0, 1, 1, -598.741, -4201.12, 39.7726, 4.70437, 0, 0, -0.709936, 0.704266, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135593, 143984, 1, 0, 0, 1, 1, -2885.89, -227.09, 53.9161, 3.88913, 0, 0, -0.930958, 0.365127, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135594, 143984, 0, 0, 0, 1, 1, 1863.97, 1579.76, 93.4618, 1.51944, 0, 0, -0.688718, -0.725029, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox'),
(2135595, 182359, 530, 0, 0, 1, 1, 10340.4, -6374.57, 35.5764, 1.84933, 0, 0, -0.798421, -0.6021, 300, 0, 1, '', NULL, 'Custom - Starter Mailbox');

UPDATE gossip_menu_option SET `BoxMoney` = 100000 WHERE BoxText LIKE "%Dual Talent%";