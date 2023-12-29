MAGM_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_MAGM_MainArea_OnTransition
	.byte 0

BattleFrontier_MAGM_MainArea_OnTransition:
	setflag FLAG_SYS_SAFARI_MODE
	end

BattleFrontier_MAGM_MainArea_Sign_BanIncineraor::
	playmoncry SPECIES_INCINEROAR, CRY_MODE_FAINT
	showmonpic SPECIES_INCINEROAR, 10, 3
	waitbuttonpress
	hidemonpic
	end
