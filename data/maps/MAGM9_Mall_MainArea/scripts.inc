MAGM9_Mall_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MAGM9_Mall_MainArea_MapScripts_OnResume
	.byte 0

MAGM9_Mall_MainArea_MapScripts_OnResume::
	goto_if_set FLAG_SYS_CTRL_OBJ_DELETE, MarioDebugRoom2_MapScripts_HideRollingGiant
	return

MarioDebugRoom2_MapScripts_HideRollingGiant:
	return

MarioDebugRoom2_MapScripts_HideRollingGiantTEST:
	removeobject 0
	return

Mall_ShopsToMall::
	setmaplayoutindex LAYOUT_MAGM9_MALL_MAIN_AREA
	setvar VAR_0x8004 4
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToShops1::
	setmaplayoutindex LAYOUT_MAGM9_MALL_SHOPS1
	setvar VAR_0x8004 1
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToArcade::
	setmaplayoutindex LAYOUT_MAGM9_MALL_ARCADE
	setvar VAR_0x8004 2
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_PCTest::
	lock
	call Common_EventScript_SaveGame
	closemessage
	end
