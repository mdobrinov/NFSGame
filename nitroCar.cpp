#include "nitroCar.h"
#include <iostream>
using namespace std;

NitroCar::NitroCar(int number, double power, double price) :Car(number, power, price), points(0) {
}
void NitroCar::print() const {
	Car::print();
	cout << " Points: " << points << endl;
}
void NitroCar::addPoints(int number) {
	points = points + number;
}