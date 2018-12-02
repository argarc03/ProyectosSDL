#include "Block.h"

void Block::render() const {
	SDL_Rect destRect = getRect();

	texture->renderFrame(destRect, color / (texture->getNumCols()), color%(texture->getNumCols()));
}
