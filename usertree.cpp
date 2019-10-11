//.cpp
#include <iostream>
#include "usertree.h"

UserTree::UserTree() {
	this->size = 0;
	this->root = NULL;
}

void UserTree::insertItem(User* user, int index) {
	bool rootDilemnaSolved = false;
	if(this->size == 0) {
		//We are inserting first item here
		//TODO: change this->size more. Only have it done here.

		tNode* tempLeaf = createLeafNode(user, index);
		this->root = createIntNode(1, tempLeaf);
		this->size = 1;
		return;
	} else {
		tNode* cur_node = root;
		// TODO: change childSize to reflect keySize instead
		while(!cur_node->leaf) {
			if(user->getPerm() >= cur_node->keys[cur_node->keySize - 1]) {
				//std::cout << "PERM was: " << user->getPerm() << " and LAST KEY was: " << cur_node->keys[cur_node->childSize-1] << std::endl;
				cur_node = cur_node->children[cur_node->keySize];
			} else {

				for(int i = 0; i < cur_node->keySize; i++) {
					if(user->getPerm() < cur_node->keys[i]) {
						if(cur_node->children[i] == NULL) {
							rootDilemnaSolved = true;
							cur_node->children[i] = createLeafNode(user, index);
							cur_node->children[i]->parent = cur_node;
							cur_node->childSize++;
							return;
						} else {
							cur_node = cur_node->children[i];
						}
						break;
					}
				}

			}
		}

		if(!rootDilemnaSolved) {		//basically, if we are in the root weird condition, children[0] is null which fucks up the code hard.
									//The code up there will do an easy insert in that situation so we just skip everything here if that happens;
			//Only dealing with adding to leafs here. May have to abstract into a function and recurse backwards
			if(cur_node->userSize == 1) {		//if current tNode is a leaf with 1 user,
				if(cur_node->left->getPerm() <= user->getPerm()) {
					cur_node->right = user;		//should always be this.
					cur_node->rightIndex = index;
				} else {
					cur_node->right = cur_node->left;
					cur_node->rightIndex = cur_node->leftIndex;
					cur_node->left = user;
					cur_node->leftIndex = index;
				}

				cur_node->userSize = 2;			//set size to 2 so it is now full

			} else if (cur_node->userSize == 2) {
				//This part splits the leaves into 2
				tNode* tempLeft = createLeafNode(cur_node->left, cur_node->leftIndex);
				tNode* tempRight = createLeafNode(cur_node->right, cur_node->rightIndex);
				cur_node->removed = true;									//must remove cur_node so parent knows its being replaced

				//This block adds user to the right location. Either tempLeft or tempRight, left or right side depending on perm comparison
				if(user->getPerm() > tempRight->left->getPerm()) {
					tempRight->right = user;
					tempRight->rightIndex = index;
					tempRight->userSize++;
				} else if (user->getPerm() > tempLeft->left->getPerm()) {
					tempLeft->right = user;
					tempLeft->rightIndex = index;
					tempLeft->userSize++;
				} else {

					tempLeft->right = tempLeft->left;
					tempLeft->rightIndex = tempLeft->leftIndex;
					tempLeft->left = user;
					tempLeft->leftIndex = index;
					tempLeft->userSize++;
				}



				//If the leaf was originally root, then there is no parent IntNode so we just do it manually here
				//Else, we split like normal and it will split roots later too

				//root code here can probably be deleted. will never happen because leaf will never be root
				if(cur_node->isRoot) {
					root = createIntNode(2, tempLeft, tempRight);
					root->isRoot = true;
					tempLeft->parent = root;
					tempRight->parent = root;
					delete cur_node;
				} else {
					splitIntNodes(cur_node->parent, tempLeft, tempRight);
				}
			}
		}

	}

	//heapify(this->root);
}



