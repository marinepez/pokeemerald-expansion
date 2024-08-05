	.include "MPlayDef.s" 

	.equ	se_giant_catch_grp, voicegroup030
	.equ	se_giant_catch_pri, 2
	.equ	se_giant_catch_rev, reverb_set+50
	.equ	se_giant_catch_mvl, 127
	.equ	se_giant_catch_key, 0
	.equ	se_giant_catch_tbs, 1
	.equ	se_giant_catch_exg, 0
	.equ	se_giant_catch_cmp, 1

	.section .rodata
	.global	se_giant_catch
	.align	2

@********************** Track  1 **********************@ (AVIRCODE) This track is currently unused due to the reverb also being present in se_rolling.s

se_giant_catch_1:
	.byte	KEYSH , se_giant_catch_key+0
	.byte	TEMPO , 220*se_giant_catch_tbs/2
	.byte		VOICE , 7
	.byte		VOL   , 80*se_giant_catch_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		TIE   , Cn3 , v127
se_giant_catch_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	se_giant_catch_1_B1
se_giant_catch_1_B2:

@******************************************************@
	.align	2

se_giant_catch:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_giant_catch_pri	@ Priority
	.byte	se_giant_catch_rev	@ Reverb.

	.word	se_giant_catch_grp

	.word	se_giant_catch_1
	.word	se_giant_catch_1

	.end
