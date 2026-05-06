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
#define forv(a,b) for(auto&a:b)
#define fi first
#define se second
#define pb push_back
#define ll long long
#define ii pair<int,int>
#define mt make_tuple
#define all(a) a.begin(),a.end()
#define reset(f,x) memset(f,x,sizeof(f))
#define getbit(x,i) ((x>>(i))&1)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1<<(i)))
#define gg exit(0);
#define debug(x) cerr << #x << " is " << x << "\n";
#define int long long
const int N=1*1e6+100;
vector<int>ke[N];
int low[N];
int num[N];
int scc[N];
int cnt=0;
int dp[N];
int n,m;
bool deleted[N];
int timedfs=0;
stack<int>st;
bool dd[N];
vector<ii>adj[N];
vector<ii>ke1[N];
void dfs(int u)
{
    low[u]=num[u]=++timedfs;
    st.push(u);
    for(auto v:ke[u])
    {
        if(deleted[v]) continue;
        if(!num[v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else low[u]=min(low[u],num[v]);
    }
    if(num[u]==low[u])
    {
        int v;
        cnt++;
        do
        {

            v=st.top();
            st.pop();
            deleted[v]=1;
            scc[v]=cnt;


        }
        while(v!=u);
    }
}

int calc(int Z)
{
    int ans=0;
    int l=1;
    int r=1e6;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(mid*(mid+1)/2<=Z)
        {
            ans=mid;
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
    }
   if(ans==0)  return 0;
   return (ans + 1) * Z -ans * (ans + 1) * (ans + 2) / 6;
}
vector<int>topo;
int f[N];
void dfs2(int u)
{
    dd[u]=1;
    for(auto v:adj[u])
    {
        if(!dd[v.fi])
        {
            dfs2(v.fi);
        }
    }
    topo.pb(u);

}
int s;
int val[N];
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>n>>m;
    forinc(i,1,m)
    {
        int u,v,w;
        cin>>u>>v>>w;
        ke[u].pb(v);
        //
        ke1[u].pb({v,w});
    }
    cin>>s;
    forinc(i,1,n)
    {
        if(!num[i])
        {
            dfs(i);
        }
    }
    forinc(i,1,n)
    {
        forv(j,ke1[i])
        {
            if(scc[i]==scc[j.fi])
            {
                val[scc[i]]+=calc(j.se);
            }
            else adj[scc[i]].pb({scc[j.fi],j.se});
        }
    }
    //forinc(i,1,cnt)  cout<<val[i]<< " ";
    //exit(0);
    //forinc(i,1,n)  cout<<dd[i];
    forinc(i,1,cnt)
    {
        if(!dd[i])
        {
            dfs2(i);
        }
    }
    forinc(i,1,cnt)  f[i]=val[i];
    forinc(i,0,topo.size()-1)
    {
        int u = topo[i];
        //cout<<u<< " "<<val[u]<< " ";
        forv(v,adj[u])
        {
            f[u] = max(f[u],f[v.fi] + val[u] + v.se);
           // cout<<"ngu";
        }
    }
   // cout<<scc[s]<< " "<<f[1]<<endl;
    cout<<f[scc[s]];


}

