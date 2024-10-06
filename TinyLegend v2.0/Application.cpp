#include "Engine.h"
#include <iostream>
#include <windows.h>
#include <vector>

//a bunch of macros to make life easier
//used to shorten vector2 calls
#define x d[0]
#define y d[1]
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

using namespace engine;
map map1();

int main() {
	game TinyLegend;

	display camera1(vector2i ZERO, vector2i(50, 25), LIGHTGRAY);

	entity John(8, vector2i ZERO, vector2i ONE, vector2i UP, image({ {2} }));
	John.hp = 3;
	John.position = vector2i(camera1.position.add(camera1.size.divide(2)));
	
	map currentMap = map1();

	TinyLegend.load_map(currentMap);
	TinyLegend.currentMap.listEntity.insert(TinyLegend.currentMap.listEntity.begin(), John); //bandaid fix for now

	/*
	To-Do

	add player
	player input
	move camera w/ player

	enemy ai
	shoot system

	implement maps

	implement player class or player speciality so characters can move across maps
	*/
	
	//game_start(); 
	while (TinyLegend.gameOver != true) {
		draw_screen( camera1, TinyLegend.currentMap );
		draw_UI();

		//calculateInput();
		//calculateEnemiesAI();
		calculate_movement(TinyLegend.currentMap.listObjectDynamic, TinyLegend.currentMap.listEntity);

		Sleep(600);
		system("cls");
	}
	//game_end();

	colour(7);
	
	std::cout << "\n\n";
	system("pause");
	return 0;
	
}


map map1() {
	map map1;
	//vector<vector<int>> bricks = {
	//{ 4, 4,13,13},
	//{12, 4, 4,12},
	//{13,13,12,12},
	//{ 5, 4, 4, 5},
	//};

	image tiles;
	tiles.imageMatrix = {
	{ 3, 3, 3, 1},
	{ 3, 9, 9, 1},
	{ 3, 9, 9, 1},
	{ 1, 1, 1, 1}
	};

	image bricks;
	bricks.imageMatrix = {
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

	map1.listObjectStatic = {
		objectStatic(vector2i ZERO, vector2i(6, 15), bricks),
		objectStatic(vector2i(5, 2), vector2i(10, 10), bricks),
		objectStatic(vector2i(20, 10), vector2i(15, 5), bricks)
	};
	map1.listObjectDynamic = {
		objectDynamic(vector2i(30, 3), vector2i(2, 2), vector2i RIGHT, tiles),
		objectDynamic(vector2i(20, 20), vector2i(5, 7), vector2i RIGHT, tiles)
	};

	map1.listEntity = {
		entity(2, vector2i(40, 20), vector2i ONE, vector2i UP,  image({ {13} }) )
	};

	return map1;
}
