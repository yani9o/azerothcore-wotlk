-- Shotgun-Approach...

UPDATE `quest_template` INNER JOIN `quest_template_addon` 
	ON `quest_template_addon`.id = `quest_template`.id
		SET `AllowableRaces` = 1791
			WHERE (`quest_template_addon`.`allowableclasses` != 0 AND `AllowableRaces` != 0) OR (`MinLevel` <= 60 AND `AllowableRaces` != 0 AND `AllowableRaces` != 690 AND `AllowableRaces` != 1101);

-- Fixes
REPLACE INTO `disables` (`sourceType`, `entry`, `flags`, `comment`) VALUES (1, 9369, 0, 'Custom - Deactivate Alliance Draenei Starter');
UPDATE `quest_template` SET `AllowableRaces` = 1024 WHERE `ID` = '9283';