#include "Pieces/piece.h"
#include "Pieces/pawn.h"
#include "Pieces/bishop.h"
#include "Pieces/king.h"
#include "Pieces/queen.h"
#include "Pieces/rook.h"
#include "Pieces/knight.h"

#define Add(x,y) vec.push_back({x, y, this})

bool CheckBounds(int x, int y)
{
	if (y < 0 || y >= 8 || x < 0 || x >= 8)
		return true;
	return false;
}
bool IsEnemy(GameModel* game, int x, int y, int m_team)
{
	if (CheckBounds(x, y))
		return false;
	int cellTeam = game->m_cells[x][y]->GetTeam();
	if (cellTeam != -1 && cellTeam != m_team)
		return true;
	return false;
}
std::vector<Move> MoveValidator(std::vector<Move>* moves, GameModel* game)
{
	std::vector<Move> valid_moves;
	for (Move pos : *moves)
	{
		if (pos.y < 0 || pos.y >= 8 || pos.x < 0 || pos.x >= 8)
			continue;

		if (game->m_cells[pos.x][pos.y]->GetTeam() == pos.piece->GetTeam())
			continue;

		valid_moves.push_back(pos);
	}
	return valid_moves;
}

std::vector<Move> Rook::ShowMoves(GameModel* game)
{
	std::vector<Move> vec;

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y + i))
			break;

		vec.push_back({ x, y + i, this });

		if (game->m_cells[x][y + i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y - i))
			break;

		vec.push_back({x, y - i , this});

		if (game->m_cells[x][y - i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y))
			break;

		vec.push_back({x + i, y, this});

		if (game->m_cells[x + i][y]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y))
			break;


		vec.push_back({x - i, y, this});

		if (game->m_cells[x - i][y]->GetTeam() != -1)
			break;
	}
	return MoveValidator(&vec, game);
}

std::vector<Move> Pawn::ShowMoves(GameModel* game)
{
	std::vector<Move> vec;

	unsigned int i = 1;
	if (m_team == 1)
		i *= -1;

	bool canEat = false;
	if (IsEnemy(game, x + i, y + i, m_team)) {
		Add(x + i, y + i);
		canEat = true;
	}

	if (IsEnemy(game, x - i, y + i, m_team))
	{
		Add(x - i, y + i);
		canEat = true;
	}

	if (!canEat && !CheckBounds(x, y + i) && game->m_cells[x][y + i]->GetTeam() == -1) {
		vec.push_back({x, y + i, this});
		if(m_firstMove && game->m_cells[x][y + i * 2]->GetTeam() == -1)
			vec.push_back({x, y + i * 2, this});
	}

	return MoveValidator(&vec, game);
}

std::vector<Move> Queen::ShowMoves(GameModel* game)
{
	std::vector<Move> vec;

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y + i))
			break;

		vec.push_back({x, y + i, this});

		if (game->m_cells[x][y + i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y - i))
			break;

		vec.push_back({x, y - i, this});

		if (game->m_cells[x][y - i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y))
			break;

		vec.push_back({x + i, y, this});

		if (game->m_cells[x + i][y]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y))
			break;


		vec.push_back({x - i, y, this});

		if (game->m_cells[x - i][y]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y + i))
			break;


		vec.push_back({x + i, y + i, this});

		if (game->m_cells[x + i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y + i))
			break;


		vec.push_back({x - i, y + i, this});

		if (game->m_cells[x - i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y - i))
			break;


		vec.push_back({x + i, y - i, this});

		if (game->m_cells[x + i][y - i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y - i))
			break;


		vec.push_back({x - i, y - i, this});

		if (game->m_cells[x - i][y - i]->GetTeam() != -1)
			break;
	}


	return MoveValidator(&vec, game);
}

std::vector<Move> King::ShowMoves(GameModel* game)
{
	std::vector<Move> vec;

	vec.push_back({x + 1, y + 1, this});
	vec.push_back({x, y + 1, this});
	vec.push_back({x - 1, y + 1, this});

	vec.push_back({x + 1, y - 1, this});
	vec.push_back({x, y - 1, this});
	vec.push_back({x - 1, y - 1, this});

	vec.push_back({x + 1, y, this});
	vec.push_back({x - 1, y, this});

	/*std::vector<Move> rookMoves;
	std::vector<Move> kingMoves;
	std::vector<Move> pawnMoves;
	std::vector<Move> bishopMoves;
	std::vector<Move> queenMoves;

	for (Move pos : vec)
	{
		std::vector<Move> enemy;

	}*/

	return MoveValidator(&vec, game);
}

std::vector<Move> Bishop::ShowMoves(GameModel* game)
{
	std::vector<Move> vec;

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y + i))
			break;


		vec.push_back({x + i, y + i, this});

		if (game->m_cells[x + i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y + i))
			break;


		vec.push_back({x - i, y + i, this});

		if (game->m_cells[x - i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y - i))
			break;


		vec.push_back({x + i, y - i, this});

		if (game->m_cells[x + i][y - i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y - i))
			break;


		vec.push_back({x - i, y - i, this});

		if (game->m_cells[x - i][y - i]->GetTeam() != -1)
			break;
	}
	return MoveValidator(&vec, game);
}

std::vector<Move> Knight::ShowMoves(GameModel* game)
{
	std::vector<Move> vec;

	vec.push_back({x + 1, y + 2, this});
	vec.push_back({x - 1, y + 2, this});

	vec.push_back({x + 2, y + 1, this});
	vec.push_back({x + 2, y - 1, this});
	
	vec.push_back({x - 2, y + 1, this});
	vec.push_back({x - 2, y - 1, this});

	vec.push_back({x + 1, y - 2, this});
	vec.push_back({x - 1, y - 2, this});

	return MoveValidator(&vec, game);
}