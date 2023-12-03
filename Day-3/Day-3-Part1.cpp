#include "Day-3-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-3-Input.txt");
    std::vector<std::vector<char>> allVals; 
    int sum = 0; 

    while(std::getline(input, line)){
        std::vector<char> currentRow; 
        for(auto c : line){
            currentRow.push_back(c); 
        }
        allVals.push_back(currentRow); 
    };

    std::string currentNumber = ""; 
    bool addNumber = false; 
    std::vector<int> dx = {-1, 0, 1}; 
    std::vector<int> dy = dx;

    // Column iterator
    for (int i=0; i < allVals.size(); i++){
        // Row iterator 
        for(int j = 0; j < allVals[0].size(); j++){
            char cVal = allVals[i][j]; 
            if(isdigit(cVal)){
                currentNumber += cVal; 
                for (int _dx : dx){
                    for (int _dy : dy){ 
                        int pos_x = j + _dx; 
                        int pos_y = i + _dy; 
                        if ((pos_x >= 0 & pos_x < allVals[0].size()) & (pos_y >= 0 & pos_y < allVals.size())){ 
                            char cCheck = allVals[pos_y][pos_x];
                            if(!isdigit(cCheck) && (cCheck != '.')){
                                addNumber = true; 
                            }
                        }
                    }
                }
            }
            else if(currentNumber != ""){
                // We finished reading the number 
                if (addNumber){
                    sum += std::stoi(currentNumber);
                }
                currentNumber = "";
                addNumber = false;
            }
        }
        if (addNumber){
            sum += std::stoi(currentNumber);
        }
        currentNumber = "";
        addNumber = false;
    }
    std::cout << sum << std::endl; 
};