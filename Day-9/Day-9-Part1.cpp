#include "Day-9-Isaac.hpp"

// Way better solution : https://github.com/lmitlaender/Advent_of_Code_2023/blob/main/Cpp_Advent_of_code_23/2023/day9.cpp 

int main(){
    std::string line;
    std::ifstream input("Day-9-Input.txt"); 

    int sum = 0; 
    
    while(std::getline(input, line)){

        std::vector<std::vector<int>> newVec; 
        std::vector<int> firstline = std::vector<int>(line.length()+1, INT16_MAX);
        std::stringstream ss(line); 
        int out = 0;
        int iter = 0;
        while(ss >> out){ 
            firstline[iter] = out; 
            iter++;    
        }
        newVec.push_back(firstline); 
        firstline = std::vector<int>(firstline.size(), INT16_MAX); 

        int currentRow = 0; 
        bool exit = false; 
        int i; 
        while(!exit){ 
            i = 1; 
            exit = true; 
            while((newVec[currentRow][i] != INT16_MAX) || newVec[currentRow][i] < newVec[currentRow].size()){
                int dif = newVec[currentRow][i] - newVec[currentRow][i-1]; 
                firstline[i-1] = dif; 
                i++;
                if(dif != 0){
                    exit = false; 
                }
            }
            newVec.push_back(firstline);
            firstline = std::vector<int>(firstline.size(), INT16_MAX); 
            currentRow ++;             
        }
        currentRow = newVec.size()-1; 
        newVec[currentRow][i-1] = 0;
        currentRow--;

        int predictedValue;

        while(currentRow >= 0){ 
            int value = 0;
            while(newVec[currentRow][value] != INT16_MAX){ 
                value++; 
            }
            predictedValue = newVec[currentRow][value-1] + newVec[currentRow+1][value-1];
            newVec[currentRow][value]= predictedValue;
            currentRow--; 
        }
        sum += predictedValue;

    }
    std::cout<< sum << std::endl;
}