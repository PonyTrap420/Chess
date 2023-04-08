#pragma once
#include "piece.h"
#include "../game.h"

class Rook : public Piece
{
public:

	inline Rook(unsigned int x, unsigned int y, int team) : Piece(x,y,ROOK, team) {};

	std::vector<sf::Vector2u> ShowMoves(Game* game);
private:
};