-- Restore rep requirement to Mantle of the Dawn
UPDATE item_template SET RequiredReputationFaction=529, RequiredReputationRank=6 WHERE entry IN (18169, 18170, 18171, 18172, 18173);
UPDATE item_template SET RequiredReputationFaction=529, RequiredReputationRank=7 WHERE entry=18182;

-- Restore quiver functionality
UPDATE `item_template` SET `spellid_1` = 29418 WHERE `entry` IN (2101, 3573, 5439, 7278, 11362); 
UPDATE `item_template` SET `spellid_1` = 14824 WHERE `entry` IN (2102, 3574, 5441, 7279, 11363);
UPDATE `item_template` SET `spellid_1` = 29414 WHERE `entry` IN (18714, 19319, 29143, 29144, 34100, 34105, 44448);
UPDATE `item_template` SET `spellid_1` = 14829 WHERE `entry` IN (19320, 29118, 34099, 34106, 44447);
UPDATE `item_template` SET `spellid_1` = 29415 WHERE `entry` = 2662;
UPDATE `item_template` SET `spellid_1` = 14828 WHERE `entry` = 2663;
UPDATE `item_template` SET `spellid_1` = 14825 WHERE `entry` = 3604;
UPDATE `item_template` SET `spellid_1` = 29417 WHERE `entry` = 3605;
UPDATE `item_template` SET `spellid_1` = 29416 WHERE `entry` = 7371;
UPDATE `item_template` SET `spellid_1` = 14826 WHERE `entry` = 7372;
UPDATE `item_template` SET `spellid_1` = 29413 WHERE `entry` = 8217;
UPDATE `item_template` SET `spellid_1` = 14827 WHERE `entry` = 8218;


/* =========== NON-EQUIPMENT ITEMS ================ */

/*  Scroll of Strength  */
UPDATE item_template SET ItemLevel = 20, RequiredLevel = 10 WHERE entry=954;

/*  Scroll of Intellect  */
UPDATE item_template SET ItemLevel = 15, RequiredLevel = 5 WHERE entry=955;

/*  Large Moneybag (old)  */
UPDATE item_template SET ItemLevel = 25, bonding = 1, class = 1 WHERE entry=1014;

/*  Tablet of Serpent Totem  */
UPDATE item_template SET BuyPrice = 80 WHERE entry=1029;

/*  Horn of the Black Wolf  */
UPDATE item_template SET Quality = 3, bonding = 1, BuyPrice = 100000 WHERE entry=1041;

/*  Tablet of Restoration III  */
UPDATE item_template SET BuyPrice = 1800 WHERE entry=1057;

/*  Scroll of Stamina  */
UPDATE item_template SET ItemLevel = 15, RequiredLevel = 5 WHERE entry=1180;

/*  Scroll of Spirit  */
UPDATE item_template SET ItemLevel = 10 WHERE entry=1181;

/*  Linen Bandage  */
UPDATE item_template SET BuyPrice = 40, SellPrice = 10 WHERE entry=1251;

/*  Scroll of Agility II  */
UPDATE item_template SET ItemLevel = 35, RequiredLevel = 25 WHERE entry=1477;

/*  Scroll of Stamina II  */
UPDATE item_template SET ItemLevel = 30, RequiredLevel = 20 WHERE entry=1711;

/*  Scroll of Strength II  */
UPDATE item_template SET ItemLevel = 35, RequiredLevel = 25 WHERE entry=2289;

/*  Scroll of Intellect II  */
UPDATE item_template SET ItemLevel = 30, RequiredLevel = 20 WHERE entry=2290;

/*  Light Leather  */
UPDATE item_template SET BuyPrice = 60 WHERE entry=2318;

/*  Palomino  */
UPDATE item_template SET Quality = 3, bonding = 1, BuyPrice = 100000, SellPrice = 0 WHERE entry=2413;

/*  White Stallion  */
UPDATE item_template SET Quality = 3, bonding = 1, BuyPrice = 100000, SellPrice = 0 WHERE entry=2415;

/*  Earthroot  */
UPDATE item_template SET ItemLevel = 5 WHERE entry=2449;

/*  Recipe: Elixir of Tongues  */
UPDATE item_template SET subclass = 6, BuyPrice = 160 WHERE entry=2556;

/*  Hot Spices  */
UPDATE item_template SET Quality = 1 WHERE entry=2692;

/*  Deadly Poison  */
UPDATE item_template SET BuyPrice = 120, SellPrice = 30 WHERE entry=2892;

/*  Deadly Poison II  */
UPDATE item_template SET BuyPrice = 220, SellPrice = 55 WHERE entry=2893;

