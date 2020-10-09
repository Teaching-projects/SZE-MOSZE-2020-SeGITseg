#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <fstream>
#include <string>

class Unit
{
private:
	const std::string name;
	int hp;
	const int dmg;
	const double cd;

public:
	Unit(const std::string name, const int hp, const int dmg, const double cd);
	std::string getName() const;
	int getHp() const;
	int getDmg() const;
	double getCd() const;
	void fight(Unit &other);
	static Unit parseUnit(const std::string fileName);
	friend std::ostream &operator<<(std::ostream &out, const Unit &u);
};

#endif
