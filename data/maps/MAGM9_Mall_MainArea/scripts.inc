.set LOCALID_GIANT, 1

MAGM9_Mall_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MAGM9_Mall_MainArea_MapScripts_OnResume
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MAGM9_Mall_MainArea_OnWarp
	.byte 0

MAGM9_Mall_MainArea_MapScripts_OnResume::
	goto_if_set FLAG_SYS_CTRL_OBJ_DELETE, MAGM9_Mall_MainArea_MapScripts_HideRollingGiant
	return

MAGM9_Mall_MainArea_OnWarp::
	map_script_2 VAR_ROLLING_GIANT_LOCALID, 0, MAGM9_Mall_MainArea_MapScripts_SetInitialVars
	.2byte 0

MAGM9_Mall_MainArea_MapScripts_SetInitialVars::
	setvar VAR_ROLLING_GIANT_LOCALID LOCALID_GIANT
	setvar VAR_ROLLING_GIANT_AI_STATE 2
	return

MAGM9_Mall_MainArea_MapScripts_HideRollingGiant:
	return

MAGM9_Mall_MainArea_MapScripts_HideRollingGiantTEST:
	removeobject LOCALID_GIANT
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

Mall_WarpToLowerFloorLeft::
	warp MAP_MAGM9_MALL_LOWER_FLOOR, 43, 45
	waitstate
	end

Mall_WarpToLowerFloorRight::
	warp MAP_MAGM9_MALL_LOWER_FLOOR, 49, 45
	waitstate
	end

Mall_WarpToMainAreaLeft::
	warp MAP_MAGM9_MALL_MAIN_AREA, 43, 41
	waitstate
	end

Mall_WarpToMainAreaRight::
	warp MAP_MAGM9_MALL_MAIN_AREA, 49, 41
	waitstate
	end
