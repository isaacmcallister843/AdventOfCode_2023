#include "Day-1-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-1-Input.txt");

    std::map<std::string, std::string> numberMap = { 
        {"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"}, 
        {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"},
        {"eight", "8"}, {"nine", "9"}
    };

    int sum = 0; 

    while(std::getline(input, line)){
        std::string finalString = ""; 

        bool foundNumber_LHS = false;
        char c_1;
        std::vector<std::string> lhsList;

        for (int i = 0; i < line.length() ; ++i){

            c_1 = line[i]; 

            if(isdigit(c_1)){
                finalString += std::string(1, c_1); 
                break; 
            }; 

            if(lhsList.size() != 0){ 
                for (int i = 0; i < lhsList.size(); ++i ){
                    lhsList[i] = lhsList[i] + std::string(1, c_1); 
                    if(numberMap.find(lhsList[i]) != numberMap.end()){
                        foundNumber_LHS = true; 
                        finalString += numberMap[lhsList[i]];
                        break;

                    };
                }; 
            };

            if(foundNumber_LHS){
                break; 
            }

            lhsList.push_back(std::string(1, c_1));
        };
        
        bool foundNumber_RHS = false;
        char c_2;
        std::vector<std::string> rhsList;

        for (int i = line.length() - 1; i >= 0; --i){
            c_2 = line[i]; 
            

            if(isdigit(c_2)){
                finalString += std::string(1, c_2); 
                break; 
            };

            if(rhsList.size() != 0){ 
                for (int i = 0; i < rhsList.size(); ++i ){
                    rhsList[i] = std::string(1, c_2) + rhsList[i]; 
                    if(numberMap.find(rhsList[i]) != numberMap.end()){
                        foundNumber_RHS = true; 
                        finalString += numberMap[rhsList[i]];
                        break; 
                    };
                }; 
            };
        

            if(foundNumber_RHS){
                break; 
            };

            rhsList.push_back(std::string(1, c_2));

        }; 
        sum += std::stoi(finalString); 
    }; 

    std::cout<<sum<<std::endl; 
};