#pragma once

class Carte {

private :
	int penaltyPoint;
	int value;
public :
	Carte(int, int);
	int getPenaltyPoint();
	int getValue();
};