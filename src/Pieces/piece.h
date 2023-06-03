#pragma once
#include "../pch.h"

class Game;
class GameModel;

constexpr unsigned int PIECE_WIDTH = 133;

enum PIECE_TYPE {
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN,
	NONE,
};

class Piece;

struct Move {
	unsigned prevx;
	unsigned prevy;

	unsigned int x;
	unsigned int y;
	Piece* piece;
	Piece* captured = nullptr;

	Move(unsigned x, unsigned y, Piece* piece)
	{
		this->x = x;
		this->y = y;
		this->piece = piece;
	}

	Move() {};
};

class Piece
{
public:
	unsigned int x;
	unsigned int y;
	bool m_isSelected = false;

	Piece(unsigned int x, unsigned int y, PIECE_TYPE type, int team);

	inline int GetTeam() { return m_team; }
	inline PIECE_TYPE GetType() { return m_type; }
	inline sf::RectangleShape* getShape(){ return m_shape; }
	inline sf::RectangleShape* getTexture() { return m_textureShape; }


	inline void setShape(sf::RectangleShape& shape) { this->m_shape = &shape; }
	inline void setTexture(sf::RectangleShape& texure) { this->m_textureShape = &texure; }

	virtual void MovePiece(unsigned int x, unsigned int y);
	virtual std::vector<Move> ShowMoves(GameModel* game) = 0;

private:
	sf::RectangleShape* m_shape = nullptr;
	sf::RectangleShape* m_textureShape = nullptr;
	sf::Texture* m_texture = nullptr;

protected:
	PIECE_TYPE m_type;
	int m_team;
};

class Empty : public Piece
{
public:
	inline Empty(unsigned int x, unsigned int y) : Piece(x, y, NONE, -1) {};

	inline std::vector<Move> ShowMoves(GameModel* game)
	{
		std::vector<Move> vec;
		return vec;
	}
private:
};