
#ifndef HASHTABLES_H
#define HASHTABLES_H


#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<fstream>

using namespace std;

typedef unordered_map<string,long long int> dictionary;

void GenerateEdits(vector<string>&edits,dictionary &d,string &word);
void GenerateCandidates(vector<string>&edits,dictionary &d,map<long long int,string> &candidates);
void DisplayResult(map<long long int,string>&candidates);
void LoadFromFile(const string& filename,dictionary &d);

#endif
