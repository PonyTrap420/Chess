#pragma once
#include "../pch.h"

class Game;

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

	virtual void Move(unsigned int x, unsigned int y);
	virtual std::vector<sf::Vector2u> ShowMoves(Game* game) = 0;

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

	inline std::vector<sf::Vector2u> ShowMoves(Game* game)
	{
		std::vector<sf::Vector2u> vec;
		return vec;
	}
private:
};