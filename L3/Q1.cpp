#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*!
This is the node for Binary Search Tree
 */
class Node{
public:
	Node* left; //! Pointer to left child
	Node* right; //! Pointer to right child
	int data; //! Data stored in the node
	int height = 1; //! Height of the node
	int balanceFactor = 0; //! Balance factor of the node
	
	/*!
	This is the constructor of node class 
	which initialises the data of the node
	@param data 	The data stored in the node
	 */
	Node(int data){
		this->data = data;
	}

};

/*!
This is the node for Red Black Tree
 */
class RBNode {
public :
    int data; //! Data stored in node
    bool isBlack; //! Boolean to identify color of node
    int balancefactor; //! Balance factor of the node
    int h; //! Height of the node
    RBNode *left; //! Left child of node
	RBNode *right; //! Right child of node
	RBNode *parent; //! Parent of the node

    RBNode(int data) { 
    	
		this->data = data; 
        left = right = parent = NULL; 
        this->isBlack = false; 
    
	}   
};

class BiSearchTree{			
public:
	Node* root = NULL; //! Root node of tree
	vector<int> inOrderTree;

	/*!
	This function inserts new data into the tree
	@param parent 	The parent/root node
	@param data 	The data to be inserted
	@return Node*  	The parent/root node with the data inserted
	 */
	Node* insert(Node *parent, int data) {
            
            if(parent == NULL) {
                Node *temp = new Node(data);
                return temp;
            }
            if(data >= parent->data) {
                parent->right = insert(parent->right, data); 
                if(parent->left != NULL) { 
                    parent->height = max(parent->left->height, parent->right->height) + 1;
                    parent->balanceFactor = abs(parent->left->height - parent->right->height);
                } else {
                    parent->height = parent->right->height + 1;
                    parent->balanceFactor = parent->right->height;
                }
            }
            else {
                parent->left = insert(parent->left, data);
                if(parent->right != NULL) { 
                    parent->height = max(parent->left->height, parent->right->height) + 1;
                    parent->balanceFactor = abs(parent->left->height - parent->right->height);
                } else {
                    parent->height = parent->left->height;
                    parent->balanceFactor = parent->left->height;
                }
            }
            return parent;     
    }

	/*!
	This function creates a sorted array through 
	inorder traversal of the Binary Search Tree
	@param node 	The parent/root node
	@return ---
	 */
	void createArray_inOrder(Node* node){
		if(node == NULL) return;

		createArray_inOrder(node->left);
		inOrderTree.push_back(node->data);
		createArray_inOrder(node->right);
	}
	
	/*!
	This function calls itself recursively to convert the
	BST to an AVL tree
	@param root 	The parent/root node
	@param first 	The starting position in vector
	@param median 	The middle positioon of the vector
	@param last 	The end position of the vector
	@return Node* 	The parent/node with the subtree converted to AVL
	 */
	Node* generateAVL(Node* root, int first, int median, int last){
		
		if(first > last) return NULL;
	    root = new Node(inOrderTree[median]);
    	root->height = median - first + 1;
    
    	root->left = generateAVL(root->left, first, (first + median - 1) / 2, median-1);
    	root->right = generateAVL(root->right, median+1, (median + 1 + last) / 2, last);

    	root->balanceFactor = abs(((root->left != NULL) ? root->left->height : 0) - ((root->right != NULL) ? root->right->height : 0));
		return root;
	}

	/*!
	This function converts the Binary Search Tree to AVL Tree
	@return ---
	 */
	void convertToAvl(){
		
		inOrderTree.clear();
		createArray_inOrder(root);
		root = generateAVL(root, 0, floor(inOrderTree.size() / 2), inOrderTree.size() - 1);

	}

	/*!
	This function prints the data in the tree
	through inorder traversal
	@param parent 	The parent node for traversal
	@return ---
	 */
	void print_InOrder(Node *parent) { 
		
		if(parent == NULL) return;

        print_InOrder(parent->left);
        cout << parent->data << " ";
        print_InOrder(parent->right);  

	}

