#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Block :public ArkanoidObject {
private:
	uint color = 0;
	uint row = 0; uint col = 0; //fila y columna en mapa de bloques

	uint textRow = 0; uint textCol = 0; //fila y columna en la textura
public:
	Block() {}
	Block(uint w, uint h, Vector2D pos, uint color, uint row, uint col, Texture* t) :
		ArkanoidObject(w, h, pos, t), color(color), row(row), col(col) {}
	virtual ~Block() {}

	virtual void render() const;

	uint getColor() { return color; };

	uint getRow() { return row; };
	uint getCol() { return col; };
};

