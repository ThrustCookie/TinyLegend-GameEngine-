#include <iostream>
#include <windows.h>
#include <vector>

#include <string> // debugging purposes only


//a bunch of macros to make my life easier

//used to shorten vector2 calls
#define x vector[0]
#define y vector[1]

#define elif else if

//Written Colour definitions for reading comprehension
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define ORANGE 6
#define LIGHTGRAY 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTORANGE 14
#define WHITE 15

//2D vector directions
#define ZERO (0,0)
#define ONE (1,1)
#define UP (0,-1)
#define LEFT (-1,0)
#define DOWN (0,1)
#define RIGHT (1,0)

using namespace std;

// A vector with two intiger coordinate numbers
// used to write more legible code
struct vector2i {
	int vector[2];

	// BaseCondition
	vector2i() {
		vector[0] = 0;
		vector[1] = 0;
	};
	// set an array equal to a coordinate
	vector2i(int xNum, int yNum) {
		x = xNum;
		y = yNum;
	};

	vector2i add(vector2i adder) {
		return vector2i(x + adder.x, y + adder.y);
	}

	vector2i subtract(vector2i subtracter) {
		return add(subtracter.multiply(-1));
	}

	vector2i multiply(int multiplier) {
		return vector2i(x * multiplier, y * multiplier);
	}
	vector2i multiply(vector2i multiplier) {
		return vector2i(x * multiplier.x, y * multiplier.y);
	}
	vector2i divide(int divisor) {
		float floatX = x / divisor;
		float floatY = y / divisor;

		return vector2i(round(floatX), round(floatY));
	}
	vector2i divide(vector2i divisor) {
		float floatX = x / divisor.x;
		float floatY = y / divisor.y;

		return vector2i(round(floatX), round(floatY));
	}

	//returns the current vector with values -1, 1 or 0
	vector2i signed_vector() {
		return vector2i((x != 0) ? x / x : 0, (y != 0) ? y / y : 0); // this might turn into a problem later when it returns zero
	}

	// returns true if one of the intiger pairs are equal
	bool OR_Equal(vector2i match) const {
		return (x == match.x || y == match.y);
	}
	// returns true if both of the intiger pairs are equal
	bool AND_Equal(vector2i match) const {
		return (x == match.x && y == match.y);
	}

	// returns true if one of vector1 variables are greater than vector2
	bool OR_Greater(vector2i quantify) const {
		return (x >= quantify.x || y >= quantify.y);
	}
	// returns true if both of vector1 variables are greater than vector2
	bool AND_Greater(vector2i quantify) const {
		return (x >= quantify.x && y >= quantify.y);
	}

	// returns true if one of vector1 variables are lesser than vector2
	bool OR_Lesser(vector2i quantify) const {
		return (x <= quantify.x || y <= quantify.y);
	}
	// returns true if both of vector1 variables are lesser than vector2
	bool AND_Lesser(vector2i quantify) const {
		return (x <= quantify.x && y <= quantify.y);
	}

	// return vector in string format
	string vectorString() {
		string vectorDebug = "( ";
		vectorDebug.append(to_string(x));
		vectorDebug.append(", ");
		vectorDebug.append(to_string(y));
		vectorDebug.append(")");
		return vectorDebug;
	}
};

/*
struct imageStatic {


	imageStatic() {
	int sprite =
	}

	vector2i size() {

	}
	int at(vector2i coordinate) {
	return sprite[coordinate.y][coordinate.x];
	}
};
*/

struct objectEmpty {
	const int objectId = 0;
	vector2i position,
		size;

	objectEmpty() {
		position = vector2i ZERO;
		size = vector2i ONE;
	}
	//set position
	objectEmpty(vector2i newPosition) {
		position = newPosition;
		size = vector2i ONE;
	}
	//set position & size
	objectEmpty(vector2i newPosition, vector2i newSize) {
		position = newPosition;
		size = newSize;
	}

	vector2i start() const { return position; }
	vector2i end() {
		return ((size.OR_Equal(vector2i ZERO)) ? vector2i ZERO : position.add(size.subtract(vector2i ONE)));
	}
};
struct objectStatic : objectEmpty {
	const int objectId = 1;
	vector< vector<int> > sprite = {
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 }
	};

	objectStatic() {
		position = vector2i ZERO;
		size = vector2i ZERO;
	}

	//set position, size & sprite
	objectStatic(vector2i newPosition, vector2i newSize, vector< vector<int>> newSprite) {
		position = newPosition;
		size = newSize;
		sprite = newSprite;
	}

	//add preset textures so you can instance new objects with words

};

