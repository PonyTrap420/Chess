#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
	
	inline Bishop(unsigned int x, unsigned int y, int team) : Piece(x,y,BISHOP, team) {};

	std::vector<Move> ShowMoves(GameModel* game);
private:
};