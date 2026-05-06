#include <bits/stdc++.h>
using namespace std;
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x; })
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r)
{
    return l + rng() % (r - l + 1);
}
#define fasty ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define forinc(x, a, b) for (int x = a; x <= b; x++)
#define fordec(x, a, b) for (int x = a; x >= b; x--)
#define forv(a, b) for (auto &a : b)
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define mt make_tuple
#define reset(f, x) memset(f, x, sizeof(f))
#define getbit(x, i) ((x >> i) & 1)
#define batbit(x, i) (x | (1 << i))
#define tatbit(x, i) (x & ~(1 << i))
#define int long long
#define all(v) v.begin(), v.end()
#define gg exit(0)
const int N = 3e5 + 100;
#define endl "\n"
// #define int long long
int n,m,id[N],num[N],low[N],Time,cnt,f[N];
vector<ii>ke[N],adj[N];
stack<int>sta;
int st,ed;
void dfs(int u,int pre=0)
{
    num[u]=low[u]=++Time;
    sta.push(u);
    for(auto [v,w]:ke[u]) if(v!=pre)
        {
            if(!num[v])
            {
                dfs(v,u);
                low[u]=min(low[u],low[v]);
            }
            else low[u]=min(low[u],num[v]);
        }
    if(low[u]==num[u])
    {
        int v;
        cnt++;
        do
        {
            v=sta.top();
            sta.pop();
            id[v]=cnt;
        }
        while (v!=u);
    }
}
void dfs2(int u,int pa)
{
    for(auto [v,w]:adj[u])
    {
        if(v!=pa)
        {
            f[v]+=f[u]+w;
            dfs2(v,u);
        }
    }
}
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>n>>m;
    forinc(i,1,m)
    {
        int u,v,w;
        cin>>u>>v>>w;
        ke[u].pb({v,w});
        ke[v].pb({u,w});
    }
    cin>>st>>ed;
    dfs(st,-1);

    forinc(i,1,n)
    {
        for(auto [v,w]:ke[i])
        {
            if(id[i]!=id[v])
            {
                adj[id[i]].pb({id[v],w});
                //adj[id[v]].pb({id[i],w});
            }
            else f[id[i]]+=w;
        }
    }
    dfs2(id[st],-1);
    if(!f[id[ed]])     cout<<"NO";
    else cout<<"YES";
}
