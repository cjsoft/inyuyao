#include<bits/stdc++.h>
#include"MXPOINT.h" 
using namespace std;
//int ask(int x,int y)
int mp[2010][2010];
int ask(int x,int y)
{
	if (mp[x][y]) return mp[x][y];
	else if ((x<1)||(x>2000)||(y<1)||(y>2000)) return mp[x][y]=-1; 
	return mp[x][y]=ASK(x,y);
}
bool check(int x,int y)
{
	if (ask(x,y)<=ask(x,y+1)) return false;
	if (ask(x,y)<=ask(x,y-1)) return false;
	if (ask(x,y)<=ask(x-1,y)) return false;
	if (ask(x,y)<=ask(x+1,y)) return false;
	return true;
}
pair<int,int> find(int lx,int rx,int ly,int ry)
{
	//cout<<lx<<' '<<rx<<' '<<ly<<' '<<ry<<endl;
	for (int i=lx;i<=rx;i++)
	for (int j=ly;j<=ry;j++)
	{
		if ((ask(i,j)>ask(i-1,j))&&(ask(i,j)>ask(i+1,j))&&(ask(i,j)>ask(i,j-1))&&(ask(i,j)>ask(i,j+1))) return pair<int,int>(i,j);
	}
	assert(0);
}
pair<int,int> FINDMXPOINT()
{
	memset(mp,0,sizeof(mp)); 
	return find(1,2000,1,2000);
} 
