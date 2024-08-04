	.include "MPlayDef.s"

	.equ	mus_giant_battle_1_grp, voicegroup030
	.equ	mus_giant_battle_1_pri, 0
	.equ	mus_giant_battle_1_rev, reverb_set+50
	.equ	mus_giant_battle_1_mvl, 127
	.equ	mus_giant_battle_1_key, 0
	.equ	mus_giant_battle_1_tbs, 1
	.equ	mus_giant_battle_1_exg, 0
	.equ	mus_giant_battle_1_cmp, 1

	.section .rodata
	.global	mus_giant_battle_1
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_giant_battle_1_1:
	.byte	KEYSH , mus_giant_battle_1_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 120/2
	.byte		VOICE , 8
	.byte		PAN   , c_v-0
	.byte		VOL   , 127*mus_giant_battle_1_mvl/mxv
	.byte		BEND  , c_v-0
	.byte		TIE   , Cn3 , v100
mus_giant_battle_1_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_giant_battle_1_1_B1
mus_giant_battle_1_1_B2:

@******************************************************@
	.align	2

mus_giant_battle_1:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_giant_battle_1_pri	@ Priority
	.byte	mus_giant_battle_1_rev	@ Reverb.

	.word	mus_giant_battle_1_grp

	.word	mus_giant_battle_1_1
	.word	mus_giant_battle_1_1

	.end
