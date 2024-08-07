MAGM9_Hilltop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM9_Hilltop_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MAGM9_Hilltop_OnWarp
	.byte 0

MAGM9_Hilltop_OnTransition:
	setwarp MAP_MAGM9_STAIRS_DOWN, 1, 2
	end

MAGM9_Hilltop_OnWarp::
	map_script_2 VAR_TEMP_0, 0, MAGM9_Hilltop_EventScript_SetUpRoomObjects
	.2byte 0

MAGM9_Hilltop_EventScript_SetUpRoomObjects::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	end