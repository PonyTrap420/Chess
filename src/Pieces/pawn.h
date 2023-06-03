#pragma once
#include "piece.h"

class Pawn : public Piece
{
public:

	inline Pawn(unsigned int x, unsigned int y, int team) : Piece(x,y,PAWN, team) {};

	std::vector<Move> ShowMoves(GameModel* game);
	
	inline void MovePiece(unsigned int x, unsigned int y) override {
		Piece::MovePiece(x,y);
		if (m_firstMove)
			m_firstMove = false;
	}

private:
	bool m_firstMove = true;
};