#include "splay.cpp"
using namespace std;




template <class T>
void print_splay_tree(SplayNode<T>* node,int level){
	if (node!=NULL) {
		print_splay_tree(node->right,level+1);
		for (int i=0; i<level; i++) {
			cout<<"   ";
		}
		cout<<node->value<<endl;
		print_splay_tree(node->left,level+1);
	}	
}



int main(int argc,char **argv){

	SplayTree<int> *st= new SplayTree<int>();
	
	
	SplayNode<int> *sn;
	
	cout<<"*************************************"<<endl;
	cout<<"insert"<<endl;
	cout<<"*************************************"<<endl;

	sn=st->splay_insert(1);
	sn=st->splay_insert(4);
	sn=st->splay_insert(21);
	sn=st->splay_insert(3);
	sn=st->splay_insert(5);
	sn=st->splay_insert(16);
	sn=st->splay_insert(7);
	sn=st->splay_insert(8);
	

	print_splay_tree(st->root,0);
	
	cout<<"*************************************"<<endl;
	cout<<"delete"<<endl;
	cout<<"*************************************"<<endl;
	
	sn=st->splay_delete(5);
	print_splay_tree(st->root,0);

	
	cout<<"*************************************"<<endl;
	cout<<"search"<<endl;
	cout<<"*************************************"<<endl;

	sn=st->splay_search(16);
	print_splay_tree(st->root,0);
	
	
	
	return 0;

}


