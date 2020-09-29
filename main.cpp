#include <iostream>
#include "unit.h"

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cout << "Too many/few arguments detected!" << std::endl;
		return 1;
	}
	else {
		try {
			Unit A = Unit::parseUnit(argv[1]);
			Unit B = Unit::parseUnit(argv[2]);

			A.fight(B);
		}
		catch (std::runtime_error& e) {
			std::cout << e.what() << std::endl;
			return 1;
		}
	}

	return 0;
}