	/*!
	This function prints the data in the tree 
	in level-wise indentation
	@param parent 	The parent node
	@param spaces 	The number of appropriate spaces for indentation
	@return ---
	 */
	void print_LevelOrder(Node *parent, int spaces) {
		
		if(parent == NULL) return;

		for(int i = 1; i <= spaces; i++) cout << "  ";

		cout << parent->data;

		if(parent->balanceFactor != 0) cout << "[" << parent->balanceFactor << "]";
		
		cout << "\n";    
		print_LevelOrder(parent->left, spaces+1);
		print_LevelOrder(parent->right, spaces+1);
	}

	/*!
	This recursive function iterates to all the leaf nodes
	@param root 	The root/parent node
	@param path		A vector containing the path to leaf node 
	@return ---
	 */
	void toLeafNodes(Node *root, vector<int> path) {

    	if(root == NULL) return;

    	if(root->right == NULL && root->left == NULL) {
        	path.push_back(root->data);
        	for(int i = 0; i < path.size(); i++) {
            	if(i == path.size()-1) cout << path[i] << "\n";
            	else cout << path[i] << "->";
        	}
        	return;
    	}

    	path.push_back(root->data);
    
    	toLeafNodes(root->left, path);
    	toLeafNodes(root->right, path);    
	}

	/*!
	This function prints paths to all leaf nodes
	@param root 	The root/parent node
	@return ---
	 */
	void printPaths(Node *root) {

    	if(root == NULL) return;

    	toLeafNodes(root, {});
    	printPaths(root->left);
    	printPaths(root->right);
	}

};

class RedBlackTree{
public:
	RBNode *root = NULL;

	/*!
	This function inserts the data in the tree
	in the same fashion as BST insertion
	@param root 	The parent/root node
	@param temp 	A temporary node
	@return RBNode*  	The parent/root node with the data inserted
	*/ 
	RBNode* BSTInsert(RBNode *root, RBNode* temp) {

		if (root == NULL) 
		return temp; 
	
		if (temp->data <= root->data) 
		{ 
			root->left  = BSTInsert(root->left, temp); 
			root->left->parent = root; 
		} 
		else if (temp->data > root->data) 
		{ 
			root->right = BSTInsert(root->right, temp); 
			root->right->parent = root; 
		} 
	
		return root; 
	};

	/*!
	This function calculates the balance factor of
	each node upon insertion of a new one
	@param 		The root/parent node
	@return 	---
	*/
	void calculateBalFactor(RBNode *root){
		
		if(root == NULL) return; 

		calculateBalFactor(root->left);
		calculateBalFactor(root->right);

		int lh = ((root->left != NULL)? root->left->h	 : 0);
		int rh = ((root->right != NULL)? root->right->h : 0);
		root->h = max(lh, rh) + 1;
		root->balancefactor = abs(lh - rh);
	}

	/*!
	This function balances the tree by rotation around a node in right direction
	@param root 	The root/parent node
	@param temp 	A temporary node
	@return ---
	*/
	void rotateRight(RBNode *&root, RBNode *&temp){ 
		RBNode *temp_left = temp->left; 
	
		temp->left = temp_left->right; 
	
		if (temp->left != NULL) 
			temp->left->parent = temp; 
	
		temp_left->parent = temp->parent; 
	
		if (temp->parent == NULL) 
			root = temp_left; 
	
		else if (temp == temp->parent->left) 
			temp->parent->left = temp_left; 
	
		else
			temp->parent->right = temp_left; 
	
		temp_left->right = temp; 
		temp->parent = temp_left; 
	}

	/*!
	This function balances the tree by rotation around a node in left direction
	@param root 	The root/parent node
	@param temp 	A temporary node
	@return ---
	*/
	void rotateLeft(RBNode *&root, RBNode *&temp){ 
		RBNode *temp_right = temp->right; 
	
		temp->right = temp_right->left; 
	
		if (temp->right != NULL){
			temp->right->parent = temp;
		}
			
		temp_right->parent = temp->parent; 
	
		if (temp->parent == NULL){
			root = temp_right;
		}else if (temp == temp->parent->left){
			temp->parent->left = temp_right;
		}else{
			temp->parent->right = temp_right;
		} 
	
		temp_right->left = temp;
		temp->parent = temp_right;
	}

