#include "Day-2-Isaac.hpp"

int main(){
    std::string line;
    std::ifstream input("Day-2-Input.txt");
    std::map<std::string, int> maxValues = {{"red", 12}, {"green", 13}, {"blue", 14}}; 
    int sum = 0; 

    while(std::getline(input, line)){
        bool addID = true; 

        // We need to split our inputs by game number and the rest of the data 
        int spacePos = line.find(" "); 
        int colonPos = line.find(":"); 

        // Get the game number 
        int numberGame = std::stoi(line.substr(spacePos, colonPos-spacePos)); 

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
                addID = false; 
                break;
            }
        }

        if(addID){
            sum+=numberGame; 
        }
    };
    std::cout<<sum<<std::endl; 
};