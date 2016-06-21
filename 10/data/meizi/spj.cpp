#include<bits/stdc++.h>
using namespace std;
FILE *fin, *fout, *fans, *fsco, *fmsg;
void score(int s, const char *message) {
	fprintf(fsco,"%d\n",s);
	fprintf(fmsg,"%s\n",message);
	exit(0);
}
int main(int argc, char **argv)
{
	fsco=fopen(argv[5], "w");
	fmsg=fopen(argv[6], "w");
	fout=fopen(argv[2], "r");
	//fmsg = fopen(argv[5], "w");  // message output file (can be NULL)
	//fout = fopen(argv[2], "r");  // contestant output file (data*.out)
	//freopen(argv[2],"r",stdin);  // contestant output file (data*.out)
	//freopen(argv[5],"w",stdout);
	if (fout == NULL) score(0,"File not found");
	int ans=0;
	for (int i=1;i<=20;i++)
	{
		int ths;
		fscanf(fout,"%d",&ths);
		if (ths==-1) score(0,"Wrong answer");
		if (ths==-2) score(0,"Too many queries");
		ans=max(ans,ths);
	}
	if (ans<=6050) score(100,(ans==0)?"papapa":"100");
	if (ans<=16050) score(70,"70");
	if (ans<=48050) score(50,"50");
	if (ans<=180050) score(30,"30");
	if (ans<=4000050) score(10,"10");
	score(0,"too many queries");
}
