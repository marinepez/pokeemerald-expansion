.set LOCALID_HERACROSS, 3
.set LOCALID_EXEGGUTOR, 4
.set LOCALID_HAWLUCHA, 5
.set LOCALID_SMEARGLE, 6

MAGM_Wrestling_Area_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MAGM_Wrestling_Area_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_Wrestling_Area_OnTransition
	.byte 0

MAGM_Wrestling_Area_OnTransition:
	setflag FLAG_HIDE_MAP_NAME_POPUP
	clearflag FLAG_SYS_SAFARI_MODE
	end

MAGM_Wrestling_Area_OnResume:
	call_if_eq VAR_TEMP_9, 0, MAGM_Wrestling_Area_EventScript_AddAudience
	end

MAGM_Wrestling_Area_EventScript_AddAudience::
	getplayerxy VAR_TEMP_2, VAR_TEMP_3
	goto_if_ne VAR_TEMP_2, 28, MAGM_Wrestling_Area_EventScript_AddAudienceLeft
	goto MAGM_Wrestling_Area_EventScript_AddAudienceRight
	end

MAGM_Wrestling_Area_EventScript_SmeargleNoticePlayer::
	setvar VAR_WRESTLING_AREA_STATE 1
	playse SE_PIN
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_NoticePlayer
	waitmovement 0
	msgbox MAGM_Wrestling_Area_Text_SmeargleGuide, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_SmeargleWalk1
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Wrestling_Area_Movement_SmeargleWalk1
	waitmovement 0
	goto MAGM_Wrestling_Area_EventScript_SmeargleShowPlayerRing
	end

MAGM_Wrestling_Area_EventScript_SmeargleNoticePlayer2::
	setvar VAR_WRESTLING_AREA_STATE 1
	playse SE_PIN
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_NoticePlayer2
	waitmovement 0
	msgbox MAGM_Wrestling_Area_Text_SmeargleGuide, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_SmeargleWalk2
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Wrestling_Area_Movement_SmeargleWalk2
	waitmovement 0
	goto MAGM_Wrestling_Area_EventScript_SmeargleShowPlayerRing
	end

MAGM_Wrestling_Area_EventScript_SmeargleShowPlayerRing::
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_SmeargleWalk3
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Wrestling_Area_Movement_SmeargleWalk3
	waitmovement 0
	delay 60
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, MAGM_Wrestling_Area_Movement_CameraPanUp
	waitmovement 0
	playse SE_APPLAUSE
	delay 60
	applymovement LOCALID_EXEGGUTOR, MAGM_Wrestling_Area_Movement_LeftLunge
	waitmovement 0
	delay 60
	applymovement LOCALID_HERACROSS, MAGM_Wrestling_Area_Movement_RightJump
	waitmovement 0
	delay 60
	applymovement LOCALID_EXEGGUTOR, MAGM_Wrestling_Area_Movement_LeftJump
	waitmovement 0
	playse SE_APPLAUSE
	call MAGM_Wrestling_Area_EventScript_AllAudienceCheerFast
	delay 60
	applymovement OBJ_EVENT_ID_CAMERA, MAGM_Wrestling_Area_Movement_CameraPanDown
	waitmovement 0
	call MAGM_Wrestling_Area_EventScript_AllAudienceCheer
	special RemoveCameraObject
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_GoToCave
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Wrestling_Area_Movement_GoToCave
	waitmovement 0
	applymovement LOCALID_SMEARGLE, MAGM_Wrestling_Area_Movement_SmeargleEnterCave
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Wrestling_Area_Movement_PlayerEnterCave
	waitmovement 0
	setflag FLAG_HIDE_SMEARGLE_WRESTLING
	warpsilent MAP_MAGM_HAWLUCHA_CAVE, 0
	waitstate
	end

MAGM_Wrestling_Area_Text_SmeargleGuide::
	.string "Smeargle is leading you\n"
	.string "by the hand.$"

