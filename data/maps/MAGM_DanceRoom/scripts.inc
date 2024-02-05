.set LOCALID_GLOOM, 1
.set LOCALID_LOMBRE, 2
.set LOCALID_ORICORIO, 4
.set LOCALID_MAROWAK, 5
.set LOCALID_LUDICOLO, 6
.set LOCALID_BELLOSSOM, 7

.set PARTYID_GLOOM, 0
.set PARTYID_LOMBRE, 1
.set BOXID_GLOOM, 0
.set BOXID_LOMBRE, 1

MAGM_DanceRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_DanceRoom_OnTransition
	.byte 0

MAGM_DanceRoom_OnTransition:
	setflag FLAG_HIDE_MAP_NAME_POPUP
	clearflag FLAG_SYS_SAFARI_MODE
	call_if_eq VAR_MAGM_DANCE_AREA_STATE, 1, MAGM_DanceRoom_MoveDancersToHigherStage
	end

MAGM_DanceRoom_EventScript_GiveMons::
	setvar VAR_TEMP_0, 1
	special ZeroPlayerPartyMons
	//Get Gloom from PC
	setvar VAR_0x8004, PARTYID_GLOOM
	setvar VAR_0x8005, BOXID_GLOOM
	special ScriptGetBoxMon
	//Get Lombre from PC
	setvar VAR_0x8004, PARTYID_LOMBRE
	setvar VAR_0x8005, BOXID_LOMBRE
	special ScriptGetBoxMon
	return

MAGM_DanceRoom_EventScript_SendMonsToPC::
	setvar VAR_TEMP_0, 0
	//Send Gloom to PC
	setvar VAR_0x8004, BOXID_GLOOM
	setvar VAR_0x8005, PARTYID_GLOOM
	special ScriptSetBoxMon
	//Send Lombre to PC
	setvar VAR_0x8004, BOXID_LOMBRE
	setvar VAR_0x8005, PARTYID_LOMBRE
	special ScriptSetBoxMon
	special ZeroPlayerPartyMons
	return

MAGM_DanceRoom_MoveDancersToHigherStage::
	setobjectxyperm LOCALID_GLOOM, 12, 9
	setobjectxyperm LOCALID_LOMBRE, 14, 9
	return

MAGM_DanceRoom_EventScript_Bellossom::
	playmoncry SPECIES_BELLOSSOM, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_BELLOSSOM_GAVE_PAGE, MAGM_BeachShore_EventScript_GiveFirstLetter
	msgbox MAGM_DanceRoom_Text_BellossomHappy, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_PlayerDance
	end

MAGM_DanceRoom_EventScript_Ludicolo::
	playmoncry SPECIES_LUDICOLO, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_LUDICOLO_GAVE_PAGE, MAGM_BeachShore_EventScript_GiveSecondLetter
	msgbox MAGM_DanceRoom_Text_LudicoloHappy, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_PlayerDance
	end

MAGM_BeachShore_EventScript_GiveFirstLetter::
	setflag FLAG_BELLOSSOM_GAVE_PAGE
	bufferspeciesname 0, SPECIES_BELLOSSOM
	msgbox MAGM_DanceRoom_Text_MonWantsToGiveYou, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	closemessage
	end

MAGM_BeachShore_EventScript_GiveSecondLetter::
	setflag FLAG_LUDICOLO_GAVE_PAGE
	bufferspeciesname 0, SPECIES_LUDICOLO
	msgbox MAGM_DanceRoom_Text_MonWantsToGiveYou, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	closemessage
	end

MAGM_DanceRoom_EventScript_Marowak::
	playmoncry SPECIES_MAROWAK_ALOLAN, CRY_MODE_NORMAL
	waitmoncry
	bufferspeciesname 0, SPECIES_MAROWAK
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_PlayerDance
	end

MAGM_DanceRoom_EventScript_Oricorio::
	playmoncry SPECIES_ORICORIO, CRY_MODE_NORMAL
	waitmoncry
	bufferspeciesname 0, SPECIES_ORICORIO
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_PlayerDance
	end

MAGM_DanceRoom_EventScript_Thwackey::
	playmoncry SPECIES_THWACKEY, CRY_MODE_NORMAL
	waitmoncry
	end

MAGM_DanceRoom_EventScript_DanceChallengeMonsAskForHelp::
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_GloomDanceShort
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_LombreDanceShort
	waitmovement 0
	msgbox MAGM_DanceRoom_Text_ThisIsADanceBattle, MSGBOX_DEFAULT
	waitmessage
	applymovement LOCALID_GLOOM, Common_Movement_FaceDown
	applymovement LOCALID_LOMBRE, Common_Movement_FaceDown
	delay 16
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_HelpThemDance, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_DoDanceBattle
	msgbox MAGM_DanceRoom_Text_TheyWillWait, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

