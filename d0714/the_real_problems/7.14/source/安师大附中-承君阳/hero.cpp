#include<bits/stdc++.h>
#define M make_pair
#define A(u,v,f,c) e[++t]=v,g[t]=h[u],w[t]=f,l[t]=c,h[u]=t,e[++t]=u,g[t]=h[v],l[t]=-c,h[v]=t
#define N 666666
using namespace std;
int h[N],e[N],g[N],l[N],w[N],t=1,n,m,k,T=N-1,S,f[N],d[N],O=1<<30,i,j,x;
set<pair<pair<int,int>,int> >E;
int F()
{
	for(E.insert(M(M(0,0),0)),i=1;i<N;i++)d[i]=O;
	while(!E.empty())for(x=(*E.begin()).second,E.erase(E.begin()),i=h[x];i;i=g[i])if(w[i]&&d[x]+l[i]<d[j=e[i]])
		E.erase(M(M((j-1)/m,d[j]),j)),E.insert(M(M((j-1)/m,d[j]=d[x]+l[f[j]=i]),j));
	for(S+=d[i=T];i;i=e[j])w[j=f[i]]--,w[j^=1]++;
}
main()
{
	for(freopen("hero.in","r",stdin),freopen("hero.out","w",stdout),cin>>n>>m>>k,i=0;i<n;i++)for(j=1;j<=m;j++)
		scanf("%d",&x),j<m?A(i*m+j,i*m+j+1,O,k),A(i*m+j+1,i*m+j,O,k):0,A(i?i*m-m+j:0,i*m+j,1,x),!i?A(n*m-m+j,T,1,0):0;
	F();F();cout<<S;
}//23333
