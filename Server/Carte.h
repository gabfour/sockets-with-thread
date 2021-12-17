#pragma once

class Carte {

private :
	int val;
	int point;

	void setPoint(int newPoint);
	void setVal(int newVal);

public :
	Carte(int val, int point);
	int getPointCarte();
	int getValCarte();
};