MAGM_DanceRoom_EventScript_SecondTimeMonsAskForHelp::
	msgbox MAGM_DanceRoom_Text_HelpThemDance, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_DoDanceBattle
	return

MAGM_DanceRoom_DoDanceBattle::
	applymovement LOCALID_LOMBRE, Common_Movement_FaceUp
	applymovement LOCALID_GLOOM, Common_Movement_FaceUp
	applymovement LOCALID_ORICORIO, Common_Movement_FaceDown
	applymovement LOCALID_MAROWAK, Common_Movement_FaceLeft
	clearflag FLAG_SYS_SAFARI_MODE
	trainerbattle_double TRAINER_DANCERS, GabbyAndTy_Text_TyIntro, GabbyAndTy_Text_TyDefeat, GabbyAndTy_Text_TyNotEnoughMons, MAGM_DanceRoom_AfterDanceBattle
	end

MAGM_DanceRoom_AfterDanceBattle::
	call MAGM_DanceRoom_EventScript_SendMonsToPC
	setvar VAR_MAGM_DANCE_AREA_STATE, 2
	playmoncry SPECIES_ORICORIO, CRY_MODE_NORMAL
	waitmoncry
	playse SE_LEDGE
	applymovement LOCALID_ORICORIO, MAGM_DanceRoom_Movement_OricorioGiveStones
	waitmovement 0
	fadeoutbgm 1
	delay 30
	applymovement LOCALID_GLOOM, Common_Movement_WalkInPlaceDown
	applymovement LOCALID_LOMBRE, Common_Movement_WalkInPlaceDown
	playse MUS_EVOLUTION_INTRO
	waitse
	playbgm MUS_EVOLUTION, FALSE
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_EvolutionSpin
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_EvolutionSpin
	waitmovement 0
	fadescreen FADE_TO_WHITE
	fadeoutbgm 1
	delay 30
	playmoncry SPECIES_BELLOSSOM, CRY_MODE_NORMAL
	waitmoncry
	delay 30
	playmoncry SPECIES_LUDICOLO, CRY_MODE_NORMAL
	waitmoncry
	clearflag FLAG_HIDE_BELLOSSOM
	clearflag FLAG_HIDE_LUDICOLO
	removeobject LOCALID_GLOOM, MAP_MAGM_DANCE_ROOM
	removeobject LOCALID_LOMBRE, MAP_MAGM_DANCE_ROOM
	addobject LOCALID_BELLOSSOM, MAP_MAGM_DANCE_ROOM
	addobject LOCALID_LUDICOLO, MAP_MAGM_DANCE_ROOM
	setobjectxy LOCALID_BELLOSSOM, 12, 9
	setobjectxy LOCALID_LUDICOLO, 14, 9
	setobjectxyperm LOCALID_BELLOSSOM, 12, 9
	setobjectxyperm LOCALID_LUDICOLO, 14, 9
	fadescreen FADE_FROM_WHITE
	playse MUS_EVOLVED
	waitse
	playbgm MUS_SAFARI_ZONE, FALSE
	releaseall
	end

MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene::
	goto_if_eq VAR_GLOOM_MOVE4,  0, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_End
	goto_if_eq VAR_LOMBRE_MOVE4, 0, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_End
	goto_if_eq VAR_MAGM_DANCE_AREA_STATE, 1, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_End
	setvar VAR_MAGM_DANCE_AREA_STATE, 1
	applymovement LOCALID_GLOOM, Common_Movement_FacePlayer
	applymovement LOCALID_LOMBRE, Common_Movement_FacePlayer
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	delay 16
	playmoncry SPECIES_LOMBRE, CRY_MODE_NORMAL
	waitmoncry
	delay 16
	//Start moving towards the ladder
	getplayerxy VAR_TEMP_2, VAR_TEMP_3
MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_CheckIfGloomMoves::
	goto_if_ne VAR_TEMP_2,  9, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_CheckIfLombreMoves
	goto_if_ne VAR_TEMP_3, 13, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_CheckIfLombreMoves
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_WalkRightUpAlt
	goto MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_DoLombreNormalMovement
MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_CheckIfLombreMoves::
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_WalkRightUpNormal
	goto_if_ne VAR_TEMP_2, 11, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_DoLombreNormalMovement
	goto_if_ne VAR_TEMP_3, 13, MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_DoLombreNormalMovement
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_WalkRightUpAlt
	goto MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_MonsGoToLadder
MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_DoLombreNormalMovement::
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_WalkRightUpNormal
MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_MonsGoToLadder::
	waitmovement 0
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_LombreWalkToLadder
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_GloomWalkToLadder
	waitmovement 0
	setobjectxyperm LOCALID_GLOOM, 12, 9
	setobjectxyperm LOCALID_LOMBRE, 14, 9
MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene_End::
	releaseall
	end

