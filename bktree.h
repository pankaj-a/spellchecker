#ifndef BKTREE_H
#define BKTREE_H

#include<iostream>
#include<algorithm>
#include<fstream>
#include<string.h>
#include<map>
#include<vector>
#include "levenshtein.h"

using namespace std;

struct node
{
	string value;
	long long int freq;
	map<int,node*> *children;
};

node* createnode(string s,long long int cnt);
bool insert(node *root,node *cur);
void GenerateResult(node *root,string x,int tolerance,map<unsigned long long int,string >&result,set<string>&result_strings);
node* LoadFromFile(const string& filename);

#endif
