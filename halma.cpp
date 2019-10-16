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
	vector<Point> greenCorner;
	vector<Point> redCorner;
	int turn =2;
	Board() {
		board.resize(16);

		for (int i = 0; i < 16; ++i)	
			board[i].resize(16);
	}

	Board(vector<vector<char>> dup_board) { 
		board = dup_board;
		greenCorner = getGreenCorner();
		redCorner = getRedCorner();
	}
	Board(const Board &bref) 
	{
		board = bref.board;
		greenCorner = bref.greenCorner;
		redCorner = bref.redCorner;
	}

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
void switchTurn()
{
	if(turn==1)
		turn= 2;

	else
		turn= 1;

}

vector<Point> getRedCorner()
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
	return redCorner;
}
vector<Point> getGreenCorner()
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
	return greenCorner;
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
char remove_piece_at(Point p)
{
	char p1=board[p.x][p.y];
	board[p.x][p.y]='*';
	return p1;
}
//Move a piece from one position to another on the data board
void move_piece(Point start_pos,Point end_pos){

	char player = remove_piece_at(start_pos);
    place_piece(player, end_pos);
}
void place_piece(char player,Point pt) 
{
	board[pt.x][pt.y]=player;
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
		bool to_explore;
		double node_value;
		Board board;
		int move;
		vector<Point> children;

		Node(int p, Board b, int nd): player(p), board(b), node_depth(nd) {}

};
class Moves
{
public:
	Point source;
	Point destination;
	Moves(Point s, Point d): source(s), destination(d) {}
	Moves() {}
};
class Node_Action
{
public:
	Node node;
	Moves m;
	Node_Action(Node n, Moves m): node(n), m(m) {}
};


class Player
{
public:
	vector<Point> previous_spots;
	vector<Point> moves;
	//long int start=0;
	//long int end=0;
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	double run_time;
	Player(int t):run_time(t){}

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
			if(((x+row_offset)>=16) or ((y+col_offset)>=16))
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

                    if (((row_jump_offset) >= 16) or ((col_jump_offset) >= 16))
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

						for(auto ele:jumps)
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

	if(x>=16 or y>=16)
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
			if(((x+row_offset)>=16) or ((y+col_offset)>= 16))
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
					green+=-100;

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
					red+=-100;

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

Node_Action max_value(double alpha, double beta, Node node)
{
	end = high_resolution_clock::now(); 
	Board b=node.board;
	vector<bool> winCheck=b.detectWin();
	vector<Point> player_positions;
	Moves best_move;

	chrono::duration<double, std::milli> fp_ms = end - start;
	if(winCheck[0]==true or winCheck[1]==true or node.node_depth<=0 or fp_ms.count()>run_time*1000)
	{
		node.node_value=eval_function(node);
		return Node_Action(node,best_move);

	}
	int next_player = node.player, player = node.player;
	if(node.player == 1)
        player_positions = b.getGreenPosition();
    else if(player == 2)
        player_positions = b.getRedPosition();

    double value=DBL_MIN;
    Node return_node = Node(player, b, node.node_depth - 1);

    for(auto p:player_positions)
    {
    	vector<Point> legal_moves=step_search(b,Point(p.x,p.y));
    	if(legal_moves.size()==0)
    		continue;

    	for(auto legal_move:legal_moves)
    	{
    		end = high_resolution_clock::now(); 
    		
    		std::chrono::duration<double, std::milli> fp_ms = end - start;
    		if(fp_ms.count()>run_time*1000)
    		{
    			return Node_Action(node,best_move);
    		}
    		Board board_copy=b;
    		board_copy.move_piece(legal_move,p);
    		Node next_node = Node(player, board_copy, node.node_depth - 1);
    		Node_Action node_action = min_value( alpha, beta, next_node);
    		Node child = node_action.node;
    		if(value<child.node_value)
    			best_move = Moves(p,legal_move);

    		value=max(value,child.node_value);
    		return_node=next_node;
    		if (value > beta)
    		{
    			return_node.node_value = beta;
    			return Node_Action(return_node, Moves());
    		}
    		beta = min(beta, value);


    	}

    }
    return_node.node_value = value;
    return Node_Action(return_node, best_move);
}
Node_Action min_value(double alpha, double beta, Node n)
{
		end = high_resolution_clock::now(); 
    	Board b = n.board;
    	double value;
    	vector<bool> winCheck = b.detectWin();
    	vector<Point> player_positions;
    	Moves best_move;
    	chrono::duration<double, std::milli> fp_ms = end - start;
    	if (winCheck[0] == true || winCheck[1] == true || n.node_depth<=0 || fp_ms.count()>run_time*1000) /////////////////////////////////
    	{
    		double eval = eval_function(n);
    		n.node_value = eval;
    		return Node_Action(n,best_move);
    	}
    	int next_player = n.player, player = n.player;
    	if(player == 1)
    		player_positions = b.getGreenPosition();
    	
    	else 
    		player_positions = b.getRedPosition();
    	

    	Node return_node = Node(player, b, n.node_depth - 1);
    	value = DBL_MAX;
    	
    	for(auto p:player_positions)
    	{
    		vector<Point> legal_moves = step_search(b,Point(p.x,p.y));
    		if(legal_moves.size() == 0)
    			continue;
    		for(auto legal_move:legal_moves)
    		{
    			end = high_resolution_clock::now(); 
    		
    			std::chrono::duration<double, std::milli> fp_ms = end - start;
	    		if(fp_ms.count()>run_time*1000)
	    		{
	    			return Node_Action(n,best_move);
	    		}
    			Board b_copy = b;
    			b_copy.move_piece(p,legal_move);
    			Node next_node = Node(player, b_copy, n.node_depth - 1);
    			Node_Action bs = max_value(alpha, beta, next_node);
    			Node child = bs.node;

    			
    			b_copy.move_piece(legal_move,p);
    			
    			if (value > child.node_value)
    			{
    				best_move = Moves(p,legal_move);
    			}
    			
    			value = min(value, child.node_value);
    			return_node = next_node;
    			
    			if (value < alpha)
    			{
    				return_node.node_value = value;
    				return Node_Action(return_node, Moves());
    			}
    			alpha = max(alpha, value);

    		}
    	}
    	return_node.node_value = value;
    	return Node_Action(return_node, best_move);
    }
Node_Action alphaBetaMinimax(Node node)
{
	start = high_resolution_clock::now(); 
	Node_Action m =max_value(DBL_MIN, DBL_MAX, node);
	Board data_board=node.board;
	Node max_node=m.node;
	Moves move=m.m;
	Point source=move.source;
	Point destination=move.destination;
	data_board.move_piece(source, destination);
	data_board.switchTurn();
	return m;
}

void clear_moves(){
	moves.clear();
}



};






int main()
{
	string game_type, my_color;
	
	
	double alpha = DBL_MIN, beta = DBL_MAX;
	float run_time;

	ifstream fin;
    fin.open("input.txt");

    fin>>game_type>>my_color>>run_time;
    
    Board board;

    for (int i = 0; i < 16; i++) 
        for (int j = 0; j < 16; j++)
            fin>> board.board[i][j];


    for(int i=0;i<16;i++)
    	for(int j=0;j<16;j++)
    		cout<<board.board[i][j];

    //if(game_type=="SINGLE")

    //else if(game_type=="GAME")


return 0;
}