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
	msgbox MAGM_IndoorHut_Text_ThankYou, MSGBOX_DEFAULT
	closemessage
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

MAGM_IndoorHut_Text_ThankYou:
	.string "Boop.$"

MAGM_IndoorHut_Text_Book:
	.string "The pages have been\n"
	.string "torn out.$"

MAGM_IndoorHut_Text_BookShelf:
	.string "It's empty.$"

MAGM_IndoorHut_Text_Bed:
	.string "A sleeping bag.\p"
	.string "Looks pretty dusty.$"
