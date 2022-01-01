#pragma once

class Carte {

private :
	int val;
	int point;
	void setPoint(int newPoint);
	void setVal(int newVal);

	friend class Deck;
public :

	int getPointCarte();
	int getValCarte();
};