	/*!
	This function restores the properties of Red Black Tree
	@param root 	The root/parent node
	@param temp 	A temporary node
	@return ---
	*/
	void restoreRBProps(RBNode* &root, RBNode* &temp){

			RBNode *parent_temp = NULL; 
			RBNode *grand_parent_temp = NULL; 

			while ((temp != root) && (temp->isBlack == false) && (temp->parent->isBlack == false)){ 
		
				parent_temp = temp->parent; 
				grand_parent_temp = temp->parent->parent; 
		
				if (parent_temp == grand_parent_temp->left) 
				{ 
		
					RBNode *uncle_temp = grand_parent_temp->right; 
		
					if (uncle_temp != NULL && uncle_temp->isBlack == false) 
					{ 
						grand_parent_temp->isBlack = false; 
						parent_temp->isBlack = true; 
						uncle_temp->isBlack = true; 
						temp = grand_parent_temp; 

					}else { 
						if (temp == parent_temp->right){ 
							
							rotateLeft(root, parent_temp); 
							temp = parent_temp; 
							parent_temp = temp->parent; 

						} 
		
						rotateRight(root, grand_parent_temp); 
						swap(parent_temp->isBlack, grand_parent_temp->isBlack); 
						temp = parent_temp; 
					} 
				}else{ 
					RBNode *uncle_temp = grand_parent_temp->left; 
		
					if ((uncle_temp != NULL) && (uncle_temp->isBlack == false)){ 
						grand_parent_temp->isBlack = false; 
						parent_temp->isBlack = true; 
						uncle_temp->isBlack = true; 
						temp = grand_parent_temp; 
					} 
					else{ 
						if (temp == parent_temp->left){ 
							rotateRight(root, parent_temp); 
							temp = parent_temp; 
							parent_temp = temp->parent; 
						} 
		
						rotateLeft(root, grand_parent_temp); 
						swap(parent_temp->isBlack, grand_parent_temp->isBlack); 
						temp = parent_temp; 
					} 
				} 
			} 
		
		root->isBlack = true; 
					
	};

	/*!
	This function inserts new data into the tree
	@param data 	The data to be inserted
	@return ---
	 */
	void insert(int data) 
		{ 
			RBNode *temp = new RBNode(data); 
		
			root = BSTInsert(root, temp); 
		
			restoreRBProps(root, temp); 

			calculateBalFactor(root);
		}; 
	
	/*!
	This function prints the data in the tree
	through inorder traversal
	@param root 	The parent/root node for traversal
	@return ---
	 */
	void print_InOrder(RBNode *root) { 
		if (root == NULL) 
			return; 
	
		print_InOrder(root->left); 
		cout << root->data  << " "; 
		print_InOrder(root->right); 
	}    

	/*!
	This function prints the data in the tree 
	in level-wise indentation
	@param root 	The parent/root node
	@param spaces 	The number of appropriate spaces for indentation
	@return ---
	 */
	void print_LevelOrder(RBNode *root, int spaces) {
		
		if(root == NULL) return;

		for(int i = 1; i <= spaces; i++) cout << "  ";

		cout << root->data;

		if(root->balancefactor != 0)
			cout << "[" << root->balancefactor << "]";
		cout << ((root->isBlack)? "[BLACK]" : "[RED]");    
		cout << "\n";    
		print_LevelOrder(root->left, spaces+1);
		print_LevelOrder(root->right, spaces+1);
	}

	/*!
	This recursive function iterates to all the leaf nodes
	@param root 	The root/parent node
	@param path		A vector containing the path to leaf node 
	@return ---
	 */
	void toLeafNodes(RBNode *root, vector<int> path) {

    	if(root == NULL) return;

    	if(root->right == NULL && root->left == NULL) {
        	path.push_back(root->data);
        	for(int i = 0; i < path.size(); i++) {
            	if(i == path.size()-1) cout << path[i] << "\n";
            	else cout << path[i] << "->";
        	}
        	return;
    	}

    	path.push_back(root->data);
    
    	toLeafNodes(root->left, path);
    	toLeafNodes(root->right, path);    
	}

	/*!
	This function prints paths to all leaf nodes
	@param root 	The root/parent node
	@return ---
	 */
	void printPaths(RBNode *root) {

    	if(root == NULL) return;

    	toLeafNodes(root, {});
    	printPaths(root->left);
    	printPaths(root->right);
	}

};


