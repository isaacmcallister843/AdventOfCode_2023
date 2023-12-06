#include "Day-6-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-6-Input.txt");
    std::vector<long long> puzzleData; 

    while(std::getline(input, line)){
        std::string Input = line.substr(line.find(":") + 1, line.find(":") + 1 + line.length()); 
        std::stringstream ss(Input); 
        std::string inTake = ""; 
        char output; 
        while(ss >> output){
            inTake = inTake +  output;             
        }
        puzzleData.push_back(std::stoll(inTake));
    }
    std::cout << puzzleData[0] << std::endl ;
    std::cout << puzzleData[1] << std::endl ;


    int outValue = 1; 
    long long time = puzzleData[0]; 
    long long distance = puzzleData[1]; 
    int numVictories = 0; 

    for(int pushTime = 0; pushTime <= time; pushTime++){ 
        long long runTime = time - pushTime; 
        long long simDistance = pushTime * runTime ;

        if(simDistance > distance){ 
            numVictories++; 
        }
    
    }

    std::cout << numVictories << std::endl; 

} 