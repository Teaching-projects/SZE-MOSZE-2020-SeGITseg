#include "Hero.h"
#include "JSON.h"
#include <iostream>

Hero::Hero(const std::string &name, int hp, int dmg, double cd, const double XpPerLevel, const double HpBonusPerLevel, const double DamageBonusPerLevel, const double CdMultiplierPerLevel)
    : Monster{name, hp, dmg, cd}, maxHP(hp), xp(0), lvl(1), XpPerLevel(XpPerLevel), HpBonusPerLevel(HpBonusPerLevel), DamageBonusPerLevel(DamageBonusPerLevel), CdMultiplierPerLevel(CdMultiplierPerLevel) {}

void Hero::addXp(const int &dmg)
{
    xp += dmg;
    while (xp >= XpPerLevel)
    {
        lvlUp();
        xp -= XpPerLevel;
    }
}

void Hero::lvlUp()
{
    lvl++;
    maxHP += HpBonusPerLevel;
    hp = maxHP;
    cd *= CdMultiplierPerLevel;
    dmg += DamageBonusPerLevel;
}

int Hero::attack(Monster &target)
{
    int dmgPerRound = 0;
    dmgPerRound = Monster::attack(target);
    addXp(dmgPerRound);
    return dmgPerRound;
}

int Hero::getLevel() const
{
    return lvl;
}

int Hero::getXp() const
{
    return xp;
}

int Hero::getMaxHealthPoints() const
{
    return maxHP;
}

Hero Hero::parse(const std::string &fileName)
{
    JSON data = JSON::parseFromFile(fileName);

    return Hero(
        data.get<std::string>("name"),
        data.get<int>("base_health_points"),
        data.get<int>("base_damage"),
        data.get<double>("base_attack_cooldown"),
        data.get<double>("experience_per_level"),
        data.get<double>("health_point_bonus_per_level"),
        data.get<double>("damage_bonus_per_level"),
        data.get<double>("cooldown_multiplier_per_level"));
}