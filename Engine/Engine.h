#pragma once

#include <math.h>
#include <windows.h>
#include <vector>
#include <string>

/*
 This project needs a more strict naming scheme
 So far the loose naming schema is
 variablesUseCamelCase 
	going from biggest to smallest 
	example
		list
		object
		objectType
		objectName
*/

//a bunch of macros to make life easier

#define xPos d[0] // figure out how to make this 'x' and not 'xPos'
#define yPos d[1] // figure out how to make this 'y' and not 'yPos'
//2D vector directions
#define ZERO (0,0)
#define ONE (1,1)
#define UP (0,-1)
#define LEFT (-1,0)
#define DOWN (0,1)
#define RIGHT (1,0)
//used to shorten vector2 calls
#define elif else if

namespace engine {
	// A vector with two intiger coordinate numbers
	struct vector2i {
		int d[2];
		
		// BaseCondition delted
		vector2i() {
			xPos = 0;
			yPos = 0;
		}
		// set an array equal to a coordinate
		vector2i(int xNum, int yNum) {
			xPos = xNum;
			yPos = yNum;
		};

		vector2i add(vector2i adder) {
			return vector2i(xPos + adder.xPos, yPos + adder.yPos);
		}

		vector2i subtract(vector2i subtracter) {
			return add(subtracter.multiply(-1));
		}

		vector2i multiply(int multiplier) {
			return vector2i(xPos * multiplier, yPos * multiplier);
		}
		vector2i multiply(vector2i multiplier) {
			return vector2i(xPos * multiplier.xPos, yPos * multiplier.yPos);
		}
		vector2i divide(int divisor) {
			float floatX = xPos / divisor;
			float floatY = yPos / divisor;

			return vector2i(round(floatX), round(floatY));
		}
		vector2i divide(vector2i divisor) {
			float floatX = xPos / divisor.xPos;
			float floatY = yPos / divisor.yPos;

			return vector2i(round(floatX), round(floatY));
		}

		//returns the current vector with values -1, 1 or 0
		vector2i signed_vector() {
			return vector2i((xPos != 0) ? xPos / xPos : 0, (yPos != 0) ? yPos / yPos : 0); // this might turn into a problem later when it returns zero
		}

		// returns true if one of the intiger pairs are equal
		bool OR_Equal(vector2i match) const {
			return (xPos == match.xPos || yPos == match.yPos);
		}
		// returns true if both of the intiger pairs are equal
		bool AND_Equal(vector2i match) const {
			return (xPos == match.xPos && yPos == match.yPos);
		}

		// returns true if one of vector1 variables are greater than vector2
		bool OR_Greater(vector2i quantify) const {
			return (xPos >= quantify.xPos || yPos >= quantify.yPos);
		}
		// returns true if both of vector1 variables are greater than vector2
		bool AND_Greater(vector2i quantify) const {
			return (xPos >= quantify.xPos && yPos >= quantify.yPos);
		}

		// returns true if one of vector1 variables are lesser than vector2
		bool OR_Lesser(vector2i quantify) const {
			return (xPos <= quantify.xPos || yPos <= quantify.yPos);
		}
		// returns true if both of vector1 variables are lesser than vector2
		bool AND_Lesser(vector2i quantify) const {
			return (xPos <= quantify.xPos && yPos <= quantify.yPos);
		}

		// return vector in string format
		std::string to_string() {
			std::string vectorDebug = "( ";
			vectorDebug.append(std::to_string(xPos));
			vectorDebug.append(", ");
			vectorDebug.append(std::to_string(yPos));
			vectorDebug.append(")");
			return vectorDebug;
		}
	};

	struct image {
		std::vector< std::vector<int> > imageMatrix;

		image() {
			imageMatrix = { {13} };
		}
		image(std::vector< std::vector<int> > newImageMatrix) {
			imageMatrix = newImageMatrix;
		}
	};

	//objectTypes

	struct objectEmpty {
		vector2i position, size;

		objectEmpty() {
			position = vector2i ZERO;
			size = vector2i ONE;
		}
		//create with position & size
		objectEmpty(vector2i newPosition, vector2i newSize) {
			position = newPosition;
			size = newSize;
		}

