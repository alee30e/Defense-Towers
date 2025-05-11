// Tower.hpp
#pragma once
#include "player.h"
#include "monster.h"
#include <string>
#include <memory>

class Tower {
protected:
    int level;
    int damage;
    int HP;
    int price;
    std::string symbol;
    mutable bool attacking=false;
    

public:
    Tower(int baseDamage, const std::string& sym);

     Tower(const Tower& other);
    Tower& operator=(const Tower& other);

    virtual ~Tower() = default;

    int getLevel() const;

    virtual void attack(Monstru& monster) const = 0;
    virtual bool canUpgrade(Player& player) const;
    virtual void upgrade(Player& player);
    virtual std::string getSymbol() const;
    virtual int getHP() const { return HP;}
    virtual int getDamage() const {return damage;}
    virtual bool isUp() const { return HP > 0;}
    virtual void getsAttacked(Monstru& monster);
    virtual std::unique_ptr<Tower> clone() const = 0;
    virtual bool isAttacking() const { return attacking; }
    virtual void resetAttacking() { attacking = false;}
};
    
class ArcherTower : public Tower {
public:
    ArcherTower();
    // void getsAttacked(Monstru& monster) override;
    void attack(Monstru& monster) const override;
    std::unique_ptr<Tower> clone() const override;
};

class CannonTower : public Tower {
public:
    CannonTower();
    // void getsAttacked(Monstru& monster) override;
    void attack(Monstru& monster) const ;
    std::unique_ptr<Tower> clone() const;
};

class MagicTower : public Tower {
public:
    MagicTower();
    // void getsAttacked(Monstru& monster) override;
    void attack(Monstru& monster) const override;
    std::unique_ptr<Tower> clone() const override;
};

class IceTower : public Tower {
public:
    IceTower();
    // void getsAttacked(Monstru& monster) override;
    void attack(Monstru& monster) const override;
    std::unique_ptr<Tower> clone() const override;
};
