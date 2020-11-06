#include "Monster.h"
#include "JSON.h"

Monster::Monster(const std::string& name, int hp, int dmg, double cd)
	: name(name), hp(hp), dmg(dmg), cd(cd) {}

std::string Monster::getName() const
{
	return name;
}

int Monster::getHealthPoints() const
{
	return hp;
}

int Monster::getDamage() const
{
	return dmg;
}

double Monster::getAttackCoolDown() const
{
	return cd;
}

int Monster::attack(Monster& target)
{
	int damagePerRound=0;
	if (target.getHealthPoints() - dmg > 0)
	{
		target.hp -= dmg;
		damagePerRound=dmg;
	}
	else
	{
		damagePerRound=target.getHealthPoints();
		target.hp = 0;
	}
	return damagePerRound;
}

void Monster::fightTilDeath(Monster& other)
{
	attack(other);
	if (other.isAlive())
		other.attack(*this);

	double timeA = cd;
	double timeB = other.getAttackCoolDown();

	while (this->isAlive() && other.isAlive())
	{
		if (timeA <= timeB)
		{
			attack(other);
			timeA += cd;
		}
		else
		{
			other.attack(*this);
			timeB += other.getAttackCoolDown();
		}
	}
}

bool Monster::isAlive() const
{
	if (hp > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Monster Monster::parse(const std::string& fileName)
{
	std::string name;
	int hp, dmg;
	double cd;
	JSON unitData = JSON::parseFromFile(fileName);
	try
	{
		name = unitData.get<std::string>("name");
		hp = unitData.get<int>("hp");
		dmg = unitData.get<int>("dmg");
		cd = unitData.get<double>("cd");
	}
	catch (const std::out_of_range& oor)
	{
		throw std::runtime_error("Missing data: " + (std::string)oor.what());
	}

	return Monster(name, hp, dmg, cd);
}
