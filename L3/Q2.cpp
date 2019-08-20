#include <iostream>
#include <sstream>

using namespace std;

/*!
This is the node for linked list
 */
class Node{
public:
	Node* next = NULL;
	int data;

	Node(int data){
		this->data = data;
	}
};


class LinkedList{
public:
	Node* head = NULL;

	/*!
	This function inserts the pre-xor into the linked list
	@param data 	The data to be inserted
	@return ---
	 */	
	void insert(int data){
		Node* newNode = new Node(data);
		Node* temp;
		temp = head;
		if(head == NULL){
			head = newNode;
		}else{
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

};

int* input; //! The input array
int* xorK; //! Pre-xor array
int n; //! Number of inputs 
int number = 0; //! Number of triplets
LinkedList linkedList;

/*!
This function prints the triplets of a subarray
@param i 	The starting index of array
@param j 	The ending index of array
 */
void printTriplets(int i, int k){
	for(int j = i+2; j <= k+1; j++){
		printf("( %d, %d, %d)\n" ,(i+1), j, (k+1));
		number++;
	}
}

int main(){
	
	cin >> n;
	input = new int[n];
	xorK = new int[n];
	xorK[0] = 0;
	for(int i = 0; i < n; i++){
		cin >> input[i];
		if(i == 0){
			xorK[i] = input[i];
			linkedList.insert(xorK[i]);
		}else{
			xorK[i] = xorK[i-1]^input[i];
			linkedList.insert(xorK[i]);
		}

	}

	for(int i = 0; i < n; i++){
		if(xorK[i] == 0){
			printTriplets(0,i);
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < i-1; j++){
			if((xorK[j]^xorK[i]) == 0){
				printTriplets(j+1,i);
			}
		}
	}

	cout << "\nThe number of triplets is: " << number << "\n";
	return 0;
}
