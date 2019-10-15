#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <chrono>
#include <float.h>

using namespace std;
using namespace std::chrono; 
class Point {
public:
	int x;
	int y;
	Point():x(0),y(0) {}
	Point(int x, int y):x(x),y(y) {}
};


//black-2 white-1
class Board {
public:
	vector<vector<char> > board;
	//vector<vector<int> > board( 16 , vector<int> (16,'*')); 
	int row=16, column= 16;
	vector<Point> greenCorner;
	vector<Point> redCorner;

vector<bool> detectWin()
{
	vector<bool> winCheckArray(2);
	bool redWin=false, greenWin=false;
	int x,y;

	//checking if all tiles in green corner are filled with red tiles
	for(auto coord: greenCorner)
	{
		x=coord.x;
		y=coord.y;
		if(board[x][y]=='*' || board[x][y]=='R'){
			redWin=false;
			break;
		}

		else if(board[x][y]=='G')
			redWin=true;

	}
	for(auto coord: redCorner)
	{
		x=coord.x;
		y=coord.y;
		if(board[x][y]=='*' || board[x][y]=='G'){
			greenWin=false;
			break;
		}

		else if(board[x][y]=='R')
			greenWin=true;

	}
	winCheckArray[0]=redWin;
	winCheckArray[1]=greenWin;
	return winCheckArray;

}
int switchTurn(int turn)
{
	if(turn==1)
		return 2;

	else
		return 1;

}

void getRedCorner()
{
	redCorner.push_back(Point(11,14));
	redCorner.push_back(Point(11,15));
	redCorner.push_back(Point(12,13));
	redCorner.push_back(Point(12,14));
	redCorner.push_back(Point(12,15));
	redCorner.push_back(Point(13,12));
	redCorner.push_back(Point(13,13));
	redCorner.push_back(Point(13,14));
	redCorner.push_back(Point(13,15));
	redCorner.push_back(Point(14,11));
	redCorner.push_back(Point(14,12));
	redCorner.push_back(Point(14,13));
	redCorner.push_back(Point(14,14));
	redCorner.push_back(Point(14,15));
	redCorner.push_back(Point(15,11));
	redCorner.push_back(Point(15,12));
	redCorner.push_back(Point(15,13));
	redCorner.push_back(Point(15,14));
	redCorner.push_back(Point(15,15));
}
void getGreenCorner()
{
	greenCorner.push_back(Point(0,0));
	greenCorner.push_back(Point(0,1));
	greenCorner.push_back(Point(0,2));
	greenCorner.push_back(Point(0,3));
	greenCorner.push_back(Point(0,4));
	greenCorner.push_back(Point(1,0));
	greenCorner.push_back(Point(1,1));
	greenCorner.push_back(Point(1,2));
	greenCorner.push_back(Point(1,3));
	greenCorner.push_back(Point(1,4));
	greenCorner.push_back(Point(2,0));
	greenCorner.push_back(Point(2,1));
	greenCorner.push_back(Point(2,2));
	greenCorner.push_back(Point(2,3));
	greenCorner.push_back(Point(3,0));
	greenCorner.push_back(Point(3,1));
	greenCorner.push_back(Point(3,2));
	greenCorner.push_back(Point(4,0));
	greenCorner.push_back(Point(4,1));
}

vector<Point> getGreenPosition()
{
	vector<Point> green_pos_list;

    for(int i=0;i<16;i++)
    {
    	for(int j=0;j<16;j++)
    	{
    		if(board[i][j]=='G')
    			green_pos_list.push_back(Point(i,j));
    	}
    }
    return green_pos_list;
}
vector<Point> getRedPosition()
{
	vector<Point> red_pos_list;
	for(int i=0;i<16;i++)
    {
    	for(int j=0;j<16;j++)
    	{
    		if(board[i][j]=='R')
    			red_pos_list.push_back(Point(i,j));
    	}
    }
    return red_pos_list;
}
bool find_redCorner(Point p)
{
	for(auto point:redCorner)
	{
		if((point.x==p.x) && (point.y==p.y))
			return true;
	}
	return false;
}

bool find_greenCorner(Point p)
{
	for(auto point:greenCorner)
	{
		if((point.x==p.x) && (point.y==p.y))
			return true;
	}
	return false;
}
char removePieceAt(Point p)
{
	char p1=board[p.x][p.y];
	board[p.x][p.y]='*';
	return p1;
}
void placePieceAt(Point p)
{

}
void movePieceTo(Point p)
{

}
char getPieceAt(Point p)
{
	return board[p.x][p.y];
}
void printBoard()
{
	for(int i=0;i<board.size();i++)
	{
		for(int j=0;j<board[0].size();j++)
			cout<<board[i][j];
	}
}
};
class Node{
	public:
		int player;
		int node_depth;
		int to_explore;
		int node_value;
		Board board;
		vector<Point> children;


};
class Moves
{
public:
	Point source;
	Point destination;
	Node node;