struct objectDynamic : objectStatic {
	const int objectId = 2;
	vector2i direction;
	int speed;

	objectDynamic() {
		direction = vector2i UP;
		speed = 1;
	}
	objectDynamic(vector2i newPosition, vector2i newSize, vector2i newDirection, int newSpeed, vector<vector<int>> newSprite) {
		position = newPosition;
		size = newSize;
		direction = newDirection;
		speed = newSpeed;
		sprite = newSprite;
	}
};

struct entity : objectDynamic {
	bool isDead = false;
	int hp = hpMax;
	int hpMax;

	entity() {
		isDead = false;
		hpMax = 2;
	}
	entity(vector2i newPosition, vector2i newSize, int maxHP) {
		position = newPosition;
		size = newSize;
		hpMax = maxHP;
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
		bg_colour = LIGHTGRAY;
	}
	display(vector2i newPosition, vector2i newSize, int colour) {
		position = newPosition;
		size = newSize;
		bg_colour = colour;
	}
};

struct game {
	bool gameOver = 0;

	vector<objectStatic> staticObjectList;
	vector<objectDynamic> dynamicObjectList;
	vector<entity> entityList;
};

//draw

// Prints out whatever is in the given camera
void draw_screen(display camera, vector<objectStatic> staticObjectList); // I hate having to shove all the terms in like this
int calculate_pixel_colour(vector2i pixel, vector<objectStatic> objectList);
// Prints out extra information under the screen
void draw_UI(vector<objectStatic> staticObjectList);

vector<objectStatic> merge_staticObjectList(vector<objectStatic> staticObjectList, vector<objectDynamic> dynamicObjectList, vector<entity> entityList);
void load_map(vector<objectStatic>& staticObjectList, vector<objectDynamic>& dynamicObjectList, vector<entity>& entityList);
void calculate_movement(vector<objectDynamic>& dynamicObjectList, vector<entity>& entityList);

//functional

void colour(int colourIndex) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colourIndex); }
void colour_bg(int colourIndex);

void debug(int debugInfo, string prefaceInfo);
void debug(int debugInfo);
void debug(string debugString);

void test(int& number) {
	number++;
}

int main() {
	game TinyLegend;

	display camera1(vector2i ZERO, vector2i(50, 25), LIGHTGRAY);

	entity JohnPlayer(vector2i ZERO, vector2i ONE, 8);
	JohnPlayer.hp = 3;
	JohnPlayer.position = vector2i(camera1.position.add(camera1.size.divide(2)));

	TinyLegend.entityList.push_back(JohnPlayer);
	load_map(TinyLegend.staticObjectList, TinyLegend.dynamicObjectList, TinyLegend.entityList);

	/*
	To-Do

	character movement
	move camera w/ character

	enemies
	shoot system

	implement maps
	*/

	//game_start(); 

	while (TinyLegend.gameOver != true) {
		vector<objectStatic> objectList = merge_staticObjectList(TinyLegend.staticObjectList, TinyLegend.dynamicObjectList, TinyLegend.entityList);
		draw_screen(camera1, objectList);
		draw_UI(objectList);

		//calculateInput();
		//calculateEnemies();
		calculate_movement(TinyLegend.dynamicObjectList, TinyLegend.entityList);

		Sleep(600);
		system("cls");
	}
	//game_end();

	colour(7);
	cout << "\n\n";
	system("pause");
	return 0;
}

void draw_screen(display camera, vector<objectStatic> staticObjectList) {
	//calculate all obj actually in view of camera
	//store into the object array that gets processed

	//print camera
	vector2i currentPixel = camera.start();
	for (; currentPixel.y < camera.end().y; currentPixel.y++) {
		for (; currentPixel.x < camera.end().x; currentPixel.x++) {
			int colour = calculate_pixel_colour(currentPixel, staticObjectList);
			(colour >= 0) ? colour_bg(colour) : colour_bg(camera.bg_colour);
			cout << "  ";
		}
		currentPixel.x = 0;
		colour_bg(0);
		cout << endl;
	}
}
int calculate_pixel_colour(vector2i pixel, vector<objectStatic> objectList) {

	for (int i = 0; i < objectList.size(); i++) {
		vector2i topLeft = objectList.at(i).start();
		vector2i bottomRight = objectList.at(i).end();

		if (
			topLeft.x <= pixel.x && bottomRight.x >= pixel.x &&
			topLeft.y <= pixel.y && bottomRight.y >= pixel.y
			//topLeft.AND_Greater(pixel) && topLeft.AND_Lesser(pixel)
			) {
			vector<vector<int>> image = objectList.at(i).sprite;

			vector2i imageIndex; {
				vector2i distanceFromObject = (pixel.subtract(topLeft));
				int repetitionCap;

				repetitionCap = image.size();
				imageIndex.y = distanceFromObject.y % repetitionCap;

				repetitionCap = image[imageIndex.y].size();
				imageIndex.x = distanceFromObject.x % repetitionCap;
			}
			return image[imageIndex.y][imageIndex.x];
		}
	}
	return -1;
}

