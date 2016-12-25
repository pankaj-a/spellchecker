#include<iostream>
#include<cmath>
#include<bitset>
#include<fstream>
#include<vector>
#include "bloomfilter.h"

using namespace std;

typedef unsigned long long int  (*HashFunction)(string&);


void DisplayResult(vector<string> &answer)
{
	for(vector<string>::iterator it=answer.begin();it!=answer.end();++it)
	{
		cout<<*it<<endl;
	}
}
void GenerateCandidates(vector<string>&edits,bloomfilter &filter,vector<string> &candidates)
{
	for(vector<string>::iterator it=edits.begin();it!=edits.end();++it)
	{
		if(filter.b.test(RSHash(*it)%1118344)&&
		filter.b.test(JSHash(*it)%1118344)&&
		filter.b.test(PJWHash(*it)%1118344)&&
		filter.b.test(ELFHash(*it)%1118344)&&
		filter.b.test(BKDRHash(*it)%1118344)&&
		filter.b.test(SDBMHash(*it)%1118344)&&
		filter.b.test(DJBHash(*it)%1118344)&&
		filter.b.test(DEKHash(*it)%1118344)&&
		filter.b.test(BPHash(*it)%1118344)&&
		filter.b.test(FNVHash(*it)%1118344)&&
		filter.b.test(APHash(*it)%1118344))candidates.push_back(*it);
	}
	cout<<"Candidates generated succesfully\n";
}

void GenerateEdits(vector<string>&edits,string &word)
{
	int i;
	char r='a';
	for(i=0;i<word.size();i++)edits.push_back(word.substr(0,i)+word.substr(i+1));//deletions
	for(i=0;i<word.size()-1;i++)edits.push_back(word.substr(0,i)+word[i+1]+word[i]+word.substr(i+2));//transpositions
	while(r<='z')
	{
		for(i=0;i<word.size();++i)edits.push_back(word.substr(0,i)+r+word.substr(i+1));//alterations
		for(i=0;i<=word.size();++i)edits.push_back(word.substr(0,i)+r+word.substr(i));//insertions
		r++;
	}
	cout<<"Edits generated succesfully\n";
}

long long int createbitarray(bloomfilter &filter)
{
	long long int cnt=0;
	string word;
	ifstream ifile("cleaned_dict.txt");
	while(ifile)
	{
		ifile>>word;
		cnt++;
		filter.b.set(RSHash(word)%1118344);
		filter.b.set(JSHash(word)%1118344);
		filter.b.set(PJWHash(word)%1118344);
		filter.b.set(ELFHash(word)%1118344);
		filter.b.set(BKDRHash(word)%1118344);
		filter.b.set(SDBMHash(word)%1118344);
		filter.b.set(DJBHash(word)%1118344);
		filter.b.set(DEKHash(word)%1118344);
		filter.b.set(BPHash(word)%1118344);
		filter.b.set(FNVHash(word)%1118344);
		filter.b.set(APHash(word)%1118344);
		//cout<<b<<endl;
	}
	cout<<"Bit array created succesfully\n";
	return cnt;
}

bool check(bloomfilter &filter, string &word)
{
	if(filter.b.test(RSHash(word)%1118344)&&
		filter.b.test(JSHash(word)%1118344)&&
		filter.b.test(PJWHash(word)%1118344)&&
		filter.b.test(ELFHash(word)%1118344)&&
		filter.b.test(BKDRHash(word)%1118344)&&
		filter.b.test(SDBMHash(word)%1118344)&&
		filter.b.test(DJBHash(word)%1118344)&&
		filter.b.test(DEKHash(word)%1118344)&&
		filter.b.test(BPHash(word)%1118344)&&
		filter.b.test(FNVHash(word)%1118344)&&
		filter.b.test(APHash(word)%1118344))return true;
	return false;
}

unsigned long long int  RSHash( string& str)
{
   unsigned long long int  y    = 378551;
   unsigned long long int  x    = 63689;
   unsigned long long int  hash_value = 0;

   for(int i = 0; i < str.length(); i++)
   {
      hash_value = hash_value * x + str[i];
      x    = x *y;
   }

   return hash_value;
}



unsigned long long int  JSHash( string& str)
{
   unsigned long long int  hash_value = 1315423911;

   for(int i = 0; i < str.length(); i++)
   {
      hash_value ^= ((hash_value << 5) + str[i] + (hash_value >> 2));
   }

   return hash_value;
}



unsigned long long int  PJWHash( string& str)
{
   unsigned long long int  BitsInUnsignedInt = (unsigned long long int )(sizeof(unsigned long long int ) * 8);
   unsigned long long int  threefourth     = (unsigned long long int )((BitsInUnsignedInt  * 3) / 4);
   unsigned long long int  oneeighth         = (unsigned long long int )(BitsInUnsignedInt / 8);
   unsigned long long int  highbit          = (unsigned long long int )(0xFFFFFFFF) << (BitsInUnsignedInt - oneeighth);
   unsigned long long int  hash              = 0;
   unsigned long long int  test              = 0;

   for(int i = 0; i < str.length(); i++)
   {
      hash = (hash << oneeighth) + str[i];

      if((test = hash & highbit)  != 0)
      {
         hash = (( hash ^ (test >> threefourth)) & (~highbit));
      }
   }

   return hash;
}



unsigned long long int  ELFHash( string& str)
{
   unsigned long long int  hash = 0;
   unsigned long long int  x    = 0;

   for(int i = 0; i < str.length(); i++)
   {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}



unsigned long long int  BKDRHash( string& s)			//5
{
   unsigned long long int  x = 131; 
   unsigned long long int  hsh = 0;

   for(int i = 0; i < s.length(); i++)
   {
      hsh = (hsh * x) + s[i];
   }

   return hsh;
}



unsigned long long int  SDBMHash( string& s)				//6
{
   unsigned long long int  hsh = 0;

   for(int i = 0; i < s.length(); i++)
   {
      hsh = s[i] + (hsh << 6) + (hsh << 16) - hsh;
   }

   return hsh;
}



unsigned long long int  DJBHash( string& s)			//7
{
   unsigned long long int  hsh = 5381;

   for(int i = 0; i < s.length(); i++)
   {
      hsh = ((hsh << 5) + hsh) + s[i];
   }

   return hsh;
}


unsigned long long int  DEKHash( string& s)
{
   unsigned long long int  h = static_cast<unsigned long long int >(s.length());

   for(int t = 0; t < s.length(); t++)
   {
      h = ((h << 5) ^ (h >> 27)) ^ s[t];
   }

   return h;
}



unsigned long long int  BPHash( string& s)
{
   unsigned long long int  h = 0;
   for(int t = 0; t < s.length(); t++)
   {
      h = h << 7 ^ s[t];
   }

   return h;
}



unsigned long long int  FNVHash( string& s)
{
    unsigned long long int  p = 0x811C9DC5;
   unsigned long long int  h = 0;
   for(int t = 0; t < s.length(); t++)
   {
      h *= p;
      h ^= s[t];
   }

   return h;
}



unsigned long long int  APHash( string& s)
{
   unsigned long long int  h = 0xAAAAAAAA;

   for(int t = 0; t < s.length(); t++)
   {
      h ^= ((t & 1) == 0) ? (  (h <<  7) ^ s[t] * (h >> 3)) :
                               (~((h << 11) + (s[t] ^ (h >> 5))));
   }

   return h;
}

