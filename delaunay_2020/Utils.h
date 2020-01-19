#pragma once

#include <iostream>
#include <vector>

#include "Vector2.h"

using namespace d20;

class Utils
{
public:
	static void printPointset(std::shared_ptr<std::vector<Vector2>> pointset)
	{
		for (const Vector2& vec : *pointset)
		{
			std::cout << "X: " << vec.x << ", Y: " << vec.y << std::endl;
		}	
	}
};
