.set LOCALID_GIANT, 1

MAGM9_Mall_MainArea_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MAGM9_Mall_MainArea_MapScripts_OnResume
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MAGM9_Mall_MainArea_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM9_Mall_MainArea_OnTransition
	.byte 0

MAGM9_Mall_MainArea_MapScripts_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MAGM9_Mall_MainArea_MapScripts_HideRollingGiant
	goto_if_set FLAG_POWER_ON, MAGM9_Mall_LightsOnSetup
	return

MAGM9_Mall_MainArea_OnWarp::
	map_script_2 VAR_ROLLING_GIANT_LOCALID, 0, MAGM9_Mall_MainArea_MapScripts_SetInitialVars
	.2byte 0

MAGM9_Mall_MainArea_MapScripts_SetInitialVars::
	setvar VAR_ROLLING_GIANT_LOCALID LOCALID_GIANT
	setvar VAR_ROLLING_GIANT_AI_STATE 2
	return

MAGM9_Mall_MainArea_OnTransition::
	setflashlevel 3
	end

MAGM9_CheckGiant::
	lock
	msgbox MAGM9_CheckGiantMsg, MSGBOX_AUTOCLOSE
	goto MAGM9_Mall_LightsTurnOnCS
	end

MAGM9_CheckGiantMsg:
	.string "It seems to be some kind of uncanny\nstatue of someone.$"

MAGM9_Mall_LightsOnSetup:
	setflashlevel 0
	savebgm MUS_MALL
	return

MAGM9_Mall_LightsTurnOnCS::
	lockall
	applymovement LOCALID_GIANT, Common_Movement_FacePlayer
	playse SE_POWER_ON
	setflashalpha 01
	special UpdateFlashScanlines
	delay 2
	setflashalpha 13
	special UpdateFlashScanlines
	delay 2
	setflashalpha 7
	special UpdateFlashScanlines
	delay 4
	setflashalpha 13
	special UpdateFlashScanlines
	delay 3
	setflashalpha 0
	special UpdateFlashScanlines
	delay 2
	setflashalpha 7
	special UpdateFlashScanlines
	delay 4
	setflashalpha 13
	special UpdateFlashScanlines
	delay 3
	setflashalpha 0
	special UpdateFlashScanlines
	delay 8
	setflashalpha 13
	special UpdateFlashScanlines
	delay 6
	setflashalpha 7
	special UpdateFlashScanlines
	delay 12
	setflashalpha 13
	special UpdateFlashScanlines
	delay 12
	setflashalpha 12
	special UpdateFlashScanlines
	delay 2
	setflashalpha 10
	special UpdateFlashScanlines
	delay 2
	setflashalpha 8
	special UpdateFlashScanlines
	delay 2
	setflashalpha 0
	special UpdateFlashScanlines
	setvar VAR_ROLLING_GIANT_AI_STATE, 1
	setwildbattle SPECIES_ROLLING_GIANT, 50, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	releaseall
	end

MAGM9_Mall_MainArea_MapScripts_HideRollingGiant:
	removeobject LOCALID_GIANT
	setflashalpha 13
	special UpdateFlashScanlines
	return

Mall_HiddenItem_Mart_1::
	call_if_set FLAG_MART_HIDDENITEM_1, Mall_Nothing
	setflag FLAG_MART_HIDDENITEM_1
	setmetatile 68, 35,	METATILE_Shop_Empty_Tile, FALSE
	special DrawWholeMapView
	giveitem ITEM_POTION
	closemessage
	end
Mall_HiddenItem_Mart_2::
	call_if_set FLAG_MART_HIDDENITEM_2, Mall_Nothing
	setflag FLAG_MART_HIDDENITEM_2
	setmetatile 60, 22,	METATILE_Shop_Empty_Tile, FALSE
	special DrawWholeMapView
	giveitem ITEM_POTION
	closemessage
	end
Mall_HiddenItem_Mart_3::
	call_if_set FLAG_MART_HIDDENITEM_3, Mall_Nothing
	setflag FLAG_MART_HIDDENITEM_3
	setmetatile 72, 34, METATILE_Shop_Empty_Tile, FALSE
	special DrawWholeMapView
	giveitem ITEM_POTION
	closemessage
	end
Mall_HiddenItem_Mart_4::
	call_if_set FLAG_MART_HIDDENITEM_4, Mall_Nothing
	setflag FLAG_MART_HIDDENITEM_4
	setmetatile 79, 21, METATILE_Shop_Empty_Tile, FALSE
	special DrawWholeMapView
	giveitem ITEM_POTION
	closemessage
	end
Mall_HiddenItem_Mart_5::
	call_if_set FLAG_MART_HIDDENITEM_5, Mall_Nothing
	setflag FLAG_MART_HIDDENITEM_5
	setmetatile 82, 36, METATILE_Shop_Empty_Tile, FALSE
	special DrawWholeMapView
	giveitem ITEM_POTION
	closemessage
	end
