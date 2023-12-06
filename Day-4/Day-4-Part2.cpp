#include "Day-4-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-4-Input.txt");

    int currentCard = 1; 
    int numberCards[1000];  
    std::fill(numberCards, numberCards+1000, 1); 
    
    while(std::getline(input, line)){
        int numMatches = 0; 
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
                numMatches++; 
            }
        }
        
        for(int i = currentCard+1; i <= currentCard + numMatches; i++){ 
            numberCards[i] += 1 * numberCards[currentCard]; 
        }
        currentCard++; 
    }

    int sum = 0; 
    for(int j = 1; j <= 198; j++){
        std::cout << j << " : " << numberCards[j] << std::endl; 
        sum += numberCards[j];
    }
    std::cout<<sum<<std::endl; 
};