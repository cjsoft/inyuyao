/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define ALL(X)       X.begin(),X.end()
#define FOR(I,A,B)   for(int (I) = (A); (I) <= (B); (I)++)
#define FORW(I,A,B)  for(int (I) = (A); (I) < (B);  (I)++)
#define FORD(I,A,B)  for(int (I) = (A); (I) >= (B); (I)--)
#define CLEAR(X)     memset(X,0,sizeof(X))
#define SIZE(X)      int(X.size())
#define CONTAIN(A,X) (A.find(X) != A.end())
#define PB           push_back
#define MP           make_pair
#define X            first
#define Y            second
using namespace std;
typedef signed long long slong;
typedef long double ldouble;
const slong Infinity = 1000000100;
const ldouble Epsilon = 1e-9;
template<typename T, typename U> ostream& operator << (ostream& os, const pair<T,U>&p) { return os << "(" << p.X << "," << p.Y << ")"; }
template<typename T> ostream& operator << (ostream &os, const vector<T>& V) { os << "["; FORW(i,0,SIZE(V)) os << V[i] << ((i==SIZE(V)-1) ? "" : ","); return os << "]"; }
template<typename T> ostream& operator << (ostream &os, const set<T>& S) {os << "("; for(T i: S) os << i << (i==*S.rbegin()?"":","); return os << ")"; }
template<typename T, typename U> ostream& operator << (ostream &os, const map<T, U>& M){os << "{"; for(pair<T,U> i: M) os << i << (i.X==M.rbegin()->X?"":","); return os << "}"; }
template<typename T, typename F> T lbound(T p, T q, F f) { while(p < q) { T r = p+(q-p)/2; if(f(r)) q = r; else p = r+1; } return p; }
template<typename T, typename F> T lboundl(T p, T q, F f) { FOR(i,1,70) { T r = (p+q)/2; if(f(r)) q = r; else p = r; } return p; }

const int N=50042;
typedef pair<int,int> pii;
vector<pii> d, q;
int ans[2*N], git[2*N];
int Q, n;
vector<int> v[N];

int dzieli(pii x, pii y)
{
    int a=min(x.X,x.Y), b=max(x.X,x.Y);
    int c=min(y.X,y.Y), dd=max(y.X,y.Y);
    if(b<c || dd<a) return 0;
    if(a<c && dd < b) return 0;
    if(c<a && b<dd) return 0;
    return 1;
}

vector<int> dists(int x)
{
    vector<int> ret(n+1, Infinity);
    ret[x]=0;
    queue<int> qq;
    qq.push(x);
    while(qq.size())
    {
        int cur=qq.front();
        qq.pop();
        for(int nxt : v[cur])
        {
            if(ret[cur]+1<ret[nxt])
            {
                ret[nxt]=ret[cur]+1;
                qq.push(nxt);
            }
        }
    }
    return move(ret);
}

int rr[N], vis[N];
int cnt=1;

int dist(int x, int y)
{
    rr[x]=0;
    vis[x]=cnt;
    queue<int> qq;
    qq.push(x);
    while(qq.size())
    {
        int cur=qq.front();
        qq.pop();
        if (cur == y) break;
        for(int nxt : v[cur])
        {
            if(vis[nxt]!=cnt || rr[cur]+1<rr[nxt])
            {
                vis[nxt]=cnt;
                rr[nxt]=rr[cur]+1;
                qq.push(nxt);
            }
        }
    }
    cnt++;
    return rr[y];
}

int main()
{
    ios_base::sync_with_stdio(0);

    cin>>n;
    FOR(i,1,n-3)
    {
        pii a;
        cin>>a.X>>a.Y;
        d.PB(a);
        v[a.X].PB(a.Y);
        v[a.Y].PB(a.X);
    }

    FORW(i,1,n)
    {
        v[i].PB(i+1);
        v[i+1].PB(i);
    }
    v[1].PB(n);
    v[n].PB(1);

    cin>>Q;
    FOR(i,1,Q)
    {
        pii a;
        cin>>a.X>>a.Y;
        q.PB(a);
    }

    //cout<<"\nwut\n";

    random_shuffle(ALL(d));


    FORW(i,0,min(SIZE(d),100))
    {
        pii cur=d[i];
        //cout<<"cur "<<cur<<endl;
        auto dx=dists(cur.X), dy=dists(cur.Y);
        FORW(j,0,Q)
        {
            if(dzieli(cur,q[j]))
            {
                git[j]=1;
                //cout<<"solve "<<q[j]<<dx[q[j].X]<<" "<<dx[q[j].Y]
                    //<<" "<<dy[q[j].X]<<" "<<dy[q[j].Y]<<endl;
                ans[j]=min(dx[q[j].X]+dx[q[j].Y], dy[q[j].X] + dy[q[j].Y]);
            }
        }
    }

    FORW(i,0,Q)
    {
        if(!git[i])
        {
            //cout<<"obsluga "<<q[i]<<endl;
            auto dx=dists(q[i].X);
            ans[i]=dx[q[i].Y];
        }
    }

    FORW(i,0,Q) cout<<ans[i]<<"\n";

	return 0;
}
