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

class TrieTree
{
	Trie *root;
	public:
		TrieTree()
		{
			root=new Trie;
		}
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
	void deleteTrieTree(string word)
	{
		deleteTrie(root,word,0);
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
};

int main()
{
	TrieTree tree;
	cout<<boolalpha;
	tree.insert("hello");
	cout<<tree.search("hello")<<endl;
	tree.deleteTrieTree("hello");
	cout<<tree.search("hello")<<endl;	
} 
