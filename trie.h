#ifndef TRIE_H
#define TIRE_H

#include<string>
#include<map>

using namespace std;

struct trie_node
{
        char info;
        int cnt;
        string Word;
        struct trie_node *ptr[256];

};

trie_node *inittrie_node(trie_node *r);
void insertstring(string word,int pos,trie_node *root,int c);
int find(string key,int pos, trie_node *root);
void printcountwise(map<long long int,string>&fin);
void printinsert(trie_node *root,string key,map<long long int,string>&);
void printall(trie_node *root);
void suggestword(string key,int pos,trie_node *root,map<long long int,string>&);

#endif
