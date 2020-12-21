#pragma once
#include "types.h"
#include <vector>
#include "move.h"
#include "chessPiece.h"
#include "PoolAllocatorr.h"
#include "Vector2.h"
#include <queue>
#include <iostream> // for debugging

class ChessBoard {

	ChessPiece m_board[8][8];
	float m_points[2];
	Teams m_current_team; //0 = white, black = 1
	Move* m_last_move;
	PoolAllocator<Move>* pool;
	
	public:
		ChessBoard(PoolAllocator<Move>*);
		ChessBoard(const ChessBoard &other);
		void standardStart();
		void CustomStart();
		void drawBoard();
		std::queue<std::vector<Move*>> fakeMiniMax(int depth);
		std::vector<Move*> getAllPossibelMoves();
		std::vector<Move*> getAllPossibelMovesForTeam(Teams);
		void movePiece(Move*);
	
	private:
		//void calculatePoints();
		std::vector<Move*> getPossibleMoves(Vector2);
		

		

};
