MAGM9_Mall_Maintenance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM9_Mall_Maintenance_OnTransition
	.byte 0

MAGM9_Mall_Maintenance_OnTransition:
	setflashlevel 3
	setvar VAR_FLASH_LAYER 1
	special SetFlashlightRevealLayer
	end

MAGM9_Mall_Maintenance_SetFlashLayer0::
	setvar VAR_FLASH_LAYER 0
	special SetFlashlightRevealLayer
	releaseall
	end

MAGM9_Mall_Maintenance_SetFlashLayer4::
	setvar VAR_FLASH_LAYER 5
	special SetFlashlightRevealLayer
	releaseall
	end

MAGM9_Mall_Maintenance_Book1::
	lock
	msgbox MAGM9_Mall_Maintenance_Text_Book1_Memo, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, MAGM9_Mall_Maintenance_Book1_ReadMemo
	case NO, MAGM9_Mall_Maintenance_Book1_End
	case MULTI_B_PRESSED, MAGM9_Mall_Maintenance_Book1_End
MAGM9_Mall_Maintenance_Book1_ReadMemo::
	msgbox MAGM9_Mall_Maintenance_Text_Book1, MSGBOX_SIGN
MAGM9_Mall_Maintenance_Book1_End::
	release
	end

MAGM9_Mall_Maintenance_Text_Book1_Memo:
	.string "Looks like an internal\nmemo. Read it?$"

MAGM9_Mall_Maintenance_Text_Book1:
	.string "Memo: Revitalizing ValleyView Mall\nStudio Spaces for Artists\pTeam,\nAs we all know, ValleyView Mall\lis currently facing significant\lchallenges with revenue.\pTo address this, we need to\ntake immediate action.\pThe recent success of the Giants\nParade has shown that there's\lstrong public interest in the arts.\pBy recruiting local artists to\nopen studios in our vacant spaces,\lwe can attract more visitors\land generate much-needed revenue.\pBest regards,\nManagement$"

MAGM9_Mall_Maintenance_Shelf::
	lock
	msgbox MAGM9_Mall_Maintenance_Text_Shelf, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, MAGM9_Mall_Maintenance_Book2_ReadMemo
	case NO, MAGM9_Mall_Maintenance_Book2_End
	case MULTI_B_PRESSED, MAGM9_Mall_Maintenance_Book2_End
MAGM9_Mall_Maintenance_Book2_ReadMemo::
	msgbox MAGM9_Mall_Maintenance_Text_Book2, MSGBOX_SIGN
MAGM9_Mall_Maintenance_Book2_End::
	release
	end

MAGM9_Mall_Maintenance_Text_Shelf:
	.string "The shelf is mostly empty,\nexcept for a dusty memo.\pRead it?$"

MAGM9_Mall_Maintenance_Text_Book2:
	.string "Memo: Safe Use Protocols\pDear Team,\nIt has come to our attention that\lsome of you may be unclear about\lthe purpose of the safe in the\lstorage area.\pLet me reiterate: this safe is\nreserved for items important to\lour resident artist, so\lplease leave it alone.\pThank you for your\ncooperation.\pBest regards,\nManagement$"

MAGM9_Mall_Maintenance_Phone::
	lock
	msgbox MAGM9_Mall_Maintenance_Text_Phone, MSGBOX_SIGN
	release
	end

MAGM9_Mall_Maintenance_Text_Phone:
	.string "Just dial-up noises.$"

MAGM9_Mall_Maintenance_FlickerLights::
	goto_if_eq VAR_TEMP_1, 1, MAGM9_Mall_Maintenance_FlickerLights_End
	setvar VAR_TEMP_1, 1
	lockall
	setflashalpha 3
	special UpdateFlashScanlines
	playse SE_SHIP
	delay 14
	setflashalpha 4
	special UpdateFlashScanlines
	delay 12
	setflashalpha 5
	special UpdateFlashScanlines
	delay 10
	setflashalpha 6
	special UpdateFlashScanlines
	delay 8
	setflashalpha 9
	special UpdateFlashScanlines
	delay 6
	setflashalpha 12
	special UpdateFlashScanlines
	delay 11
	setflashalpha 4
	special UpdateFlashScanlines
	delay 4
	setflashalpha 13
	special UpdateFlashScanlines
	delay 12
	setflashalpha 5
	special UpdateFlashScanlines
	delay 5
	setflashalpha 14
	special UpdateFlashScanlines
	waitse 
	releaseall
MAGM9_Mall_Maintenance_FlickerLights_End::
	end

MAGM9_Mall_Maintenance_Passcode_Guide::
	lock
	msgbox MAGM9_Mall_Maintenance_Passcode_GuideMsg, MSGBOX_SIGN
	release
	end

MAGM9_Mall_Maintenance_Passcode_GuideMsg:
	.string "TIPS FOR MAKING A GOOD PASSCODE:\pMix and match things about you\nand your personal life!\pFor example:\lFirst four letters of your last name.\lYour employer's first name.\lA year of great significance for you.$"

