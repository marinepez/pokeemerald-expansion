.set LOCALID_HAWLUCHA, 1
.set LOCALID_SMEARGLE, 2
.set LOCALID_PIKACHU, 3

MAGM_HawluchaCave_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MAGM_HawluchaCave_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_HawluchaCave_OnTransition
	.byte 0

MAGM_HawluchaCave_OnFrame::
	map_script_2 VAR_HAWLUCHA_CAVE_STATE, 0, MAGM_HawluchaCave_EventScript_IntroCutscene
	.2byte 0

MAGM_HawluchaCave_OnTransition:
	setflag FLAG_HIDE_MAP_NAME_POPUP
	clearflag FLAG_SYS_SAFARI_MODE
	end

//Pikachu is the competitor in CAVE_STATE 4

MAGM_HawluchaCave_EventScript_IntroCutscene::
	setvar VAR_HAWLUCHA_CAVE_STATE, 1
	applymovement LOCALID_HAWLUCHA, Common_Movement_Delay48
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_HAWLUCHA, MAGM_HawluchaCave_Movement_HawluchaNoticeSmeargle
	waitmovement 0
	applymovement LOCALID_SMEARGLE, MAGM_HawluchaCave_Movement_SmeargleApproachHawlucha
	waitmovement 0
	playmoncry SPECIES_SMEARGLE, CRY_MODE_NORMAL
	waitmoncry
	delay 60
	playmoncry SPECIES_HAWLUCHA, CRY_MODE_ENCOUNTER
	applymovement LOCALID_HAWLUCHA, MAGM_HawluchaCave_Movement_HawluchaAngry
	waitmoncry
	waitmovement 0
	applymovement LOCALID_SMEARGLE, MAGM_HawluchaCave_Movement_SmeargleWalkBackToPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_HawluchaCave_Movement_PlayerMoveOutOfWay
	waitmovement 0
	applymovement LOCALID_SMEARGLE, MAGM_HawluchaCave_Movement_SmeargleExit
	waitmovement 0
	removeobject LOCALID_SMEARGLE, MAP_MAGM_HAWLUCHA_CAVE
	end

MAGM_HawluchaCave_EventScript_GameCube::
	goto_if_eq VAR_HAWLUCHA_CAVE_STATE, 2, MAGM_HawluchaCave_EventScript_GameCube_LookAtGameCube
	goto_if_set FLAG_INSERTED_GAME, MAGM_HawluchaCave_EventScript_GameCube_PlayGame
	checkitem ITEM_VIDEO_GAME
	goto_if_eq VAR_RESULT, TRUE, MAGM_HawluchaCave_EventScript_GameCube_InsertGame
MAGM_HawluchaCave_EventScript_GameCube_LookAtGameCube::
	msgbox MAGM_HawluchaCave_Text_GameCube, MSGBOX_DEFAULT
	closemessage
	end

MAGM_HawluchaCave_EventScript_GameCube_InsertGame::
	removeitem ITEM_VIDEO_GAME, 1
	setflag FLAG_INSERTED_GAME
	msgbox MAGM_HawluchaCave_Text_InsertedGame, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_HAWLUCHA, MAGM_HawluchaCave_Movement_NoticeGameInserted
	waitmovement 0
	msgbox MAGM_HawluchaCave_Text_HawluchaPickedUpController, MSGBOX_DEFAULT
MAGM_HawluchaCave_EventScript_GameCube_PlayGame::
	special ZeroPlayerPartyMons
	call_if_ne VAR_HAWLUCHA_CAVE_STATE, 4, MAGM_HawluchaCave_EventScript_BufferHawluchaName
	call_if_eq VAR_HAWLUCHA_CAVE_STATE, 4, MAGM_HawluchaCave_EventScript_BufferPikachuName
	random 7
	copyvar VAR_OPPONENT_FIGHTER_CHOICE, VAR_RESULT
	switch VAR_OPPONENT_FIGHTER_CHOICE
	case 0, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseSamus
	case 1, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseGameNWatch
	case 2, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseFalco
	case 3, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseIceClimbers
	case 4, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseJigglypuff
	case 5, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChosePikachu
	case 6, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseRandom
MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter::
	msgbox MAGM_HawluchaCave_Text_OpponentChoseCharacter, MSGBOX_DEFAULT
	waitmessage
	dynmultipush MAGM_DanceRoom_Text_Samus, 0
	dynmultipush MAGM_DanceRoom_Text_GameNWatch, 1
	dynmultipush MAGM_DanceRoom_Text_Falco, 2
	dynmultipush MAGM_DanceRoom_Text_IceClimbers, 3
	dynmultipush MAGM_DanceRoom_Text_Jigglypuff, 4
	goto_if_ne VAR_HAWLUCHA_CAVE_STATE, 4, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_AddRandomOption
	dynmultipush MAGM_DanceRoom_Text_Pikachu, 5
