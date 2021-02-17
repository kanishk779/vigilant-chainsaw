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
	int curr_size;
	Node * parent;
	int which_child;
};
// REMEMBER TO DELETE UNUSED NODES
struct ToBeInserted
{
	int val;
	Node * left;
	Node * right;
};
// 1. get a ToBeInserted Node.
// 2. Insert at correct place by shifting others.
// 3. If the size is greater than again split and create a ToBeInserted Node.
// 4. Repeat above 3 steps recursively
Node * root = NULL;

Node * give_node(){
	Node * root = new Node;
	root->curr_size = 1;
	root->is_leaf = true;
	root->next_node = NULL;
	rep(i,0,3){
		root->subtree_size[i] = 0;
		root->children[i] = NULL;
		root->freq[i] = 0;
	}
	root->parent = NULL;
	root->which_child = -1;
	return root;
}
void insert_internal(Node * node, ToBeInserted * ins){
	return;
}
void insert(Node * node, int val){
	if(root == NULL){
		root = give_node();
		root->keys[0] = val;
		root->freq[0] = 1;
		return;
	}
	while(node->is_leaf == false){
		if(val < node->keys[0])
			node = node->children[0];
		else{
			if(node->curr_size == 1)
				node = node->children[1];
			else{
				if(val >= node->keys[0] && val < node->keys[1])
					node = node->children[1];
				else
					node = node->children[2];
			}
		}
	}
	if(node->curr_size == 1){
		if(val == node->keys[0]){
			node->freq[0]++;
		}
		else{
			if(val > node->keys[0]){
				node->keys[1] = val;
				node->freq[1] = 1;
			}
			else{
				swap(node->keys[0], node->keys[1]);
				swap(node->freq[0], node->freq[1]);
				node->keys[0] = val;
				node->freq[0] = 1;
			}
		}
	}
	else{
		if(val == node->keys[0]){
			node->freq[0]++;
		}
		else if(val == node->keys[1]){
			node->freq[1]++;
		}
		else{
			// split and call
			ToBeInserted * ins = new ToBeInserted;
			ins->val = val;
			ins->left = ins->right = NULL;
			insert_internal(node, ins);
		}
	}
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
// [l, r] is covered by current node
int range(Node * node, int x, int y, int l, int r){
	if(x > r || y < l || l > r || node == NULL)
		return 0;
	if(x <= l && r <= y)
		return node->subtree_size[0] + node->subtree_size[1] + node->subtree_size[2];
	LL ans = range(node->children[0], x, y, l, min(r, node->keys[0]-1));
	ans += range(node->children[1], x, y, max(l, node->keys[0]), min(r, node->keys[1]-1));
	ans += range(node->children[2], x, y, max(l, node->keys[1]), r);
	return ans;
} 
LL min_key = 1e9;
LL max_key = -1e9;
int main(){
	IO();
	
	return 0;
}