tNode* UserTree::createLeafNode(User* user, int index) {
	tNode* temp = new tNode();
	temp->leaf = true;
	temp->removed = false;
	temp->isRoot = false;
	temp->userSize = 1;
	temp->left = user;
	temp->leftIndex = index;
	temp->right = NULL;
	temp->parent = NULL;	//TODO:: make sure that splitIntNodes will fix parents each time it sets a children
	return temp;
}

tNode* UserTree::createIntNode(int size, tNode* n1, tNode* n2, tNode* n3, tNode* n4) {
	tNode* temp = new tNode();
	temp->leaf = false;
	temp->removed = false;
	temp->isRoot = false;
	temp->childSize = size;

	temp->children = new tNode*[4]; 	// DONE: initialize children as array first
										// note: using 4 because that is full size the array will be
	temp->children[0] = n1;				// DONE: add to children[0]
	temp->children[1] = n2;				// DONE: add to children[1]
	temp->children[2] = n3;				// set to null by default
	temp->children[3] = n4;				// set to null by default

	temp->keys = new int[3];			// DONE: initialize keys as array too
										// note: 3 keys are used for 4 children


	if(size == 1) {
		temp->isRoot = true;
		temp->children[0] = NULL;
		temp->children[1] = n1;
		temp->children[1]->parent = temp;
		temp->keys[0] = findSmallestUser(n1)->getPerm();
		temp->keySize = 1;
	} else {
		temp->keySize = size - 1;
		temp->keys[0] = findSmallestUser(n2)->getPerm();
		if(n3 != NULL) {
			temp->keys[1] = findSmallestUser(n3)->getPerm();
		}
		if(n4 != NULL) {
			temp->keys[2] = findSmallestUser(n4)->getPerm();
		}


		for(int i = 0; i < size; i++) {		// DONE: add parent Node
			if(temp->children[i] != NULL) {
				temp->children[i]->parent = temp;
			}
		}
	}
	return temp;

	//TODO: situation when size is 1, set isRoot to true, n1 now is in slot 2, maybe more
}

void UserTree::splitIntNodes(tNode* parent, tNode* newLeft, tNode* newRight) {
	//2 cases:
	//1) tNode is not full. so replace new left with current spot. Then replace next in line with right and shift the other ones down.
	//2) tNode is full. Now we have to split into two interior nodes and recurse up.
	tNode** tChildren = new tNode*[parent->childSize + 1];	//create array of pointer of children. This is them in their proper order
	int newCount = 0;

	int startInd = 0;
	if(parent->keySize == parent->childSize) {								//So if keySize == childSize, we know index 0 is a bust.
		startInd = 1;
	}

	for(int i = startInd; i < parent->childSize + startInd; i++) {		// Loops through the current parent
		tNode* cNode = parent->children[i];								// 1) If child is not the one being removed,
		if(!cNode->removed) {											// then just put it in normally
			tChildren[newCount++] = cNode;
		} else {														// it means the child's 2 children are being added
			tChildren[newCount++] = newLeft;							// Thats why we add them twice.
			tChildren[newCount++] = newRight;							// We use newCount because we have to finish adding
		}
	}

	//TODO: deleting removed node should be in the if(!cNode->removed) part

	if(parent->childSize < 4) {
//	std::cout << 		//childSize is 2 or 3. NOT FULL so just add tChildren in. This ends the recursion.
		parent->childSize++;
		for(int i = 0; i < parent->childSize; i++) {		//based off childSize, not keySize.
			parent->children[i] = tChildren[i];
			if(i != 0) {
				parent->keys[i-1] = findSmallestUser(parent->children[i])->getPerm();
			}
			//std::cout << "index is " << i << std::endl;
			//std::cout << "current children node is on: " << std::endl;
			//printNode(parent->children[i]);
			//std::cout << "smallest in this parent's key is: " << findSmallestUser(parent->children[i])->getPerm() << std::endl;

			parent->keySize = i;			//NOTE: if keySize is 0, error;
			tChildren[i]->parent = parent;	//DONE: each time you add child to parent, make sure to also add parent to the child
		}

		//heapify(this->root);

	} else {								//childSize is 4 (it is full)
		tNode* newLeftParent = createIntNode(3, tChildren[0], tChildren[1], tChildren[2]);
		tNode* newRightParent = createIntNode(2, tChildren[3], tChildren[4]);
		parent->removed = true;
		//DONE: each time you add child to parent, make sure to also add parent to the child.
		//DONE: did this in the createIntNode function

		if(parent->isRoot) {
			root = createIntNode(2, newLeftParent, newRightParent);
			root->isRoot = true;
			newLeftParent->parent = root;
			newRightParent->parent = root;
			delete parent;
		} else {
			splitIntNodes(parent->parent, newLeftParent, newRightParent);
		}
	}

}

