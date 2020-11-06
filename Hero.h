#ifndef HERO_H
#define HERO_H

#include "Monster.h"

class Hero : public Monster
{
private:
    int maxHP;				///< The maximal health points of the unit.
    int xp;					///< The xp of the unit.
    int lvl;				///< The level of the unit.
    const float XpPerLevel; ///< Experience per level.
    const float HpBonusPerLevel; ///< Health point bonus per level
    const float DamageBonusPerLevel;///< Damage bonus per level.
    const float CdMultiplierPerLevel; ///< Cooldown mulitplier per level.

public:
    /// This is the constructor for the Hero class.
    Hero(const std::string& name, int hp, int dmg, double cd, const float XpPerLevel, const float HpBonusPerLevel, const float DamageBonusPerLevel, const float CdMultiplierPerLevel /** [in] The name, health, damage, attackcooldown, xp per level, hp bonus per level, damagebonus per level and the cooldown multiplier of the hero. */);

    /**
     *  \brief This is a simple getter function for max health points.
     * 	\param none
     *  \return Returns the unit's max health.
    */
    int getMaxHealthPoints() const;

    /**
     *  \brief This is a simple getter function for unit level.
     * 	\param none
     *  \return Returns the unit's level.
    */
    int getLevel() const;

    /**
    *  \brief This is a simple getter function for unit xp.
    * 	\param none
    *  \return Returns the unit's xp.
   */
    int getXp() const;

    /// This function adds xp to the unit when doing damage.
    void addXp(const int& dmg /** [in] The damage param. */);

    void lvlUp(); ///< Function to level up the unit.

    virtual int attack(Monster& target /** [in] The target param. */);

    /**
     *  \brief  This function inputs the units from files.
     *  \return It returns the unit name, hp, damage and cooldown.
    */
    static Hero parse(const std::string& fileName /** [in] The name of the input file. */);

};

#endif