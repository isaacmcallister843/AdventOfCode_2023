#include "Day-10-Isaac.hpp"

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

void floodFill(std::vector<std::vector<char>>& matrix, int x, int y, char oldChar, char newChar) {
    // Base cases
    if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()) return; // Boundary check
    if (matrix[x][y] != oldChar) return; // Check if the cell needs to be filled

    // Replace the character
    matrix[x][y] = newChar;

    // Recursively call for adjacent cells
    floodFill(matrix, x + 1, y, oldChar, newChar);
    floodFill(matrix, x - 1, y, oldChar, newChar);
    floodFill(matrix, x, y + 1, oldChar, newChar);
    floodFill(matrix, x, y - 1, oldChar, newChar);
}


int main(){

    // --------- Variable Setup 
    std::string line;
    std::ifstream input_1("Day-10-Input.txt");
    std::getline(input_1, line);
    int dataSize = line.length(); 
    std::ifstream input("Day-10-Input.txt");

    std::vector<std::vector<Node*>> matrix; 

    std::map<Node*, int> distances;

    addPair('|', 1, 0, -1, 0);
    addPair('-', 0, 1, 0, -1);
    addPair('L', -1, 0, 0, 1);
    addPair('J', -1, 0, 0, -1);
    addPair('7', 0, -1, 1, 0);
    addPair('F', 1, 0, 0, 1);

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

    // --------- Find Valid Neighbours  
 
    for(int i = 1; i< matrix.size()-1 ; i++){
        for(int j = 1; j < matrix[0].size() - 1; j++){ 
            Node* currentNode = matrix[i][j];
            if(currentNode->name != '.' && currentNode->name != 'S'){ 
                std::pair<connections, connections> currentConnection = newMap[currentNode->name]; 
                Node* firstNode = matrix[i + currentConnection.first.ychange][j + currentConnection.first.xchange]; 
                Node* secondNode = matrix[i + currentConnection.second.ychange][j + currentConnection.second.xchange]; 
                
                if(firstNode != emptyNode) {
                    currentNode->neighbors.push_back(firstNode);
                }

                if(secondNode != emptyNode){ 
                    currentNode->neighbors.push_back(secondNode);
                } 
                if(firstNode == startingNode) startingNode->neighbors.push_back(currentNode); 
                if(secondNode == startingNode) startingNode->neighbors.push_back(currentNode); 
            }
        }
    }
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
    Node* maxNode = new Node; 

    for (auto d : matrix) { 
        for(auto L : d){
            if((distances[L] > maxDistances ) && (distances[L] != INT16_MAX)){
                maxDistances =distances[L]; 
                maxNode = L; 
            }
        }
    }
    std::cout<<maxDistances << std::endl;
    std::vector<Node*> path_LHS; 
    path_LHS.push_back(maxNode); 
    path_LHS.push_back(maxNode->neighbors[1]); 
    Node* CurrentNodeInplace = maxNode->neighbors[1]; 
    Node* prevNode = maxNode; 
    while( CurrentNodeInplace != maxNode){ 

        for(auto v : CurrentNodeInplace->neighbors){ 
            if(v != prevNode){
                path_LHS.push_back(v);
                prevNode = CurrentNodeInplace;
                CurrentNodeInplace = v; 
                break; 
            }
        }
    }
    std::cout << path_LHS.size() << std::endl; 

    std::vector<std::vector<char>> matrixForFloodFill; 

    for(int i = 0; i< matrix.size() ; i++){
        std::vector<char> newRow; 
        for(int j = 0; j < matrix[0].size(); j++){ 
            Node* currentNode = matrix[i][j];
            auto it = std::find(path_LHS.begin(), path_LHS.end(), currentNode);
            char k; 
            if(it != path_LHS.end()){
                k = currentNode->name; 
            }else{
                k = '.';
            }
            
            newRow.push_back(k);
        }
        //std::cout << std::endl; 
        matrixForFloodFill.push_back(newRow); 
       
    }
    floodFill(matrixForFloodFill, 0, 0, '.', 'P');

    bool inInside = false;

    for (int i = 1; i < matrixForFloodFill.size(); i++) {
        for (int j = 1; j < matrixForFloodFill[0].size(); j++) {
            char val = matrixForFloodFill[i][j];
            Node* noVal = matrix[i][j];

            // Are we connected to the node ABOVE 
            bool isTransition = (val == '|' || val == 'J'|| val == 'L');
            if(isTransition){ 
                matrixForFloodFill[i][j] = 'T'; 
                inInside = !inInside;
            }
            if(val == '.' && inInside){
                floodFill(matrixForFloodFill, i, j, '.', 'M');
            }
        }
        inInside = false; // Reset for each row
    }

    int numEnclosed =0;
  
    for (auto& row : matrixForFloodFill) {
        for (auto& col : row) {
            std::cout << std::setw(4) << col; 
            if(col == 'M'){
                numEnclosed++;
            }
        }
    }
    std::cout << numEnclosed << std::endl;
};
