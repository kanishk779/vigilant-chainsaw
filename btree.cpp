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
    freopen("./output.txt", "w", stdout);
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
Node * split_left = NULL;
Node * split_right = NULL;

Node * give_node(){
	Node * root = new Node;
	root->curr_size = 1;
	root->is_leaf = false;
	root->next_node = NULL;
	rep(i,0,4){
		root->subtree_size[i] = 0;
		root->children[i] = NULL;
	}
	rep(i,0,3){
		root->freq[i] = 0;
	}
	root->parent = NULL;
	return root;
}
int give_size(Node * node){
	if(node == NULL)
		return 0;
	if(node->is_leaf){
		return node->freq[0] + node->freq[1];
	}
	if(node->curr_size == 1){
		return node->subtree_size[0] + node->subtree_size[1];
	}
	else
		return node->subtree_size[0] + node->subtree_size[1] + node->subtree_size[2];
}
void recalculate_subtree_sizes(Node * node){
	// update the subtree sizes for all ancestors
	// cout<<"recalculate_subtree_sizes\n";
	while(node->parent != NULL){
		rep(i,0,3){
			assert(node != NULL);
			node->parent->subtree_size[i] = give_size(node->parent->children[i]);
		}
		node = node->parent;
	}
}
void insert_internal(Node * node, ToBeInserted * ins){
	// cout<<"trying to insert "<<ins->val<<"\n";
	if(node == NULL){
		// create a new root node
		// cout<<"creating new root\n";
		root = give_node();
		root->keys[0] = ins->val;
		root->children[0] = ins->left;
		root->children[1] = ins->right;
		// cout<<"left val "<<ins->left->keys[0]<<"\n";
		// cout<<"right val "<<ins->right->keys[0]<<"\n";
		// cout<<"right size "<<ins->right->curr_size<<"\n";
		root->children[0]->parent = root;
		root->children[1]->parent = root;
		root->subtree_size[0] = give_size(ins->left);
		root->subtree_size[1] = give_size(ins->right);
		return;
	}
	// cout<<"curr_size for node is "<<node->curr_size<<"\n";
	// cout<<"first key of node is "<<node->keys[0]<<"\n";
	if(node->curr_size == 1){
		// cout<<"current node size is one(insert_internal)\n";
		if(ins->val < node->keys[0]){
			// cout<<"insert at index 0\n";
			node->children[2] = node->children[1];
			node->subtree_size[2] = node->subtree_size[1];
			node->children[1] = ins->right;
			node->subtree_size[1] = give_size(ins->right);
			node->children[0] = ins->left;
			node->subtree_size[0] = give_size(ins->left);
			node->keys[1] = node->keys[0];
			node->keys[0] = ins->val;
		}
		else{
			// cout<<"insert at index 1\n";
			node->children[1] = ins->left;
			node->subtree_size[1] = give_size(ins->left);
			node->children[2] = ins->right;
			node->subtree_size[2] = give_size(ins->right);
			node->keys[1] = ins->val;
		}
		node->curr_size++;
	}
	else{
		// find the position where this node to be inserted will actually be inserted
		if(ins->val < node->keys[0]){
			// insert at the start at index -> 0
			// cout<<"inserting at index 0\n";
			for(int i=2;i>=1;i--){
				node->keys[i] = node->keys[i-1]; // shift the keys
			}
			if(node->is_leaf){
				for(int i=2;i>=1;i--){
					node->freq[i] = node->freq[i-1]; // shift the freq
				}
				node->freq[0] = 1;
			}
			for(int i=3;i>=2;i--){
				node->children[i] = node->children[i-1];
				node->subtree_size[i] = node->subtree_size[i-1];
			}
			node->subtree_size[0] = give_size(ins->left);
			node->subtree_size[1] = give_size(ins->right);
			node->children[0] = ins->left;
			node->children[1] = ins->right;
			node->keys[0] = ins->val;  // Assign the new value to be inserted
		}
		else if(ins->val > node->keys[0] && ins->val < node->keys[1]){
			// insert at index -> 1
			// cout<<"inserting at index 1\n";
			node->children[3] = node->children[2];
			node->subtree_size[3] = node->subtree_size[2];
			node->children[2] = ins->right;
			node->subtree_size[2] = give_size(ins->right);
			node->children[1] = ins->left;
			node->subtree_size[1] = give_size(ins->left);
			
			if(node->is_leaf){  // update freq if the node is a leaf
				node->freq[2] = node->freq[1];
				node->freq[1] = 1;
			}
			node->keys[2] = node->keys[1];
			node->keys[1] = ins->val;
		}
		else{
			// insert at index -> 2
			// cout<<"inserting at index 2\n";
			node->children[3] = ins->right;
			node->subtree_size[3] = give_size(ins->right);
			node->children[2] = ins->left;
			node->subtree_size[2] = give_size(ins->left);
			node->keys[2] = ins->val;
			if(node->is_leaf)
				node->freq[2] = 1;
		}
		// create two new nodes (leftc and rightc)
		Node * leftc = give_node();
		Node * rightc = give_node();
		rep(i,0,2){
			leftc->children[i] = node->children[i];
			leftc->subtree_size[i] = node->subtree_size[i];
		}
		leftc->keys[0] = node->keys[0];

		if(node->is_leaf){
			// cout<<"The node split is leaf node\n";
			leftc->is_leaf = true;
			rightc->is_leaf = true;
			leftc->freq[0] = node->freq[0];

			rep(i,0,2){
				rightc->keys[i] = node->keys[i+1]; // the middle key will also be part of the right child for leaf
				rightc->freq[i] = node->freq[i+1];
			}
			rightc->curr_size = 2;
			leftc->next_node = rightc; // for the leaf nodes there should be pointer to the next b+tree node
			split_left = leftc;
			split_right = rightc;
		}
		else{
			rep(i,0,2){
				rightc->children[i] = node->children[i+2];
				rightc->subtree_size[i] = node->subtree_size[i+2];
			}
			rightc->keys[0] = node->keys[2];
		}
		// adjust the parent pointers (new parents will be alloted)
		leftc->parent = node->parent;
		rightc->parent = node->parent;
		rep(i,0,4){
			if(leftc->children[i] != NULL){
				leftc->children[i]->parent = leftc;
			}
			if(rightc->children[i] != NULL){
				rightc->children[i]->parent = rightc;
			}
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
		// cout<<"root is NULL\n";
		root = give_node();
		root->keys[0] = val;
		root->freq[0] = 1;
		root->is_leaf = true;
		return;
	}
	// cout<<"going to leaf\n";
	assert(node != NULL);
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
		assert(node != NULL);
	}
	// cout<<"reach leaf\n";
	if(node->curr_size == 1){
		// cout<<"leaf size is one\n";
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
			node->curr_size++;
		}
		split_left = node;
	}
	else{
		// cout<<"leaf size is two\n";
		if(val == node->keys[0] || val == node->keys[1]){
			// cout<<"duplicate entry\n";
			if(val == node->keys[0]){
				node->freq[0]++;
				// cout<<"new size "<<node->freq[0]<<"\n";
			}
			else if(val == node->keys[1]){
				node->freq[1]++;
				// cout<<"new size "<<node->freq[1]<<"\n";
			}
			split_left = node;
		}
		else{
			// split and call
			// cout<<"splitting and call\n";
			ToBeInserted * ins = new ToBeInserted;
			ins->val = val;
			ins->left = ins->right = NULL;
			assert(node != NULL);
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
void dfs(Node * node, int d){
	string s((size_t) 4*d, ' ');
	if(node != NULL){
		// cout<<s;
		// cout<<"sub[0] : "<<node->subtree_size[0]<<"\n";
		cout<<s;
		cout<<node->keys[0]<<"\n";
		// cout<<s;
		// cout<<"sub[1] : "<<node->subtree_size[1]<<"\n";
		dfs(node->children[0], d+1);
		dfs(node->children[1], d+1);
		if(node->curr_size == 2){
			cout<<s;
			cout<<node->keys[1]<<"\n";
			// cout<<s;
			// cout<<"sub[2] : "<<node->subtree_size[2]<<"\n";
			dfs(node->children[2], d+1);
		}
	}
}
// subtree_size[0] -> stores the frequency of node->keys[0] in the leaf (because it does not have any subtree)
// I could have created another variable for it so that it will be easy to understand.
// [l, r] is covered by current node
int range(Node * node, int x, int y, int l, int r, int d=0){
	string s((size_t) 4*d, ' ');
	if(x > r || y < l || l > r || node == NULL)
		return 0;
	// cout<<s;
	// cout<<l<<" "<<r<<"\n";
	if(x <= l && r <= y)
		return give_size(node);
	LL ans = 0;
	if(node->is_leaf){
		rep(i,0,2)
		if(node->keys[i] >= x && node->keys[i] <= y)
			ans += node->freq[i];
		return ans;
	}
	ans += range(node->children[0], x, y, l, min(r, node->keys[0]-1), d+1);
	if(node->curr_size == 1){
		ans += range(node->children[1], x, y, max(l, node->keys[0]), r, d+1);
	}
	else{
		ans += range(node->children[1], x, y, max(l, node->keys[0]), min(r, node->keys[1]-1), d+1);
		ans += range(node->children[2], x, y, max(l, node->keys[1]), r, d+1);
	}
	return ans;
} 
int min_key = 1e9;
int max_key = -1e9;
int main(){
	IO();
	string s;
	getline(cin, s);
	while(!s.empty()){
		// cout<<s<<"\n";
		istringstream iss(s);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		if(tokens[0][0] == 'I'){
			int x = stoi(tokens[1]);
			split_right = split_left = NULL;
			min_key = min(min_key, x);
			max_key = max(max_key, x);
			insert(root, x);
			if(split_left != NULL)
				recalculate_subtree_sizes(split_left);
			if(split_right != NULL)
				recalculate_subtree_sizes(split_right);
			// dfs(root, 0);
		}
		else if(tokens[0][0] == 'F'){
			int x = stoi(tokens[1]);
			II res = find_val(root, x);
			if(res.F){
				cout<<"f\n";
			}
			else
				cout<<"nf\n";
		}
		else if(tokens[0][0] == 'C'){
			int x = stoi(tokens[1]);
			cout<<count_val(x)<<"\n";
		}
		else if(tokens[0][0] == 'R'){
			int x = stoi(tokens[1]);
			int y = stoi(tokens[2]);
			int ans = range(root, x, y, min_key, max_key);
			cout<<ans<<"\n";
		}
		else{
			cout<<"Sorry We don't do that Here\n";
		}
		getline(cin, s);
	}
	return 0;
}