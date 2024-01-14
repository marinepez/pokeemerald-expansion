.set LOCALID_WINGULL, 1
.set LOCALID_PLAYERFACADE, 2

MAGM_BeachShore_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MAGM_BeachShore_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MAGM_BeachShore_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_BeachShore_OnTransition
	.byte 0

MAGM_BeachShore_OnTransition:
	clearflag FLAG_SYS_SAFARI_MODE
	setflag FLAG_HIDE_MAP_NAME_POPUP
	end

MAGM_BeachShore_OnFrame:
	map_script_2 VAR_BEACH_INTRO_STATE, 0, MAGM_BeachShore_EventScript_DropMail
	.2byte 0

MAGM_BeachShore_OnWarp:
	map_script_2 VAR_BEACH_INTRO_STATE, 0, MAGM_BeachShore_EventScript_SetUpRoomObjects
	.2byte 0

MAGM_BeachShore_EventScript_SetUpRoomObjects::
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_MAGM_BEACH_SHORE
	addobject LOCALID_PLAYERFACADE
	setobjectxy LOCALID_PLAYERFACADE, 15, 10
	end

MAGM_BeachShore_EventScript_DropMail::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_BeachShore_Movement_CameraPanUp
	waitmovement 0
	removeobject LOCALID_PLAYERFACADE
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_MAGM_BEACH_SHORE
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_BeachShore_Movement_LookAtWingullExclamation
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_BeachShore_Movement_LookAtWingull
	applymovement LOCALID_WINGULL, MAGM_BeachShore_Movement_Wingull
	waitmovement 0
	removeobject LOCALID_WINGULL
	additem ITEM_FRIEND_LETTER
	additem ITEM_LEAGUE_LETTER
	additem ITEM_MASTER_BALL
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	setvar VAR_BEACH_INTRO_STATE 1
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setflag FLAG_SYS_B_DASH
	setflag FLAG_SYS_SAFARI_MODE
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	//Hiding mons that shouldn't appear at first
	setflag FLAG_HIDE_BELLOSSOM
	setflag FLAG_HIDE_LUDICOLO
	setflag FLAG_HIDE_HAWLUCHA_WRESTLING
	setflag FLAG_HIDE_PIKACHU
	setflag FLAG_HIDE_PIKACHU_CAVE
	msgbox MAGM_BeachShore_MapScripts_Text_LeftALetter, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, MAGM_BeachShore_MapScripts_EventScript_ReadLetter
	case NO, MAGM_BeachShore_MapScripts_EventScript_PutLetterAway
	case MULTI_B_PRESSED, MAGM_BeachShore_MapScripts_EventScript_PutLetterAway
	end

MAGM_BeachShore_MapScripts_EventScript_ReadLetter::
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 0 //Letter from friend
	special CheckSpecialMail
	end

MAGM_BeachShore_MapScripts_EventScript_PutLetterAway::
	msgbox MAGM_BeachShore_MapScripts_Text_PutLetterAway, MSGBOX_DEFAULT
	closemessage
	end

MAGM_BeachShore_MapScripts_EventScript_Boat::
	msgbox MAGM_BeachShore_MapScripts_Text_CantLeaveYet, MSGBOX_SIGN
	end

MAGM_BeachShore_Movement_CameraPanUp:
	delay_16
	delay_16
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	face_down
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

MAGM_BeachShore_Movement_LookAtWingullExclamation:
	face_right
	emote_exclamation_mark
	step_end

MAGM_BeachShore_Movement_LookAtWingull:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_up
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	face_left
	step_end

MAGM_BeachShore_Movement_Wingull:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MAGM_BeachShore_MapScripts_Text_PutLetterAway::
	.string "You put the letter in your bag.$"

MAGM_BeachShore_MapScripts_Text_LeftALetter::
	.string "It dropped a letter in the sand.\n"
	.string "Read it?$"

MAGM_BeachShore_MapScripts_Text_CantLeaveYet::
	.string "Can't leave yet.\n"
	.string "You need to go through with this.$"
