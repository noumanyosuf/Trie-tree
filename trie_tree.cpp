#include<iostream>
#include <map>
#include<string>
/*
	Trie tree is an ordered  ds used to stored dynamic set of set where key is a  string string.
	aka digital tree, radix tree, prefix tree.
*/
/*
To do : find a simpler way to delete.
*/
using namespace std;

class Trie
{
	public:
		bool endOfWord;
		map<char,Trie*> children;
		Trie()
		{
			endOfWord=false;	
		}
};
Trie *root;

void insert(string word)
{
	Trie *current=root;
	for(int i=0;i<word.length();i++)
	{
		Trie *node=current->children[word[i]];
		if(!node)
		{
			node=new Trie;
			current->children[word[i]]=node;
		}
		current=node;
	}
	current->endOfWord=true;
}
void insertRecursive(Trie *current,string word,int index=0)
{
	if(word.length()==index-1)
	{
		current->endOfWord=true;
		return;
	}
	Trie *node=current->children[word[index]];
	if(!node)
	{
		node=new Trie;
		current->children[word[index]]=node;
	}
	insertRecursive(node,word,index+1);
}

bool search(string word)
{
	Trie *current=root;
	for(int i=0;i<word.length();i++)
	{
		Trie *node=current->children[word[i]];
		if(!node)
		{
			return false;
		}
		current=node;
	}
	return current->endOfWord;
}

bool deleteTrie(Trie *current,string word,int index)
{
	if(index==word.length())
	{
		if(!current->endOfWord)return false;
		current->endOfWord=false;
		return current->children.size() == 0;
	}
	Trie *node=current->children[word[index]];
	if(!node)return false;
	
	bool deleteCurrentNode;
	deleteCurrentNode=deleteTrie(node,word,index+1);
	
	if(deleteCurrentNode)
	{
		delete node;
		current->children.erase(word[index]);
		return current->children.size() == 0;
	}
	return false;
}

int main()
{
	root=new Trie;
	cout<<boolalpha;
	insert("hello");
	cout<<search("hello")<<endl;
	deleteTrie(root,"hello",0);
	cout<<search("hello")<<endl;	
} 