EventScript_GiveGloomSitrusBerry::
	goto_if_set FLAG_GLOOM_SITRUS, EventScript_GiveGloomSitrusBerry_End
	playse SE_BALL
	applymovement LOCALID_GLOOM Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_GLOOM Common_Movement_QuestionMark
	applymovement LOCALID_GLOOM Common_Movement_Delay48
	waitse
	bufferspeciesname 0, SPECIES_GLOOM
	msgbox MAGM_DanceRoom_Text_MonNoticedBerry, MSGBOX_DEFAULT
	setflag FLAG_GLOOM_SITRUS
	removeitem ITEM_SITRUS_BERRY, 1
	closemessage
EventScript_GiveGloomSitrusBerry_End::
	release
	return

EventScript_GiveLombreSitrusBerry::
	goto_if_set FLAG_LOMBRE_SITRUS, EventScript_GiveLombreSitrusBerry_End
	playse SE_BALL
	applymovement LOCALID_LOMBRE Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_LOMBRE Common_Movement_QuestionMark
	applymovement LOCALID_LOMBRE Common_Movement_Delay48
	waitse
	bufferspeciesname 0, SPECIES_LOMBRE
	msgbox MAGM_DanceRoom_Text_MonNoticedBerry, MSGBOX_DEFAULT
	setflag FLAG_LOMBRE_SITRUS
	removeitem ITEM_SITRUS_BERRY, 1
	closemessage
EventScript_GiveLombreSitrusBerry_End::
	release
	return

MAGM_DanceRoom_EventScript_Gloom::
	checkitem ITEM_SITRUS_BERRY, 1
	call_if_eq VAR_RESULT, TRUE, EventScript_GiveGloomSitrusBerry
	call_if_eq VAR_MAGM_DANCE_AREA_STATE, 1, MAGM_DanceRoom_EventScript_SecondTimeMonsAskForHelp
	bufferspeciesname 0, SPECIES_GLOOM
	goto_if_set FLAG_DANCED_WITH_GLOOM, MAGM_DanceRoom_EventScript_Gloom_SkipToTeachMove
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_DanceWithGloom
	release
	end

MAGM_DanceRoom_EventScript_Gloom_SkipToTeachMove::
	msgbox MAGM_DanceRoom_Text_ShortTeachMonADance, MSGBOX_DEFAULT
	waitmessage
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_CheckSunnyDay
	end

MAGM_DanceRoom_EventScript_DanceWithGloom::
	setflag FLAG_DANCED_WITH_GLOOM
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDance0
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_GloomDance
	waitmovement 0
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_MonIsDancingWithYou, MSGBOX_DEFAULT
	waitmessage
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckSunnyDay::
	compare VAR_GLOOM_MOVE1, 241
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckAfterYou
	compare VAR_GLOOM_MOVE2, 241
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckAfterYou
	compare VAR_GLOOM_MOVE3, 241
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckAfterYou
	compare VAR_GLOOM_MOVE4, 241
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckAfterYou
	dynmultipush MAGM_DanceRoom_Text_SunnyDayDance, 0
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckAfterYou::
	compare VAR_GLOOM_MOVE1, 495
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckPetalDance
	compare VAR_GLOOM_MOVE2, 495
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckPetalDance
	compare VAR_GLOOM_MOVE3, 495
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckPetalDance
	compare VAR_GLOOM_MOVE4, 495
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckPetalDance
	dynmultipush MAGM_DanceRoom_Text_AfterYouDance, 1
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckPetalDance::
	compare VAR_GLOOM_MOVE1, 80
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckMimic
	compare VAR_GLOOM_MOVE2, 80
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckMimic
	compare VAR_GLOOM_MOVE3, 80
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckMimic
	compare VAR_GLOOM_MOVE4, 80
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckMimic
	dynmultipush MAGM_DanceRoom_Text_PetalDanceDance, 2
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckMimic::
	compare VAR_GLOOM_MOVE1, 102
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCharm
	compare VAR_GLOOM_MOVE2, 102
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCharm
	compare VAR_GLOOM_MOVE3, 102
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCharm
	compare VAR_GLOOM_MOVE4, 102
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCharm
	dynmultipush MAGM_DanceRoom_Text_MimicDance, 3
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCharm::
	compare VAR_GLOOM_MOVE1, 204
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckTeeterDance
	compare VAR_GLOOM_MOVE2, 204
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckTeeterDance
	compare VAR_GLOOM_MOVE3, 204
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckTeeterDance
	compare VAR_GLOOM_MOVE4, 204
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckTeeterDance
	dynmultipush MAGM_DanceRoom_Text_CharmDance, 4
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckTeeterDance::
	compare VAR_GLOOM_MOVE1, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCheckMoves
	compare VAR_GLOOM_MOVE2, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCheckMoves
	compare VAR_GLOOM_MOVE3, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCheckMoves
	compare VAR_GLOOM_MOVE4, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCheckMoves
	dynmultipush MAGM_DanceRoom_Text_TeeterDanceDance, 5
