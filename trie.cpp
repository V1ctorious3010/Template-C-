#include <bits/stdc++.h>
using namespace std;

#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define forinc(x,a,b) for(int x=a;x<=b;x++)
#define fordec(x,a,b) for(int x=a;x>=b;x--)
#define iii pair<ii,int>
#define fi first
#define se second
#define ii pair<int,int>
#define getbit(x,i) ((x>>(i))&1ll)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1ll<<(i)))
#define endl '\n'
//#define int long long
#define pb push_back
const int N=3e6+10;
int T;
int L,R,a[N];
int nxt[N][2];
int it=0;
void add(int x)
{
    int cur=0;
    for(int bit=16;bit>=0;bit--)
    {
        int val=getbit(x,bit);
        if(!nxt[cur][val])   nxt[cur][val]=++it;
        cur=nxt[cur][val];
    }
}
int mi(int cur,int x,int bit)
{
    if(bit<0) return 0;
    int val=getbit(x,bit);
    if(nxt[cur][val])    return mi(nxt[cur][val],x,bit-1);
    return (1<<bit)+mi(nxt[cur][1-val],x,bit-1);
}
int ma(int cur,int x,int bit)
{
    if(bit<0) return 0;
    int val=getbit(x,bit);
    if(nxt[cur][1-val])  return (1<<bit)+ma(nxt[cur][1-val],x,bit-1);
    return ma(nxt[cur][val],x,bit-1);
}
void solve()
{
        for(int i=1;i<=R-L+1;i++)
        {
            int x=a[i]^L;
            if(mi(0,x,16)==L&&ma(0,x,16)==R)
            {
                cout<<x<<endl;
                return;
            }
        }
}
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>T;
    while(T--)
    {
        cin>>L>>R;
        for(int i=1;i<=R-L+1;i++)
        {
            cin>>a[i];
            add(a[i]);
        }
        solve();
        for(int i=0;i<=it;i++)   nxt[i][0]=nxt[i][1]=0;
        it=0;
    }
}

