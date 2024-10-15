#pragma once

#include <string>

namespace utils {
	//colour functions (for windows)
	void colour(int colourIndex);
	void colour_bg(int colourIndex);

	//debug information
	void debug(int debugInfo, std::string prefaceInfo);
	void debug(int debugInfo);
	void debug(std::string debugString);
}