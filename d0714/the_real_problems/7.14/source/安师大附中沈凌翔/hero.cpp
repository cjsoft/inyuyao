#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int E=512;
int k,m,n,r[301],t[301][301],v[301][301],ans;
bool tag[301][301];

void work() {
	int g[601][301],z,mn=2000000000;
	register int a,b,c,d,u,w,now=0,next;
	bool used[400001]; queue<int> q;
	memset (used,false,sizeof (used));
	memset (g,-1,sizeof (g));
	for (a=1;a<=n;a++) {
		if (r[1]==a) continue;
		q.push (E+a); g[1][a]=0;
		used[E+a]=true; now++;
	}
	while (now) {
		next=0;
		while (now--) {
			d=q.front (); q.pop (); used[d]=false;
			a=d/E; b=d%E;
			if (a>n) {a-=n; z=1;} else z=0;
			if (z==0) {
				if (!tag[a][b]) {
					u=a+n; c=u*E+b;
					d=g[a][b]+t[a][b];
					if (g[u][b]==-1||d<g[u][b]) {
						g[u][b]=d;
						if (!used[c]) {
							used[c]=true; q.push (c);
							next++;
						}
					}
				} else {
					u=r[a-1]; w=a-1+n; c=w*E+u;
					d=g[a][b]-v[u][b];
					if (g[w][u]==-1||d<g[w][u]) {
						g[w][u]=d;
						if (!used[c]) {
							used[c]=true; q.push (c);
							next++;
						}
					}
				}
			} else {
				u=a+1; w=a+n;
				if (a==n) {
					if (g[w][b]<mn)
						mn=g[w][b];
					continue;
				}
				for (int i=1;i<=m;i++) {
					c=u*E+i;
					d=g[w][b]+v[b][i];
					if (g[u][i]==-1||d<g[u][i]) {
						g[u][i]=d;
						if (!used[c]) {
							used[c]=true; q.push (c);
							next++;
						}
					}
				}
			}
		}
		now=next;
	}
	ans+=mn;
}

int main() {
	freopen ("hero.in","r",stdin);
	freopen ("hero.out","w",stdout);
	int a,b,c,d,f[301][301],l[301][301];
	scanf ("%d %d %d",&n,&m,&k);
	for (a=1;a<=n;a++)
		for (b=1;b<=m;b++)
			scanf ("%d",&t[a][b]);
	for (a=1;a<=m;a++) {
		for (b=a;b<=m;b++)
			v[a][b]=v[b][a]=(b-a)*k;
		l[1][a]=1; f[1][a]=t[1][a];
	}
	for (a=2;a<=n;a++) {
		for (b=1;b<=m;b++) {
			f[a][b]=f[a-1][1]+v[1][b]; l[a][b]=1;
			for (c=2;c<=m;c++) {
				d=f[a-1][c]+v[c][b];
				if (d<f[a][b]) {f[a][b]=d; l[a][b]=c;}
			}
			f[a][b]+=t[a][b];
		}
	}
	for (a=1,c=2000000000;a<=m;a++)
		if (f[n][a]<c) {b=a; c=f[n][a];}
	for (a=n,ans=c;a>=1;tag[a][b]=true,b=l[a--][b]) r[a]=b;
	work (); printf ("%d\n",ans); return 0;
}
