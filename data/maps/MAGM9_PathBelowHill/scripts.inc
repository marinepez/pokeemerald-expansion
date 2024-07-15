MAGM9_PathBelowHill_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PathBelowHill_OnTransition
	.byte 0

PathBelowHill_OnTransition::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	end