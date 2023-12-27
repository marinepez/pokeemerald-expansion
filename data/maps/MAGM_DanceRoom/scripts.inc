.set LOCALID_GLOOM, 1
.set LOCALID_LOMBRE, 2

MAGM_DanceRoom_MapScripts::
	.byte 0

MAGM_DanceRoom_EventScript_Marowak::
	playmoncry SPECIES_MAROWAK_ALOLAN, CRY_MODE_NORMAL
	waitmoncry
	bufferspeciesname 0, SPECIES_MAROWAK
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_PlayerDance
	end

MAGM_DanceRoom_EventScript_Oricorio::
	playmoncry SPECIES_ORICORIO, CRY_MODE_NORMAL
	waitmoncry
	bufferspeciesname 0, SPECIES_ORICORIO
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_PlayerDance
	end

MAGM_DanceRoom_EventScript_Thwackey::
	playmoncry SPECIES_THWACKEY, CRY_MODE_NORMAL
	waitmoncry
	end

MAGM_DanceRoom_EventScript_Gloom::
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	bufferspeciesname 0, SPECIES_GLOOM
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_DanceWithGloom
	end

MAGM_DanceRoom_EventScript_DanceWithGloom::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDance0
	applymovement LOCALID_GLOOM, MAGM_DanceRoom_Movement_GloomDance
	waitmovement 0
	playmoncry SPECIES_GLOOM, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_MonIsDancingWithYou, MSGBOX_DEFAULT
	waitmessage
	multichoicegrid 8, 8, MULTI_GLOOM_MOVES, 2, FALSE
	release
	end

MAGM_DanceRoom_EventScript_Lombre::
	playmoncry SPECIES_LOMBRE, CRY_MODE_NORMAL
	waitmoncry
	bufferspeciesname 0, SPECIES_LOMBRE
	msgbox MAGM_DanceRoom_Text_MonIsDancing, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, MAGM_DanceRoom_EventScript_DanceWithLombre
	end

MAGM_DanceRoom_EventScript_DanceWithLombre::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDance1
	applymovement LOCALID_LOMBRE, MAGM_DanceRoom_Movement_LombreDance
	waitmovement 0
	playmoncry SPECIES_LOMBRE, CRY_MODE_NORMAL
	waitmoncry
	msgbox MAGM_DanceRoom_Text_MonIsDancingWithYou, MSGBOX_DEFAULT
	closemessage
	release
	end

MAGM_DanceRoom_EventScript_PlayerDance::
	applymovement OBJ_EVENT_ID_PLAYER, MAGM_DanceRoom_Movement_PlayerDanceShort
	waitmovement 0
	release
	end

MAGM_DanceRoom_Text_MonIsDancingWithYou:
	.string "{STR_VAR_1} is dancing with you!\p"
	.string "Teach it a dance?$"

MAGM_DanceRoom_Text_MonIsDancing:
	.string "{STR_VAR_1} is dancing!\n"
	.string "Dance with it?$"

MAGM_DanceRoom_Movement_PlayerDanceShort:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_slow_right
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	step_end

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
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_PlayerDance1:
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	step_end

MAGM_DanceRoom_Movement_GloomDance:
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
	walk_in_place_fast_down
	walk_in_place_fast_left
	walk_in_place_fast_up
	walk_in_place_fast_right
	walk_in_place_slow_down
	face_player
	step_end

MAGM_DanceRoom_Movement_LombreDance:
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
	delay_16
	delay_16
	delay_16
	walk_in_place_left
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_in_place_left
	delay_8
	walk_in_place_right
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	walk_in_place_right
	delay_8
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_slow_down
	step_end
