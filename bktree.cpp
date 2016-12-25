#include<iostream>
#include<algorithm>
#include<set>
#include<fstream>
#include<string.h>
#include<map>
#include<vector>
#include "bktree.h"
#include<math.h>
#include "levenshtein.h"

using namespace std;


node* createnode(string s,long long int cnt)
{
	node *temp=new node;
	temp->value=s;
	temp->freq=cnt;
	temp->children=NULL;
	return temp;
}

/*char filterNonAlphabetic(char& letter) {
	if (isalpha(letter)) { return tolower(letter); }
	return '-';
}*/

bool insert(node *root,node *cur)
{
	if(cur==NULL)
	{
		cout<<"Null node insertion not possible\n";
		return false;
	}
	int d=DynamicLevenshtein(root->value,cur->value);
	//cout<<d<<endl;
	if(d==0)
	{
		//cout<<"already exists\n";
		return false;
	}
	if(!root->children)
	{
		root->children=new map<int,node*>();
		root->children->insert(make_pair(d,cur));
	}
	else
	{
		map<int,node*>::iterator it=root->children->find(d);
		if(it==root->children->end())
		{
			root->children->insert(make_pair(d,cur));
			return true;
		}
		insert(it->second,cur);
	}
}
void GenerateResult(node *root,string x,int tolerance,map<unsigned long long int,string >&result,set<string>&result_strings)
{
	int dis=DynamicLevenshtein(root->value,x);
	//cout<<root->value<<endl;
	//if(dis==0){cout<<root->value<<"\n\n";//return 0;
	//		return 0;}
	
		
	if(dis<=tolerance)
	{
		//cout<<root->value<<'\n';
		result_strings.insert(root->value);
		result.insert(make_pair((unsigned long long int)(root->freq*pow(1000,tolerance-dis)),root->value));
	}
	if(root->children!=NULL)
	{
		for(map<int,node*>::iterator it=root->children->begin();it!=root->children->end();++it)
		{
			if(dis-tolerance<=it->first && dis+tolerance>=it->first)
			{	//cout<<it->second->value<<endl;
				GenerateResult(it->second,x,tolerance,result,result_strings);
				}
		}
	}
}
/*node* LoadFromFile(const string& filename)
{
	node *root=NULL;
	string x;
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
		x=line.substr(begin, i - begin);
		if(root==NULL)root=createnode(x);
		else insert(root,createnode(x));
	}
	cout<<"Dictionary loaded successfully\n";
	return root;
}*/
node* LoadFromFile(const string& filename)
{
	node *root=NULL;
	string x;
	long long int cnt;
	ifstream ifile(filename.c_str());
	while(ifile)
	{
		ifile>>x;
		ifile>>cnt;
		//cout<<x<<' '<<cnt<<endl;
		if(root==NULL)root=createnode(x,cnt);
		else insert(root,createnode(x,cnt));
	}
	cout<<"Dictionary loaded successfully\n";
	return root;
}


