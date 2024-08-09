MAGM9_GameOver_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MAGM9_GameOver_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MAGM9_GameOver_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MAGM9_GameOver_OnFrame
	.byte 0

MAGM9_GameOver_OnLoad:
	setflag FLAG_USE_FOREST_PAL
	setflag FLAG_GRAYSCALE
	end

MAGM9_GameOver_OnWarp:
	map_script_2 VAR_TEMP_0, 0, MAGM9_GameOver_Setup
	.2byte 0

MAGM9_GameOver_OnFrame:
	map_script_2 VAR_TEMP_0, 0, MAGM9_GameOver
	.2byte 0

MAGM9_GameOver_Setup::
	setobjectxy OBJ_EVENT_ID_PLAYER, 10, 12
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	end

MAGM9_GameOver::
	lockall
	delay 340
	applymovement 0xFF, MAGM9_GameOver_CameraPan
	delay 80
	setvar VAR_0x8004, 4  @ vertical pan
	setvar VAR_0x8005, 4  @ horizontal pan
	setvar VAR_0x8006, 255  @ num shakes
	setvar VAR_0x8007, 1  @ shake delay
	special ShakeCamera
	delay 40
	setvar VAR_0x8004, 8  @ vertical pan
	setvar VAR_0x8005, 8  @ horizontal pan
	playse SE_RESET
	fadescreenspeed FADE_TO_WHITE, 6
	special DoSoftReset
	end

MAGM9_GameOver_CameraPan:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end
