# vigilant-chainsaw
B+Tree
This was a project done as part of Data-Systems (Advanced DBMS) course in 6th
Semester. The objective was to learn how the index structures help in answering 
range queries in database system by implementing a B+Tree. 

## How to execute this code
```
python3 testGenerator.py
g++ -std=c++11 btree.cpp
./a.out input.txt
```

## To Verify
To verify that the code produces correct results, we can run the segtree.cpp.
Running it will generate output1.txt, which can be later used by checker.py .
```
g++ -std=c++11 btree.cpp
./a.out input.txt
g++ -std=c++11 segtree.cpp
./a.out
python3 checker.py
```
The output of checker.py tells the number of total queries and how many lines
are not matching with segtree output.
NOTE : the numbers inserted in btree and segtree must be in **range [1, 1e6]**
otherwise segtree's output is wrong but that of btree's output is correct, and
we should not compare with segtree.

## Explanation regarding algorithm
### Structures
```
// 2 keys and 3 children
struct Node
{
	int keys[3];
	int freq[3]; // stores the frequency of keys ( only useful at leaf nodes )
	Node * children[4]; // child pointers
	int is_leaf = true;
	Node * next_node; // next node, matters only at leaf node.
	int subtree_size[4]; // stores number of keys associated with each of the child pointers
	int curr_size; // how many keys are present in a node.
	Node * parent; // parent of this Node, NULL for root
};

struct ToBeInserted
{
	int val;
	Node * left;
	Node * right;
};
```
### Insert
This is the most challenging function to implement.
1. Check if the root is NULL, if it is allocate a new root and insert the
   number.
2. Now since we know that root is not NULL, we traverse down the b+tree to find
   the appropriate the node in which the number will be inserted.
3. If the node is not full, we will simply insert the number at its correct
   place in sorted order and mark it's frequency = 1.
4. If the number is a duplicate just increase it's frequency.
5. If it is full than we need to split the node for this purpose ToBeInserted
   struct is used.
6. This struct represents an element which is to be inserted in some node. It
   contains a left and right pointers of type Node and a number (Integer).


### Insert Internal
This is the recursive method for splitting nodes of type Node and inserting ToBeInserted
nodes.
1. If the node in which some number is to be inserted is NULL, that means we
   need to create a new **root** node.
2. If the number of keys in the node is 1, which means there is space for the
   new number to be inserted. So we insert it at correct place in sorted order.
3. Else we know that the current Node is full, hence we need to split. But
   before that we will put the **ToBeInserted** node at the correct place in
   sorted order.
4. Children pointers and subtree_size values need to be shifted in some cases.
5. After this we create two new Nodes, since we need to further split this node.
6. If the node that is going to be split is a leaf node than the right Node
   created in above step will have two keys, otherwise it will have only one
   key. 
7. A new **ToBeInserted** Node is created with it's left and right pointers set
   to the newly created left and right Nodes. And it's val will be set to the
   number which is the 2nd key of the node being split.


### Range
This is a recursive function which gives the number of element in range [x, y]
both inclusive.
1. The initial range is the [min, max] where min is the minimum key inserted
   till now and max is maximum key.
2. If there is no overlap between the current range and given range [x, y] then
   return 0.
3. Else if the current range is completely inside the given range [x, y] then
   return the number of keys in this range.
4. Else call this function on children pointers.
5. If a leaf is reached than check how many keys are within the given range.