int main(){
	BiSearchTree bstree;
	RedBlackTree rbtree;
	int input = 0;
	int data;

	do{		
		cout << "\n\n1) Insert new node in BST and Red-Black-Tree" << "\n";
        cout << "2) Create AVL tree from the inorder traversal of the BST" << "\n";
        cout << "3) Print tree data through inorder traversal" << "\n";
        cout << "4) Print all the paths in the BST/AVL/Red-Black-Tree" << "\n";
        cout << "5) Print the BST/AVL/Red-Black-Tree using level-wise indentation" << "\n"; 
        cout << "6) Exit" << "\n\n";

		cin >> input;

		switch(input) {

            case 1: {

                cout << "Enter data to be inserted" << "\n";
                cin >> data;

				bstree.root = bstree.insert(bstree.root, data);
				rbtree.insert(data);

				break;
            }

            case 2: {
                bstree.convertToAvl();
				break;
            }

            case 3: {
                
                cout << "1) Red Black Tree" << "\n";
                cout << "2) Binary Search Tree" << "\n";

                int x; cin >> x;

                switch(x) {
                    case 1:
                        cout << "\n";					
                        rbtree.print_InOrder(rbtree.root);
                        cout << "\n";
                        break;

                    case 2:
                        cout << "\n";
                        bstree.print_InOrder(bstree.root);
                        cout << "\n";
                        break;

                    default:
                        cout << "Invalid input.";            
                }    
                break;
            }

            case 4: {
                cout << "1) Red Black Tree" << "\n";
                cout << "2) Binary Search Tree" << "\n";

                int x; cin >> x;

                switch(x) {

                    case 1:
                        rbtree.printPaths(rbtree.root);
                        break;

                    case 2:
                        bstree.printPaths(bstree.root);
						break;

                    default:
                        cout << "Invalid input." << "\n";   
                }

                break;
            }

            case 5: {
                cout << "1) Red Black Tree" << "\n";
                cout << "2) Binary Search Tree" << "\n";

                int x; cin >> x;

                switch(x) {
                    case 1:
                        rbtree.print_LevelOrder(rbtree.root, 0);
                        break;

                    case 2:
                        bstree.print_LevelOrder(bstree.root, 0);
                        break;

                    default:
                        cout << "Invalid input!";            
                }    
                break;
            }

            case 6: {
                return 0;                
            }

            default:
                cout << "Invalid input." << "\n";
        }
    }while(input != 6);

	// newBSTree.root = newBSTree.insert(newBSTree.root, 10);
	// newBSTree.root = newBSTree.insert(newBSTree.root, 20);
	// newBSTree.root = newBSTree.insert(newBSTree.root, 30);
	// newBSTree.root = newBSTree.insert(newBSTree.root, 40);
	// newBSTree.root = newBSTree.insert(newBSTree.root, 50);
	// newBSTree.root = newBSTree.insert(newBSTree.root, 25);
	// // newBSTree.root = newBSTree.insert(newBSTree.root, 55);
	// //newBSTree.insert(55);
	// newBSTree.print_InOrder(newBSTree.root);
	// cout << "\n";
	// cout << "\n";
	// newBSTree.print_LevelOrder(newBSTree.root, 0);
	// cout << "\n";
	// cout << "\n";
	// newBSTree.printPaths(newBSTree.root);
	// cout << "\n";
	// cout << "\n";
	// newBSTree.convertToAvl();
	// newBSTree.print_InOrder(newBSTree.root);
	// cout << "\n";
	// cout << "\n";
	// newBSTree.print_LevelOrder(newBSTree.root, 0);
	// cout << "\n";
	// cout << "\n";
	// newBSTree.printPaths(newBSTree.root);
	// cout << "\n";
	// cout << "\n";
	// cout << "\n";
	// cout << "\n";
	// RedBlackTree rbtree;
	// rbtree.insert(10);
	// rbtree.insert(20);
	// rbtree.insert(30);
	// rbtree.insert(40);
	// rbtree.insert(50);
	// rbtree.insert(25);
	// //rbtree.insert(55);
	// rbtree.print_InOrder(rbtree.root);
	// cout << "\n";
	// cout << "\n";
	// rbtree.print_LevelOrder(rbtree.root, 0);
	// cout << "\n";
	// cout << "\n";
	// rbtree.printPaths(rbtree.root);
	// cout << "\n";
	// cout << "\n";

	return 0;
}