MAGM_Wrestling_Area_Movement_GoToCave::
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
	step_end

MAGM_Wrestling_Area_Movement_SmeargleEnterCave::
	walk_up
	set_invisible
	step_end

MAGM_Wrestling_Area_Movement_PlayerEnterCave::
	walk_left
	walk_up
	set_invisible
	step_end

MAGM_Wrestling_Area_Movement_LeftLunge::
	lock_facing_direction
	walk_fast_left
	walk_fast_right
	step_end

MAGM_Wrestling_Area_Movement_RightLunge::
	lock_facing_direction
	walk_fast_right
	walk_fast_left
	step_end

MAGM_Wrestling_Area_Movement_LeftJump::
	lock_facing_direction
	jump_left
	walk_fast_right
	step_end

MAGM_Wrestling_Area_Movement_RightJump::
	lock_facing_direction
	jump_right
	walk_fast_left
	step_end

MAGM_Wrestling_Area_Movement_CameraPanUp::
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

MAGM_Wrestling_Area_Movement_CameraPanDown::
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

MAGM_Wrestling_Area_Movement_NoticePlayer::
	face_right
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	step_end

MAGM_Wrestling_Area_Movement_NoticePlayer2::
	face_right
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

MAGM_Wrestling_Area_Movement_SmeargleWalk1::
	face_left
	delay_16
	walk_left
	step_end

MAGM_Wrestling_Area_Movement_SmeargleWalk2::
	face_up
	delay_16
	walk_up
	walk_left
	step_end

MAGM_Wrestling_Area_Movement_SmeargleWalk3::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MAGM_Wrestling_Area_EventScript_AddAudienceRight::
	createvobject OBJ_EVENT_GFX_EXPERT_F			 0, 11, 3
	createvobject OBJ_EVENT_GFX_LINK_RECEPTIONIST	 1, 12, 3
	createvobject OBJ_EVENT_GFX_HIKER				 2, 13, 3
	createvobject OBJ_EVENT_GFX_FAT_MAN				 3, 14, 3
	createvobject OBJ_EVENT_GFX_CAMPER				 4, 15, 3
	createvobject OBJ_EVENT_GFX_GENTLEMAN			 5, 16, 3
	createvobject OBJ_EVENT_GFX_MAN_2				 6, 17, 3
	createvobject OBJ_EVENT_GFX_MANIAC				 7, 18, 3
	createvobject OBJ_EVENT_GFX_HEX_MANIAC			 8, 19, 3
	createvobject OBJ_EVENT_GFX_MAN_3				 9, 10, 4
	createvobject OBJ_EVENT_GFX_FISHERMAN			10, 11, 4
	createvobject OBJ_EVENT_GFX_ARTIST				11, 12, 4
	createvobject OBJ_EVENT_GFX_BEAUTY				12, 13, 4
	createvobject OBJ_EVENT_GFX_GIRL_2				13, 14, 4
	createvobject OBJ_EVENT_GFX_BOY_3				14, 15, 4
	createvobject OBJ_EVENT_GFX_LASS				15, 16, 4
	createvobject OBJ_EVENT_GFX_MOM					16, 17, 4
	createvobject OBJ_EVENT_GFX_LEAF				17, 18, 4
	createvobject OBJ_EVENT_GFX_CONTEST_JUDGE		18, 20, 4
	createvobject OBJ_EVENT_GFX_GIRL_3				19,  9, 5, 3, 7
	createvobject OBJ_EVENT_GFX_EXPERT_M			20,  9, 6, 3, 7
	createvobject OBJ_EVENT_GFX_BUG_CATCHER			21,  9, 7, 3, 7
	createvobject OBJ_EVENT_GFX_CAMERAMAN			22,  9, 8, 3, 7
	createvobject OBJ_EVENT_GFX_BOY_2				23,  9, 9, 3, 7
	createvobject OBJ_EVENT_GFX_DEVON_EMPLOYEE		24, 21, 6, 3, 6
	createvobject OBJ_EVENT_GFX_MAN_4				25, 21, 7, 3, 6
	createvobject OBJ_EVENT_GFX_MAN_5				26, 21, 9, 3, 6
	createvobject OBJ_EVENT_GFX_MART_EMPLOYEE		27, 21, 10, 3, 6
	end

