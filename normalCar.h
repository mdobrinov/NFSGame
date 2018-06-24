#ifndef NORMAL_CAR_H
#define NORMAL_CAR_H
#include "car.h"
#include <iostream>
using namespace std;

class NormalCar : public Car {
public:
	NormalCar(int = 0, double = 0, double = 0);
};

#endif

