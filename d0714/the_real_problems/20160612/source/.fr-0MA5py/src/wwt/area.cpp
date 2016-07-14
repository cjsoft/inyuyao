#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
#include <iostream>

using namespace std;

const int MAXN = 5005;

typedef long long LL;

struct Node
{
	LL x,y;

	Node(void){}
	Node(LL a,LL b) : x(a),y(b){}

}Po[MAXN],Cur[MAXN];

Node operator +(const Node &a,const Node &b) {return Node(a.x + b.x,a.y + b.y);}
Node operator -(const Node &a,const Node &b) {return Node(a.x - b.x,a.y - b.y);}
LL operator ^(const Node &a,const Node &b) {return a.x * b.y - a.y * b.x;}
LL operator *(const Node &a,const Node &b) {return a.x * b.x + a.y * b.y;}

map<pair<int,int>,bool> Hash;
LL ans,Best[MAXN];
int N,Stack[MAXN],Stack2[MAXN];

bool cmp(const Node &a,const Node &b) {return a.x < b.x || a.x == b.x && a.y < b.y;}

LL Area(const int &a,const int &b,const int &c)
{
	return abs((Cur[b].x - Cur[a].x) * (Cur[c].y - Cur[a].y) - (Cur[b].y - Cur[a].y) * (Cur[c].x - Cur[a].x));
}

int main()
{
	freopen("area.in","r",stdin),freopen("area.out","w",stdout);
	scanf("%d", &N);
	for(int i = 1;i <= N;i ++)
	{
		int x,y;
		scanf("%d%d", &x, &y);
		if (Hash[make_pair(x,y)]) i --,N --; else
		{
			Hash[make_pair(x,y)] = 1;
			Po[i] = Node(x,y);
		}
	}
	sort(Po + 1,Po + N + 1,cmp);
	for(int o = 1;o <= N;o ++)
	{
		int tot = 0;
		for(int i = o;i <= N;i ++)
			if (Po[i].x > Po[o].x || Po[i].x == Po[o].x && Po[i].y >= Po[o].y) Cur[++ tot] = Po[i];
		int top = 1;
		Stack[1] = 1;
		for(int i = 2;i <= tot;i ++)
		{
			for(;top > 1 && ((Cur[Stack[top]] - Cur[Stack[top - 1]]) ^ (Cur[i] - Cur[Stack[top]])) >= 0;top --);
			Stack[++ top] = i;
		}
		int top2 = 1;
		Stack2[top2] = 1;
		for(int i = 2;i <= tot;i ++)
		{
			for(;top2 > 1 && ((Cur[Stack2[top2]] - Cur[Stack2[top2 - 1]]) ^ (Cur[i] - Cur[Stack2[top2]])) <= 0;top2 --);
			Stack2[++ top2] = i;
		}
		for(int i = top2 - 1;i;i --) Stack[++ top] = Stack2[i];
		for(int i = 1;i <= top;i ++) Best[i] = 0;
		for(int i = 1,j = 1;i <= top;i ++)
		{
			for(;j + 1 < i && Area(Stack[1],Stack[j + 1],Stack[i]) > Area(Stack[1],Stack[j],Stack[i]);j ++);
			Best[i] = Area(Stack[1],Stack[j],Stack[i]);
			ans = max(ans,Best[i]);
		}
		for(int i = top,j = top;i;i --)
		{
			for(;j - 1 > i && Area(Stack[1],Stack[j - 1],Stack[i]) > Area(Stack[1],Stack[j],Stack[i]);j --);
			ans = max(ans,Best[i] + Area(Stack[1],Stack[j],Stack[i]));
		}
	}
	if (ans & 1) cout << ans / 2,printf(".5\n"); else
		cout << ans / 2,printf(".0\n");
	return 0;
}
