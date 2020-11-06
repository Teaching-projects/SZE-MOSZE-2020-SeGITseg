/**
* \class Monster
*
* \brief This is the Monster class, which contains the attributes and methods of the monsters.
*
* \author Boros Dávid, Káldy Kristóf, Kreutzog András
*
* \version 1.0
*
* \date 2020/10/09 15:40
*
* Created on: 2020/10/09 15:40
*/

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <fstream>
#include <string>

class Monster
{
protected:
	const std::string name; ///< The name of the unit.
	int hp;					///< The current health points of the unit.
	int dmg;				///< The damage of the unit.
	double cd;		///< The attack cooldown of the unit (in seconds).

public:
	/// This is the constructor for the Unit class.
	Monster(const std::string& name, int hp, int dmg, double cd /** [in] The name, health, damage and cooldown of the unit. */);

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
	int getHealthPoints() const;

	/**
	 *  \brief This is a simple getter function for unit damage.
	 * 	\param none
	 *  \return Returns the unit damage.
	*/
	int getDamage() const;

	/**
	 *  \brief This is a simple getter function for unit attack cooldown.
	 * 	\param none
	 *  \return Returns the unit attack cooldown.
	*/
	double getAttackCoolDown() const;

	/**
	 *  \brief This shows if the unit is alive or not (hp>0).
	 *  \return It returns true or false.
	*/
	bool isAlive() const;

	/// This function does a single attack against a target unit.
	virtual void attack(Monster& target /** [in] The target param. */);

	void fightTilDeath(Monster& other /** [in] The opponent param. */);

	/**
	 *  \brief  This function inputs the units from files.
	 *  \return It returns the unit name, hp, damage and cooldown.
	*/
	static Monster parse(const std::string& fileName /** [in] The name of the input file. */);

	/**
	 *  \brief This is an output operator, used to output the unit's attributes.
	 *  \return It returns every important information about the unit (name, hp, dmg, cd).
	*/
};

#endif
