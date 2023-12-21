MAGM_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_MAGM_MainArea_OnTransition
	.byte 0

BattleFrontier_MAGM_MainArea_OnTransition:
	setflag FLAG_SYS_SAFARI_MODE
	end
