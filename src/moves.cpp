#include "Pieces/piece.h"
#include "Pieces/pawn.h"
#include "Pieces/bishop.h"
#include "Pieces/king.h"
#include "Pieces/queen.h"
#include "Pieces/rook.h"
#include "Pieces/knight.h"

#define Add(x,y) vec.push_back(sf::Vector2u(x, y))

bool CheckBounds(int x, int y)
{
	if (y < 0 || y >= 8 || x < 0 || x >= 8)
		return true;
	return false;
}
bool IsEnemy(Game* game, int x, int y, int m_team)
{
	if (CheckBounds(x, y))
		return false;
	int cellTeam = game->m_cells[x][y]->GetTeam();
	if (cellTeam != -1 && cellTeam != m_team)
		return true;
	return false;
}

std::vector<sf::Vector2u> Rook::ShowMoves(Game* game)
{
	std::vector<sf::Vector2u> vec;

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y + i))
			break;

		vec.push_back(sf::Vector2u(x, y + i));

		if (game->m_cells[x][y + i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y - i))
			break;

		vec.push_back(sf::Vector2u(x, y - i));

		if (game->m_cells[x][y - i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y))
			break;

		vec.push_back(sf::Vector2u(x + i, y));

		if (game->m_cells[x + i][y]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y))
			break;


		vec.push_back(sf::Vector2u(x - i, y));

		if (game->m_cells[x - i][y]->GetTeam() != -1)
			break;
	}
	return vec;
}

std::vector<sf::Vector2u> Pawn::ShowMoves(Game* game)
{
	std::vector<sf::Vector2u> vec;

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
		vec.push_back(sf::Vector2u(x, y + i));
		if(m_firstMove && game->m_cells[x][y + i * 2]->GetTeam() == -1)
			vec.push_back(sf::Vector2u(x, y + i * 2));
	}

	return vec;
}

std::vector<sf::Vector2u> Queen::ShowMoves(Game* game)
{
	std::vector<sf::Vector2u> vec;

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y + i))
			break;

		vec.push_back(sf::Vector2u(x, y + i));

		if (game->m_cells[x][y + i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x, y - i))
			break;

		vec.push_back(sf::Vector2u(x, y - i));

		if (game->m_cells[x][y - i]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y))
			break;

		vec.push_back(sf::Vector2u(x + i, y));

		if (game->m_cells[x + i][y]->GetTeam() != -1)
			break;
	}
	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y))
			break;


		vec.push_back(sf::Vector2u(x - i, y));

		if (game->m_cells[x - i][y]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y + i))
			break;


		vec.push_back(sf::Vector2u(x + i, y + i));

		if (game->m_cells[x + i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y + i))
			break;


		vec.push_back(sf::Vector2u(x - i, y + i));

		if (game->m_cells[x - i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y - i))
			break;


		vec.push_back(sf::Vector2u(x + i, y - i));

		if (game->m_cells[x + i][y - i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y - i))
			break;


		vec.push_back(sf::Vector2u(x - i, y - i));

		if (game->m_cells[x - i][y - i]->GetTeam() != -1)
			break;
	}


	return vec;
}

std::vector<sf::Vector2u> King::ShowMoves(Game* game)
{
	std::vector<sf::Vector2u> vec;

	vec.push_back(sf::Vector2u(x + 1, y + 1));
	vec.push_back(sf::Vector2u(x, y + 1));
	vec.push_back(sf::Vector2u(x - 1, y + 1));

	vec.push_back(sf::Vector2u(x + 1, y - 1));
	vec.push_back(sf::Vector2u(x, y - 1));
	vec.push_back(sf::Vector2u(x - 1, y - 1));

	vec.push_back(sf::Vector2u(x + 1, y));
	vec.push_back(sf::Vector2u(x - 1, y));

	std::vector<sf::Vector2u> rookMoves;
	std::vector<sf::Vector2u> kingMoves;
	std::vector<sf::Vector2u> pawnMoves;
	std::vector<sf::Vector2u> bishopMoves;
	std::vector<sf::Vector2u> queenMoves;

	for (sf::Vector2u pos : vec)
	{
		std::vector<sf::Vector2u> enemy;

	}

	return vec;
}

std::vector<sf::Vector2u> Bishop::ShowMoves(Game* game)
{
	std::vector<sf::Vector2u> vec;

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y + i))
			break;


		vec.push_back(sf::Vector2u(x + i, y + i));

		if (game->m_cells[x + i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y + i))
			break;


		vec.push_back(sf::Vector2u(x - i, y + i));

		if (game->m_cells[x - i][y + i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x + i, y - i))
			break;


		vec.push_back(sf::Vector2u(x + i, y - i));

		if (game->m_cells[x + i][y - i]->GetTeam() != -1)
			break;
	}

	for (unsigned int i = 1; i < 8; i++)
	{
		if (CheckBounds(x - i, y - i))
			break;


		vec.push_back(sf::Vector2u(x - i, y - i));

		if (game->m_cells[x - i][y - i]->GetTeam() != -1)
			break;
	}
	return vec;
}

std::vector<sf::Vector2u> Knight::ShowMoves(Game* game)
{
	std::vector<sf::Vector2u> vec;

	vec.push_back(sf::Vector2u(x + 1, y + 2));
	vec.push_back(sf::Vector2u(x - 1, y + 2));

	vec.push_back(sf::Vector2u(x + 2, y + 1));
	vec.push_back(sf::Vector2u(x + 2, y - 1));	
	
	vec.push_back(sf::Vector2u(x - 2, y + 1));
	vec.push_back(sf::Vector2u(x - 2, y - 1));

	vec.push_back(sf::Vector2u(x + 1, y - 2));
	vec.push_back(sf::Vector2u(x - 1, y - 2));

	return vec;
}