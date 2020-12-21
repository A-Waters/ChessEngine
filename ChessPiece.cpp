#include "ChessPiece.h"


ChessPiece::ChessPiece(ChessPieceType type, Teams color, Vector2 location, bool firstMove) {
	this->m_type = type;
	this->m_color = color;
	this->m_location = location;
	this->m_firstMove = firstMove;
}

ChessPiece::ChessPiece() {
	this->m_type = NONE;
	this->m_color = NEUTRAL;
	this->m_location = { 0,0 };
	this->m_firstMove = false;
}

ChessPiece::ChessPiece(const ChessPiece& other) {
	this->m_color = other.m_color;
	this->m_type = other.m_type;
	this->m_location = other.m_location;
	this->m_firstMove = other.m_firstMove;

}