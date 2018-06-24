#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "dynamicArray.h"
#include "nfs.h"
#include "realCompetitor.h"
#include "virtualCompetitor.h"

using namespace std;

const int POINTS = 10;
const int WINNER_SKILLS = 15;
const int WINNER_CASH = 150;
const int MAX_SIZE = 1000;
const int VIRTUAL = 10;

Nfs::Nfs(int m, int n) : numberRealCompetitors(m), numberVirtualCompetitors(n), competitors(m + n), isFreeRealEnemy(m),
	isFreeVirtualEnemy(n), enemies(m + n), competitionsCounter(0), numberFreeRealCompetitors(0), numberFreeVirtualCompetitors(0) {
	for (int i = 0; i < m; i++) {
		competitors[i] = new RealCompetitor;
		assert(competitors[i] != NULL);
	}
	for (int i = m; i < m + n; i++) {
		competitors[i] = new VirtualCompetitor;
		assert(competitors[i] != NULL);
	}
}
Nfs::~Nfs() {
	int allPlayers = numberRealCompetitors + numberVirtualCompetitors;
	for (int i = 0; i < allPlayers; i++) delete competitors[i];
}
void Nfs::startGame() {
	cout << endl;
	cout << "Let's start playing..." << endl;
	generateCompetitors();
	startRound();
}
void Nfs::nextRound() {
	cout << endl;
	cout << ">> Do you want to play more?" << endl;
	cout << ">> If you want - type 'Y', if no - type 'N'" << endl;
	char symbol;
	do {
		cin >> symbol;
	} while (symbol != 'Y' && symbol != 'N');
	if (symbol == 'Y') startRound();
	else if (symbol == 'N') {
		cout << ">> You have quit the NFS game!" << endl;
		return;
	}
}
void Nfs::startRound() {
	numberFreeRealCompetitors = 0;
	numberFreeVirtualCompetitors = 0;
	int allPlayers = numberRealCompetitors + numberVirtualCompetitors;
	for (int i = 0; i < numberRealCompetitors; i++) {
		isFreeRealEnemy[i] = true;
		numberFreeRealCompetitors++;
	}
	for (int i = 0; i < numberVirtualCompetitors; i++) {
		isFreeVirtualEnemy[i] = true;
		numberFreeVirtualCompetitors++;
	}
	for (int i = 0; i < allPlayers;i++) {
		enemies.pop();
		enemies[i] = -1;
	}
	if ((competitionsCounter + 1) % 3 == 0) {
		for (int i = 0; i < numberRealCompetitors; i++) {
			competitors[i]->getBestCar()->addPoints(POINTS);
		}
		for (int i = numberRealCompetitors; i < allPlayers; i++) {
			competitors[i]->getBestCar()->addPoints(POINTS);
		}
	}
	competitionsCounter++;
	chooseAction();
	chooseRandomEnemy();
	compete();
	ranking();
	nextRound();
}
void Nfs::generateCompetitors() {
	srand(time(NULL));
	int allPlayers = numberRealCompetitors + numberVirtualCompetitors;
	int randomCarType = rand() % 2;
	int randomCarID = rand() % 2;
	for (int i = 0; i < numberRealCompetitors; i++) {
		competitors[i]->setId(i);
		if (randomCarType == 0) {
			((RealCompetitor*)competitors[i])->addCar(carShop.getCar(randomCarID));
		}
		else if (randomCarType == 1) {
			((RealCompetitor*)competitors[i])->addCar(carShop.getCar(VIRTUAL + randomCarID));
		}
	}
	for (int i = numberRealCompetitors; i < allPlayers; i++) {
		competitors[i]->setId(i - numberRealCompetitors);
		if (randomCarType == 0) {
			((VirtualCompetitor*)competitors[i])->setCar(carShop.getCar(randomCarID));
		}
		else if (randomCarType == 1) {
			((VirtualCompetitor*)competitors[i])->setCar(carShop.getCar(VIRTUAL + randomCarID));
		}
	}
}
void Nfs::chooseAction() {
	char actionCode[MAX_SIZE];
	for (int i = 0; i < numberRealCompetitors; i++) {
		if (isFreeRealEnemy[i] == true) {
			cout << endl;
			cout << "Competitor " << i << " please choose what you want to do this round!" << endl;
			cout << ">> If you want to compete, type 'C'" << endl;
			cout << ">> If you want to buy a new car from the shop, type 'B': ";
			do {
				cin >> actionCode;
			} while ((actionCode[0] != 'C' && actionCode[0] != 'B') || strlen(actionCode) != 1);
			if (actionCode[0] == 'B') buyCar(competitors[i]);
			cout << endl;
			chooseEnemy(i);
		}
		else {
			cout << endl;
			cout << ">> Competitor "<<i<<" you have been already chosen to be an opponent!" << endl;
			cout << ">> If you want to buy a new car from the shop, type 'B'" << endl;
			cout << ">> If you do NOT want to go to the shop, type 'N' : ";
			do {
				cin >> actionCode;
			} while ((actionCode[0] != 'N' && actionCode[0] != 'B') || strlen(actionCode) != 1);
			if (actionCode[0] == 'B') buyCar(competitors[i]);
		}
	}
}
void Nfs::buyCar(Competitor* competitor) {
	cout << endl;
	cout << setw(60) << "Welcome to the shop!" << endl;
	cout << setw(60) << "Here is the list of all cars in the shop!" << endl;
	carShop.showCars();
	cout << ">> Choose what type of car do you want to buy" << endl;
	cout << ">> Type 'N' for Normal Car or 'T' - for Nitro Car: ";
	char typeCar[MAX_SIZE];
	do {
		cin >> typeCar;
	} while ((typeCar[0] != 'N' && typeCar[0] != 'T') || strlen(typeCar) != 1);
	int id;
	if (typeCar[0] == 'N') {
		cout << endl;
		cout << ">> Type the ID of the car you have chosen: ";
		cin >> id;
		double differ = ((RealCompetitor*)competitor)->getCash() - carShop.getCar(id)->getPrice();
		if (differ < 0) {
			cout << "WARNING: Not enough cash!" << endl << endl;
			char symbol;
			cout << "Enter a symbol to continue with choosing an oponent:";
			cin >> symbol;
			return;
		}
		((RealCompetitor*)competitor)->addCar(carShop.getCar(id));
		((RealCompetitor*)competitor)->setCash(differ);
	}
	if (typeCar[0] == 'T') {
		cout << endl;
		cout << ">> Type the ID of the car you have chosen: ";
		cin >> id;
		double differ = ((RealCompetitor*)competitor)->getCash() - carShop.getCar(VIRTUAL + id)->getPrice();
		if (differ < 0) {
			cout << "WARNING: Not enough cash!" << endl << endl;
			char symbol;
			cout << "Enter a symbol to continue with choosing an oponent:";
			cin >> symbol;
			return;
		}
		((RealCompetitor*)competitor)->addCar(carShop.getCar(VIRTUAL + id));
		((RealCompetitor*)competitor)->setCash(differ);
	}
}
void Nfs::showFreeEnemies() {
	cout << endl;
	int allPlayers = numberRealCompetitors + numberVirtualCompetitors;
	numberFreeRealCompetitors--;
	if (numberFreeRealCompetitors > 0) {
		cout << setw(50) << "List of the Real Competitors" << endl;
		for (int i = 0; i < numberRealCompetitors; i++) {
			if (isFreeRealEnemy[i] == true) competitors[i]->print();
		}
		cout << endl;
	}
	if (numberFreeVirtualCompetitors > 0) {
		cout << setw(50) << "List of the Virtual Competitors" << endl;
		for (int i = numberRealCompetitors; i < allPlayers; i++) {
			if (isFreeVirtualEnemy[i - numberRealCompetitors] == true) {
				competitors[i]->print();
				cout << endl;
			}
		}
		cout << endl;
	}
	
}
void Nfs::chooseEnemy(int number) {
	cout << endl;
	isFreeRealEnemy[number] = false;
	showFreeEnemies();
	char symbol[MAX_SIZE];
	int id;
	do {
		cout << "<< Type 'R' for the Real Competitors and type 'V' for Virtual Competitors: ";
		cin >> symbol;
	} while ((symbol[0] != 'R' && symbol[0] != 'V') || strlen(symbol) != 1);
	if (symbol[0] == 'R') {
		do {
			cout << "<< Enter the ID of the player: ";
			cin >> id;
		} while (isFreeRealEnemy[id] == false || id >= numberRealCompetitors || id < 0);
		isFreeRealEnemy[id] = false;
		numberFreeRealCompetitors--;
		enemies.push(id);
	}
	else if (symbol[0] == 'V') {
		do {
			cout << "<< Enter the ID of the player: ";
			cin >> id;
		} while (isFreeVirtualEnemy[id] == false || id >= numberVirtualCompetitors || id < 0);
		isFreeVirtualEnemy[id] = false;
		numberFreeVirtualCompetitors--;
		enemies.push(numberRealCompetitors + id);
	}
	enemies.push(number);
}
void Nfs::chooseRandomEnemy() {
	srand(time(NULL));
	Array<int> tempFreeEnemies;
	for (int i = 0; i < numberVirtualCompetitors; i++) {
		if (isFreeVirtualEnemy[i]) tempFreeEnemies.push(i + numberRealCompetitors);
	}
	int size = tempFreeEnemies.getSize();
	Array<bool> usedCompetitors(size);
	for (int i = 0; i < size; i++) {
		usedCompetitors[i] = false;
	}
	int tempID, tempCounter = 0;
	while (tempCounter < size) {
		tempID = rand() % size;
		if (usedCompetitors[tempID] == false) {
			enemies.push(tempFreeEnemies[tempID]);
			usedCompetitors[tempID] = true;
			isFreeVirtualEnemy[tempID] = false;
			tempCounter++;
		}
	}
}
void Nfs::compete() {
	double coefficientOne, coefficientTwo;
	int allPlayers = numberRealCompetitors + numberVirtualCompetitors;
	int bonus = rand() % 21;
	cout << endl << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	cout << setw(50) << "RESULTS" << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	for (int i = 0; i < allPlayers; i += 2) {
		coefficientOne = 0;
		coefficientTwo = 0;
		if (enemies[i] < numberRealCompetitors) {
				coefficientOne = (competitors[enemies[i]]->getSkills() + competitors[enemies[i]]->getBestCar()->getPower())*(100 + bonus);
			if (enemies[i + 1] < numberRealCompetitors) {
					coefficientTwo = (competitors[enemies[i + 1]]->getSkills() + competitors[enemies[i + 1]]->getBestCar()->getPower())*(100 + bonus);
				if (coefficientOne >= coefficientTwo) {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the real player with ID " << enemies[i] << endl;
					competitors[enemies[i]]->setSkills(competitors[enemies[i]]->getSkills() + WINNER_SKILLS);
					((RealCompetitor*)competitors[enemies[i]])->setCash(((RealCompetitor*)competitors[enemies[i]])->getCash() + WINNER_CASH);
				}
				else {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the real player with ID " << enemies[i + 1] << endl;
					competitors[enemies[i + 1]]->setSkills(competitors[enemies[i + 1]]->getSkills() + WINNER_SKILLS);
					((RealCompetitor*)competitors[enemies[i + 1]])->setCash(((RealCompetitor*)competitors[enemies[i + 1]])->getCash() + WINNER_CASH);
				}
			}
			if (enemies[i + 1] >= numberRealCompetitors) {
					coefficientTwo = (competitors[enemies[i + 1]]->getSkills() + competitors[enemies[i + 1]]->getBestCar()->getPower())*(100 + bonus);
				if (coefficientOne >= coefficientTwo) {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the real player with ID " << enemies[i] << endl;
					competitors[enemies[i]]->setSkills(competitors[enemies[i]]->getSkills() + WINNER_SKILLS);
					((RealCompetitor*)competitors[enemies[i]])->setCash(((RealCompetitor*)competitors[enemies[i]])->getCash() + WINNER_CASH);
				}
				else {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the virtual player with ID " << enemies[i + 1] - numberRealCompetitors << endl;
					competitors[enemies[i + 1]]->setSkills(competitors[enemies[i + 1]]->getSkills() + WINNER_SKILLS);
				}
			}
		}
		if (enemies[i] >= numberRealCompetitors) {
			coefficientOne = (competitors[enemies[i]]->getSkills() + competitors[enemies[i]]->getBestCar()->getPower())*(100 + bonus);
			if (enemies[i + 1] < numberRealCompetitors) {
				coefficientTwo = (competitors[enemies[i + 1]]->getSkills() + competitors[enemies[i + 1]]->getBestCar()->getPower())*(100 + bonus);
				if (coefficientOne >= coefficientTwo) {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the virtual player with ID " << enemies[i] - numberRealCompetitors << endl;
					competitors[enemies[i]]->setSkills(competitors[enemies[i]]->getSkills() + WINNER_SKILLS);
				}
				else {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the real player with ID " << enemies[i + 1] << endl;
					competitors[enemies[i + 1]]->setSkills(competitors[enemies[i + 1]]->getSkills() + WINNER_SKILLS);
					((RealCompetitor*)competitors[enemies[i + 1]])->setCash(((RealCompetitor*)competitors[enemies[i + 1]])->getCash() + WINNER_CASH);
				}
			}
			if (enemies[i + 1] >= numberRealCompetitors) {
				coefficientTwo = (competitors[enemies[i + 1]]->getSkills() + competitors[enemies[i + 1]]->getBestCar()->getPower())*(100 + bonus);
				if (coefficientOne >= coefficientTwo) {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the virtual player with ID " << enemies[i] - numberRealCompetitors << endl;
					competitors[enemies[i]]->setSkills(competitors[enemies[i]]->getSkills() + WINNER_SKILLS);
				}
				else {
					cout << "<< The winner from the " << i / 2 + 1 << " duel is the virtual player with ID " << enemies[i + 1] - numberRealCompetitors << endl;
					competitors[enemies[i + 1]]->setSkills(competitors[enemies[i + 1]]->getSkills() + WINNER_SKILLS);
				}
			}
		}
	}
}
void Nfs::ranking() {
	int allPlayers = numberRealCompetitors + numberVirtualCompetitors;
	cout << endl << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	cout << setw(60) << "Real Competitors Ranking" << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	Array<Competitor*> tempCompetitors = competitors;
	Competitor* tempCompetitor;
	for (int i = 0; i < numberRealCompetitors - 1; i++) {
		for (int j = i + 1; j < numberRealCompetitors; j++) {
			if (tempCompetitors[i]->getSkills() < tempCompetitors[j]->getSkills()) {
				tempCompetitor = tempCompetitors[i];
				tempCompetitors[i] = tempCompetitors[j];
				tempCompetitors[j] = tempCompetitor;
			}
		}
	}
	for (int i = 0; i < numberRealCompetitors; i++) {
		tempCompetitors[i]->print();
	}
	cout << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	cout << setw(60) << "Virtual Competitors Ranking" << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	for (int i = numberRealCompetitors; i < allPlayers - 1; i++) {
		for (int j = i + 1; j < allPlayers; j++) {
			if (tempCompetitors[i]->getSkills() < tempCompetitors[j]->getSkills()) {
				tempCompetitor = tempCompetitors[i];
				tempCompetitors[i] = tempCompetitors[j];
				tempCompetitors[j] = tempCompetitor;
			}
		}
	}
	for (int i = numberRealCompetitors; i < allPlayers; i++) {
		tempCompetitors[i]->print();
		cout << endl;
	}
	cout << endl;
	cout << endl;
}
