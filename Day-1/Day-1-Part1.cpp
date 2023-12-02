#include "Day-1-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-1-Input.txt");
    int sum = 0; 

    while(std::getline(input, line)){
        char c_1;
        char c_2; 

        for (int i = 0; i < line.length() ; ++i){
            c_1 = line[i]; 
            if(isdigit(c_1)){
                break; 
            }; 
        };

        for (int i = line.length() - 1; i >= 0; --i){
            c_2 = line[i]; 
            if(isdigit(c_2)){
                break; 
            };

        }; 
        sum += std::stoi(std::string() + c_1 + c_2); 
    };

    std::cout<< sum <<std::endl; 
};