MAGM_Indoor_Hut_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_Hut_OnTransition
	.byte 0

MAGM_Hut_OnTransition:
	clearflag FLAG_SYS_SAFARI_MODE
	special ZeroPlayerPartyMons
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

MAGM_IndoorHut_Text_Book:
	.string "The pages have been\n"
	.string "torn out.$"

MAGM_IndoorHut_Text_BookShelf:
	.string "It's empty.$"

MAGM_IndoorHut_Text_Bed:
	.string "A sleeping bag.\p"
	.string "Looks pretty dusty.$"
