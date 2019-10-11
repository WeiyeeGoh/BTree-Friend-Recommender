#ifndef USERTREE_H
#define USERTREE_H
#include "user.h"

struct tNode {
	bool removed;
	bool isRoot;
	bool leaf;   			//if leaf, holds 2 users instead of tNodes
	int userSize;			//number of users [must be at least 1], [max is 2]
	int childSize;			//number of children [min 2], [max 4]
	int keySize;
	tNode* parent;			//pointer to its parent
	
	//Only if interior node
	tNode** children;		//array of pointers to next interior nodes. Max is 4 items
	int* keys;				//holds keys. each key is a perm used to traverse tree

	//Only if leaf
	User* left;				//if leaf, left is required. 	
	User* right;			//right user may or may not exist
	int leftIndex;
	int rightIndex;
};

class UserTree {
public:
	UserTree();
	void insertItem(User* user, int index);
	User* findUser(int perm);
	int findIndex(int perm);
	int findIndexHelper(int perm, tNode* current);
	User* findUserHelper(int perm, tNode* current);
	User* findSmallestUser(tNode* n);
	tNode* findSmallestLeaf(tNode* n);
	void deleteItem(int perm);
	tNode* createLeafNode(User* user, int index);						//create leaf node given inputs. return node.
	tNode* createIntNode(	int size,
							tNode* n1, 
							tNode* n2 = NULL, 
							tNode* n3 = NULL, 
							tNode* n4 = NULL);							//create interior node given inputs. return node.
	//void deleteItem(User& user);										//overloaded version
	void splitIntNodes(tNode* parent, tNode* newLeft, tNode* newRight);
	int heapify(tNode* root);
	void printUser(int perm);
	void print();
	void printNode(tNode* n);
	tNode* root;
private:
	int size;		//number of leaves
	//tNode* root;	//pointer to the root
};

#endif