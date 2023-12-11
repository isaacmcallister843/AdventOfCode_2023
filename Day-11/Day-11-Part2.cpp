#include "Day-11-Isaac.hpp"

bool allEqual(const std::vector<char>& vec) {
    return std::all_of(vec.begin(), vec.end(), 
                       [first = vec.front()](char elem) { return elem == first; });
}

bool isNumber(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isdigit(c); });
}


struct Node {
    char name; 
    std::vector<Node*> neighbors; // Adjacent nodes
};

// I am actually a fucking idiot for using this just do delta x and delta y BUT WHATEVER 

std::map<std::pair<long long, long long>, long long>  DjserksSearch (std::vector<std::vector<std::string>> Grid, std::pair<long long, long long> startingLocation) { 
    std::map<std::pair<long long, long long>, long long> distances;
    
    for(long long i =0; i < Grid.size(); i ++){
        for(long long j = 0; j< Grid[0].size(); j++){
            distances[std::make_pair(i, j)] = LLONG_MAX; 
        }
    }
    distances[startingLocation] = 0; 

    // --------- Apply Djserks
    std::priority_queue<std::pair<long long, std::pair<long long,long long>>> pq; // setup maxheap 
    pq.push(std::make_pair(0, startingLocation));

    while(!pq.empty()){
        // Get the pair from the "Top"
        auto element = pq.top();
        pq.pop();
        long long currentDistance = -1*element.first; // Want a min heap 
        
        std::pair<long long, long long> currentNode = element.second;

        std::vector<std::pair<long long, long long>>  neighbours; 
        std::vector<std::pair<long long, long long>> delta = {{0, 1}, {0, -1}, {1,0}, {-1, 0}};
        
        for (const auto& val : delta){
            std::pair<long long, long long> potentialNeighbour = {currentNode.first + val.first, currentNode.second + val.second}; 
            if((potentialNeighbour.first >= 0) && (potentialNeighbour.first < Grid.size()) && 
                (potentialNeighbour.second >= 0) && (potentialNeighbour.second < Grid[0].size())){ 
                long long distance;
                
                if(Grid[potentialNeighbour.first][potentialNeighbour.second]  == "E"){ 
                    distance = currentDistance + 1000000; 
                }   
                else{
                    distance = currentDistance + 1; 
                }           
                
                if(distance < distances[potentialNeighbour]){
                    distances[potentialNeighbour] = distance; 
                    pq.push(std::make_pair(-1* distance, potentialNeighbour));
                }
            }
        }   
    }

    // for(long long i = 0; i < Grid.size(); i ++){ 
    //     for(long long j = 0; j < Grid.size(); j ++) { 
    //         std::cout << std::setw(3) << distances[std::make_pair(i, j)] << " "; 
    //     }
    //     std::cout << std::endl;
    // }

    return distances; 

}

int main(){

    // --------- Variable Setup 
    std::string line;
    std::ifstream input("Day-11-Input.txt");

    std::vector<std::vector<char>> puzzleInput; 

    // -------- Read puzzle input
    
    while(std::getline(input, line)){ 
        std::vector<char> newR; 
        for(auto c : line){
            newR.push_back(c); 
        }
        puzzleInput.push_back(newR); 
    }

    // -------- Perform expansion 

    std::vector<long long> colToExpand; 
    std::vector<long long> rowToExpand; 

    for(long long j = 0; j < puzzleInput[0].size(); j++){
        std::vector<char> newCol; 
        for(long long i = 0; i < puzzleInput.size(); i++){
            newCol.push_back(puzzleInput[i][j]);
        }
        if(allEqual(newCol)){
            colToExpand.push_back(j);
        }
    }

    for(long long j = 0; j < puzzleInput.size(); j++){ 
        if(allEqual(puzzleInput[j])){
            rowToExpand.push_back(j);
        }
    }

    std::vector<std::vector<std::string>> expandedUniverse; 
    
    for (long long j = 0; j < puzzleInput.size(); j++){
        
        auto it = std::find(rowToExpand.begin(), rowToExpand.end(), j);
        if(it != rowToExpand.end()){
            
            std::vector<std::string> myVector(puzzleInput[0].size(), "E");
            expandedUniverse.push_back(myVector);
        }
        else{ 
            std::vector<std::string> newR; 
            for(long long i = 0; i < puzzleInput[0].size(); i++){
                auto it = std::find(colToExpand.begin(), colToExpand.end(), i);
                if(it != colToExpand.end()){
                    newR.push_back("E");
                }
                else{
                    newR.push_back(std::string() +  puzzleInput[j][i]);
                }   
            }
            expandedUniverse.push_back(newR);  
        }
        
       
    }


    std::vector<std::pair<long long, long long>> nodeLocations; 
    for(long long j = 0; j < expandedUniverse.size(); j++){
        for(long long i =0 ; i < expandedUniverse[0].size(); i++){
            if(expandedUniverse[j][i] == "#"){
                nodeLocations.push_back(std::make_pair(j, i));
            }
        }
    }
    // ------ Mapping
    
    // for(auto d : expandedUniverse){
    //     for(auto f : d){
    //         std::cout << f << " ";
    //     }
    //     std::cout << std::endl; 
    // }

    std::cout << "-----" << std::endl;
    std::set<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>> allNodePairs; 

    for(long long i = 0; i < nodeLocations.size(); i++){ 
        for(long long j = i+1; j < nodeLocations.size(); j++){
            allNodePairs.insert(std::make_pair(nodeLocations[i], nodeLocations[j]));
        }
    }

    // for (auto pair : allNodePairs) {
    //     std::cout << "(" << pair.first.first << ", " << pair.first.second << ") : (" << pair.second.first << ", " << pair.second.second << ") " << std::endl;
    // }


    std::map<std::pair<long long, long long>, long long> currentMap; 
    std::pair<long long, long long> prevPair = {-1, -1}; 
    long long sumDistance = 0; 

    for (auto pair : allNodePairs) {

        std::pair<long long, long long> currentStarting = {pair.first.first, pair.first.second}; 
        std::pair<long long, long long> targetLocation = {pair.second.first, pair.second.second}; 


        if(currentStarting != prevPair){ 
            prevPair = currentStarting; 
            currentMap = DjserksSearch(expandedUniverse, currentStarting); 
        }

        long long pairDistance = currentMap[targetLocation]; 
        // std::cout << "(" << pair.first.first << ", " << pair.first.second << ") : (" << pair.second.first << ", " << pair.second.second << ") " <<  "  :  " << pairDistance << std::endl;
        sumDistance += pairDistance; 

    }
    std::cout << sumDistance << std::endl; 
    


    //DjserksSearch (expandedUniverse, nodeLocations[0]);

};
