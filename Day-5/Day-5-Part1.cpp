#include "Day-5-Isaac.hpp"

int main(){
    std::map<std::pair<long long, long long>, long long> newMap; 

    std::string line;
    std::ifstream input("Day-5-Input.txt");

    std::vector<long long> valuesToLookup;
    std::getline(input, line); 
    std::string substr = line.substr(line.find(":") + 1, line.find(":") + line.length()) ;
    std::stringstream sl(substr); 
    long long startValues;
    long long rangeValues; 
    while(sl >> startValues){
        ///std::cout << startValues << " : " << rangeValues <<  std::endl;

        valuesToLookup.push_back(startValues); 
    }

    while(std::getline(input, line)){
        if(line.find("map") != std::string::npos){
           newMap.clear(); 
        }
        else if(std::isdigit(static_cast<char>(line[0]))){
            std::stringstream ss(line); 
            long long dest_range_start; 
            long long source_range_start; 
            long long range_length; 
            ss >> dest_range_start >> source_range_start >> range_length; 
            newMap[std::make_pair(source_range_start, source_range_start + range_length)] = dest_range_start - source_range_start; 
        }
        else if(line.empty()){ 
            if(!newMap.empty()){ 
                for(int i = 0; i < valuesToLookup.size(); i++ ){ 
                    long long currentValue = valuesToLookup[i]; 
                    for (auto pair : newMap){ 
                        long long minVal = pair.first.first; 
                        long long maxVal = pair.first.second; 
                        if((minVal < currentValue) && (currentValue < maxVal)){ 
                            valuesToLookup[i] = currentValue + pair.second;
                        }
                    } 
                }
            }
        }
    }
    std::cout <<  *std::min_element(valuesToLookup.begin(), valuesToLookup.end()) << std::endl; 
} 