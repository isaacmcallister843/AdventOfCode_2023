#include "Day-5-Isaac.hpp"

int main(){

    std::string line;
    std::ifstream input("Day-5-Input.txt");

    // This vector will hold the min and max values, and the change that occurs 
    std::vector<std::tuple<long long, long long>> seedRanges;
    

    // New structure stores min value, max value, for input and change to be added
    std::vector<std::pair<std::string,std::vector< std::tuple<long long, long long, long long>>>> allMaps;
    std::vector<std::tuple<long long, long long, long long>> newMap; 

    std::getline(input, line); 
    std::string substr = line.substr(line.find(":") + 1, line.find(":") + line.length()) ;
    std::stringstream sl(substr); 
    long long startValues;
    long long rangeValues; 

    while(sl >> startValues >> rangeValues){
        // std::cout << startValues << " : " << startValues + rangeValues - 1<<  std::endl;
        seedRanges.push_back(std::make_tuple(startValues, startValues + rangeValues - 1)); 
    }
    std::string nameTemp = ""; 

    while(std::getline(input, line)){
        

        if(line.find("map") != std::string::npos){            
            if(newMap.size() != 0){ 
                allMaps.push_back(std::make_pair(nameTemp, newMap));
            }
            nameTemp = line;
            newMap.clear(); 
        }

        else if(std::isdigit(static_cast<char>(line[0]))){
            std::stringstream ss(line); 
            long long dest_range_start; 
            long long source_range_start; 
            long long range_length; 
            ss >> dest_range_start >> source_range_start >> range_length; 
            newMap.push_back(std::make_tuple(dest_range_start, dest_range_start + range_length - 1, source_range_start - dest_range_start));
        }
    }
    
    allMaps.push_back(std::make_pair(nameTemp, newMap));
    
    for(auto vals: allMaps){ 
        std::string name = vals.first; 
        auto map = vals.second;
        // std::cout<< name << std::endl; 
        for(auto t : map){ 
            // std::cout << "      " << std::get<0>(t) << " : " << std::get<1>(t) << " : " << std::get<2>(t) << std::endl; 
        }
    }

    long long startLocation = 0; 

    while (startLocation < 864495840000) {
        // std::cout << startLocation << std::endl; 
        long long tempLocation = startLocation; 

        for(int i = allMaps.size() - 1; i >= 0; --i){
            //std::cout << "Starting Location: "  <<tempLocation<< " : " << allMaps[i].first << std::endl;  

            auto currentMaps = allMaps[i].second; 

            long long valForwardAdjustment = 0; 
            bool foundMap = false; 

            for(auto t : currentMaps){ 
                long long minVal = std::get<0>(t); 
                long long maxVal = std::get<1>(t); 
                long long valForwardAdjustment_ = std::get<2>(t); 
                
                if(minVal <= tempLocation && tempLocation <= maxVal){ 
                    // std::cout << "      MAP:  "<< "  :  " << minVal << " : " << maxVal << " : Adjustment: " << valForwardAdjustment_ << std::endl; 
                    valForwardAdjustment = valForwardAdjustment_;
                    foundMap = true; 
                    break; 
                }
            }
            if(!foundMap){
                // std::cout<<"No Adjustment Needed" << std::endl; 
            }
            tempLocation += valForwardAdjustment;
            // std::cout << "Final Temp: " << tempLocation << std::endl; 
            // std::cout << "-----" << std::endl; 
            
        }

        bool done = false; 

        for(auto t : seedRanges){
            
            long long minVal = std::get<0>(t); 
            long long maxVal = std::get<1>(t); 

            if(tempLocation > minVal && tempLocation < maxVal){
                std::cout<<"----------" << std::endl; 
                std::cout << startLocation << std::endl; 
                std::cout << tempLocation << std::endl; 
                done= true; 
                break;

            }
        }
        if (done){
            break; 
        }

        startLocation++; 
    }
} 