void draw_UI(vector<objectStatic> staticObjectList) {
	for (int i = 0; i < 16; i++) {
		if (i % (16 / 2) == 0) cout << endl;
		colour_bg(i);
		cout << "  ";
	}
	colour(7);
	for (int i = 0; i < staticObjectList.size(); i++) {
		cout << staticObjectList[i].position.vectorString() << "  ";
	}
	
	colour(7);
}

vector<objectStatic> merge_staticObjectList(vector<objectStatic> staticObjectList, vector<objectDynamic> dynamicObjectList, vector<entity> entityList) {
	vector<objectStatic> mergedObjectList;
	for (int i = 0; i < staticObjectList.size(); i++)
		mergedObjectList.push_back(staticObjectList[i]);

	for (int i = 0; i < dynamicObjectList.size(); i++)
		mergedObjectList.push_back(dynamicObjectList[i]);

	for (int i = 0; i < entityList.size(); i++)
		mergedObjectList.push_back(entityList[i]);

	return mergedObjectList;
}

void load_map(vector<objectStatic>& staticObjectList, vector<objectDynamic>& dynamicObjectList, vector<entity>& entityList) {
	/*
	vector<vector<int>> bricks = {
	{ 4, 4,13,13},
	{12, 4, 4,12},
	{13,13,12,12},
	{ 5, 4, 4, 5},
	};
	*/
	vector<vector<int>> tiles = {
	{ 3, 3, 3, 1},
	{ 3, 9, 9, 1},
	{ 3, 9, 9, 1},
	{ 1, 1, 1, 1}
	};
	vector<vector<int>> bricks = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{13,13,13,13,13, 0,12,12,12,12,12, 0, 4, 4, 4, 0},
	{13,13,13,13,13, 0,12,12,12,12,12, 0, 4, 4, 4, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 5, 5, 5, 0,13,13,13,13,13, 0, 4, 4, 4, 4, 4},
	{ 0, 5, 5, 5, 0,13,13,13,13,13, 0, 4, 4, 4, 4, 4},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{12,12,12,12,12, 0, 4, 4, 4, 4, 4, 0, 5, 5, 5, 0},
	{12,12,12,12,12, 0, 4, 4, 4, 4, 4, 0, 5, 5, 5, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0,12,12,12, 0, 4, 4, 4, 4, 4, 0,12,12,12,12,12},
	{ 0,12,12,12, 0, 4, 4, 4, 4, 4, 0,12,12,12,12,12},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 5, 5, 5, 5, 5, 0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 0},
	{ 5, 5, 5, 5, 5, 0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	staticObjectList.push_back(objectStatic(vector2i ZERO, vector2i(6, 15), bricks));
	staticObjectList.push_back(objectStatic(vector2i(5, 2), vector2i(10, 10), bricks));
	staticObjectList.push_back(objectStatic(vector2i(20, 10), vector2i(15, 5), bricks));

	dynamicObjectList.push_back(objectDynamic(vector2i(30, 3), vector2i(2, 2), vector2i RIGHT, 1, tiles));
	dynamicObjectList.push_back(objectDynamic(vector2i(20, 20), vector2i(5, 7), vector2i RIGHT, 1, tiles));

	entityList;
}

void calculate_movement(vector<objectDynamic>& dynamicObjectList, vector<entity>& entityList) {
	for (int i = 0; i < dynamicObjectList.size(); i++) {
		vector2i movementDirection = dynamicObjectList[i].direction.multiply(dynamicObjectList[i].speed);

		dynamicObjectList[i].position = dynamicObjectList[i].position.add(movementDirection);
	}
	for (int i = 0; i < entityList.size(); i++) {
		vector2i movementDirection = entityList[i].direction. multiply (entityList[i].speed);

		entityList[i].position = entityList[i].position. add (movementDirection);
	}
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

void debug(int debugInfo, string prefaceInfo) {
	cout << prefaceInfo << ": " << to_string(debugInfo) << endl;
	system("pause");
}
void debug(int debugInfo) {
	cout << "Info: " << to_string(debugInfo) << endl;
	system("pause");
}
void debug(string debugString) {
	cout << debugString << endl;
	system("pause");
}
