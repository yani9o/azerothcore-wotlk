DELETE FROM `trainer_spell` WHERE `SpellId` IN (90001,90002,90003,90004);
INSERT INTO `trainer_spell` (`TrainerId`, `SpellId`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqAbility1`, `ReqAbility2`, `ReqAbility3`, `ReqLevel`, `VerifiedBuild`) VALUES 
(3, 90001, 10, 0, 0, 0, 0, 0, 2, 0), -- Holy Strike
(4, 90001, 10, 0, 0, 0, 0, 0, 2, 0), -- Holy Strike
(5, 90001, 10, 0, 0, 0, 0, 0, 2, 0), -- Holy Strike
(6, 90001, 10, 0, 0, 0, 0, 0, 2, 0), -- Holy Strike
(7, 90002, 2200, 0, 0, 0, 0, 0, 20, 0), -- Exhilaration
(9, 90003, 3000, 0, 0, 0, 0, 0, 20, 0), -- Crimson Vial
(16, 90004, 2000, 0, 0, 0, 0, 0, 20, 0); -- Revert Time

UPDATE `trainer_spell` SET `ReqLevel` = 20, `MoneyCost` = 3000 WHERE `SpellId` = 51723; -- Fan of Knives at level 20
UPDATE `trainer_spell` SET `ReqLevel` = 20, `MoneyCost` = 2000 WHERE `SpellId` = 62078; -- Swipe for cat at level 20