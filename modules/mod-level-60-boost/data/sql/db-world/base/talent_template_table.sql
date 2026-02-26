DROP TABLE IF EXISTS `mod_boost_talents`;
CREATE TABLE IF NOT EXISTS `mod_boost_talents` (
    `player_class` VARCHAR(50) NOT NULL,
    `player_spec` VARCHAR(50) NOT NULL,
    `talent_id` INT UNSIGNED NOT NULL DEFAULT '0'
) COLLATE='utf8mb4_general_ci' COMMENT='Talent Templates';

