	.include "MPlayDef.s"

	.equ	mus_mall_grp, voicegroup030
	.equ	mus_mall_pri, 0
	.equ	mus_mall_rev, reverb_set+50
	.equ	mus_mall_mvl, 127
	.equ	mus_mall_key, 0
	.equ	mus_mall_tbs, 1
	.equ	mus_mall_exg, 0
	.equ	mus_mall_cmp, 1

	.section .rodata
	.global	mus_mall
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_mall_1:
	.byte	KEYSH , mus_mall_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 120/2
	.byte		VOICE , 0
	.byte		PAN   , c_v-0
	.byte		VOL   , 92*mus_mall_mvl/mxv
	.byte		BEND  , c_v-0
	.byte		TIE   , Cn3 , v100
mus_mall_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_mall_1_B1
mus_mall_1_B2:

@******************************************************@
	.align	2

mus_mall:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_mall_pri	@ Priority
	.byte	mus_mall_rev	@ Reverb.

	.word	mus_mall_grp

	.word	mus_mall_1
	.word	mus_mall_1

	.end
