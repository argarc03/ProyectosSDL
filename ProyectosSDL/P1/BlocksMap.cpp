#include "BlocksMap.h"
#include "Block.h"
#include <fstream>
#include <algorithm>

void BlocksMap::render() const {
	for (uint i = 0; i < nRows; i++) {
		for (uint j = 0; j < nCols; j++) {
			if (map[i][j] != nullptr)
				map[i][j]->render();
		}
	}
}

// Load the map from file filename.
void BlocksMap::load(string filename, Texture* t) {
	ifstream input;
	input.open(filename);
	if (!input.is_open())
		throw "Error loading the file " + filename;

	input >> nRows;
	input >> nCols;

	cellW = w / nCols;
	cellH = h / nRows;
	//Create map (bidimensional array)
	map = new Block**[nRows];
	for (uint i = 0; i < nRows; i++)
		map[i] = new Block*[nCols];
	//Create each block in map. If color is 0, the block is not created. 
	int color;
	for (uint i = 0; i < nRows; i++) {
		for (uint j = 0; j < nCols; j++) {
			input >> color;
			if (color != 0) {
				map[i][j] = new Block(cellW, cellH, Vector2D(pos.getX() + j * cellW, pos.getY() + i * cellH),
					color - 1, i, j, t);
				numBlocks++;
			}
			else
				map[i][j] = nullptr;
		}
	}

	input.close();
}

Block* BlocksMap::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector) {
	Vector2D p0 = { double(ballRect.x), double(ballRect.y) }; // top-left
	Vector2D p1 = { double(ballRect.x) + double(ballRect.w),  double(ballRect.y) }; // top-right
	Vector2D p2 = { double(ballRect.x),  double(ballRect.y) + double(ballRect.h) }; // bottom-left
	Vector2D p3 = { double(ballRect.x) + double(ballRect.w),  double(ballRect.y) + double(ballRect.h) }; // bottom-right
	Block* b = nullptr;
	if (ballVel.getX() < 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p0))) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2))) collVector = { 1,0 };
	}
	else if (ballVel.getX() >= 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p1))) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel.getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3))) collVector = { -1,0 };
	}
	else if (ballVel.getX() > 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p3))) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1))) collVector = { -1,0 };
	}
	else if (ballVel.getX() < 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p2))) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0))) collVector = { 1,0 };
	}
	return b;
}

//Return the block at the point p.
Block* BlocksMap::blockAt(const Vector2D& p) {
	Block* b = nullptr;
	if (p.getX() > pos.getX() && p.getX() < pos.getX() + w && p.getY() > pos.getY() && p.getY() < pos.getY() + h) {
		uint row = (p.getY() - pos.getY()) / cellH;
		uint col =  std::min(int((p.getX() - pos.getX()) / cellW),int(nCols-1));
		b = map[row][col];
	}

	return b;
}

//Destroy the block that is hit by the ball
void BlocksMap::ballHitsBlock(Block* block) {
	uint row = block->getRow();
	uint col = block->getCol();
	delete map[row][col];
	map[row][col] = nullptr;

	numBlocks--;
}

//Save the map in the output stream out.
void BlocksMap::save(ofstream& out) {
	out << nRows << ' ';
	out << nCols << endl;

	for (uint i = 0; i < nRows; i++) {
		for (uint j = 0; j < nCols; j++) {
			if (map[i][j] == nullptr)
				out << 0;
			else
				out << map[i][j]->getColor() + 1;
			if (j < nCols - 1)
				out << ' ';
			else
				out << endl;
		}
	}
}
