-- !!! NOTE: set these before running the queries in order to avoid conflicts !!!
SET @GO_TEMPLATE = 500000; -- 8 slots
SET @GO_SPAWN = 2000000; -- 35 slots (3 x 8 + 12)

DELETE FROM `gameobject_template` WHERE `entry` IN (
    @GO_TEMPLATE + 0,
    @GO_TEMPLATE + 1,
    @GO_TEMPLATE + 2,
    @GO_TEMPLATE + 3,
    @GO_TEMPLATE + 4,
    @GO_TEMPLATE + 5,
    @GO_TEMPLATE + 6,
    @GO_TEMPLATE + 7
);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(@GO_TEMPLATE + 0, 22, 4396, 'Portal nach Stormwind', '', '', '', 1, 17334, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 1, 22, 4393, 'Portal nach Darnassus', '', '', '', 1, 17608, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 2, 22, 6955, 'Portal zur Exodar', '', '', '', 1, 32268, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 3, 22, 4394, 'Portal nach Eisenschmiede', '', '', '', 1, 17607, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 4, 22, 4395, 'Portal nach Orgrimmar', '', '', '', 1, 17609, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 5, 22, 6956, 'Portal nach Silbermond', '', '', '', 1, 32270, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 6, 22, 4397, 'Portal nach Donnerfels', '', '', '', 1, 17610, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_TEMPLATE + 7, 22, 4398, 'Portal nach Unterstadt', '', '', '', 1, 17611, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0);

DELETE FROM `gameobject_template_locale` WHERE `entry` BETWEEN @GO_TEMPLATE + 0 AND @GO_TEMPLATE + 7;

INSERT INTO `gameobject_template_locale` (`entry`, `locale`, `name`, `castBarCaption`, `VerifiedBuild`)
SELECT @GO_TEMPLATE + 0, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176296  #Portal to Stormwind
UNION
SELECT @GO_TEMPLATE + 1, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176498  #Portal to Darnassus
UNION
SELECT @GO_TEMPLATE + 2, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 182351  #Portal to Exodar
UNION
SELECT @GO_TEMPLATE + 3, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176497  #Portal to Ironforge
UNION
SELECT @GO_TEMPLATE + 4, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176499  #Portal to Orgrimmar
UNION
SELECT @GO_TEMPLATE + 5, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 182352  #Portal to Silvermoon
UNION
SELECT @GO_TEMPLATE + 6, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176500  #Portal to Thunder Bluff
UNION
SELECT @GO_TEMPLATE + 7, L.locale, L.name, '', 0
FROM gameobject_template AS T
INNER JOIN gameobject_template_locale AS L
ON T.entry = L.entry
WHERE T.entry = 176501; #Portal to Undercity

DELETE FROM `gameobject_template_addon` WHERE `entry` IN (
    @GO_TEMPLATE + 0,
    @GO_TEMPLATE + 1,
    @GO_TEMPLATE + 2,
    @GO_TEMPLATE + 3,
    @GO_TEMPLATE + 4,
    @GO_TEMPLATE + 5,
    @GO_TEMPLATE + 6,
    @GO_TEMPLATE + 7
);
INSERT INTO `gameobject_template_addon` (`entry`, `faction`, `flags`, `mingold`, `maxgold`) VALUES
-- Alliance
(@GO_TEMPLATE + 0, 1732, 0, 0, 0),
(@GO_TEMPLATE + 1, 1732, 0, 0, 0),
(@GO_TEMPLATE + 2, 1732, 0, 0, 0),
(@GO_TEMPLATE + 3, 1732, 0, 0, 0),
-- Horde
(@GO_TEMPLATE + 4, 1735, 0, 0, 0),
(@GO_TEMPLATE + 5, 1735, 0, 0, 0),
(@GO_TEMPLATE + 6, 1735, 0, 0, 0),
(@GO_TEMPLATE + 7, 1735, 0, 0, 0);

