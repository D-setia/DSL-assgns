#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
/*!
This is the Node class with all the important attributes
*/
class Node{
public:
	Node* child[26];
	bool wordEnd;
	string wordMeaning;

	Node(){
		this->wordEnd = false;
		for(int i = 0; i< 26; i++){
			this->child[i] = NULL;
		}
	}
};

Node* root;
Node* searchResult;
string ipline;
string inputWord; 
string inputMeaning;

/*!
This function inserts a word into the dictionary along with its meaning
@param word     The word to add to the dictionary
@param wordMeanig   Meaning of the word
@return ---
*/
void insert(string word, string wordMeaning){
	Node* node=root;
	for(int i=0;i<word.length();i++)
	{
		int letter=(int)word[i]-(int)'a';
		if(!node->child[letter])
		{
			Node* newNode=new Node();
			node->child[letter]=newNode;
		}
		node=node->child[letter];
	}
	node->wordEnd=true;
	node->wordMeaning=wordMeaning;
}

/*!
This function serches for the word specified by the argument in the dictionary
@param word     The word to search in the dictionary
@return Node*   A node with the meaning set as the required meaning
*/
Node* search(string word)
{
	Node* node=root;
	for(int i=0;i<word.length();i++)
	{
		int letter=(int)word[i]-(int)'a';
		if(!node->child[letter])
			return NULL;
		node=node->child[letter];
	}
	if(node->wordEnd){
		Node* temp = new Node();
		temp->wordMeaning = node->wordMeaning;
		return temp;
	}else{
		return NULL;
	}
}

int main(){
	root=new Node();

	ifstream str;
	str.open("L4_P1_input.csv");
	if(!str.is_open())
		cout<<"Input file not found."<<endl;
	
	while(getline(str,ipline))
	{
		stringstream string(ipline);
		getline(string, inputWord,';');
		getline(string,inputMeaning,';');
        
        for (int i=0; i < inputWord.length(); i++)
        inputWord[i] = tolower(inputWord[i]);
        
        for (int i=0; i < inputMeaning.length(); i++)
        inputMeaning[i] = tolower(inputMeaning[i]);

        // inputMeaning = inputMeaning.tolower();
		insert(inputWord,inputMeaning);
	}

	string input;
	getline(cin,input);
	
	searchResult = search(input);
	if(searchResult)
		cout<<searchResult->wordMeaning<<endl;
	else
		cout<<"Word not found in dictionary."<<endl;
	return 0;
}