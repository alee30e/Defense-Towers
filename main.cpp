// #include <iostream>
// #include <memory>
// #include <thread>
// #include <chrono>
// #include <vector>
// #include<algorithm>

// #include "player.h"
// #include "tower.h"
// #include "monster.h"
// #include "gameManager.h"

// void drawMap(const std::vector<std::shared_ptr<Monstru>>& monsters, const std::vector<std::shared_ptr<Tower>>& towers) {
//     const int rows = 4;
//     const int cols = 10;
//     std::vector<std::vector<std::string>> map(rows, std::vector<std::string>(cols, ". "));

//     for (const auto& monster : monsters) {
//         if (!monster->hasReachedTower() && monster->getX() >= 0 && monster->getY() >= 0) {
//             map[monster->getY()][monster->getX()] = monster->getSymbol() + " ";
//         }
//     }

//     for (int i = 0; i < rows; ++i) {
//         if (i < towers.size() && towers[i]) {
//             map[i][0] = towers[i]->getSymbol();
//         }
//     }

//     for (const auto& row : map) {
//         for (const auto& cell : row) {
//             std::cout << cell;
//         }
//         std::cout << "\n";
//     }
// }

// std::vector<std::shared_ptr<Monstru>> generateNextMonsters(int maxPerStep, int rows, int cols) {
//     std::vector<std::shared_ptr<Monstru>> newMonsters;
//     for (int i = 0; i < rows; ++i) {
//         int count = rand() % (maxPerStep + 1);  // până la maxPerStep monștri noi per rând
//         std::vector<int> positions;

//         while (positions.size() < static_cast<size_t>(count)) {
//             int x = rand() % cols;
//             if (std::find(positions.begin(), positions.end(), x) == positions.end()) {
//                 positions.push_back(x);
//             }
//         }

//         for (int x : positions) {
//             int type = rand() % 4; // cu Zombie inclus
//             if (type == 0)
//                 newMonsters.push_back(std::make_shared<Goblin>(x, i));
//             else if (type == 1)
//                 newMonsters.push_back(std::make_shared<Orc>(x, i));
//             else if (type == 2)
//                 newMonsters.push_back(std::make_shared<TankZombie>(x, i));
//             else
//                 newMonsters.push_back(std::make_shared<FastZombie>(x, i)); // dacă ai clasa Zombie
//         }
//     }
//     return newMonsters;
// }


#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include<algorithm>

#include "player.h"
#include "tower.h"
#include "monster.h"
#include "gameException.h"

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void drawMap(const std::vector<std::shared_ptr<Monstru>>& monsters, const std::vector<std::shared_ptr<Tower>>& towers) {
    const int rows = 4;
    const int cols = 10;
    std::vector<std::vector<std::string>> map(rows, std::vector<std::string>(cols, ". "));

    for (const auto& monster : monsters) {
        if ( monster->getX() >= 0 && monster->getY() >= 0) {
            map[monster->getY()][monster->getX()] = monster->getSymbol() + " ";
        }
    }

    // for (int i = 0; i < rows; ++i) {
    //     if (i < towers.size() && towers[i]) {
    //         map[i][0] = towers[i]->getSymbol();
    //     }
    // }
    for (int i = 0; i < rows; ++i) {
        if (i < towers.size() && towers[i]) {
            if (towers[i]->getHP() > 0) {
                map[i][0] = towers[i]->getSymbol();
            } else {
                map[i][0] = ". "; 
            }
        }
    }

    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
}

// std::vector<std::shared_ptr<Monstru>> spawnWave(int cols) {
//     std::vector<std::shared_ptr<Monstru>> monsters;
//     for (int i = 0; i < 4; ++i) {
//         int numMonsters = 1 + rand() % 3; // 1-3 monsters per row
//         std::vector<int> positions;

//         // Generate unique random positions for monsters in the row
//         while (positions.size() < static_cast<size_t>(numMonsters)) {
//             int pos = rand() % cols;
//             if (std::find(positions.begin(), positions.end(), pos) == positions.end()) {
//                 positions.push_back(pos);
//             }
//         }

//         for (int pos : positions) {
//             int type = rand() % 3;
//             if (type == 0)
//                 monsters.push_back(std::make_shared<Goblin>(pos, i));
//             else if (type == 1)
//                 monsters.push_back(std::make_shared<Orc>(pos, i));
//             else
//                 monsters.push_back(std::make_shared<FastZombie>(pos, i));
//         }
//     }
//     return monsters;
// }

std::vector<std::shared_ptr<Monstru>> spawnWave(int cols) {
    std::vector<std::shared_ptr<Monstru>> monsters;
    const int totalMonsters = 6;

    for (int i = 0; i < totalMonsters; ++i) {
        int row = rand() % 4; 
        int x = cols - 1;

        int type = rand() % 3;
        if (type == 0)
            monsters.push_back(std::make_shared<Goblin>(x, row));
        else if (type == 1)
            monsters.push_back(std::make_shared<Orc>(x, row));
        else
            monsters.push_back(std::make_shared<FastZombie>(x, row));
    }

    return monsters;
}

void afiseazaStatusTurele(const std::vector<std::shared_ptr<Tower>>& towers) {
    std::cout << "\n--- Status Turnuri ---\n";
    for (size_t i = 0; i < towers.size(); ++i) {
        if (towers[i]) {
            std::cout << "Turnul " << i + 1 << " (tip: " << towers[i]->getSymbol()
                      << ") - HP: " << towers[i]->getHP()
                      << " | Nivel: " << towers[i]->getLevel() << "\n";
        }
    }
    std::cout << "----------------------\n";
}

