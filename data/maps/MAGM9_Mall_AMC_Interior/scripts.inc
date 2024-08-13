.set LOCALID_GIANT, 1

MAGM9_Mall_AMC_Interior_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MAGM9_Mall_AMC_Interior_OnFrame
	.byte 0

MAGM9_Mall_AMC_Interior_OnFrame::
	map_script_2 VAR_TEMP_0, 0, MAGM9_Mall_AMC_Interior_SetGiantXY
	.2byte 0

MAGM9_Mall_AMC_Interior_SetGiantXY::
	setvar VAR_TEMP_0, 1
	setflashlevel 3
	setobjectxy LOCALID_GIANT, 8, 8
	end

MAGM9_Mall_AMC_Interior_BeforeBattleCutscene::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, AMC_Interior_Movement_CameraPanUp
	waitmovement 0
	releaseall
	end

AMC_Interior_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	delay_16
	step_end
