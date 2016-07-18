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
	if ((rx-lx<=3)&&(ry-ly<=3))
	{
		for (int i=lx;i<=rx;i++)
		for (int j=ly;j<=ry;j++)
		{
			if ((ask(i,j)>ask(i-1,j))&&(ask(i,j)>ask(i+1,j))&&(ask(i,j)>ask(i,j-1))&&(ask(i,j)>ask(i,j+1))) return pair<int,int>(i,j);
		}
		assert(0);
	}
	int mxed=0,idx,idy;
	for (int i=lx-1;i<=rx+1;i++)
	for (int j=ly-1;j<=ry+1;j++)
	{
		if (((int)((i>=lx)&&(i<=rx)))+((int)(j>=ly)&&(j<=ry))==2) continue;
		if (ask(i,j)>mxed)
		{
			mxed=ask(i,j);
			idx=i;idy=j;
		}
	}
	if (rx-lx+1>ry-ly+1)
	{
		int mid=(lx+rx)>>1;
		int mx=0;
		for (int i=ly;i<=ry;i++) mx=max(mx,ask(mid,i));
		if (mx<mxed)
		{
			if (idx<mid) return find(lx,mid-1,ly,ry);
			else if (idx==mid) assert(0);
			else return find(mid+1,rx,ly,ry);
		}
		for (int i=ly;i<=ry;i++) if (mx==ask(mid,i))
		{
			int p1=ask(mid-1,i),p2=ask(mid+1,i);
			if (check(mid,i)) return make_pair(mid,i);
			else if ((p1>mx)&&(mx>p2)) return find(lx,mid-1,ly,ry);
			else if ((p2>mx)&&(mx>p1)) return find(mid+1,rx,ly,ry);
			else assert(0); 
		}
	}
	else
	{
		int mid=(ly+ry)>>1;
		int mx=0;
		for (int i=lx;i<=rx;i++) mx=max(mx,ask(i,mid));
		if (mx<mxed)
		{
			if (idy<mid) return find(lx,rx,ly,mid-1);
			else if (idy==mid) assert(0);
			else return find(lx,rx,mid+1,ry);
		}
		for (int i=lx;i<=rx;i++) if (mx==ask(i,mid))
		{
			int p1=ask(i,mid-1),p2=ask(i,mid+1);
			if (check(i,mid)) return make_pair(i,mid);
			else if ((p1>mx)&&(mx>p2)) return find(lx,rx,ly,mid-1);
			else if ((p2>mx)&&(mx>p1)) return find(lx,rx,mid+1,ry);
			else assert(0);
		}
	}
}
pair<int,int> FINDMXPOINT()
{
	memset(mp,0,sizeof(mp)); 
	return find(1,2000,1,2000);
} 
