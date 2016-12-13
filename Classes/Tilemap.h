#pragma once
#include <iostream>
#include <vector>
enum TILEMAPS {
	L1_S1,
	T_TOTAL
};
static const char* const TilemapFileName[T_TOTAL] = { "Tilemaps/Level1_Stage1.tmx" };
class Tilemap
{
	
public:
	Tilemap();
	~Tilemap();
};

