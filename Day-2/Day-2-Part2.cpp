#include "Day-2-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-2-Input.txt");
    int sum = 0; 

    while(std::getline(input, line)){
        std::map<std::string, int> maxValues = {{"red", 0}, {"green", 0}, {"blue", 0}}; 

        // We need to split our inputs by game number and the rest of the data 
        int colonPos = line.find(":"); 

        // Get the rest of the data 
        std::string iterateString = line.substr(colonPos+1, line.size() - colonPos);

        // Get rid of the ; dont need them 
        std::replace(iterateString.begin(), iterateString.end(), ';', ',');

        // Now need to iterate through the string and find min and max values 
        std::stringstream strStream(iterateString);
        std::string tmp; 

        while(std::getline(strStream, tmp, ',')){
            std::stringstream dataStream(tmp);
            int number; 
            std::string color; 
            dataStream >> number >> color; 
            if(number > maxValues[color]){
                maxValues[color] = number; 
            }
        }
        int power = 1; 
        // int product = std::accumulate(maxValues.begin(), maxValues.end(), 1,
        //    [](int acc, const std::pair<std::string, int>& p) { return acc * p.second; });
        for (auto val : maxValues) { 
            power *= val.second; 
        }
        sum += power; 
    };
    std::cout<< sum<< std::endl; 
};