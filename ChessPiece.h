#pragma once
#include "Types.h"
#include <vector>
#include "Move.h"
#include "Vector2.h"


class ChessPiece 
{
	ChessPieceType m_type;
	Vector2 m_location;
	Teams m_color;
	bool m_firstMove;
	int m_value; 

	public:
		ChessPiece();
		ChessPiece(ChessPieceType type, Teams color, Vector2 location, bool firstMove);
		ChessPiece(const ChessPiece& other);
	
		ChessPieceType getType() { return m_type; };
		Vector2 getLocation() { return m_location; };
		Teams getTeam() { return m_color; };
		bool getFirstMove() { return  m_firstMove; };

		void setFirstMove(bool value) { m_firstMove = value; };

};

