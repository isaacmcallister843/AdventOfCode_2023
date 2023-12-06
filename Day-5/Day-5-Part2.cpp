#include "Day-5-Isaac.hpp"

int main(){

    std::string line;
    std::ifstream input("Day-5-Input.txt");

    // This vector will hold the min and max values, and the change that occurs 
    std::vector<std::tuple<long long, long long, long long>> seedRanges;

    // New structure stores min value, max value, for input and change to be added
    std::vector<std::tuple<long long, long long, long long>> newMap;

    std::getline(input, line); 
    std::string substr = line.substr(line.find(":") + 1, line.find(":") + line.length()) ;
    std::stringstream sl(substr); 
    long long startValues;
    long long rangeValues; 

    while(sl >> startValues >> rangeValues){
        // std::cout << startValues << " : " << startValues + rangeValues - 1<<  std::endl;
        seedRanges.push_back(std::make_tuple(startValues, startValues + rangeValues - 1, 0)); 
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
            newMap.push_back(std::make_tuple(source_range_start, source_range_start + range_length - 1, dest_range_start - source_range_start));
        }

        else if(line.empty()){ 
            if(!newMap.empty()){ 
                // Min seed, max seed, corresponding value

                // For all the ranges we have chek if they overlap with a map 
                std::vector<std::tuple<long long, long long, long long>> newSeedRanges; 

                for(int i = 0; i < seedRanges.size(); i++){ 
                    long long value = std::get<2>(seedRanges[i]);
                    long long minSeed = std::get<0>(seedRanges[i]);
                    long long maxSeed = std::get<1>(seedRanges[i]);
                    std::cout << " Input Range: " << minSeed << " : " << maxSeed  << std::endl; 
                    // Case 1: Bottom overlap 
                    //          [ Map Range ]
                    //  [ Seed Range ] 

                    bool noMapOverlap = true;

                    std::vector<std::tuple<long long, long long, long long>> newSeedRange; 

                    for(int j = 0; j < newMap.size(); j++){
                        long long minMap = std::get<0>(newMap[j]);
                        long long maxMap = std::get<1>(newMap[j]);
                        long long changeMap = std::get<2>(newMap[j]);
                        std::cout << "  Map to proccess: " << minMap - value << " : " << maxMap - value << " : " <<  changeMap << std::endl; 
                    
                        if ((minMap < (maxSeed + value)) && ((minSeed+ value) < minMap)){ 
                            std::cout << "      Top overlap" << std::endl;
                            // Add a new range that has changes
                            newSeedRange.push_back(std::make_tuple(minMap - value, maxSeed, value + changeMap));
                            // Add range that didnt change 
                            //newSeedRanges.push_back(std::make_tuple(minSeed, minMap - 1  - value, value)); 
                            noMapOverlap = false; 
                        }
                        // Case 3: Bottom overlap 
                        //  [ Seed Range ]
                        //          [ Map Range ]
                        //                   
                        else if(((minSeed + value) < maxMap) && (maxMap < (maxSeed + value))){
                            std::cout << "      Bottom overlap" << std::endl;
                            // Add new changes values 
                            newSeedRange.push_back(std::make_tuple(minSeed, maxMap - value, value + changeMap)); 

                            // Heres the problem we are pushing back a new block of data that has already  been updated
                            
                            newSeedRange.push_back(std::make_tuple(maxMap + 1- value, maxSeed, value)); 
                            noMapOverlap = false; 
                        }
                        // Case 4: Complete Overlap 
                        //                  [Seed Range ]
                        //          [ Map Range          ]
                        ///            
                        else if ((minMap <=  (minSeed + value)) && ((maxSeed + value) <= maxMap)){ 
                            std::cout << "      Complete Overlap Map over seed" << std::endl;
                            newSeedRange.push_back(std::make_tuple(minSeed, maxSeed, value + changeMap));
                            noMapOverlap = false; 
                        }
                        // Case 5: Seed encompasses map 
                        //      [       Seed Range         ]
                        //              [ Map Range ] 
                        else if(((minSeed + value) < minMap) && (maxMap < (maxSeed + value))){ 
                            std::cout << "      Seed Over Map" << std::endl;
                            //newSeedRanges.push_back(std::make_tuple(minSeed, minMap - 1, value));
                            newSeedRange.push_back(std::make_tuple(minMap, maxMap, value + changeMap));
                            //newSeedRanges.push_back(std::make_tuple(maxMap+1, maxSeed, value));
                            noMapOverlap = false; 
                        }
                        else {
                            std::cout << "      No Overlap" << std::endl;
                        }
                    } // Map proccessing loop 
                    
                    if(noMapOverlap){ 
                        std::cout << "      No Overlap" << std::endl; 
                        newSeedRanges.push_back(seedRanges[i]);
                    }
                    else { 
                        std::cout<<"ADDING NEW" << std::endl;
                        for (auto t : newSeedRange){
                            newSeedRanges.push_back(t); 
                            std::cout << std::get<0>(t) <<  " : " << std::get<1>(t)<<  " : "  << std::get<2>(t) << std::endl; 
                        }
                    }
                }// Seed proccesing loop


                seedRanges = newSeedRanges; 
                std::cout<<"----------"<<std::endl; 
                for (auto row : seedRanges){ 
                    std::cout << std::get<0>(row) <<  " : " << std::get<1>(row) <<  " : " << std::get<2>(row) <<std::endl; 
                }
            }
        }
    }

    long long minVal = LLONG_MAX; 

    for (auto row : seedRanges){ 
        long long tempVal = std::get<0>(row) + std::get<2>(row); 
        if (tempVal < minVal & tempVal != 0){ 
            minVal = tempVal; 
        }
        std::cout << std::get<0>(row) <<  " : " << std::get<1>(row) <<  " : " << std::get<2>(row) <<std::endl; 
    }
    std::cout << minVal << std::endl; 

} 