MAGM_HawluchaCave_EventScript_GameCube_PlayGame_AddRandomOption::
	dynmultipush MAGM_DanceRoom_Text_Random, 6
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, HawluchaCave_EventScript_GameCube_GiveSamus
	case 1, HawluchaCave_EventScript_GameCube_GiveGameNWatch
	case 2, HawluchaCave_EventScript_GameCube_GiveFalco
	case 3, HawluchaCave_EventScript_GameCube_GiveIceClimbers
	case 4, HawluchaCave_EventScript_GameCube_GiveJigglypuff
	case 5, HawluchaCave_EventScript_GameCube_GivePikachu
	case 6, HawluchaCave_EventScript_GameCube_GiveRandom
	case MULTI_B_PRESSED MAGM_HawluchaCave_EventScript_GameCube_PlayGame_End
MAGM_HawluchaCave_EventScript_GameCube_PlayGame_End::
	closemessage
	release
	end

HawluchaCave_EventScript_GameCube_StartGame::
	addvar VAR_SMASH_BROS_GAMES, 1
	goto_if_eq VAR_HAWLUCHA_CAVE_STATE, 4, HawluchaCave_EventScript_GameCube_StartGame_Pikachu
	switch VAR_OPPONENT_FIGHTER_CHOICE
	case 0, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Samus
	case 1, HawluchaCave_EventScript_GameCube_StartGame_Opponent_GameWatch
	case 2, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Falco
	case 3, HawluchaCave_EventScript_GameCube_StartGame_Opponent_IceClimbers
	case 4, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Jigglypuff
	case 5, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Pikachu
HawluchaCave_EventScript_GameCube_StartGame_Pikachu::
	switch VAR_OPPONENT_FIGHTER_CHOICE
	case 0, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Samus_Pikachu
	case 1, HawluchaCave_EventScript_GameCube_StartGame_Opponent_GameWatch_Pikachu
	case 2, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Falco_Pikachu
	case 3, HawluchaCave_EventScript_GameCube_StartGame_Opponent_IceClimbers_Pikachu
	case 4, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Jigglypuff_Pikachu
	case 5, HawluchaCave_EventScript_GameCube_StartGame_Opponent_Pikachu_Pikachu
	end

HawluchaCave_EventScript_GameCube_AfterBattle::
	special ZeroPlayerPartyMons
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HawluchaCave_EventScript_GameCube_WonBattle
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame
	end

HawluchaCave_EventScript_GameCube_WonBattle::
	addvar VAR_SMASH_BROS_WINS, 1
	goto_if_lt VAR_SMASH_BROS_WINS, 3, MAGM_HawluchaCave_EventScript_GameCube_PlayGame
	goto_if_eq VAR_HAWLUCHA_CAVE_STATE, 4, HawluchaCave_EventScript_GameCube_WonBattle_End
	setvar VAR_HAWLUCHA_CAVE_STATE, 2
	setvar VAR_WRESTLING_AREA_STATE, 2
	setflag FLAG_HIDE_HERACROSS
	clearflag FLAG_HIDE_HAWLUCHA_WRESTLING
	clearflag FLAG_HIDE_SMEARGLE_WRESTLING
	delay 30
	playmoncry SPECIES_HAWLUCHA, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_HAWLUCHA, MAGM_HawluchaCave_Movement_BreakTV
	waitmovement 0
	playse SE_BREAKABLE_DOOR
	setmetatile 3, 1, METATILE_Building_TV_Off, TRUE
	special DrawWholeMapView
	applymovement LOCALID_HAWLUCHA, MAGM_HawluchaCave_Movement_HawluchaLeave
	waitmovement 0
	removeobject LOCALID_HAWLUCHA
	end

HawluchaCave_EventScript_GameCube_WonBattle_End::
	releaseall
	end

HawluchaCave_EventScript_GameCube_StartGame_Opponent_Samus::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_SAMUS, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_GameWatch::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_GAMEWATCH, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Falco::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_FALCO, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_IceClimbers::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_ICECLIMBERS, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Jigglypuff::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_JIGGLYPUFF, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Samus_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_SAMUS_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_GameWatch_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_GAMEWATCH_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Falco_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_FALCO_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_IceClimbers_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_ICECLIMBERS_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Jigglypuff_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_JIGGLYPUFF_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end
HawluchaCave_EventScript_GameCube_StartGame_Opponent_Pikachu_Pikachu::
	trainerbattle_no_whiteout_continue_script TRAINER_SMASHBROS_PIKACHU_PIKACHU, HawluchaCave_EventScript_GameCube_HawluchaIntroText, HawluchaCave_EventScript_GameCube_HawluchaLoseText, HawluchaCave_EventScript_GameCube_AfterBattle
	end

