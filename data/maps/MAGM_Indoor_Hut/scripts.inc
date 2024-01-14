.set LOCALID_MEW, 2
.set LOCALID_MASTERBALL, 3

MAGM_Indoor_Hut_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_Hut_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MAGM_Hut_OnFrame
	.byte 0

MAGM_Hut_OnFrame:
	map_script_2 VAR_MAGM_HUT_STATE, 1, MAGM_Hut_DoMewCutscene
	.2byte 0

MAGM_Hut_OnTransition:
	clearflag FLAG_SYS_SAFARI_MODE
	setflag FLAG_HIDE_MAP_NAME_POPUP
	special ZeroPlayerPartyMons
	checkitem ITEM_RARE_CANDY, 3
	goto_if_eq VAR_RESULT, TRUE, MAGM_Hut_EnableMewCutscene
	end

MAGM_Hut_EnableMewCutscene::
	setvar VAR_MAGM_HUT_STATE, 1
	end

MAGM_Hut_DoMewCutscene::
	setvar VAR_MAGM_HUT_STATE, 2
	playse SE_BALL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox MAGM_Hut_Text_SomethingFeelsDifferent, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Hut_Movement_Walk_In
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	playmoncry SPECIES_MEW, CRY_MODE_NORMAL
	waitmoncry
	addobject LOCALID_MEW, MAP_MAGM_INDOOR_HUT
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_Hut_Movement_WatchMew
	applymovement LOCALID_MEW, MAGM_Hut_Movement_Mew
	waitmovement 0
	msgbox MAGM_IndoorHut_Text_MewIsEatingCandy, MSGBOX_DEFAULT
	removeitem ITEM_RARE_CANDY, 3
	playmoncry SPECIES_MEW, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_MEW, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	applymovement LOCALID_MEW, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox MAGM_IndoorHut_Text_ThisIsIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MAGM_IndoorHut_CatchMew
	msgbox MAGM_IndoorHut_Text_DidNotCatchMew MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_MEW, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_MEW, MAGM_Hut_Movement_MewLeaves
	waitmovement 0
MAGM_IndoorHut_StartCredits::
	fadescreen FADE_TO_BLACK
	delay 60
	msgbox MAGM_IndoorHut_Text_ThankYouForPlaying, MSGBOX_DEFAULT
	closemessage
	givemon SPECIES_BELLOSSOM, 35
	givemon SPECIES_LUDICOLO, 35
	givemon SPECIES_MAROWAK_ALOLAN, 50
	givemon SPECIES_ORICORIO_POM_POM, 50
	givemon SPECIES_HAWLUCHA, 50
	givemon SPECIES_PIKACHU_LIBRE, 50
	givemon SPECIES_MEW, 50
	special StartCredits
	end

MAGM_IndoorHut_CatchMew::
	closemessage
	playse SE_BALL_THROW
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	waitse
	playse SE_BALL_TRADE
	removeobject LOCALID_MEW, MAP_MAGM_INDOOR_HUT
	addobject LOCALID_MASTERBALL, MAP_MAGM_INDOOR_HUT
	waitse
	delay 15
	playse SE_BALL_BOUNCE_1
	waitse	
	delay 10
	playse SE_BALL_BOUNCE_2
	waitse	
	delay 10
	playse SE_BALL_BOUNCE_3
	waitse	
	playse SE_BALL_BOUNCE_4
	waitse	
	delay 50
	playse SE_BALL
	waitse
	delay 50
	playse SE_BALL
	waitse
	delay 50
	playse SE_BALL
	waitse
	delay 65
	playse SE_CLICK
	waitse
	delay 60
	msgbox MAGM_IndoorHut_Text_CaughtMew, MSGBOX_DEFAULT
	closemessage
	goto MAGM_IndoorHut_StartCredits
	end

MAGM_IndoorHut_ItemMachete::
	finditem ITEM_MACHETE
	end

MAGM_IndoorHut_EventScript_Book::
	msgbox MAGM_IndoorHut_Text_Book, MSGBOX_SIGN
	end
	
MAGM_IndoorHut_EventScript_BookShelf::
	msgbox MAGM_IndoorHut_Text_BookShelf, MSGBOX_SIGN
	end

MAGM_IndoorHut_EventScript_Bed::
	msgbox MAGM_IndoorHut_Text_Bed, MSGBOX_SIGN
	end

MAGM_Hut_Text_SomethingFeelsDifferent:
	.string "Something feels different...$"

MAGM_IndoorHut_Text_MewIsEatingCandy:
	.string "Mew is eating the candy\n"
	.string "in your bag!$"

MAGM_IndoorHut_Text_DidNotCatchMew:
	.string "You chose to leave Mew\n"
	.string "alone.$"

MAGM_IndoorHut_Text_CaughtMew:
	.string "You did it.\n"
	.string "You caught Mew.\p"
	.string "It's time to go back\n"
	.string "home, now.$"

MAGM_IndoorHut_Text_ThisIsIt:
	.string "This is it, the chance that\n"
	.string "you were looking for.\p"
	.string "Use the Master Ball?$"

MAGM_IndoorHut_Text_ThankYouForPlaying:
	.string "Hello!\p"
	.string "This is the dev, Pez. Thank you for\n"
	.string "playing my entry to MAGM8.\p"
	.string "The game ends here. Although I cut\n"
	.string "most of the story due to deadlines,\l"
	.string "I'm happy with what I put together.\p"
	.string "I'm open to feedback on the Anthroyd\n"
	.string "discord, and would be happy to add\l"
	.string "more if people enjoyed this.\p"
	.string "I'd also like to give thanks to:\l"
	.string "RHH Hideout: Pkmn Emerald Expansion\l"
	.string "Ghoulslash: Custom givemon\l"
	.string "Sbird: Dynamic Multichoice\p"
	.string "Anyways, the competition requires\n"
	.string "that the game end with a credits\l"
	.string "screen, so, uh, here you go.$"

MAGM_IndoorHut_Text_Book:
	.string "The pages have been\n"
	.string "torn out.$"

MAGM_IndoorHut_Text_BookShelf:
	.string "It's empty.$"

MAGM_IndoorHut_Text_Bed:
	.string "A sleeping bag.\p"
	.string "Looks pretty dusty.$"

MAGM_Hut_Movement_Walk_In:
	walk_up
	delay_16
	delay_16
	delay_8
	walk_in_place_left
	delay_16
	delay_16
	delay_8
	walk_in_place_right
	delay_16
	delay_16
	delay_8
	face_up
	step_end

MAGM_Hut_Movement_Mew:
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_16
	set_visible
	delay_8
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	walk_left
	walk_down
	walk_in_place_right
	walk_down
	walk_right
	walk_right
	walk_up
	walk_in_place_left
	walk_in_place_left
	walk_in_place_left
	walk_in_place_left
	walk_in_place_left
	walk_in_place_left
	step_end

MAGM_Hut_Movement_WatchMew:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	//waiting for invis
	delay_16
	face_left
	delay_16
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	face_left
	step_end

MAGM_Hut_Movement_MewLeaves::
	walk_down
	walk_left
	walk_left
	walk_up
	walk_in_place_right
	walk_in_place_right
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	delay_16
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end