MAGM_Wrestling_Area_EventScript_AddAudienceLeft::
	createvobject OBJ_EVENT_GFX_EXPERT_F			 0, 10, 3
	createvobject OBJ_EVENT_GFX_LINK_RECEPTIONIST	 1, 11, 3
	createvobject OBJ_EVENT_GFX_HIKER				 2, 12, 3
	createvobject OBJ_EVENT_GFX_FAT_MAN				 3, 13, 3
	createvobject OBJ_EVENT_GFX_CAMPER				 4, 14, 3
	createvobject OBJ_EVENT_GFX_GENTLEMAN			 5, 15, 3
	createvobject OBJ_EVENT_GFX_MAN_2				 6, 16, 3
	createvobject OBJ_EVENT_GFX_MANIAC				 7, 17, 3
	createvobject OBJ_EVENT_GFX_HEX_MANIAC			 8, 18, 3
	createvobject OBJ_EVENT_GFX_MAN_3				 9,  9, 4
	createvobject OBJ_EVENT_GFX_FISHERMAN			10, 10, 4
	createvobject OBJ_EVENT_GFX_ARTIST				11, 11, 4
	createvobject OBJ_EVENT_GFX_BEAUTY				12, 12, 4
	createvobject OBJ_EVENT_GFX_GIRL_2				13, 13, 4
	createvobject OBJ_EVENT_GFX_BOY_3				14, 14, 4
	createvobject OBJ_EVENT_GFX_LASS				15, 15, 4
	createvobject OBJ_EVENT_GFX_MOM					16, 16, 4
	createvobject OBJ_EVENT_GFX_LEAF				17, 17, 4
	createvobject OBJ_EVENT_GFX_CONTEST_JUDGE		18, 19, 4
	createvobject OBJ_EVENT_GFX_GIRL_3				19,  8, 5, 3, 7
	createvobject OBJ_EVENT_GFX_EXPERT_M			20,  8, 6, 3, 7
	createvobject OBJ_EVENT_GFX_BUG_CATCHER			21,  8, 7, 3, 7
	createvobject OBJ_EVENT_GFX_CAMERAMAN			22,  8, 8, 3, 7
	createvobject OBJ_EVENT_GFX_BOY_2				23,  8, 9, 3, 7
	createvobject OBJ_EVENT_GFX_DEVON_EMPLOYEE		24, 20, 6, 3, 6
	createvobject OBJ_EVENT_GFX_MAN_4				25, 20, 7, 3, 6
	createvobject OBJ_EVENT_GFX_MAN_5				26, 20, 9, 3, 6
	createvobject OBJ_EVENT_GFX_MART_EMPLOYEE		27, 20, 10, 3, 6
	end

MAGM_Wrestling_Area_EventScript_DoAudienceLookAround::
	gettime
	call_if_eq VAR_0x8002,  0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_A
	call_if_eq VAR_0x8002, 15, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_B
	call_if_eq VAR_0x8002, 30, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_C
	call_if_eq VAR_0x8002, 40, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_D
	call_if_eq VAR_0x8002, 50, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_E
	call_if_eq VAR_0x8002, 10, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_A
	call_if_eq VAR_0x8002, 25, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_B
	call_if_eq VAR_0x8002, 45, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_C
	call_if_eq VAR_0x8002, 55, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_D
	call_if_eq VAR_0x8002, 05, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_E
	release
	end

