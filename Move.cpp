#include "Move.h"

Move::Move(Vector2 old_pos, Vector2 new_pos, Move* mother) {
	m_motherMove = mother;

	this->m_old_pos.x = old_pos.x;
	this->m_old_pos.y = old_pos.y;

	this->m_new_pos.x = new_pos.x;
	this->m_new_pos.y = new_pos.y;

}


Move::Move() {
	m_motherMove = nullptr;

	this->m_old_pos.x = 0;
	this->m_old_pos.y = 0;

	this->m_new_pos.x = 0;
	this->m_new_pos.y = 0;
}

Move::~Move() {
	int i = 0;
}

std::vector<Move*> Move::getAllPreviousMoves(){
	
	std::vector<Move*> previous_moves;

	Move* move_to_check = this->getMotherMove();

	while (move_to_check != nullptr) {
		previous_moves.push_back(move_to_check);

		move_to_check = move_to_check->m_motherMove;
	}

	std::reverse(previous_moves.begin(), previous_moves.end());


	return previous_moves;
}