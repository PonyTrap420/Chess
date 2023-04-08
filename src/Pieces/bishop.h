#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
	
	inline Bishop(unsigned int x, unsigned int y, int team) : Piece(x,y,BISHOP, team) {};

	std::vector<sf::Vector2u> ShowMoves(Game* game);
private:
};