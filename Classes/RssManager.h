#pragma once
#include <iostream>
#include <vector>

enum RESOURCES {
	R_SOLDIERIDLE,
	R_SOLDIERUP,
	R_SOLDIERDOWN,
	R_SOLDIERLEFT,
	R_SOLDIERRIGHT,
	R_TOTAL
};
static const char* const ResourceFileName[R_TOTAL] = { "Characters/SoldierIdle.png", "Characters/SoldierUp.png", "Characters/SoldierDown.png", "Characters/SoldierLeft.png", "Characters/SoldierRight.png" };
class RssManager
{
	
public:
	RssManager();
	~RssManager();
};

