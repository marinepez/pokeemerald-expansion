.set LOCALID_BERRY_GROWER, 10

HomeBase_TilledLand_MapScripts::
	.byte 0

HomeBase_TilledLand_EventScript_HelpingGrowBerries::
	lock
	delay 5
	playse SE_LEDGE
	applymovement LOCALID_BERRY_GROWER, HomeBase_TilledLand_Movement_JumpHappily1
	waitmovement 0
	delay 2
	playse SE_LEDGE
	applymovement LOCALID_BERRY_GROWER, HomeBase_TilledLand_Movement_JumpHappily2
	waitmovement 0
	delay 5
	msgbox HomeBase_TilledLand_Text_HelpingGrowBerries, MSGBOX_NPC
	end

HomeBase_TilledLand_Text_HelpingGrowBerries:
	.string "Your POKéMON is happily helping the\n" 
	.string "berries grow.$"

HomeBase_TilledLand_Movement_JumpHappily1:
	jump_in_place_down_up
	step_end

HomeBase_TilledLand_Movement_JumpHappily2:
	jump_in_place_left_right
	face_player
	step_end
