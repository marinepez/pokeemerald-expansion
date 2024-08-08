	.include "MPlayDef.s"

	.equ	se_reset_grp, voicegroup030
	.equ	se_reset_pri, 2
	.equ	se_reset_rev, reverb_set+50
	.equ	se_reset_mvl, 127
	.equ	se_reset_key, 0
	.equ	se_reset_tbs, 1
	.equ	se_reset_exg, 0
	.equ	se_reset_cmp, 1

	.section .rodata
	.global	se_reset
	.align	2

@********************** Track  1 **********************@

se_reset_1:
	.byte	KEYSH , se_reset_key+0
	.byte	TEMPO , 20*se_reset_tbs/2
	.byte		VOICE , 10
	.byte		VOL   , 127*se_reset_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		N96   , Cn3 , v127
	.byte	W96
	.byte	FINE

@******************************************************@
	.align	2

se_reset:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_reset_pri	@ Priority
	.byte	se_reset_rev	@ Reverb.

	.word	se_reset_grp

	.word	se_reset_1
	.word	se_reset_1
	.word	se_reset_1

	.end
