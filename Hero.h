#ifndef HERO_H
#define HERO_H

class Hero : public Monster
{
private:
    float XpPerLevel;
    float DamageBonusPerLevel;
    float HpBonusPerLevel;
    float CdMultiplierPerLevel;
public:
    Hero();
    static Hero parse(const std::string&);
};

#endif