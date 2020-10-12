#include "unit.h"

Unit::Unit(const std::string name, const int hp, const int dmg, const double cd)
	: name(name), hp(hp), dmg(dmg), cd(cd) {}

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

double Unit::getCd() const
{
	return cd;
}

void Unit::attack(Unit &target)
{
	(target.getHp() - dmg > 0) ? target.hp -= dmg : target.hp = 0;
}

Unit *Unit::fight(Unit &other)
{
	attack(other);
	other.attack(*this);

	double timeA = cd;
	double timeB = other.getCd();

	while (hp > 0 && other.getHp() > 0)
	{
		if (timeA <= timeB)
		{
			attack(other);
			timeA += cd;
		}
		else
		{
			other.attack(*this);
			timeB += other.getCd();
		}
	}

	if (hp == 0)
	{
		return &other;
	}
	else
	{
		return this;
	}
}

Unit Unit::parseUnit(std::string fileName)
{
	std::string name;
	int hp = 0;
	int dmg = 0;
	double cd = 0;

	std::ifstream file("units/" + fileName);

	if (!file.fail() && file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			int startPos = line.find_first_of(":") + 2;

			if (line.find("name") != std::string::npos)
			{
				name = line.substr(startPos + 1, line.length() - (startPos + 3));
			}
			else if (line.find("hp") != std::string::npos)
			{
				hp = std::stoi(line.substr(startPos, line.length() - (startPos + 1)));
			}
			else if (line.find("dmg") != std::string::npos)
			{
				dmg = std::stoi(line.substr(startPos, line.length() - startPos));
			}
			else if (line.find("cd") != std::string::npos)
			{
				cd = std::stod(line.substr(startPos, line.length() - startPos));
			}
		}
	}
	else
	{
		throw std::runtime_error("Error while opening the file: " + fileName);
	}

	return Unit(name, hp, dmg, cd);
}

std::ostream &operator<<(std::ostream &out, const Unit &u)
{
	return out << u.getName() << ": HP: " << u.getHp() << ", DMG: " << u.getDmg() << ", CD: " << u.getCd() << "\n";
}
