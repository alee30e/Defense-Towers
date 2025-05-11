#pragma once
#include<string>
#include<memory>

class Monstru 
{
    protected:
        int x;
        int y;
        int hp;
        int damage;
        std::string symbol;
        bool reachedTower;
        mutable bool addedGold = false;
    
    public:
        Monstru(int startX, int startY, int hp, int damage, const std::string& symbol);
        virtual ~Monstru() = default;

        virtual void move() = 0;
        virtual void takeDamage(int amount);
        virtual bool isAlive() const;
        virtual bool isDead() const;
        virtual bool hasReachedTower() const;
        virtual int getX() const;
        virtual int getY() const;
        virtual int getDamage() const {return damage;};
        virtual int getHP() const { return hp;};
        virtual std::string getSymbol() const; 
        virtual bool getAddedGold(); 
        virtual void setAddedGold() { addedGold = true; }
        
        
        virtual std::shared_ptr<Monstru> clone() const = 0;

};

class Zombie: virtual public Monstru
{
    public:
        Zombie(int x, int y, int hp, int damage, const std::string& sym) : Monstru(x, y, hp, damage, sym) {}

        // void move() override;
        // std::shared_ptr<Monstru> clone() const override {
        //     return std::make_shared<Zombie>(this);
        // }
};

class FastZombie:public Zombie 
{
    public:
        FastZombie(int x, int y) : Monstru(x, y, 60, 6, "F"), Zombie(x, y, 60, 6, "F") {}
        std::shared_ptr<Monstru> clone() const override {
            return std::make_shared<FastZombie>(*this);}
        void move() override;
};

class TankZombie:public Zombie
{
    int armor;
    public:

        TankZombie(int x, int y) :Monstru(x, y, 60, 6, "T"), Zombie(x, y, 90, 10, "T"), armor(20) {}
        void move() override;
        std::shared_ptr<Monstru> clone() const override {
            return std::make_shared<TankZombie>(*this);}
        int getArmor() const;
};

class Orc : public Monstru {
    public:
        Orc(int x, int y) : Monstru(x, y, 15, 5, "O") {}
        void move() override;
        std::shared_ptr<Monstru> clone() const override {
            return std::make_shared<Orc>(*this);
        }
    };
        class Goblin : public Monstru {
        public:
        Goblin(int x, int y) : Monstru(x, y, 16, 4, "G") {}
            void move() override;
            std::shared_ptr<Monstru> clone() const override {
                return std::make_shared<Goblin>(*this);
            }
        };
        