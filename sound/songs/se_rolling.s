	.include "MPlayDef.s"

	.equ	se_rolling_grp, voicegroup030
	.equ	se_rolling_pri, 2
	.equ	se_rolling_rev, reverb_set+50
	.equ	se_rolling_mvl, 127
	.equ	se_rolling_key, 0
	.equ	se_rolling_tbs, 1
	.equ	se_rolling_exg, 0
	.equ	se_rolling_cmp, 1

	.section .rodata
	.global	se_rolling
	.align	2

@********************** Track  1 **********************@

se_rolling_1:
	.byte	KEYSH , se_rolling_key+0
	.byte	TEMPO , 220*se_rolling_tbs/2
	.byte		VOICE , 5
	.byte		VOL   , 127*se_rolling_mvl/mxv
	.byte		TIE   , Cn3 , v127
se_rolling_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	se_rolling_1_B1
se_rolling_1_B2:

@********************** Track  2 **********************@
se_rolling_2:
	.byte	KEYSH , se_rolling_key+0
	.byte		VOICE , 6
	.byte		VOL   , 1*se_rolling_mvl/mxv
	.byte		TIE   , Cn3 , v127
se_rolling_2_B1:
	.byte	W96
	.byte	GOTO
	 .word	se_rolling_2_B1
se_rolling_2_B2:

@******************************************************@
	.align	2

se_rolling:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_rolling_pri	@ Priority
	.byte	se_rolling_rev	@ Reverb.

	.word	se_rolling_grp

	.word	se_rolling_1
	.word	se_rolling_2

	.end
