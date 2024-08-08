	.include "MPlayDef.s"

	.equ	mus_forest_grp, voicegroup030
	.equ	mus_forest_pri, 0
	.equ	mus_forest_rev, reverb_set+50
	.equ	mus_forest_mvl, 127
	.equ	mus_forest_key, 0
	.equ	mus_forest_tbs, 1
	.equ	mus_forest_exg, 0
	.equ	mus_forest_cmp, 1

	.section .rodata
	.global	mus_forest
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_forest_1:
	.byte	KEYSH , mus_forest_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 120/2
	.byte		VOICE , 9
	.byte		PAN   , c_v-0
	.byte		VOL   , 92*mus_forest_mvl/mxv
	.byte		BEND  , c_v-0
	.byte		TIE   , Cn3 , v100
mus_forest_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_forest_1_B1
mus_forest_1_B2:

@******************************************************@
	.align	2

mus_forest:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_forest_pri	@ Priority
	.byte	mus_forest_rev	@ Reverb.

	.word	mus_forest_grp

	.word	mus_forest_1
	.word	mus_forest_1

	.end
