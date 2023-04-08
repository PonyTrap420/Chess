#pragma once
#include "piece.h"

class King : public Piece
{
public:

	inline King(unsigned int x, unsigned int y, int team) : Piece(x,y,KING, team) {};

	std::vector<sf::Vector2u> ShowMoves(Game* game);
private:
};