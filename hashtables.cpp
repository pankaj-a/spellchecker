#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include "hashtables.h"

using namespace std;

typedef unordered_map<string,long long int> dictionary;

/*char filterNonAlphabetic(char& letter) {
	if (isalpha(letter)) { return tolower(letter); }
	return '-';
}*/

void GenerateEdits(vector<string>&edits,dictionary &d,string &word)
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
void GenerateCandidates(vector<string>&edits,dictionary &d,map<long long int,string> &candidates)
{
	dictionary::iterator found;
	for(vector<string>::iterator it=edits.begin();it!=edits.end();++it)
	{
		found=d.find(*it);
		if(found!=d.end())
			candidates[found->second]=found->first;
	}
	cout<<"Candidates generated succesfully\n";
}
void DisplayResult(map<long long int,string>&candidates)
{
	int i=0;
	for(map<long long int,string>::reverse_iterator it=candidates.rbegin();it!=candidates.rend();++it)
	{
		cout<<it->second<<' '<<it->first<<endl;
		++i;
		if(i==5)break;
	}
}
void LoadFromFile(const string& filename,dictionary &d)
{
	string x;
	long long int cnt;
	ifstream ifile(filename.c_str());
	while(ifile)
	{
		ifile>>x;
		ifile>>cnt;
		d[x]=cnt;
		//cout<<x<<' '<<cnt<<endl;
	}
	cout<<"Dictionary loaded successfully\n";
}
/*void LoadFromFile(const string& filename, dictionary &d)
{
	ifstream file(filename.c_str(), ios_base::binary | ios_base::in);
	file.seekg(0, ios_base::end);
	int length = file.tellg();
	file.seekg(0, ios_base::beg);
	string line(length, '0');
	file.read(&line[0], length);
	transform(line.begin(), line.end(), line.begin(), filterNonAlphabetic);
	string::size_type end = line.size();
	//cout<<line;
	for (string::size_type i = 0;;) 
	{
		while (line[++i] == '-' && i < end); //find first '-' character
		if (i >= end) { break; }
		string::size_type begin = i;
		while (line[++i] != '-' && i < end); //find first not of '-' character
		d[line.substr(begin, i - begin)]++;
	}
	cout<<"Dictionary loaded successfully\n";
}
int main()
{

	dictionary d; 
	map<int,string>candidates;
	vector<string>edits;
	string word;
	dictionary::iterator it;
	LoadFromFile("big.txt",d);
	cin>>word;
	if(d.find(word)!=d.end())
		cout<<"correct spelling"<<endl;
	else
	{	
		GenerateEdits(edits,d,word);
		GenerateCandidates(edits,d,candidates);
		DisplayResult(candidates);
	}
}*/