MAGM_DanceRoom_EventScript_DanceWithGloom_CheckCheckMoves::
	compare VAR_GLOOM_MOVE1, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_CreateMultichoiceList
	dynmultipush MAGM_DanceRoom_Text_CheckMoves, 6
MAGM_DanceRoom_EventScript_DanceWithGloom_CreateMultichoiceList::
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachSunnyDay
	case 1, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachAfterYou
	case 2, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachPetalDance
	case 3, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMimic
	case 4, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachCharm
	case 5, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachTeeterDance
	case 6, MAGM_DanceRoom_EventScript_DanceWithGloom_ShowMoves
	case MULTI_B_PRESSED MAGM_DanceRoom_EventScript_DanceWithGloom_End
MAGM_DanceRoom_EventScript_DanceWithGloom_End::
	closemessage
	release
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_ShowMoves::
	bufferspeciesname STR_VAR_1, SPECIES_GLOOM
	msgbox MAGM_DanceRoom_Text_MonHasMoves, MSGBOX_DEFAULT
	waitmessage
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_GLOOM_MOVE1
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move1
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
	waitmessage
	compare VAR_GLOOM_MOVE2, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_ShowMoves_End
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_GLOOM_MOVE2
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move2
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
	waitmessage
	compare VAR_GLOOM_MOVE3, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_ShowMoves_End
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_GLOOM_MOVE3
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move3
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
	waitmessage
	compare VAR_GLOOM_MOVE4, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithGloom_ShowMoves_End
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_GLOOM_MOVE4
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move4
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
MAGM_DanceRoom_EventScript_DanceWithGloom_ShowMoves_End::
	closemessage
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachSunnyDay::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepDown
	setvar VAR_TEMP_A, 241
	msgbox MAGM_DanceRoom_Text_SunnyDayFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachAfterYou::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepSides
	setvar VAR_TEMP_A, 495
	msgbox MAGM_DanceRoom_Text_AfterYouFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachPetalDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerSpin
	setvar VAR_TEMP_A, 80
	msgbox MAGM_DanceRoom_Text_PetalDanceFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMimic::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepDown
	setvar VAR_TEMP_A, 102
	msgbox MAGM_DanceRoom_Text_MimicFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachCharm::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepSides
	setvar VAR_TEMP_A, 204
	msgbox MAGM_DanceRoom_Text_CharmFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachTeeterDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerSpin
	setvar VAR_TEMP_A, 298
	msgbox MAGM_DanceRoom_Text_TeeterDanceFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove::
	setvar VAR_0x8004, PARTYID_GLOOM
	copyvar VAR_0x8005, VAR_TEMP_A
	special TeachPartyMonMove
	switch VAR_RESULT
	case 0, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonAlreadyKnowsMove
	case 1, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_SetVars
	case 2, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonNeedsToReplaceMove
	releaseall
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_SetVars::
	compare VAR_GLOOM_MOVE1, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_Move2
	copyvar VAR_GLOOM_MOVE1, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_Move2::
	compare VAR_GLOOM_MOVE2, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_Move3
	copyvar VAR_GLOOM_MOVE2, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_Move3::
	compare VAR_GLOOM_MOVE3, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_Move4
	copyvar VAR_GLOOM_MOVE3, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_Move4::
	compare VAR_GLOOM_MOVE4, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonHasFourMoves
	copyvar VAR_GLOOM_MOVE4, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonLearnedMove
//Should never occur
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonHasFourMoves::
	copyvar VAR_0x8001, VAR_GLOOM_MOVE1
	copyvar VAR_GLOOM_MOVE1, VAR_GLOOM_MOVE2
	copyvar VAR_GLOOM_MOVE2, VAR_GLOOM_MOVE3
	copyvar VAR_GLOOM_MOVE3, VAR_GLOOM_MOVE4
	copyvar VAR_GLOOM_MOVE4, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonReplacedMove
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonAlreadyKnowsMove::
	bufferspeciesname 0, SPECIES_GLOOM
	buffermovename 1, VAR_TEMP_A
	msgbox MAGM_DanceRoom_Text_MonAlreadyKnowsMove, MSGBOX_DEFAULT
	waitse
	closemessage
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonLearnedMove::
	bufferspeciesname 0, SPECIES_GLOOM
	buffermovename 1, VAR_TEMP_A
	playse MUS_LEVEL_UP
	msgbox MAGM_DanceRoom_Text_MonLearnedMove, MSGBOX_DEFAULT
	waitse
	closemessage
	goto MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene
	end

MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonNeedsToReplaceMove::
	setvar VAR_0x8004, PARTYID_GLOOM
	copyvar VAR_0x8005, VAR_TEMP_A
	bufferspeciesname 0, SPECIES_GLOOM
	buffermovename 1, VAR_TEMP_A
	msgbox MAGM_DanceRoom_Text_AskLearnNewMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonNeedsToReplaceMove_End
	special PartyMonForgetMove
	waitstate
	switch VAR_RESULT
	case 0, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove1
	case 1, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove2
	case 2, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove3
	case 3, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove4
	case 4, MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonNeedsToReplaceMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove1::
	buffermovename 2, VAR_GLOOM_MOVE1
	copyvar VAR_GLOOM_MOVE1, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonReplacedMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove2::
	buffermovename 2, VAR_GLOOM_MOVE2
	copyvar VAR_GLOOM_MOVE2, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonReplacedMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove3::
	buffermovename 2, VAR_GLOOM_MOVE3
	copyvar VAR_GLOOM_MOVE3, VAR_TEMP_A
	goto MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonReplacedMove
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_ReplaceMove4::
	buffermovename 2, VAR_GLOOM_MOVE4
	copyvar VAR_GLOOM_MOVE4, VAR_TEMP_A
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonReplacedMove::
	bufferspeciesname 0, SPECIES_GLOOM
	buffermovename 1, VAR_TEMP_A
	playse MUS_LEVEL_UP
	msgbox MAGM_DanceRoom_Text_MonReplacedMove, MSGBOX_DEFAULT
	waitse
MAGM_DanceRoom_EventScript_DanceWithGloom_TeachMove_MonNeedsToReplaceMove_End::
	closemessage
	releaseall
	end

MAGM_DanceRoom_EventScript_Lombre::
	checkitem ITEM_SITRUS_BERRY, 1
	call_if_eq VAR_RESULT, TRUE, EventScript_GiveLombreSitrusBerry
	call_if_eq VAR_MAGM_DANCE_AREA_STATE, 1, MAGM_DanceRoom_EventScript_SecondTimeMonsAskForHelp
	bufferspeciesname 0, SPECIES_LOMBRE
	goto_if_set FLAG_DANCED_WITH_LOMBRE, MAGM_DanceRoom_EventScript_Lombre_SkipToTeachMove
	playmoncry SPECIES_LOMBRE, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_DanceWithLombre
	release
	end

MAGM_DanceRoom_EventScript_Lombre_SkipToTeachMove::
	msgbox MAGM_DanceRoom_Text_ShortTeachMonADance, MSGBOX_DEFAULT
	waitmessage
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_CheckRainDance
	end

MAGM_DanceRoom_EventScript_DanceWithLombre::
	setflag FLAG_DANCED_WITH_LOMBRE
	getplayerxy VAR_TEMP_2, VAR_TEMP_3
	//Forcing the player to walk down if in the way
	goto_if_ne VAR_TEMP_2, 10, MAGM_DanceRoom_EventScript_DanceWithLombre_Normal_Dance
	goto_if_ne VAR_TEMP_3, 14, MAGM_DanceRoom_EventScript_DanceWithLombre_Normal_Dance
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_WalkDown
	waitmovement 0
MAGM_DanceRoom_EventScript_DanceWithLombre_Normal_Dance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDance1
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_LombreDance
	waitmovement 0
	playmoncry SPECIES_LOMBRE, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_MonIsDancingWithYou, MSGBOX_DEFAULT
	waitmessage
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckRainDance::
	compare VAR_LOMBRE_MOVE1, 240
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckWeatherBall
	compare VAR_LOMBRE_MOVE2, 240
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckWeatherBall
	compare VAR_LOMBRE_MOVE3, 240
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckWeatherBall
	compare VAR_LOMBRE_MOVE4, 240
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckWeatherBall
	dynmultipush MAGM_DanceRoom_Text_RainDanceDance, 0
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckWeatherBall::
	compare VAR_LOMBRE_MOVE1, 311
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckFakeOut
	compare VAR_LOMBRE_MOVE2, 311
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckFakeOut
	compare VAR_LOMBRE_MOVE3, 311
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckFakeOut
	compare VAR_LOMBRE_MOVE4, 311
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckFakeOut
	dynmultipush MAGM_DanceRoom_Text_WeatherBallDance, 1
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckFakeOut::
	compare VAR_LOMBRE_MOVE1, 252
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckGrassyGlide
	compare VAR_LOMBRE_MOVE2, 252
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckGrassyGlide
	compare VAR_LOMBRE_MOVE3, 252
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckGrassyGlide
	compare VAR_LOMBRE_MOVE4, 252
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckGrassyGlide
	dynmultipush MAGM_DanceRoom_Text_FakeOutDance, 2
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckGrassyGlide::
	compare VAR_LOMBRE_MOVE1, 731
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckSwordsDance
	compare VAR_LOMBRE_MOVE2, 731
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckSwordsDance
	compare VAR_LOMBRE_MOVE3, 731
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckSwordsDance
	compare VAR_LOMBRE_MOVE4, 731
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckSwordsDance
	dynmultipush MAGM_DanceRoom_Text_GrassyGlideDance, 3
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckSwordsDance::
	compare VAR_LOMBRE_MOVE1, 14
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckTeeterDance
	compare VAR_LOMBRE_MOVE2, 14
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckTeeterDance
	compare VAR_LOMBRE_MOVE3, 14
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckTeeterDance
	compare VAR_LOMBRE_MOVE4, 14
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckTeeterDance
	dynmultipush MAGM_DanceRoom_Text_SwordsDanceDance, 4
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckTeeterDance::
	compare VAR_LOMBRE_MOVE1, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckCheckMoves
	compare VAR_LOMBRE_MOVE2, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckCheckMoves
	compare VAR_LOMBRE_MOVE3, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckCheckMoves
	compare VAR_LOMBRE_MOVE4, 298
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CheckCheckMoves
	dynmultipush MAGM_DanceRoom_Text_TeeterDanceDance, 5
