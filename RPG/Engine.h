#pragma once
#include "Monster.h"
#include "Player.h"
#include "NameHelper.h"
//#include "SaveLoad.h"
//#include "Event.h"

#include <ctime>
#include "FunctionHelper.h"
#include "SkillInterface.h"
#include "MSkillInterface.h"
#include "Block.h"
#include "Attack.h"
#include "CriticalAttack.h"
#include "MBlock.h"
#include "MAttack.h"
#include <iostream>
#include <cstdlib>
#include "PotionInterface.h"
#include "APotion.h"
#include "EPotion.h"
#include "PPotion.h"
#include "ExpPotion.h"
#include "HpPotion.h"
using namespace std;

class Engine {
private:
	Monster* monster = NULL;
	Player* player = NULL;
	FunctionHelper* fH = NULL;
	NameHelper* nH = NULL;
	//SaveLoad* saveL = NULL;
	SkillInterface* skill = NULL;
	MSkillInterface* mskill = NULL;

	bool defenseChance() {
		int defenseChance = ((((this->player->getShield()->getDefense() + this->player->getEndurance()) - 3) + 1) * 100) / this->player->getC();
		if (1 + rand() % defenseChance == 1 + rand() % defenseChance) {
			return 1;
		}
		return 0;
	}

	bool monsterDefenseChance() {
        int c = 22;
        c += this->monster->getLevel() * 4;
        int shieldChance = (this->fH->randomRes(1, c) * 100) / c;

        int rand1 = 1 + rand() % shieldChance;
        int rand2 = 1 + rand() % shieldChance;

        if (rand1 == rand2) {
            return true;
        }

        return false;
    }



	bool criticalChance() {
		int percentage = 6;
		percentage += 5 * (this->player->getLevel()-1);
		
		int criticalChance = this->player->getAgility() * 10 / percentage;
		if (criticalChance != 0) {

			if (1 + (rand() % (10 / criticalChance)) == 1 + (rand() % (10 / criticalChance))) {
				return 1;
			}
		}
		return 0;
	}
	

	int monsterTurn(int miss) {
		int gap = 0;
		int f = 0;

		int mb = 0;
		int chance = rand() % 3;
		if (miss == 1) {
			cout << this->player->getName() << "'s block" << endl;
			return 0;
		}
		else if(miss == 2) {
			cout << this->player->getName() << "'s block" << endl;
			return 2;
		}
		if (monsterDefenseChance() == 1) {
			mb = 1;
		}
		if (monsterDefenseChance() == 1 && chance == 0) {
			mskill = new MBlock();
			this->monster->setHealth(mskill->use(this->monster));
			f = this->monster->getHealth();
		}
		else {
			mskill = new MAttack();
			gap = this->mskill->use(this->monster);
			f = this->player->getHealth() - gap;
		}

		if (f < this->player->getHealth()) {
			(f < 0) ? player->setHealth(0) : this->player->setHealth(f);
			cout << "-" << gap << endl << "Your health: " << this->player->getHealth() << endl;

		}

		return mb;
	}
	
