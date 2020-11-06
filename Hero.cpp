#include "Hero.h"
#include "JSON.h"
#include <iostream>

Hero::Hero(const std::string& name, int hp, int dmg, double cd, const float XpPerLevel, const float HpBonusPerLevel, const float DamageBonusPerLevel, const float CdMultiplierPerLevel)
    : Monster{ name,hp,dmg,cd }, maxHP(hp), xp(0), lvl(1), XpPerLevel(XpPerLevel), HpBonusPerLevel(HpBonusPerLevel), DamageBonusPerLevel(DamageBonusPerLevel), CdMultiplierPerLevel(CdMultiplierPerLevel) {}

void Hero::addXp(const int& dmg)
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
    dmg += HpBonusPerLevel;
}

int Hero::attack(Monster& target)
{
    int damagePerRound = Monster::attack(target);
    addXp(damagePerRound);
    return damagePerRound;
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

Hero Hero::parse(const std::string& fileName)
{

}