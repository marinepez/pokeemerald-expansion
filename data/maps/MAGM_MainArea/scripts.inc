MAGM_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_MainArea_OnTransition
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, MAGM_MainArea_CheckIfGiveNote
	.byte 0

MAGM_MainArea_OnTransition:
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setflag FLAG_SYS_SAFARI_MODE
	end

MAGM_MainArea_CheckIfGiveNote:
	goto_if_set FLAG_GOT_OLD_NOTE, MAGM_MainArea_CheckIfGiveNote_End
	special ScriptGetPokedexInfo
	goto_if_lt VAR_0x8009, 10, MAGM_MainArea_CheckIfGiveNote_End //Number of national pokemon caught
	setflag FLAG_GOT_OLD_NOTE
	msgbox MAGM_MainArea_Text_FoundSomethingOnGround, MSGBOX_DEFAULT
	giveitem ITEM_LETTER_PLACEHOLDER
	closemessage
MAGM_MainArea_CheckIfGiveNote_End::
	end

MAGM_MainArea_ItemVideoGame::
	finditem ITEM_VIDEO_GAME
	end

MAGM_MainArea_EventScript_CutTree1::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_1
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree2::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_2
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree3::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_3
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree4::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_4
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree5::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_5
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree6::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_6
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree7::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_7
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree8::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_8
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree9::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_9
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree10::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_10
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree11::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_11
	goto EventScript_CutTree
	end

MAGM_MainArea_EventScript_CutTree12::
	checkitem ITEM_MACHETE, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckTreeCantCut
	setflag FLAG_CUT_TREE_12
	goto EventScript_CutTree
	end

MAGM_MainArea_Sign_BanIncineraor::
	playmoncry SPECIES_INCINEROAR, CRY_MODE_FAINT
	showmonpic SPECIES_INCINEROAR, 10, 3
	waitbuttonpress
	hidemonpic
	end

MAGM_MainArea_Text_FoundSomethingOnGround:
	.string "Huh? There's something in\n"
	.string "the grass.$"
