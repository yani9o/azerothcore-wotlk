-- Human use Tauren
SET @HumanFireTotem := 30754;
SET @HumanEarthTotem := 30753;
SET @HumanWaterTotem := 30755;
SET @HumanAirTotem := 30736;

-- Nightelf use Draenei
SET @NightElfFireTotem := 19074;
SET @NightElfEarthTotem := 19073;
SET @NightElfWaterTotem := 19075;
SET @NightElfAirTotem := 19071;

-- Gnome use Dwarf
SET @GnomeFireTotem := 30754;
SET @GnomeEarthTotem := 30753;
SET @GnomeWaterTotem := 30755;
SET @GnomeAirTotem := 30736;

-- Undead use Troll
SET @UndeadFireTotem := 30762;
SET @UndeadEarthTotem := 30761;
SET @UndeadWaterTotem := 30763;
SET @UndeadAirTotem := 30760;

-- Bloodelf use Tauren
SET @BloodElfFireTotem := 4589;
SET @BloodElfEarthTotem := 4588;
SET @BloodElfWaterTotem := 4587;
SET @BloodElfAirTotem := 4590;

-- Human, Night Elf, Undead, Gnome and Blood Elf
DELETE FROM player_totem_model WHERE RaceID IN (1,4,5,7,10);
INSERT INTO player_totem_model (TotemID, RaceID, ModelID) VALUES 
(1, 1, @HumanFireTotem),
(2, 1, @HumanEarthTotem),
(3, 1, @HumanWaterTotem),
(4, 1, @HumanAirTotem),

(1, 4, @NightElfFireTotem),
(2, 4, @NightElfEarthTotem),
(3, 4, @NightElfWaterTotem),
(4, 4, @NightElfAirTotem),

(1, 5, @UndeadFireTotem),
(2, 5, @UndeadEarthTotem),
(3, 5, @UndeadWaterTotem),
(4, 5, @UndeadAirTotem),

(1, 7, @GnomeFireTotem),
(2, 7, @GnomeEarthTotem),
(3, 7, @GnomeWaterTotem),
(4, 7, @GnomeAirTotem),

(1, 10, @BloodElfFireTotem),
(2, 10, @BloodElfEarthTotem),
(3, 10, @BloodElfWaterTotem),
(4, 10, @BloodElfAirTotem);