	Moves() {}
};



class Player
{
public:
	vector<Point> previous_spots;
	vector<Point> moves;
	int start;
	int end;
	int run_time;
int distance(Point p1, Point p2)
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.x-p2.y)*(p1.x-p2.y);
}
bool find_PrevCorner(Point p)
{
	for(auto point:previous_spots)
	{
		if((point.x==p.x) && (point.y==p.y))
			return true;
	}
	return false;
}
//recursive function to get jump chains for a specific position
vector<Point> jump_search(Point pt,Board board)
{
	
	vector<int> row_offsets={-1,0,1};
	vector<int> col_offsets={-1,0,1};
	vector<Point> jumps;
	int x=pt.x,y=pt.y, row_jump_offset, col_jump_offset;

	//check adjacent squares for valid jumps
	for(auto row_offset: row_offsets)
	{
		for(auto col_offset: col_offsets)
		{
			//out of bounds
			if(((x+row_offset)>=board.board.size()) or ((y+col_offset)< board.board[0].size()))
				continue;

			//if it is out of bounds
			if((x+row_offset<0) or (y+col_offset<0))
				continue;

			//check if we looking at the same location
			if (((x + row_offset) == x) and ((y + col_offset) == y))
                continue;

            //check if position at offset is filled
            if (board.board[x + row_offset][y + col_offset] != '*')
            {
                   // if it is, check the position past it to see if it is empty.
                   // Do this by doubling the x and y offsets and checking that position
                    row_jump_offset = x + 2*row_offset;
                    col_jump_offset = y + 2*col_offset;

                    if (((row_jump_offset) >= board.board.size()) or ((col_jump_offset) >= board.board[0].size()))
                        continue;

                    if ((row_jump_offset) < 0 or (col_jump_offset) < 0)
                        continue;


                    if (board.board[row_jump_offset][col_jump_offset] == '*' and !find_PrevCorner(Point(row_jump_offset,col_jump_offset )))
                    {
                    	Point p(row_jump_offset,col_jump_offset);
		            	if(board.board[x][y]=='R')
		            	{
		            		
		            		if (!board.find_redCorner(pt))
		            			if(board.find_redCorner(p))
		            				continue;


		            	}
		            	if(board.board[x][y]=='G')
		            	{
		            		
		            		if (!board.find_greenCorner(pt))
		            			if(board.find_greenCorner(p))
		            				continue;

		            			
		            	}
		            	previous_spots.push_back(pt);
		            	jumps.push_back(p);
		            	vector<Point> st=jump_search(Point(row_jump_offset, col_jump_offset), board);
						for(auto element: st)
							jumps.push_back(element);

						for(auto ele:st)
							moves.push_back(ele);


                    }

			}

		}
	}
	return jumps;
}

