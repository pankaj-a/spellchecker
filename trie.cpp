#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include "trie.h"
#include "levenshtein.h"

using namespace std;

trie_node *inittrie_node(trie_node *r)
{
trie_node *itrie_node=r;
   for(int i=0;i<256;i++)
     {
    itrie_node->ptr[i]=NULL;
    }
            itrie_node->cnt=0;
            itrie_node->info='\0';
            itrie_node->Word="";

return itrie_node;

}

void insertstring(string word,int pos,trie_node *root,int c)
{
    if(word.length()==pos)
    {
        root->Word=word;
        root->cnt=c;
        return;
    }
    if( root-> ptr[word[pos]]==NULL )
    {
        trie_node *newn;
        newn= new trie_node;
          newn=inittrie_node(newn);
        newn->info=word[pos];
        root->ptr[word[pos]]=newn;
        insertstring(word,pos+1,root->ptr[word[pos]],c);
    }
    else
        insertstring(word,pos+1,root->ptr[word[pos]],c);
}

int find(string key,int pos, trie_node *root)
{
    if((key != root->Word) && (root->ptr[key[pos]] != NULL))
        return find(key,pos+1,root->ptr[key[pos]]);
    else if(key==root->Word)
    {
         cout<<"The spelling of the word '"<<root->Word<<"' is correct"<<endl;
         return 1;
    }
    return 0;
}

/*int DynamicLevenshtein(string s1,string s2)
{
	int i,j;
	int d[s1.size()+1][s2.size()+1];
	d[0][0]=0;
	for(i=1;i<=s1.size();i++)d[i][0]=i;
	for(i=1;i<=s2.size();i++)d[0][i]=i;
	for(i=1;i<=s1.size();++i)
	{
		for(j=1;j<=s2.size();++j)
		{
			if(s1[i-1]==s2[j-1])
			{
				d[i][j]=min(min(d[i-1][j]+1,d[i][j-1]+1),d[i-1][j-1]);
			}
			else
			{
				d[i][j]=min(min(d[i-1][j]+1,d[i][j-1]+1),d[i-1][j-1]+2);
			}
		}
	}
	return d[s1.size()][s2.size()];
}*/

void printcountwise(map<long long int,string> &fin)
{
  std::map<long long int,string>::reverse_iterator rit;


  for (rit=fin.rbegin(); rit!=fin.rend(); ++rit)
    std::cout <<"frquency : "<< rit->first << "   =>   " << rit->second << '\n';

}

void printinsert(trie_node *root,string key,map<long long int,string>&finmap)
{

    for(int i=0;i<256;i++)
        if(root->ptr[i]!=NULL)
        {
         printinsert(root->ptr[i],key,finmap);
        }

    if(root->Word!="" && root->cnt!=0)
   {
       map<long long int,string> mymap;


//POSSIBLE SUGGESTION ADDED TO MAP<COUNT,WORD>
  mymap.insert ( std::pair<long long int,string>(root->cnt,root->Word) );

//       map.insert(pair<int,string>(root->cnt,root->Word));
        /*
        cout<<" -> "<<root->Word<<endl;
        cout<<" -> "<<root->cnt<<endl;
        */
    int x;
       map<long long int,string>::reverse_iterator rit;
       for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
        {
          x=DynamicLevenshtein(key,rit->second);
            //map<int,string> finmap;

            if(x<=4)
            {
            finmap.insert( std::pair<int,string>(rit->first,rit->second) );

           //  cout<<" -> "<<rit->second<<endl;
            // cout<<" -> "<<rit->first<<endl;
            }
        }
   }

}

void printall(trie_node *root)
{
    for(int i=0;i<256;i++)
        if(root->ptr[i]!=NULL)
        {

            printall(root->ptr[i]);
        }

    if(root->Word!="" && root->cnt!=0)
   {
        cout<<" -> "<<root->Word<<endl;
        cout<<" -> "<<root->cnt<<endl;
   }

}

void suggestword(string key,int pos,trie_node *root,map<long long int,string>&finmap)
{
    if((key != root->Word) && (root->ptr[key[pos]] != NULL))
    {
            suggestword(key,pos+1,root->ptr[key[pos]],finmap);

    }//   (key=root->Word) && (root->ptrs[key[pos]] == NULL)
    else
    {
            printinsert(root,key,finmap);
    }

}
