#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>

class Unit
{
private:
	const std::string name;
	int hp;
	const int dmg;

public:
	Unit(const std::string name, const int hp, const int dmg);
	std::string getName() const;
	int getHp() const;
	int getDmg() const;
	void fight(Unit &other);
	static Unit parseUnit(const std::string fileName);
	friend std::ostream &operator<<(std::ostream &out, const Unit &u);
};

#endif