MAGM_DanceRoom_EventScript_DanceWithLombre_CheckCheckMoves::
	compare VAR_LOMBRE_MOVE1, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_CreateMultichoiceList
	dynmultipush MAGM_DanceRoom_Text_CheckMoves, 6
MAGM_DanceRoom_EventScript_DanceWithLombre_CreateMultichoiceList::
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, MAGM_DanceRoom_EventScript_DanceWithLombre_TeachRainDance
	case 1, MAGM_DanceRoom_EventScript_DanceWithLombre_TeachWeatherBall
	case 2, MAGM_DanceRoom_EventScript_DanceWithLombre_TeachFakeOut
	case 3, MAGM_DanceRoom_EventScript_DanceWithLombre_TeachGrassyGlide
	case 4, MAGM_DanceRoom_EventScript_DanceWithLombre_TeachSwordsDance
	case 5, MAGM_DanceRoom_EventScript_DanceWithLombre_TeachTeeterDance
	case 6, MAGM_DanceRoom_EventScript_DanceWithLombre_ShowMoves
	case MULTI_B_PRESSED MAGM_DanceRoom_EventScript_DanceWithLombre_End
MAGM_DanceRoom_EventScript_DanceWithLombre_End::
	closemessage
	release
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_ShowMoves::
	bufferspeciesname STR_VAR_1, SPECIES_LOMBRE
	msgbox MAGM_DanceRoom_Text_MonHasMoves, MSGBOX_DEFAULT
	waitmessage
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_LOMBRE_MOVE1
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move1
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
	waitmessage
	compare VAR_LOMBRE_MOVE2, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_ShowMoves_End
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_LOMBRE_MOVE2
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move2
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
	waitmessage
	compare VAR_LOMBRE_MOVE3, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_ShowMoves_End
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_LOMBRE_MOVE3
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move3
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
	waitmessage
	compare VAR_LOMBRE_MOVE4, 0
	goto_if_eq MAGM_DanceRoom_EventScript_DanceWithLombre_ShowMoves_End
	playse SE_SELECT
	buffermovename STR_VAR_2, VAR_LOMBRE_MOVE4
	bufferstring STR_VAR_3, MAGM_DanceRoom_Text_Move4
	msgbox MAGM_DanceRoom_Text_ListMove, MSGBOX_DEFAULT
MAGM_DanceRoom_EventScript_DanceWithLombre_ShowMoves_End::
	closemessage
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachRainDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerSpin
	setvar VAR_0x8000, 240
	msgbox MAGM_DanceRoom_Text_RainDanceFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachWeatherBall::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepSides
	setvar VAR_0x8000, 311
	msgbox MAGM_DanceRoom_Text_WeatherBallFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachFakeOut::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepDown
	setvar VAR_0x8000, 252
	msgbox MAGM_DanceRoom_Text_FakeOutFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachGrassyGlide::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepSides
	setvar VAR_0x8000, 731
	msgbox MAGM_DanceRoom_Text_GrassyGlideFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachSwordsDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerStepDown
	setvar VAR_0x8000, 14
	msgbox MAGM_DanceRoom_Text_SwordsDanceFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachTeeterDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerSpin
	setvar VAR_0x8000, 298
	msgbox MAGM_DanceRoom_Text_TeeterDanceFlavor, MSGBOX_DEFAULT
	waitmovement 0
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove::
	compare VAR_LOMBRE_MOVE1, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_Move2
	copyvar VAR_LOMBRE_MOVE1, VAR_0x8000
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_Move2::
	compare VAR_LOMBRE_MOVE2, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_Move3
	copyvar VAR_LOMBRE_MOVE2, VAR_0x8000
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_Move3::
	compare VAR_LOMBRE_MOVE3, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_Move4
	copyvar VAR_LOMBRE_MOVE3, VAR_0x8000
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_Move4::
	compare VAR_LOMBRE_MOVE4, 0
	goto_if_ne MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonHasFourMoves
	copyvar VAR_LOMBRE_MOVE4, VAR_0x8000
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonLearnedMove
MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonHasFourMoves::
	copyvar VAR_0x8001, VAR_LOMBRE_MOVE1
	copyvar VAR_LOMBRE_MOVE1, VAR_LOMBRE_MOVE2
	copyvar VAR_LOMBRE_MOVE2, VAR_LOMBRE_MOVE3
	copyvar VAR_LOMBRE_MOVE3, VAR_LOMBRE_MOVE4
	copyvar VAR_LOMBRE_MOVE4, VAR_0x8000
	goto MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonReplacedMove
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonReplacedMove::
	bufferspeciesname 0, SPECIES_LOMBRE
	buffermovename 1, VAR_0x8000
	buffermovename 2, VAR_0x8001
	playse MUS_LEVEL_UP
	msgbox MAGM_DanceRoom_Text_MonReplacedMove, MSGBOX_DEFAULT
	waitse
	closemessage
	goto MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene
	end

