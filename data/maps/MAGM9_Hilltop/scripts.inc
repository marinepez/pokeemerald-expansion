MAGM9_Hilltop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM9_Hilltop_OnTransition
	.byte 0

MAGM9_Hilltop_OnTransition:
	setwarp MAP_MAGM9_STAIRS_DOWN, 2, 2
	end

