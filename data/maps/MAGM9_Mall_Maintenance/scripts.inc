MAGM9_Mall_Maintenance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MAGM9_Mall_Maintenance_OnTransition
	.byte 0

MAGM9_Mall_Maintenance_OnTransition:
	setflashlevel 3
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
	.string "OBRESCOTT1988$"

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
	bufferstring STR_VAR_2, query_julienreverchon
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

research_paradeofgiants:
	.string "3/10/12\nParade of Giants\p" 
	.string "Many people look at celebrities\nas giants among us.\pBut in the city of Dallas, they take it...\nA bit more literally.\p"
	.string "The Parade of Giants is an annual event\ndisplaying music, puppets, floats,\land expressions of their culture!\p"
	.string "The puppets, known as the rolling giants,\nfeature historical figures who were\limportant to the history of Dallas.\pOne depiction is of “Julien Reverchon”,\na famous botanist.\pAlthough he passed in 1905, he will\nforever be immortalized in his puppet.$"

query_julienreverchon:
	.string "JULIENREVERCHON$"

research_julienreverchon:
	.string "(Assuming you meant “JULIEN REVERCHON”)\n" 
	.string "6/10/17\nJulien Reverchon - French Botanist.\p" 
	.string "A man who lived from 1837 to 1905.\p"
	.string "Julien was fairly instrumental to the\ncreation of the city of Dallas,\lcontributing via his research and\lteachings involving many new species\lof plants within the area.\pOne Dallas artist, a man named\nKevin Obregón (EMAIL: KevGon123),\lcreated a puppet for an event known as\lthe Parade of Giants.\pHere is a picture of that puppet:$"

research_julienreverchon2:
	.string "The puppet has been nicknamed as\nthe rolling giant by its fans, and could\lbe seen in Obregón's studio during\l2013-2016.\pUnfortunately, in recent times, the\npuppet has been demolished alongside\lmuch of the mall due to\lredevelopment plans.\pIt's unfortunate such an art piece\nhad to be lost.$"

query_kevgon123:
	.string "KEVGON123$"

research_kevgon123:
	.string "Email Database: KEVGON123\nRE: Acceptance\pThank you for accepting my request\nto open my studio in ValleyView!\pEver since I moved to Dallas in 1988,\nI've always dreamed of having my own\lstudio to teach my artistic methods!\pI will be moving my stuff into the mall\ntomorrow, so please look forward to it!\pAnyways, I am excited to contribute to\nthe evergrowing art community here\land maybe teach some history!$"

query_midtowndallas:
	.string "MIDTOWN DALLAS$"

research_midtowndallas:
	.string "6/10/17\nMidtown Dallas - The ambitious revamp\lfor the ValleyView Center.\pThe revamp has been in the works\nfor many years now, however, it's\lbeen delayed numerous times due to\lfinancial, communal, and complexity\nrelated issues.\pThe mall's current owner, “Beck\nVentures”, has revealed their plans to\lfinally begin demolition on the mall to\lmake room for new developments.\pThis is in part due to online shopping\nmaking many malls across the country\lobsolete, and ValleyView Mall is\lunfortunately no exception.$"

query_beckventures:
	.string "BECK VENTURES$"

research_beckventures:
	.string "1/1/24\nBeck Ventures - A Dallas realestate firm.\pJeffrey Beck founded the company 40\nyears ago, but in 2001, left the keys\lto the company to his son, Scott Beck.\pTheir most notorious project,\nknown as Dallas Midtown, has been in\lfairly early stages of development\lfor over a decade.$"


query_error:
	.string "ERROR CODE 404\nNo results for “{STR_VAR_1}.”$"

