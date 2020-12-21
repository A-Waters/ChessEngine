#pragma once
#include <vector>
#include "Vector2.h"

class Move
{
	Move* m_motherMove;
	Vector2 m_old_pos;
	Vector2 m_new_pos;
	
	

	public:
		Move();
		Move(Vector2 old_pos, Vector2 new_pos , Move* mother);
		Vector2 getOldPos() { return m_old_pos; };
		Vector2 getNewPos() { return m_new_pos; };
		Move* getMotherMove() { return m_motherMove; };
		std::vector<Move*> getAllPreviousMoves();
		~Move();

};

