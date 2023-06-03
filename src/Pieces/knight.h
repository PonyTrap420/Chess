#pragma once
#include "piece.h"

class Knight : public Piece
{
public:

	inline Knight(unsigned int x, unsigned int y, int team) : Piece(x,y,KNIGHT, team) {};

	std::vector<Move> ShowMoves(GameModel* game);
private:};