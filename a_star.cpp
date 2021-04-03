#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<utility>
#include<string>

using std::string;

string empty = "0    ";
string obstacle = "\U000026F0";
string path = "\U0001F3C3"; 
string start = "\U0001F3E0";
string end = "\U0001F3F3";
enum class State {kEmpty , kObstacle , kClosed , kPath , kStart , kEnd};

std::vector<State> ParseLine(std::string line){
    std::vector<State> output;

    std::istringstream ss(line);
    for(int i;ss>>i;){
        if(i==1){
            output.push_back(State::kObstacle);
        }else if(i==2){
            output.push_back(State::kClosed);
        }else if(i==3){
            output.push_back(State::kPath);
        }else if(i==4){
            output.push_back(State::kStart);
        }else if(i==5){
            output.push_back(State::kEnd);
        }else{
            output.push_back(State::kEmpty);
        }
        
        if(ss.peek()==','){
            ss.ignore();
        }
    }

    return output;
}

std::vector<std::vector<State>> ReadBoardFile(std::string file_name){
    std::vector<std::vector<State>> output;
    std::ifstream filereader;
    std::string line;
    filereader.open(file_name);
    
    if(filereader.is_open()){
        while(std::getline(filereader,line))
        {
            output.push_back(ParseLine(line));
        }
        filereader.close();
    }else{
        std::cout<<"file cannot be opened";
    }

    return output;
}

std::string CellString(State cell){
    switch(cell){
        case State::kObstacle: return obstacle+"\t";
        // case State::kClosed: return ;
        case State::kPath: return path+"\t";
        case State::kStart: return start+"\t";
        case State::kEnd: return end+"\t";
        default : return empty+"\t";
    }
}

void PrintBoard(std::vector<std::vector<State>> const &board){
    for(std::vector<State> row:board){
        for(State& col:row){
            std::cout<<CellString(col)<<"  ";
        }
        std::cout<<"\n";
    }

    return ;
}

void PrintBoardpair(std::vector<std::vector<std::pair<State,int>>> &grid){
    for(auto row:grid){
        for(auto col:row){
            std::cout<<(col.second)<<"    ";
        }
        std::cout<<"\n";
    }

    return;

}

bool compare(std::vector<int> v1,std::vector<int> v2){
    int f1 = v1[2]+v1[3] ;      //f=g+h;
    int f2 = v2[2]+v2[3] ;
    if(f1<f2){
        return true;
    }else{
        return false;
    }

}

std::vector<int> CellSort(std::vector<std::vector<int>> & open_nodes){
    std::sort(open_nodes.begin(),open_nodes.end(),compare);
    std::vector<int> smallest = open_nodes[0];
    open_nodes.erase(open_nodes.begin());                           //q.pop
    return smallest;
}

bool checkValidCell(int x,int y,std::vector<std::vector<std::pair<State,int>>> & grid ,std::vector<std::vector<State>> board){
    bool check = (x>=0 && x<board.size() && y>=0 && y<board[0].size()  && board[x][y]!=State::kObstacle && grid[x][y].first!=State::kClosed);
    return check;
}

int Heuristic(int x1,int y1,int x2,int y2){
    int dis = abs(x2-x1) + abs(y2-y1);
    return dis;
}

void AddToOpen(int x,int y,int g,int h,std::vector<std::vector<int>> &open_nodes,std::vector<std::vector<std::pair<State,int>>> &grid){
    std::vector<int> node(4);
    node[0] = x;
    node[1] = y;
    node[2] = g;
    node[3] = h;
    
    open_nodes.push_back(node);              //add to queue
    
    grid[x][y].first = State::kClosed;       //visited
    grid[x][y].second = g;
    
    return ;
}

void ExpandNeighbours(std::vector<int> curr_node , std::vector<std::vector<State>> board , std::vector<std::vector<std::pair<State,int>>> & grid , std::vector<std::vector<int>> & open_nodes){
    // left x-1,y   //right x+1,y   //top x,y-1    //bottom x,y+1
    int curr_x = curr_node[0] ;
    int curr_y = curr_node[1] ;
    int curr_g = curr_node[2] ;
    int curr_h = curr_node[3] ;
    if(checkValidCell(curr_x-1,curr_y,grid,board)){
        int h = Heuristic(curr_x-1,curr_y,board.size()-1,board[0].size()-1);
        AddToOpen(curr_x-1,curr_y,curr_g+1,h,open_nodes,grid);
    }
    if(checkValidCell(curr_x+1,curr_y,grid,board)){
        int h = Heuristic(curr_x+1,curr_y,board.size()-1,board[0].size()-1);
        AddToOpen(curr_x+1,curr_y,curr_g+1,h,open_nodes,grid);
    }
    if(checkValidCell(curr_x,curr_y-1,grid,board)){
        int h = Heuristic(curr_x,curr_y-1,board.size()-1,board[0].size()-1);
        AddToOpen(curr_x,curr_y-1,curr_g+1,h,open_nodes,grid);
    }
    if(checkValidCell(curr_x,curr_y+1,grid,board)){
        int h = Heuristic(curr_x,curr_y+1,board.size()-1,board[0].size()-1);
        AddToOpen(curr_x,curr_y+1,curr_g+1,h,open_nodes,grid);
    }

    return;
} 

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> board , int start[2] ,int end[2]){
    std::vector<std::vector<State>>path(board.size(),std::vector<State>(board[0].size())); 
    std::vector<std::vector<int>>open_nodes;                       //queue
    std::vector<std::vector<std::pair<State,int>>>grid(board.size(),std::vector<std::pair<State,int>>(board[0].size()));             //visited array
    
    int initial_cost = 0; //g initial
    int heuristic_value = Heuristic(start[0],start[1],end[0],end[1]);   //h initial
    AddToOpen(start[0],start[1],initial_cost,heuristic_value,open_nodes,grid);  // add first node to queue

    while(!open_nodes.empty()){
        
        std::vector<int> curr_node = CellSort(open_nodes);            //q.front
        

        int x,y,g,h;
        x = curr_node[0];
        y = curr_node[1];
        g = curr_node[2];
        h = curr_node[3];
                
        if(x==end[0] && y==end[1]){
            // grid[x][y] = State::finish;
            std::cout<<"steps needed: "<<grid[x][y].second<<"\n";
            std::cout<<"found a path\n\n";
            path[x][y] = State::kPath;
            return path;
        }

        path[x][y] = State::kPath;
        ExpandNeighbours(curr_node,board,grid,open_nodes);
    }

    std::cout<<"no path found\n";
    return path;
}



int main(){

    int start[2] = {0,0};
    int end[2] = {4,5};

    std::string file_name = "1.board.txt";
    std::vector<std::vector<State>> board;
    board = ReadBoardFile(file_name);
    std::cout<<"board\n";
    PrintBoard(board);

    std::cout<<"\n";

    std::vector<std::vector<State>> path;
    path = Search(board,start,end);

    path[start[0]][start[1]] = State::kStart;
    path[end[0]][end[1]] = State::kEnd;
    PrintBoard(path);
    
    return 0;
}