		vector2i start() const { return position; }
		vector2i end() {
			return ( (size.OR_Equal(vector2i ZERO) ) ? vector2i ZERO : position.add(size.subtract(vector2i ONE)));
		}
	}; 

	//there should be an object inbetween or a re-purposed object type with no collision

	struct objectStatic : objectEmpty {
		image sprite;

		objectStatic() {
			position = vector2i ZERO;
			size = vector2i ZERO;
		}

		//set position, size & sprite
		objectStatic(vector2i startPosition, vector2i startSize, image startSprite) {
			position = startPosition;
			size = startSize;
			sprite = startSprite;
		}

		//add preset textures so you can instance new objects with words
	};
	struct objectDynamic : objectStatic {
		vector2i direction;
		int speed = 1;

		objectDynamic() {
			direction = vector2i ONE;
		}
		objectDynamic(vector2i startPosition, vector2i startSize, vector2i startDirection, image startSprite) {
			position = startPosition;
			size = startSize;
			direction = startDirection;
			sprite = startSprite;
		}
	};
	struct entity : objectDynamic {
		bool isDead = false;
		int hp = hpMax;
		int hpMax;

		entity() {
			hpMax = 2;
		}
		entity(int startHp, vector2i startPosition, vector2i startSize, vector2i startDirection, image startSprite) {
			hpMax = startHp;
			position = startPosition;
			size = startSize;
			speed = 1;
			direction = startDirection;
			sprite = startSprite;
		}

		void applyDamage(int damage) {
			hp -= damage;
		}
	};

	struct display : objectEmpty {
		int bg_colour;

		display() {
			position = vector2i ZERO;
			size = vector2i(50, 25);
			bg_colour = 0;
		}
		display(vector2i newPosition, vector2i newSize, int colour) {
			position = newPosition;
			size = newSize;
			bg_colour = colour;
		}
	};

	//should be an object with position and scale so you can move it as a group
	struct map {
		std::vector<objectStatic> listObjectStatic;
		std::vector<objectDynamic> listObjectDynamic;
		std::vector<entity> listEntity;

		map() {
			listObjectStatic;
			listObjectDynamic;
			listEntity;
		}
		map(std::vector<objectStatic> newListObjectStatic, std::vector<objectDynamic> newListObjectDynamic, std::vector<entity> newListEntity) {
			listObjectStatic = newListObjectStatic;
			listObjectDynamic = newListObjectDynamic;
			listEntity = newListEntity;
		}

		// merges all objects from static onward into a list
		std::vector<objectStatic> merge_listObjectStatic() {
			std::vector<objectStatic> listMerged = listObjectStatic;

			for (int i = 0; i < listObjectDynamic.size(); i++) {
				listMerged.push_back(listObjectDynamic[i]);
			}

			for (int i = 0; i < listEntity.size(); i++) {
				listMerged.push_back(listEntity[i]);
			}

			return listMerged;
		}

		// merges all objects from dynamic onward into a list
		std::vector<objectDynamic> merge_listObjectDynamic() {
			std::vector<objectDynamic> listMerged;

			for (int i = 0; i < listObjectDynamic.size(); i++) {
				listMerged.push_back(listObjectDynamic[i]);
			}

			for (int i = 0; i < listEntity.size(); i++) {
				listMerged.push_back(listEntity[i]);
			}

			return listMerged;
		}
	}; 

	struct game {
		bool gameOver = 0;
		map currentMap;

		void load_map(map newMap) {
			currentMap = newMap;
		}
	};
	
	//draw
	// Prints out whatever is in the given camera
	void draw_screen(display camera, map currentMap);
	int calculate_pixel_colour(vector2i pixel, std::vector<objectStatic> objectList);
	// Prints out extra information under the screen
	void draw_UI();

	void calculate_movement(std::vector<objectDynamic>& dynamicObjectList, std::vector<entity>& entityList);

	//consider moving these to their own libarary

	//colour functions (for windows)
	void colour(int colourIndex);
	void colour_bg(int colourIndex);
	
	//debug information
	void debug(int debugInfo, std::string prefaceInfo);
	void debug(int debugInfo);
	void debug(std::string debugString);
}