/*  Dust of Decay  */
UPDATE `item_template` SET `Quality` = 0, `class` = 15, `subclass` = 0 WHERE `entry` = 2928;

/*  Essence of Pain  */
UPDATE `item_template` SET `Quality` = 0, `class` = 15, `subclass` = 0 WHERE `entry` = 2930;

/*  Maiden's Anguish  */
UPDATE item_template SET Quality = 1, ItemLevel = 34, class = 7, BuyPrice = 100, SellPrice = 25 WHERE entry=2931;

/*  Scroll of Agility  */
UPDATE item_template SET ItemLevel = 20, RequiredLevel = 10 WHERE entry=3012;

/*  Scroll of Protection  */
UPDATE item_template SET ItemLevel = 10 WHERE entry=3013;

/*  Grimoire of Burning Spirit II  */
UPDATE item_template SET BuyPrice = 1800 WHERE entry=3144;

/*  Grave Moss  */
UPDATE item_template SET ItemLevel = 24 WHERE entry=3369;

/*  Elixir of Ogre's Strength  */
UPDATE item_template SET BuyPrice = 80, SellPrice = 20 WHERE entry=3391;

/*  Dog Whistle  */
UPDATE item_template SET Quality = 2 WHERE entry=3456;

/*  Wool Bandage  */
UPDATE item_template SET BuyPrice = 115, SellPrice = 28 WHERE entry=3530;

/*  Belamoore's Research Journal  */
UPDATE item_template SET Quality = 1, BuyPrice = 0, SellPrice = 0 WHERE entry=3711;

/*  Soothing Spices  */
UPDATE item_template SET Quality = 1 WHERE entry=3713;

/*  Crippling Poison  */
UPDATE item_template SET BuyPrice = 52, SellPrice = 13 WHERE entry=3775;

/*  Crippling Poison II  */
UPDATE item_template SET Quality = 1, class = 0 WHERE entry=3776;

/*  Lethargy Root  */
UPDATE `item_template` SET `Quality` = 0, `class` = 15, `subclass` = 0 WHERE `entry` = 3777;

/*  Carefully Folded Note  */
UPDATE item_template SET ItemLevel = 45, RequiredLevel = 45 WHERE entry=4098;

/*  Tome of Conjure Food II  */
UPDATE item_template SET BuyPrice = 500 WHERE entry=4143;

/*  Codex of Heal  */
UPDATE item_template SET BuyPrice = 1300, SellPrice = 325 WHERE entry=4273;

/*  Mechanical Squirrel Box  */
UPDATE item_template SET bonding = 3 WHERE entry=4401;

/*  Accurate Scope  */
UPDATE item_template SET Quality = 1 WHERE entry=4407;

/*  Scroll of Intellect III  */
UPDATE item_template SET ItemLevel = 45, RequiredLevel = 35 WHERE entry=4419;

/*  Scroll of Stamina III  */
UPDATE item_template SET ItemLevel = 45, RequiredLevel = 35 WHERE entry=4422;

/*  Scroll of Agility III  */
UPDATE item_template SET ItemLevel = 50, RequiredLevel = 40 WHERE entry=4425;

/*  Scroll of Strength III  */
UPDATE item_template SET ItemLevel = 50, RequiredLevel = 40 WHERE entry=4426;

/*  Flint and Tinder  */
UPDATE item_template SET Quality = 1 WHERE entry=4471;

/*  Frost Vial  */
UPDATE item_template SET SellPrice = 10 WHERE entry=5024;

/*  Explosive Shell  */
UPDATE item_template SET SellPrice = 25 WHERE entry=5105;

/*  Long Tail Feather  */
UPDATE item_template SET Quality = 1 WHERE entry=5116;

/*  Flash Powder  */
UPDATE `item_template` SET `Quality` = 1, `Flags` = 0, `class` = 5, `subclass` = 0 WHERE `entry` = 5140;

/* Blinding Powder */
UPDATE `item_template` SET `Quality` = 1, `Flags` = 0, `class` = 5, `subclass` = 0, description = '' WHERE `entry` = 5530;

/*  Book of Healing Touch III  */
UPDATE item_template SET BuyPrice = 900 WHERE entry=5150;

/*  Deathweed  */
UPDATE `item_template` SET `Quality` = 0, `class` = 15, `subclass` = 0 WHERE `entry` = 5173;

/*  Mind-numbing Poison  */
UPDATE item_template SET BuyPrice = 72, SellPrice = 18 WHERE entry=5237;

/*  Glowing Cat Figurine  */
UPDATE item_template SET ItemLevel = 1 WHERE entry=5332;

/*  Dartol's Rod of Transformation  */
UPDATE item_template SET bonding = 1 WHERE entry=5462;

