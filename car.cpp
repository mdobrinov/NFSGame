#include "car.h"
#include <iostream>
#include <iomanip>
using namespace std;

Car::Car(int number, double power, double price) : serialNumber(number), power(power), price(price) {
}
Car::~Car() {
}
double Car::getPower() const {
	return power;
}
double Car::getPrice() const {
	return price;
}
void Car::addPoints(int)
{
}
void Car::print() const {
	cout << setw(10) << "<> carID: " << serialNumber << "  Power: " << power << "  Price: $" << price;
}