Mall_Nothing::
	end

Mall_Mart_CreepyThing::
	end

Mall_StockedShelf_1::
	call_if_set FLAG_MART_SHELF_1, Mall_Nothing
	setflag FLAG_MART_SHELF_1
	setmetatile 57, 33, METATILE_Shop_Empty_Shelf_V2, TRUE
	setmetatile 57, 34, METATILE_Shop_Empty_Shelf_V1, TRUE
	special DrawWholeMapView
	giveitem ITEM_ETHER
	closemessage
	end
Mall_StockedShelf_2::
	call_if_set FLAG_MART_SHELF_2, Mall_Nothing
	setflag FLAG_MART_SHELF_2
	setmetatile 59, 24, METATILE_Shop_Empty_Shelf_H1, TRUE
	setmetatile 60, 24, METATILE_Shop_Empty_Shelf_H2, TRUE
	special DrawWholeMapView
	giveitem ITEM_ETHER
	closemessage
	end
Mall_StockedShelf_3::
	call_if_set FLAG_MART_SHELF_3, Mall_Nothing
	setflag FLAG_MART_SHELF_3
	setmetatile 71, 22, METATILE_Shop_Empty_Shelf_V4_Left, TRUE
	special DrawWholeMapView
	giveitem ITEM_ETHER
	closemessage
	end
Mall_StockedShelf_4::
	call_if_set FLAG_MART_SHELF_4, Mall_Nothing
	setflag FLAG_MART_SHELF_4
	setmetatile 82, 27, METATILE_Shop_Empty_Shelf_V2_Left, TRUE
	setmetatile 82, 28, METATILE_Shop_Empty_Shelf_V1_Left, TRUE
	special DrawWholeMapView
	giveitem ITEM_ETHER
	closemessage
	end

Mall_Register1::
	lockall
	goto_if_set FLAG_REGISTER1_USED, Mall_Register_Empty
	setflag FLAG_REGISTER1_USED
	goto Mall_Register_GiveCoin
	end

Mall_Register2::
	lockall
	goto_if_set FLAG_REGISTER2_USED, Mall_Register_Empty
	setflag FLAG_REGISTER2_USED
	goto Mall_Register_GiveCoin
	end

Mall_Register3::
	lockall
	goto_if_set FLAG_REGISTER3_USED, Mall_Register_Empty
	setflag FLAG_REGISTER3_USED
	goto Mall_Register_GiveCoin
	end

Mall_Register_GiveCoin::
	msgbox Mall_Text_CoinInRegister, MSGBOX_DEFAULT
	giveitem ITEM_STAR_PIECE
	releaseall
	end

Mall_Register_Empty::
	msgbox Mall_Text_RegisterIsEmpty, MSGBOX_DEFAULT
	releaseall
	end

Mall_Text_CoinInRegister:
	.string "An old register. There's a coin inside.$"

Mall_Text_RegisterIsEmpty:
	.string "The register is empty.$"

Mall_FridgeForRotom::
	lockall
	msgbox Mall_FridgeForRotom_Text1, MSGBOX_DEFAULT
	waitmessage
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox Mall_FridgeForRotom_Text2, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, Mall_FridgeForRotom_RotomPossessedFridge
	case NO, Mall_FridgeForRotom_NoFridge
	case MULTI_B_PRESSED, Mall_FridgeForRotom_NoFridge
Mall_FridgeForRotom_RotomPossessedFridge::
	fadescreen FADE_TO_BLACK
	call Mall_FridgeForRotom_RemoveFridge
	special TryRotomFormChangeInParty
	setflag FLAG_HAS_ROTOM_FROST
	releaseall
	end

Mall_FridgeForRotom_NoFridge::
	msgbox Mall_FridgeForRotom_Text_NoFridge, MSGBOX_DEFAULT
	releaseall
	end

Mall_FridgeForRotom_RemoveFridge::
	setmetatile 84, 70, METATILE_PokemonFanClub_Floor, FALSE
	setmetatile 84, 69, METATILE_PokemonFanClub_Wall_Bottom, TRUE
	return

Mall_FridgeForRotom_Text1::
	.string "This fridge is still here?$"

Mall_FridgeForRotom_Text2::
	.string "Rotom seems to want to possess the\n"
	.string "fridge! Let Rotom in?$"

Mall_FridgeForRotom_Text_NoFridge::
	.string "You left the fridge alone.$"

Mall_ShopsToMall::
	setmaplayoutindex LAYOUT_MAGM9_MALL_MAIN_AREA
	setvar VAR_FLASH_LAYER 4
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToShops1::
	setmaplayoutindex LAYOUT_MAGM9_MALL_SHOPS1
	setvar VAR_FLASH_LAYER 2
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_ArcadeToSecretRoom::
	setmaplayoutindex LAYOUT_MAGM9_MALL_SHOPS1
	setflag FLAG_DISABLE_GIANT_ENCOUNTERS
	setvar VAR_FLASH_LAYER 2
	special SetFlashlightRevealLayer
	call_if_set FLAG_HAS_ROTOM_FROST Mall_FridgeForRotom_RemoveFridge
	special DrawWholeMapView
	releaseall
	end