/*  Cowardly Flight Potion  */
UPDATE item_template SET BuyPrice = 340 WHERE entry=5632;

/*  Recipe: Instant Toxin  */
UPDATE item_template SET BuyPrice = 1000 WHERE entry=5657;

/*  Libram: Seal of Righteousness  */
UPDATE item_template SET BuyPrice = 1300 WHERE entry=5660;

/*  Henrig Lonebrow's Journal  */
UPDATE item_template SET ItemLevel = 29, RequiredLevel = 29 WHERE entry=5791;

/*  Kravel's Scheme  */
UPDATE item_template SET bonding = 0 WHERE entry=5826;

/*  Harness: Black Ram  */
UPDATE item_template SET Quality = 3, bonding = 1, BuyPrice = 100000 WHERE entry=5874;

/*  Harness: Blue Ram  */
UPDATE item_template SET Quality = 3, bonding = 1, BuyPrice = 100000 WHERE entry=5875;

/*  Vimes's Report  */
UPDATE item_template SET bonding = 5 WHERE entry=6075;

/*  Greater Mana Potion  */
UPDATE item_template SET BuyPrice = 480, SellPrice = 120 WHERE entry=6149;

/*  Mystical Powder  */
UPDATE item_template SET SellPrice = 6 WHERE entry=6216;

/*  Enchanted Powder  */
UPDATE item_template SET SellPrice = 125 WHERE entry=6374;

/*  Snakeskin Bag  */
UPDATE item_template SET Quality = 1, bonding = 0 WHERE entry=6446;

/*  Silk Bandage  */
UPDATE item_template SET BuyPrice = 800, SellPrice = 200 WHERE entry=6450;

/*  Stoneskin Totem Scroll  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=6648;

/*  Searing Totem Scroll  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=6649;

/*  Instant Poison  */
UPDATE item_template SET BuyPrice = 22, SellPrice = 5 WHERE entry=6947;

/*  Instant Poison II  */
UPDATE item_template SET BuyPrice = 80, SellPrice = 20 WHERE entry=6949;

/*  Instant Poison III  */
UPDATE item_template SET BuyPrice = 120, SellPrice = 30 WHERE entry=6950;

/*  Mind-numbing Poison II  */
UPDATE item_template SET Quality = 1, class = 0 WHERE entry=6951;

/*  Shadowcat Hide  */
UPDATE item_template SET Quality = 1, class = 7, BuyPrice = 1000, SellPrice = 250 WHERE entry=7428;

/*  Gni'kiv Medallion  */
UPDATE item_template SET Quality = 1 WHERE entry=7740;

/*  The Shaft of Tsol  */
UPDATE item_template SET Quality = 1 WHERE entry=7741;

/*  Plans: Ornate Mithril Breastplate  */
UPDATE item_template SET BuyPrice = 10000, SellPrice = 2500 WHERE entry=7986;

/*  Plans: Ornate Mithril Helm  */
UPDATE item_template SET BuyPrice = 10000, SellPrice = 2500 WHERE entry=7987;

/*  Plans: Ornate Mithril Boots  */
UPDATE item_template SET BuyPrice = 10000, SellPrice = 2500 WHERE entry=7988;

/*  Plans: Orcish War Leggings  */
UPDATE item_template SET BuyPrice = 8000, SellPrice = 2000 WHERE entry=7994;

/*  Wicked Claw  */
UPDATE item_template SET Quality = 1, class = 7, subclass = 11 WHERE entry = 8146;

/*  Wildvine  */
UPDATE item_template SET Quality = 1 WHERE entry=8153;

/*  Jet Black Feather  */
UPDATE item_template SET Quality = 1 WHERE entry=8168;

/*  Thick Wolfhide  */
UPDATE item_template SET Quality = 1, class = 7 WHERE entry=8368;

/*  Large Ruffled Feather  */
UPDATE item_template SET Quality = 0, BuyPrice = 0, SellPrice = 0 WHERE entry=8426;

/*  Cat Carrier (Bombay)  */
UPDATE item_template SET bonding = 3 WHERE entry=8485;

/*  Cat Carrier (Cornish Rex)  */
UPDATE item_template SET bonding = 3 WHERE entry=8486;

/*  Cat Carrier (Orange Tabby)  */
UPDATE item_template SET bonding = 3 WHERE entry=8487;

/*  Cat Carrier (Silver Tabby)  */
UPDATE item_template SET bonding = 3 WHERE entry=8488;

/*  Cat Carrier (White Kitten)  */
UPDATE item_template SET bonding = 3 WHERE entry=8489;

/*  Cat Carrier (Siamese)  */
UPDATE item_template SET bonding = 3 WHERE entry=8490;

