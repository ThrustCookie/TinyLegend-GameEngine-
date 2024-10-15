#include "CemiUtils.h"
#include <Windows.h>
#include <iostream>

namespace utils {

	void colour(int colourIndex) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colourIndex);
	}
	void colour_bg(int colourIndex) {
		switch (colourIndex) {
		case 0:  colour(0); break;                                                                          //black
		case 1:  colour(BACKGROUND_BLUE); break;                                                            //blue
		case 2:  colour(BACKGROUND_GREEN); break;                                                          	//green
		case 3:  colour(BACKGROUND_BLUE | BACKGROUND_GREEN); break;                                         //cyan
		case 4:  colour(BACKGROUND_RED); break;                                                             //red
		case 5:  colour(BACKGROUND_RED | BACKGROUND_BLUE); break;                                          	//purple
		case 6:  colour(BACKGROUND_RED | BACKGROUND_GREEN); break;                                          //orange
		case 7:  colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); break;                        //lightGray
		case 8:  colour(BACKGROUND_INTENSITY); break;                                                      	//gray
		case 9:  colour(BACKGROUND_INTENSITY | BACKGROUND_BLUE); break;                                     //lightBlue
		case 10: colour(BACKGROUND_INTENSITY | BACKGROUND_GREEN); break;                                    //lightGreen
		case 11: colour(BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN); break;                  //lightCyan
		case 12: colour(BACKGROUND_INTENSITY | BACKGROUND_RED); break;                                      //lightRed
		case 13: colour(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE); break;                    //lightPurple
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