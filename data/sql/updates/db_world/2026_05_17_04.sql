-- DB update 2026_05_17_03 -> 2026_05_17_04
-- Correct Fix for Issue 25666
UPDATE `smart_scripts` SET `event_param5` = 1 WHERE `entryorguid` IN (28715,28347,29491,28997) and `event_type` = 10;
