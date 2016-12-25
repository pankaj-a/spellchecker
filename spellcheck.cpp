//Spell checker submitted as Algorithm Lab Project
//By Gaurav Yadav B7 14103216
//	 Pankaj Ahuja B7 14103235
//	 Pragesh Trivedi B7 14103239
//	 Shaurya Rastogi B7 14103241

#include<ctime>
#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include "hashtables.h"
#include "bktree.h"
#include "bloomfilter.h"
#include "levenshtein.h"
#include "trie.h"

using namespace std;

typedef unordered_map<string,long long int> dictionary;


int main()
{
	clock_t start,end;
	double time_used;
	//c++ stl hash tables
	dictionary d; 
	map<long long int,string>candidates;
	vector<string>edits;
	string word;
	cout<<"This is using C++ STL Hash Tables(unordered_map)\n\n";
	dictionary::iterator it;
	start=clock();
	LoadFromFile("cleaned_dict.txt",d);
	end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"Time taken to load the dictionary "<<time_used<<" seconds\n\n";
	cout<<"Enter word ";
	cin>>word;
	if(d.find(word)!=d.end())
		cout<<"correct spelling"<<endl;
	else
	{	
		start=clock();
		GenerateEdits(edits,d,word);
		GenerateCandidates(edits,d,candidates);
		DisplayResult(candidates);
		end=clock();
		time_used=((double) (end - start)) / CLOCKS_PER_SEC;
		cout<<"\nTime taken taken to suggest words by C++ Hash tables "<<time_used<<" seconds\n\n";
	}

	//c++ stl hash tables ends
	
	//bktree
	
	cout<<"This is using Burkhard-Keller Trees\n\n";
	node *root;
	string x;
	map<unsigned long long int,string>result;
	set<string>result_strings;
	start=clock();
	root=LoadFromFile("cleaned_dict.txt");	
	end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"Time taken to load the dictionary "<<time_used<<" seconds\n\n";
	//cout<<root->value<<endl;
	cout<<"Enter word ";
	cin>>x;
	start=clock();
	GenerateResult(root,x,((x.length())/5+1),result,result_strings);
	if(result_strings.find(x)!=result_strings.end())cout<<"Correct word\n";
	else{
	cout<<"Did you mean\n";
	for(map<unsigned long long int,string>::reverse_iterator rit=result.rbegin();rit!=result.rend();++rit)
	{
		cout<<rit->first<<' '<<rit->second<<endl;
	}
	}
	end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"\nTime taken to suggest words "<<time_used<<" seconds\n\n";
	
	//bktree ends
	
	//bloomfilter
	
	cout<<"This is using bloomfilter\n\n";
	bloomfilter filter;
	vector<string>edits1;
	vector<string>answer;
	start=clock();
	filter.n=createbitarray(filter);
	end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"Time taken to load the dictionary "<<time_used<<" seconds\n";
	filter.m=5300000;
	filter.k=11;
	cout<<"Enter word ";
	cin>>x;
	start=clock();
	if(check(filter,x))cout<<"Word present"<<endl;
	else
	{
		cout<<"Word not present"<<endl;
		GenerateEdits(edits1,x);
		GenerateCandidates(edits1,filter,answer);
		DisplayResult(answer);
	}
	end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"\nTime taken to suggest words "<<time_used<<" seconds\n\n";
	
	//bloomfilter ends
	
	//trie
	
	cout<<"This is using Trie"<<endl;
	long long int c;
	map<long long int,string> finmap;
    string key;
    int counter=0;
    trie_node *trie_root;
    start=clock();
    trie_root = new trie_node;	
    trie_root=inittrie_node(trie_root);
    ifstream in("cleaned_dict.txt");
  	//string str;
    while(in)
    {
        in>>word;
        in>>c;
        //cout<<word<<endl;
       	insertstring(word,0,trie_root,c);
	}
    in.close();
    cout<<endl<<"Trie Construction Successful\n\n";
    end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"Time taken to load dictionary "<<time_used<<" seconds\n";
    

    //printall(root);//jab zyada words trie mei insert kare toh ye hata dio.....tim e kam lagega !


    cout<<"Enter the word to be searched for : ";
    cin>>key;
	start=clock();
    counter=find(key,0,trie_root);

    if(!counter)
    {
        cout<<endl<<"The spelling is incorrect, Possible suggestions are :"<<endl;

        suggestword(key,0,trie_root,finmap);
        printcountwise(finmap);
    }
    end=clock();
	time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"\nTime taken to suggest words "<<time_used<<" seconds\n";
	//trie ends
}