MAGM9_Mall_Maintenance_Safe::
	lockall
	special DoWaldaNamingScreen
	waitstate
	bufferstring STR_VAR_2, msg_passcode
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, FALSE, MAGM9_Mall_Maintenance_Safe_Wrong
	playse SE_TRUCK_DOOR
	delay 20
	giveitem ITEM_OAKS_PARCEL
	msgbox msg_test, MSGBOX_AUTOCLOSE
	releaseall
	end

MAGM9_Mall_Maintenance_Painting::
	lock
	msgbox MAGM9_Mall_Maintenance_PaintingMsg, MSGBOX_SIGN
	releaseall
	end

MAGM9_Mall_Maintenance_PaintingMsg:
	.string "It's a photograph of an artist\nstanding with a photorealistic statue.\pIt's pretty uncanny looking...$"

MAGM9_Mall_Maintenance_MidtownDallasRender::
	lock
	msgbox MAGM9_Mall_Maintenance_MidtownDallasRenderMsg, MSGBOX_SIGN
	releaseall
	end

MAGM9_Mall_Maintenance_MidtownDallasRenderMsg:
	.string "It's a rendering of a fancy\nbuilding on a corner.\pThe label says “Midtown Dallas”.$"

MAGM9_Mall_Maintenance_ParadeOfGiantsPhoto::
	lock
	msgbox MAGM9_Mall_Maintenance_ParadeOfGiantsPhotoMsg, MSGBOX_SIGN
	releaseall
	end

MAGM9_Mall_Maintenance_ParadeOfGiantsPhotoMsg:
	.string "It looks like a parade of some\nkind.\pThe label says “Giants Parade”$"


MAGM9_Mall_Maintenance_Safe_Wrong:
	playse SE_BOO
	releaseall
	end

msg_test:
	.string "{STR_VAR_1}.$"

msg_passcode:
	.string "OBRESCOTT2012$"

MAGM9_Mall_Maintenance_PCs::
	playse SE_PC_LOGIN
	lockall
	messageinstant MAGM9_Mall_Maintenance_PC_Research
	waitbuttonpress
	special DoWaldaNamingScreen
	waitstate
	bufferstring STR_VAR_2, query_paradeofgiants
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ParadeOfGiants
	bufferstring STR_VAR_2, query_paradeofgiants2
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ParadeOfGiants
	bufferstring STR_VAR_2, query_paradeofgiants3
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ParadeOfGiants
	bufferstring STR_VAR_2, query_paradeofgiants4
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ParadeOfGiants
	bufferstring STR_VAR_2, query_paradeofgiants5
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ParadeOfGiants
	bufferstring STR_VAR_2, query_julienreverchon
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_JulienReverchon
	bufferstring STR_VAR_2, query_julienreverchon2
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_JulienReverchon
	bufferstring STR_VAR_2, query_julienreverchon3
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_JulienReverchon
	bufferstring STR_VAR_2, query_kevgon123
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_KevGon123
	bufferstring STR_VAR_2, query_midtowndallas
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_MidtownDallas
	bufferstring STR_VAR_2, query_beckventures
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_BeckVentures
	bufferstring STR_VAR_2, query_beckventures2
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_BeckVentures
	bufferstring STR_VAR_2, query_ValleyViewCenter
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ValleyViewMall
	bufferstring STR_VAR_2, query_ValleyViewCenter2
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ValleyViewMall
	bufferstring STR_VAR_2, query_ValleyViewCenter3
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ValleyViewMall
	bufferstring STR_VAR_2, query_ValleyViewCenter4
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ValleyViewMall
	bufferstring STR_VAR_2, query_ValleyViewCenter5
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ValleyViewMall
	bufferstring STR_VAR_2, query_ValleyViewCenter6
	special CapitalizeAndCompareString
	goto_if_eq VAR_RESULT, TRUE, MAGM9_Mall_Maintenance_PCs_ValleyViewMall
	playse SE_BOO
	releaseall
	end

MAGM9_Mall_Maintenance_PCs_ParadeOfGiants:
	playse SE_PC_LOGIN
	msgbox research_paradeofgiants, MSGBOX_DEFAULT
	releaseall
	end

MAGM9_Mall_Maintenance_PCs_JulienReverchon:
	playse SE_PC_LOGIN
	msgbox research_julienreverchon, MSGBOX_DEFAULT
	showmonpic SPECIES_ROLLING_GIANT, 10, 3
	delay 40
	msgbox research_julienreverchon2, MSGBOX_DEFAULT
	hidemonpic
	releaseall
	end

MAGM9_Mall_Maintenance_PCs_KevGon123:
	playse SE_PC_LOGIN
	msgbox research_kevgon123, MSGBOX_DEFAULT
	releaseall
	end

MAGM9_Mall_Maintenance_PCs_MidtownDallas:
	playse SE_PC_LOGIN
	msgbox research_midtowndallas, MSGBOX_DEFAULT
	releaseall
	end

MAGM9_Mall_Maintenance_PCs_ValleyViewMall:
	playse SE_PC_LOGIN
	msgbox research_valleyviewmall, MSGBOX_DEFAULT
	releaseall
	end

