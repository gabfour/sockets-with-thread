#include "Carte.h"

Carte::Carte(int val, int point)
{
	this->point = point;
	this->val = val;
}

void Carte::setPoint(int newPoint)
{
	point = newPoint;
}

void Carte::setVal(int newVal)
{
	val = newVal;
}

int Carte::getPointCarte()
{
	return point;
}

int Carte::getValCarte() {
	return val;
}
