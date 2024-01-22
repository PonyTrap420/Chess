#include "model.h"
#include <algorithm>


GameModel::GameModel()
{
	for (unsigned int i = 0; i < BOARD_WIDTH; i++)
	{
		m_cells[i][1] = new Pawn(i, 1, BLACK);
		m_cells[i][6] = new Pawn(i, 6, WHITE);
		for (unsigned int j = 2; j < BOARD_HEIGHT - 2; j++)
		{
			m_cells[i][j] = new Empty(i, j);
		}
	}

	m_cells[0][0] = new Rook(0, 0, BLACK);
	m_cells[1][0] = new Knight(1, 0, BLACK);
	m_cells[2][0] = new Bishop(2, 0, BLACK);
	m_cells[3][0] = new Queen(3, 0, BLACK);
	m_cells[4][0] = new King(4, 0, BLACK);
	m_cells[5][0] = new Bishop(5, 0, BLACK);
	m_cells[6][0] = new Knight(6, 0, BLACK);
	m_cells[7][0] = new Rook(7, 0, BLACK);

	m_cells[0][7] = new Rook(0, 7, WHITE);
	m_cells[1][7] = new Knight(1, 7, WHITE);
	m_cells[2][7] = new Bishop(2, 7, WHITE);
	m_cells[3][7] = new Queen(3, 7, WHITE);
	m_cells[4][7] = new King(4, 7, WHITE);
	m_cells[5][7] = new Bishop(5, 7, WHITE);
	m_cells[6][7] = new Knight(6, 7, WHITE);
	m_cells[7][7] = new Rook(7, 7, WHITE);

	for (unsigned int i = 0; i < BOARD_WIDTH; i++)
	{
		for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
		{
			unsigned int team = m_cells[i][j]->GetTeam();
			if (team == WHITE)
				white.push_back(m_cells[i][j]);
			else if (team == BLACK)
				black.push_back(m_cells[i][j]);
		}
	}

	ToString();
}

std::vector<Move> GameModel::GetAvailableMoves(unsigned int team) {
	std::vector<Piece*>* list;
	if (team == BLACK)
		list = &black;
	else
		list = &white;

	std::vector<Move> moves;

	for (Piece* piece : *list)
	{
		std::vector<Move> newmoves = piece->ShowMoves(this);
		moves.insert(moves.end(), newmoves.begin(), newmoves.end());
	}
	return moves;
}

bool GameModel::ExecuteMove(Move& move)
{
	if (m_cells[move.x][move.y]->GetType() != NONE) {
		unsigned int team = m_cells[move.x][move.y]->GetTeam();
		std::vector<Piece*>* list;
		if (team == BLACK)
			list = &black;
		else
			list = &white;

		list->erase(std::remove(list->begin(), list->end(), m_cells[move.x][move.y]), list->end());
	}

	move.captured = m_cells[move.x][move.y];

	int prev_row = move.piece->x;
	int prev_col = move.piece->y;

	move.prevx = prev_row;
	move.prevy = prev_col;

	m_cells[move.x][move.y] = move.piece;
	move.piece->x = move.x;
	move.piece->y = move.y;

	m_cells[prev_row][prev_col] = new Empty(prev_row, prev_col);

	if (m_cells[move.x][move.y]->GetType() == PAWN && (m_cells[move.x][move.y]->GetTeam() == 0 && move.y == 7 || m_cells[move.x][move.y]->GetTeam() == 1 && move.y == 0))
	{
		//piece menu
	}
	turn = !turn;
	return false;
}

void GameModel::UnmakeMove(Move& move)
{
	if (move.captured && move.captured->GetType() != NONE) {
		unsigned int team = move.captured->GetTeam();
		std::vector<Piece*>* list;
		if (team == BLACK)
			list = &black;
		else
			list = &white;

		list->push_back(move.captured);
	}

	m_cells[move.prevx][move.prevy] = move.piece;
	move.piece->x = move.prevx;
	move.piece->y = move.prevy;

	m_cells[move.x][move.y] = move.captured;

	turn = !turn;
}

int GameModel::Search(int depth, int alpha, int beta)
{
	if (depth == 0)
	{
		return Evaluate();
	}

	std::vector<Move> moves = GetAvailableMoves(turn);

	for (Move& move : moves)
	{
		ExecuteMove(move);
		int eval = -Search(depth - 1, -beta, -alpha);
		UnmakeMove(move);
		if (eval >= beta)
		{
			return beta;
		}
		if (eval > alpha)
		{
			alpha = eval;
			m_nextMove = move;
		}
	}
	return alpha;
}

int GameModel::Evaluate()
{
	int blackEval = CountScore(BLACK);
	int whiteEval = CountScore(WHITE);

	int evaluation = whiteEval - blackEval;

	int team = (turn) ? 1 : -1;
	return evaluation * team;
}

int GameModel::CountScore(int team) {
	int sum = 0;

	std::vector<Piece*>* list;
	if (team == BLACK)
		list = &black;
	else
		list = &white;

	std::vector<Move> moves;

	for (Piece* piece : *list)
	{
		switch (piece->GetType())
		{
			case ROOK:
				sum += 500;
				break;
			case BISHOP:
				sum += 300;
				break;
			case QUEEN:
				sum += 900;
				break;
			case PAWN:
				sum += 100;
				break;
			case KNIGHT:
				sum += 300;
				break;
			case KING:
				sum += 100000;
		}
	}
	return sum;
}

void GameModel::ToString() {
	std::cout << "----------------------\n";
	for (unsigned int i = 0; i < BOARD_WIDTH; i++)
	{
		for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
		{
			
			if (m_cells[j][i]->GetType() == KING)
				std::cout << "K";
			else if (m_cells[j][i]->GetType() != NONE)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "----------------------";
}