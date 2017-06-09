//
//  main.cpp
//  bay_bridges
//
//  Created by Simran Kaur Arora on 9/10/16.
//  Copyright © 2016 Simran Kaur Arora. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class bayBridges {
    
public:
    vector<vector<int>> results;
    bayBridges(ifstream &inFile);
    void optimise();
    
private:
    vector<vector<float>> _mapping;
    bool largestVector(vector<vector<int>> &input, vector<int> &popVector);
    bool intersect(vector<float> A, vector<float> B, vector<float> C, vector<float> D);
    bool checkCounterclockwise(vector<float> A, vector<float> B, vector<float> C);
    void recordIntersection();
};


bool bayBridges::largestVector(vector<vector<int>> &input, vector<int> &popVector) {
    // Pops the largest sub vector in a vector
    // Returns false if all sub vectors are of size 1
    vector<int> sizeofVectors(input.size());
    int countEmpty = 0, popIndex, N = input.size();
    
    // Record all the sub vector sizes
    for (int i = 0; i < N; i++) {
        sizeofVectors[i] = input[i].size();
    }
    
    // Check if all vectors are of size 1
    for (auto i: sizeofVectors) {
        if (i == 1) {
            ++countEmpty;
        }
    }
    if (countEmpty == N) {
        return(false);
    }
    
    // Pop largest vector
    auto maxSize = max_element(sizeofVectors.begin(), sizeofVectors.end());
    popIndex = distance(sizeofVectors.begin(), maxSize);
    popVector = input[popIndex];
    input.erase(input.begin()+popIndex);
    return(true);
}


void bayBridges::optimise() {
    recordIntersection();
    vector<int> popVector;
    
    while (largestVector(results, popVector)) {
        int removeBridge = popVector[0];
        
        for (auto &bridge: results) {
            for (int i = 1; i < bridge.size(); i++) {
                if (bridge[i] == removeBridge) {
                    bridge.erase(bridge.begin()+i);
                }
            }
        }
        
    }
}


bool bayBridges::checkCounterclockwise(vector<float> A, vector<float> B, vector<float> C) {
    // Returns true if all 3 points are in counter clockwise order
    return((C[1]-A[1])*(B[0]-A[0]) > (B[1]-A[1])*(C[0]-A[0]));
}


bool bayBridges::intersect(vector<float> A, vector<float> B, vector<float> C, vector<float> D) {
    // Returns true if the line AB & CD intersect, general case only
    return(checkCounterclockwise(A, C, D) != checkCounterclockwise(B, C, D) && checkCounterclockwise(A, B, C) != checkCounterclockwise(A, B, D));
}


void bayBridges::recordIntersection() {
    // Find all line intersects and store in "results" in the form
    // {[pair designation],3,6,8,5,2} , where the the latter numbers are the bridges
    // the current pair designation intercepts with.
    vector<int> tmp;
    vector<float> A(2), B(2), C(2), D(2);
    int nBridge = _mapping.size();
    tmp.reserve(nBridge+1);
    results.reserve(nBridge);
    
    for (int i = 0; i < nBridge; i++) {
        tmp.push_back(int(_mapping[i][0])); // Capture bridge name
        A[0] = _mapping[i][1];
        A[1] = _mapping[i][2];
        B[0] = _mapping[i][3];
        B[1] = _mapping[i][4];
        
        for (int j = 0; j < nBridge; j++) {
            if (j == i) {
                continue;
            }
            else {
                C[0] = _mapping[j][1];
                C[1] = _mapping[j][2];
                D[0] = _mapping[j][3];
                D[1] = _mapping[j][4];
                
                if (intersect(A, B, C, D)) {
                    tmp.push_back(int(_mapping[j][0]));
                }
            }
        }
        results.push_back(tmp);
        tmp.clear();
    }
}


bayBridges::bayBridges(ifstream &inFile) {
    // Parse all the bridges positional data into a container from stream
    float num, p1x, p1y, p2x, p2y;
    while (inFile.peek() != EOF) {
        inFile >> num;
        inFile.ignore(4);
        inFile >> p1x;
        inFile.ignore(1);
        inFile >> p1y;
        inFile.ignore(4);
        inFile >> p2x;
        inFile.ignore(1);
        inFile >> p2y;
        _mapping.push_back({num, p1x, p1y, p2x, p2y});
        inFile.ignore(3, '\n');
    }
}


int main(int argc, char* argv[]) {
    ifstream inFile(argv[1]);
    
    bayBridges config(inFile);
    config.optimise();
    
    for (auto bridge: config.results) {
        cout << bridge[0] << "\n";
    }
    
    return(0);
}