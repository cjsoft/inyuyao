#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int a,b,c,k,l[30],r[30],n,t,cnt;
int f[2][30];
struct node {
	int x,y;
}v[30];

int cmp(const void *a,const void *b) {
	if ((*(node *)a).x==(*(node *)b).x) {
		if ((*(node *)a).y<(*(node *)b).y) return -1;
		return 1;
	}
	if ((*(node *)a).x<(*(node *)b).x) return 1;
	return -1;
}

int cmp1(const void *a,const void *b) {
	if ((*(node *)a).y==(*(node *)b).y) {
		if ((*(node *)a).x<(*(node *)b).x) return -1;
		return 1;
	}
	if ((*(node *)a).y<(*(node *)b).y) return 1;
	return -1;
}

int main() {
	freopen ("assign.in","r",stdin);
	freopen ("assign.out","w",stdout);
	scanf ("%d",&n);
	for (a=1;a<=n;a++) scanf ("%d",&l[a]);
	for (a=1;a<=n;a++) scanf ("%d",&r[a]);
	scanf ("%d",&k); t=10000000/n;
	while (t--) {
		for (a=1;a<=n;a++) {
			v[a].x=(rand ()%(r[a]-l[a]+1))+l[a];
			v[a].y=a;
		}
		qsort (v+1,n,sizeof (node),cmp);
		qsort (v+1,k,sizeof (node),cmp1);
		for (a=1,b=1,c=0;a<=k;a++,b++) {
			if (b==2) {b=0; c^=1;}
			f[c][v[a].y]++;
		}
		cnt++;
	}
	for (a=1;a<=n;a++) {
		if (f[0][a]==0) printf ("0.000000 "); else printf ("%lf ",(double)f[0][a]/cnt);
		if (f[1][a]==0) printf ("0.000000\n"); else printf ("%lf\n",(double)f[1][a]/cnt);
	}
	return 0;
}