HawluchaCave_EventScript_GameCube_GiveSamus::
	givecustommon SPECIES_SAMUS, 50, ITEM_NONE, ITEM_GREAT_BALL, NATURE_QUIET, 0, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 31, MOVE_ZAP_CANNON, MOVE_GYRO_BALL, MOVE_FLASH_CANNON, MOVE_RAPID_SPIN, FALSE
	goto HawluchaCave_EventScript_GameCube_StartGame
	end

HawluchaCave_EventScript_GameCube_GiveGameNWatch::
	givecustommon SPECIES_GAMEWATCH, 50, ITEM_NONE, ITEM_GREAT_BALL, NATURE_HASTY, 0, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 31, MOVE_MAGNITUDE, MOVE_ORDER_UP, MOVE_OCTAZOOKA, MOVE_HEAL_BELL, FALSE
	goto HawluchaCave_EventScript_GameCube_StartGame
	end

HawluchaCave_EventScript_GameCube_GiveFalco::
	givecustommon SPECIES_FALCO, 50, ITEM_NONE, ITEM_GREAT_BALL, NATURE_ADAMANT, 0, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 31, MOVE_JUMP_KICK, MOVE_FLAME_CHARGE, MOVE_AERIAL_ACE, MOVE_MIRROR_COAT, FALSE
	goto HawluchaCave_EventScript_GameCube_StartGame
	end

HawluchaCave_EventScript_GameCube_GiveIceClimbers::
	givecustommon SPECIES_ICLIMBERS, 50, ITEM_NONE, ITEM_GREAT_BALL, NATURE_IMPISH, 0, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 31, MOVE_ICICLE_SPEAR, MOVE_FROST_BREATH, MOVE_BOUNCE, MOVE_DOUBLE_HIT, FALSE
	goto HawluchaCave_EventScript_GameCube_StartGame
	end

HawluchaCave_EventScript_GameCube_GiveJigglypuff::
	givecustommon SPECIES_JIGGLYPUFF, 50, ITEM_NONE, ITEM_GREAT_BALL, NATURE_CAREFUL, 0, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 31, MOVE_REST, MOVE_ROLLOUT, MOVE_SING, MOVE_POUND, FALSE
	goto HawluchaCave_EventScript_GameCube_StartGame
	end

HawluchaCave_EventScript_GameCube_GivePikachu::
	//Reroll random if Pikachu isn't available
	goto_if_ne VAR_HAWLUCHA_CAVE_STATE, 4, HawluchaCave_EventScript_GameCube_GiveRandom
	givecustommon SPECIES_PIKACHU_LIBRE, 50, ITEM_NONE, ITEM_GREAT_BALL, NATURE_HARDY, 0, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 31, MOVE_QUICK_ATTACK, MOVE_THUNDER, MOVE_SKULL_BASH, MOVE_FLYING_PRESS, FALSE
	goto HawluchaCave_EventScript_GameCube_StartGame
	end

HawluchaCave_EventScript_GameCube_GiveRandom::
	random 6
	switch VAR_RESULT
	case 0, HawluchaCave_EventScript_GameCube_GiveSamus
	case 1, HawluchaCave_EventScript_GameCube_GiveGameNWatch
	case 2, HawluchaCave_EventScript_GameCube_GiveFalco
	case 3, HawluchaCave_EventScript_GameCube_GiveIceClimbers
	case 4, HawluchaCave_EventScript_GameCube_GiveJigglypuff
	case 5, HawluchaCave_EventScript_GameCube_GivePikachu
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseSamus::
	bufferspeciesname STR_VAR_2, SPECIES_SAMUS
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseGameNWatch::
	bufferspeciesname STR_VAR_2, SPECIES_GAMEWATCH
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseFalco::
	bufferspeciesname STR_VAR_2, SPECIES_FALCO
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseIceClimbers::
	bufferspeciesname STR_VAR_2, SPECIES_ICLIMBERS
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseJigglypuff::
	bufferspeciesname STR_VAR_2, SPECIES_JIGGLYPUFF
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChosePikachu::
	bufferspeciesname STR_VAR_2, SPECIES_PIKACHU
	goto_if_eq VAR_HAWLUCHA_CAVE_STATE, 4, MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	setvar VAR_OPPONENT_FIGHTER_CHOICE, 2 //Do Falco instead
	bufferspeciesname STR_VAR_2, SPECIES_FALCO
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_GameCube_PlayGame_OpponentChoseRandom::
	random 4 //Choose a different mon
	copyvar VAR_OPPONENT_FIGHTER_CHOICE, VAR_RESULT
	bufferstring STR_VAR_2, MAGM_HawluchaCave_Text_LowercaseRandom
	goto MAGM_HawluchaCave_EventScript_GameCube_PlayGame_ChooseCharacter
	end

