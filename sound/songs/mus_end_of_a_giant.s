	.include "MPlayDef.s"

	.equ	mus_end_of_a_giant_grp, voicegroup030
	.equ	mus_end_of_a_giant_pri, 0
	.equ	mus_end_of_a_giant_rev, reverb_set+50
	.equ	mus_end_of_a_giant_mvl, 127
	.equ	mus_end_of_a_giant_key, 0
	.equ	mus_end_of_a_giant_tbs, 1
	.equ	mus_end_of_a_giant_exg, 0
	.equ	mus_end_of_a_giant_cmp, 1

	.section .rodata
	.global	mus_end_of_a_giant
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_end_of_a_giant_1:
	.byte	KEYSH , mus_end_of_a_giant_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 120/2
	.byte		VOICE , 11
	.byte		PAN   , c_v-0
	.byte		VOL   , 92*mus_end_of_a_giant_mvl/mxv
	.byte		BEND  , c_v-0
	.byte		TIE   , Cn3 , v100
mus_end_of_a_giant_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_end_of_a_giant_B1
mus_end_of_a_giant_B2:

@******************************************************@
	.align	2

mus_end_of_a_giant:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_end_of_a_giant_pri	@ Priority
	.byte	mus_end_of_a_giant_rev	@ Reverb.

	.word	mus_end_of_a_giant_grp

	.word	mus_end_of_a_giant_1
	.word	mus_end_of_a_giant_1

	.end
