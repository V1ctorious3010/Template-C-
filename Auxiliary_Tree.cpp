#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
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
const int N = 1e5 + 100;
int P[N][22], in[N], out[N], a[N], dd[N], mark[N];
int res=0;
int n,m,q,it;
int lg;
vector<int> ke[N];
vector<int> tree[N]; //vector ke cua cay ao
// cay ao gom nhung nut quan trong da cho va cac nut cha de ket noi cac nut nay
bool cmp(int a, int b)
{
    return in[a] < in[b];
}
void dfs(int u, int par)
{
    in[u]=++it;
    forinc( i,1,lg )   P[u][i]=P[P[u][i-1]][i-1];
    for(auto v:ke[u])
    {
        if(v==par) continue;
        P[v][0]=u;
        dfs(v,u);
    }
    out[u]=it;
}

bool anc(int u,int v)
{
    if(in[u]<=in[v]&&out[u]>=out[v]||(!u)) return 1;
    return 0;
}
bool ok=1;
int lca(int u, int v)
{
    if(anc(u,v)) return u;
    if(anc(v,u)) return v;
    fordec(i, lg, 0 ) if(!anc(P[u][i], v)) u = P[u][i];
    return P[u][0];
}
int calc(int u)
{
    int cnt=0;
    for(auto v : tree[u])
    {
        if(dd[u])
        {
            if(dd[v]&&P[v][0]==u) ok=0;
            res+=calc(v);
        }
        else cnt+=calc(v);
    }
    if(dd[u]||cnt==1) return 1;
    if(cnt>1) res++;
    return 0;
}
void solve()
{
    ok=1;
    int k;
    cin >> k;
    forinc(i,1,k)
    {
        cin >> a[i];
        dd[a[i]]=1;
        mark[a[i]]=1;
    }
    sort(a+1,a+k+1, cmp);
    forinc(i,1,k-1)
    {
        int tmp = lca(a[i], a[i+1]);
        if(!mark[tmp])
        {
            a[++k] = tmp;
            mark[tmp]=1;
            tree[tmp].clear();
        }
    }
    sort(a+1,a+k +1, cmp);
    stack<int> stt;
    stt.push(a[1]);
    forinc(i,2,k)
    {
        while(out[stt.top()]<out[a[i]]) stt.pop();
        tree[stt.top()].pb(a[i]);
        stt.push(a[i]);
    }
    res=0;
    calc(a[1]);
    if(!ok)   cout<<-1<<endl;
    else cout << res << "\n";
    forinc(i,1,k)
    {
        dd[a[i]]=0;
        mark[a[i]]=0;
        tree[a[i]].clear();
    }
}
int main()
{
    //freopen("task.inp", "r", stdin);
    fasty;
    cin >> n;
    lg = log2(n);
    forinc(i,1,n-1)
    {
        int u,v;
        cin >> u >> v;
        ke[u].pb(v);
        ke[v].pb(u);
    }
    dfs(1,0);
    cin >> m;
    forinc(_,1,m)
    {
        solve();
    }


}
