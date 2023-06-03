#include "algo.h"
#include "../model.h"

#include <chrono>
#include <thread>

Node* MCTS::findBestChild(std::vector<Node*> children)
{
	Node* bestChild = children[0];
	double bestExpValue = -DBL_MAX;
	for (Node* child : children) {
		double expValue = child->ExploitationValue();
		if (expValue > bestExpValue) {
			bestChild = child;
			bestExpValue = expValue;
		}
	}
	return bestChild;
}

Node* MCTS::select(Node* node)
{
	while (!node->IsLeaf())
	{
		node = node->GetBestChild();
	}
	return node;
}

Node* MCTS::expand(Node* parent)
{
	GameModel* parentState = parent->GetState();
	std::vector<Move> availableMoves = parentState->GetAvailableMoves(0);

	if (availableMoves.empty()) {
		return parent;
	}

	for (Move& availableMove : availableMoves) {
		GameModel* childState = new GameModel(parentState);
		childState->ExecuteMove(availableMove);
		Node* child = new Node(childState, &availableMove, parent);
		parent->AddChild(child);
	}

	return parent->GetRandomChild();
}

Move MCTS::GetRandomMove(std::vector<Move>& moves)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, moves.size()-1);

	Move move = moves[dist(gen)];
	return move;
}

int MCTS::simulate(Node* node)
{
	GameModel* state = node->GetState();
	std::vector<Move> availableMoves;

	bool turn = 0; 
	bool game_status = false;

	availableMoves = state->GetAvailableMoves(turn);
	while (!availableMoves.empty() || game_status) {
		Move randomMove = GetRandomMove(availableMoves);
		game_status = state->ExecuteMove(randomMove);
		turn = !turn;
		availableMoves = state->GetAvailableMoves(turn);
		state->ToString();

	}
	return !turn;
}

void MCTS::BackPropagation(Node* node, int wins)
{
	while (node != nullptr)
	{
		node->Update(wins);
		node = node->GetParent();
	}
}


Move MCTS::GetNextMove(GameModel* state)
{
	Node* root = new Node(state);
	for (unsigned int i = 0; i < simulations; i++)
	{
		Node* node = select(root);
		Node* selected = node;
		if (node->GetVisits() != 0)
		{
			selected = expand(node);
		}
		int wins = simulate(selected);
		BackPropagation(selected, wins);
	}
	Node* bestChild = findBestChild(root->GetChildren());
	return *bestChild->GetMove();
}

void Node::Update(int wins)
{
	this->m_wins += wins;
	this->m_visits++;
}

bool Node::IsLeaf()
{
	return m_children.empty();
}

Node* Node::GetBestChild()
{
	Node* max = m_children[0];
	double maxUCT = 0;
	for (Node* child : m_children) {
		double uct = child->UCTValue();
		if (uct > maxUCT)
		{
			maxUCT = uct;
			max = child;
		}
	}
	return max;
}

void Node::AddChild(Node* child)
{
	m_children.push_back(child);
}

Node* Node::GetRandomChild()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	if (IsLeaf())
		return nullptr;
	std::uniform_int_distribution<int> dist(0, m_children.size());
	return m_children[dist(gen)];
}

double Node::ExploitationValue()
{
	if (m_visits == 0) {
		return 0;
	}
	return (double)m_wins / m_visits;
}


double Node::ExplorationValue()
{
	return exploration * std::sqrt(std::log(m_parent->m_visits) / m_visits);
}


double Node::UCTValue()
{
	return ExploitationValue() + ExplorationValue();
}
