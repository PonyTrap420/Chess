#pragma once

class GameModel;
struct Move;


class Node {
public:

	Node(GameModel* state)
		:m_state(state)
	{
	}

	Node(GameModel* state, Move* move, Node* parent)
		:m_parent(parent), m_move(move), m_state(state)
	{
	}

	void Update(int wins);

	double UCTValue();

	bool IsLeaf();

	Node* GetBestChild();

	void AddChild(Node* child);

	Node* GetRandomChild();

	double ExploitationValue();
	double ExplorationValue();

	int GetVisits() { return m_visits; }
	Move* GetMove() { return m_move; }
	GameModel* GetState() { return m_state; }
	Node* GetParent() { return m_parent; }
	std::vector<Node*> GetChildren() { return m_children; }



private:
	Node* m_parent = nullptr;
	std::vector<Node*> m_children = {};

	int m_wins = 0;
	int m_visits = 0;
	Move* m_move;
	GameModel* m_state;
};

class MCTS {
public:
	
	Move GetNextMove(GameModel* state);

private:

	Node* findBestChild(std::vector<Node*> children);

	Node* select(Node* node);

	Node* expand(Node* parent);

	int simulate(Node* node);

	void BackPropagation(Node* node, int wins);

	Move GetRandomMove(std::vector<Move>& moves);

};