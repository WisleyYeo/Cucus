#pragma once
#include <iostream>
#include <vector>
enum TILEMAPS {
	L1_S1,
	L1_S2,
	L1_S3,
	T_TOTAL
};
static const char* const TilemapFileName[T_TOTAL] = { "Tilemaps/Level1_Stage1.tmx", "Tilemaps/Level1_Stage2.tmx", "Tilemaps/Level1_Stage3.tmx" };
class Tilemap
{
	
public:
	Tilemap();
	~Tilemap();
};

