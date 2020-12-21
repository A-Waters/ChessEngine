// Chess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ChessBoard.h"
#include <vector>
#include "Move.h"
#include "PoolAllocatorr.h"
#include <thread>

int main()
{
    std::cout << std::thread::hardware_concurrency() << std::endl;
    

    PoolAllocator<Move> Pool;
    ChessBoard newGame = ChessBoard(&Pool);

    newGame.standardStart();
    ChessBoard copy_game = newGame;
    

    
    //int location[2] = { 1, 0 };
    //std::vector<Move> moves = newGame.getAllPossibelMoves();
    
    int turns = 1;
    std::queue<std::vector<Move*>> moves = newGame.fakeMiniMax(turns);


    std::cout << "GameStates:" << moves.size() << std::endl;

    newGame.drawBoard();

    moves.pop();
    moves.pop();
    Move* move_to_make = moves.front().at(0);

    std::cout << "Moves In GameState after " << turns << " Turns: " << moves.front().size() << std::endl;
    
    std::vector<Move*> previous_moves = move_to_make->getAllPreviousMoves();

    for (Move* prev_move : previous_moves) {

        newGame.movePiece(prev_move);
        std::cout << prev_move->getOldPos() << " >> " << prev_move->getNewPos() << std::endl;
    }


    newGame.drawBoard();
    
    
    
}





