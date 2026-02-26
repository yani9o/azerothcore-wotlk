-- also comment out all backstab ids in SpellMgr.cpp! (around line 3335)

-- ROGUE
-- Backstab
DELETE FROM spell_custom_attr WHERE spell_id IN ( 53, 2589, 2590, 2591, 8721, 11279, 11280, 11281, 25300, 26863, 48656, 48657 );
INSERT IGNORE INTO spell_script_names (spell_id, ScriptName) VALUES ('-53', 'spell_front_backstab');

-- Ambush
DELETE FROM spell_custom_attr WHERE spell_id IN ( 8676, 8724, 8725, 11267, 11268, 11269, 27441, 48689, 48690, 48691 );
INSERT IGNORE INTO spell_script_names (spell_id, ScriptName) VALUES ('-8676', 'spell_front_backstab');

-- Garrote
DELETE FROM spell_custom_attr WHERE spell_id IN ( 703, 8631, 8632, 8633, 11289, 11290, 26839, 26884, 48675, 48676 );
INSERT IGNORE INTO spell_script_names (spell_id, ScriptName) VALUES ('-703', 'spell_front_backstab');

-- DRUID
-- Shred
DELETE FROM spell_custom_attr WHERE spell_id IN ( 5221, 6800, 8992, 9829, 9830, 27001, 27002, 48571, 48572 );
INSERT IGNORE INTO spell_script_names (spell_id, ScriptName) VALUES ('-5221', 'spell_front_backstab');

-- Ravage
DELETE FROM spell_custom_attr WHERE spell_id IN ( 6785, 6787, 9866, 9867, 27005, 48578, 48579 );
INSERT IGNORE INTO spell_script_names (spell_id, ScriptName) VALUES ('-6785', 'spell_front_backstab');
