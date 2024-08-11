MAGM9_StairsSide_MapScripts::
	.byte 0


MAGM9_StairsSide_Darken0::
setflashalpha 0
setflashlevel 0
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken1::
setflashalpha 2
setflashlevel 8
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken2::
setflashalpha 4
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken3::
setflashalpha 6
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken4::
setflashalpha 8
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken5::
setflashalpha 10
setflashlevel 8
clearflag FLAG_TEMP_1
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken6::
setflashalpha 11
setflashlevel 7
call_if_unset FLAG_TEMP_1, MAGM9_StairsSide_FlashlightSound
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken7::
setflashalpha 12
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_Darken8::
setflashalpha 14
goto MAGM9_StairsSide_UpdateFlash

MAGM9_StairsSide_UpdateFlash:
special UpdateFlashScanlines
releaseall
end

MAGM9_StairsSide_FlashlightSound:
playse SE_CLICK
setflag FLAG_TEMP_1
return

Test::
playse SE_PIN
releaseall
end

