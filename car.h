#ifndef CAR_H
#define CAR_H

class Car {
protected:
	int serialNumber;
	double power;
	double price;
public:
	Car(int = 0, double = 0, double = 0);
	virtual ~Car();
	double getPower() const;
	double getPrice() const;
	virtual void addPoints(int);
	virtual void print() const;
};

#endif
