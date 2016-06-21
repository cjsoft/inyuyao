#include<bits/stdc++.h>
#include"MXPOINT.h" 
using namespace std;
pair<int,int> FINDMXPOINT()
{
	for (int i=1;i<=2000;i++)
	for (int j=1;j<=2000;j++)
		if ((ASK(i,j)>ASK(i-1,j))&&(ASK(i,j)>ASK(i+1,j))&&(ASK(i,j)>ASK(i,j-1))&&(ASK(i,j)>ASK(i,j+1))) return pair<int,int>(i,j);
} 
