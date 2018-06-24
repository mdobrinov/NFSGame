#include <iostream>
#include <iomanip>
#include "functions.h"
#include "nfs.h"

using namespace std;

void startGame() {
	cout << setw(70) << "---------------------------------------------" << endl;
	cout << setw(60) << "Welcome to the NFS Game!" << endl;
	cout << setw(70) << "---------------------------------------------" << endl;
	int m, n;
	do {
		cout << ">> Enter how many players do you want to compete in the game: ";
		cin >> m;
	} while (m % 2 != 0 || m <= 0);
	do {
		cout << ">> Enter how many real players do you want to compete in this game: ";
		cin >> n;
	} while (n > m || n < 0);
	Nfs Game(n, m - n);
	Game.startGame();
}