Mall_SecretRoomToArcade::
	setmaplayoutindex LAYOUT_MAGM9_MALL_ARCADE
	clearflag FLAG_DISABLE_GIANT_ENCOUNTERS
	setvar VAR_FLASH_LAYER 2
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToArcade::
	setmaplayoutindex LAYOUT_MAGM9_MALL_ARCADE
	setvar VAR_FLASH_LAYER 2
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToGroceryStore::
	setmaplayoutindex LAYOUT_MAGM_MALL_SHOPS2
	setvar VAR_FLASH_LAYER 2
	call Mall_MallToGroceryStore_SetTiles
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToGroceryStore_SetTiles::
	call_if_unset FLAG_MART_HIDDENITEM_1, Mall_MallToGroceryStore_SetItemBalls_1
	call_if_unset FLAG_MART_HIDDENITEM_2, Mall_MallToGroceryStore_SetItemBalls_2
	call_if_unset FLAG_MART_HIDDENITEM_3, Mall_MallToGroceryStore_SetItemBalls_3
	call_if_unset FLAG_MART_HIDDENITEM_4, Mall_MallToGroceryStore_SetItemBalls_4
	call_if_unset FLAG_MART_HIDDENITEM_5, Mall_MallToGroceryStore_SetItemBalls_5
	call_if_set FLAG_MART_SHELF_1, Mall_MallToGroceryStore_SetEmptyShelf_1
	call_if_set FLAG_MART_SHELF_2, Mall_MallToGroceryStore_SetEmptyShelf_2
	call_if_set FLAG_MART_SHELF_3, Mall_MallToGroceryStore_SetEmptyShelf_3
	call_if_set FLAG_MART_SHELF_4, Mall_MallToGroceryStore_SetEmptyShelf_4
	return

Mall_MallToGroceryStore_SetItemBalls_1::
	setmetatile 68, 35,	METATILE_Shop_Item_Ball, TRUE
	return
Mall_MallToGroceryStore_SetItemBalls_2::
	setmetatile 60, 22,	METATILE_Shop_Item_Ball, TRUE
	return
Mall_MallToGroceryStore_SetItemBalls_3::
	setmetatile 72, 34, METATILE_Shop_Item_Ball, TRUE
	return
Mall_MallToGroceryStore_SetItemBalls_4::
	setmetatile 79, 21, METATILE_Shop_Item_Ball, TRUE
	return
Mall_MallToGroceryStore_SetItemBalls_5::
	setmetatile 82, 36, METATILE_Shop_Item_Ball, TRUE
	return

Mall_MallToGroceryStore_SetEmptyShelf_1::
	setmetatile 57, 33, METATILE_Shop_Empty_Shelf_V2, TRUE
	setmetatile 57, 34, METATILE_Shop_Empty_Shelf_V1, TRUE
	return
Mall_MallToGroceryStore_SetEmptyShelf_2::
	setmetatile 59, 24, METATILE_Shop_Empty_Shelf_H1, TRUE
	setmetatile 60, 24, METATILE_Shop_Empty_Shelf_H2, TRUE
	return
Mall_MallToGroceryStore_SetEmptyShelf_3::
	setmetatile 71, 22, METATILE_Shop_Empty_Shelf_V4_Left, TRUE
	return
Mall_MallToGroceryStore_SetEmptyShelf_4::
	setmetatile 82, 27, METATILE_Shop_Empty_Shelf_V2_Left, TRUE
	setmetatile 82, 28, METATILE_Shop_Empty_Shelf_V1_Left, TRUE
	return

Mall_MallToDojo::
	setmaplayoutindex LAYOUT_MAGM9_MALL_DOJO
	setvar VAR_FLASH_LAYER 2
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_MallToRestaurants::
	setmaplayoutindex LAYOUT_MAGM9_MALL_RESTAURANTS
	setvar VAR_FLASH_LAYER 2
	special SetFlashlightRevealLayer
	special DrawWholeMapView
	releaseall
	end

Mall_PCTest::
	lock
	call Common_EventScript_SaveGame
	closemessage
	end

Save_PC::
	lockall
	playse SE_PC_LOGIN
	msgbox Save_PC_Prompt, MSGBOX_DEFAULT
	call Common_EventScript_SaveGame
	closemessage
	releaseall
	end

Save_PC_Prompt:
	.string "Somehow, this PC appears to be in\nworking condition.\p{PLAYER} can save their progress\nwith it.$"

Mall_WarpToLowerFloorLeft::
	warp MAP_MAGM9_MALL_TOP_FLOOR, 43, 44
	waitstate
	end

Mall_WarpToLowerFloorRight::
	warp MAP_MAGM9_MALL_TOP_FLOOR, 49, 44
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
