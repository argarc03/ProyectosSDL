#pragma once
#include "checkML.h"
#include <math.h>
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Game;

class Counter : public ArkanoidObject {
private:
	uint totalDigits = 0;
	uint initialNumber = 0;
	uint number = 0;

	int saveTime = 0;

	double startTime = 0;

	int* digits;
public:
	Counter(Vector2D pos, uint w, uint h, uint initialNumber, uint totalDigits, Texture* t) : ArkanoidObject(w, h, pos, t), initialNumber(initialNumber), totalDigits(totalDigits) {
		digits = new int[totalDigits];

		startTime = 0;

		for (uint i = 0; i < totalDigits; i++)
			digits[i] = (initialNumber%int(pow(10, totalDigits - i))) / pow(10, totalDigits - 1 - i);
	};
	~Counter() {
		delete digits;
	};

	void render() const;
	void update();
	int getNumber()const { return number; };

	void setStartTime() { startTime = SDL_GetTicks(); };

	// Loads from file the Counter's number
	virtual void loadFromFile(ifstream& in);
	// Saves to file the Counter's number
	virtual void saveToFile(ofstream& out);

	void setSaveTime();
};