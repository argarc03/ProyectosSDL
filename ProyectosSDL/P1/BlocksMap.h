#pragma once

#include "checkML.h"
#include "Block.h"
#include <string>
#include "ArkanoidObject.h"

typedef unsigned int uint;

class BlocksMap : public ArkanoidObject {
private:
	uint nRows = 0;
	uint nCols = 0;

	Block*** map;

	uint numBlocks = 0;

	uint cellW = 0; uint cellH = 0;

public:
	BlocksMap(Vector2D pos, uint w, uint h) : ArkanoidObject(w, h, pos, nullptr) {};

	virtual ~BlocksMap() {
		for (uint i = 0; i < nRows; i++) {
			for (uint j = 0; j < nCols; j++)
				delete map[i][j];
			delete[] map[i];
		}
		delete map;
		map = nullptr;
	};

	void load(string filename, Texture* t);
	virtual void render() const;

	uint getNumBlocks() const { return numBlocks; };
	uint getnRows() const { return nRows; };

	Block* collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
	Block* blockAt(const Vector2D& p);
	void ballHitsBlock(Block* block);

	void save(ofstream& out);
};

