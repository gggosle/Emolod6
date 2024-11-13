#pragma once
#include "NameTrait.h"
#include "FunctionHelper.h"
#include <iostream>
using namespace std;
class Characteristics : public NameTrait
{

protected:
	int health = 0;
	int healthMax = 0;
	int energy = 0;
	int energyMax = 0;
	int level = 0;
	FunctionHelper* fH = NULL;

public:
	Characteristics(int health, int energy, string name, int level) : NameTrait(name)
	{
		this->healthMax = health;
		this->health = health;
		this->energy = energy;
		this->energyMax = energy;
		this->level = level;
		this->fH = new FunctionHelper();
	}

	void setHealth(int health) {
		this->health = health;
	}
	int getHealth() {
		return this->health;
	}
	void setHealthMax(int healthMax) {
		this->healthMax = healthMax;
	}
	int getHealthMax() {
		return this->healthMax;
	}
	void setEnergy(int energy) {
			this->energy = energy;
	}
	/*int getEnergyMax() {
		return this->energy;
	}
	void setHealthMax(int healhMax) {
		this->healthMax = healthMax;
	}*/
	int getEnergy() {
		return this->energy;
	}
	void setName(std::string& name) {
		this->name = name;
	}
	string getName() {
		return this->name;
	}
	void setLevel(int level) {
		this->level = level;
	}
	int getLevel() {
		return level;
	}

};


