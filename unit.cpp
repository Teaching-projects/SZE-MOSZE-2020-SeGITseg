#include "unit.h"
#include "jsonparser.h"

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
	int hp, dmg;
	std::map<std::string, std::string> unitData = JSONParser::Parse(fileName);
	try {
		name = unitData.at("name");
		hp = std::stoi(unitData.at("hp"));
		dmg = std::stoi(unitData.at("dmg"));
	}
	catch (const std::out_of_range &oor) {
		throw std::runtime_error("Missing data: " + (std::string)oor.what());
	}

	return Unit(name, hp, dmg);
}

std::ostream &operator<<(std::ostream &out, const Unit &u)
{
	return out << u.getName() << ": HP: " << u.getHp() << ", DMG: " << u.getDmg() << "\n";
}