MAGM_DanceRoom_EventScript_DanceWithLombre_TeachMove_MonLearnedMove::
	bufferspeciesname 0, SPECIES_LOMBRE
	buffermovename 1, VAR_0x8000
	playse MUS_LEVEL_UP
	msgbox MAGM_DanceRoom_Text_MonLearnedMove, MSGBOX_DEFAULT
	waitse
	closemessage
	goto MAGM_DanceRoom_EventScript_StartDanceChallengeCutscene
	end


MAGM_DanceRoom_EventScript_PlayerDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDanceShort
	waitmovement 0
	release
	end

MAGM_DanceRoom_Text_MonNoticedBerry:
	.string "{STR_VAR_1} noticed you have\n"
	.string "a sitrus berry.\p"
	.string "{PLAY_SE MUS_LEVEL_UP}You gave the berry\n"
	.string "to {STR_VAR_1}.$"

MAGM_DanceRoom_Text_MonWantsToGiveYou:
	.string "Looks like {STR_VAR_1} wants\n"
	.string "to give you something.$"

MAGM_DanceRoom_Text_LudicoloHappy:
	.string "Ludicolo looks really happy!\n"
	.string "Dance with him?$"

MAGM_DanceRoom_Text_BellossomHappy:
	.string "Bellossom looks really happy!\n"
	.string "Dance with her?$"

MAGM_DanceRoom_Text_ThisIsADanceBattle:
	.string "Is this a dance battle?$"

MAGM_DanceRoom_Text_HelpThemDance:
	.string "Looks like they want your\n"
	.string "help.\p"
	.string "Lead the dance battle?$"

MAGM_DanceRoom_Text_TheyWillWait:
	.string "Seems like they'll wait for\n"
	.string "you.$"

MAGM_DanceRoom_Text_MonHasMoves:
	.string "{STR_VAR_1} has the following\n"
	.string "moves:$"

MAGM_DanceRoom_Text_ListMove:
	.string "{STR_VAR_3} {STR_VAR_2}$"

MAGM_DanceRoom_Text_Move1:
	.string "1: $"

MAGM_DanceRoom_Text_Move2:
	.string "2: $"

MAGM_DanceRoom_Text_Move3:
	.string "3: $"

MAGM_DanceRoom_Text_Move4:
	.string "4: $"

MAGM_DanceRoom_Text_WeatherBallFlavor:
	.string "You move freely, changing\n"
	.string "steps like changing weather.$"

MAGM_DanceRoom_Text_WeatherBallDance:
	.string "Improvise$"

MAGM_DanceRoom_Text_RainDanceFlavor:
	.string "Your steps fall like\n"
	.string "raindrops.$"

MAGM_DanceRoom_Text_RainDanceDance:
	.string "Stormy$"

MAGM_DanceRoom_Text_FakeOutFlavor:
	.string "You bust a quick set of moves.$"

MAGM_DanceRoom_Text_FakeOutDance:
	.string "Breakdance$"

MAGM_DanceRoom_Text_GrassyGlideFlavor:
	.string "You slide your feet like\n"
	.string "there's no friction.$"

MAGM_DanceRoom_Text_GrassyGlideDance:
	.string "Smooth$"

MAGM_DanceRoom_Text_SwordsDanceFlavor:
	.string "You slash and thrust with an\n"
	.string "imaginary blade.$"

MAGM_DanceRoom_Text_SwordsDanceDance:
	.string "Frenzied$"

MAGM_DanceRoom_Text_TeeterDanceFlavor:
	.string "You spin and wave your hands with\n"
	.string "little rhyme or reason.$"

