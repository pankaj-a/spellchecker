#include "levenshtein.h"

int DynamicLevenshtein(string s1,string s2)//wagner-fischer
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
				d[i][j]=min(min(d[i-1][j]+1,d[i][j-1]+1),d[i-1][j-1]+1);
			}
		}
	}
	return d[s1.size()][s2.size()];
}

