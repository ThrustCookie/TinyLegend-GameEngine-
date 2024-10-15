#include "Engine.h"
#include "CemiUtils.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <string> // debugging purposes only

namespace engine {
	
	void draw_screen(display camera, map currentMap) {
		//calculate all obj actually in view of camera
		//store into the object array that gets processed

		std::vector<objectStatic> staticObjectList = currentMap.merge_listObjectStatic();

		// print camera
		vector2i currentPixel = camera.start();
		for (; currentPixel.y < camera.end().y; currentPixel.y++) {
			for (; currentPixel.x < camera.end().x; currentPixel.x++) {
				int colour = calculate_pixel_colour(currentPixel, staticObjectList);
				(colour >= 0) ? set_pixel(currentPixel, colour) : set_pixel(currentPixel, camera.bg_colour);
				std::cout << "  ";
			}

			currentPixel.x = 0;
			utils::colour_bg(0); // this has to be done with current colour type

			std::cout << std::endl;
		}
	}
	int calculate_pixel_colour(vector2i pixel, std::vector<objectStatic> objectList) {

		for (int i = 0; i < objectList.size(); i++) {
			vector2i topLeft = objectList[i].start();
			vector2i bottomRight = objectList[i].end();

			if (topLeft.AND_Lesser(pixel) && bottomRight.AND_Greater(pixel)) {
				image image = objectList.at(i).sprite;

				vector2i imageIndex; 
				{
					vector2i distanceFromObject = (pixel.subtract(topLeft));
					int repetitionCap;

					repetitionCap = image.imageMatrix.size();
					imageIndex.y = distanceFromObject.y % repetitionCap;

					repetitionCap = image.imageMatrix[imageIndex.y].size();
					imageIndex.x = distanceFromObject.x % repetitionCap;
				}
				return image.imageMatrix[imageIndex.y][imageIndex.x];
			}
		}
		return -1;
	}
	void set_pixel(vector2i pixel, int colourIndex) {
		//unused pixel variable to set
		utils::colour_bg(colourIndex);
	}

	void draw_UI() {
		for (int i = 0; i < 16; i++) {
			if (i % (16 / 2) == 0) std::cout << std::endl;
			utils::colour_bg(i);
			std::cout << "  ";
		}
		utils::colour(7);
	}

	void calculate_movement(std::vector<objectDynamic>& dynamicObjectList, std::vector<entity>& entityList) {
		for (int i = 0; i < dynamicObjectList.size(); i++) {
			vector2i movementDirection = dynamicObjectList[i].direction.multiply(dynamicObjectList[i].speed);

			dynamicObjectList[i].position = dynamicObjectList[i].position.add(movementDirection);
		}
		for (int i = 0; i < entityList.size(); i++) {
			vector2i movementDirection = entityList[i].direction.multiply(entityList[i].speed);

			entityList[i].position = entityList[i].position.add(movementDirection);
		}
	}
}