/*  Cat Carrier (Black Tabby)  */
UPDATE item_template SET bonding = 3 WHERE entry=8491;

/*  Parrot Cage (Green Wing Macaw)  */
UPDATE item_template SET bonding = 3 WHERE entry=8492;

/*  Parrot Cage (Hyacinth Macaw)  */
UPDATE item_template SET Quality = 1, bonding = 3 WHERE entry=8494;

/*  Parrot Cage (Senegal)  */
UPDATE item_template SET bonding = 3 WHERE entry=8495;

/*  Parrot Cage (Cockatiel)  */
UPDATE item_template SET bonding = 3 WHERE entry=8496;

/*  Rabbit Crate (Snowshoe)  */
UPDATE item_template SET bonding = 3 WHERE entry=8497;

/*  Tiny Emerald Whelpling  */
UPDATE item_template SET bonding = 3 WHERE entry=8498;

/*  Tiny Crimson Whelpling  */
UPDATE item_template SET bonding = 3 WHERE entry=8499;

/*  Great Horned Owl  */
UPDATE item_template SET bonding = 3 WHERE entry=8500;

/*  Hawk Owl  */
UPDATE item_template SET bonding = 3 WHERE entry=8501;

/*  Mageweave Bandage  */
UPDATE item_template SET BuyPrice = 1600, SellPrice = 400 WHERE entry=8544;

/*  Heavy Mageweave Bandage  */
UPDATE item_template SET BuyPrice = 2400, SellPrice = 600 WHERE entry=8545;

/*  Mithril Insignia  */
UPDATE item_template SET bonding = 4 WHERE entry=8663;

/*  Clara's Fresh Apple  */
UPDATE item_template SET BuyPrice = 4, SellPrice = 1 WHERE entry=8683;

/*  Elixir of Water Walking  */
UPDATE item_template SET ItemLevel = 34, RequiredLevel = 24 WHERE entry=8827;

/*  Essence of Agony  */
UPDATE `item_template` SET `Quality` = 0, `class` = 15, `subclass` = 0 WHERE `entry` = 8923;

/*  Dust of Deterioration  */
UPDATE `item_template` SET `Quality` = 0, `class` = 15, `subclass` = 0 WHERE `entry` = 8924;

/*  Instant Poison IV  */
UPDATE item_template SET BuyPrice = 300, SellPrice = 75 WHERE entry=8926;

/*  Instant Poison V  */
UPDATE item_template SET BuyPrice = 400, SellPrice = 100 WHERE entry=8927;

/*  Instant Poison VI  */
UPDATE item_template SET BuyPrice = 500, SellPrice = 125 WHERE entry=8928;

/*  Codex of Flash Heal  */
UPDATE item_template SET BuyPrice = 2900 WHERE entry=8964;

/*  Deadly Poison III  */
UPDATE item_template SET BuyPrice = 400, SellPrice = 100 WHERE entry=8984;

/*  Deadly Poison IV  */
UPDATE item_template SET BuyPrice = 600, SellPrice = 150 WHERE entry=8985;

/*  Magic Resistance Potion  */
UPDATE item_template SET BuyPrice = 80, SellPrice = 20 WHERE entry=9036;

/*  Mind-numbing Poison III  */
UPDATE item_template SET Quality = 1, class = 0 WHERE entry=9186;

/*  Troll Tribal Necklace  */
UPDATE item_template SET bonding = 0 WHERE entry=9259;

/*  Scroll of Protection IV  */
UPDATE item_template SET ItemLevel = 55, RequiredLevel = 45 WHERE entry=10305;

/*  Scroll of Spirit IV  */
UPDATE item_template SET ItemLevel = 55, RequiredLevel = 45 WHERE entry=10306;

/*  Scroll of Stamina IV  */
UPDATE item_template SET ItemLevel = 60, RequiredLevel = 50 WHERE entry=10307;

/*  Scroll of Intellect IV  */
UPDATE item_template SET ItemLevel = 60, RequiredLevel = 50 WHERE entry=10308;

/*  Scroll of Agility IV  */
UPDATE item_template SET ItemLevel = 65, RequiredLevel = 55 WHERE entry=10309;

/*  Scroll of Strength IV  */
UPDATE item_template SET ItemLevel = 65, RequiredLevel = 55 WHERE entry=10310;

/*  Black Kingsnake  */
UPDATE item_template SET bonding = 3 WHERE entry=10360;

/*  Brown Snake  */
UPDATE item_template SET bonding = 3 WHERE entry=10361;

/*  Crimson Snake  */
UPDATE item_template SET bonding = 3 WHERE entry=10392;

/*  Cockroach  */
UPDATE item_template SET bonding = 3 WHERE entry=10393;

