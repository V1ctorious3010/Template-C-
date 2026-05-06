#include <bits/stdc++.h>
using namespace std;
// #define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x; })
#define fasty ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define getbit(x, i) ((x >> (i)) & 1)
#define batbit(x, i) (x | (1ll << (i)))
#define tatbit(x, i) (x & ~(1 << (i)))
#define endl '\n'
#define int long long
#define forinc(x, a, b) for (int x = a; x <= b; x++)
#define fordec(x, a, b) for (int x = a; x >= b; x--)
const int N=1e6+10;
string str;
int n;
struct node
{
    int open,close;
    //open so ngoac mo thua
    //close so ngoac dong thua
    node operator+(node b)
    {
        node res;
        int t=min(open,b.close);
        res.open=open+b.open-t;
        res.close=close+b.close-t;
        return res;
    }
} T[4*N];
void build(int s,int l,int r)
{
    if(l>r) return;
    if(l==r)
    {
         if(str[l]=='(') T[s]={1,0};
         else T[s]={0,1};
         return;
    }
    int mid=(l+r)/2;
    build(s*2,l,mid);
    build(s*2+1,mid+1,r);
    T[s]=T[s*2]+T[s*2+1];
}
node get(int s,int l,int r,int u,int v)
{
    if(l>v||r<u)  return {0,0};
    if(l>=u&&r<=v)  return T[s];
    int mid=(l+r)/2;
    return get(s*2,l,mid,u,v)+get(s*2+1,mid+1,r,u,v);
}
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>str;
    n=str.size();
    str=" "+str;
    build(1,1,n);
    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        node ans=get(1,1,n,l,r);
        cout<<r-l+1-ans.open-ans.close<<endl;
    }
}
