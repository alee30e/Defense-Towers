// Player.cpp
#include "Player.h"

Player::Player() : name("Unnamed"), gold(0) {}

Player::Player(const std::string& name, int gold, int lifes) : name(name), gold(0), lifes(3) {}

const std::string& Player::getName() const {
    return name;
}

int Player::getGold() {
    return gold;
}
int Player::getLifes() {
    return lifes;
}
int Player::takeLife()
{
    lifes--;
    return lifes;
}
void Player::loseLife() {
    if (lifes > 0) {
        --lifes;
    }
    if (lifes == 0)
    {
        std::cout<<"Ai pierdut toate vietile!";
        exit(0);
    }
}

void Player::addGold(int amount) {
    gold += amount;
}

bool Player::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}
