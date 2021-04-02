#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

std::vector<int> ParseLine(std::string line){
    std::vector<int> output;

    std::istringstream ss(line);
    for(int i;ss>>i;){
        output.push_back(i);
        if(ss.peek()==','){
            ss.ignore();
        }
    }

    return output;
}

std::vector<std::vector<int>> ReadBoardFile(std::string file_name){
    std::vector<std::vector<int>> output;
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

void PrintBoard(std::vector<std::vector<int>> const &board){
    for(std::vector<int> row:board){
        for(int& col:row){
            std::cout<<col<<"  ";
        }
        std::cout<<"\n";
    }

    return ;
}

int main(){

    std::string file_name = "1.board.txt";
    std::vector<std::vector<int>> board(ReadBoardFile(file_name));
    // board = ReadBoardFile(file_name);
    PrintBoard(board);

    return 0;
}