#pragma once
#include "Player.h"
#include "Monster.h"
#include "Engine.h"
#include <vector>
#include "FunctionHelper.h"
#include "NameHelper.h"
#include <iostream>
#include "PotionInterface.h"
#include "HpPotion.h"
#include "PPotion.h"
#include "ExpPotion.h"
#include "EPotion.h"
#include "APotion.h"
#include <ctime>
using namespace std;

class Event {
private:
	int n = 0;

	//Monster* monster = NULL;
	Player* player = NULL;
	Engine* engine = NULL;
	vector <Shield*> shiel;
	vector <Weapon*> weap;
	vector <PotionInterface*> inventory;
public:
	Event(Player* player, Engine* engine) {
		this->player = player;
		this->engine = engine;
	}

	int potionShop() {
        // Check if the player has enough cash for the cheapest potion
        if (this->player->getCash() < this->engine->aPotionGeneration()->getPrice()) {
            return 0;
        }

        // Check if the player has at least 60 grivnas to enter the shop
        if (this->player->getCash() >= 60) {
            int c = 0;
            cout << "You look in your wallet and see " << this->player->getCash() << " grivnas" << endl;

            // Clear the inventory and generate 5 random potions
            inventory.clear();
            for (int i = 0; i < 5; i++) {
                int k = rand() % 5;
                switch (k) {
                    case 0: inventory.push_back(this->engine->aPotionGeneration()); break;
                    case 1: inventory.push_back(this->engine->ePotionGeneration()); break;
                    case 2: inventory.push_back(this->engine->pPotionGeneration()); break;
                    case 3: inventory.push_back(this->engine->expPotionGeneration()); break;
                    case 4: inventory.push_back(this->engine->hpPotionGeneration()); break;
                }
            }

            // Display the inventory
            for (int i = 0; i < 5; i++) {
                cout << i + 1 << ". ";
                inventory[i]->showPotionData(inventory[i]->getName());
            }

            // Prompt the player for their choice
            cout << "Input number of item you chose or other if you want to leave: " << endl;
            cin >> c;

            // Process the player's choice
            if (c >= 1 && c <= 5) {
                int index = c - 1;
                if (this->player->getCash() >= inventory[index]->getPrice()) {
                    inventory[index]->drink(player);
                } else {
                    cout << "Unfortunately, you don't have enough money for this item" << endl;
                }
            }

            // Exit message
            cout << "Good luck on your way, " << this->player->getName() << endl;
        }

        return 0;
    }

	int shop() {
        if (this->player->getCash() < this->engine->weaponGeneration()->getPrice()) {
            cout << "You don't have enough money to buy anything from the shop." << endl;
            return 0;
        }

        cout << "You look in your wallet and see " << this->player->getCash() << " grivnas" << endl;

        // Clear existing inventory
        shiel.clear();
        weap.clear();

        // Generate shields
        for (int i = 0; i < 3; i++) {
            shiel.push_back(this->engine->shieldGeneration());
        }

        // Generate weapons
        for (int i = 0; i < 3; i++) {
            weap.push_back(this->engine->weaponGeneration());
        }

        // Display shields
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". ";
            shiel[i]->showShieldData();
        }

        // Display weapons
        for (int i = 0; i < 3; i++) {
            cout << i + 4 << ". ";
            weap[i]->showWeaponData();
        }

        // Player choice
        int choice;
        cout << "Input the number of the item you want to buy or any other number to leave: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) { // Buying a shield
            int index = choice - 1;
            if (shiel[index]->getPrice() <= this->player->getCash()) {
                this->player->setCash(this->player->getCash() - shiel[index]->getPrice());
                this->player->setShield(shiel[index]);
                cout << "You bought a shield." << endl;
            } else {
                cout << "Unfortunately, you don't have enough money to buy this shield." << endl;
            }
        } else if (choice >= 4 && choice <= 6) { // Buying a weapon
            int index = choice - 4;
            if (weap[index]->getPrice() <= this->player->getCash()) {
                this->player->setCash(this->player->getCash() - weap[index]->getPrice());
                this->player->setWeapon(weap[index]);
                cout << "You bought a weapon." << endl;
            } else {
                cout << "Unfortunately, you don't have enough money to buy this weapon." << endl;
            }
        } else {
            cout << "You decided to leave the shop." << endl;
        }

        return 0;
    }



	bool bumpIntoMonster() {
		Monster* monster = this->engine->monsterGeneration(this->player->getLevel());
		this->engine->fight(player, monster);
		return 0;
	}
};
