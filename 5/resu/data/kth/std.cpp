#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;

const int maxn=100900,B=450;
const int MXV=100010;
int a[maxn],s[maxn];
int tmp[maxn],tc;
int bs[maxn];
void quicksort(int *arr,int left,int right){
    int min = (left+right)>>1;
    int i = left;
    int j = right;
    int pivot = arr[min];
    while(left<j || i<right) {
        while(arr[i]<pivot) i++;
        while(arr[j]>pivot) j--;
        if(i<=j){
            swap(arr[i],arr[j]);
            i++; j--;
        }
        else{
            if(left<j) quicksort(arr, left, j);
            if(i<right) quicksort(arr,i,right);
            return;
        }
    }
}
int fastUBD(int *arr,int N,int v){
    int L=0,R=N-1,ans=N;
    while(L<=R){
        int mid=(L+R)>>1;
        if(arr[mid]<=v) L=mid+1;
        else R=(ans=mid)-1;
    }
    return ans;
}

void beforePartUpdate(int bid){
    int *xa=a+bid*B;
    int *xs=s+bid*B;
    for(int i=0;i<B;++i) xs[i]=xa[i]+=bs[bid]; bs[bid]=0;
}
void afterPartUpdate(int bid){
    int *xs=s+bid*B;
    //sort(xs,xs+B);
    quicksort(xs,0,B-1);
}
int check(int LB,int RB,int k,int vv){
    for(int i=LB;i<=RB;++i){
        int *xs=s+i*B;
        //k-=upper_bound(xs,xs+B,vv-bs[i])-xs;
        k-=fastUBD(xs,B,vv-bs[i]);
        if(k<=0)return 1;
    }
    //k-=upper_bound(tmp,tmp+tc,vv)-tmp;
    k-=fastUBD(tmp,tc,vv);
    return k<=0;
}

int main() {
    int n,st=0; scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d",a+i); s[i]=a[i];
        if(i%B == B-1){
            //sort(s+st,s+i+1);
            quicksort(s,st,i);
            st=i+1;
        }
    }
    int q;scanf("%d",&q);
    while(q--){
        int t,L,R,x;
        scanf("%d%d%d%d",&t,&L,&R,&x); --L; --R;
        if(t==1){
            int LB=L/B,RB=R/B;
            if(LB==RB){
                beforePartUpdate(LB);
                for(int i=L;i<=R;++i) s[i]=a[i]+=x;
                afterPartUpdate(LB);
            }else{
                for(int i=LB+1;i<RB;++i)bs[i]+=x;
                beforePartUpdate(LB);
                beforePartUpdate(RB);
                for(int i=L;i<(LB+1)*B;++i) s[i]=a[i]+=x;
                for(int i=RB*B;   i<=R;++i) s[i]=a[i]+=x;
                afterPartUpdate(LB);
                afterPartUpdate(RB);
            }
        }else{
            int LB=L/B,RB=R/B; tc=0;
            if(LB==RB){
                for(int i=L;i<=R;++i)tmp[tc++]=a[i]+bs[LB];
                nth_element(tmp,tmp+x-1,tmp+tc);
                printf("%d\n",tmp[x-1]);
            }else{
                for(int i=L;i<(LB+1)*B;++i) tmp[tc++]=a[i]+bs[LB];
                for(int i=RB*B;   i<=R;++i) tmp[tc++]=a[i]+bs[RB];
                //sort(tmp,tmp+tc);
                quicksort(tmp,0,tc-1);
                int L=0,R=MXV+MXV,ans=INT_MAX;
                while(L<=R){
                    int mid=(L+R)>>1;
                    if(check(LB+1,RB-1,x,mid-MXV)) {
                        R=(ans=mid)-1;
                    }else{
                        L=mid+1;
                    }
                }
                printf("%d\n",ans-MXV);
            }
        }
    }
    return 0;
}
