#include <bits/stdc++.h>
using namespace std;
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define forinc(x,a,b) for(int x=a;x<=b;x++)
#define fordec(x,a,b) for(int x=a;x>=b;x--)
#define iii pair<ii,int>
#define fi first
#define se second
#define pb push_back
#define ll long long
#define ii pair<int,int>
#define mt make_tuple
#define getbit(x,i) ((x>>(i))&1)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1<<(i)))
#define endl '\n'
#define gg exit(0);
const int N=500000+100;
int n,m,it;
int par[N] , T[4*N] , lazy[4*N] , st[N] , ed[N];
vector<int> ke[N];

void dfs(int u, int pr)
{
    st[u]=++it;
    for(auto v : ke[u])
    {
        if(v == pr) continue;
        par[v]=u;
        dfs(v,u);
    }
    ed[u]=it;
}
void push(int s ,int l , int r)
{
    int t = lazy[s];
    if(t > 0)
    {
        if(l < r)
        {
            T[2*s]+=t;
            T[2*s +1]+=t;
            lazy[2*s]+=t;
            lazy[2*s +1]+=t;
        }
    }
    lazy[s] = 0;
}
void update(int s, int l, int r, int u , int v, int val)
{
    if(l > v || u > r) return;
    if(u<=l && r <= v)
    {
        T[s] = val;
        lazy[s]=val;
        return;
    }
    push(s,l,r);
    int mid = (l+r) /2;
    update(2*s , l , mid , u , v , val);
    update(2*s +1 , mid+1 , r , u , v , val);
    T[s] = min(T[2*s] , T[2*s+1]);
}

int get(int s, int l, int r , int u , int v)
{
    if(l > v || u > r) return 1e9;
    if(u<=l && r <= v)
    {
        return T[s];
    }
    push(s,l,r);
    int mid = (l+r) /2;
    return min(get(2*s,l,mid,u,v),get(2*s+1,mid+1,r,u,v));
}

main()
{

    fasty;
    cin >> n;
    forinc(i,1,n-1)
    {
        int u,v;
        cin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
    int q;
    cin >> q;
    dfs(1,0);
    forinc(i,1,q)
    {
        int typ,v;
        cin >> typ >> v;
        if(typ==1)
        {
            if (get(1,1,n,st[v],ed[v])==0)
            {
                int u=par[v];
                if(u) update(1,1,n,st[u],st[u],0);
            }
            update(1,1,n,st[v],ed[v],1);
        }
        if(typ==2) update(1,1,n,st[v],st[v],0);
        if(typ==3) cout<<(get(1,1,n,st[v],ed[v])==0?0:1)<<"\n";
    }
}

