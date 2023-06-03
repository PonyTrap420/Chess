#pragma once
#include "piece.h"

class King : public Piece
{
public:

	inline King(unsigned int x, unsigned int y, int team) : Piece(x,y,KING, team) {};

	std::vector<Move> ShowMoves(GameModel* game);
private:
};