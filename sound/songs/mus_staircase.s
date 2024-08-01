	.include "MPlayDef.s"

	.equ	mus_staircase_grp, voicegroup030
	.equ	mus_staircase_pri, 0
	.equ	mus_staircase_rev, reverb_set+50
	.equ	mus_staircase_mvl, 127
	.equ	mus_staircase_key, 0
	.equ	mus_staircase_tbs, 1
	.equ	mus_staircase_exg, 0
	.equ	mus_staircase_cmp, 1

	.section .rodata
	.global	mus_staircase
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_staircase_1:
	.byte	KEYSH , mus_staircase_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 120/2
	.byte		VOICE , 1
	.byte		PAN   , c_v-0
	.byte		VOL   , 46*mus_staircase_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		TIE   , Cn3 , v100
mus_staircase_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_staircase_1_B1
mus_staircase_1_B2:

@**************** Track 2 (Midi-Chn.2) ****************@

mus_staircase_2:
	.byte	KEYSH , mus_staircase_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 85/2
	.byte		VOICE , 2
	.byte		VOL   , 42*mus_staircase_mvl/mxv
	.byte		BEND  , c_v-12
mus_staircase_2_B1:
	.byte		PAN   , c_v-12
	.byte	W32
	.byte		TIE   , Cn3 , v096
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W28
	.byte		EOT
	.byte		PAN   , c_v+21
	.byte		TIE   , Cn3 , v076
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W28
	.byte		EOT
	.byte	GOTO
	 .word	mus_staircase_2_B1
mus_staircase_2_B2:
	
@**************** Track 3 (Midi-Chn.3) ****************@

mus_staircase_3:
	.byte	KEYSH , mus_staircase_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 3
	.byte		VOL   , 1*mus_staircase_mvl/mxv
	.byte		TIE   , Cn4 , v100
mus_staircase_3_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_staircase_3_B1
mus_staircase_3_B2:

@**************** Track 4 (Midi-Chn.4) ****************@

mus_staircase_4:
	.byte	KEYSH , mus_staircase_key+0
@ 000   ----------------------------------------
	.byte		PAN   , c_v-12
	.byte		VOICE , 3
	.byte		MOD , 40
	.byte		LFOS , 1
	.byte		VOL   , 1*mus_staircase_mvl/mxv
	.byte		TIE   , Cn4 , v068
mus_staircase_4_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_staircase_4_B1
mus_staircase_4_B2:


@******************************************************@
	.align	2

mus_staircase:
	.byte	3	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_staircase_pri	@ Priority
	.byte	mus_staircase_rev	@ Reverb.

	.word	mus_staircase_grp

	.word	mus_staircase_1
	.word	mus_staircase_2
	.word	mus_staircase_3

	.end
