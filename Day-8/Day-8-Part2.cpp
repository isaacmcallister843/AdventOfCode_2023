#include "Day-8-Isaac.hpp"

// Common alogrithm stolen from online 
long long gcd(long long a, long long b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b; // Rearranged to avoid overflow
}

long long findLCM(std::vector<std::pair<std::string, long long>> numbers) {
    long long result = numbers.begin()->second;
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = lcm(result, numbers[i].second);
    }
    return result;
}

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
    std::string directions = repeatString(line, 100);
    std::getline(input, line); 

    // Now ready to iterate 
    std::map<std::string, std::pair<std::string, std::string>> puzzleMap; 

    // Curent value, num turns to get their 
    std::vector<std::pair<std::string, long long>> inputPaths; 
    
    while(std::getline(input, line)){
        std::string key = line.substr(0, line.find("=")-1); 
        std::string val1 = line.substr(line.find("(")+1, line.find(",")-line.find("(")-1);
        std::string val2 = line.substr(line.find(",")+2, line.find(")") - line.find(",") -2);
        puzzleMap[key] = std::make_pair(val1, val2); 
        if(key[2] == 'A'){ 
            inputPaths.push_back(std::make_pair(key, 0)); 
        }
    }

    std::pair<std::string, std::string> possiblePath; 

    for (auto dir : directions){ 
        // Check if we can exit 
        bool exit = true; 
        for(int d = 0; d< inputPaths.size(); ++d){
            possiblePath = puzzleMap[inputPaths[d].first];
            if(inputPaths[d].first[2] != 'Z'){
                inputPaths[d].second ++; 
                if(dir == 'R'){
                    inputPaths[d].first = possiblePath.second; 
                }
                else{ 
                    inputPaths[d].first = possiblePath.first; 
                }
                exit = false; 
            }
        }
        if(exit){
            break; 
        }
    }

    for (int m = 0; m < inputPaths.size(); m ++){
        std::cout << inputPaths[m].first << " : " << inputPaths[m].second << std::endl; 
    }

    std::cout <<findLCM(inputPaths) <<std::endl;   
}