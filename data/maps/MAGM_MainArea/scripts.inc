MAGM_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM_MainArea_OnTransition
	.byte 0

MAGM_MainArea_OnTransition:
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setflag FLAG_SYS_SAFARI_MODE
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

MAGM_MainArea_Sign_BanIncineraor::
	playmoncry SPECIES_INCINEROAR, CRY_MODE_FAINT
	showmonpic SPECIES_INCINEROAR, 10, 3
	waitbuttonpress
	hidemonpic
	end
