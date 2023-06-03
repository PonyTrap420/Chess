#include "game.h"


Game::Game(sf::RenderWindow& window, unsigned int rows, unsigned int cols)
{
	this->m_target = &window;
	this->m_rows = rows;
	this->m_cols = cols;
	this->m_model = new GameModel();
	this->m_state = DrawState::Board;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_state == DrawState::EndGame)
	{
		sf::Font font;
		font.loadFromFile("assets/kanit.ttf");
		std::string team[2] = {"Black", "White"};
		sf::Text text(sf::String(team[winner] + " Has Won"),font,70);
		text.setPosition(sf::Vector2f(170.f, 330.f));

		target.draw(text);

		if (m_model->m_cells[1][1]->GetTeam())
		{
			for (unsigned int i = 0; i < m_rows; i++)
			{
				for (unsigned int j = 0; j < m_cols; j++)
				{
					delete m_model->m_cells[i][j];
				}
			}
		}

		return;
	}
	for (unsigned int i = 0; i < m_rows; i++)
	{
		for (unsigned int j = 0; j < m_cols; j++)
		{
			sf::RectangleShape* shape = m_model->m_cells[i][j]->getShape();
			sf::RectangleShape* texture = m_model->m_cells[i][j]->getTexture();

			target.draw(*shape);
			target.draw(*texture);

			if (m_model->m_cells[i][j]->m_isSelected)
			{
				sf::CircleShape selected(10,100);

				if (m_model->m_cells[i][j]->GetTeam() != -1)
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
		delete m_model->m_cells[x][y];

		switch (int(coords.x / 187))
		{
			case 0:
				m_model->m_cells[x][y] = new Knight(x, y, m_selected->GetTeam());
				break;
			case 1:
				m_model->m_cells[x][y] = new Queen(x, y, m_selected->GetTeam());
				break;
			case 2:
				m_model->m_cells[x][y] = new Bishop(x, y, m_selected->GetTeam());
				break;
			case 3:
				m_model->m_cells[x][y] = new Rook(x, y, m_selected->GetTeam());
				break;
		}
		m_state = DrawState::Board;
	}
	else{}
		//newgame
}

void Game::CellPressed(int row, int col)
{
	if (m_model->m_cells[row][col]->GetTeam() != m_model->turn && m_model->m_cells[row][col]->GetTeam() != -1 && !m_model->m_cells[row][col]->m_isSelected)
		return;

	if (m_model->m_cells[row][col]->m_isSelected)
	{
		if (m_model->m_cells[row][col]->GetType() == KING)
		{
			m_state = DrawState::EndGame;
			winner = WHITE;
		}

		Move m(row, col, m_selected);
		MovePiece(m);

		if (m_model->m_cells[row][col]->GetType() == PAWN && (m_model->m_cells[row][col]->GetTeam() == 0 && col == 7 || m_model->m_cells[row][col]->GetTeam() == 1 && col == 0))
		{
			m_state = DrawState::PieceMenu;
		}

		ResetBoard();

		m_model->turn = !m_model->turn;

		std::vector<Move> moves = m_model->GetAvailableMoves(0);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, moves.size() - 1);

		m_model->Search(3, INT_MIN, INT_MAX);

		m_selected = m_model->m_nextMove.piece;
		MovePiece(m_model->m_nextMove);
		if (m_model->m_nextMove.captured->GetType() == KING)
		{
			m_state = DrawState::EndGame;
			winner = BLACK;
		}
		
		m_model->turn = !m_model->turn;

		m_model->ToString();

		return;
	}
	if (m_model->m_cells[row][col]->GetType() == NONE || m_model->m_cells[row][col] == m_selected)
		return;

	ResetBoard();

	m_selected = m_model->m_cells[row][col];

	std::vector<Move> moves = m_model->m_cells[row][col]->ShowMoves(m_model);
	for (const Move& pos : moves)
	{
		m_model->m_cells[pos.x][pos.y]->m_isSelected = true;
	}

	sf::RectangleShape* shape = m_model->m_cells[row][col]->getShape();
	sf::Color c = sf::Color(56, 115, 209, 255);
	shape->setFillColor(c);

}

void Game::MovePiece(Move& move) {

	if (m_model->m_cells[move.x][move.y]->GetType() != NONE) {
		unsigned int team = m_model->m_cells[move.x][move.y]->GetTeam();
		std::vector<Piece*>* list;
		if (team == BLACK)
			list = &m_model->black;
		else
			list = &m_model->white;

		list->erase(std::remove(list->begin(), list->end(), m_model->m_cells[move.x][move.y]), list->end());

		m_player.openFromFile("assets/capture.mp3");
	}
	else
	{
		m_player.openFromFile("assets/move.mp3");
		
	}
	m_player.play();

	delete m_model->m_cells[move.x][move.y];

	int prev_row = move.piece->x;
	int prev_col = move.piece->y;

	m_selected->MovePiece(move.x, move.y);
	m_model->m_cells[move.x][move.y] = m_selected;

	m_model->m_cells[prev_row][prev_col] = new Empty(prev_row, prev_col);

}

void Game::ResetBoard() {
	for (unsigned int i = 0; i < m_rows; i++)
	{
		for (unsigned int j = 0; j < m_cols; j++)
		{
			m_model->m_cells[i][j]->m_isSelected = false;
			sf::RectangleShape* shape = m_model->m_cells[i][j]->getShape();

			sf::Color c(107, 149, 189, 255);
			if ((i + j) % 2 == 0)
				c = sf::Color(198, 222, 255, 255);

			shape->setFillColor(c);
		}
	}
}

void Game::SwapPieces(Piece* p, Piece* p2)
{
	Piece* temp = p;

}