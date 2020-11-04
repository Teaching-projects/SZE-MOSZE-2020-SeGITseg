#include "Monster.h"
#include "JSON.h"
#include <cmath>

Monster::Monster(const std::string& name, int hp, int dmg, const double& cd)
	: name(name), hp(hp), dmg(dmg), cd(cd), maxHP(hp), xp(0), lvl(1) {}

std::string Monster::getName() const
{
	return name;
}

int Monster::getHp() const
{
	return hp;
}

int Monster::getDmg() const
{
	return dmg;
}

double Monster::getCd() const
{
	return cd;
}

int Monster::getLvl() const
{
	return lvl;
}

void Monster::attack(Monster& target)
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

void Monster::addXp(const int& dmg)
{
	xp += dmg;
	while (xp >= 100)
	{
		lvlUp();
		xp -= 100;
	}
}

void Monster::lvlUp()
{
	lvl++;
	maxHP = round(maxHP * 1.1);
	hp = maxHP;
	dmg = round(dmg * 1.1);
}

Monster* Monster::fight(Monster& other)
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

Monster Monster::parseUnit(const std::string& fileName)
{
	std::string name;
	int hp, dmg;
	double cd;
	std::map<std::string, std::string> unitData = JSON::ParseFile(fileName);
	try
	{
		name = unitData.at("name");
		hp = std::stoi(unitData.at("hp"));
		dmg = std::stoi(unitData.at("dmg"));
		cd = std::stod(unitData.at("cd"));
	}
	catch (const std::out_of_range& oor)
	{
		throw std::runtime_error("Missing data: " + (std::string)oor.what());
	}

	return Monster(name, hp, dmg, cd);
}

std::ostream& operator<<(std::ostream& out, const Monster& u)
{
	return out << u.getName() << ": HP: " << u.getHp() << ", DMG: " << u.getDmg() << ", CD: " << u.getCd() << "\n";
}
