#include "Engine.h"
#include "CemiUtils.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace engine;
map map1();

int main() {
	//game_start(); 
		// start with game and game name
		game TinyLegend;

		// make camera with position, size and colour
		display camera1(vector2i ZERO, vector2i(50, 25), LIGHTGRAY);

		// make player and character stats
		entity John(8, vector2i ZERO, vector2i ONE, vector2i UP, image({ {2} }));
		John.hp = 3;
		John.position = vector2i(camera1.position.add(camera1.size.divide(2)));
	
		//load map
		map currentMap = map1();
		TinyLegend.load_map(currentMap);

		//insert character to maplist
		TinyLegend.currentMap.listEntity.insert(TinyLegend.currentMap.listEntity.begin(), John); //bandaid fix for now
	
	// main gameloop
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

	utils::colour(7);
	
	std::cout << "\n\n";
	system("pause");
	return 0;

	/*
	To-Do

	player input
	move camera w/ player

	enemy ai
	shoot system

	implement maps

	implement player class or player speciality so characters can move across maps
	*/
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

void read_input(char key) {
	switch (key) {
	case 'w': break;
	case 'a': break;
	case 's': break;
	case 'd': break;
	}
}