MAGM_DanceRoom_Text_CheckMoves:
	.string "Check Moves$"

MAGM_DanceRoom_Text_TeeterDanceDance:
	.string "Silly$"

MAGM_DanceRoom_Text_SunnyDayFlavor:
	.string "You raise your arms\n"
	.string "and praise the sun.$"

MAGM_DanceRoom_Text_SunnyDayDance:
	.string "Radiant$"

MAGM_DanceRoom_Text_AfterYouFlavor:
	.string "You lead Gloom in a\n"
	.string "classic box step.$"

MAGM_DanceRoom_Text_AfterYouDance:
	.string "Ballroom$"

MAGM_DanceRoom_Text_PetalDanceFlavor:
	.string "You twirl with the grace\n"
	.string "of falling petals.$"

MAGM_DanceRoom_Text_PetalDanceDance:
	.string "Flowery$"

MAGM_DanceRoom_Text_MimicFlavor:
	.string "You do the Macarena!$"

MAGM_DanceRoom_Text_MimicDance:
	.string "Simple$"

MAGM_DanceRoom_Text_CharmFlavor:
	.string "You release your inner\n"
	.string "flamenco.$"

MAGM_DanceRoom_Text_CharmDance:
	.string "Tango$"

MAGM_DanceRoom_Text_MonIsDancingWithYou:
	.string "{STR_VAR_1} is dancing with you!\n"
	.string "Teach it a dance?$"

MAGM_DanceRoom_Text_ShortTeachMonADance:
	.string "Teach {STR_VAR_1} a dance?$"

MAGM_DanceRoom_Text_MonIsDancing:
	.string "{STR_VAR_1} is dancing!\n"
	.string "Dance with it?$"

MAGM_DanceRoom_Text_MonAlreadyKnowsMove:
	.string "{STR_VAR_1} already knows {STR_VAR_2}.$"	

MAGM_DanceRoom_Text_MonLearnedMove:
	.string "{STR_VAR_1} learned {STR_VAR_2}!$"

MAGM_DanceRoom_Text_MonReplacedMove:
	.string "{STR_VAR_1} forgot {STR_VAR_3} and\n"
	.string "learned {STR_VAR_2}!$"

MAGM_DanceRoom_Text_AskLearnNewMove:
	.string "{STR_VAR_1} wants to learn {STR_VAR_2},\n"
	.string "But it already knows four moves.\p"
	.string "Replace a move?$"

MAGM_DanceRoom_Movement_WalkDown:
	walk_down
	step_end

MAGM_DanceRoom_Movement_WalkRightUpAlt:
	walk_right
	walk_up
	walk_up
	step_end

MAGM_DanceRoom_Movement_WalkRightUpNormal:
	walk_up
	walk_up
	walk_right
	step_end

MAGM_DanceRoom_Movement_WalkRight:
	walk_right
	step_end

MAGM_DanceRoom_Movement_PlayerSpin:
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_PlayerStepSides:
	walk_in_place_left
	walk_in_place_left
	walk_in_place_right
	walk_in_place_right
	walk_in_place_down
	step_end

MAGM_DanceRoom_Movement_PlayerStepDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

MAGM_DanceRoom_Movement_PlayerDanceShort:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_PlayerDance0:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_PlayerDance1:
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_GloomDance:
	face_player
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	face_player
	step_end

MAGM_DanceRoom_Movement_GloomDanceShort:
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	face_player
	step_end

MAGM_DanceRoom_Movement_LombreDance:
	face_player
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	step_end


MAGM_DanceRoom_Movement_LombreDanceShort:
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_GloomWalkToLadder:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_left
	face_up
	step_end

MAGM_DanceRoom_Movement_LombreWalkToLadder:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	face_up
	step_end

MAGM_DanceRoom_Movement_OricorioGiveStones:
	jump_in_place_left_right
	face_down
	delay_16
	walk_down
	delay_16
	walk_in_place_slow_down
	walk_right
	walk_right
	delay_16
	walk_in_place_slow_down
	walk_left
	walk_left
	walk_up
	face_down
	step_end

MAGM_DanceRoom_Movement_EvolutionSpin:
	delay_16
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_fast_down
	walk_in_place_faster_left
	walk_in_place_faster_up
	walk_in_place_faster_right
	walk_in_place_faster_down
	walk_in_place_faster_left
	walk_in_place_faster_up
	walk_in_place_faster_right
	walk_in_place_faster_down
	walk_in_place_faster_left
	walk_in_place_faster_up
	walk_in_place_faster_right
	walk_in_place_faster_down
	walk_in_place_faster_left
	walk_in_place_faster_up
	walk_in_place_faster_right
	walk_in_place_faster_down
	walk_in_place_faster_left
	walk_in_place_faster_up
	walk_in_place_faster_right
	walk_in_place_faster_down
	step_end
