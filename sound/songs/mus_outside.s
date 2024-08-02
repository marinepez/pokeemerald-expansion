	.include "MPlayDef.s"

	.equ	mus_outside_grp, voicegroup030
	.equ	mus_outside_pri, 0
	.equ	mus_outside_rev, reverb_set+50
	.equ	mus_outside_mvl, 127
	.equ	mus_outside_key, 0
	.equ	mus_outside_tbs, 1
	.equ	mus_outside_exg, 0
	.equ	mus_outside_cmp, 1

	.section .rodata
	.global	mus_outside
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_outside_1:
	.byte	KEYSH , mus_outside_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 1
	.byte		PAN   , c_v-0
	.byte		VOL   , 92*mus_outside_mvl/mxv
	.byte		BEND  , c_v+0
	.byte		TIE   , Cn3 , v100
mus_outside_1_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_outside_1_B1
mus_outside_1_B2:

@**************** Track 2 (Midi-Chn.2) ****************@

mus_outside_2:
	.byte	KEYSH , mus_outside_key+0
@ 000   ----------------------------------------
	.byte		TEMPO , 85/2
	.byte		VOICE , 2
	.byte		VOL   , 42*mus_outside_mvl/mxv
	.byte		BEND  , c_v-12
mus_outside_2_B1:
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
	 .word	mus_outside_2_B1
mus_outside_2_B2:
	
@**************** Track 3 (Midi-Chn.3) ****************@

mus_outside_3:
	.byte	KEYSH , mus_outside_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 3
	.byte		VOL   , 1*mus_outside_mvl/mxv
	.byte		TIE   , Cn4 , v100
mus_outside_3_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_outside_3_B1
mus_outside_3_B2:

@**************** Track 4 (Midi-Chn.4) ****************@

mus_outside_4:
	.byte	KEYSH , mus_outside_key+0
@ 000   ----------------------------------------
	.byte		PAN   , c_v-12
	.byte		VOICE , 3
	.byte		MOD , 40
	.byte		LFOS , 1
	.byte		VOL   , 1*mus_outside_mvl/mxv
	.byte		TIE   , Cn4 , v068
mus_outside_4_B1:
	.byte	W96
	.byte	GOTO
	 .word	mus_outside_4_B1
mus_outside_4_B2:


@******************************************************@
	.align	2

mus_outside:
	.byte	2	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_outside_pri	@ Priority
	.byte	mus_outside_rev	@ Reverb.

	.word	mus_outside_grp

	.word	mus_outside_1
	.word	mus_outside_2

	.end
