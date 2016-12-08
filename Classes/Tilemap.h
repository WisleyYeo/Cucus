#pragma once
#include <iostream>
#include <vector>
enum TILEMAPS {
	L1_COLLIDE,
	L1_HEALTH,
	L1_SPEED,
	L1_STRENGTH,
	T_TOTAL
};
static const char* const TilemapFileName[T_TOTAL] = { "Tilemaps/Level1_Collide.tmx", "Tilemaps/Level1_Health.tmx", "Tilemaps/Level1_Speed.tmx", "Tilemaps/Level1_Strength.tmx" };
class Tilemap
{
	
public:
	Tilemap();
	~Tilemap();
};

