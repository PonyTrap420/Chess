#pragma once
#include "piece.h"

class Queen : public Piece
{
public:
	inline Queen(unsigned int x, unsigned int y, int team) : Piece(x,y,QUEEN, team){};

	std::vector<Move> ShowMoves(GameModel* game);
private:
};