//
//  main.cpp
//  type_ahead
//
//  Created by Simran Kaur Arora on 9/29/16.
//  Copyright © 2016 Simran Kaur Arora. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

bool valid(char cur) {
    if (cur >= 'a' && cur <= 'z') return true;
    if (cur >= 'A' && cur <= 'Z') return true;
    if (cur >= '0' && cur <= '9') return true;
    if (cur == ' ') return true;
    
    return false;
}

void removeNonAlpha(string &msg) {
    string res = "";
    for (int i = 0; i < msg.size(); ++i) {
        if (valid(msg[i])) res += msg[i];
    }
    msg = res;
}

bool compare(pair<string, int> a, pair<string, int> b) {
    if (a.second > b.second) return true;
    if (a.second < b.second) return false;
    if (a.first.compare(b.first) < 0) return true;
    return false;
}

int main(int argc, char *argv[]) {
    string msg = "Mary had a little lamb its fleece was white as snow; And everywhere that Mary went, the lamb was sure to go. It followed her to school one day, which was against the rule; It made the children laugh and play, to see a lamb at school. And so the teacher turned it out, but still it lingered near, And waited patiently about till Mary did appear. \"Why does the lamb love Mary so?\" the eager children cry;\"Why, Mary loves the lamb, you know\" the teacher did reply.\"";
    
    removeNonAlpha(msg);
    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
    
//     vector<string> words;
//     istringstream iss(msg);
//     string temp;
//     while (iss >> temp) {
//     	words.push_back(temp);
//     }
//    
    ifstream ifs(argv[1]);
    string line;
    
    while (getline(ifs, line)) {
        line = line.substr(line.find(',')+1);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        
        map<string, int> res;
        int count = 0;
        int pos = msg.find(line);
        while (pos != string::npos) {
            int pos2 = msg.find(' ', pos+line.size()+1);
            string tmp = msg.substr(pos+line.size()+1, pos2-pos-line.size()-1);
            res[tmp]++;
            count++;
            pos = msg.find(line, pos+line.size()+1);
        }
        
        vector<pair<string, int> > table;
        for (map<string, int>::iterator it = res.begin(); it != res.end(); ++it) {
            table.push_back(make_pair("string",it->second));
        }
        
        sort(table.begin(), table.end(), compare);
        for (int i = 0; i < table.size(); ++i) {
            cout << table[i].first << "," << fixed << setprecision(3) << (double)(table[i].second/(double)count);
            if (i != table.size()-1) cout << ";";
        }
        cout << endl;
        
    }
    
    return 0;
}
