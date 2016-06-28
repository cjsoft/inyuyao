#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=head[x];i!=-1;i=ne[i])
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int,int> pin;
#define mk(a,b) make_pair(a,b)
#define lowbit(x) ((x)&(-(x)))
#define sqr(a) ((a)*(a))
#define clr(a) (memset((a),0,sizeof(a)))
#define ls ((x)<<1)
#define rs (((x)<<1)|1)
#define mid (((l)+(r))>>1)
#define pb push_back
#define w1 first
#define w2 second
inline void read(int &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
inline void judge(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
}
/*******************************head*******************************/
FILE *fin,*fout,*fans,*fmes,*fsco;
int score,n,m;
const double eps=1e-6;
inline void close()
{
	fclose(fin);fclose(fout);fclose(fans);
	fclose(fmes);fclose(fsco);
}
void Invalid()
{
	fprintf(fmes,"Invalid output");
	fprintf(fsco,"%d",0);
	close();exit(0);
}
inline void AC(int mjy)
{
	fprintf(fmes,"Right Answer! %d Right Lines",mjy);
	fprintf(fsco,"%d",20);
	close();exit(0);
}
void Right(int mjy)
{
	double zxo=mjy*0.5-27.5;
	fprintf(fmes,"Acceptable Answer! %d Right Lines",mjy);
	fprintf(fsco,"%d",(int)floor(zxo+eps));
	close();exit(0);
}
void Mid(int mjy)
{
	double zxo=mjy*0.2-2;
	fprintf(fmes,"Acceptable Answer! %d Right Lines",mjy);
	fprintf(fsco,"%d",(int)floor(zxo+eps));
	close();exit(0);
}
void Left(int mjy)
{
	double zxo=mjy*2.0/15.0+7.0/3.0;
	fprintf(fmes,"Acceptable Answer! %d Right Lines",mjy);
	fprintf(fsco,"%d",(int)floor(zxo+eps));
	close();exit(0);
}
void Orz(int mjy)
{
	double zxo=mjy*2.0/17.0+49.0/17.0;
	fprintf(fmes,"Acceptable Answer! %d Right Lines",mjy);
	fprintf(fsco,"%d",(int)floor(zxo+eps));
	close();exit(0);
}
void WA()
{
	fprintf(fmes,"Wrong Answer! 0 Right Lines");
	fprintf(fsco,"%d",0);
	close();exit(0);
}
int mjy=0;
void check()
{
	fscanf(fin,"%d",&m);
	for (int i=1;i<=100;i++)
	{
		bool zxo=true;
		for (int j=1;j<=m;j++)
		{
			char std,src;
			fscanf(fans,"%c",&std);
			while (std!='V' && std!='C')	fscanf(fans,"%c",&std);
			if (fscanf(fout,"%c",&src)==EOF)	Invalid();
			while (src!='V' && src!='C')
			if (fscanf(fout,"%c",&src)==EOF)	Invalid();
			if (std!=src)	zxo=false;
		}
		if (zxo)	mjy++;
	}
}
int main(int argc,char* argv[])
{
	//judge();
	fin=fopen(argv[1],"r");
	fout=fopen(argv[2],"r");
	fans=fopen(argv[3],"r");
	score=atoi(argv[4]);
	fsco=fopen(argv[5],"w");
	fmes=fopen(argv[6],"w");
	check();
	if (mjy>=95)	AC(mjy);
	if (mjy>=85)	Right(mjy);
	if (mjy>=65)	Mid(mjy);
	if (mjy>=35)	Left(mjy);
	if (mjy>=1)	Orz(mjy);
	WA();
	return 0;
}
