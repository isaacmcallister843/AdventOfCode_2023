#include "Day-6-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-6-Input.txt");
    std::vector<std::vector<int>> puzzleData; 
    std::vector<int> newLine; 

    while(std::getline(input, line)){
        std::string Input = line.substr(line.find(":") + 1, line.find(":") + 1 + line.length()); 
        std::stringstream ss(Input); 
        int output; 
        while(ss >> output){
            newLine.push_back(output);             
        }
        puzzleData.push_back(newLine);
        newLine.clear(); 
    }

    int outValue = 1; 

    for(int i = 0; i < puzzleData[0].size(); i++ ){ 
        int time = puzzleData[0][i]; 
        int distance = puzzleData[1][i]; 
        int numVictories = 0; 

        for(int pushTime = 0; pushTime <= time; pushTime++){ 
            int runTime = time - pushTime; 
            int simDistance = pushTime * runTime ;

            if(simDistance > distance){ 
                numVictories++; 
            }
        }
        outValue *= numVictories; 
    }
} 