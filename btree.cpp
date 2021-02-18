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
	int freq[3]; // matters only at leaf nodes
	Node * children[4]; // child pointers
	int is_leaf = true;
	Node * next_node; // next node, matters only at leaf node.
	int subtree_size[4]; // stores number of keys associated with each of the child pointers
	int curr_size; // how many keys are present in a node.
	Node * parent; // parent of this Node, NULL for root
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
// 3. If the size of the b+tree node is greater than again split and create a ToBeInserted Node.
// 4. Repeat above 3 steps recursively
Node * root = NULL;

Node * give_node(){
	Node * root = new Node;
	root->curr_size = 1;
	root->is_leaf = false;
	root->next_node = NULL;
	rep(i,0,3){
		root->subtree_size[i] = 0;
		root->children[i] = NULL;
		root->freq[i] = 0;
	}
	root->parent = NULL;
	return root;
}
int give_size(Node * node){
	if(node == NULL)
		return 0;
	if(node->curr_size == 1){
		return node->subtree_size[0] + node->subtree_size[1];
	}
	else
		return node->subtree_size[0] + node->subtree_size[1] + node->subtree_size[2];
}
void insert_internal(Node * node, ToBeInserted * ins){
	if(node == NULL){
		// create a new root node
		root = give_node();
		root->keys[0] = ins->val;
		root->children[0] = ins->left;
		root->children[1] = ins->right;
		root->subtree_size[0] = give_size(ins->left);
		root->subtree_size[1] = give_size(ins->right);
		return;
	}
	if(node->curr_size == 1){
		if(ins->val < node->keys[0]){
			node->children[2] = node->children[1];
			node->subtree_size[2] = node->subtree_size[1];
			node->children[1] = ins->right;
			node->subtree_size[1] = give_size(ins->right);
			node->children[0] = ins->left;
			node->subtree_size[0] = give_size(ins->left);
		}
		else{
			node->children[1] = ins->left;
			node->subtree_size[1] = give_size(ins->left);
			node->children[2] = ins->right;
			node->subtree_size[2] = give_size(ins->right);
		}
		node->curr_size++;
	}
	else{
		// find the position where this node to be inserted will actually be inserted
		if(ins->val < node->keys[0]){
			// insert at the start at index -> 0
			for(int i=3;i>=2;i--){
				node->children[i] = node->children[i-1];
				node->subtree_size[i] = node->subtree_size[i-1];
			}
			node->children[0] = ins->left;
			node->subtree_size[0] = give_size(ins->left);
			node->children[1] = ins->right;
			node->subtree_size[1] = give_size(ins->right);
		}
		else if(ins->val > node->keys[0] && ins->val < node->keys[1]){
			// insert at index -> 1
			node->children[3] = node->children[2];
			node->subtree_size[3] = node->subtree_size[2];
			node->children[2] = ins->right;
			node->subtree_size[2] = give_size(ins->right);
			node->children[1] = ins->left;
			node->subtree_size[1] = give_size(ins->left);
		}
		else{
			// insert at index -> 2
			node->children[3] = ins->right;
			node->subtree_size[3] = give_size(ins->right);
			node->children[2] = ins->left;
			node->subtree_size[2] = give_size(ins->left);
		}
		// create two new nodes (leftc and rightc)
		Node * leftc = give_node();
		Node * rightc = give_node();
		leftc->children[0] = node->children[0];
		leftc->subtree_size[0] = node->subtree_size[0];
		leftc->children[1] = node->children[1];
		leftc->subtree_size[1] = node->subtree_size[1];
		leftc->keys[0] = node->keys[0];

		rightc->children[0] = node->children[2];
		rightc->subtree_size[0] = node->subtree_size[2];
		rightc->children[1] = node->children[3];
		rightc->subtree_size[1] = node->subtree_size[3];
		rightc->keys[0] = node->keys[2];

		if(node->is_leaf){
			leftc->next_node = rightc; // for the leaf nodes there should be pointer to the next b+tree node
		}
		// prepare next "ToBeInserted" node for recursive call
		ToBeInserted * next_ins = new ToBeInserted;
		next_ins->val = node->keys[1]; // the second key in this node will be promoted upwards towards the parent
		next_ins->left = leftc;
		next_ins->right = rightc;
		insert_internal(node->parent, next_ins);
		// delete this node because this is not needed
		delete node;
	}
	return;
}
void insert(Node * node, int val){
	if(root == NULL){
		root = give_node();
		root->keys[0] = val;
		root->freq[0] = 1;
		root->is_leaf = true;
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
	if(node->curr_size == 1){
		if(val < node->keys[0])
			return find_val(node->children[0], val);
		else
			return find_val(node->children[1], val);
	}
	else{
		if(val < node->keys[0])
			return find_val(node->children[0], val);
		else if(val >= node->keys[0] && val < node->keys[1])
			return find_val(node->children[1], val);
		else
			return find_val(node->children[2], val);
	}
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
		return give_size(node);
	LL ans = range(node->children[0], x, y, l, min(r, node->keys[0]-1));
	ans += range(node->children[1], x, y, max(l, node->keys[0]), min(r, node->keys[1]-1));
	ans += range(node->children[2], x, y, max(l, node->keys[1]), r);
	return ans;
} 
LL min_key = 1e9;
LL max_key = -1e9;
int main(){
	IO();
	string s;
	getline(cin, s);
	while(!s.empty()){
		istringstream iss(s);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		if(tokens[0][0] == 'I'){
			
		}
		else if(tokens[0][0] == 'F'){

		}
		else if(tokens[0][0] == 'C'){

		}
		else if(tokens[0][0] == 'R'){

		}
		else{
			cout<<"Sorry We don't do that Here\n";
		}
		getline(cin, s);
	}
	return 0;
}