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
	int maxHP;
	int dmg;
	int xp;
	int lvl;
	void lvlUp();
	void addXp(const int &dmg);

public:
	Unit(const std::string &name, int hp, int dmg);
	std::string getName() const;
	int getHp() const;
	int getDmg() const;
	int getLvl() const;
	void fight(Unit &other);
	static Unit parseUnit(const std::string &fileName);
	friend std::ostream &operator<<(std::ostream &out, const Unit &u);
};

#endif
