#include "ChessBoard.h"

ChessBoard::ChessBoard() {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			Vector2 location = { signed char(x), signed char(y) };
			this->m_board[x][y] = ChessPiece(NONE, NEUTRAL, location, true);
		}
	}
	

	this->m_points[0] = 0.0f;
	this->m_points[1] = 0.0f;

	this->m_current_team = WHITE;

	this->m_last_move = nullptr;

	return;
};

ChessBoard::ChessBoard(const ChessBoard& other) {

	
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			this->m_board[x][y] = other.m_board[x][y];
		}
	}

	this->m_points[0] = other.m_points[0];
	this->m_points[1] = other.m_points[1];

	this->m_current_team = other.m_current_team;

	this->m_last_move = other.m_last_move;


}

ChessBoard::~ChessBoard() {}

void ChessBoard::standardStart() {
	
	//ChessBoard[x][y]

	//pawns
	for (int i = 0; i < 8; i++) {

		Vector2 location = { signed char(i), signed char(1) };
		this->m_board[i][1] = ChessPiece(PAWN, WHITE, location, true);
		
		location.y = 6;
		this->m_board[i][6] = ChessPiece(PAWN, BLACK, location, true);
	}
	
	//majors- white
	Vector2 location = { 0,0 };

	this->m_board[0][0] = ChessPiece(ROOK, WHITE, location, true);
	
	location.y = 1;
	this->m_board[1][0] = ChessPiece(KNIGHT, WHITE, location, true);

	location.y = 2;
	this->m_board[2][0] = ChessPiece(BISHIOP, WHITE, location, true);

	location.y = 3;
	this->m_board[3][0] = ChessPiece(KING, WHITE, location, true);

	location.y = 4;
	this->m_board[4][0] = ChessPiece(QUEEN, WHITE, location, true);

	location.y = 5;
	this->m_board[5][0] = ChessPiece(BISHIOP, WHITE, location, true);

	location.y = 6;
	this->m_board[6][0] = ChessPiece(KNIGHT, WHITE, location, true);

	location.y = 7;
	this->m_board[7][0] = ChessPiece(ROOK, WHITE, location, true);

	//majors - black

	location.y = 0;
	location.x = 7;

	this->m_board[0][7] = ChessPiece(ROOK, BLACK, location, true);

	location.y = 1;
	this->m_board[1][7] = ChessPiece(KNIGHT, BLACK, location, true);

	location.y = 2;
	this->m_board[2][7] = ChessPiece(BISHIOP, BLACK, location, true);

	location.y = 3;
	this->m_board[3][7] = ChessPiece(KING, BLACK, location, true);

	location.y = 4;
	this->m_board[4][7] = ChessPiece(QUEEN, BLACK, location, true);

	location.y = 5;
	this->m_board[5][7] = ChessPiece(BISHIOP, BLACK, location, true);

	location.y = 6;
	this->m_board[6][7] = ChessPiece(KNIGHT, BLACK, location, true);

	location.y = 7;
	this->m_board[7][7] = ChessPiece(ROOK, BLACK, location, true);


	return;

}

void ChessBoard::CustomStart() {
	this->m_board[4][4] = ChessPiece(QUEEN, WHITE, {(signed char)4,(signed char)4}, true);
	this->m_board[4][3] = ChessPiece(PAWN, BLACK, { (signed char)4,(signed char)4 }, false);
}

