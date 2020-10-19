#include "unit.h"
#include <cmath>

Unit::Unit(const std::string &name, int hp, int dmg, const double &cd)
	: name(name), hp(hp), dmg(dmg), cd(cd), maxHP(hp), xp(0), lvl(1) {}

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

int Unit::getLvl() const
{
	return lvl;
}

void Unit::attack(Unit &target)
{
	if (target.getHp() - dmg > 0)
	{
		target.hp -= dmg;
		addXp(dmg);
	}
	else
	{
		int tmpHp = target.hp;
		target.hp = 0;
		addXp(tmpHp);
	}
}

void Unit::addXp(const int &dmg)
{
	xp += dmg;
	while (xp >= 100)
	{
		lvlUp();
		xp -= 100;
	}
}

void Unit::lvlUp()
{
	lvl++;
	maxHP = round(maxHP * 1.1);
	hp = maxHP;
	dmg = round(dmg * 1.1);
}

Unit *Unit::fight(Unit &other)
{
	attack(other);
	if (other.getHp() > 0)
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

Unit Unit::parseUnit(const std::string &fileName)
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