	int playerTurn(int miss) {
		int f = 0;
		char action = 0;
		int gap = 0;
		bool cc = 0;
		bool dc = 0;
		int pc = 0;
		bool kc = 0;
		bool rc = 0;
		if (miss == 1) {
			cout << this->monster->getName() << "'s block" << endl;
			return 0;
		}
		else if (miss == 2) {
			cout << "To get critical attack, input 'c'" << endl;
			cc = 1;
		}
		cout << "To attack input 'a'" << endl;
		if (criticalChance() == true && this->monster->getId() == this->player->getWeapon()->getId()) {
			cout << "To get double attack, input 'k'" << endl;
			kc = 1;
		}
		if (defenseChance() == true && this->monster->getId() == this->player->getShield()->getId()) {
			cout << "To get health regeneration + attack, input 'r'" << endl;
			rc = 1;
		}
		if (criticalChance() == true && miss != 2) {
			cout << "To get critical attack, input 'c'" << endl;
			cc = 1;
		}
		if (defenseChance() == true) {
			cout << "To get shield, input 'd'" << endl;
			dc = 1;
		}
		if (defenseChance() == true) {
			pc = 1;
		}
		cin >> action;
		if (action == 'a') {
			this->skill = new Attack();
			gap = this->skill->use(this->player);
			f = this->monster->getHealth() - gap;
		}
		else if (rc == 1 && action == 'r') {
			this->player->healthRegeneration();
			this->skill = new Attack();
			gap = this->skill->use(this->player);
			f = this->monster->getHealth() - gap;
		}
		else if (cc == 1 && action == 'c') {
			this->skill = new CriticalAttack();
			gap = this->skill->use(this->player);
			f = this->monster->getHealth() - gap;
		}
		else if (kc == 1 && action == 'k') {
			this->skill = new CriticalAttack();
			gap = this->skill->use(this->player);
			f = this->monster->getHealth() - gap;
			pc = 2;
		}
		else if (dc == 1 && action == 'd') {
			this->skill = new Block();
			this->player->setHealth(this->player->getHealth() + this->skill->use(this->player));
			f = this->monster->getHealth();
			cout << "Your health++: " << this->player->getHealth() << endl;
		}
		else {
			cout << "missed hit" << endl;
			return 0;
		}
		if (f < this->monster->getHealth()) {
			(f < 0) ? monster->setHealth(0) : this->monster->setHealth(f);

			cout << "-" << gap << endl << "Monster's health : " << this->monster->getHealth() << endl;
		}
		return pc;
	}

	void win() {
		if (rand() % 3 == 0) {
			char choice = 0;
			cout << "You've run into the guard. Run or pay 200 griven fine for killing an extinct creature.('r'?'p')" << endl;
			cin >> choice;
			if (choice == 'p') {
				this->player->setCash(this->player->getCash() - 200);
			}
			else if(choice == 'r') {
				this->player->setEnergy(this->player->getEnergy() - rand() % 15 + 1);
				if (this->player->getEnergy() < 0) { 
					this->player->setEnergy(0);
					cout << "Unfortunately, you were not fast enough, -500 griven" << endl;
					this->player->setCash(this->player->getCash() - 500);
				}
				else {
					cout << "You've escaped succesfully!" << endl;
					this->player->setCash(this->player->getCash() + this->monster->getCash());
					cout << "Your experience: +" << monster->getPlayerExperience() << endl;

					this->player->setExperience(this->monster->getPlayerExperience());
					cout << "Your cash: +" << monster->getCash() << endl;

				}
			}

		}
		else {
			this->player->setCash(this->player->getCash() + this->monster->getCash());
			cout << "Your experience: +" << monster->getPlayerExperience() << endl;

			this->player->setExperience(this->monster->getPlayerExperience());
			cout << "Your cash: +" << monster->getCash() << endl;

		}
		if (this->monster->getName() == "Yeti") {
			cout << "Your experience: +" << monster->getPlayerExperience() << endl;
			cout << " 'Regulations Governing Mountain Climbing Expeditions in Nepal - Relating to Yeti.':" << endl;
			cout << "2. Hunters can photograph or catch a Yeti but not shoot or kill it - unless in self-defense." << endl;
			cout << "Penalty: 500 griven" << endl;
			this->player->setCash(this->player->getCash() - 500);
		}
	}
public:
	Engine(FunctionHelper* fH, NameHelper* nH)
	{
		this->fH = fH;
		this->nH = nH;

	}

	Shield* shieldGeneration() {
		int defense = this->fH->randomRes(4, 20);
		int price = defense * 200;
		string name = this->nH->getShieldName();
		return new Shield(name, defense, price, nH->getShieldId(name));
	}

	Weapon* weaponGeneration() {

		int damage = this->fH->randomRes(4, 20);
		int price = damage * 200;
		string name = this->nH->getWeaponName();

		return new Weapon(name, damage, price, this->nH->getWeaponId(name));
	}


	Player* playerGeneration() {
		int power = 1, endurance = 1, agility = 1;
		int choice = 0;
		string name = "";


		cout << "Name:";
		cin >> name;
		cout << "Your role(barbarian - 1, tank - 2, thief - 3): ";
		cin >> choice;
		if (choice == 1) {
			power += 3;
		}
		else if (choice == 2) {
			endurance += 3;
		}
		else {
			agility += 3;
		}


		return new Player(35, 30, 1, power, agility, endurance, name, 50);
	}

