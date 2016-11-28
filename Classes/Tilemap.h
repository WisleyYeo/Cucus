#pragma once
#include <iostream>
#include <vector>
enum TILEMAPS {
	L1_COLLIDE,
	L1_COLLECT,
	T_TOTAL
};
static const char* const TilemapFileName[T_TOTAL] = { "Tilemaps/Level1_Collide.tmx", "Tilemaps/Level1_Collect.tmx" };
class Tilemap
{
	
public:
	Tilemap();
	~Tilemap();
};

