DROP TABLE IF EXISTS `mod_boost_glyphs`;
CREATE TABLE IF NOT EXISTS `mod_boost_glyphs` (
    `player_class` VARCHAR(50) NOT NULL,
    `player_spec` VARCHAR(50) NOT NULL,
    `glyph_slot` TINYINT UNSIGNED NOT NULL DEFAULT '0',
    `glyph_id` SMALLINT UNSIGNED NOT NULL DEFAULT '0'
) COLLATE='utf8mb4_general_ci' COMMENT='Glyph Templates';