MAGM_Wrestling_Area_EventScript_AllAudienceCheer::
	turnvobject  0, 4
	turnvobject  1, 4
	turnvobject  2, 4
	turnvobject  3, 4
	turnvobject  4, 4
	turnvobject  5, 4
	turnvobject  6, 4
	turnvobject  7, 4
	turnvobject  8, 4
	turnvobject  9, 4
	turnvobject 10, 4
	turnvobject 11, 4
	turnvobject 12, 4
	turnvobject 13, 4
	turnvobject 14, 4
	turnvobject 15, 4
	turnvobject 16, 4
	turnvobject 17, 4
	turnvobject 18, 4
	turnvobject 19, 7
	turnvobject 20, 7
	turnvobject 21, 7
	turnvobject 22, 7
	turnvobject 23, 7
	turnvobject 24, 6
	turnvobject 25, 6
	turnvobject 26, 6
	turnvobject 27, 6
	release
	return

MAGM_Wrestling_Area_EventScript_AllAudienceCheerFast::
	turnvobject  0, 8
	turnvobject  1, 8
	turnvobject  2, 8
	turnvobject  3, 8
	turnvobject  4, 8
	turnvobject  5, 8
	turnvobject  6, 8
	turnvobject  7, 8
	turnvobject  8, 8
	turnvobject  9, 8
	turnvobject 10, 8
	turnvobject 11, 8
	turnvobject 12, 8
	turnvobject 13, 8
	turnvobject 14, 8
	turnvobject 15, 8
	turnvobject 16, 8
	turnvobject 17, 8
	turnvobject 18, 8
	turnvobject 19, 11
	turnvobject 20, 11
	turnvobject 21, 11
	turnvobject 22, 11
	turnvobject 23, 11
	turnvobject 24, 10
	turnvobject 25, 10
	turnvobject 26, 10
	turnvobject 27, 10
	release
	return

