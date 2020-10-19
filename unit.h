/**
* \class Unit
*
* \brief This is the Unit class, which contains the attributes and methods of the units.
*
* \author Kreutzog András, Káldy Kristóf, Boros Dávid
*
* \version 0.1
*
* \date 2020/10/09 15:40
*
* Created on: 2020/10/09 15:40
*/

#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <fstream>
#include <string>

class Unit
{
private:
	const std::string name; ///< The name of the unit.
	int hp;					///< The current health points of the unit.
	int dmg;				///< The damage of the unit.
	const double cd;		///< The attack cooldown of the unit (in seconds).
	int maxHP;				///< The maximal health points of the unit.
	int xp;					///< The xp of the unit.
	int lvl;				///< The level of the unit.

	void lvlUp(); ///< Function to level up the unit.
	/// This private function adds xp to the unit when doing damage.
	void addXp(const int &dmg /** [in] The damage param. */);
	/// This private function does a single attack against a target unit.
	void attack(Unit &target /** [in] The target param. */);

public:
	/// This is the constructor for the Unit class.
	Unit(const std::string &name, int hp, int dmg, const double &cd /** [in] The name, health, damage and cooldown of the unit. */);

	/**
	 *  \brief This is a simple getter function for unit name.
	 *  \param none
	 *  \return Returns the unit name.
	*/
	std::string getName() const;

	/**
	 *  \brief This is a simple getter function for unit health points.
	 * 	\param none
	 *  \return Returns the unit health.
	*/
	int getHp() const;

	/**
	 *  \brief This is a simple getter function for unit damage.
	 * 	\param none
	 *  \return Returns the unit damage.
	*/
	int getDmg() const;

	/**
	 *  \brief This is a simple getter function for unit attack cooldown.
	 * 	\param none
	 *  \return Returns the unit attack cooldown.
	*/
	double getCd() const;

	/**
	 *  \brief This is a simple getter function for unit level.
	 * 	\param none
	 *  \return Returns the unit level.
	*/
	int getLvl() const;

	/**
	 *  \brief This is the function where the units fights each other until one of them dies (hp goes to 0).
	 *  \return It returns the winner unit.
	*/
	Unit *fight(Unit &other /** [in] The opponent param. */);

	/**
	 *  \brief  This function inputs the units from files.
	 *  \return It returns the unit name, hp, damage and cooldown.
	*/
	static Unit parseUnit(const std::string &fileName /** [in] The name of the input file. */);

	/**
	 *  \brief This is an output operator, used to output the unit's attributes.
	 *  \return It returns every important information about the unit (name, hp, dmg, cd).
	*/
	friend std::ostream &operator<<(std::ostream &out, const Unit &u /** [in] The unit param. */);
};

#endif