std::vector<Move*> ChessBoard::getPossibleMoves(Vector2 location, PoolAllocator<Move>* pool) {

	std::vector<Move*> possible_moves = {};

	ChessPiece current_piece = this->m_board[location.x][location.y];

	switch (current_piece.getType())
	{
	case PAWN:

		possible_moves.reserve(5);

		int y_movement; 


		if (current_piece.getTeam() == WHITE) {
			y_movement = location.y + 1;
		}
		else {
			y_movement = location.y - 1;
		}


		if (current_piece.getFirstMove()) {
			if (current_piece.getTeam() == WHITE) {

				if (this->m_board[location.x][location.y + 2].getType() == NONE) {
					Vector2 new_location = {location.x, location.y + 2};
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}

			}
			else {
				if (this->m_board[location.x][location.y - 2].getType() == NONE) {
					Vector2 new_location = { location.x, location.y - 2 };
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			}
		}


		if (y_movement >= 0 && y_movement <= 7) {
			if (location.x >= 0 && location.x <= 7) {
				if (this->m_board[location.x][y_movement].getType() == NONE) {
					Vector2 new_location = { location.x,signed char(y_movement) };
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			}


			if (location.x + 1 >= 0 && location.x + 1 <= 7) {
				if (this->m_board[location.x + 1][y_movement].getType() != NONE) {
					Teams color = this->m_board[location.x + 1][y_movement].getTeam();
					if (color != current_piece.getTeam()) {
						Vector2 new_location = { location.x + 1,signed char(y_movement) };
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}

				}
			}


			if (location.x - 1 >= 0 && location.x <= 7) {
				if (this->m_board[location.x - 1][y_movement].getType() != NONE) {
					Teams color = this->m_board[location.x - 1][y_movement].getTeam();
					if (color != current_piece.getTeam()) {
						Vector2 new_location = { location.x - 1,signed char(y_movement) };
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}

				}
			}

		}

		break;



	case ROOK:
		possible_moves.reserve(14);

		for (int x = location.x-1; x > -1; x--) {

				Vector2 new_location = { signed char(x), location.y};
				if (this->m_board[x][location.y].getType() != NONE) {
					Teams color = this->m_board[x][location.y].getTeam();
					
					if (color != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
					

				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			

		}



		for (int x = location.x + 1; x < 8; x++) {
			Vector2 new_location = { signed char(x), location.y };
			if (this->m_board[x][location.y].getType() != NONE) {
				Teams color = this->m_board[x][location.y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;


			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}
			
		}


		for (int y = location.y + 1; y < 8; y++) {
			Vector2 new_location = { location.x, signed char(y) };
			if (this->m_board[location.x][y].getType() != NONE) {
				Teams color = this->m_board[location.x][y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;


			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}
			
		}


		for (int y = location.y - 1; y > -1; y--) {

			Vector2 new_location = { location.x, signed char(y) };
			if (this->m_board[location.x][y].getType() != NONE) {
				Teams color = this->m_board[location.x][y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;


			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}
		

		}

		break;

	case KNIGHT:
		possible_moves.reserve(8);

		{

		int places_to_check[8][2] = {
			{location.x + 2, location.y + 1},
			{location.x + 2, location.y - 1},
			{location.x + 1, location.y + 2},
			{location.x + 1, location.y - 2},
			{location.x - 1, location.y + 2},
			{location.x - 1, location.y - 2},
			{location.x - 2, location.y + 1},
			{location.x - 2, location.y - 1}
		};

		for (int i = 0; i < 8; i++) {
			if (places_to_check[i][0] < 0 || places_to_check[i][1] < 0 || places_to_check[i][1] > 7 || places_to_check[i][0] > 7) {
				continue;
			}

			Vector2 new_location = { signed char(places_to_check[i][0]),signed char(places_to_check[i][1]) };
			if (this->m_board[places_to_check[i][0]][places_to_check[i][1]].getType() != NONE) {
				if (this->m_board[places_to_check[i][0]][places_to_check[i][1]].getTeam() != current_piece.getTeam())
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}
			else
			{
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}

		}

		
		}
		break;
	case BISHIOP:
		possible_moves.reserve(16);

		for (int i = 1; i < 8; i++) {

			
			Vector2 new_location = { signed char(location.x + i), signed char(location.y + i) };

			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}


			}
			


			

		}


		for (int i = 1; i < 8; i++) {

			
			Vector2 new_location = { signed char(location.x - i), signed char(location.y - i) };
			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}

			}
			


		}



		for (int i = 1; i < 8; i++) {

			
			Vector2 new_location = { signed char(location.x - i), signed char(location.y + i) };
			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}


			}
			
		}


		for (int i = 1; i < 8; i++) {

			
			Vector2 new_location = { signed char(location.x + i), signed char(location.y - i) };
			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}


			}

		}

		break;



	case QUEEN:
		possible_moves.reserve(18);

		//BISHIOP MOVEMENT 
		for (int i = 1; i < 8; i++) {


			Vector2 new_location = { signed char(location.x + i), signed char(location.y + i) };

			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			}
		}


		for (int i = 1; i < 8; i++) {
			Vector2 new_location = { signed char(location.x - i), signed char(location.y - i) };
			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			}
		}



		for (int i = 1; i < 8; i++) {
			Vector2 new_location = { signed char(location.x - i), signed char(location.y + i) };
			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			}
		}


		for (int i = 1; i < 8; i++) {
			Vector2 new_location = { signed char(location.x + i), signed char(location.y - i) };
			if (new_location.isPosValid()) {

				if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
					if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
					break;
				}
				else {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
			}
		}


		//ROOK MOVEMENT

		for (int x = location.x - 1; x > -1; x--) {

			Vector2 new_location = { signed char(x), location.y };
			if (this->m_board[x][location.y].getType() != NONE) {
				Teams color = this->m_board[x][location.y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;
			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}
		}



		for (int x = location.x + 1; x < 8; x++) {
			Vector2 new_location = { signed char(x), location.y };
			if (this->m_board[x][location.y].getType() != NONE) {
				Teams color = this->m_board[x][location.y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;
			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}
		}


		for (int y = location.y + 1; y < 8; y++) {
			Vector2 new_location = { location.x, signed char(y) };
			if (this->m_board[location.x][y].getType() != NONE) {
				Teams color = this->m_board[location.x][y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;
			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}

		}


		for (int y = location.y - 1; y > -1; y--) {

			Vector2 new_location = { location.x, signed char(y) };
			if (this->m_board[location.x][y].getType() != NONE) {
				Teams color = this->m_board[location.x][y].getTeam();

				if (color != current_piece.getTeam()) {
					possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
				}
				break;
			}
			else {
				possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
			}

		}

		break;

		//king movement is in the next section , roll over


	case KING:
		possible_moves.reserve(8);
		//overlaps with rook moves
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				
				Vector2 new_location = { signed char(location.x + x), signed char(location.y + y) };
				if (new_location.isPosValid()) {
					if (this->m_board[new_location.x][new_location.y].getType() != NONE) {
						if (this->m_board[new_location.x][new_location.y].getTeam() != current_piece.getTeam()) {
							possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
						}
					}
					else {
						possible_moves.push_back(pool->alloc(location, new_location, this->m_last_move));
					}
				}
			}
		}

		break;

	default:
		break;
	}
	possible_moves.shrink_to_fit();
	return possible_moves;
}

