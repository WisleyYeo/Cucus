#pragma once
#include <iostream>
#include <vector>
enum TILEMAPS {
	T_TEST,
	T_TOTAL
};
static const char* const TilemapFileName[T_TOTAL] = { "Tilemaps/Test.tmx" };
class Tilemap
{
	
public:
	Tilemap();
	~Tilemap();
};

