#ifndef REAL_COMPETITOR_H
#define REAL_COMPETITOR_H
#include "competitor.h"
#include "dynamicArray.h"
#include "car.h"

class RealCompetitor : public Competitor {
private:
	Array<Car*> cars;
	double cash;
	Car* bestCar;
public:
	RealCompetitor();
	void addCar(Car*);
	void print() const;
	double getCash() const;
	void setCash(double);
	Car* getBestCar() const;
};

#endif
