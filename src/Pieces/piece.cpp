#include "piece.h"

Piece::Piece(unsigned int x, unsigned int y, PIECE_TYPE type, int team)
{
	this->x = x;
	this->y = y;
	this->m_type = type;
	this->m_team = team;
	
	unsigned int height = 0;
	
	m_texture = new sf::Texture();
	m_shape = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
	m_textureShape = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));

	if (team == 0)
	{
		height = PIECE_WIDTH;
	}

	sf::Color c(107, 149, 189, 255);
	if ((x + y) % 2 == 0)
		c = sf::Color(198, 222, 255, 255);

	m_texture->loadFromFile("assets/pieces.png", sf::IntRect(PIECE_WIDTH * m_type, height, PIECE_WIDTH, PIECE_WIDTH));
	m_texture->setSmooth(true);

	m_shape->setFillColor(c);													 
	m_shape->setPosition(x * 100, y * 100);										 
	m_textureShape->setPosition(x * 100, y * 100);								 
																				 
	m_textureShape->setTexture(m_texture);

	m_shape->setOutlineThickness(2);											 
	m_shape->setOutlineColor(sf::Color(56, 115, 209, 255));						 
}																				 
																				 
void Piece::MovePiece(unsigned int x, unsigned int y)								 
{																				 
	this->x = x;																 
	this->y = y;																 
																				 
	sf::Color c(107, 149, 189, 255);
	if ((x + y) % 2 == 0)														 																	 
		c = sf::Color(198, 222, 255, 255);

	m_shape->setFillColor(c);													 
	m_shape->setPosition(x * 100, y * 100);										 
	m_textureShape->setPosition(x * 100, y * 100);								 
}
