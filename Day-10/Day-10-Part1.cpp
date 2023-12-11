#include "Day-10-Isaac.hpp"
// This one is SO BAD LITERALLY THE WORST WAY TODO IT 


struct Node {
    char name; 
    std::vector<Node*> neighbors; // Adjacent nodes
};

struct connections {
    int xchange; 
    int ychange; 

    // Default constructor
    connections() : xchange(0), ychange(0) {}

    // Constructor with parameters
    connections(int val1, int val2) : xchange(val1), ychange(val2) {}

};

std::map<char, std::pair<connections, connections>> newMap;

void addPair(char val, int y1, int x1,int y2,  int x2){ 
    newMap[val] = std::pair<connections, connections>(connections(x1, y1), connections(x2, y2));
}


int main(){

    // --------- Variable Setup 
    std::string line;
    std::ifstream input_1("Day-10-Input.txt");
    std::getline(input_1, line);
    int dataSize = line.length(); 
    std::ifstream input("Day-10-Input.txt");

    std::vector<std::vector<Node*>> matrix; 

    // For the longest path algoirithem 
    std::map<Node*, int> distances;

    // Grid 
    //   0,0   0,1   0,2 
    //   1,0   1,1   1,2   
    //   2,0   2,1   2,2

    // Think of everything as node connectios 
    // (y, x)
    //  |  =  +/-  (1, 0)
    //  -  =  +/-  (0, 1)
    //  L  =  + (-1, 0), (0,  1)
    //  J  =  + (-1, 0), (0, -1)
    //  7  =  + (-1, 0), (1,  0)
    //  F  =  + ( 1, 0), (0,  1)
    //  .  =  no connection 

    // --------- Map Setup 

    addPair('|', 1, 0, -1, 0);
    addPair('-', 0, 1, 0, -1);
    addPair('L', -1, 0, 0, 1);
    addPair('J', -1, 0, 0, -1);
    addPair('7', 0, -1, 1, 0);
    addPair('F', 1, 0, 0, 1);

    // --------- Node Setup 


    Node* startingNode; 
    Node* emptyNode = new Node();
    emptyNode->name = '.'; 

    std::vector<Node*> paddingRow;
    for(int i = 0 ; i < dataSize+2; i++){
        paddingRow.push_back(emptyNode); 
    }
    matrix.push_back(paddingRow); 


    while(std::getline(input, line)){ 
        std::vector<Node*> currentRow; 
        currentRow.push_back(emptyNode);

        for(auto c : line){ 
            if (c == '.'){
                currentRow.push_back(emptyNode); 
            }
            else{
                Node* newNode = new Node();
                newNode->name = c; 
                currentRow.push_back(newNode); 
                if(c == 'S'){ 
                    startingNode = newNode; 
                }
                distances[newNode] = INT16_MAX;
                
            }
            
        }
        currentRow.push_back(emptyNode); 
        matrix.push_back(currentRow); 
    }
    matrix.push_back(paddingRow); 

    //std::cout << "---------" << std::endl;
    for (auto d : matrix) { 
        for(auto L : d){
            //std::cout << std::setw(5)  << L->name << " "; 
        }
        //std::cout << std::endl; 
    }
    //std::cout << "---------" << std::endl;

    // --------- Find all neighbours for each node 

    for(int i = 1; i< matrix.size()-1 ; i++){
        for(int j = 1; j < matrix[0].size() - 1; j++){ 
            Node* currentNode = matrix[i][j];
            if(currentNode->name != '.' && currentNode->name != 'S'){ 
                std::pair<connections, connections> currentConnection = newMap[currentNode->name]; 
                Node* firstNode = matrix[i + currentConnection.first.ychange][j + currentConnection.first.xchange]; 
                Node* secondNode = matrix[i + currentConnection.second.ychange][j + currentConnection.second.xchange]; 
                
                if(firstNode != emptyNode) {
                    ////std::cout << firstNode->name << std::endl; 
                    currentNode->neighbors.push_back(firstNode);
                }

                if(secondNode != emptyNode){ 
                    currentNode->neighbors.push_back(secondNode);
                    // //std::cout << secondNode->name << std::endl; 
                } 
                if(firstNode == startingNode) startingNode->neighbors.push_back(currentNode); 
                if(secondNode == startingNode) startingNode->neighbors.push_back(currentNode); 

            }
            ////std::cout << matrix[i][j]->name << " ";
        }
        ////std::cout << std::endl; 
    }

    //std::cout << "---------" << std::endl;

    distances[startingNode] = 0; 

    //std::cout << "---------" << std::endl;
    for (auto d : matrix) { 
        for(auto L : d){
            //std::cout << std::setw(5)  << distances[L] << " "; 
        }
        //std::cout << std::endl; 
    }
    //std::cout << "---------" << std::endl;

    // --------- Apply Djserks
    std::priority_queue<std::pair<int, Node*>> pq; // setup maxheap 
    pq.push(std::make_pair(0, startingNode));

    while(!pq.empty()){
        // Get the pair from the "Top"
        auto element = pq.top();
        pq.pop();
        int currentDistance = -1*element.first; // Want a min heap 
        
        Node* currentNode = element.second; 
        
        for (const auto& neighbour : currentNode->neighbors){
            int distance = currentDistance + 1; 
            if(distance < distances[neighbour]){
                distances[neighbour] = distance; 
                pq.push(std::make_pair(-1* distance, neighbour));
            }
        }   
    }

    int maxDistances = 0; 

     for (auto d : matrix) { 
        for(auto L : d){
            if((distances[L] > maxDistances ) && (distances[L] != INT16_MAX)){
                maxDistances =distances[L]; 
            }
        }
    }

    std::cout << maxDistances << std::endl; 
};