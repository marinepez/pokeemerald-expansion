.set LOCALID_GLOOM, 1
.set LOCALID_LOMBRE, 2

MAGM_DanceRoom_MapScripts::
	.byte 0

MAGM_DanceRoom_EventScript_Marowak::
	playmoncry SPECIES_MAROWAK_ALOLAN, CRY_MODE_NORMAL
	waitmoncry
	end

MAGM_DanceRoom_EventScript_Oricorio::
	playmoncry SPECIES_ORICORIO, CRY_MODE_NORMAL
	waitmoncry
	end

MAGM_DanceRoom_EventScript_Thwackey::
	playmoncry SPECIES_THWACKEY, CRY_MODE_NORMAL
	waitmoncry
	end

MAGM_DanceRoom_EventScript_Gloom::
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_GloomIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_DanceWithGloom
	end

MAGM_DanceRoom_EventScript_DanceWithGloom::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDance0
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_GloomDance0
	waitmovement 0
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_GloomIsCopyingYourDance, MSGBOX_DEFAULT
	closemessage
	end

MAGM_DanceRoom_EventScript_Lombre::
	playmoncry SPECIES_LOMBRE, CRY_MODE_NORMAL
	waitmoncry
	end

MAGM_DanceRoom_Text_GloomIsCopyingYourDance:
	.string "Gloom is dancing with you!$"

MAGM_DanceRoom_Text_GloomIsDancing:
	.string "Gloom is dancing!\n"
	.string "Dance with it?$"

MAGM_DanceRoom_Movement_PlayerDance0:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_GloomDance0:
	face_player
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	face_player
	step_end
