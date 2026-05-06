#include <bits/stdc++.h>

using namespace std;
/*#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}*/
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
#define endl '\n'
#define int long long
const int N=2e5+105;
int sa[N], pos[N], tmp[N], lcp[N];
int st[N][23];
int lg[N];
vector<char>S;
int n, gap;
int m;
int f[N][32];
void maxi(int &x,int y)
{
    x=max(x,y);
}
string s1,s2;
bool sufCmp(int i, int j)
{
    int SZ=S.size();
    if (pos[i] != pos[j])
        return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < SZ && j < SZ) ? pos[i] < pos[j] : i > j;
}

void buildSA()
{
    int SZ=S.size();
    forinc(i,0,SZ-1) sa[i] = i, pos[i] = S[i];
    for (gap = 1;; gap *= 2)
    {
        sort(sa, sa + SZ, sufCmp);
        forinc(i,0,SZ-2)  tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
        forinc(i,0,SZ-1) pos[sa[i]] = tmp[i];
        if (tmp[SZ - 1] == SZ - 1) break;
    }
}

void buildLCP()
{
    int SZ=S.size();
    for (int i = 0, k = 0; i < SZ; ++i) if (pos[i] != SZ - 1)
        {
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
                ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
}
int l[N],r[N],sum[N];
int res=0;
int get(int x,int y)
{
    if (x == y) return S.size() - x;
    int l=pos[x];
    int r=pos[y];
    if(l>r) swap(l,r);
    r--;
    int p=lg[r-l+1];
    return min(st[l][p],st[r-(1<<p)+1][p]);
}
main() {
    fasty;
    forinc(i, 0, N - 1) lg[i] = log2(i);

    string AA;
    cin >> AA;

    S.assign(AA.begin(), AA.end()); // Nạp trực tiếp chuỗi AA vào S

    buildSA();
    buildLCP();

    // Xây dựng Sparse Table cho LCP
    for(int j = 0; (1 << j) <= S.size() - 1; j++) {
        for(int i = 0; i + (1 << j) - 1 <= S.size() - 1; i++) {
            if(!j) st[i][j] = lcp[i];
            else st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    // In mảng Suffix Array
    for (int i = 0; i < S.size(); i++) {
        cout << sa[i] << " ";
    }
    cout << '\n';

    // Ví dụ truy vấn LCP
    cout << get(0, 2) << '\n';
}