/*  Prairie Dog Whistle  */
UPDATE item_template SET bonding = 3 WHERE entry=10394;

/*  Mechanical Chicken  */
UPDATE item_template SET bonding = 3 WHERE entry=10398;

/*  Undamaged Hippogryph Feather  */
UPDATE item_template SET Quality = 1 WHERE entry=10450;

/*  Explosive Arrow  */
UPDATE item_template SET BuyPrice = 300, SellPrice = 0 WHERE entry=10579;

/*  Goblin Engineer Membership Card  */
UPDATE item_template SET Quality = 1 WHERE entry=10791;

/*  Dark Whelpling  */
UPDATE item_template SET bonding = 3 WHERE entry=10822;

/*  Crystallized Note  */
UPDATE item_template SET Quality = 1 WHERE entry=10839;

/*  Crystallized Note  */
UPDATE item_template SET Quality = 1 WHERE entry=10840;

/*  Wound Poison  */
UPDATE item_template SET BuyPrice = 170, SellPrice = 42 WHERE entry=10918;

/*  Wound Poison II  */
UPDATE item_template SET BuyPrice = 270, SellPrice = 67 WHERE entry=10920;

/*  Wound Poison III  */
UPDATE item_template SET BuyPrice = 500, SellPrice = 125 WHERE entry=10921;

/*  Wound Poison IV  */
UPDATE item_template SET BuyPrice = 700, SellPrice = 175 WHERE entry=10922;

/*  Shadowforge Key  */
UPDATE item_template SET bonding = 4 WHERE entry=11000;

/*  Ancona Chicken  */
UPDATE item_template SET bonding = 3 WHERE entry=11023;

/*  Tree Frog Box  */
UPDATE item_template SET bonding = 3 WHERE entry=11026;

/*  Wood Frog Box  */
UPDATE item_template SET bonding = 3 WHERE entry=11027;

/*  Sprite Darter Egg  */
UPDATE item_template SET BuyPrice = 2000, SellPrice = 500 WHERE entry=11474;

/*  Crystal Pylon User's Manual  */
UPDATE item_template SET Quality = 1, bonding = 4 WHERE entry=11482;

/*  Altered Black Dragonflight Molt  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=11609;

/*  Lesser Arcanum of Rumination  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11622;

/*  Lesser Arcanum of Constitution  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11642;

/*  Lesser Arcanum of Tenacity  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11643;

/*  Lesser Arcanum of Resilience  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11644;

/*  Lesser Arcanum of Voracity  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11645;

/*  Lesser Arcanum of Voracity  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11646;

/*  Lesser Arcanum of Voracity  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11647;

/*  Lesser Arcanum of Voracity  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11648;

/*  Lesser Arcanum of Voracity  */
UPDATE item_template SET ItemLevel = 50, bonding = 4, RequiredLevel = 0 WHERE entry=11649;

/*  Shadowforge Torch  */
UPDATE item_template SET BuyPrice = 2846, SellPrice = 711 WHERE entry=11885;

/*  Cat Carrier (Corrupted Kitten)  */
UPDATE item_template SET bonding = 3 WHERE entry=11903;

/*  Worg Carrier  */
UPDATE item_template SET BuyPrice = 6000, SellPrice = 1500 WHERE entry=12264;

/*  Smolderweb Carrier  */
UPDATE item_template SET BuyPrice = 6000, SellPrice = 1500 WHERE entry=12529;

/*  Attuned Dampener  */
UPDATE item_template SET description = 'This object has been attuned to work against a specific being.' WHERE entry=12650;

/*  Crystal of Zin-Malor  */
UPDATE item_template SET Quality = 2 WHERE entry=13347;

/*  Greater Shadow Protection Potion  */
UPDATE item_template SET BuyPrice = 400, SellPrice = 100 WHERE entry=13459;

/*  Recipe: Transmute Water to Air  */
UPDATE item_template SET RequiredReputationRank = 0 WHERE entry=13485;

/*  Flask of the Titans  */
UPDATE item_template SET BuyPrice = 20000, SellPrice = 5000 WHERE entry=13510;

/*  Flask of Distilled Wisdom  */
UPDATE item_template SET BuyPrice = 20000, SellPrice = 5000 WHERE entry=13511;

/*  Flask of Supreme Power  */
UPDATE item_template SET BuyPrice = 20000, SellPrice = 5000 WHERE entry=13512;

/*  Flask of Chromatic Resistance  */
UPDATE item_template SET BuyPrice = 20000, SellPrice = 5000 WHERE entry=13513;

/*  Zergling Leash  */
UPDATE item_template SET Quality = 1 WHERE entry=13582;

/*  Panda Collar  */
UPDATE item_template SET Quality = 1 WHERE entry=13583;

