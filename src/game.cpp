#include "game.h"

Game::Game(sf::RenderWindow& window, unsigned int rows, unsigned int cols)
{
	this->m_target = &window;
	this->m_rows = rows;
	this->m_cols = cols;
	InitBoard();
}

void Game::InitBoard()
{
	turn = 1;
	this->m_state = DrawState::Board;
	for (unsigned int i = 0; i < m_rows; i++)
	{
		m_cells[i][1] = new Pawn(i, 1, BLACK);
		m_cells[i][6] = new Pawn(i, 6, WHITE);
		for (unsigned int j = 2; j < m_cols - 2; j++)
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
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_state == DrawState::EndGame)
	{
		sf::Font font;
		font.loadFromFile("assets/kanit.ttf");
		std::string team[2] = {"Black", "White"};
		sf::Text text(sf::String(team[!turn] + " Has Won"),font,70);
		text.setPosition(sf::Vector2f(170.f, 330.f));

		target.draw(text);

		if (m_cells[1][1]->GetTeam())
		{
			for (unsigned int i = 0; i < m_rows; i++)
			{
				for (unsigned int j = 0; j < m_cols; j++)
				{
					delete m_cells[i][j];
				}
			}
		}

		return;
	}
	for (unsigned int i = 0; i < m_rows; i++)
	{
		for (unsigned int j = 0; j < m_cols; j++)
		{
			sf::RectangleShape* shape = m_cells[i][j]->getShape();
			sf::RectangleShape* texture = m_cells[i][j]->getTexture();

			target.draw(*shape);
			target.draw(*texture);

			if (m_cells[i][j]->m_isSelected)
			{
				sf::CircleShape selected(10,100);

				if (m_cells[i][j]->GetTeam() != -1)
					selected.setFillColor(sf::Color(209, 56, 56, 200));
				else
					selected.setFillColor(sf::Color(56, 115, 209, 200));
				selected.setPosition(shape->getPosition() + sf::Vector2f(40.f,40.f));
				target.draw(selected);
			}
		}
	}

	if (m_state == DrawState::PieceMenu)
	{
		sf::RectangleShape menu(sf::Vector2f(800.f, 300.f));
		menu.setFillColor(sf::Color(12,12,12,70));
		menu.setPosition(sf::Vector2f(0,250.f));

		target.draw(menu);

		PIECE_TYPE types[4] = { KNIGHT, QUEEN, BISHOP, ROOK };
		int offset = 50;
		sf::Texture k;
		for (unsigned int i = 0; i < 4; i++)
		{
			sf::RectangleShape type(sf::Vector2f(140.f, 140.f));
			type.setPosition(sf::Vector2f(offset, 330));
			type.setFillColor(sf::Color(56, 115, 209, 255));

			k.loadFromFile("assets/pieces.png", sf::IntRect(PIECE_WIDTH * types[i], 0, PIECE_WIDTH, PIECE_WIDTH));
			type.setTexture(&k);

			offset += 187;
			target.draw(type);
		}
	}
}

void Game::MousePressed()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*m_target);
	sf::Vector2f coords = m_target->mapPixelToCoords(mouse);
	if (m_state == DrawState::Board)
	{
		CellPressed(coords.x / 100, coords.y / 100);
	}
	else if (m_state == DrawState::PieceMenu)
	{
		int x = m_selected->x;
		int y = m_selected->y;
		delete m_cells[x][y];

		switch (int(coords.x / 187))
		{
			case 0:
				m_cells[x][y] = new Knight(x, y, !m_selected->GetTeam());
				break;
			case 1:
				m_cells[x][y] = new Queen(x, y, !m_selected->GetTeam());
				break;
			case 2:
				m_cells[x][y] = new Bishop(x, y, !m_selected->GetTeam());
				break;
			case 3:
				m_cells[x][y] = new Rook(x, y, !m_selected->GetTeam());
				break;
		}
		m_state = DrawState::Board;
	}
	else
		InitBoard();
}

void Game::CellPressed(int row, int col)
{
	if (m_cells[row][col]->GetTeam() != turn && m_cells[row][col]->GetTeam() != -1 && !m_cells[row][col]->m_isSelected)
		return;

	if (m_cells[row][col]->m_isSelected)
	{
		if (m_cells[row][col]->GetType() == KING)
		{
			m_state = DrawState::EndGame;
		}

		delete m_cells[row][col];

		int prev_row = m_selected->x;
		int prev_col = m_selected->y;

		m_selected->Move(row, col);
		m_cells[row][col] = m_selected;

		m_cells[prev_row][prev_col] = new Empty(prev_row, prev_col);

		if (m_cells[row][col]->GetType() == PAWN && (m_cells[row][col]->GetTeam() == 0 && col == 7 || m_cells[row][col]->GetTeam() == 1 && col == 0))
		{
			m_state = DrawState::PieceMenu;
		}

		ResetBoard();

		if (turn == 1)
			turn = 0;
		else
			turn = 1;
		return;
	}
	if (m_cells[row][col]->GetType() == NONE || m_cells[row][col] == m_selected)
		return;

	ResetBoard();

	m_selected = m_cells[row][col];

	std::vector<sf::Vector2u> moves = m_cells[row][col]->ShowMoves(this);
	for (sf::Vector2u pos : moves)
	{
		if (pos.y < 0 || pos.y >= 8 || pos.x < 0 || pos.x >= 8)
			continue;

		if (m_cells[pos.x][pos.y]->GetTeam() == m_selected->GetTeam())
		{
			continue;
		}

		Selected(pos.x, pos.y);
	}

	sf::RectangleShape* shape = m_cells[row][col]->getShape();
	sf::Color c = sf::Color(56, 115, 209, 255);
	shape->setFillColor(c);

}

void Game::Selected(unsigned int row, unsigned int col)
{
	m_cells[row][col]->m_isSelected = true;
	sf::RectangleShape* shape = m_cells[row][col]->getShape();
	sf::Color c = shape->getFillColor();
	if ((row + col) % 2 == 0)
	{
		c += sf::Color(50, 50, 50, 255);
	}
	else
	{
		c -= sf::Color(50, 50, 50, 20);
	}
	shape->setFillColor(c);
}

void Game::ResetBoard() {
	for (unsigned int i = 0; i < m_rows; i++)
	{
		for (unsigned int j = 0; j < m_cols; j++)
		{
			m_cells[i][j]->m_isSelected = false;
			sf::RectangleShape* shape = m_cells[i][j]->getShape();

			sf::Color c(255, 255, 255, 255);
			if ((i + j) % 2 == 0)
				c = sf::Color(20, 20, 20, 255);

			shape->setFillColor(c);
		}
	}
}

void Game::SwapPieces(Piece* p, Piece* p2)
{
	Piece* temp = p;

}