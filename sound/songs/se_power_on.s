	.include "MPlayDef.s"

	.equ	se_power_on_grp, voicegroup030
	.equ	se_power_on_pri, 2
	.equ	se_power_on_rev, reverb_set+50
	.equ	se_power_on_mvl, 127
	.equ	se_power_on_key, 0
	.equ	se_power_on_tbs, 1
	.equ	se_power_on_exg, 0
	.equ	se_power_on_cmp, 1

	.section .rodata
	.global	se_power_on
	.align	2

@********************** Track  1 **********************@

se_power_on_1:
	.byte	KEYSH , se_power_on_key+0
	.byte	TEMPO , 20*se_power_on_tbs/2
	.byte		VOICE , 12
	.byte		VOL   , 127*se_power_on_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		N96   , Cn3 , v127
	.byte	W96
	.byte	FINE

@******************************************************@
	.align	2

se_power_on:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_power_on_pri	@ Priority
	.byte	se_power_on_rev	@ Reverb.

	.word	se_power_on_grp

	.word	se_power_on_1
	.word	se_power_on_1
	.word	se_power_on_1

	.end
