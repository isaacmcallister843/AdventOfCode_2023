#include "Day-8-Isaac.hpp"

std::string repeatString(std::string inputStr, int numStr){ 
    std::string output = ""; 
    for(int i =0; i< numStr; i++){
        output += inputStr;
    }
    return output; 
}

int main(){
    std::string line;
    std::ifstream input("Day-8-Input.txt");

    std::getline(input, line); 
    std::string directions = repeatString(line, 1000);
    std::getline(input, line); 

    // Now ready to iterate 
    std::map<std::string, std::pair<std::string, std::string>> puzzleMap; 
    
    while(std::getline(input, line)){
        std::string key = line.substr(0, line.find("=")-1); 
        std::string val1 = line.substr(line.find("(")+1, line.find(",")-line.find("(")-1);
        std::string val2 = line.substr(line.find(",")+2, line.find(")") - line.find(",") -2);
        puzzleMap[key] = std::make_pair(val1, val2); 
    }

    std::string lookupVal = puzzleMap.begin()->first; 
    std::pair<std::string, std::string> possiblePath; 
    int numSteps = 0; 

    for (auto dir : directions){ 
        std::cout << lookupVal << std::endl; 
        if(lookupVal == "ZZZ"){
            break;
        }
        possiblePath = puzzleMap[lookupVal]; 
        if(dir == 'R'){
            lookupVal = possiblePath.second; 
        }
        else{ 
            lookupVal = possiblePath.first; 
        }
        numSteps++; 
    }
    std::cout << numSteps <<std::endl;
}