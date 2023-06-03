#pragma once
#include "Pieces/pawn.h"
#include "Pieces/bishop.h"
#include "Pieces/king.h"
#include "Pieces/queen.h"
#include "Pieces/rook.h"
#include "Pieces/knight.h"


constexpr unsigned int BOARD_WIDTH = 8;
constexpr unsigned int BOARD_HEIGHT = 8;

constexpr int simulations = 1;
constexpr double exploration = 1.414;

#define BishopValue

class GameModel
{
public:

	Piece* m_cells[BOARD_WIDTH][BOARD_HEIGHT];

	std::vector<Piece*> white;
	std::vector<Piece*> black;

	std::stack<Move> m_moves;
	Move m_nextMove;

	bool turn = 1;

	GameModel();
	GameModel(GameModel* other)
	{
		white = other->white;
		black = other->black;
		memcpy(m_cells, other->m_cells, sizeof(other->m_cells));
	}

	std::vector<Move> GetAvailableMoves(unsigned int team);
	bool ExecuteMove(Move& move);
	void UnmakeMove(Move& move);

	void ToString();
	int Search(int depth, int alpha, int beta);
	int Evaluate();
	int CountScore(int team);
};
