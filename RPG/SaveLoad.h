//#pragma once
//#include "Player.h"
//#include <fstream>
//#include <ncurses.h>
//#include <conio.h>
//
//class SaveLoad {
//public:
//    Player* load() {
//        ifstream loadFile("emolod.txt", ios::binary);
//        if (!loadFile.is_open()) {
//            return nullptr;
//        }
//
//        Player* player = new Player();
//        // Assume Player has attributes like `int health` and `string name`
//        int health;
//        string name;
//
//        loadFile.read((char*)&health, sizeof(health));
//        getline(loadFile, name);
//
//        player->setHealth(health);
//        player->setName(name);
//
//        loadFile.close();
//        return player;
//    }
//
//    void save(Player* player) {
//        ofstream saveFile("emolod.txt", ios::binary);
//        if (!saveFile.is_open()) {
//            return;
//        }
//
//        int health = player->getHealth();
//        string& name = player->getName();
//
//        saveFile.write((char*)&health, sizeof(health));
//        saveFile << name << '\n';
//
//        saveFile.close();
//    }
//};