.set LOCALID_GIANT, 1

MAGM9_Mall_AMC_Interior_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MAGM9_Mall_AMC_Interior_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MAGM9_Mall_AMC_Interior_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MAGM9_Mall_AMC_Interior_OnWarp
	.byte 0

MAGM9_Mall_AMC_Interior_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MAGM9_Mall_AMC_Interior_HideRollingGiant
	end

MAGM9_Mall_AMC_Interior_OnWarp::
	map_script_2 VAR_TEMP_2, 0, MAGM9_Mall_AMC_Interior_SetPlayerPos
	.2byte 0

MAGM9_Mall_AMC_Interior_OnFrame::
	map_script_2 VAR_TEMP_1, 0, MAGM9_Mall_AMC_Interior_SetGiantXY
	.2byte 0

MAGM9_Mall_AMC_Interior_HideRollingGiant:
	removeobject LOCALID_GIANT
	return

MAGM9_Mall_AMC_Interior_SetPlayerPos::
	setvar VAR_TEMP_2, 1
	setflag FLAG_DISABLE_GIANT_ENCOUNTERS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	setflashlevel 3
	end

MAGM9_Mall_AMC_Interior_SetGiantXY::
	setvar VAR_TEMP_1, 1
	setobjectxy LOCALID_GIANT, 8, 8
	end

MAGM9_Mall_AMC_Interior_BeforeBattleCutscene::
	lockall
	createplayerfacade
	setflag FLAG_DISABLE_COLLISION
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	delay 32
	setflag FLAG_FORCE_AMC_LIGHTS
	setflag FLAG_AMC_LIGHTS_ON
	applymovement OBJ_EVENT_ID_PLAYER, AMC_Interior_Movement_CameraPanUp
	call MAGM9_Mall_AMC_Interior_FlickerLights
	waitmovement 0
	call MAGM9_Mall_AMC_Interior_ShowPortrait
	delay 16
	setflashalpha 16
	clearflag FLAG_AMC_LIGHTS_ON
	playse SE_POWER_ON
	delay 16
	playse SE_ROLLING
	delay 80
	setwildbattle SPECIES_ROLLING_GIANT, 80, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	releaseall
	end

MAGM9_Mall_AMC_Interior_FlickerLights::
	delay 18
	clearflag FLAG_AMC_LIGHTS_ON
	delay 4
	setflag FLAG_AMC_LIGHTS_ON
	delay 9
	clearflag FLAG_AMC_LIGHTS_ON
	delay 14
	setflag FLAG_AMC_LIGHTS_ON
	delay 25
	clearflag FLAG_AMC_LIGHTS_ON
	delay 39
	setflag FLAG_AMC_LIGHTS_ON
	delay 7
	clearflag FLAG_AMC_LIGHTS_ON
	delay 11
	setflag FLAG_AMC_LIGHTS_ON
	delay 20
	return

MAGM9_Mall_AMC_Interior_ShowPortrait::
	setmetatile 7, 1, METATILE_DewfordGym_Reverchon_1, FALSE
	setmetatile 8, 1, METATILE_DewfordGym_Reverchon_2, FALSE
	setmetatile 9, 1, METATILE_DewfordGym_Reverchon_3, FALSE
	setmetatile 7, 2, METATILE_DewfordGym_Reverchon_4, FALSE
	setmetatile 8, 2, METATILE_DewfordGym_Reverchon_5, FALSE
	setmetatile 9, 2, METATILE_DewfordGym_Reverchon_6, FALSE
	setmetatile 7, 3, METATILE_DewfordGym_Reverchon_7, FALSE
	setmetatile 8, 3, METATILE_DewfordGym_Reverchon_8, FALSE
	setmetatile 9, 3, METATILE_DewfordGym_Reverchon_9, FALSE
	setmetatile 6, 4, METATILE_DewfordGym_Reverchon_10, FALSE
	setmetatile 7, 4, METATILE_DewfordGym_Reverchon_11, FALSE
	setmetatile 8, 4, METATILE_DewfordGym_Reverchon_12, FALSE
	setmetatile 9, 4, METATILE_DewfordGym_Reverchon_13, FALSE
	setmetatile 6, 5, METATILE_DewfordGym_Reverchon_14, FALSE
	setmetatile 7, 5, METATILE_DewfordGym_Reverchon_15, FALSE
	setmetatile 8, 5, METATILE_DewfordGym_Reverchon_16, FALSE
	setmetatile 9, 5, METATILE_DewfordGym_Reverchon_17, FALSE
	clearflag FLAG_AMC_LIGHTS_ON
	special DrawWholeMapView
	return

MAGM9_Mall_AMC_Interior_FlashlightDied::
	goto_if_ne VAR_TEMP_3, 0, MAGM9_Mall_AMC_Interior_DoNothing
	setvar VAR_TEMP_3, 1
	playse SE_CLICK
	setflashlevel 8
	delay 32
	msgbox AMC_Interior_Text_FlashlightDead, MSGBOX_DEFAULT
	closemessage
MAGM9_Mall_AMC_Interior_DoNothing::
	end

AMC_Interior_Text_FlashlightDead::
	.string "Your flashlight died...$"

AMC_Interior_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	delay_16
	step_end
