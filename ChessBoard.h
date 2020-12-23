#pragma once
#include "types.h"
#include <vector>
#include "move.h"
#include "chessPiece.h"
#include "PoolAllocatorr.h"
#include "Vector2.h"
#include <mutex>
#include <queue>
#include <thread>
#include <iostream> // for debugging
#include <Windows.h>
#include <functional>

class ChessBoard {

	ChessPiece m_board[8][8];
	float m_points[2];
	Teams m_current_team; //0 = white, black = 1
	Move* m_last_move;
	
	std::mutex get_job_mtx;
	std::mutex push_job_mtx;
	
	
	public:
		ChessBoard();
		ChessBoard(const ChessBoard &other);
		~ChessBoard();
		void standardStart();
		void CustomStart();
		void drawBoard();
		std::queue<std::vector<Move*>> setupMiniMax(int depth, PoolAllocator<Move>* pools);
		void movePiece(Move*);
	
	private:
		//void calculatePoints();
		std::vector<Move*> getPossibleMoves(Vector2, PoolAllocator<Move>*);
		std::vector<Move*> getNewJob(std::queue<std::vector<Move*>>& );
		void PushNewJob(std::queue<std::vector<Move*>>&, std::vector<Move*>&);
		std::vector<Move*> getAllPossibelMoves(PoolAllocator<Move>*);
		std::vector<Move*> getAllPossibelMovesForTeam(Teams, PoolAllocator<Move>*);
		void startMiniMax(int, std::queue<std::vector<Move*>>&, PoolAllocator<Move>&);
		int getJobsSize(std::queue<std::vector<Move*>>&);
		

};
