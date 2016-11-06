#pragma once
#include <iostream>
#include <vector>

enum RESOURCES {
	R_BLUEGEM,
	R_REDGEM,
	R_GREENGEM,
	R_PURPLEGEM,
	R_WHITEGEM,
	R_TOTAL
};
static const char* const ResourceFileName[R_TOTAL] = { "blue.png", "red.png", "green.png", "purple.png", "white.png" };
class RssManager
{
	
public:
	RssManager();
	~RssManager();
};

