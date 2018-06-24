#ifndef VIRTUAL_COMPETITOR_H
#define VIRTUAL_COMPETITOR_H
#include "competitor.h"

class VirtualCompetitor : public Competitor {
private:
	Car* car;
public:
	VirtualCompetitor();
	void setCar(Car*);
	Car* getBestCar() const;
};

#endif
