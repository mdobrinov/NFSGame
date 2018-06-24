#include "shop.h"
#include "nitroCar.h"
#include "normalCar.h"
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

Shop::Shop() {
	cars[0] = new NormalCar(0, 50, 1000);
	cars[1] = new NormalCar(1, 150, 2000);
	cars[2] = new NormalCar(2, 200, 3000);
	cars[3] = new NormalCar(3, 250, 4000);
	cars[4] = new NormalCar(4, 300, 5000);
	cars[5] = new NormalCar(5, 350, 6000);
	cars[6] = new NormalCar(6, 400, 7000);
	cars[7] = new NormalCar(7, 450, 7500);
	cars[8] = new NormalCar(8, 500, 8000);
	cars[9] = new NormalCar(9, 800, 9000);
	cars[10] = new NitroCar(0, 50, 1000);
	cars[11] = new NitroCar(1, 150, 2000);
	cars[12] = new NitroCar(2, 200, 3000);
	cars[13] = new NitroCar(3, 250, 4000);
	cars[14] = new NitroCar(4, 300, 5000);
	cars[15] = new NitroCar(5, 350, 6000);
	cars[16] = new NitroCar(6, 400, 7000);
	cars[17] = new NitroCar(7, 450, 7500);
	cars[18] = new NitroCar(8, 500, 8000);
	cars[19] = new NitroCar(9, 800, 9000);
}
Shop::~Shop() {
	for (int i = 0; i < ARRAY_SIZE; i++) delete cars[i];
}
Shop::Shop(const Shop& other) {
	for (int i = 0; i < ARRAY_SIZE / 2; i++) {
		cars[i] = new NormalCar(*(NormalCar*)(other.cars[i]));
		assert(cars[i] != NULL);
	}
	for (int i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++) {
		cars[i] = new NitroCar(*(NitroCar*)(other.cars[i]));
		assert(cars[i] != NULL);
	}
}
Shop& Shop::operator=(const Shop& other) {
	if (this != &other) {
		for (int i = 0; i < ARRAY_SIZE; i++) delete cars[i];
		for (int i = 0; i < ARRAY_SIZE / 2; i++) {
			cars[i] = new NormalCar(*(NormalCar*)(other.cars[i]));
			assert(cars[i] != NULL);
		}
		for (int i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++) {
			cars[i] = new NitroCar(*(NitroCar*)(other.cars[i]));
			assert(cars[i] != NULL);
		}
	}
	return *this;
}
void Shop::showCars() const {
	cout << endl;
	cout << setw(40) << "Here is the list of all Normal Cars:" << endl << endl;
	for (int i = 0; i < ARRAY_SIZE /2; i++) {
		cars[i]->print();
		cout << endl;
	}
	cout << endl;
	cout << setw(40) << "Here is the list of all Nitro Cars:" << endl << endl;
	for (int i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++) {
		cars[i]->print();
	}
	cout << endl;
}
Car* Shop::getCar(int number) {
	return cars[number];
}