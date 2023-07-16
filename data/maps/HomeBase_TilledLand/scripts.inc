.set LOCALID_BERRY_GROWER, 10

HomeBase_TilledLand_MapScripts::
	.byte 0

HomeBase_TilledLand_EventScript_HelpingGrowBerries::
	applymovement LOCALID_BERRY_GROWER, HomeBase_TilledLand_Movement_JumpHappily
	waitmovement 0
	msgbox HomeBase_TilledLand_Text_HelpingGrowBerries, MSGBOX_NPC
	end

HomeBase_TilledLand_Text_HelpingGrowBerries:
	.string "Your POKéMON is happily helping the\n" 
	.string "berries grow.$"

HomeBase_TilledLand_Movement_JumpHappily:
	jump_in_place_down_up
	jump_in_place_left_right
	face_player
	step_end
