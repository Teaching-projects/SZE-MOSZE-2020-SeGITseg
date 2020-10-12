#include <iostream>
#include "unit.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Too many/few arguments detected!" << std::endl;
		return 1;
	}
	else
	{
		try
		{
			Unit A = Unit::parseUnit(argv[1]);
			Unit B = Unit::parseUnit(argv[2]);

			if (A.fight(B) == &B)
			{
				std::cout << B.getName() << " wins. Remaining HP: " << B.getHp() << std::endl;
			}
			else
			{
				std::cout << A.getName() << " wins. Remaining HP: " << A.getHp() << std::endl;
			}
		}
		catch (std::runtime_error &e)
		{
			std::cout << e.what() << std::endl;
			return 1;
		}
	}

	return 0;
}
