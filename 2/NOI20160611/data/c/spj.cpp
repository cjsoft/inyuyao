#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

FILE *fin,*fout,*fstd,*fsrc;
int n,m;
long double a[5010][5010],x[5010],U;

long double calc(FILE *f)
{
    long double ret=0;
    for (int i=1;i<=n;++i)
        if (fscanf(f,"%Lf",x+i)!=1)
            {printf("0\n"); exit(0);}
    for (int i=1;i<=m;++i)
    {
        long double tmp=0;
        for (int j=1;j<=n;++j)
            tmp+=x[j]*a[i][j];
        ret+=1.0L*(tmp-a[i][n+1])*(tmp-a[i][n+1]);
    }
    return ret;
}

int main(int argc,char **argv)
{
    fin=fopen(argv[1],"r");
    fout=fopen(argv[2],"r"); fstd=fopen(argv[3],"r");
		fsrc=fopen(argv[5],"w");
    if (!fin||!fout||!fstd) {fprintf(fsrc,"0\n"); return 0;}
    fscanf(fin,"%d%d%Lf",&m,&n,&U);
    for (int i=1;i<=m;++i)
        for (int j=1;j<=n+1;++j)
            fscanf(fin,"%Lf",&a[i][j]);
    long double Nout=calc(fout),Nstd=calc(fstd);
    fprintf(stderr,"your answer: %.6Lf\n std answer: %.6Lf\n",Nout,Nstd);
    Nout=logl(Nout+1.0L); Nstd=logl(Nstd+1.0L);
		fprintf(stderr,"%.3Lf\n",Nout);
		fprintf(stderr,"%.3Lf\n",Nstd);
    if (Nout>U) fprintf(fsrc,"0\n");
    else if (Nout<Nstd) fprintf(fsrc,"10\n");
    else fprintf(fsrc,"%d\n",(int)(10.0*(U-Nout)/(U-Nstd)));
    return 0;
}
