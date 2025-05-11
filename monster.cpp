
#include "monster.h"

Monstru::Monstru (int startX, int startY, int health, int dmg, const std::string& sym)
    : x(startX), y(startY), hp(health), damage(dmg), symbol(sym), reachedTower(false){}
// Monstru::Monstru 
void Monstru::takeDamage(int amount){
    hp = hp - amount;
    if (hp < 0) hp = 0;
}

bool Monstru::getAddedGold(){
    return addedGold;
}

bool Monstru::isAlive() const {
    return hp > 0;
}

bool Monstru::hasReachedTower() const {
    return reachedTower;
}

bool Monstru::isDead() const {

    return !isAlive();
}

int Monstru::getX() const {
    return x;
}

int Monstru::getY() const {
    return y;
}

std::string Monstru::getSymbol() const {
    return symbol;
}

void FastZombie::move()
{
    if (x > 2) x-=2;
    else reachedTower = true;
}

void Orc::move()
{
    if (x>1) x-=1;
    else reachedTower = true;
}

void Goblin::move()
{
    if (x>1) x-=1;
    else reachedTower = true;
}

int TankZombie::getArmor() const{
    return armor;
}