std::vector<Move*> ChessBoard::getAllPossibelMoves(PoolAllocator<Move>* pool) {

	std::vector<Move*> all_moves;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			Vector2 piece_location = { signed char(x), signed char(y) };
			std::vector<Move*> piece_moves = getPossibleMoves(piece_location, pool);
			all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());


		}
	}


	return all_moves;
}

std::vector<Move*> ChessBoard::getAllPossibelMovesForTeam(Teams color, PoolAllocator<Move>* pool) {

	std::vector<Move*> all_moves;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (this->m_board[x][y].getTeam() == color) {
				Vector2 piece_location = { signed char(x), signed char(y) };
				std::vector<Move*> piece_moves = getPossibleMoves(piece_location, pool);
				all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
			}
		}
	}


	return all_moves;
}

void ChessBoard::drawBoard() {


	for (int y = 0; y < 8; y++) {
		std::cout << y << " | ";

		for (int x = 0; x < 8; x++) {
			std::cout << this->m_board[x][y].getType() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "    ";
	for (int x = 0; x < 8; x++) {
		std::cout << "--";
	}
	std::cout << std::endl;
	std::cout << "    ";
	for (int x = 0; x < 8; x++) {
		std::cout << x << " ";
	}
	std::cout << std::endl;


	std::cout << this->m_board[0][1].getType() << std::endl;
}

std::queue<std::vector<Move*>> ChessBoard::setupMiniMax(int goal_depth, PoolAllocator<Move>* m_pools) {

	std::vector<std::thread> threads;

	const int MAX_THREADS = 8; //std::thread::hardware_concurrency()

	std::queue<std::vector<Move*>> distrbiuted_games[MAX_THREADS]; // 8 = std::thread::hardware_concurrency() change if needed

	std::queue<std::vector<Move*>> all_games;

	all_games.push(this->getAllPossibelMovesForTeam(m_current_team, &m_pools[0]));


	int current_depth = 0;
	while (current_depth != goal_depth+1) {
		std::cout << "CURRENT DEPTH: " << current_depth << std::endl;
		
		int current_thread = 0;
		//catoagrize games
		while (all_games.size() > 0) {
			distrbiuted_games[current_thread].push(all_games.front());
			all_games.pop();
			current_thread = (current_thread + 1) % MAX_THREADS;
		}

		//distribute games
		for (int thread = 0; thread < MAX_THREADS; thread++) {
			threads.push_back(std::thread(&ChessBoard::startMiniMax, this, std::ref(distrbiuted_games[thread]), std::ref(m_pools[thread])));
		}

		
		//moves games back to all games
		for (int thread = 0; thread < MAX_THREADS; thread++) {

			std::cout << "Joining thread " << threads[thread].get_id() << std::endl;
			threads[thread].join();
			while (distrbiuted_games[thread].size() > 0) {
				all_games.push(distrbiuted_games[thread].front());
				distrbiuted_games[thread].pop();
			}
		}
	


		
		
		threads.clear();
		current_depth++;
	}

	
	
	
		
	





	
	/*

	for (int i = 0; i < (int)std::thread::hardware_concurrency(); i++) {
		std::cout << "Creating thread" << std::endl;
		threads.push_back(std::thread(&ChessBoard::startMiniMax, this, goal_depth, std::ref(all_games), std::ref(m_pools[i])));
		
	}
	
	


	for (std::thread &th : threads) {
		std::cout << "Joining thread " << th.get_id() << std::endl;
		th.join(); 
		
	}
	
	*/


	//start alogorithm


	return all_games;
	

}

void ChessBoard::movePiece(Move* move_to_make) {
	Vector2* old_pos = &move_to_make->getOldPos();
	Vector2* new_pos = &move_to_make->getNewPos();

	this->m_board[new_pos->x][new_pos->y] = this->m_board[old_pos->x][old_pos->y];
	this->m_board[old_pos->x][old_pos->y] = ChessPiece(NONE, NEUTRAL, *old_pos, false);
	
	this->m_board[new_pos->x][new_pos->y].setFirstMove(false);

	if (this->m_current_team == WHITE)
		this->m_current_team = BLACK;
	else
		this->m_current_team = WHITE;


	this->m_last_move = move_to_make;
	
}

void ChessBoard::startMiniMax(std::queue<std::vector<Move*>>& give_games, PoolAllocator<Move>& pool_to_use) {
	std::cout << "DOING MATH" << std::endl;
	
	int games_to_run = give_games.size();
	int games_ran = 0;

	while (games_ran != games_to_run) {
		std::vector<Move*> moves_to_run = give_games.front();
		give_games.pop();

		//make previous moves
		ChessBoard current_game = ChessBoard();
		current_game.standardStart();

		std::vector<Move*> previous_moves = moves_to_run[0]->getAllPreviousMoves();
		
		for (Move* prev_move : previous_moves) {
			current_game.movePiece(prev_move);
		}
		
		//for (Move* move_to_make : moves_to_run) {
		for (int i = 0; i < moves_to_run.size(); i++) {
			Move* move_to_make = moves_to_run[i];

			//create starting position
			ChessBoard future_game = current_game;

			// move piece
			future_game.movePiece(move_to_make);

			//get all possible moves from future game
			std::vector<Move*> future_moves = future_game.getAllPossibelMovesForTeam(future_game.m_current_team, &pool_to_use);

			//push games 
			give_games.push(future_moves);

		}

		games_ran++;
		
	}
	
}
