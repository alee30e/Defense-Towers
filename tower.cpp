// Tower.cpp
#include "tower.h"
#include "player.h"
#include <iostream>

Tower::Tower(int baseDamage, const std::string& sym)
    : level(1), damage(baseDamage), symbol(sym), HP(100) {}

bool Tower::canUpgrade(Player& player) const {
    if (player.getGold() > price)
    return 1;
    else
    return 0;
}

Tower::Tower(const Tower& other)
    : level(other.level), damage(other.damage), HP(other.HP), price(other.price), symbol(other.symbol), attacking(other.attacking) {
    std::cout << "Copy constructor called for Tower: " << symbol << "\n";
}


Tower& Tower::operator=(const Tower& other) {
    if (this == &other) {
        return *this;
    }

    level = other.level;
    damage = other.damage;
    HP = other.HP;
    price = other.price;
    symbol = other.symbol;
    attacking = other.attacking;

    std::cout << "Assignment operator called for Tower: " << symbol << "\n";

    return *this;
}

int Tower::getLevel() const {
    return level;
}
void Tower::upgrade(Player& player) {
    if (canUpgrade(player)) {
        player.spendGold(price);
        ++level;
        damage += 5;
    }
}

std::string Tower::getSymbol() const {
    return symbol + std::to_string(level);
}

ArcherTower::ArcherTower() : Tower(20, "A") {}

void ArcherTower::attack(Monstru& monster) const {
    
    if (monster.getX() < 5)
    {
        attacking = true;
        monster.takeDamage(damage);
    }
    else attacking = false;
    
}
void Tower::getsAttacked(Monstru& monster){
    if (monster.getX() == 1)
    {
        HP = HP - monster.getDamage();
    }
}

std::unique_ptr<Tower> ArcherTower::clone() const {
    return std::make_unique<ArcherTower>(*this);
}

CannonTower::CannonTower() : Tower(12, "C") {}

void CannonTower::attack(Monstru& monster) const {
    if (monster.getX() < 3)
    {
        monster.takeDamage(damage);
        attacking = true;
    }
     else attacking = false;
}

// void CannonTower::getsAttacked(Monstru& monster){
//     if (monster.getX() == 1)
//     {
//         HP = HP - monster.getDamage();
//     }
// }

std::unique_ptr<Tower> CannonTower::clone() const {
    return std::make_unique<CannonTower>(*this);
}

// === MagicTower ===
MagicTower::MagicTower() : Tower(10, "M") {}

void MagicTower::attack(Monstru& monster) const {
    if (monster.getX() < 6)
    {
        monster.takeDamage(damage);
        attacking = true;
    }
     else attacking = false;
}

// void MagicTower::getsAttacked(Monstru& monster){
//     if (monster.getX() == 1)
//     {
//         HP = HP - monster.getDamage();
//     }
// }
std::unique_ptr<Tower> MagicTower::clone() const {
    return std::make_unique<MagicTower>(*this);
}

// === IceTower ===
IceTower::IceTower() : Tower(8, "I") {}

void IceTower::attack(Monstru& monster) const {
    if (monster.getX() < 8)
    {
        attacking = true;
        monster.takeDamage(damage);
    }
     else attacking = false;
}
// void IceTower::getsAttacked(Monstru& monster){
//     if (monster.getX() == 1)
//     {
//         HP = HP - monster.getDamage();
//     }
// }

std::unique_ptr<Tower> IceTower::clone() const {
    return std::make_unique<IceTower>(*this);
}