// void towersAttack(std::vector<std::shared_ptr<Tower>>& towers, std::vector<std::shared_ptr<Monstru>>& monsters, Player& player) {
//     for (size_t row = 0; row < towers.size(); ++row) {
//         auto& tower = towers[row];
//         if (!tower) continue;

//         for (auto& monster : monsters) {
//             if (monster->getY() == static_cast<int>(row) && monster->isAlive()) {
//                 int damage = tower->getDamage();
//                 tower->attack(*monster);

//                 if (tower->isAttacking()) 
//                 {
//                     std::cout << "Turnul " << row + 1 << " (" << tower->getSymbol()
//                           << ") a lovit monstrul " << monster->getSymbol()
//                           << " si i-a dat " << damage << " damage. ";
//                 }
//                 if (monster->getX() == 1) 
//                 {
//                     std::cout << "Monstrul a ajuns la turn!";
//                     tower->getsAttacked(*monster);
//                 }
//                 if (monster->isDead() && monster->getAddedGold()== false) {
//                     std::cout << "Monstrul a murit! +10 gold!\n" ;
//                     player.addGold(10);
//                     monster->setAddedGold();
                    
//                 } else {
//                     std::cout << "Monstrul are acum " << monster->getHP() << " HP.\n";
//                 }
//                 break;
//             }
//         }
//     }
//     monsters.erase(
//         std::remove_if(monsters.begin(), monsters.end(), [](const std::shared_ptr<Monstru>& m) {
//             return m->isDead();
//         }),
//         monsters.end()
//     );
// }

void towersAttack(std::vector<std::shared_ptr<Tower>>& towers, std::vector<std::shared_ptr<Monstru>>& monsters, Player& player) {
    for (size_t row = 0; row < towers.size(); ++row) {
        auto& tower = towers[row];
        if (!tower) continue;

        for (auto& monster : monsters) {
            if (monster->getY() == static_cast<int>(row) && monster->isAlive()) {
                int damage = tower->getDamage();
                tower->attack(*monster);

                if (tower->isAttacking()) {
                    std::cout << "Turnul " << row + 1 << " (" << tower->getSymbol()
                              << ") a lovit monstrul " << monster->getSymbol()
                              << " si i-a dat " << damage << " damage. ";
                }
                if (monster->getX() == 1) {
                    std::cout << "Monstrul a ajuns la turn!";
                    tower->getsAttacked(*monster);
                }
                if (monster->isDead() && monster->getAddedGold() == false) {
                    std::cout << "Monstrul a murit! +10 gold!\n";
                    player.addGold(10);
                    monster->setAddedGold();
                } else {
                    std::cout << "Monstrul are acum " << monster->getHP() << " HP.\n";
                }
                break;
            }
        }
    }

    for (auto& monster : monsters) {
        if (monster->getX() == 1) { 
            int row = monster->getY();
            if (row < towers.size() && (!towers[row] || towers[row]->getHP() <= 0)) {
                std::cout << "Un monstru a trecut de turnul distrus! Pierzi o viata!\n";
                player.loseLife();
            }
        }
    }

    monsters.erase(
        std::remove_if(monsters.begin(), monsters.end(), [](const std::shared_ptr<Monstru>& m) {
            return m->isDead();
        }),
        monsters.end()
    );
}

void upgradePhase(Player& player, std::vector<std::shared_ptr<Tower>>& towers) {
    std::cout << "\nUpgrade phase. Aur disponibil: " << player.getGold() << "\n";
    afiseazaStatusTurele(towers);

    for (size_t i = 0; i < towers.size(); ++i) {
        auto& tower = towers[i];
        if (!tower) continue;

        std::cout << "Vrei sa upgradezi turnul " << i + 1 << " (cost 20 gold)? (y/n): ";
        char raspuns;
        std::cin >> raspuns;

        if (raspuns == 'y' || raspuns == 'Y') {
            if (player.getGold() >= 20) {
                tower->upgrade(player);
                player.spendGold(20);
                std::cout << "Turnul " << i + 1 << " a fost upgradat.\n";
            } else {
                std::cout << "Nu ai suficient aur pentru upgrade!\n";
            }
        }
    }

    std::cin.ignore();
    std::cout << "Apasa Enter pentru a continua...";
    std::cin.get();
}


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    try {
        std::cout << "Introdu numele: ";
        std::string playerName;
        std::getline(std::cin, playerName);

        if (playerName.empty()) {
            throw InvalidNameException(playerName);
        }

        Player player(playerName);

        std::vector<std::shared_ptr<Tower>> towers = {
            std::make_shared<ArcherTower>(),
            std::make_shared<CannonTower>(),
            std::make_shared<MagicTower>(),
            std::make_shared<IceTower>()
        };

        const int cols = 10;
        const int maxRounds = 3;
        const int wavesPerRound = 4;

        for (int round = 1; round <= maxRounds; ++round) {
            
            std::cout << "=== RUNDA " << round << " ===\n";

            for (int wave = 1; wave <= wavesPerRound; ++wave) {
                std::cout << "-- Wave " << wave << " --\n";
                auto monsters = spawnWave(cols);

                while (!monsters.empty()) {
                    clearScreen();
                    drawMap(monsters, towers);
                    towersAttack(towers, monsters, player);

                    for (auto& monster : monsters) {
                        monster->move();
                    }

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }

                upgradePhase(player, towers);
            }

            std::cout << "Runda completa!\nApasa Enter...";
            std::cin.get();
        }

        std::cout << "Joc pierdut! Multumim, " << player.getName() << "!\n";

    } catch (const GameException& ex) {
        std::cout << "Eroare: " << ex.what() << "\n";
    }

    return 0;
}
