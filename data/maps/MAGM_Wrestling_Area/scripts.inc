MAGM_Wrestling_Area_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MAGM_Wrestling_Area_OnResume
	.byte 0

MAGM_Wrestling_Area_OnResume:
	call_if_eq VAR_TEMP_9, 0, MAGM_Wrestling_Area_EventScript_AddAudience
	end

MAGM_Wrestling_Area_EventScript_AddAudience::
	setvar VAR_TEMP_9, 1
	createvobject OBJ_EVENT_GFX_BOY_2, 2, 10, 4
	createvobject OBJ_EVENT_GFX_BOY_3, 3, 11, 4
	createvobject OBJ_EVENT_GFX_BUG_CATCHER, 4, 12, 4
	createvobject OBJ_EVENT_GFX_CAMERAMAN, 5, 13, 4
	createvobject OBJ_EVENT_GFX_CAMPER, 6, 14, 4
	createvobject OBJ_EVENT_GFX_CONTEST_JUDGE, 7, 15, 4
	createvobject OBJ_EVENT_GFX_MANIAC, 8, 16, 4
	createvobject OBJ_EVENT_GFX_DEVON_EMPLOYEE, 9, 17, 4
	createvobject OBJ_EVENT_GFX_EXPERT_F, 10, 18, 4
	createvobject OBJ_EVENT_GFX_ARTIST, 0, 19, 4
	createvobject OBJ_EVENT_GFX_BEAUTY, 1, 20, 4
	createvobject OBJ_EVENT_GFX_FISHERMAN, 13, 10, 3
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 14, 11, 3
	createvobject OBJ_EVENT_GFX_GIRL_2, 15, 12, 3
	createvobject OBJ_EVENT_GFX_GIRL_3, 16, 13, 3
	createvobject OBJ_EVENT_GFX_HEX_MANIAC, 17, 14, 3
	createvobject OBJ_EVENT_GFX_HIKER, 18, 15, 3
	createvobject OBJ_EVENT_GFX_FAT_MAN, 12, 21, 5
	createvobject OBJ_EVENT_GFX_LINK_RECEPTIONIST, 21, 21, 6
	createvobject OBJ_EVENT_GFX_LASS, 19, 9, 7
	createvobject OBJ_EVENT_GFX_LEAF, 20, 9, 8
	createvobject OBJ_EVENT_GFX_EXPERT_M, 11, 9, 9
	return
