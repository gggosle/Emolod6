#pragma once
#include "Characteristics.h"
#include <iostream>
#include "Shield.h"
#include "Weapon.h"
using namespace std;

class Player : public Characteristics {
private:
	int hp = 0;
	int mp = 0;
	int exp = 0;
	int power = 0;
	int c = 22;
	int agility = 0;
	int endurance = 0;
	int experience = 0;
	int experienceMax = 0;
	int playerDamage = 0;
	int playerDefense = 0;
	int cash = 0;
	Shield* shield = NULL;
	Weapon* weapon = NULL;

public:
	Player(int health, int energy, int level, int power, int agility, int endurance, string name, int cash) :Characteristics(health, energy, name, level)
	{
		this->hp = 100;
		this->mp = 50;
		this->exp = 10;
		this->cash = cash;
		this->power = power;
		this->agility = agility;
		this->endurance = endurance;
		this->experience = 0;
		this->level = level;
		this->experienceMax = 100 * this->level;

	}

	void setHp(int hp) {
		this->hp = hp;
	}
	int getHp() {
		return this->hp;
	}

	void setMp(int mp) { 
		this->mp = mp;
	}
	int getMp() {
		return this->mp;
	}

	void setExp(int exp) {
		this->exp = exp; 
	}
	int getExp() {
		return this->exp;
	}
	int getEndurance() {
		return this->endurance;
	}
	int getPower() {
		return this->power;
	}
	int getAgility() {
		return this->agility;
	}

	void stats() {
		(this->cash >= 0) ? cout << endl << "Cash: " << this->cash << endl : cout << endl<< "You're in debt of " << this->cash*(-1) << " griven" << endl;
		cout << "Power: " << this->power << endl;
		cout << "Agility: " << this->agility << endl;
		cout << "Endurance: " << this->endurance << endl;
		cout << "XP: " << this->experience << endl;
		cout << "Level: " << this->level << endl;
		cout << "Health: " << this->healthMax << endl;
		cout << "Your weapon: " << this->getWeapon()->getName() << " with damage value " << this->getWeapon()->getDamage() << endl;
		cout << "Your shield: " << this->getShield()->getName() << " with defense value " << this->getShield()->getDefense() << endl;
		cout << "Energy: " << this->energy << endl;

	}
	int levelUp() {
		this->level += 1;
		this->agility += rand() % 5;
		this->endurance += rand() % 5;
		this->power += rand() % 5;
		this->health = this->healthMax;
		this->c += 4;
		this->experience = 0;

		cout <<endl<< "Congrats! You've reached new level!" << endl;
		cout << "Your power now: " << getPower() << endl;
		cout << "Your agility now: " << getAgility() << endl;
		cout << "Your endurance now: " << getEndurance() << endl;


		return 1;
	}
	int getLevel() {
		return this->level;

	}
	int getC() {
		return this->c;

	}
	void setCash(int cash) {
		this->cash = cash;
	}
	int getCash() {
		return cash;
	}

	int healthRegeneration() {
		return this->health = this->healthMax;
		cout << "Genius of the year" << endl;
	}
	int energyRegeneration() {
		return this->energy = this->energyMax;
	}
	void setShield(Shield* shield) {
		this->shield = shield;
	}

	Shield* getShield() {
		return this->shield;
	}

	void setWeapon(Weapon* weapon) {
		this->weapon = weapon;
	}

	Weapon* getWeapon() {
		return this->weapon;
	}

	void setPower(int power) {
		this->power = power;
	}
	void setAgility(int agility) {
		this->agility = agility;
	}
	void setEndurance(int endurance) {
		this->endurance = endurance;
	}
	int cashUp(int cash) {
		this->cash += cash;
	}
	void setExperience(int experience) {
		if (this->experienceUp(experience) > this->experienceMax) {
			this->experience = this->experienceUp(experience) - this->experienceMax;
			this->levelUp();
		}
		else {
			this->experienceUp(experience);
		}
	}
	int experienceUp(int experience) {
		this->experience += experience;

		return this->experience;
	}
	int getExperience() {
		return experience;
	}
	void setCriticalDamage(int damage) {
		playerDamage =  this->fH->getCharacteristic(health, level-1, 10);
		/*int percentage = 4;
		for (int i = 0; i < level; i++) {
			percentage += 4;
		}
		int criticalChance = agility * 100 / percentage;
		if (criticalChance != 0) {


			if (1 + rand() % (10 / criticalChance) == 1 + rand() % (10 / criticalChance)) {
				playerDamage =  this->fH->getCharacteristic(health, level, 10);
			}
		}*/
	}
	

	void setDamage(int damage) {
		playerDamage = (((damage + this->power) - 3) * this->fH->getCharacteristic(health, level, 10)) / this->c;	

		}
	int getDamage() {
		return playerDamage;
	}

	int getDefense(int defense) {
		return playerDefense = (((defense + endurance) - 3) * this->fH->getCharacteristic(health, level, 10)) / this->c;

	}
};


