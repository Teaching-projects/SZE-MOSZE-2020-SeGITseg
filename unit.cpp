#include "unit.h"

Unit::Unit(const std::string name, const int hp, const int dmg)
	: name(name), hp(hp), dmg(dmg) {}

std::string Unit::getName() const
{
	return name;
}

int Unit::getHp() const
{
	return hp;
}

int Unit::getDmg() const
{
	return dmg;
}

void Unit::fight(Unit &other)
{
	while (hp > 0)
	{
		(other.getHp() - dmg > 0) ? other.hp -= dmg : other.hp = 0;

		if (other.getHp() == 0) { break; }

		(hp - other.getDmg() > 0) ? hp -= other.dmg : hp = 0;
	}

	if (other.getHp() == 0) {
		std::cout << name << " wins. Remaining HP: " << hp << std::endl;
	}
	else {
		std::cout << other.getName() << " wins. Remaining HP: " << other.getHp() << std::endl;
	}
}

Unit Unit::parseUnit(std::string fileName)
{
	std::string name;
	int hp = 0;
	int dmg = 0;

	std::ifstream file("units/" + fileName);

	if (!file.fail() && file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			int startPos = line.find_first_of(":") + 2;

			if (line.find("name") != std::string::npos) {
				name = line.substr(startPos + 1, line.length() - (startPos + 3));
			}
			else if (line.find("hp") != std::string::npos) {
				hp = std::stoi(line.substr(startPos, line.length() - (startPos + 1)));
			}
			else if (line.find("dmg") != std::string::npos) {
				dmg = std::stoi(line.substr(startPos, line.length() - startPos));
			}
		}
	}
	else {
		throw std::runtime_error("Error while opening the file: " + fileName);
	}

	return Unit(name, hp, dmg);
}

std::ostream &operator<<(std::ostream &out, const Unit &u)
{
	return out << u.getName() << ": HP: " << u.getHp() << ", DMG: " << u.getDmg() << "\n";
}