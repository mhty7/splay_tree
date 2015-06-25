#ifndef __SPLAY_H__
#define __SPLAY_H__

#include <iostream>

template <class T>
class SplayNode {
	public:
	T value;
	SplayNode *left;
	SplayNode *right;
	SplayNode *parent;
	SplayNode(const T & v, SplayNode *lt, SplayNode *rt);
	SplayNode();
};

template <class T>
class SplayTree{
	public:
	SplayTree();
	~SplayTree();
	SplayNode<T>* splay_search(const T & x);
	SplayNode<T>* splay_insert(const T & x);
	SplayNode<T>* splay_delete(const T & x);
	SplayNode<T> *root;
	private:
	
	void splay(SplayNode<T>* node,SplayNode<T>** r_node);
	SplayNode<T>* find(const T & x,SplayNode<T>** r_node);
	SplayNode<T>* new_node(const T & x);
	void rotate1(SplayNode<T>* node,SplayNode<T>** r_node);
	void rotate2(SplayNode<T>* node,SplayNode<T>** r_node);
};

#endif