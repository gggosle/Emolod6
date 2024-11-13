#include <iostream>
#include <ctime>
#include <cmath>
#include <vector> 
#include "NameTrait.h" 
#include "Shield.h" 
#include "Characteristics.h"
#include "Weapon.h"
#include "FunctionHelper.h"
#include "Player.h"
#include "Monster.h"
#include "NameHelper.h"
#include "Engine.h"
#include "Event.h"
//#include "SaveLoad.h"
#include <fstream>
#include <conio.h>
#include <ncurses.h>


using namespace std;

int main() {
	
	srand(time(NULL));
	Player* player = NULL;
	NameHelper* nH = new NameHelper();
	
	Engine* engine = new Engine(new FunctionHelper(), new NameHelper());
//	SaveLoad* saveload = new SaveLoad();
//	cout << "Continue?(Press 'c')" << endl;
//	char choice;
//	cin >> choice;
//	if (choice == 'c') {
//	    player = saveload->load();
//	}

	    player = engine->playerGeneration();
        Weapon* fists = new Weapon("bare fists", 4, 0, 0);
        player->setWeapon(fists);
        Shield* adrenaline = new Shield("adrenaline", 4, 0, 0);
        player->setShield(adrenaline);




	cout << endl;
	player->stats();
	cout << endl;
	//cout << "To save your character's progress input 's'" << endl;
	cout << "To see your stats, input 't'" << endl;
	cout << "To get energy, input 'e'" << endl;

	Event* event = new Event(player, engine);
	int pos = 0;

	while (player->getLevel() < 10) {

		pos = 1 + rand() % 75;
		if (pos <= 10) {
			cout << endl;
			event->shop();
		}
		else if (pos > 10 && pos <= 45) {
			cout << endl;
			event->bumpIntoMonster();
		}
		else if (pos > 45 && pos <= 70) {
			cout << endl;
			player->setEnergy(player->getEnergy()+1);

			cout << "Have some rest" << endl;
			player->setHealthMax(player->getHealthMax() + 1);
			cout << "Health: " << player->getHealthMax() << endl;
			cout << "Energy: " << player->getEnergy();
		}
		else if (pos > 70 && pos <= 75) {
			cout << endl;
			event->potionShop();
		}

	}

}