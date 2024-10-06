#include "Engine.h"
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
				(colour >= 0) ? colour_bg(colour) : colour_bg(camera.bg_colour);
				std::cout << "  ";
			}
			currentPixel.x = 0;
			colour_bg(0);
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

	void draw_UI() {
		for (int i = 0; i < 16; i++) {
			if (i % (16 / 2) == 0) std::cout << std::endl;
			colour_bg(i);
			std::cout << "  ";
		}
		colour(7);
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

	void colour(int colourIndex) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colourIndex);
	}
	void colour_bg(int colourIndex) {
		switch (colourIndex) {
		case 0:  colour(0); break;                                                                          	//black
		case 1:  colour(BACKGROUND_BLUE); break;                                                              	//blue
		case 2:  colour(BACKGROUND_GREEN); break;                                                          	//green
		case 3:  colour(BACKGROUND_BLUE | BACKGROUND_GREEN); break;                                          	//cyan
		case 4:  colour(BACKGROUND_RED); break;                                                              	//red
		case 5:  colour(BACKGROUND_RED | BACKGROUND_BLUE); break;                                          	//purple
		case 6:  colour(BACKGROUND_RED | BACKGROUND_GREEN); break;                                          	//orange
		case 7:  colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); break;                          	//lightGray
		case 8:  colour(BACKGROUND_INTENSITY); break;                                                      	//gray
		case 9:  colour(BACKGROUND_INTENSITY | BACKGROUND_BLUE); break;                                      	//lightBlue
		case 10: colour(BACKGROUND_INTENSITY | BACKGROUND_GREEN); break;                                      	//lightGreen
		case 11: colour(BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN); break;                  	//lightCyan
		case 12: colour(BACKGROUND_INTENSITY | BACKGROUND_RED); break;                                      	//lightRed
		case 13: colour(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE); break;                      	//lightPurple
		case 14: colour(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN); break;                  	//lightOrange
		case 15: colour(BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); break;	//white
		}
	}
	
	void debug(int debugInfo, std::string prefaceInfo) {
		std::cout << prefaceInfo << ": " << std::to_string(debugInfo) << std::endl;
		system("pause");
	}
	void debug(int debugInfo) {
		std::cout << "Info: " << std::to_string(debugInfo) << std::endl;
		system("pause");
	}
	void debug(std::string debugString) {
		std::cout << debugString << std::endl;
		system("pause");
	}
}