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

    // want to index the row and column value with the number its 
    // associated with 
    std::map <std::pair<int, int>, int> newMap; 
    std::list<std::pair<int, int>> indexForNumber;
    std::string currentNumber = "";  

    // Organize all out data 
    // Col iterator 
    for (int i=0; i < allVals.size(); i++){
        // Row iterator
        for(int j = 0; j < allVals[0].size(); j++){
            char cVal = allVals[i][j]; 
            if(isdigit(cVal)){
                currentNumber += cVal; 
                std::pair<int, int> pairLocation(j, i); 
                indexForNumber.push_back(pairLocation);
            }
            else if(currentNumber != ""){
                int tempInt = std::stoi(currentNumber); 
                for (auto val : indexForNumber){
                    newMap[val] = tempInt; 
                }
                indexForNumber.clear(); 
                currentNumber = ""; 
            }
        }
        if(currentNumber != ""){
            int tempInt = std::stoi(currentNumber); 
            for (auto val : indexForNumber){
                newMap[val] = tempInt; 
            }
            indexForNumber.clear(); 
            currentNumber = ""; 
        }
    }

    std::vector<int> dx = {-1, 0, 1}; 
    std::vector<int> dy = dx;
    std::vector<int> validNumbers; 

    // Go over everything again 
    for (int i=0; i < allVals.size(); i++){
        // Row iterator 
        for(int j = 0; j < allVals[0].size(); j++){
            char cVal = allVals[i][j]; 
            // If we have a * 
            if(cVal == '*'){
                // Perform check 
                for (int _dx : dx){
                    for (int _dy : dy){ 
                        int pos_x = j + _dx; 
                        int pos_y = i + _dy; 
                        if ((pos_x >= 0 & pos_x < allVals[0].size()) & (pos_y >= 0 & pos_y < allVals.size())){ 
                           char cCheck = allVals[pos_y][pos_x];
                           if(isdigit(cCheck)){ 
                            std::pair<int, int> digitLocation(pos_x, pos_y); 
                            int _val = newMap[digitLocation];
                            // Check if already there 
                            auto it = std::find(validNumbers.begin(), validNumbers.end(), _val);
                            if(it == validNumbers.end()){ 
                                validNumbers.push_back(_val); 
                            }
                           }
                        }
                    }
                }

                if(validNumbers.size() == 2){ 
                    sum += validNumbers[0] * validNumbers[1]; 
                }
                validNumbers.clear(); 
            }
        }
    }

    // x, y coordinates 
    std::pair <int, int> testPair(6,2); 
    std::cout<< sum << std::endl; 
};