DELETE FROM `gameobject` WHERE `guid` IN (
	151160, -- delete Tauren default blasted lands portal
    @GO_SPAWN + 00,
    @GO_SPAWN + 01,
    @GO_SPAWN + 02,
    @GO_SPAWN + 03,
    @GO_SPAWN + 04,
    @GO_SPAWN + 05,
    @GO_SPAWN + 06,
    @GO_SPAWN + 07,
    @GO_SPAWN + 08,
    @GO_SPAWN + 09,
    @GO_SPAWN + 10,
    @GO_SPAWN + 11,
    @GO_SPAWN + 12,
    @GO_SPAWN + 13,
    @GO_SPAWN + 14,
    @GO_SPAWN + 15,
    @GO_SPAWN + 16,
    @GO_SPAWN + 17,
    @GO_SPAWN + 18,
    @GO_SPAWN + 19,
    @GO_SPAWN + 20,
    @GO_SPAWN + 21,
    @GO_SPAWN + 22,
    @GO_SPAWN + 23,
    @GO_SPAWN + 24,
    @GO_SPAWN + 25,
    @GO_SPAWN + 26,
    @GO_SPAWN + 27,
    @GO_SPAWN + 28,
    @GO_SPAWN + 29,
    @GO_SPAWN + 30,
    @GO_SPAWN + 31,
    @GO_SPAWN + 32,
    @GO_SPAWN + 33,
    @GO_SPAWN + 34,
    @GO_SPAWN + 35,
    @GO_SPAWN + 36,
    @GO_SPAWN + 37,
    @GO_SPAWN + 38,
    @GO_SPAWN + 39,
    @GO_SPAWN + 40,
    @GO_SPAWN + 41,
    @GO_SPAWN + 42,
    @GO_SPAWN + 43,
    @GO_SPAWN + 44,
    @GO_SPAWN + 45,
    @GO_SPAWN + 46,
    @GO_SPAWN + 47,
    @GO_SPAWN + 48,
    @GO_SPAWN + 49,
    @GO_SPAWN + 50,
    @GO_SPAWN + 51,
    @GO_SPAWN + 52
);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`, `Comment`)
VALUES
(@GO_SPAWN + 00, 500002, 0, 0, 0, 1, 1, -4605.71, -918.564, 501.07, 3.05297, -0, -0, -0.999018, -0.0442966, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 01, 500001, 0, 0, 0, 1, 1, -4610.43, -931.21, 501.068, 1.7335, -0, -0, -0.76223, -0.647307, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 02, 500000, 0, 0, 0, 1, 1, -4603.77, -925.467, 501.071, 2.7663, -0, -0, -0.982446, -0.186547, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 03, 500003, 530, 0, 0, 1, 1, -4044.65, -11577.1, -138.484, 1.0649, -0, -0, -0.507644, -0.861567, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 04, 500001, 530, 0, 0, 1, 1, -4038.96, -11580.8, -138.431, 1.63038, -0, -0, -0.727858, -0.685728, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 05, 500000, 530, 0, 0, 1, 1, -4047.49, -11569.3, -138.49, 6.10779, -0, -0, -0.0875875, 0.996157, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 06, 500003, 1, 0, 0, 1, 1, 9651.76, 2506.87, 1331.56, 1.18996, -0, -0, -0.560493, -0.828159, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 07, 500002, 1, 0, 0, 1, 1, 9656.46, 2506.88, 1331.59, 2.06333, -0, -0, -0.858154, -0.513392, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 08, 500000, 1, 0, 0, 1, 1, 9646.91, 2512.91, 1331.51, 0.135276, -0, -0, -0.0675867, -0.997713, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 09, 500003, 0, 0, 0, 1, 1, -8983.95, 856.786, 29.6206, 3.72043, -0, -0, -0.958409, 0.285397, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 10, 500002, 0, 0, 0, 1, 1, -8983.28, 852.043, 29.6206, 2.97923, -0, -0, -0.996707, -0.0810928, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 11, 500001, 0, 0, 0, 1, 1, -8994.92, 846.253, 29.6206, 1.30609, -0, -0, -0.607609, -0.794236, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 12, 500006, 0, 0, 0, 1, 1, 1773.91, 70.543, -46.3191, 4.90662, -0, -0, -0.635213, 0.772337, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 13, 500005, 0, 0, 0, 1, 1, 1768.73, 69.0272, -46.3206, 5.49978, -0, -0, -0.38176, 0.924261, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 14, 500004, 0, 0, 0, 1, 1, 1763.72, 62.1829, -46.3206, 6.13989, -0, -0, -0.0715876, 0.997434, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 15, 500007, 1, 0, 0, 1, 1, -958.541, 294.523, 109.79, 4.55545, 0, 0, -0.76036, 0.649502, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 16, 500005, 1, 0, 0, 1, 1, -965.9, 295.335, 109.796, 4.4023, 0, 0, -0.80782, 0.58943, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 17, 500004, 1, 0, 0, 1, 1, -972.592, 296.286, 109.817, 4.72368, -0, -0, -0.703102, 0.711089, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 18, 500007, 530, 0, 0, 1, 1, 9987.34, -7113.53, 47.7055, 0.79852, -0, -0, -0.388737, -0.921349, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 19, 500006, 530, 0, 0, 1, 1, 9995.38, -7092.29, 47.7055, 5.05381, -0, -0, -0.576705, 0.816953, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 20, 500004, 530, 0, 0, 1, 1, 9989.99, -7093.12, 47.7055, 5.19517, -0, -0, -0.517567, 0.855642, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 21, 500007, 1, 0, 0, 1, 1, 1468.88, -4214.92, 58.9939, 4.66052, -0, -0, -0.725205, 0.688534, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 22, 500006, 1, 0, 0, 1, 1, 1464.81, -4215.45, 58.9939, 5.36738, -0, -0, -0.442067, 0.896982, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 23, 500005, 1, 0, 0, 1, 1, 1462.06, -4218.48, 58.9939, 5.74045, -0, -0, -0.268048, 0.963406, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 24, 500001, 1, 0, 0, 1, 1, 10346.445, 816.778, 1325.1594, 2.37538, 0, 0, -0.927507, -0.373806, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 25, 500002, 530, 0, 0, 1, 1, -3959.54, -13914.1, 101.237, 3.13684, 0, 0, -0.999997, -0.00237603, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 26, 500003, 0, 0, 0, 1, 1, -6216.96, 345.677, 384.037, 3.49515, 0, 0, -0.984416, 0.175858, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 27, 500000, 0, 0, 0, 1, 1, -8925.1, -146.099, 81.4466, 2.72017, 0, 0, -0.977883, -0.209155, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 28, 500004, 1, 0, 0, 1, 1, -597.911, -4250.77, 38.9562, 0.00231743, 0, 0, -0.00115741, -0.999999, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 29, 500006, 1, 0, 0, 1, 1, -2902.79, -231.388, 53.8569, 4.8701, 0, 0, -0.649209, 0.76061, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 30, 500005, 530, 0, 0, 1, 1, 10362.3, -6373.8, 36.7516, 0.906878, 0, 0, -0.43806, -0.898946, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 31, 500007, 0, 0, 0, 1, 1, 1660.23, 1668.81, 141.851, 4.71759, 0, 0, -0.705267, 0.708942, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 33, 500000, 0, 0, 0, 1, 1, -11814.1, -3206.94, -29.6735, 1.84699, 0, 0, -0.797715, -0.603035, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 34, 500004, 0, 0, 0, 1, 1, -11813.1, -3174.79, -29.4765, 4.90611, 0, 0, -0.635408, 0.772177, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 35, 192786, 0, 0, 0, 1, 1, -9004.19, 855.131, 29.6211, 0.607119, 0, 0, -0.298919, -0.954278, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 36, 192786, 1, 0, 0, 1, 1, 9663.38, 2514.69, 1331.67, 3.0011, 0, 0, -0.997534, -0.0701908, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 37, 192786, 530, 0, 0, 1, 1, -4034.07, -11551.9, -138.266, 5.65799, 0, 0, -0.307533, 0.951537, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 38, 192786, 0, 0, 0, 1, 1, -4610.5, -895.838, 502.767, 5.45079, 0, 0, -0.404286, 0.914633, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 39, 192786, 0, 0, 0, 1, 1, 1773.67, 56.0922, -46.3228, 2.37783, 0, 0, -0.927966, -0.372665, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 40, 192786, 1, 0, 0, 1, 1, 1475.8, -4218.49, 58.9939, 3.90655, 0, 0, -0.927743, 0.37322, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 41, 192786, 1, 0, 0, 1, 1, -942.698, 274.766, 111.515, 2.3689, 0, 0, -0.926293, -0.376805, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 42, 195142, 1, 0, 0, 1, 1, -941.253, 281.588, 110.507, 3.22499, 0, 0, -0.999131, 0.0416858, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 43, 192786, 530, 0, 0, 1, 1, 10000.1, -7120.21, 47.7058, 1.68995, 0, 0, -0.747955, -0.66375, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 44, 201797, 530, 0, 0, 1, 1, 10008.8, -7114.88, 47.7058, 2.49891, 0, 0, -0.948812, -0.315841, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 45, 201797, 530, 0, 0, 1, 1, -1887.6, 5359.4, -12.4273, 1.18501, 0, 0, -0.558439, -0.829546, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 46, 201797, 530, 0, 0, 1, 1, -4018.87, -11552.5, -138.092, 4.57413, 0, 0, -0.75426, 0.656576, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 47, 201797, 0, 0, 0, 1, 1, -8987.54, 848.393, 29.6206, 2.16611, 0, 0, -0.883394, -0.46863, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 48, 201797, 0, 0, 0, 1, 1, -4605.8, -891.769, 502.767, 4.9285, 0, 0, -0.626723, 0.779242, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 49, 201797, 1, 0, 0, 1, 1, 9662.29, 2519.49, 1331.63, 3.34274, 0, 0, -0.994947, 0.100406, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 50, 201797, 1, 0, 0, 1, 1, 1467.74, -4226.2, 58.9939, 1.27153, 0, 0, -0.593795, -0.804616, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 51, 201797, 1, 0, 0, 1, 1, -951.096, 287.918, 109.831, 4.11564, 0, 0, -0.88373, 0.467997, 300, 0, 1, '', 0, 'Custom - City Portal'),
(@GO_SPAWN + 52, 201797, 0, 0, 0, 1, 1, 1777.84, 60.4878, -46.3223, 2.31893, 0, 0, -0.916589, -0.39983, 300, 0, 1, '', 0, 'Custom - City Portal');

DELETE FROM `conditions` WHERE `SourceEntry` IN (65728, 65729) AND `ErrorTextId` = 66;
