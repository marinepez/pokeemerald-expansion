	.include "MPlayDef.s"

	.equ	mus_mall_dark_grp, voicegroup030
	.equ	mus_mall_dark_pri, 0
	.equ	mus_mall_dark_rev, reverb_set+50
	.equ	mus_mall_dark_mvl, 127
	.equ	mus_mall_dark_key, 0
	.equ	mus_mall_dark_tbs, 1
	.equ	mus_mall_dark_exg, 0
	.equ	mus_mall_dark_cmp, 1

	.section .rodata
	.global	mus_mall_dark
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_mall_dark_1:
	.byte	KEYSH , mus_mall_dark_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 3
	.byte		VOL   , 100*mus_mall_dark_mvl/mxv
	.byte		TIE   , Cn4 , v100
mus_mall_dark_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_mall_dark_1_B1
mus_mall_dark_1_B2:


@******************************************************@
	.align	2

mus_mall_dark:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_mall_dark_pri	@ Priority
	.byte	mus_mall_dark_rev	@ Reverb.

	.word	mus_mall_dark_grp

	.word	mus_mall_dark_1
	.word	mus_mall_dark_1

	.end
