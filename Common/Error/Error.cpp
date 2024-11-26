#include "Error.h"
#include <iostream>


bool error(std::string explanation, std::string error_type, bool fatal) {
	if (fatal) {
		throw Message("[ERROR] " + error_type + "Error: " + explanation);
	} else {
		//std::cerr << "[WARNING] " + error_type + "Error: " + explanation + "\n";
	};
	return false;
}