/*  Diablo Stone  */
UPDATE item_template SET Quality = 1 WHERE entry=13584;

/*  Skeleton Key  */
UPDATE item_template SET bonding = 4 WHERE entry=13704;

/*  Runecloth Bandage  */
UPDATE item_template SET BuyPrice = 2000, SellPrice = 500 WHERE entry=14529;

/*  Ironfeather  */
UPDATE item_template SET Quality = 1, class = 7 WHERE entry=15420;

/*  Frostsaber Leather  */
UPDATE item_template SET Quality = 1, class = 7 WHERE entry=15422;

/*  Chimera Leather  */
UPDATE item_template SET Quality = 1, class = 7 WHERE entry=15423;

/*  Rotten Apple  */
UPDATE item_template SET bonding = 4 WHERE entry=15875;

/*  Lifelike Mechanical Toad  */
UPDATE item_template SET bonding = 3 WHERE entry=15996;

/*  Expert Fishing - The Bass and You  */
UPDATE item_template SET RequiredLevel = 20 WHERE entry=16083;

/*  Artisan First Aid - Heal Thyself  */
UPDATE item_template SET SellPrice = 5000 WHERE entry=16085;

/*  Commander's Steed  */
UPDATE item_template SET Quality = 4, bonding = 1, BuyPrice = 1000000 WHERE entry=16339;

/*  Wild Root  */
UPDATE item_template SET SellPrice = 175 WHERE entry=17024;

/*  Shiny Fish Scales  */
UPDATE item_template SET BuyPrice = 30 WHERE entry=17057;

/*  Fish Oil  */
UPDATE item_template SET BuyPrice = 30 WHERE entry=17058;

/*  Elegant Letter  */
UPDATE item_template SET bonding = 4 WHERE entry=17126;

/*  Blue Sack of Gems  */
UPDATE item_template SET bonding = 0 WHERE entry=17962;

/*  Red Moro'gai Gem  */
UPDATE item_template SET Quality = 2 WHERE entry=18153;

/*  Flame Mantle of the Dawn  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=18169;

/*  Frost Mantle of the Dawn  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=18170;

/*  Arcane Mantle of the Dawn  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=18171;

/*  Nature Mantle of the Dawn  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=18172;

/*  Shadow Mantle of the Dawn  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=18173;

/*  Chromatic Mantle of the Dawn  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=18182;

/*  Major Rejuvenation Potion  */
UPDATE item_template SET BuyPrice = 60, SellPrice = 15 WHERE entry=18253;

/*  Imbued Vial  */
UPDATE item_template SET BuyPrice = 30000, SellPrice = 1500 WHERE entry=18256;

/*  Formula: Enchant Weapon - Healing Power  */
UPDATE item_template SET bonding = 1 WHERE entry=18260;

/*  Arcanum of Rapidity  */
UPDATE item_template SET ItemLevel = 50, RequiredLevel = 0 WHERE entry=18329;

/*  Arcanum of Focus  */
UPDATE item_template SET ItemLevel = 50, RequiredLevel = 0 WHERE entry=18330;

/*  Arcanum of Protection  */
UPDATE item_template SET ItemLevel = 50, RequiredLevel = 0 WHERE entry=18331;

/*  Heated Ancient Blade  */
UPDATE item_template SET Quality = 4 WHERE entry=18488;

/*  Treated Ancient Blade  */
UPDATE item_template SET Quality = 4 WHERE entry=18492;

/*  Vessel of Rebirth DEPRECATED  */
UPDATE item_template SET RequiredLevel = 100 WHERE entry=18565;

/*  Essence of the Firelord DEPRECATED  */
UPDATE item_template SET Quality = 5 WHERE entry=18566;

/*  Alliance Battle Standard  */
UPDATE item_template SET BuyPrice = 50000, SellPrice = 12500 WHERE entry=18606;

/*  Horde Battle Standard  */
UPDATE item_template SET BuyPrice = 50000, SellPrice = 12500 WHERE entry=18607;

/*  Mature Black Dragon Sinew  */
UPDATE item_template SET bonding = 1 WHERE entry=18705;

/*  Combat Mana Potion  */
UPDATE item_template SET BuyPrice = 1100, SellPrice = 275 WHERE entry=18841;

/*  Turtle Egg (Loggerhead)  */
UPDATE item_template SET BuyPrice = 4000 WHERE entry=18964;

/*  Essence of the Firelord  */
UPDATE item_template SET Quality = 5 WHERE entry=19017;

/*  Stormpike Battle Standard  */
UPDATE item_template SET BuyPrice = 50000, SellPrice = 12500 WHERE entry=19045;

