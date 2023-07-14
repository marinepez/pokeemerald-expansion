Lion_Battlefield_MapScripts::
	.byte 0

Lion_Battlefield_EventScript_LionEndlessBattle::
	lock
	faceplayer
	setwildbattle SPECIES_LION, 20
	waitse
	playmoncry SPECIES_LION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Lion_Battlefield_EventScript_DefeatedSingleLion
	release
	end

Lion_Battlefield_EventScript_LionSingleBattle::
	lock
	faceplayer
	setwildbattle SPECIES_LION, 20
	waitse
	playmoncry SPECIES_LION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Lion_Battlefield_EventScript_DefeatedSingleLion
	release
	end

Lion_Battlefield_EventScript_DefeatedSingleLion::
	setvar VAR_DECREMENT_COUNT, 1
	setvar VAR_DECREMENT_THOUSANDS, 0
	callnative CMD_LionCounter_DecrementCounter
	setflag FLAG_DEFEATED_FIRST_LION
	goto Common_EventScript_RemoveStaticPokemon
	end
