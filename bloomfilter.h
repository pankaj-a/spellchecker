#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include<vector>
#include<bitset>

#define NO_OF_BITS 1118344
using namespace std;
struct bloomfilter
{
	long long int m,n,k;
	bitset<NO_OF_BITS> b;
};

unsigned long long int RSHash  ( string& str);
unsigned long long int JSHash  ( string& str);
unsigned long long int PJWHash ( string& str);
unsigned long long int ELFHash ( string& str);
unsigned long long int BKDRHash( string& str);
unsigned long long int SDBMHash( string& str);
unsigned long long int DJBHash ( string& str);
unsigned long long int DEKHash ( string& str);
unsigned long long int BPHash  ( string& str);
unsigned long long int FNVHash ( string& str);
unsigned long long int APHash  ( string& str);
void DisplayResult(vector<string> &answer);
void GenerateCandidates(vector<string>&edits,bloomfilter &filter,vector<string> &candidates);
long long int createbitarray(bloomfilter &filter);
bool check(bloomfilter &filter, string &word);
void GenerateEdits(vector<string>&edits,string &word);

#endif
