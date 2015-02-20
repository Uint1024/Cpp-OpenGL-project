/*
 * Math.cpp

 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#include <iostream>
#include <glm.hpp>
#include "Math.h"

namespace math
{
	void PrintMatrice4Values(glm::mat4 mat4)
	{
		std::cout << std::endl;
		for(int y = 0 ; y < 4 ; ++y)
		{
			for(int x = 0 ; x < 4 ; ++x)
			{
				std::cout << mat4[x][y] << ";";
			}
			std::cout << std::endl;
		}
	}
}