	Monster* monsterGeneration(int level) {

		level = this->fH->randomRes(level - 1, level + 1);

		int health = 25;
		int energy = 25;
		/*int cash = 10;
		cash = this->fH->getCharacteristic(cash, level, 5);*/

		health = this->fH->getCharacteristic(health, level - 1, 10);
		energy = this->fH->getCharacteristic(energy, level, 10);
		int playerExperience = this->fH->getCharacteristic(0, level, 10);
		string name = this->nH->getMonsterName();
		Monster* monster = new Monster(
			name,
			health,
			energy,
			playerExperience,
			level, this->nH->getMonsterId(name));

		return monster;
	}
	
	PPotion* pPotionGeneration() {
		int def = this->fH->randomRes(3, 10);
		int price = def * 200;
		PPotion* power = new PPotion(price, def);
		return power;
	}
	APotion* aPotionGeneration() {
		int def = this->fH->randomRes(3, 10);
		int price = def * 200;
		APotion* agility = new APotion(price, def);
		return agility;
	}
	EPotion* ePotionGeneration() {
		int def = this->fH->randomRes(3, 10);
		int price = def * 200;
		EPotion* endurance = new EPotion(price, def);
		return endurance;
	}
	ExpPotion* expPotionGeneration() {
		int def = this->fH->randomRes(10, 60);
		int price = def * 20*3;
		ExpPotion* experience = new ExpPotion(price, def);
		return experience;
	}
	HpPotion* hpPotionGeneration() {
		int def = this->fH->randomRes(3, 10);
		int price = def * 200;
		HpPotion* health = new HpPotion(price, def);
		return health;
	}
	int fight(Player* player, Monster* monster) {
		//this->saveL = new SaveLoad();
		int f = 0;
		char choice;
		this->player = player;
		this->monster = monster;
		cout << endl << "Your opponnent's stats: "<<endl << this->monster->getName() << endl << "Level: " << this->monster->getLevel() << endl << "Health: " << this->monster->getHealth() << endl;
		cout << "Experience: " << this->monster->getPlayerExperience() << endl << "Cash: " << this->monster->getCash() << endl;
		if (this->monster->getId() == this->player->getWeapon()->getId() || this->monster->getId() == this->player->getShield()->getId()) {
			cout << "You've got an advantage over this monster " << endl;
		}
		cout << "You wanna fight?(y/n)";
		cin >> choice;

		if (choice == 't') {
			this->player->stats();
			return 0;
		}

		if (choice == 'e') {
			char in = 0;
			
			cout << "20 energy points - 400 griven('y' / 'n') " << endl;
			cin >> in;
			if (in == 'y') {
				this->player->energyRegeneration();
				this->player->setCash(this->player->getCash() - 400);
			}
			return 0;
		}
//		else if (choice == 's') {
//			this->saveL->save(player);
//			cout << "You saved your progress" << endl;
//			return 0;
//		}
		else if (choice != 'y') {
			return 0;
		}
		this->player->setEnergy(this->player->getEnergy() - this->monster->getLevel() * 2);
		if (this->player->getEnergy() < 0) {
			this->player->setEnergy(0);

			int robbery = 100 * this->monster->getLevel() + rand() % 200;
				cout << "You ran out of energy and fell. " << this->monster->getName() << " robbed you of " << robbery << " griven" << endl;
				this->player->setCash(this->player->getCash() - robbery);
			return 0;
		}

		int c = rand() % 2;
		int pd = 0;
		int md = 0;
		if (c == 1) {
			cout << "Your turn!" << endl;
			do {
				pd = playerTurn(md);
				if (this->monster->getHealth() <= 0) {
					cout << "You win!" << endl;
					win();
					break;
				}
				md = monsterTurn(pd);
				if (this->player->getHealth() <= 0) {
					cout << "You lose!" << endl;
					break;
				}
			} while (this->player->getHealth() > 0 || this->monster->getHealth() > 0);
		}
		else {
			cout << "Opponent's turn!" << endl;
			do {
				md = monsterTurn(pd);
				if (this->player->getHealth() <= 0) {
					cout << "You lose!" << endl;
					break;
				}
				pd = playerTurn(md);
				if (this->monster->getHealth() <= 0) {
					cout << "You win!" << endl;
					win();
					break;
				}
			} while ((this->player->getHealth() > 0 || this->monster->getHealth() > 0));
		}

		return this->player->healthRegeneration();



	}
};