#include "Day-7-Isaac.hpp"

int translation(std::string hand) { 
    std::map<char, char> input_to_hex = {{'T', 'A'}, {'J', '1'}, {'Q', 'C'}, {'K', 'D'}, {'K', 'E'}, {'A', 'F'}};
    
    std::string hexString = ""; 
    for(char c : hand){ 
        if(input_to_hex.find(c) != input_to_hex.end()){ 
            hexString += input_to_hex[c]; 
        }
        else { 
            hexString += c; 
        }
    }
    std::map<char, int> seenValues;

    for(char c : hexString){
        if (seenValues.find(c) == seenValues.end()){
            seenValues[c] = 1;
        }
        else{
            seenValues[c]++; 
        }
    }
    int numJ = seenValues['1']; 
    seenValues['1'] = 0; 

    std::vector<std::pair<char, int>> vec(seenValues.begin(), seenValues.end());
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    vec[0].second += numJ;

    if(vec[0].second == 5) { 
        hexString = "6" + hexString;  
    } 
    else if(vec[0].second == 4){ 
        hexString = "5" + hexString;
    }
    else if(vec[0].second == 3 && vec[1].second == 2){
        hexString = "4" + hexString;
    }
    else if(vec[0].second == 3 && vec[1].second == 1){
        hexString = "3" + hexString;  
    }
    else if(vec[0].second == 2 && vec[1].second == 2){
        hexString = "2" + hexString;
    }
    else if(vec[0].second == 2){ 
        hexString = "1" + hexString;
    }
    return std::stoi(hexString, nullptr, 16); 
}

int main(){
    std::string line;
    std::ifstream input("Day-7-Input.txt");
    std::vector<std::pair<int, int>> hands_bets; 

    while(std::getline(input, line)){
        std::stringstream ss(line); 
        std::string newHand;
        int betValue; 
        ss >> newHand >> betValue; 
        int transValue = translation(newHand);
        hands_bets.push_back(std::make_pair(transValue, betValue)); 
    }
    std::sort(hands_bets.begin(), hands_bets.end()); 
        int totalValue = 0; 
    for(int i = 0; i < hands_bets.size(); i++){ 
        totalValue += (i+1) * hands_bets[i].second; 
    }
    std::cout <<totalValue << std::endl;
}