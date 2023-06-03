#pragma once
#include "pch.h"
#include "MCTS/algo.h"
#include "Pieces/piece.h"
#include "model.h"

#define BLACK 0
#define WHITE 1

enum DrawState {
	Board,
	PieceMenu,
	EndGame
};

class Game : public sf::Drawable
{
public:
	DrawState m_state;

	Game(sf::RenderWindow& window, unsigned int rows, unsigned int cols);

	void MousePressed();
	void CellPressed(int row, int col);

	GameModel* m_model;
	MCTS m_mcts;
	sf::Music m_player;
	bool winner;

private:
	virtual void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void MovePiece(Move& m);
	void ResetBoard();
	void SwapPieces(Piece* p, Piece* p2);

	sf::RenderWindow* m_target = nullptr;
	unsigned int m_rows;
	unsigned int m_cols;

	sf::Texture m_tileset;

	Piece* m_selected = nullptr;
};