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
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
	#endif
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	off;
}
// val >= key is stored in the right child of that key in the node.
// 2 keys and 3 children
struct Node
{
	int keys[3];
	int freq[3];
	Node * children[4];
	int is_leaf = true;
	Node * next_node;
	int subtree_size[4];
};
Node * root = NULL;

void insert(Node * node, int val){
	return;
}
II find_val(Node * node, int val){
	assert(node != NULL);
	if (node->is_leaf == true){
		if(node->keys[0] == val)
			return MP(1, node->freq[0]);
		else if(node->keys[1] == val)
			return MP(1, node->freq[1]);
		else
			return MP(0, -1);
	}
	if(val < node->keys[0])
		return find_val(node->children[0], val);
	else if(val >= node->keys[0] && val < node->keys[1])
		return find_val(node->children[1], val);
	else
		return find_val(node->children[2], val);
}
int count_val(int val){
	II present = find_val(root, val);
	if(present.F){
		return present.S;
	}
	else
		return 0;
}
// smallest number greater than or equal to val
int find_geq(Node * node, int val){
	assert(root == NULL);
	if(node->is_leaf == true){
		if(node->keys[0] >= val)
			return node->keys[0];
		else if(node->keys[1] >= val)
			return node->keys[1];
		else
			return -1;
	}
	if(val < node->keys[0])
		return find_geq(node->children[0], val);
	else if(val >= node->keys[0] && val < node->keys[1])
		return find_geq(node->children[1], val);
	else
		return find_geq(node->children[2], val);
}
// largest number smaller or equal than val
int find_leq(Node * node, int val){
	assert(root == NULL);
	if(node->is_leaf == true){
		if(node->keys[1] > val)
			return -1;
		if(node->keys[1] <= val)
			return node->keys[1];
		else if(node->keys[0] <= val)
			return node->keys[0];
	}
	if(node->keys[1] <= val)
		return find_leq(node->children[2], val);
	else if(node->keys[0] <= val)
		return find_leq(node->children[1], val);
	else
		return find_leq(node->children[0], val);
}
int range(Node * node, int x, int y){
	return 0;
} 

int main(){
	IO();
	
	return 0;
}