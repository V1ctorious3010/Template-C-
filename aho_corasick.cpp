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
#define eb emplace_back
struct node{
	int link = -1, slink = -1, p = -1;
	char ch;
	int nxt[26], go[26];
	vector <int> Leaf;
	node(int p = -1, char ch = ' ') : p(p), ch(ch) {
		for(int i = 0; i < 26; i++)
		{
			nxt[i] = -1;
			go[i] = -1;
		}
	}
};

int n;
int sz[100005], k[100005];
string s, t;
vector <int> Nice[100005];

vector <node> Trie(1);

void Add(string s, int id)
{
	int root = 0;
	for(auto x : s)
	{
		int temp = x - 'a';
		if(Trie[root].nxt[temp] == -1)
		{
			Trie[root].nxt[temp] = Trie.size();
			Trie.eb(root, x);
		}
		root = Trie[root].nxt[temp];
	}
	Trie[root].Leaf.eb(id);
}

int go(int root, char ch);

int get_link(int root)
{
	if(Trie[root].link == -1)
	{
		if(root == 0 or Trie[root].p == 0)
		{
			Trie[root].link = 0;
		}
		else
		{
			Trie[root].link = go(get_link(Trie[root].p), Trie[root].ch);
		}
	}
	return Trie[root].link;
}

int go(int root, char ch)
{
	int c = ch - 'a';
	if(Trie[root].go[c] == -1)
	{
		if(Trie[root].nxt[c] != -1)
		{
			Trie[root].go[c] = Trie[root].nxt[c];
		}
		else
		{
			Trie[root].go[c] = root == 0 ? 0 : go(get_link(root), ch);
		}
	}
	return Trie[root].go[c];
}

int get_suffix_link(int root)
{
	if(Trie[root].slink == -1)
	{
		int temp = get_link(root);
		if(temp == 0 or root == 0)
		{
			Trie[root].slink = 0;
		}
		else if(Trie[temp].Leaf.size() > 0)
		{
			Trie[root].slink = temp;
		}
		else
		{
			Trie[root].slink = get_suffix_link(temp);
		}
	}
	return Trie[root].slink;
}

void go_suffix(int v, int i)
{
	while(v)
	{
		for(auto x : Trie[v].Leaf)
		{
			Nice[x].eb(i - sz[x] + 1);
		}
		v = get_suffix_link(v);
	}
}

main()
{
    fasty;
    //freopen("task.inp", "r", stdin);
	cin >> s;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> t;
		sz[i] = t.size();
		Add(t, i);
	}
	int root = 0, len = s.length();
	for(int i = 0; i < len; i++)
	{
		root = go(root, s[i]);
		go_suffix(root, i);
	}
	for(int i = 1; i <= n; i ++){
        cout << i << " : ";
        for(auto v: Nice[i]){
            cout << v << " ";
        }
        cout << endl;
	}
}
