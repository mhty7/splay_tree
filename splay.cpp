 #include "splay.h"

template <class T>
SplayNode<T>::SplayNode(const T & v, SplayNode *lt, SplayNode *rt){
	value=v;
	left=lt;
	right=rt;
	parent = NULL;
}

template <class T>
SplayTree<T>::SplayTree(){
	root=NULL;
}


template <class T>
SplayTree<T>::~SplayTree(){
	
}



template <class T>
SplayNode<T>* SplayTree<T>::splay_search(const T & x){
	SplayNode<T>* n_node;
	n_node = find(x,&root);
	splay(n_node,&root);
	if (n_node->value==x) {
		return n_node;
	}
	else {
		return NULL;
	}

}



template <class T>
SplayNode<T>* SplayTree<T>::splay_insert(const T & x){
	SplayNode<T>* n_node;
	if (root==NULL) {
		n_node=new_node(x);
		root=n_node;
		return n_node;
	}
	
	n_node = find(x,&root);
	
	
	if (n_node->value==x) {
		splay(n_node,&root);
		return n_node;
	}
	
	SplayNode<T>* nn_node;
	nn_node=new_node(x);
	
	nn_node->parent=n_node;
	
	if (x<n_node->value) {
		n_node->left=nn_node;
	}
	else {
		n_node->right=nn_node;
	}
	splay(nn_node,&root);
	

	return nn_node;
	
	
}

template <class T>
SplayNode<T>* SplayTree<T>::splay_delete(const T & x){
	SplayNode<T>* n_node;
	if (root==NULL) {
		return NULL;
	}
	
	n_node = find(x,&root);
	splay(n_node,&root);
	if(x!=n_node->value){
		return root;
	}
	else {
		if (n_node->left==NULL) {
			n_node->right->parent=NULL;
			root=n_node->right;
		}
		else {
			splay(find(x,&n_node->left),&n_node->left);
			n_node->left->parent=NULL;
			root=n_node->left;
			
			//at this point, the right child of the root should be NULL.
			n_node->right->parent=root;
			root->right=n_node->right;
			
		}		
		n_node->parent=NULL;
		n_node->left=NULL;
		n_node->right=NULL;
		delete n_node;
		return root;
	}
	
}

template <class T>
SplayNode<T>* SplayTree<T>::new_node(const T & x){
	SplayNode<T>* n_node = new SplayNode<T> (x,NULL,NULL);
	return n_node;
}

//find the node with value 'x' in this tree.
template <class T>
SplayNode<T>* SplayTree<T>::find(const T & x,SplayNode<T>** r_node){
	SplayNode<T>* c_node;
	SplayNode<T>* p_node;
	
	//searching starts with the root.
	c_node=*r_node;
	p_node=*r_node;
	
	while (c_node != NULL) {
		if (x<c_node->value) {
			p_node=c_node;
			c_node=c_node->left;
		}
		else if(x>c_node->value){
			p_node=c_node;
			c_node=c_node->right;
		}
		
		//in case we found the key, return it.
		else {
			return c_node;
		}
	}
	
	//otherwise return the node with the beggest value along the way acheiving here.
	return p_node;
}


template <class T>
void SplayTree<T>::splay(SplayNode<T>* node,SplayNode<T>** r_node){
	if(!node){
		return;
	}
	
	
	while (node != *r_node) {
		
		if(node->parent == *r_node){
			rotate1(node,r_node);
		}
		else {
			rotate2(node,r_node);
		}
	}
}




//lifting up by one level.
//this operation is of zig.
template <class T>
void SplayTree<T>::rotate1(SplayNode<T>* node,SplayNode<T>** r_node){
	SplayNode<T>* parent;
	SplayNode<T>* T1;
	SplayNode<T>* T2;
	SplayNode<T>* W;
	
	parent=node->parent;
	
	//the node is the left child of his parent.
	if (node==parent->left) {
		W=node->left;
		T1=node->right;
		T2=parent->right;
		
		node->left = W;
		if(W!=NULL){
			W->parent=node;
		}
		
		node->right=parent;
		parent->parent=node;
		
		parent->left=T1;
		if(T1!=NULL){
			T1->parent=parent;
		}
		
		parent->right=T2;
		if (T2!=NULL) {
			T2->parent=parent;
		}
		
		
	}
	//the node is the right child of his parent.
	else {
		W=node->right;
		T1=parent->left;
		T2=node->left;
		
		node->left=parent;
		parent->parent=node;
		
		node->right=W;
		if (W!=NULL) {
			W->parent=node;
		}
		
		parent->left=T1;
		if (T1!=NULL) {
			T1->parent=parent;
		}
		
		parent->right=T2;
		if (T2!=NULL) {
			T2->parent=parent;
		}
		
	}
	
	*r_node=node;
	node->parent=NULL;

}