//function to check 8-directionally available spaces
vector<Point> step_search(Board board, Point pt)
{

	int x=pt.x,y=pt.y;
	vector<int> row_offsets={-1,0,1};
	vector<int> col_offsets={-1,0,1};
	vector<Point> legal_moves;

	if(x>=board.row or y>=board.column)
		return legal_moves;

	if(x<0 or y<0)
		return legal_moves;

	//no piece at that position
	if(board.board[x][y]==0)
		return legal_moves;

	for(auto row_offset: row_offsets)
	{
		for(auto col_offset: col_offsets)
		{
			//out of bounds
			if(((x+row_offset)>=board.row) or ((y+col_offset)< board.column))
				continue;

			//out of bounds
			if((x+row_offset<0) or (y+col_offset<0))
				continue;

			//check if we looking at the same location
			if (((x + row_offset) == x) and ((y + col_offset) == y))
                continue;

            //Check if the position at the offset is filled
            if (board.board[x + row_offset][y + col_offset] == '*')
            {
            	Point p(x + row_offset,y + col_offset);
            	if(board.board[x][y]=='R')
            	{
            		
            		if (!board.find_redCorner(pt))
            			if(board.find_redCorner(p))
            				continue;


            	}
            	if(board.board[x][y]=='G')
            	{
            		
            		if (!board.find_greenCorner(pt))
            			if(board.find_greenCorner(p))
            				continue;

            			
            	}

            	legal_moves.push_back(Point(x + row_offset, y + col_offset));
            }
            


		}
	}
	vector<Point> st=jump_search(Point(x, y), board);
	for(auto element: st)
		legal_moves.push_back(element);

	for(auto ele: st)
		moves.push_back(ele);

	return legal_moves;


}
double eval_function(Node node)
{

	Board board=node.board;
	int red,green=0;
	double value=0;
	vector<int> distanceList;
	vector<bool> winCheck(2);
	winCheck=board.detectWin();

	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			char piece=board.board[i][j];
			Point p(i,j);
			if(piece=='G')
			{
				for(auto point: board.redCorner)
				{
					if(board.board[point.x][point.y]!='G'){
						distanceList.push_back(distance(p,point));

					}
				}
				if(distanceList.empty())
					green=-100;

				else{
					int t=*max_element(distanceList.begin(), distanceList.end());
					green+=t;
				}


			}
			else if(piece=='R')
			{
				for(auto point: board.greenCorner)
				{
					if(board.board[point.x][point.y]!='R'){
						distanceList.push_back(distance(p,point));

					}
				}
				if(distanceList.empty())
					red=-100;

				else{
					int t=*max_element(distanceList.begin(), distanceList.end());
					red+=t;
				}


			}
			


		}
	}
	if(node.player==1)
		value = (double)red/green;

	else
        value = (double)green/red;

    if (winCheck[0])
        value = DBL_MAX;

    else if(winCheck[1])
        value = DBL_MAX;

    return value;


}

// Moves max_value(Board board,int alpha, int beta, Node node)
// {
// 	auto wincheck=detectWin(board);
// 	Moves best_move=NULL;
// 	if(winCheck[0]==true or winCheck[1]==true or node.node_depth<=0 or end-start>run_time)
// 	{
// 		node.node_value eval_score=eval_function(board,node);
// 		return Moves(node,best_move);

// 	}
// 	if(node.player == 1)
//         Vector<Point> player_positions = board.get_green_positions();
//     else if(player == 2)
//         Vector<Point> player_positions = board.get_red_positions();

//     double value=DBL_MIN;

//     for(auto p:player_positions)
//     {
//     	auto legal_moves=step_search(board,Point(p.x,p.y));
//     	if(legal_moves.size()==0)
//     		continue;

//     	for(auto legal_move:legal_moves)
//     	{
//     		auto end = high_resolution_clock::now(); 
//     		if(end-start>timeLimit)
//     		{
//     			best_move=
//     		}


//     	}

//     }

// }
// void alphaBetaMinimax(Node node)
// {
// // 	// def alphaBetaMinimax(self, node):
// //  //        self.start = time.time()
// //  //        max_node, best_move = self.maxValue(node, float("-inf"), float("inf"))
// //  //        data_board = node.get_board()
// //  //        data_board.move_piece(best_move[0], best_move[1])
// //  //        print("Took", self.end - self.start, "seconds to choose a move.")
// //  //        print("Pruned", self.prunes, "branches.")
// //  //        print("Generated", self.boards, "boards.")
// //  //        self.prunes = 0
// //  //        self.boards = 0
// //  //        data_board.chosenMove = best_move
// //  //        data_board.changeTurn()
// //  //        return max_node, best_move
// //  //        # return the action to do from the state

// 	auto start = high_resolution_clock::now(); 
// 	Moves m =maxValue(node, DBL_MIN, DBL_MAX);
// 	Node max_node=m.node;
// 	Point source=m.source;
// 	Point destination=m.destination;
// 	data_board=max_node.board;
// 	move_piece(source, destination);
// 	switchTurn();
// 	return m;
// }

void clear_moves(){
	moves.clear();
}



};






int main()
{
	string game_type, my_color;
	
	int play_time;
	int alpha = INT_MIN, beta = INT_MAX;
	float run_time;

	ifstream fin;
    fin.open("input.txt");

    fin>>game_type>>my_color>>play_time;
    Board board;

    for (int i = 0; i < 16; i++) 
        for (int j = 0; j < 16; j++)
            fin>> board.board[i][j];




return 0;
}