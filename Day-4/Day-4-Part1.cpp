#include "Day-4-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-4-Input.txt");

    int sum = 0; 
    
    while(std::getline(input, line)){
        int currentMatch = -1; 
        int semiPos = line.find(":") + 1;
        int middPos = line.find("|");

        std::string leftStr = line.substr(semiPos, middPos - semiPos);
        std::string rightStr = line.substr(middPos + 1, line.length());
        std::stringstream ssl(leftStr);

        int number;

        std::set<int> winningNumbers; 
        while (ssl >> number){ 
            winningNumbers.insert(number); 
        }

        std::stringstream ssr(rightStr);
        while(ssr >> number){
            if(winningNumbers.count(number) != 0){
                currentMatch++; 
            }
        }

        if(currentMatch >= 0){
            sum += pow(2, currentMatch);
        }
    }
    
    std::cout<<sum<<std::endl; 
};