MAGM_HawluchaCave_EventScript_BufferHawluchaName::
	bufferspeciesname STR_VAR_1, SPECIES_HAWLUCHA
	return

MAGM_HawluchaCave_EventScript_BufferPikachuName::
	bufferspeciesname STR_VAR_1, SPECIES_PIKACHU
	return

MAGM_HawluchaCave_EventScript_ComicBook::
	msgbox MAGM_HawluchaCave_Text_ComicBook, MSGBOX_SIGN
	end

MAGM_HawluchaCave_EventScript_Hawlucha::
	goto_if_set FLAG_INSERTED_GAME, MAGM_HawluchaCave_EventScript_Hawchula_WaitingForYou
	msgbox MAGM_HawluchaCave_Text_WatchingTrashTV, MSGBOX_DEFAULT
	closemessage
	end

MAGM_HawluchaCave_EventScript_Hawchula_WaitingForYou::
	msgbox MAGM_HawluchaCave_Text_WaitingForYou, MSGBOX_DEFAULT
	closemessage
	end

MAGM_HawluchaCave_Text_InsertedGame:
	.string "You inserted the disk\n"
	.string "into the GameCube.$"

MAGM_HawluchaCave_Text_HawluchaPickedUpController:
	.string "Hawlucha picked up a\n"
	.string "controller.$"

HawluchaCave_EventScript_GameCube_HawluchaIntroText:
	.string "READY? GO!$"

HawluchaCave_EventScript_GameCube_HawluchaLoseText:
	.string "GAME!$"

MAGM_HawluchaCave_Text_OpponentChoseCharacter:
	.string "{STR_VAR_1} chose {STR_VAR_2}.\n"
	.string "Who will you play as?$"

MAGM_HawluchaCave_Text_GameCube:
	.string "The gamecube is off.\p"
	.string "Where did Hawlucha\n"
	.string "get this?$"

MAGM_HawluchaCave_Text_ComicBook:
	.string "A superhero comic!\n"
	.string "Looks well cared for.$"

MAGM_HawluchaCave_Text_WaitingForYou:
	.string "She's waiting for you\n"
	.string "to choose a character.$"

MAGM_HawluchaCave_Text_WatchingTrashTV:
	.string "She's ignoring you\n"
	.string "and watching trash TV.$"

MAGM_DanceRoom_Text_Samus:
	.string "SAMUS$"

MAGM_DanceRoom_Text_GameNWatch:
	.string "GAME&WATCH$"

MAGM_DanceRoom_Text_Falco:
	.string "FALCO$"

MAGM_DanceRoom_Text_IceClimbers:
	.string "ICE CLIMBERS$"

MAGM_DanceRoom_Text_Jigglypuff:
	.string "JIGGLYPUFF$"

MAGM_DanceRoom_Text_Pikachu:
	.string "PIKACHU$"

MAGM_DanceRoom_Text_Random:
	.string "RANDOM$"

MAGM_HawluchaCave_Text_LowercaseRandom:
	.string "Random$"

MAGM_HawluchaCave_Movement_BreakTV:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_fast_up
	step_end

MAGM_HawluchaCave_Movement_HawluchaLeave:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	delay_16
	delay_16
	delay_16
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_in_place_fast_down
	step_end

MAGM_HawluchaCave_Movement_SmeargleExit:
	walk_slow_right
	walk_in_place_slow_down
	step_end

MAGM_HawluchaCave_Movement_PlayerMoveOutOfWay:
	walk_right
	face_left
	step_end

MAGM_HawluchaCave_Movement_HawluchaAngry:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_up
	step_end

MAGM_HawluchaCave_Movement_HawluchaNoticeSmeargle:
	face_down
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

MAGM_HawluchaCave_Movement_SmeargleWalkBackToPlayer:
	walk_in_place_slow_up
	delay_16
	delay_16
	walk_slow_down
	walk_slow_down
	face_up
	delay_16
	delay_16
	delay_16
	face_right
	step_end

MAGM_HawluchaCave_Movement_SmeargleApproachHawlucha:
	walk_up
	walk_up
	walk_in_place_slow_up
	step_end

MAGM_HawluchaCave_Movement_NoticeGameInserted:
	face_right
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_slow_right
	walk_in_place_slow_up
	delay_16
	delay_16
	delay_16
	step_end
