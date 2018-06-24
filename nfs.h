#ifndef NFS_H
#define NFS_H
#include "dynamicArray.h"
#include "competitor.h"
#include "shop.h"

class Nfs {
private:
	int numberRealCompetitors;
	int numberVirtualCompetitors;
	int numberFreeRealCompetitors;
	int numberFreeVirtualCompetitors;
	Array<Competitor*> competitors;
	Shop carShop;
	void generateCompetitors();
	Array<bool> isFreeRealEnemy;
	Array<bool> isFreeVirtualEnemy;
	Array<int> enemies;
	int competitionsCounter;
	void showFreeEnemies();
	void chooseAction();
	void buyCar(Competitor*);
	void chooseEnemy(int);
	void chooseRandomEnemy();
	void startRound();
	void nextRound();
	void compete();
	void ranking();
public:
	Nfs(int, int);
	~Nfs();
	void startGame();
};

#endif
