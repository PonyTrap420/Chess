#pragma once
#include "piece.h"

class Pawn : public Piece
{
public:

	inline Pawn(unsigned int x, unsigned int y, int team) : Piece(x,y,PAWN, team) {};

	std::vector<sf::Vector2u> ShowMoves(Game* game);
	
	inline void Move(unsigned int x, unsigned int y) override {
		Piece::Move(x,y);
		if (m_firstMove)
			m_firstMove = false;
	}

private:
	bool m_firstMove = true;
};