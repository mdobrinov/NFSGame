#ifndef COMPETITOR_H
#define COMPETITOR_H
#include "car.h"

class Competitor {
private:
	int competitorId;
	int skills;
public:
	Competitor();
	virtual ~Competitor();
	virtual void print() const;
	void setId(int);
	void setSkills(int);
	int getCompetitorId() const;
	int getSkills() const;
	virtual Car* getBestCar() const = 0;
};

#endif
