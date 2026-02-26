DELETE FROM `command` WHERE `name` IN ('xp', 'xp set', 'xp view', 'xp default', 'xp enable', 'xp disable');

INSERT INTO `command` (`name`, `security`, `help`) VALUES 
('xp', 0, 'Syntax: .xp $subcommand\nGib .help xp ein, um eine Liste der Unterbefehle zu sehen\noder .help xp $subcommand, um Informationen zu einem Unterbefehl zu erhalten.'),
('xp set', 0, 'Syntax: .xp set $rate\nSetzt deine benutzerdefinierte XP-Rate.'),
('xp view', 0, 'Syntax: .xp view\nZeigt deine aktuelle XP-Rate an.'),
('xp default', 0, 'Syntax: .xp default\nSetzt deine benutzerdefinierte XP-Rate auf den Standardwert zurück.'),
('xp enable', 0, 'Syntax: .xp enable\nAktiviert die benutzerdefinierte XP-Rate.'),
('xp disable', 0, 'Syntax: .xp disable\nDeaktiviert die benutzerdefinierte XP-Rate.');