/*  Frostwolf Battle Standard  */
UPDATE item_template SET BuyPrice = 50000, SellPrice = 12500 WHERE entry=19046;

/*  Beasts Deck  */
UPDATE item_template SET ItemLevel = 1, BuyPrice = 400000, SellPrice = 100000 WHERE entry=19228;

/*  Warlords Deck  */
UPDATE item_template SET ItemLevel = 1, BuyPrice = 400000, SellPrice = 100000 WHERE entry=19257;

/*  Elementals Deck  */
UPDATE item_template SET ItemLevel = 1, BuyPrice = 400000, SellPrice = 100000 WHERE entry=19267;

/*  Portals Deck  */
UPDATE item_template SET ItemLevel = 1, BuyPrice = 400000, SellPrice = 100000 WHERE entry=19277;

/*  Harpy Hide Quiver  */
UPDATE item_template SET BuyPrice = 350000, SellPrice = 87500 WHERE entry=19319;

/*  Gnoll Skin Bandolier  */
UPDATE item_template SET BuyPrice = 350000, SellPrice = 87500 WHERE entry=19320;

/*  Zandalar Signet of Mojo  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=20076;

/*  Zandalar Signet of Might  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=20077;

/*  Zandalar Signet of Serenity  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=20078;

/*  Defiler's Enriched Ration  */
UPDATE item_template SET RequiredReputationFaction = 510, RequiredReputationRank = 4 WHERE entry=20222;

/*  Defiler's Field Ration  */
UPDATE item_template SET RequiredReputationFaction = 510, RequiredReputationRank = 4 WHERE entry=20223;

/*  Defiler's Iron Ration  */
UPDATE item_template SET RequiredReputationFaction = 510, RequiredReputationRank = 4 WHERE entry=20224;

/*  Highlander's Enriched Ration  */
UPDATE item_template SET RequiredReputationFaction = 509, RequiredReputationRank = 4 WHERE entry=20225;

/*  Highlander's Field Ration  */
UPDATE item_template SET RequiredReputationFaction = 509, RequiredReputationRank = 4 WHERE entry=20226;

/*  Highlander's Iron Ration  */
UPDATE item_template SET RequiredReputationFaction = 509, RequiredReputationRank = 4 WHERE entry=20227;

/*  Defiler's Mageweave Bandage  */
UPDATE item_template SET RequiredReputationFaction = 510, RequiredReputationRank = 4 WHERE entry=20232;

/*  Defiler's Runecloth Bandage  */
UPDATE item_template SET RequiredReputationFaction = 510, RequiredReputationRank = 4 WHERE entry=20234;

/*  Defiler's Silk Bandage  */
UPDATE item_template SET RequiredReputationFaction = 510, RequiredReputationRank = 4 WHERE entry=20235;

/*  Highlander's Mageweave Bandage  */
UPDATE item_template SET RequiredReputationFaction = 509, RequiredReputationRank = 4 WHERE entry=20237;

/*  Highlander's Runecloth Bandage  */
UPDATE item_template SET RequiredReputationFaction = 509, RequiredReputationRank = 4 WHERE entry=20243;

/*  Highlander's Silk Bandage  */
UPDATE item_template SET RequiredReputationFaction = 509, RequiredReputationRank = 4 WHERE entry=20244;

/*  Blue Murloc Egg  */
UPDATE item_template SET Quality = 1 WHERE entry=20371;

/*  Head of the Broodlord Lashlayer  */
UPDATE item_template SET Quality = 4, description = 'Only ONE May Rise... (and consequently, only ONE may loot this head)' WHERE entry=20383;

/*  Twilight Lexicon - Chapter 1  */
UPDATE item_template SET bonding = 5 WHERE entry=20394;

/*  Twilight Lexicon - Chapter 2  */
UPDATE item_template SET bonding = 5 WHERE entry=20395;

/*  Twilight Lexicon - Chapter 3  */
UPDATE item_template SET bonding = 5 WHERE entry=20396;

/*  Geologist's Transcription Kit  */
UPDATE item_template SET bonding = 1 WHERE entry=20453;

/*  Orange Murloc Egg  */
UPDATE item_template SET Quality = 1 WHERE entry=20651;

/*  Disgusting Oozeling  */
UPDATE item_template SET bonding = 3 WHERE entry=20769;

/*  Deadly Poison V  */
UPDATE item_template SET BuyPrice = 600, SellPrice = 150 WHERE entry=20844;

/*  Golden Token  */
UPDATE item_template SET RequiredLevel = 58 WHERE entry=20880;

/*  Hive'Zora Scout Report  */
UPDATE item_template SET ItemLevel = 60, RequiredLevel = 58 WHERE entry=21158;

