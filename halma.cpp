#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono; 
class Point {
public:
	int x;
	int y;
	Point():x(0),y(0) {}
	Point(int x, int y):x(x),y(y) {}
};
vector<Point> greenCorner;
vector<Point> redCorner;
vector<Point> previous_spots;
vector<Point> moves;
//black-2 white-1
class State {
public:
	vector<vector<char> > board;
	
	int row=board.size(), column= board[0].size();
	

};
class Node{
		// self.board = board
  //       self.type = type
  //       self.player = player
  //       self.to_explore = True
  //       self.node_value = 0
  //       self.node_depth = node_depth
  //       self.move = 0

  //       self.children = []
	public:
		int player;
		int node_depth;
		int node_value;
		vector<Point> children;
};

int distance(Point p1, Point p2)
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.x-p2.y)*(p1.x-p2.y);
}

int switchTurn(int turn)
{
	if(turn==1)
		turn=2;

	else
		turn=1;

	return turn;
}
void getRedCorner()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8-i;j++)
			redCorner.push_back(Point(i,j));
		
	}
}
void getGreenCorner()
{
	// for i in range(0, size):
 //            cur_row = (size * 2) - (size - i)
 //            start_col = size * 2 - 1 - i
 //            end_col = size * 2
 //            for col in range(start_col, end_col):
 //                self.greenCorner.append((cur_row, col))
	int cur_row,start_col,end_col=32;

    for(int i=0;i<16;i++)
    {
    	cur_row=32-(16-i);
    	start_col= 32-1-i;
    	
    	for(int j=start_col;j<end_col;j++)
    		greenCorner.push_back({cur_row,j});
    }
}
char removePieceAt(Point p,State state)
{
	char p1=state.board[p.x][p.y];
	state.board[p.x][p.y]='*';
	return p1;
}
void placePieceAt(Point p,State state)
{

}
void movePieceTo(Point p, State state)
{

}
char getPieceAt(Point p,State state)
{
	return state.board[p.x][p.y];
}
vector<Point> getGreenPosition(State state)
{
	vector<Point> green_pos_list;

    for(int i=0;i<16;i++)
    {
    	for(int j=0;j<16;j++)
    	{
    		if(state.board[i][j]=='G')
    			green_pos_list.push_back(Point(i,j));
    	}
    }
    return green_pos_list;
}
vector<Point> getRedPosition(State state)
{
	vector<Point> red_pos_list;
	for(int i=0;i<16;i++)
    {
    	for(int j=0;j<16;j++)
    	{
    		if(state.board[i][j]=='R')
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
bool find_PrevCorner(Point p)
{
	for(auto point:previous_spots)
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
void clear_moves()
	moves.clear();
	
void printBoard(State state)
{
	for(int i=0;i<state.board.size();i++)
	{
		for(int j=0;j<state.board[0].size();j++)
			cout<<state.board[i][j];
	}
}
vector<bool> detectWin(State state)
{
	vector<bool> winCheckArray(2);
	bool redWin=false, greenWin=false;
	int x,y;

	//checking if all tiles in green corner are filled with red tiles
	for(auto coord: greenCorner)
	{
		x=coord.x;
		y=coord.y;
		if(state.board[x][y]=='*' || state.board[x][y]=='R'){
			redWin=false;
			break;
		}

		else if(state.board[x][y]=='G')
			redWin=true;

	}
	for(auto coord: redCorner)
	{
		x=coord.x;
		y=coord.y;
		if(state.board[x][y]=='*' || state.board[x][y]=='G'){
			greenWin=false;
			break;
		}

		else if(state.board[x][y]=='R')
			greenWin=true;

	}
	winCheckArray[0]=redWin;
	winCheckArray[1]=greenWin;
	return winCheckArray;


}
int eval_function(State state, Node node)
{

	int red,green=0,value=0;
	vector<int> distanceList;
	vector<bool> winCheck(2);
	winCheck=detectWin(state);

	for(int i=0;i<state.board.size();i++)
	{
		for(int j=0;j<state.board[0].size();j++)
		{
			char piece=state.board[i][j];
			Point p(i,j);
			if(piece=='G')
			{
				for(auto point: redCorner)
				{
					if(state.board[point.x][point.y]!='G'){
						distanceList.push_back(distance(p,point));

					}
				}
				if(distanceList.empty())
					green=-100;

				else
					green=*max_element(distanceList.begin(), distanceList.end());


			}
			else if(piece=='R')
			{
				for(auto point: greenCorner)
				{
					if(state.board[point.x][point.y]!='R'){
						distanceList.push_back(distance(p,point));

					}
				}
				if(distanceList.empty())
					red=-100;

				else
					red=*max_element(distanceList.begin(), distanceList.end());


			}
			


		}
	}
	if(node.player==1)
		value = red/green;

	else
        value = green/red;

    if (winCheck[0])
        value = INT_MAX;

    else if(winCheck[1])
        value = INT_MAX;

    return value;


}
//recursive function to get jump chains for a specific position
vector<Point> jump_search(Point pt,State state)
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
			if(((x+row_offset)>=state.board.size()) or ((y+col_offset)< state.board[0].size()))
				continue;

			//if it is out of bounds
			if((x+row_offset<0) or (y+col_offset<0))
				continue;

			//check if we looking at the same location
			if (((x + row_offset) == x) and ((y + col_offset) == y))
                continue;

            //check if position at offset is filled
            if (state.board[x + row_offset][y + col_offset] != '*')
            {
                   // if it is, check the position past it to see if it is empty.
                   // Do this by doubling the x and y offsets and checking that position
                    row_jump_offset = x + 2*row_offset;
                    col_jump_offset = y + 2*col_offset;

                    if (((row_jump_offset) >= state.board.size()) or ((col_jump_offset) >= state.board[0].size()))
                        continue;

                    if ((row_jump_offset) < 0 or (col_jump_offset) < 0)
                        continue;


                    if (state.board[row_jump_offset][col_jump_offset] == '*' and !find_PrevCorner(Point(row_jump_offset,col_jump_offset )))
                    {
                    	Point p(row_jump_offset,col_jump_offset);
		            	if(state.board[x][y]=='R')
		            	{
		            		
		            		if (!find_redCorner(pt))
		            			if(find_redCorner(p))
		            				continue;


		            	}
		            	if(state.board[x][y]=='G')
		            	{
		            		
		            		if (!find_greenCorner(pt))
		            			if(find_greenCorner(p))
		            				continue;

		            			
		            	}
		            	previous_spots.push_back(pt);
		            	jumps.push_back(p);
		            	vector<Point> st=jump_search(Point(row_jump_offset, col_jump_offset), state);
						for(auto element: st)
							jumps.push_back(element);

                    }

			}

		}
	}
	return jumps;
}

bool compare(Point p1, Point p2)
{
	if((p1.x==p2.x) && (p1.y==p2.y))
		return true;
	return false;
}
//function to check 8-directionally available spaces
vector<Point> step_search(State state, Point pt)
{

	int x=pt.x,y=pt.y;
	vector<int> row_offsets={-1,0,1};
	vector<int> col_offsets={-1,0,1};
	vector<Point> legal_moves;

	if(x>=state.row or y>=state.column)
		return legal_moves;

	if(x<0 or y<0)
		return legal_moves;

	//no piece at that position
	if(state.board[x][y]==0)
		return legal_moves;

	for(auto row_offset: row_offsets)
	{
		for(auto col_offset: col_offsets)
		{
			//out of bounds
			if(((x+row_offset)>=state.row) or ((y+col_offset)< state.column))
				continue;

			//out of bounds
			if((x+row_offset<0) or (y+col_offset<0))
				continue;

			//check if we looking at the same location
			if (((x + row_offset) == x) and ((y + col_offset) == y))
                continue;

            //Check if the position at the offset is filled
            if (state.board[x + row_offset][y + col_offset] == '*')
            {
            	Point p(x + row_offset,y + col_offset);
            	if(state.board[x][y]=='R')
            	{
            		
            		if (!find_redCorner(pt))
            			if(find_redCorner(p))
            				continue;


            	}
            	if(state.board[x][y]=='G')
            	{
            		
            		if (!find_greenCorner(pt))
            			if(find_greenCorner(p))
            				continue;

            			
            	}

            	legal_moves.push_back(Point(x + row_offset, y + col_offset));
            }
            

		}
	}
		vector<Point> st=jump_search(Point(x, y), state);
		for(auto element: st)
			legal_moves.push_back(element);
		return legal_moves;


}
void max_value(State state,int alpha, int beta,Node node)
{
	auto wincheck=detectWin(state);
	// if(winCheck[0]==true or winCheck[1]==true or node.node_depth<=0 or end-start>timeLimit)
	// {
	// 	int eval_score=eval_function(state,node);


	// }
}
int main()
{
	string game_type, my_color;
	
	int play_time;
	int alpha = INT_MIN, beta = INT_MAX;
	float run_time;

	ifstream fin;
    fin.open("input.txt");

    fin>>game_type>>my_color>>play_time;
    State state;

    for (int i = 0; i < 16; i++) 
        for (int j = 0; j < 16; j++)
            fin>> state.board[i][j];




return 0;
}