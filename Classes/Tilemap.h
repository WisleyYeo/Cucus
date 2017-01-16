#pragma once
#include <iostream>
#include <vector>
enum TILEMAPS {
	L1_S1,
	L1_S2,
	L1_S3,
	L2_S1,
	L2_S2,
	L2_S3,
	L3_S1,
	L3_S2,
	L3_S3,
	T_TOTAL
};
static const char* const TilemapFileName[T_TOTAL] =
{
	"Tilemaps/Level1_Stage1.tmx", "Tilemaps/Level1_Stage2.tmx", "Tilemaps/Level1_Stage3.tmx",
	"Tilemaps/Level2_Stage1.tmx", "Tilemaps/Level2_Stage2.tmx", "Tilemaps/Level2_Stage3.tmx",
	"Tilemaps/Level3_Stage1.tmx", "Tilemaps/Level3_Stage2.tmx", "Tilemaps/Level3_Stage3.tmx"
};

class Tilemap
{

public:
	Tilemap();
	~Tilemap();
};

