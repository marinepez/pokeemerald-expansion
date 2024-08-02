	.include "MPlayDef.s" 

	.equ	se_rolling_reverb_grp, voicegroup030
	.equ	se_rolling_reverb_pri, 2
	.equ	se_rolling_reverb_rev, reverb_set+50
	.equ	se_rolling_reverb_mvl, 127
	.equ	se_rolling_reverb_key, 0
	.equ	se_rolling_reverb_tbs, 1
	.equ	se_rolling_reverb_exg, 0
	.equ	se_rolling_reverb_cmp, 1

	.section .rodata
	.global	se_rolling_reverb
	.align	2

@********************** Track  1 **********************@ (AVIRCODE) This track is currently unused due to the reverb also being present in se_rolling.s

se_rolling_reverb_1:
	.byte	KEYSH , se_rolling_reverb_key+0
	.byte	TEMPO , 220*se_rolling_reverb_tbs/2
	.byte		VOICE , 6
	.byte		VOL   , 80*se_rolling_reverb_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		TIE   , Cn3 , v127
se_rolling_reverb_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	se_rolling_reverb_1_B1
se_rolling_reverb_1_B2:

@******************************************************@
	.align	2

se_rolling_reverb:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_rolling_reverb_pri	@ Priority
	.byte	se_rolling_reverb_rev	@ Reverb.

	.word	se_rolling_reverb_grp

	.word	se_rolling_reverb_1

	.end
