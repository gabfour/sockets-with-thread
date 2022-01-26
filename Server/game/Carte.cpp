#include "Carte.h"

Carte::Carte(int value, int penaltyPoint) : value(value), penaltyPoint(penaltyPoint) {

}
int Carte::getPenaltyPoint()
{
	return penaltyPoint;
}

int Carte::getValue() {
	return value;
}
