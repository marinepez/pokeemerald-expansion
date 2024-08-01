.set TRACKS_OUTSIDE, 0x3 @ Hex code for bitmask: 0000 0000 0000 0011 (only changes tracks 1 and 2, which is the outside)
.set TRACKS_STAIRS,  0x4 @ Hex code for bitmask: 0000 0000 0000 1100 (only changes tracks 3 and 4, which is the stairway ambience)

MAGM9_StairsDown_MapScripts::
	.byte 0

Stairs_VolumeFade0::
	settrackvolume TRACKS_OUTSIDE, 46*4
	settrackvolume TRACKS_STAIRS, 1
	releaseall
	end

Stairs_VolumeFade1::
	settrackvolume TRACKS_OUTSIDE, 44*4
	settrackvolume TRACKS_STAIRS, 4*2
	releaseall
	end

Stairs_VolumeFade2::
	settrackvolume TRACKS_OUTSIDE, 42*4
	settrackvolume TRACKS_STAIRS, 4*4
	releaseall
	end

Stairs_VolumeFade3::
	settrackvolume TRACKS_OUTSIDE, 40*4
	settrackvolume TRACKS_STAIRS, 4*6
	releaseall
	end

Stairs_VolumeFade4::
	settrackvolume TRACKS_OUTSIDE, 38*4
	settrackvolume TRACKS_STAIRS, 4*8
	releaseall
	end

Stairs_VolumeFade5::
	settrackvolume TRACKS_OUTSIDE, 36*4
	settrackvolume TRACKS_STAIRS, 4*10
	releaseall
	end

Stairs_VolumeFade6::
	settrackvolume TRACKS_OUTSIDE, 34*4
	settrackvolume TRACKS_STAIRS, 4*12
	releaseall
	end

Stairs_VolumeFade7::
	settrackvolume TRACKS_OUTSIDE, 32*4
	settrackvolume TRACKS_STAIRS, 4*14
	releaseall
	end

Stairs_VolumeFade8::
	settrackvolume TRACKS_OUTSIDE, 30*4
	settrackvolume TRACKS_STAIRS, 4*16
	releaseall
	end

Stairs_VolumeFade9::
	settrackvolume TRACKS_OUTSIDE, 28*4
	settrackvolume TRACKS_STAIRS, 4*18
	releaseall
	end

Stairs_VolumeFade10::
	settrackvolume TRACKS_OUTSIDE, 26*4
	settrackvolume TRACKS_STAIRS, 4*20
	releaseall
	end

Stairs_VolumeFade11::
	settrackvolume TRACKS_OUTSIDE, 24*4
	settrackvolume TRACKS_STAIRS, 4*22
	releaseall
	end

Stairs_VolumeFade12::
	settrackvolume TRACKS_OUTSIDE, 22*4
	settrackvolume TRACKS_STAIRS, 4*24
	releaseall
	end

Stairs_VolumeFade13::
	settrackvolume TRACKS_OUTSIDE, 20*4
	settrackvolume TRACKS_STAIRS, 4*26
	releaseall
	end

Stairs_VolumeFade14::
	settrackvolume TRACKS_OUTSIDE, 18*4
	settrackvolume TRACKS_STAIRS, 4*28
	releaseall
	end

Stairs_VolumeFade15::
	settrackvolume TRACKS_OUTSIDE, 16*4
	settrackvolume TRACKS_STAIRS, 4*30
	releaseall
	end

Stairs_VolumeFade16::
	settrackvolume TRACKS_OUTSIDE, 14*4
	settrackvolume TRACKS_STAIRS, 4*32
	releaseall
	end

Stairs_VolumeFade17::
	settrackvolume TRACKS_OUTSIDE, 12*4
	settrackvolume TRACKS_STAIRS, 4*34
	releaseall
	end

Stairs_VolumeFade18::
	settrackvolume TRACKS_OUTSIDE, 10*4
	settrackvolume TRACKS_STAIRS, 4*36
	releaseall
	end

Stairs_VolumeFade19::
	settrackvolume TRACKS_OUTSIDE, 8*4
	settrackvolume TRACKS_STAIRS, 4*38

	releaseall
	end

Stairs_VolumeFade20::
	settrackvolume TRACKS_OUTSIDE, 6*4
	settrackvolume TRACKS_STAIRS, 4*40
	releaseall
	end

Stairs_VolumeFade21::
	settrackvolume TRACKS_OUTSIDE, 5*4
	settrackvolume TRACKS_STAIRS, 4*42
	releaseall
	end

Stairs_VolumeFade22::
	settrackvolume TRACKS_OUTSIDE, 4*4
	settrackvolume TRACKS_STAIRS, 4*44
	releaseall
	end

Stairs_VolumeFade23::
	settrackvolume TRACKS_OUTSIDE, 15
	settrackvolume TRACKS_STAIRS, 4*46
	releaseall
	end

Stairs_VolumeFade24::
	settrackvolume TRACKS_OUTSIDE, 13
	settrackvolume TRACKS_STAIRS, 4*48
	releaseall
	end

Stairs_VolumeFade25::
	settrackvolume TRACKS_OUTSIDE, 11
	settrackvolume TRACKS_STAIRS, 4*50
	releaseall
	end

Stairs_VolumeFade26::
	settrackvolume TRACKS_OUTSIDE, 8
	settrackvolume TRACKS_STAIRS, 4*52
	releaseall
	end

Stairs_VolumeFade27::
	settrackvolume TRACKS_OUTSIDE, 6
	settrackvolume TRACKS_STAIRS, 4*54
	releaseall
	end

Stairs_VolumeFade28::
	settrackvolume TRACKS_OUTSIDE, 4
	settrackvolume TRACKS_STAIRS, 4*56
	releaseall
	end

Stairs_VolumeFade29::
	settrackvolume TRACKS_OUTSIDE, 2
	settrackvolume TRACKS_STAIRS, 4*58
	releaseall
	end

Stairs_VolumeFade30::
	settrackvolume TRACKS_OUTSIDE, 1
	settrackvolume TRACKS_STAIRS, 4*60
	releaseall
	end
