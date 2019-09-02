#include<iostream>
using namespace std;

struct trienode
{
	trienode* child[26];
	bool end;
	string meaning;
};
trienode* root;
string temp_meaning;
void insert_in_trie(string word,string meaning)
{
	trienode* node=root;
	for(int i=0;i<word.length();i++)
	{
		int pos=(int)word[i]-(int)'A';
		if(!node->child[pos])
		{
			trienode* newnode=new trienode;
			newnode->end=false;
			for(int i=0;i<26;i++)
				newnode->child[i]=NULL;
			node->child[pos]=newnode;
		}
		node=node->child[pos];
	}
	node->end=true;
	node->meaning=meaning;
	return;
}
bool search_in_trie(string word)
{
	trienode* node=root;
	for(int i=0;i<word.length();i++)
	{
		int pos=(int)word[i]-(int)'A';
		if(!node->child[pos])
			return false;
		node=node->child[pos];
	}
	if(node->end)
		temp_meaning=node->meaning;
	return node->end;
}
int main()
{
	root=new trienode;
	root->end=false;
	for(int i=0;i<26;i++)
		root->child[i]=NULL;
	ifstream fp;
	fp.open("TrieInput.csv");
	if(!fp.is_open())
		cout<<"Unable to open input file."<<endl;
	string line,word,meaning;
	while(getline(fp,line))
	{
		stringstream str(line);
		getline(str,word,';');
		getline(str,meaning,';');
		insert_in_trie(word,meaning);
	}
	string input;
	getline(cin,input);
	if(search_in_trie(input))
		cout<<temp_meaning<<endl;
	else
		cout<<"Invalid word."<<endl;
	return 0;
}
