# vigilant-chainsaw
B+Tree

## How to execute this code
```
g++ -std=c++11 btree.cpp
./a.out input.txt
```

## Explanation regarding algorithm
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

