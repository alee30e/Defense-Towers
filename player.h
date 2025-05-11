// Player.hpp
#pragma once

#include <string>
#include<iostream>

class Player {
private:
    std::string name;
    int gold;
    int lifes;

public:
    Player();
    Player(const std::string& name, int gold = 0, int = 3);

    const std::string& getName() const;
    int getGold();
    int getLifes();
    int takeLife();
    void loseLife();

    void addGold(int amount);
    bool spendGold(int amount);
};