User* UserTree::findUser(int perm) {
	User* u = findUserHelper(perm, root);
	if(u == NULL) {
	//	std::cout << "FAILED: user of perm: " << perm << " could not be found" << std::endl;
	} else {
	//	std::cout << "SUCCESS: found user of perm: " << perm << std::endl;
	}
	return u;
}

int UserTree::findIndex(int perm) {
	if(findUser(perm)) {
		return findIndexHelper(perm, root);
	}

	return -1;

}

int UserTree::findIndexHelper(int perm, tNode* current) {
	if(current->leaf) {
		if(current->left != NULL && current->left->getPerm() == perm) {
			return current->leftIndex;
		} else if (current->right != NULL && current->right->getPerm() == perm) {
			return current->rightIndex;
		} else {
			return -1;
		}
	}  else {
		if(perm >= current->keys[current->childSize - 2]) {
			return findIndexHelper(perm, current->children[current->childSize-1]);
		}
		for(int i = 0; i < current->childSize - 1; i++) {
			if(perm < current->keys[i]) {
				return findIndexHelper(perm, current->children[i]);
			}
		}
	}
}


//make sure you check if return value is null. Null means it wasnt found
User* UserTree::findUserHelper(int perm, tNode* current) {
	if(current->leaf) {
		if(current->left != NULL && current->left->getPerm() == perm) {
			return current->left;
		} else if (current->right != NULL && current->right->getPerm() == perm) {
			return current->right;
		} else {
			return NULL;
		}
	}  else {
		if(perm >= current->keys[current->childSize - 2]) {
			return findUserHelper(perm, current->children[current->childSize-1]);
		}
		for(int i = 0; i < current->childSize - 1; i++) {
			if(perm < current->keys[i]) {
				return findUserHelper(perm, current->children[i]);
			}
		}
	}
}

User* UserTree::findSmallestUser(tNode* n) {
	return findSmallestLeaf(n)->left;
}

tNode* UserTree::findSmallestLeaf(tNode* n) {

	if(n->leaf) {
		return n;
	} else {
		return findSmallestLeaf(n->children[0]);
	}
}

int UserTree::heapify(tNode* root) {
	if(!root->leaf) {
		for(int i = 0; i < root->childSize - 1; i++) {
			root->keys[i] = heapify(root->children[i + 1]);
		}
		return heapify(root->children[0]);
	} else {
		return root->left->getPerm();
	}
}

void UserTree::printUser(int perm) {
	User* u = findUser(perm);
	if( u != NULL) {
		u->print();
	} else {
		std::cout << "Could not find user of perm: " << perm << std::endl;
	}
}

