	.include "MPlayDef.s"

	.equ	se_wall_hit_reverb_grp, voicegroup030
	.equ	se_wall_hit_reverb_pri, 2
	.equ	se_wall_hit_reverb_rev, reverb_set+50
	.equ	se_wall_hit_reverb_mvl, 127
	.equ	se_wall_hit_reverb_key, 0
	.equ	se_wall_hit_reverb_tbs, 1
	.equ	se_wall_hit_reverb_exg, 0
	.equ	se_wall_hit_reverb_cmp, 1

	.section .rodata
	.global	se_wall_hit_reverb
	.align	2

@********************** Track  1 **********************@

se_wall_hit_reverb_1:
	.byte	KEYSH , se_wall_hit_reverb_key+0
	.byte	TEMPO , 220*se_wall_hit_reverb_tbs/2
	.byte		VOICE , 4
	.byte		VOL   , 127*se_wall_hit_reverb_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		N18   , Cn3 , v127
	.byte	W24
	.byte	FINE

@******************************************************@
	.align	2

se_wall_hit_reverb:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_wall_hit_reverb_pri	@ Priority
	.byte	se_wall_hit_reverb_rev	@ Reverb.

	.word	se_wall_hit_reverb_grp

	.word	se_wall_hit_reverb_1

	.end
