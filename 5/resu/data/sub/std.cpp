#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;
typedef long long LL;

const int maxn=3000100;
struct node{
    node *ch[26],*f;
    int len,cnt,ip;
}*init,*tail,pool[maxn],*st[maxn];int cnode;

node *nn(int l){
    node *a=pool+(cnode++);
    memset(a,0,sizeof(node));
    a->len=l; return a;
}

void add(int c,int l){
    node *np=nn(l),*p=tail;tail=np;
    for(;p&&!p->ch[c];p=p->f)p->ch[c]=np;
    if(!p)np->f=init;
    else{
        if(p->len+1==p->ch[c]->len)np->f=p->ch[c];
        else{
            node *q=p->ch[c],*r=nn(0);
            *r=*q;r->len=p->len+1;
            np->f=q->f=r;
            for(;p&&p->ch[c]==q;p=p->f)p->ch[c]=r;
        }
    }
}

char s[maxn];
LL ans;
LL ac,len;
void jisuan(int n){
    int tp=0;
    node *p=init;
    for(int i=0;i<n;++i){ p=p->ch[s[i]-'a']; ++p->cnt; }
    for(int i=1;i<cnode;++i)++pool[i].f->ip;
    for(int i=1;i<cnode;++i)if(!pool[i].ip)st[++tp]=pool+i;
    while(tp){
        node *p=st[tp--]; if(!p->f)continue;
        p->f->cnt+=p->cnt;
        if(!--p->f->ip)st[++tp]=p->f;

        LL now=LL(p->cnt)*p->len;
        if(p->cnt>1 && now>ans){
            ans=now;
            ac=p->cnt;len=p->len;
        }
    }
}

int main() {
    init=tail=nn(0); scanf("%s",s); int n=strlen(s);
    for(int i=0;i<n;++i)add(s[i]-'a',i+1); ans=-1;
    jisuan(n);
    printf("%lld\n",ans);
    fprintf(stderr,"CNT %lld LEN %lld\n",ac,len);
}
