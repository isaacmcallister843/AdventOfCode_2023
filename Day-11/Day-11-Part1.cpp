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
std::map<std::pair<int, int>, int>  DjserksSearch (std::vector<std::vector<std::string>> Grid, std::pair<int, int> startingLocation) { 
    std::map<std::pair<int, int>, int> distances;
    
    for(int i =0; i < Grid.size(); i ++){
        for(int j = 0; j< Grid[0].size(); j++){
            distances[std::make_pair(i, j)] = INT16_MAX; 
        }
    }
    distances[startingLocation] = 0; 

    std::priority_queue<std::pair<int, std::pair<int,int>>> pq; // setup maxheap 
    pq.push(std::make_pair(0, startingLocation));

    while(!pq.empty()){
        auto element = pq.top();
        pq.pop();
        int currentDistance = -1*element.first; // Want a min heap 
        std::pair<int, int> currentNode = element.second;
        std::vector<std::pair<int, int>>  neighbours; 
        std::vector<std::pair<int, int>> delta = {{0, 1}, {0, -1}, {1,0}, {-1, 0}};
        
        for (const auto& val : delta){
            std::pair<int, int> potentialNeighbour = {currentNode.first + val.first, currentNode.second + val.second}; 
            if((potentialNeighbour.first >= 0) && (potentialNeighbour.first < Grid.size()) && 
                (potentialNeighbour.second >= 0) && (potentialNeighbour.second < Grid[0].size())){ 
                int distance = currentDistance + 1; 
                if(distance < distances[potentialNeighbour]){
                    distances[potentialNeighbour] = distance; 
                    pq.push(std::make_pair(-1* distance, potentialNeighbour));
                }
            }
        }   
    }
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

    std::vector<int> colToExpand; 
    std::vector<int> rowToExpand; 

    for(int j = 0; j < puzzleInput[0].size(); j++){
        std::vector<char> newCol; 

        for(int i = 0; i < puzzleInput.size(); i++){
            newCol.push_back(puzzleInput[i][j]);
        }
        if(allEqual(newCol)){
            colToExpand.push_back(j);
        }
    }

    for(int j = 0; j < puzzleInput.size(); j++){ 
        if(allEqual(puzzleInput[j])){
            
            rowToExpand.push_back(j);
        }
    }

    std::vector<std::vector<std::string>> expandedUniverse; 
    std::vector<std::pair<int, int>> nodeLocations; 

    for (int j = 0; j < puzzleInput.size(); j++){
        std::vector<std::string> newR; 
        for(int i = 0; i < puzzleInput[0].size(); i++){
            
            newR.push_back(std::string() +  puzzleInput[j][i]);
            auto it = std::find(colToExpand.begin(), colToExpand.end(), i);
            if(it != colToExpand.end()){
                newR.push_back(".");
            }
            
        }
        expandedUniverse.push_back(newR);

        auto it = std::find(rowToExpand.begin(), rowToExpand.end(), j);
        if(it != rowToExpand.end()){
            std::vector<std::string> myVector(newR.size(), ".");
            expandedUniverse.push_back(myVector);
        }
    }

    for(int j = 0; j < expandedUniverse.size(); j++){
        for(int i =0 ; i < expandedUniverse[0].size(); i++){
            if(expandedUniverse[j][i] == "#"){
                nodeLocations.push_back(std::make_pair(j, i));
            }
        }
    }
    // ------ Mapping

    std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> allNodePairs; 

    for(int i = 0; i < nodeLocations.size(); i++){ 
        for(int j = i+1; j < nodeLocations.size(); j++){
            allNodePairs.insert(std::make_pair(nodeLocations[i], nodeLocations[j]));
        }
    }

    std::map<std::pair<int, int>, int> currentMap; 
    std::pair<int, int> prevPair = {-1, -1}; 
    int sumDistance = 0; 

    for (auto pair : allNodePairs) {
        std::pair<int, int> currentStarting = {pair.first.first, pair.first.second}; 
        std::pair<int, int> targetLocation = {pair.second.first, pair.second.second}; 
        if(currentStarting != prevPair){ 
            prevPair = currentStarting; 
            currentMap = DjserksSearch(expandedUniverse, currentStarting); 
        }

        int pairDistance = currentMap[targetLocation]; 
        sumDistance += pairDistance; 
    }
    std::cout << sumDistance << std::endl; 
};