#include "ChessPiece.h"


ChessPiece::ChessPiece(ChessPieceType type, Teams color, Vector2 location, bool firstMove) {
	this->m_type = type;
	this->m_color = color;
	this->m_location = location;
	this->m_firstMove = firstMove;

	switch (type)
	{
	case NONE:
		m_value = 0;
	case PAWN:
		m_value = 1;
	case ROOK:
		m_value = 5;
	case KNIGHT:
		m_value = 3;
	case BISHIOP:
		m_value = 3;
	case QUEEN:
		m_value = 9;
	case KING:
		m_value = 100;
	default:
		break;
	} 

	if (color == BLACK) {
		m_value *= -1;
	}
}

ChessPiece::ChessPiece() {
	this->m_type = NONE;
	this->m_color = NEUTRAL;
	this->m_location = { 0,0 };
	this->m_firstMove = false;
	this->m_value = 0;
}

ChessPiece::ChessPiece(const ChessPiece& other) {
	this->m_color = other.m_color;
	this->m_type = other.m_type;
	this->m_location = other.m_location;
	this->m_firstMove = other.m_firstMove;
	this->m_value = other.m_value;
}