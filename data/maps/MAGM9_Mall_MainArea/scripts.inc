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
	special DrawWholeMapView
	releaseall
	end

Mall_MallToShops1::
	setmaplayoutindex LAYOUT_MAGM9_MALL_SHOPS1
	special DrawWholeMapView
	releaseall
	end

Mall_PCTest::
	lock
	call Common_EventScript_SaveGame
	end