/*  Hive'Regal Scout Report  */
UPDATE item_template SET ItemLevel = 60, RequiredLevel = 58 WHERE entry=21160;

/*  Hive'Ashi Scout Report  */
UPDATE item_template SET ItemLevel = 60, RequiredLevel = 58 WHERE entry=21161;

/*  Baby Shark  */
UPDATE item_template SET bonding = 3, BuyPrice = 6000 WHERE entry=21168;

/*  Fresh Holly  */
UPDATE item_template SET RequiredLevel = 40 WHERE entry=21212;

/*  Preserved Holly  */
UPDATE item_template SET RequiredLevel = 40 WHERE entry=21213;

/*  Tranquil Mechanical Yeti  */
UPDATE item_template SET bonding = 3 WHERE entry=21277;

/*  Valentine's Day Card  */
UPDATE item_template SET bonding = 0 WHERE entry=22059;

/*  Pink Murloc Egg  */
UPDATE item_template SET Quality = 1 WHERE entry=22114;

/*  Silver Shafted Arrow  */
UPDATE item_template SET bonding = 1 WHERE entry=22200;

/*  Buttermilk Delight  */
UPDATE item_template SET bonding = 1 WHERE entry=22236;

/*  Dark Desire  */
UPDATE item_template SET bonding = 1 WHERE entry=22237;

/*  Very Berry Cream  */
UPDATE item_template SET bonding = 1 WHERE entry=22238;

/*  Sweet Surprise  */
UPDATE item_template SET bonding = 1 WHERE entry=22239;

/*  Crypt Fiend Parts  */
UPDATE item_template SET BuyPrice = 0, SellPrice = 0 WHERE entry=22525;

/*  Bone Fragments  */
UPDATE item_template SET BuyPrice = 0, SellPrice = 0 WHERE entry=22526;

/*  Core of Elements  */
UPDATE item_template SET BuyPrice = 0, SellPrice = 0 WHERE entry=22527;

/*  Dark Iron Scraps  */
UPDATE item_template SET BuyPrice = 0, SellPrice = 0 WHERE entry=22528;

/*  Savage Frond  */
UPDATE item_template SET BuyPrice = 0, SellPrice = 0 WHERE entry=22529;

/*  Steam Tonk Controller  */
UPDATE item_template SET bonding = 0 WHERE entry=22728;

/*  Staff Head of Atiesh  */
UPDATE item_template SET Quality = 5 WHERE entry=22733;

/*  Base of Atiesh  */
UPDATE item_template SET Quality = 5 WHERE entry=22734;

/*  White Murloc Egg  */
UPDATE item_template SET Quality = 1 WHERE entry=22780;

/*  Polar Bear Collar  */
UPDATE item_template SET bonding = 1 WHERE entry=22781;

/*  Captured Flame  */
UPDATE item_template SET Quality = 1 WHERE entry=23083;

/*  Consecrated Sharpening Stone  */
UPDATE item_template SET BuyPrice = 160, SellPrice = 40 WHERE entry=23122;

/*  Blessed Wizard Oil  */
UPDATE item_template SET BuyPrice = 160, SellPrice = 40 WHERE entry=23123;

/*  Foror's Crate of Endless Resist Gear Storage  */
UPDATE item_template SET RequiredLevel = 60 WHERE entry=23162;

/*  Bag of Smorc Ingredients  */
UPDATE item_template SET BuyPrice = 2000, SellPrice = 500 WHERE entry=23215;

/*  iCoke Gift Box Voucher  */
UPDATE item_template SET bonding = 5 WHERE entry=23227;

/*  Fiery Festival Brew  */
UPDATE item_template SET RequiredLevel = 0 WHERE entry=23246;

/*  Burning Blossom  */
UPDATE item_template SET bonding = 0 WHERE entry=23247;

/*  Crystal Flake Throat Lozenge  */
UPDATE item_template SET BuyPrice = 3000 WHERE entry=23683;

/*  Crystal Infused Bandage  */
UPDATE item_template SET BuyPrice = 6000 WHERE entry=23684;

/*  White Tiger Cub  */
UPDATE item_template SET Quality = 1, BuyPrice = 5000, SellPrice = 1250 WHERE entry=23712;

/*  Hippogryph Hatchling  */
UPDATE item_template SET Quality = 1, BuyPrice = 5000, SellPrice = 1250 WHERE entry=23713;

/*  Riding Turtle  */
UPDATE item_template SET Quality = 1, RequiredLevel = 20 WHERE entry=23720;

/* Correct drop rate for Mature Blue Dragon Sinew */
UPDATE `creature_loot_template` SET `chance` = 0.5 WHERE `item` = 18704 AND `entry` IN (7435, 7436, 7437);
