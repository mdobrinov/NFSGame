#ifndef NITRO_CAR_H
#define NITRO_CAR_H
#include "car.h"
#include <iostream>

class NitroCar;

class NitroCar : public Car {
private:
	int points;
public:
	NitroCar(int = 0, double = 0, double = 0);
	void addPoints(int);
	void print() const;
};

#endif