void UserTree::print() {
	if(root == NULL) {
		std::cout << "tree has no items" << std::endl;
	} else {
		//This just checks if the stupid root problem exists. if it does, we start from 1.
		int startInd = 0;
		if(root->childSize == root->keySize) {
			startInd = 1;
		}

		std::cout << "PRINTING ROOT" << std::endl;
		printNode(root);

		std::cout << "PRINT FIRST ROW" << std::endl;
		for(int i = startInd; i < root->childSize + startInd; i++) {
			std::cout << "-----[ child: " << i << " ]-----" << std::endl;
			printNode(root->children[i]);
		}

		std::cout << "PRINT SECOND ROW" << std::endl;
		for(int i = startInd; i < root->childSize + startInd; i++) {
			if(!root->children[i]->leaf) {
				for(int j = 0; j < root->children[i]->childSize; j++) {
					std::cout << "-----[ child: " << i  << " -> " << j << " ]-----" << std::endl;
					printNode(root->children[i]->children[j]);
				}
			}
		}

		std::cout << "PRINT THIRD ROW" << std::endl;
		for(int i = startInd; i < root->childSize + startInd; i++) {
			if(!root->children[i]->leaf) {
				for(int j = 0; j < root->children[i]->childSize; j++) {
					if(!root->children[i]->children[j]->leaf) {
						for(int k = 0; k < root->children[i]->children[j]->childSize; k++) {
							std::cout << "-----[ child: " << i  << " -> " << j << " -> " << k << " ]-----" << std::endl;
							printNode(root->children[i]->children[j]->children[k]);
						}
					}
				}
			}
		}
	}
}

void UserTree::printNode(tNode* n) {
	std::cout << "__________________________" << std::endl;
	if(n->leaf) {
		std::cout << ">> This node is a leaf" << std::endl;

		if(n->isRoot) {
			std::cout << ">> This is also a root. Double check" << std::endl;
		} else {
			std::cout << ">> Not a root. Double check" << std::endl;
		}

		if(n->removed) {
			std::cout << ">> This node has been removed" << std::endl;
		} else {
			std::cout << ">> This node has not been removed" << std::endl;
		}


		if(n->left) {
			std::cout << ">> Its left value is: " << n->left->getPerm() << std::endl;
		} else {
			std::cout << ">> ERROR This leaf doesn't contain a left value ERROR" << std::endl;
		}

		if(n->right) {
			std::cout << ">> Its right value is: " << n->right->getPerm() << std::endl;
		} else {
			std::cout << ">> This leaf doesn't contain a right value" << std::endl;
		}

		if(n->userSize) {
			std::cout << ">> UserSize is: [" << n->userSize << "]. Double check with left/right value if correct. should be 1 or 2" << std::endl;
		} else {
			std::cout << ">> ERROR You have no userSize. Correct This ERROR" <<std::endl;
		}

		std::cout << ">> The left index is: " << n->leftIndex << std::endl;
		std::cout << ">> The right index is: " << n->rightIndex << std::endl;

		if(n->parent) {
			std::cout << ">> Parent EXISTS: it contains keys ";
			for(int i = 0; i < n->parent->keySize; i++) {
				std::cout << n->parent->keys[i] << ", ";
			}
			std::cout << "]" << std::endl;
		} else {
			std::cout << ">> NO PARENTS: either root or error. " << std::endl;
		}


	} else {
		std::cout << ">> This node is an interior Node" << std::endl;

		if(n->isRoot) {
			std::cout << ">> This is also a root. Double check" << std::endl;
		} else {
			std::cout << ">> Not a root. Double check" << std::endl;
		}

		if(n->childSize) {
			std::cout << ">> childSize is: [" << n->childSize << "]. " << std::endl;
		} else {
			std::cout << ">> ERROR You have no childSize. Correct This ERROR" <<std::endl;
		}

		std::cout << ">> The keys in this node is: ";
		for(int i = 0; i < n->keySize; i++) {
			std::cout << n->keys[i] << ", ";
		}
		std::cout << "]" << std::endl;

		if(n->parent) {
			std::cout << ">> Parent EXISTS: it contains keys ";
			for(int i = 0; i < n->parent->keySize; i++) {
				std::cout << n->parent->keys[i] << ", ";
			}
			std::cout << "]" << std::endl;
		} else {
			std::cout << ">> NO PARENTS: either root or error. " << std::endl;
		}
	}
	std::cout << std::endl << std::endl;
}
