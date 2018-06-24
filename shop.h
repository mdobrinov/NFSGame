#ifndef SHOP_H
#define SHOP_H
#include "car.h"
const int ARRAY_SIZE = 20;

class Shop {
private:
	Car* cars[ARRAY_SIZE];
public:
	Shop();
	~Shop();
	Shop(const Shop&);
	Shop& operator=(const Shop&);
	void showCars() const;
	Car* getCar(int);
};

#endif
