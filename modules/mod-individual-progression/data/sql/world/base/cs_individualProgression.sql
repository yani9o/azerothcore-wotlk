DELETE FROM `command` WHERE `name` IN ('ip get', 'ip set', 'ip setbot', 'ip setrep', 'ip tele');
INSERT INTO `command` (`name`, `security`, `help`) VALUES
('ip get', 0, 'Syntax: .ip get\nZeigt Eure aktuelle Progressionsstufe oder die Eures Ziels an.'),
('ip set', 2, 'Syntax: .ip set $progressionLevel\nSetzt den Spieler auf die angegebene Progressionsstufe.'),
('ip setbot', 2, 'Syntax: .ip setbot\nSetzt alle Bots in der Gruppe auf Eure Progressionsstufe.'),
('ip setrep', 2, 'Syntax: .ip setrep\nSetzt Euren Ruf bei bestimmten Fraktionen auf den höchsten Wert, den ein Charakter auf Eurem Account besitzt.'),
('ip tele', 2, 'Syntax: .ip tele $location\Teleportiert den Spieler zum angegebenen Ort.');
