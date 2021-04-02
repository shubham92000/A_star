#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<locale.h>

enum class State {kEmpty , kObstacle};

std::vector<State> ParseLine(std::string line){
    std::vector<State> output;

    std::istringstream ss(line);
    for(int i;ss>>i;){
        if(i==1){
            output.push_back(State::kObstacle);
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
        case State::kObstacle: return "1    ";
        default : return "0    ";
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

int main(){

    std::string file_name = "1.board.txt";
    std::vector<std::vector<State>> board(ReadBoardFile(file_name));
    // board = ReadBoardFile(file_name);
    PrintBoard(board);

    return 0;
}