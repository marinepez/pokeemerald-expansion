static const union AnimCmd sAnim_StayStill[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceSouth[] =
{
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceNorth[] =
{
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceWest[] =
{
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceEast[] =
{
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoSouth[] =
{
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(3, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoNorth[] =
{
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(4, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoWest[] =
{
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoEast[] =
{
    ANIMCMD_FRAME(5, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastSouth[] =
{
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastNorth[] =
{
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(4, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastWest[] =
{
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastEast[] =
{
    ANIMCMD_FRAME(5, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterSouth[] =
{
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(3, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterNorth[] =
{
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(4, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterWest[] =
{
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterEast[] =
{
    ANIMCMD_FRAME(5, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestSouth[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(3, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestNorth[] =
{
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(4, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestWest[] =
{
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestEast[] =
{
    ANIMCMD_FRAME(5, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceSouth[] =
{
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceNorth[] =
{
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceWest[] =
{
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceEast[] =
{
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoSouth[] =
{
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoNorth[] =
{
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoWest[] =
{
    ANIMCMD_FRAME(7, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(8, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoEast[] =
{
    ANIMCMD_FRAME(7, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastSouth[] =
{
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastNorth[] =
{
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastWest[] =
{
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastEast[] =
{
    ANIMCMD_FRAME(7, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterSouth[] =
{
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterNorth[] =
{
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterWest[] =
{
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterEast[] =
{
    ANIMCMD_FRAME(7, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestSouth[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestNorth[] =
{
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestWest[] =
{
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestEast[] =
{
    ANIMCMD_FRAME(7, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunSouth[] =
{
    ANIMCMD_FRAME(12, 5),
    ANIMCMD_FRAME(9, 3),
    ANIMCMD_FRAME(13, 5),
    ANIMCMD_FRAME(9, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunNorth[] =
{
    ANIMCMD_FRAME(14, 5),
    ANIMCMD_FRAME(10, 3),
    ANIMCMD_FRAME(15, 5),
    ANIMCMD_FRAME(10, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunWest[] =
{
    ANIMCMD_FRAME(16, 5),
    ANIMCMD_FRAME(11, 3),
    ANIMCMD_FRAME(17, 5),
    ANIMCMD_FRAME(11, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunEast[] =
{
    ANIMCMD_FRAME(16, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(17, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 3, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FieldMove[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_GetOnOffSurfBlobSouth[] =
{
    ANIMCMD_FRAME(9, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobNorth[] =
{
    ANIMCMD_FRAME(10, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobWest[] =
{
    ANIMCMD_FRAME(11, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobEast[] =
{
    ANIMCMD_FRAME(11, 32, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_BunnyHopBackWheelSouth[] =
{
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelNorth[] =
{
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelWest[] =
{
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelEast[] =
{
    ANIMCMD_FRAME(17, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelSouth[] =
{
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelNorth[] =
{
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelWest[] =
{
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelEast[] =
{
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(20, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelSouth[] =
{
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelNorth[] =
{
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelWest[] =
{
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelEast[] =
{
    ANIMCMD_FRAME(17, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelSouth[] =
{
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelNorth[] =
{
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelWest[] =
{
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelEast[] =
{
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MovingWheelieSouth[] =
{
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(22, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieNorth[] =
{
    ANIMCMD_FRAME(23, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieWest[] =
{
    ANIMCMD_FRAME(25, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_FRAME(26, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieEast[] =
{
    ANIMCMD_FRAME(25, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(26, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_BerryTreeStage0[] =
{
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage1[] =
{
    ANIMCMD_FRAME(1, 32),
    ANIMCMD_FRAME(2, 32),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage2[] =
{
    ANIMCMD_FRAME(3, 48),
    ANIMCMD_FRAME(4, 48),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage3[] =
{
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage4[] =
{
    ANIMCMD_FRAME(7, 48),
    ANIMCMD_FRAME(7, 48),
    ANIMCMD_FRAME(8, 48),
    ANIMCMD_FRAME(8, 48),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_NurseBow[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(9, 32),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_RockBreak[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TreeCut[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodSouth[] =
{
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodNorth[] =
{
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodWest[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodEast[] =
{
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodSouth[] =
{
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(10, 6),
    ANIMCMD_FRAME(9, 6),
    ANIMCMD_FRAME(8, 6),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodNorth[] =
{
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(6, 6),
    ANIMCMD_FRAME(5, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodWest[] =
{
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodEast[] =
{
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_HookedPokemonSouth[] =
{
    ANIMCMD_FRAME(10, 6),
    ANIMCMD_FRAME(11, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(11, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonNorth[] =
{
    ANIMCMD_FRAME(6, 6),
    ANIMCMD_FRAME(7, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(7, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonWest[] =
{
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(3, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonEast[] =
{
    ANIMCMD_FRAME(2, 6, .hFlip = TRUE),
    ANIMCMD_FRAME(3, 6, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(3, 30, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AffineAnimCmd sAffineAnim_KyogreGroudon_GoSouthStart[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 1, 1),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 1),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 1),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 1),
    AFFINEANIMCMD_LOOP(7),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd sAffineAnim_KyogreGroudon_GoSouth[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -1, 1),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 1),
    AFFINEANIMCMD_LOOP(15),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 1, 1),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 1),
    AFFINEANIMCMD_LOOP(15),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd sAffineAnim_KyogreGroudon_AttackEast[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 10, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_KyogreGroudon_AttackWest[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 10, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_KyogreGroudon_DipEast[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -1, 1),
    AFFINEANIMCMD_LOOP(8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_KyogreGroudon_DipWest[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 1, 1),
    AFFINEANIMCMD_LOOP(8),
    AFFINEANIMCMD_END,
};

static const union AnimCmd sAnim_HoOhFlapWings[] =
{
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HoOhStayStill[] =
{
    ANIMCMD_FRAME(3, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Inanimate[] = {
    [ANIM_STAY_STILL] = sAnim_StayStill,
};

static const union AnimCmd *const sAnimTable_QuintyPlump[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_QuintyPlumpFaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_QuintyPlumpFaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_QuintyPlumpFaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_QuintyPlumpFaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_QuintyPlumpGoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_QuintyPlumpGoNorth,
    [ANIM_STD_GO_WEST] = sAnim_QuintyPlumpGoWest,
    [ANIM_STD_GO_EAST] = sAnim_QuintyPlumpGoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_QuintyPlumpGoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_QuintyPlumpGoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_QuintyPlumpGoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_QuintyPlumpGoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_QuintyPlumpGoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_QuintyPlumpGoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_QuintyPlumpGoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_QuintyPlumpGoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_QuintyPlumpGoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_QuintyPlumpGoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_QuintyPlumpGoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_QuintyPlumpGoFastestEast,
};

static const union AnimCmd sAnim_FaceSouthwest[] =
{
    ANIMCMD_FRAME(9, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceSoutheast[] =
{
    ANIMCMD_FRAME(9, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceNorthwest[] =
{
    ANIMCMD_FRAME(10, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceNortheast[] =
{
    ANIMCMD_FRAME(10, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoSouthwest[] =
{
    ANIMCMD_FRAME(11, 8),
    ANIMCMD_FRAME(9, 8),
    ANIMCMD_FRAME(12, 8),
    ANIMCMD_FRAME(9, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoSoutheast[] =
{
    ANIMCMD_FRAME(11, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoNorthwest[] =
{
    ANIMCMD_FRAME(13, 8),
    ANIMCMD_FRAME(10, 8),
    ANIMCMD_FRAME(14, 8),
    ANIMCMD_FRAME(10, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoNortheast[] =
{
    ANIMCMD_FRAME(13, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastSouthwest[] =
{
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastSoutheast[] =
{
    ANIMCMD_FRAME(11, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastNorthwest[] =
{
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastNortheast[] =
{
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterSouthwest[] =
{
    ANIMCMD_FRAME(11, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_FRAME(12, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterSoutheast[] =
{
    ANIMCMD_FRAME(11, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterNorthwest[] =
{
    ANIMCMD_FRAME(13, 2),
    ANIMCMD_FRAME(10, 2),
    ANIMCMD_FRAME(14, 2),
    ANIMCMD_FRAME(10, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterNortheast[] =
{
    ANIMCMD_FRAME(13, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Standard[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_STD_FACE_SOUTHWEST] = sAnim_FaceSouth,
    [ANIM_STD_FACE_SOUTHEAST] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTHWEST] = sAnim_FaceNorth,
    [ANIM_STD_FACE_NORTHEAST] = sAnim_FaceNorth,
    [ANIM_STD_GO_SOUTHWEST] = sAnim_GoSouth,
    [ANIM_STD_GO_SOUTHEAST] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTHWEST] = sAnim_GoNorth,
    [ANIM_STD_GO_NORTHEAST] = sAnim_GoNorth,
    [ANIM_STD_GO_FAST_SOUTHWEST] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_SOUTHEAST] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTHWEST] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_NORTHEAST] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FASTER_SOUTHWEST] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_SOUTHEAST] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTHWEST] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_NORTHEAST] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTEST_SOUTHWEST] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_SOUTHEAST] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTHWEST] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_NORTHEAST] = sAnim_GoFastestNorth,
};

static const union AnimCmd sAnim_Diagonal_FaceSouthwest[] =
{
    ANIMCMD_FRAME(9, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_FaceSoutheast[] =
{
    ANIMCMD_FRAME(9, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_FaceNorthwest[] =
{
    ANIMCMD_FRAME(10, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_FaceNortheast[] =
{
    ANIMCMD_FRAME(10, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoSouthwest[] =
{
    ANIMCMD_FRAME(11, 8),
    ANIMCMD_FRAME(9, 8),
    ANIMCMD_FRAME(12, 8),
    ANIMCMD_FRAME(9, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoSoutheast[] =
{
    ANIMCMD_FRAME(11, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoNorthwest[] =
{
    ANIMCMD_FRAME(13, 8),
    ANIMCMD_FRAME(10, 8),
    ANIMCMD_FRAME(14, 8),
    ANIMCMD_FRAME(10, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoNortheast[] =
{
    ANIMCMD_FRAME(13, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastSouthwest[] =
{
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastSoutheast[] =
{
    ANIMCMD_FRAME(11, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastNorthwest[] =
{
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastNortheast[] =
{
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFasterSouthwest[] =
{
    ANIMCMD_FRAME(11, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_FRAME(12, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFasterSoutheast[] =
{
    ANIMCMD_FRAME(11, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFasterNorthwest[] =
{
    ANIMCMD_FRAME(13, 2),
    ANIMCMD_FRAME(10, 2),
    ANIMCMD_FRAME(14, 2),
    ANIMCMD_FRAME(10, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFasterNortheast[] =
{
    ANIMCMD_FRAME(13, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastestSouthwest[] =
{
    ANIMCMD_FRAME(11, 1),
    ANIMCMD_FRAME(9, 1),
    ANIMCMD_FRAME(12, 1),
    ANIMCMD_FRAME(9, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastestSoutheast[] =
{
    ANIMCMD_FRAME(11, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(9, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastestNorthwest[] =
{
    ANIMCMD_FRAME(13, 1),
    ANIMCMD_FRAME(10, 1),
    ANIMCMD_FRAME(14, 1),
    ANIMCMD_FRAME(10, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Diagonal_GoFastestNortheast[] =
{
    ANIMCMD_FRAME(13, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(10, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Standard_Diagonal[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_STD_FACE_SOUTHWEST] = sAnim_Diagonal_FaceSouthwest,
    [ANIM_STD_FACE_SOUTHEAST] = sAnim_Diagonal_FaceSoutheast,
    [ANIM_STD_FACE_NORTHWEST] = sAnim_Diagonal_FaceNorthwest,
    [ANIM_STD_FACE_NORTHEAST] = sAnim_Diagonal_FaceNortheast,
    [ANIM_STD_GO_SOUTHWEST] = sAnim_Diagonal_GoSouthwest,
    [ANIM_STD_GO_SOUTHEAST] = sAnim_Diagonal_GoSoutheast,
    [ANIM_STD_GO_NORTHWEST] = sAnim_Diagonal_GoNorthwest,
    [ANIM_STD_GO_NORTHEAST] = sAnim_Diagonal_GoNortheast,
    [ANIM_STD_GO_FAST_SOUTHWEST] = sAnim_Diagonal_GoFastSouthwest,
    [ANIM_STD_GO_FAST_SOUTHEAST] = sAnim_Diagonal_GoFastSoutheast,
    [ANIM_STD_GO_FAST_NORTHWEST] = sAnim_Diagonal_GoFastNorthwest,
    [ANIM_STD_GO_FAST_NORTHEAST] = sAnim_Diagonal_GoFastNortheast,
    [ANIM_STD_GO_FASTER_SOUTHWEST] = sAnim_Diagonal_GoFasterSouthwest,
    [ANIM_STD_GO_FASTER_SOUTHEAST] = sAnim_Diagonal_GoFasterSoutheast,
    [ANIM_STD_GO_FASTER_NORTHWEST] = sAnim_Diagonal_GoFasterNorthwest,
    [ANIM_STD_GO_FASTER_NORTHEAST] = sAnim_Diagonal_GoFasterNortheast,
    [ANIM_STD_GO_FASTEST_SOUTHWEST] = sAnim_Diagonal_GoFastestSouthwest,
    [ANIM_STD_GO_FASTEST_SOUTHEAST] = sAnim_Diagonal_GoFastestSoutheast,
    [ANIM_STD_GO_FASTEST_NORTHWEST] = sAnim_Diagonal_GoFastestNorthwest,
    [ANIM_STD_GO_FASTEST_NORTHEAST] = sAnim_Diagonal_GoFastestNortheast,
};

static const union AnimCmd *const sAnimTable_HoOh[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_HoOhFlapWings,
    [ANIM_STD_GO_NORTH] = sAnim_HoOhStayStill,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
};

// The movements for going up use the animations for going right instead.
static const union AnimCmd *const sAnimTable_GroudonSide[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoEast,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastEast,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestEast,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
};

static const union AnimCmd sAnim_RayquazaCoiledAwake[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RayquazaFlyUp[] =
{
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RayquazaCoiledAsleep[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RayquazaCoiledMouthOpen[] =
{
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RayquazaNormal[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_JUMP(0),
};

// Identical to sAnim_RayquazaCoiledAsleep
static const union AnimCmd sAnim_RayquazaFaceSouth[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

// Identical to sAnim_RayquazaCoiledAsleep
static const union AnimCmd sAnim_RayquazaFaceNorth[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

// Identical to sAnim_RayquazaCoiledAsleep
static const union AnimCmd sAnim_RayquazaFaceWest[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

// Identical to sAnim_RayquazaNormal
static const union AnimCmd sAnim_RayquazaFaceEast[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_JUMP(0),
};

// Though they correspond to facing/walking movements, Rayquaza doesn't have
// equivalent images aside from flying up. Its other frames aside from the 'normal'
// frame are for the sequence where it awakens on Sky Pillar.
static const union AnimCmd *const sAnimTable_Rayquaza[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_RayquazaFaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_RayquazaFaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_RayquazaFaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_RayquazaFaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_RayquazaCoiledAsleep,
    [ANIM_STD_GO_NORTH] = sAnim_RayquazaFlyUp,
    [ANIM_STD_GO_WEST] = sAnim_RayquazaCoiledMouthOpen,
    [ANIM_STD_GO_EAST] = sAnim_RayquazaNormal,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_RayquazaCoiledAsleep,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_RayquazaFlyUp,
    [ANIM_STD_GO_FAST_WEST] = sAnim_RayquazaCoiledAwake,
    [ANIM_STD_GO_FAST_EAST] = sAnim_RayquazaNormal,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_RayquazaCoiledAsleep,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_RayquazaFlyUp,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_RayquazaCoiledMouthOpen,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_RayquazaNormal,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_RayquazaCoiledAsleep,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_RayquazaFlyUp,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_RayquazaCoiledMouthOpen,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_RayquazaNormal,
};

static const union AnimCmd sAnim_OnFoot_FaceSouthwest[] =
{
    ANIMCMD_FRAME(18, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_FaceSoutheast[] =
{
    ANIMCMD_FRAME(18, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_FaceNorthwest[] =
{
    ANIMCMD_FRAME(19, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_FaceNortheast[] =
{
    ANIMCMD_FRAME(19, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoSouthwest[] =
{
    ANIMCMD_FRAME(20, 8),
    ANIMCMD_FRAME(18, 8),
    ANIMCMD_FRAME(21, 8),
    ANIMCMD_FRAME(18, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoSoutheast[] =
{
    ANIMCMD_FRAME(20, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(21, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoNorthwest[] =
{
    ANIMCMD_FRAME(22, 8),
    ANIMCMD_FRAME(19, 8),
    ANIMCMD_FRAME(23, 8),
    ANIMCMD_FRAME(19, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoNortheast[] =
{
    ANIMCMD_FRAME(22, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(23, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFastSouthwest[] =
{
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFastSoutheast[] =
{
    ANIMCMD_FRAME(20, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(21, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFastNorthwest[] =
{
    ANIMCMD_FRAME(22, 4),
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(23, 4),
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFastNortheast[] =
{
    ANIMCMD_FRAME(22, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(23, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFasterSouthwest[] =
{
    ANIMCMD_FRAME(20, 2),
    ANIMCMD_FRAME(18, 2),
    ANIMCMD_FRAME(21, 2),
    ANIMCMD_FRAME(18, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFasterSoutheast[] =
{
    ANIMCMD_FRAME(20, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(21, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFasterNorthwest[] =
{
    ANIMCMD_FRAME(22, 2),
    ANIMCMD_FRAME(19, 2),
    ANIMCMD_FRAME(23, 2),
    ANIMCMD_FRAME(19, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_OnFoot_GoFasterNortheast[] =
{
    ANIMCMD_FRAME(22, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(23, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunSouthwest[] =
{
    ANIMCMD_FRAME(26, 5),
    ANIMCMD_FRAME(24, 3),
    ANIMCMD_FRAME(27, 5),
    ANIMCMD_FRAME(24, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunSoutheast[] =
{
    ANIMCMD_FRAME(26, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(27, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 3, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunNorthwest[] =
{
    ANIMCMD_FRAME(28, 5),
    ANIMCMD_FRAME(25, 3),
    ANIMCMD_FRAME(29, 5),
    ANIMCMD_FRAME(25, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunNortheast[] =
{
    ANIMCMD_FRAME(28, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(25, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(29, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(25, 3, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_BrendanMayNormal[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_STD_FACE_SOUTHWEST] = sAnim_OnFoot_FaceSouthwest,
    [ANIM_STD_FACE_SOUTHEAST] = sAnim_OnFoot_FaceSoutheast,
    [ANIM_STD_FACE_NORTHWEST] = sAnim_OnFoot_FaceNorthwest,
    [ANIM_STD_FACE_NORTHEAST] = sAnim_OnFoot_FaceNortheast,
    [ANIM_STD_GO_SOUTHWEST] = sAnim_OnFoot_GoSouthwest,
    [ANIM_STD_GO_SOUTHEAST] = sAnim_OnFoot_GoSoutheast,
    [ANIM_STD_GO_NORTHWEST] = sAnim_OnFoot_GoNorthwest,
    [ANIM_STD_GO_NORTHEAST] = sAnim_OnFoot_GoNortheast,
    [ANIM_STD_GO_FAST_SOUTHWEST] = sAnim_OnFoot_GoFastSouthwest,
    [ANIM_STD_GO_FAST_SOUTHEAST] = sAnim_OnFoot_GoFastSoutheast,
    [ANIM_STD_GO_FAST_NORTHWEST] = sAnim_OnFoot_GoFastNorthwest,
    [ANIM_STD_GO_FAST_NORTHEAST] = sAnim_OnFoot_GoFastNortheast,
    [ANIM_STD_GO_FASTER_SOUTHWEST] = sAnim_OnFoot_GoFasterSouthwest,
    [ANIM_STD_GO_FASTER_SOUTHEAST] = sAnim_OnFoot_GoFasterSoutheast,
    [ANIM_STD_GO_FASTER_NORTHWEST] = sAnim_OnFoot_GoFasterNorthwest,
    [ANIM_STD_GO_FASTER_NORTHEAST] = sAnim_OnFoot_GoFasterNortheast,
    [ANIM_RUN_SOUTH] = sAnim_RunSouth,
    [ANIM_RUN_NORTH] = sAnim_RunNorth,
    [ANIM_RUN_WEST] = sAnim_RunWest,
    [ANIM_RUN_EAST] = sAnim_RunEast,
    [ANIM_RUN_SOUTHWEST] = sAnim_RunSouthwest,
    [ANIM_RUN_SOUTHEAST] = sAnim_RunSoutheast,
    [ANIM_RUN_NORTHWEST] = sAnim_RunNorthwest,
    [ANIM_RUN_NORTHEAST] = sAnim_RunNortheast,
};

static const union AnimCmd sAnim_AcroBike_FaceSouthwest[] =
{
    ANIMCMD_FRAME(27, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_FaceSoutheast[] =
{
    ANIMCMD_FRAME(27, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_FaceNorthwest[] =
{
    ANIMCMD_FRAME(28, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_FaceNortheast[] =
{
    ANIMCMD_FRAME(28, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoSouthwest[] =
{
    ANIMCMD_FRAME(29, 8),
    ANIMCMD_FRAME(27, 8),
    ANIMCMD_FRAME(30, 8),
    ANIMCMD_FRAME(27, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoSoutheast[] =
{
    ANIMCMD_FRAME(29, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(27, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(30, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(27, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoNorthwest[] =
{
    ANIMCMD_FRAME(31, 8),
    ANIMCMD_FRAME(28, 8),
    ANIMCMD_FRAME(32, 8),
    ANIMCMD_FRAME(28, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoNortheast[] =
{
    ANIMCMD_FRAME(31, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(28, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(32, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(28, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoFastSouthwest[] =
{
    ANIMCMD_FRAME(29, 4),
    ANIMCMD_FRAME(27, 4),
    ANIMCMD_FRAME(30, 4),
    ANIMCMD_FRAME(27, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoFastSoutheast[] =
{
    ANIMCMD_FRAME(29, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(27, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(30, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(27, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoFastNorthwest[] =
{
    ANIMCMD_FRAME(31, 4),
    ANIMCMD_FRAME(28, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(28, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_AcroBike_GoFastNortheast[] =
{
    ANIMCMD_FRAME(31, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(28, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(32, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(28, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_BunnyHopBackWheelSouthwest[] =
{
    ANIMCMD_FRAME(33, 4),
    ANIMCMD_FRAME(34, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelSoutheast[] =
{
    ANIMCMD_FRAME(33, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(34, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelNorthwest[] =
{
    ANIMCMD_FRAME(35, 4),
    ANIMCMD_FRAME(36, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelNortheast[] =
{
    ANIMCMD_FRAME(35, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(36, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelSouthwest[] =
{
    ANIMCMD_FRAME(33, 4),
    ANIMCMD_FRAME(27, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelSoutheast[] =
{
    ANIMCMD_FRAME(33, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(27, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelNorthwest[] =
{
    ANIMCMD_FRAME(35, 4),
    ANIMCMD_FRAME(28, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelNortheast[] =
{
    ANIMCMD_FRAME(35, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(28, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MovingWheelieSouthwest[] =
{
    ANIMCMD_FRAME(37, 4),
    ANIMCMD_FRAME(34, 4),
    ANIMCMD_FRAME(38, 4),
    ANIMCMD_FRAME(34, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieSoutheast[] =
{
    ANIMCMD_FRAME(37, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(34, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(38, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(34, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieNorthwest[] =
{
    ANIMCMD_FRAME(39, 4),
    ANIMCMD_FRAME(36, 4),
    ANIMCMD_FRAME(40, 4),
    ANIMCMD_FRAME(36, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieNortheast[] =
{
    ANIMCMD_FRAME(39, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(36, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(40, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(36, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_AcroBike[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_STD_FACE_SOUTHWEST] = sAnim_AcroBike_FaceSouthwest,
    [ANIM_STD_FACE_SOUTHEAST] = sAnim_AcroBike_FaceSoutheast,
    [ANIM_STD_FACE_NORTHWEST] = sAnim_AcroBike_FaceNorthwest,
    [ANIM_STD_FACE_NORTHEAST] = sAnim_AcroBike_FaceNortheast,
    [ANIM_STD_GO_SOUTHWEST] = sAnim_AcroBike_GoSouthwest,
    [ANIM_STD_GO_SOUTHEAST] = sAnim_AcroBike_GoSoutheast,
    [ANIM_STD_GO_NORTHWEST] = sAnim_AcroBike_GoNorthwest,
    [ANIM_STD_GO_NORTHEAST] = sAnim_AcroBike_GoNortheast,
    [ANIM_STD_GO_FAST_SOUTHWEST] = sAnim_AcroBike_GoFastSouthwest,
    [ANIM_STD_GO_FAST_SOUTHEAST] = sAnim_AcroBike_GoFastSoutheast,
    [ANIM_STD_GO_FAST_NORTHWEST] = sAnim_AcroBike_GoFastNorthwest,
    [ANIM_STD_GO_FAST_NORTHEAST] = sAnim_AcroBike_GoFastNortheast,
    [ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH] = sAnim_BunnyHopBackWheelSouth,
    [ANIM_BUNNY_HOP_BACK_WHEEL_NORTH] = sAnim_BunnyHopBackWheelNorth,
    [ANIM_BUNNY_HOP_BACK_WHEEL_WEST] = sAnim_BunnyHopBackWheelWest,
    [ANIM_BUNNY_HOP_BACK_WHEEL_EAST] = sAnim_BunnyHopBackWheelEast,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH] = sAnim_BunnyHopFrontWheelSouth,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_NORTH] = sAnim_BunnyHopFrontWheelNorth,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_WEST] = sAnim_BunnyHopFrontWheelWest,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_EAST] = sAnim_BunnyHopFrontWheelEast,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH] = sAnim_StandingWheelieBackWheelSouth,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTH] = sAnim_StandingWheelieBackWheelNorth,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_WEST] = sAnim_StandingWheelieBackWheelWest,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_EAST] = sAnim_StandingWheelieBackWheelEast,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH] = sAnim_StandingWheelieFrontWheelSouth,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_NORTH] = sAnim_StandingWheelieFrontWheelNorth,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_WEST] = sAnim_StandingWheelieFrontWheelWest,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_EAST] = sAnim_StandingWheelieFrontWheelEast,
    [ANIM_MOVING_WHEELIE_SOUTH] = sAnim_MovingWheelieSouth,
    [ANIM_MOVING_WHEELIE_NORTH] = sAnim_MovingWheelieNorth,
    [ANIM_MOVING_WHEELIE_WEST] = sAnim_MovingWheelieWest,
    [ANIM_MOVING_WHEELIE_EAST] = sAnim_MovingWheelieEast,
    [ANIM_BUNNY_HOP_BACK_WHEEL_SOUTHWEST] = sAnim_BunnyHopBackWheelSouthwest,
    [ANIM_BUNNY_HOP_BACK_WHEEL_SOUTHEAST] = sAnim_BunnyHopBackWheelSoutheast,
    [ANIM_BUNNY_HOP_BACK_WHEEL_NORTHWEST] = sAnim_BunnyHopBackWheelNorthwest,
    [ANIM_BUNNY_HOP_BACK_WHEEL_NORTHEAST] = sAnim_BunnyHopBackWheelNortheast,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTHWEST] = sAnim_StandingWheelieBackWheelSouthwest,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTHEAST] = sAnim_StandingWheelieBackWheelSoutheast,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTHWEST] = sAnim_StandingWheelieBackWheelNorthwest,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTHEAST] = sAnim_StandingWheelieBackWheelNortheast,
    [ANIM_MOVING_WHEELIE_SOUTHWEST] = sAnim_MovingWheelieSouthwest,
    [ANIM_MOVING_WHEELIE_SOUTHEAST] = sAnim_MovingWheelieSoutheast,
    [ANIM_MOVING_WHEELIE_NORTHWEST] = sAnim_MovingWheelieNorthwest,
    [ANIM_MOVING_WHEELIE_NORTHEAST] = sAnim_MovingWheelieNortheast,
};

static const union AnimCmd sAnim_Surfing_FaceSouthwest[] =
{
    ANIMCMD_FRAME(12, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_FaceSoutheast[] =
{
    ANIMCMD_FRAME(12, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_FaceNorthwest[] =
{
    ANIMCMD_FRAME(14, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_FaceNortheast[] =
{
    ANIMCMD_FRAME(14, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoSouthwest[] =
{
    ANIMCMD_FRAME(12, 8),
    ANIMCMD_FRAME(12, 8),
    ANIMCMD_FRAME(12, 8),
    ANIMCMD_FRAME(12, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoSoutheast[] =
{
    ANIMCMD_FRAME(12, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoNorthwest[] =
{
    ANIMCMD_FRAME(14, 8),
    ANIMCMD_FRAME(14, 8),
    ANIMCMD_FRAME(14, 8),
    ANIMCMD_FRAME(14, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoNortheast[] =
{
    ANIMCMD_FRAME(14, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoFastSouthwest[] =
{
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoFastSoutheast[] =
{
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoFastNorthwest[] =
{
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Surfing_GoFastNortheast[] =
{
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobSouthwest[] =
{
    ANIMCMD_FRAME(13, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobSoutheast[] =
{
    ANIMCMD_FRAME(13, 32, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobNorthwest[] =
{
    ANIMCMD_FRAME(15, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfBlobNortheast[] =
{
    ANIMCMD_FRAME(15, 32, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Surfing[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_STD_FACE_SOUTHWEST] = sAnim_Surfing_FaceSouthwest,
    [ANIM_STD_FACE_SOUTHEAST] = sAnim_Surfing_FaceSoutheast,
    [ANIM_STD_FACE_NORTHWEST] = sAnim_Surfing_FaceNorthwest,
    [ANIM_STD_FACE_NORTHEAST] = sAnim_Surfing_FaceNortheast,
    [ANIM_STD_GO_SOUTHWEST] = sAnim_Surfing_GoSouthwest,
    [ANIM_STD_GO_SOUTHEAST] = sAnim_Surfing_GoSoutheast,
    [ANIM_STD_GO_NORTHWEST] = sAnim_Surfing_GoNorthwest,
    [ANIM_STD_GO_NORTHEAST] = sAnim_Surfing_GoNortheast,
    [ANIM_STD_GO_FAST_SOUTHWEST] = sAnim_Surfing_GoFastSouthwest,
    [ANIM_STD_GO_FAST_SOUTHEAST] = sAnim_Surfing_GoFastSoutheast,
    [ANIM_STD_GO_FAST_NORTHWEST] = sAnim_Surfing_GoFastNorthwest,
    [ANIM_STD_GO_FAST_NORTHEAST] = sAnim_Surfing_GoFastNortheast,
    [ANIM_GET_ON_OFF_POKEMON_SOUTH] = sAnim_GetOnOffSurfBlobSouth,
    [ANIM_GET_ON_OFF_POKEMON_NORTH] = sAnim_GetOnOffSurfBlobNorth,
    [ANIM_GET_ON_OFF_POKEMON_WEST] = sAnim_GetOnOffSurfBlobWest,
    [ANIM_GET_ON_OFF_POKEMON_EAST] = sAnim_GetOnOffSurfBlobEast,
    [ANIM_GET_ON_OFF_POKEMON_SOUTHWEST] = sAnim_GetOnOffSurfBlobSouthwest,
    [ANIM_GET_ON_OFF_POKEMON_SOUTHEAST] = sAnim_GetOnOffSurfBlobSoutheast,
    [ANIM_GET_ON_OFF_POKEMON_NORTHWEST] = sAnim_GetOnOffSurfBlobNorthwest,
    [ANIM_GET_ON_OFF_POKEMON_NORTHEAST] = sAnim_GetOnOffSurfBlobNortheast,
};

static const union AnimCmd *const sAnimTable_Nurse[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST]  = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST]  = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_NURSE_BOW] = sAnim_NurseBow,
};

static const union AnimCmd *const sAnimTable_FieldMove[] = {
    [ANIM_FIELD_MOVE] = sAnim_FieldMove,
};

static const union AnimCmd *const sAnimTable_BerryTree[] = {
    [BERRY_STAGE_PLANTED - 1] = sAnim_BerryTreeStage0,
    [BERRY_STAGE_SPROUTED - 1] = sAnim_BerryTreeStage1,
    [BERRY_STAGE_TALLER - 1] = sAnim_BerryTreeStage2,
    [BERRY_STAGE_TRUNK - 1] = sAnim_BerryTreeStage2,
    [BERRY_STAGE_BUDDING - 1] = sAnim_BerryTreeStage2,
    [BERRY_STAGE_FLOWERING - 1] = sAnim_BerryTreeStage3,
    [BERRY_STAGE_BERRIES - 1] = sAnim_BerryTreeStage4,
};

static const union AnimCmd *const sAnimTable_BreakableRock[] = {
    [ANIM_STAY_STILL] = sAnim_StayStill,
    [ANIM_REMOVE_OBSTACLE] = sAnim_RockBreak,
};

static const union AnimCmd *const sAnimTable_CuttableTree[] = {
    [ANIM_STAY_STILL] = sAnim_StayStill,
    [ANIM_REMOVE_OBSTACLE] = sAnim_TreeCut,
};

static const union AnimCmd sAnim_TakeOutRodSouthwest[] =
{
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodSoutheast[] =
{
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(15, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodNorthwest[] =
{
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodNortheast[] =
{
    ANIMCMD_FRAME(16, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(17, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodSouthwest[] =
{
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodSoutheast[] =
{
    ANIMCMD_FRAME(16, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(17, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodNorthwest[] =
{
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodNortheast[] =
{
    ANIMCMD_FRAME(19, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(18, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(17, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(16, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_HookedPokemonSouthwest[] =
{
    ANIMCMD_FRAME(14, 6),
    ANIMCMD_FRAME(15, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(15, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonSoutheast[] =
{
    ANIMCMD_FRAME(14, 6, .hFlip = TRUE),
    ANIMCMD_FRAME(15, 6, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(15, 30, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonNorthwest[] =
{
    ANIMCMD_FRAME(18, 6),
    ANIMCMD_FRAME(19, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(19, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonNortheast[] =
{
    ANIMCMD_FRAME(18, 6, .hFlip = TRUE),
    ANIMCMD_FRAME(19, 6, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(19, 30, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Fishing[] = {
    [ANIM_TAKE_OUT_ROD_SOUTH] = sAnim_TakeOutRodSouth,
    [ANIM_TAKE_OUT_ROD_NORTH] = sAnim_TakeOutRodNorth,
    [ANIM_TAKE_OUT_ROD_WEST] = sAnim_TakeOutRodWest,
    [ANIM_TAKE_OUT_ROD_EAST] = sAnim_TakeOutRodEast,
    [ANIM_PUT_AWAY_ROD_SOUTH] = sAnim_PutAwayRodSouth,
    [ANIM_PUT_AWAY_ROD_NORTH] = sAnim_PutAwayRodNorth,
    [ANIM_PUT_AWAY_ROD_WEST] = sAnim_PutAwayRodWest,
    [ANIM_PUT_AWAY_ROD_EAST] = sAnim_PutAwayRodEast,
    [ANIM_HOOKED_POKEMON_SOUTH] = sAnim_HookedPokemonSouth,
    [ANIM_HOOKED_POKEMON_NORTH] = sAnim_HookedPokemonNorth,
    [ANIM_HOOKED_POKEMON_WEST] = sAnim_HookedPokemonWest,
    [ANIM_HOOKED_POKEMON_EAST] = sAnim_HookedPokemonEast,
    [ANIM_TAKE_OUT_ROD_SOUTHWEST] = sAnim_TakeOutRodSouthwest,
    [ANIM_TAKE_OUT_ROD_SOUTHEAST] = sAnim_TakeOutRodSoutheast,
    [ANIM_TAKE_OUT_ROD_NORTHWEST] = sAnim_TakeOutRodNorthwest,
    [ANIM_TAKE_OUT_ROD_NORTHEAST] = sAnim_TakeOutRodNortheast,
    [ANIM_PUT_AWAY_ROD_SOUTHWEST] = sAnim_PutAwayRodSouthwest,
    [ANIM_PUT_AWAY_ROD_SOUTHEAST] = sAnim_PutAwayRodSoutheast,
    [ANIM_PUT_AWAY_ROD_NORTHWEST] = sAnim_PutAwayRodNorthwest,
    [ANIM_PUT_AWAY_ROD_NORTHEAST] = sAnim_PutAwayRodNortheast,
    [ANIM_HOOKED_POKEMON_SOUTHWEST] = sAnim_HookedPokemonSouthwest,
    [ANIM_HOOKED_POKEMON_SOUTHEAST] = sAnim_HookedPokemonSoutheast,
    [ANIM_HOOKED_POKEMON_NORTHWEST] = sAnim_HookedPokemonNorthwest,
    [ANIM_HOOKED_POKEMON_NORTHEAST] = sAnim_HookedPokemonNortheast,
};

static const union AffineAnimCmd *const sAffineAnimTable_KyogreGroudon[] = {
    sAffineAnim_KyogreGroudon_GoSouthStart, // Used by Kyogre/Groudon when awakened
    sAffineAnim_KyogreGroudon_GoSouth,      // Used by Kyogre/Groudon when awakened
    sAffineAnim_KyogreGroudon_AttackWest,   // Used by Kyogre during Sootopolis fight
    sAffineAnim_KyogreGroudon_AttackEast,   // Unused
    sAffineAnim_KyogreGroudon_DipWest,      // Unused
    sAffineAnim_KyogreGroudon_DipEast,      // Unused
};

// For animations with alternating steps
static const struct StepAnimTable sStepAnimTables[] = {
    {
        .anims = sAnimTable_QuintyPlump,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Standard,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Standard_Diagonal,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_BrendanMayNormal,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_AcroBike,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Surfing,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Nurse,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Fishing,
        .animPos = {1, 3, 0, 2},
    },
    {},
};
