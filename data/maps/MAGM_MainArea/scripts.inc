MAGM_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_MAGM_MainArea_OnTransition
	.byte 0

BattleFrontier_MAGM_MainArea_OnTransition:
	setflag FLAG_SYS_SAFARI_MODE
	end

BattleFrontier_MAGM_MainArea_EventScript_CutTree1::
	setflag FLAG_CUT_TREE_1
	goto EventScript_CutTree
	end

BattleFrontier_MAGM_MainArea_EventScript_CutTree2::
	setflag FLAG_CUT_TREE_2
	goto EventScript_CutTree
	end

BattleFrontier_MAGM_MainArea_EventScript_CutTree3::
	setflag FLAG_CUT_TREE_3
	goto EventScript_CutTree
	end

BattleFrontier_MAGM_MainArea_EventScript_CutTree4::
	setflag FLAG_CUT_TREE_4
	goto EventScript_CutTree
	end

BattleFrontier_MAGM_MainArea_EventScript_CutTree5::
	setflag FLAG_CUT_TREE_5
	goto EventScript_CutTree
	end

BattleFrontier_MAGM_MainArea_EventScript_CutTree6::
	setflag FLAG_CUT_TREE_6
	goto EventScript_CutTree
	end

BattleFrontier_MAGM_MainArea_Sign_BanIncineraor::
	playmoncry SPECIES_INCINEROAR, CRY_MODE_FAINT
	showmonpic SPECIES_INCINEROAR, 10, 3
	waitbuttonpress
	hidemonpic
	end
