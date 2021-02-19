#include<bits/stdc++.h>
using namespace std;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))
#define off ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;
typedef vector<LL> 		VL;
#define si(n) cin>>n
#define dout(n) cout<<n<<"\n"
#define DRT() int t; si(t); while(t--)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
//# define M_PI           3.14159265358979323846264338327950288
// DSU

void IO(){
	#ifndef ONLINE_JUDGE
    freopen("./input.txt", "r", stdin);
    freopen("./output1.txt", "w", stdout);
	#endif
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	off;
}
const int N = 1e6+1;
vector<int> segtree;
void update(int l, int r, int node, int ind){
	if(l == r){
		segtree[node]++;
		return ;
	}
	int mid = l + (r - l)/2;
	if(ind <= mid)
		update(l, mid, 2*(node), ind);
	else
		update(mid+1, r, 2*node+1, ind);
	segtree[node] = segtree[2*node] + segtree[2*node+1];
}
int query(int l, int r, int lg, int rg, int node){
	if(l > r || r < lg || l > rg)
		return 0;
	if(l >= lg && r <= rg)
		return segtree[node];
	int mid = l + (r - l)/2;
	return query(l, mid, lg, rg, 2*node) + query(mid+1, r, lg, rg, 2*node+1);
}
int main(){
	IO();
	segtree.resize(4*N+4, 0);
	string s;
	getline(cin, s);
	while(!s.empty()){
		istringstream iss(s);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		if(tokens[0][0] == 'I'){
			int x = stoi(tokens[1]);
			update(0, N-1, 1, x);
		}
		else if(tokens[0][0] == 'F'){
			int x = stoi(tokens[1]);
			int res = query(0, N-1, x, x, 1);
			if(res)
				cout<<"YES\n";
			else
				cout<<"NO\n";
		}
		else if(tokens[0][0] == 'C'){
			int x = stoi(tokens[1]);
			int res = query(0, N-1, x, x, 1);
			cout<<res<<"\n";
		}
		else if(tokens[0][0] == 'R'){
			int x = stoi(tokens[1]);
			int y = stoi(tokens[2]);
			int res = query(0, N-1, x, y, 1);
			cout<<res<<"\n";
		}
		else{
			cout<<"Sorry We don't do that Here\n";
		}
		getline(cin, s);
	}
	return 0;
}