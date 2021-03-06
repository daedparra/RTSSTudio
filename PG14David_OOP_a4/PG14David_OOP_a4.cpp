// PG14David_OOP_a4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

//Unit Class for the creation of every member of the army
class Unit {
public:
	//function for making damage to other unit
	void MakeDamage(Unit* target) {
		target->ReceiveDamage(mAttack);
	}
	//Constructor for every unit
	Unit(string name, int health, int attack)
		:mName(name),
		mHealth(health),
		mAttack(attack){}
	//get the power attack
	int getAttack() {
		return mAttack;
	}
	//Current health
	int getHealth() {
		return mHealth;
	}
	//print in console
	string nameYourself() {
		return mName + " CurHealth: " + to_string(mHealth) + "/ Attack: " + to_string(mAttack);
	}

protected:
	string mName;
	int mHealth;
	int mAttack;
	//function for dealing with damage
	void ReceiveDamage(int damage) {
		mHealth -= damage;
	}
};
//Elve class inherit from Unit
class Elve : public Unit {
public:
	Elve(string name, int health, int attack) : Unit(name, health, attack) {}
};
//Dwarf class inherit from Unit
class Dwarf : public Unit {
public:
	Dwarf(string name, int health, int attack) : Unit(name, health, attack) {}
};
//Creating factory for every unit in the army
class Factory {
public:
	//singleton for only one factory
	static Factory* getInstance() {
		if (Factory::mInstance == nullptr) {
			Factory::mInstance = new Factory();
		}
		return Factory::mInstance;
	}

	// 1 is Elves. 2 is Dwarfs
	Unit* newUnit(int type,int powerAttack) {
		if (type == 1) {
			elves++;
			return new Elve("elve(" + to_string(elves) + ")", 100, powerAttack);
		}
		else{
			dwarfs++;
			return new Dwarf("dwarf(" + to_string(dwarfs) + ")", 100, powerAttack);
		}
	}
protected:
	Factory() {
	}

private:
	static Factory* mInstance;

	int elves = 0;
	int dwarfs = 0;
};

Factory* Factory::mInstance = nullptr;

//Depending on what the user sets the random units will be generated
vector<Unit*>* createArmy(int unitAmount, int maxPower, Factory* factory,int type) {
	vector<Unit*>* unitArmy = new vector<Unit*>();
	if (type == 1) {
		// generate random power elves
		for (int i = 0; i < unitAmount; i++) {
			int random = (rand() % maxPower + 1);
			unitArmy->push_back(factory->newUnit(type, random));
		}
	}
	else {
		// generate random power dwarfs
		for (int i = 0; i < unitAmount; i++) {
			int random = (rand() % maxPower + 1);
			unitArmy->push_back(factory->newUnit(type, random));
		}
	}
	return unitArmy;
}

//Random to set the attacker and the enemy
int Where(vector<Unit*>* unitArmy) {
	int minimum = 0;
	int maximum = unitArmy->size() - 1;
	return (rand() % (maximum-minimum +1)+ minimum);
}
//random for knowing what team will atack
bool whoseAttacking() {
	if (rand() % 2 == 0)
		return true;
	else
		return false;
}
//do actual damage to other unit from the other army
void Melee(vector<Unit*>* unitArmy1, vector<Unit*>* unitArmy2, string ArmyName) {
	int indexAttacker = Where(unitArmy1);
	int indexEnemy = Where(unitArmy2);

	Unit * attacker = unitArmy1->at(indexAttacker);
	Unit * enemy = unitArmy2->at(indexEnemy);
	cout << "From --" << ArmyName << "--" << endl;
	cout << "The " + attacker->nameYourself() << " will attack: " << endl << enemy->nameYourself() << endl;
	attacker->MakeDamage(enemy);

	if (enemy->getHealth() < 1) {
		cout << endl;
		cout << " xDEADx" << endl;
		unitArmy2->erase(unitArmy2->begin() + indexEnemy);
	}
}

int main()
{
	//seed to generate every time random values
	srand(time(NULL));
	int amount = 0;
	int power = 0;
	bool decision;
	Factory* factory = Factory::getInstance();

	cout << "How many units do you want the army to have: ";
	cin >> amount;
	cout << "Range of power (e.g 5): ";
	cin >> power;

	//creating army for the user input
	vector<Unit*>* unitArmy1 = createArmy(amount, power, factory, 1);
	vector<Unit*>* unitArmy2 = createArmy(amount, power, factory, 2);

	//actual fight for every unit
	int turns = 0;
	while (unitArmy1->size() != 0 && unitArmy2->size() != 0) {
		turns++;
		cout << "Turn: " << to_string(turns) << endl;
		decision = whoseAttacking();
		if (decision) {
			Melee(unitArmy1, unitArmy2, "Elves");
		}
		else {
			Melee(unitArmy2, unitArmy1, "Dwarfs");
		}

	}
	//when some army has nothing 
	cout << endl;
	cout << "And the winner army is: " << endl;
	if (unitArmy1->size() != 0) {
		cout << "ELVES" << " with still " + to_string(unitArmy1->size()) + " units" << endl; 
	}
	else {
		cout << "Dwarfs" << " with still " + to_string(unitArmy2->size()) + " units" << endl; 
	}
	cout << endl;
	system("pause");
	return 0;
}