//lifting up by two levels.
//this operation is of either zig-zig or zig-zag.
template <class T>
void SplayTree<T>::rotate2(SplayNode<T>* node,SplayNode<T>** r_node){
	SplayNode<T>* parent;
	SplayNode<T>* grandparent;
	SplayNode<T>* greatparent;
	SplayNode<T>* T1;
	SplayNode<T>* T2;
	SplayNode<T>* T3;
	SplayNode<T>* T4;
	
	
	parent=node->parent;
	grandparent=parent->parent;
	greatparent=grandparent->parent;
	
	bool isLeftForParent = (parent == grandparent->left);
	bool isLeftForNode = (node == parent->left);
	
	if (isLeftForNode && isLeftForParent) {
		T1=node->left;
		T2=node->right;
		T3=parent->right;
		T4=grandparent->right;
		
		node->left = T1;
		if (T1!=NULL) {
			T1->parent=node;
		}
		
		node->right=parent;
		parent->parent=node;
		
		parent->left = T2;
		if (T2!=NULL) {
			T2->parent=parent;
		}
		
		parent->right=grandparent;
		grandparent->parent=parent;
		
		grandparent->left = T3;
		if (T3!=NULL) {
			T3->parent=grandparent;
		}
		
		grandparent->right = T4;
		if (T4!=NULL) {
			T4->parent=grandparent;
		}
		
	}
	else if(!isLeftForNode && isLeftForParent){
		T1=parent->left;
		T2=node->left;
		T3=node->right;
		T4=grandparent->right;
		
		node->left = parent;
		parent->parent=node;
		
		node->right=grandparent;
		grandparent->parent=node;
		
		parent->left=T1;
		if (T1!=NULL) {
			T1->parent=parent;
		}
		
		parent->right=T2;
		if (T2!=NULL) {
			T2->parent=parent;
		}
		
		grandparent->left=T3;
		if (T3!=NULL) {
			T3->parent=grandparent;
		}
		
		grandparent->right=T4;
		if (T4!=NULL) {
			T4->parent=grandparent;
		}
		
		
	}
	else if(isLeftForNode && !isLeftForParent){
		T1=grandparent->left;
		T2=node->left;
		T3=node->right;
		T4=parent->right;
		
		node->left=grandparent;
		grandparent->parent=node;
		
		node->right=parent;
		parent->parent=node;
		
		parent->left=T3;
		if (T3!=NULL) {
			T3->parent=parent;
		}
		
		parent->right=T4;
		if (T4!=NULL) {
			T4->parent=parent;
		}
		
		grandparent->left=T1;
		if (T1!=NULL) {
			T1->parent=grandparent;
		}
		
		grandparent->right=T2;
		if (T2!=NULL) {
			T2->parent=grandparent;
		}
		
	}
	else {
		T1=grandparent->left;
		T2=parent->left;
		T3=node->left;
		T4=node->right;
		
		node->left=parent;
		parent->parent=node;
		
		node->right=T4;
		if (T4!=NULL) {
			T4->parent=node;
		}
		
		parent->left=grandparent;
		grandparent->parent=parent;
		
		parent->right=T3;
		if (T3!=NULL) {
			T3->parent=parent;
		}
		
		grandparent->left=T1;
		if (T1!=NULL) {
			T1->parent=grandparent;
		}
		
		grandparent->right=T2;
		if (T2!=NULL) {
			T2->parent=grandparent;
		}
	}

	
	
	//to link the brought-up node with his parent if there exists.
	if(*r_node==grandparent){
		*r_node=node;
		node->parent=NULL;
	}
	else {
		if (greatparent->left==grandparent) {
			node->parent=greatparent;
			greatparent->left=node;
		}
		else {
			node->parent=greatparent;
			greatparent->right=node;
		}

	}

	
}