MAGM9_Mall_Maintenance_PCs_BeckVentures:
	playse SE_PC_LOGIN
	msgbox research_beckventures, MSGBOX_DEFAULT
	releaseall
	end

MAGM9_Mall_Maintenance_NoResultFound:
	msgbox query_error, MSGBOX_DEFAULT
	releaseall
	end

MAGM9_Mall_Maintenance_PC_Research:
	.string "Please input a topic to research into\nthe search query.$"

query_paradeofgiants:
	.string "GIANTS PARADE$"

query_paradeofgiants2:
	.string "GIANTSPARADE$"

query_paradeofgiants3:
	.string "ROLLING GIANT$"

query_paradeofgiants4:
	.string "ROLLINGGIANT$"

query_paradeofgiants5:
	.string "PARADEOFGIANTS$"

research_paradeofgiants:
	.string "3/10/12\nParade of Giants\p" 
	.string "Many people look at celebrities\nas giants among us.\pBut in the city of Dallas, they take it...\nA bit more literally.\p"
	.string "The Parade of Giants is an annual event\ndisplaying music, puppets, floats,\land expressions of their culture!\p"
	.string "The puppets, known as the rolling giants,\nfeature historical figures who were\limportant to the history of Dallas.\pOne depiction is of “JulienReverchon”,\na famous botanist.\pAlthough he passed in the\nearly 1900s, he will forever be\limmortalized in his puppet.$"

query_julienreverchon:
	.string "JULIENREVERCHON$"

query_julienreverchon2:
	.string "JULIEN REVERCHO$"

query_julienreverchon3:
	.string "JULIEN$"

research_julienreverchon:
	.string "(Assuming you meant “JULIEN REVERCHON”)\n" 
	.string "Julien Reverchon - French Botanist.\p" 
	.string "A man from the 19th century.\p"
	.string "Julien was fairly instrumental to the\ncreation of the city of Dallas,\lcontributing via his research and\lteachings involving many new species\lof plants within the area.\pOne Dallas artist, a man named\nKevin Obregón (EMAIL: KevGon123),\lcreated a puppet for an event known as\lthe Parade of Giants.\pHere is a picture of that puppet:$"

research_julienreverchon2:
	.string "The puppet has been nicknamed as\nthe rolling giant by its fans, and could\lbe seen in Obregón's studio\lafter the 2012 parade.\pUnfortunately, in recent times, the\npuppet has been demolished alongside\lmuch of the mall due to\lredevelopment plans.\pIt's unfortunate such an art piece\nhad to be lost.$"

query_kevgon123:
	.string "KEVGON123$"

research_kevgon123:
	.string "Email Database: KEVGON123\nRE: Acceptance\pThank you for accepting my request\nto open my studio in ValleyView!\pEver since I moved to Dallas,\nI've always dreamed of having my own\lstudio!\pAs we discussed earlier, I'll move\nmy stuff into the mall tomorrow, so\lplease have a safe ready for me to store\lwhat we talked about.\pAnyways, I am excited to contribute to\nthe evergrowing art community here\land maybe teach some history!$"

query_midtowndallas:
	.string "MIDTOWN DALLAS$"

research_midtowndallas:
	.string "Midtown Dallas - The ambitious revamp\nfor the ValleyView Center.\pThe revamp has been in the works\nfor many years now, however, it's\lbeen delayed numerous times due to\lfinancial, communal, and complexity\nrelated issues.\pThe mall's current owner, “Beck\nVentures”, has revealed their plans to\lfinally begin demolition on the mall to\lmake room for new developments.\pThis is in part due to online shopping\nmaking many malls across the country\lobsolete, and ValleyView Mall is\lunfortunately no exception.$"

query_ValleyViewCenter:
	.string "VALLEYVIEW CENTER$"

query_ValleyViewCenter2:
	.string "VALLEYVIEWCENTER$"

query_ValleyViewCenter3:
	.string "VALLEYVIEW$"

query_ValleyViewCenter4:
	.string "VALLEY VIEW$"

query_ValleyViewCenter5:
	.string "WHERE AM I$"

query_ValleyViewCenter6:
	.string "WHERE AM I?$"

research_valleyviewmall:
	.string "Valley View Center is a former mall\nlocated at Interstate 635 and Preston Road\lin north Dallas, Texas, U.S.\pOwned and managed by “Beck Ventures”,\nthe demolition of the mall was\lcompleted in May 2023.\pPrior to it's demolition, the mall\nwas home to an annual event\lknown as the “Giant's Parade”.$"

query_beckventures:
	.string "BECK VENTURES$"

query_beckventures2:
	.string "OWNER"

research_beckventures:
	.string "Beck Ventures - A Dallas realestate firm.\pJeffrey Beck founded the company 40\nyears ago, but in 2001, left the keys\lto the company to his son, Scott Beck.\pTheir most notorious project,\nknown as Dallas Midtown, has been in\lfairly early stages of development\lfor over a decade.$"


query_error:
	.string "ERROR CODE 404\nNo results for “{STR_VAR_1}.”$"

