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
static const char* const ResourceFileName[R_TOTAL] = { "Characters/JaronIdle.png", "Characters/JaronUp.png", "Characters/JaronDown.png", "Characters/JaronLeft.png", "Characters/JaronRight.png" };
class RssManager
{
	
public:
	RssManager();
	~RssManager();
};

