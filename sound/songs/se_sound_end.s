	.include "MPlayDef.s"

	.equ	se_sound_end_grp, voicegroup030
	.equ	se_sound_end_pri, 2
	.equ	se_sound_end_rev, reverb_set+50
	.equ	se_sound_end_mvl, 127
	.equ	se_sound_end_key, 0
	.equ	se_sound_end_tbs, 1
	.equ	se_sound_end_exg, 0
	.equ	se_sound_end_cmp, 1

	.section .rodata
	.global	se_sound_end
	.align	2

@********************** Track  1 **********************@

se_sound_end_1:
	.byte	FINE

@******************************************************@
	.align	2

se_sound_end:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_sound_end_pri	@ Priority
	.byte	se_sound_end_rev	@ Reverb.

	.word	se_sound_end_grp

	.word	se_sound_end_1

	.end
