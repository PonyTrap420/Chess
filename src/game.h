#pragma once
#include "pch.h"
#include "Pieces/piece.h"
#include "Pieces/pawn.h"
#include "Pieces/bishop.h"
#include "Pieces/king.h"
#include "Pieces/queen.h"
#include "Pieces/rook.h"
#include "Pieces/knight.h"


#define BLACK 0
#define WHITE 1

constexpr unsigned int BOARD_WIDTH = 8;
constexpr unsigned int BOARD_HEIGHT = 8;

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
	void InitBoard();

	void MousePressed();
	void CellPressed(int row, int col);

	Piece* m_cells[BOARD_HEIGHT][BOARD_WIDTH];
private:
	virtual void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void Selected(unsigned int row, unsigned int col);
	void ResetBoard();
	void SwapPieces(Piece* p, Piece* p2);

	sf::RenderWindow* m_target = nullptr;
	unsigned int m_rows;
	unsigned int m_cols;

	sf::Texture m_tileset;

	bool turn;
	Piece* m_selected = nullptr;
};