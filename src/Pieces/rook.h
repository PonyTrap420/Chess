#pragma once
#include "piece.h"
#include "../game.h"

class Rook : public Piece
{
public:

	inline Rook(unsigned int x, unsigned int y, int team) : Piece(x,y,ROOK, team) {};

	std::vector<Move> ShowMoves(GameModel* game);
private:
};