MAGM_Wrestling_Area_EventScript_AllAudienceStopCheer::
	turnvobject  0, 0
	turnvobject  1, 0
	turnvobject  2, 0
	turnvobject  3, 0
	turnvobject  4, 0
	turnvobject  5, 0
	turnvobject  6, 0
	turnvobject  7, 0
	turnvobject  8, 0
	turnvobject  9, 0
	turnvobject 10, 0
	turnvobject 11, 0
	turnvobject 12, 0
	turnvobject 13, 0
	turnvobject 14, 0
	turnvobject 15, 0
	turnvobject 16, 0
	turnvobject 17, 0
	turnvobject 18, 0
	turnvobject 19, 3
	turnvobject 20, 3
	turnvobject 21, 3
	turnvobject 22, 3
	turnvobject 23, 3
	turnvobject 24, 2
	turnvobject 25, 2
	turnvobject 26, 2
	turnvobject 27, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround::
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_A
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_B
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_A
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_C
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_D
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_B
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_E
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_C
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_D
	delay 30
	call MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_E
	end

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_A::
	random 10
	copyvar VAR_TEMP_A, VAR_RESULT
	call_if_eq VAR_TEMP_A, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupA
	call_if_eq VAR_TEMP_A, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupB
	call_if_eq VAR_TEMP_A, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupC
	call_if_eq VAR_TEMP_A, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupD
	call_if_eq VAR_TEMP_A, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupE
	call_if_eq VAR_TEMP_A, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupF
	call_if_eq VAR_TEMP_A, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupG
	call_if_eq VAR_TEMP_A, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupH
	call_if_eq VAR_TEMP_A, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupJ
	call_if_eq VAR_TEMP_A, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_A::
	call_if_eq VAR_TEMP_A, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupA
	call_if_eq VAR_TEMP_A, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupB
	call_if_eq VAR_TEMP_A, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupC
	call_if_eq VAR_TEMP_A, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupD
	call_if_eq VAR_TEMP_A, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupE
	call_if_eq VAR_TEMP_A, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupF
	call_if_eq VAR_TEMP_A, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupG
	call_if_eq VAR_TEMP_A, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupH
	call_if_eq VAR_TEMP_A, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupJ
	call_if_eq VAR_TEMP_A, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_B::
	random 10
	copyvar VAR_TEMP_B, VAR_RESULT
	call_if_eq VAR_TEMP_B, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupA
	call_if_eq VAR_TEMP_B, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupB
	call_if_eq VAR_TEMP_B, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupC
	call_if_eq VAR_TEMP_B, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupD
	call_if_eq VAR_TEMP_B, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupE
	call_if_eq VAR_TEMP_B, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupF
	call_if_eq VAR_TEMP_B, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupG
	call_if_eq VAR_TEMP_B, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupH
	call_if_eq VAR_TEMP_B, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupJ
	call_if_eq VAR_TEMP_B, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_B::
	call_if_eq VAR_TEMP_B, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupA
	call_if_eq VAR_TEMP_B, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupB
	call_if_eq VAR_TEMP_B, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupC
	call_if_eq VAR_TEMP_B, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupD
	call_if_eq VAR_TEMP_B, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupE
	call_if_eq VAR_TEMP_B, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupF
	call_if_eq VAR_TEMP_B, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupG
	call_if_eq VAR_TEMP_B, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupH
	call_if_eq VAR_TEMP_B, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupJ
	call_if_eq VAR_TEMP_B, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_C::
	random 10
	copyvar VAR_TEMP_C, VAR_RESULT
	call_if_eq VAR_TEMP_C, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupA
	call_if_eq VAR_TEMP_C, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupB
	call_if_eq VAR_TEMP_C, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupC
	call_if_eq VAR_TEMP_C, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupD
	call_if_eq VAR_TEMP_C, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupE
	call_if_eq VAR_TEMP_C, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupF
	call_if_eq VAR_TEMP_C, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupG
	call_if_eq VAR_TEMP_C, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupH
	call_if_eq VAR_TEMP_C, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupJ
	call_if_eq VAR_TEMP_C, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_C::
	call_if_eq VAR_TEMP_C, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupA
	call_if_eq VAR_TEMP_C, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupB
	call_if_eq VAR_TEMP_C, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupC
	call_if_eq VAR_TEMP_C, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupD
	call_if_eq VAR_TEMP_C, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupE
	call_if_eq VAR_TEMP_C, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupF
	call_if_eq VAR_TEMP_C, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupG
	call_if_eq VAR_TEMP_C, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupH
	call_if_eq VAR_TEMP_C, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupJ
	call_if_eq VAR_TEMP_C, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_D::
	random 10
	copyvar VAR_TEMP_D, VAR_RESULT
	call_if_eq VAR_TEMP_D, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupA
	call_if_eq VAR_TEMP_D, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupB
	call_if_eq VAR_TEMP_D, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupC
	call_if_eq VAR_TEMP_D, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupD
	call_if_eq VAR_TEMP_D, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupE
	call_if_eq VAR_TEMP_D, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupF
	call_if_eq VAR_TEMP_D, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupG
	call_if_eq VAR_TEMP_D, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupH
	call_if_eq VAR_TEMP_D, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupJ
	call_if_eq VAR_TEMP_D, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_D::
	call_if_eq VAR_TEMP_D, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupA
	call_if_eq VAR_TEMP_D, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupB
	call_if_eq VAR_TEMP_D, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupC
	call_if_eq VAR_TEMP_D, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupD
	call_if_eq VAR_TEMP_D, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupE
	call_if_eq VAR_TEMP_D, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupF
	call_if_eq VAR_TEMP_D, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupG
	call_if_eq VAR_TEMP_D, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupH
	call_if_eq VAR_TEMP_D, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupJ
	call_if_eq VAR_TEMP_D, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_ChooseRandomGroup_E::
	random 10
	copyvar VAR_TEMP_E, VAR_RESULT
	call_if_eq VAR_TEMP_E, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupA
	call_if_eq VAR_TEMP_E, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupB
	call_if_eq VAR_TEMP_E, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupC
	call_if_eq VAR_TEMP_E, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupD
	call_if_eq VAR_TEMP_E, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupE
	call_if_eq VAR_TEMP_E, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupF
	call_if_eq VAR_TEMP_E, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupG
	call_if_eq VAR_TEMP_E, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupH
	call_if_eq VAR_TEMP_E, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupJ
	call_if_eq VAR_TEMP_E, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_StopGroup_E::
	call_if_eq VAR_TEMP_E, 0, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupA
	call_if_eq VAR_TEMP_E, 1, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupB
	call_if_eq VAR_TEMP_E, 2, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupC
	call_if_eq VAR_TEMP_E, 3, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupD
	call_if_eq VAR_TEMP_E, 4, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupE
	call_if_eq VAR_TEMP_E, 5, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupF
	call_if_eq VAR_TEMP_E, 6, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupG
	call_if_eq VAR_TEMP_E, 7, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupH
	call_if_eq VAR_TEMP_E, 8, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupJ
	call_if_eq VAR_TEMP_E, 9, MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupK
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupA::
	turnvobject  0, 4
	turnvobject 11, 4
	turnvobject 14, 4
	turnvobject 18, 4
	turnvobject 27, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupA::
	turnvobject  0, 0
	turnvobject 11, 0
	turnvobject 14, 0
	turnvobject 18, 0
	turnvobject 27, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupB::
	turnvobject  1, 4
	turnvobject  7, 4
	turnvobject 12, 4
	turnvobject 25, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupB::
	turnvobject  1, 0
	turnvobject  7, 0
	turnvobject 12, 0
	turnvobject 25, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupC::
	turnvobject  0, 4
	turnvobject 15, 4
	turnvobject 22, 7
	turnvobject 27, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupC::
	turnvobject  0, 0
	turnvobject 15, 0
	turnvobject 22, 3
	turnvobject 27, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupD::
	turnvobject  2, 4
	turnvobject  6, 4
	turnvobject 11, 4
	turnvobject 17, 4
	turnvobject 26, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupD::
	turnvobject  2, 0
	turnvobject  6, 0
	turnvobject 11, 0
	turnvobject 17, 0
	turnvobject 26, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupE::
	turnvobject  3, 4
	turnvobject 16, 4
	turnvobject 22, 7
	turnvobject 25, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupE::
	turnvobject  3, 0
	turnvobject 16, 0
	turnvobject 22, 3
	turnvobject 25, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupF::
	turnvobject  0, 4
	turnvobject  5, 4
	turnvobject 13, 4
	turnvobject 19, 7
	turnvobject 20, 7
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupF::
	turnvobject  0, 0
	turnvobject  5, 0
	turnvobject 13, 0
	turnvobject 19, 3
	turnvobject 20, 3
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupG::
	turnvobject  7, 4
	turnvobject  9, 4
	turnvobject 17, 4
	turnvobject 21, 7
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupG::
	turnvobject  7, 0
	turnvobject  9, 0
	turnvobject 17, 0
	turnvobject 21, 3
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupH::
	turnvobject 11, 4
	turnvobject 22, 7
	turnvobject 19, 7
	turnvobject 20, 7
	turnvobject 24, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupH::
	turnvobject 11, 0
	turnvobject 22, 3
	turnvobject 19, 3
	turnvobject 20, 3
	turnvobject 24, 2
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupJ::
	turnvobject  3, 4
	turnvobject  7, 4
	turnvobject 10, 4
	turnvobject 13, 4
	turnvobject 23, 7
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupJ::
	turnvobject  3, 0
	turnvobject  7, 0
	turnvobject 10, 0
	turnvobject 13, 0
	turnvobject 23, 3
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceLookAround_GroupK::
	turnvobject  4, 4
	turnvobject  8, 4
	turnvobject  9, 4
	turnvobject 25, 6
	release
	return

MAGM_Wrestling_Area_EventScript_StaggeredAudienceBeStill_GroupK::
	turnvobject  4, 0
	turnvobject  8, 0
	turnvobject  9, 0
	turnvobject 25, 2
	release
	return
