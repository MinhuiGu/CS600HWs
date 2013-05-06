#include <bs_tree.h>
#include <iostream>
#include <list>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{ 
  	T_nil = new bs_tree_node();
  	T_nil->p = T_nil;
  	T_nil->left = T_nil;
  	T_nil->right = T_nil;

  	T_root = T_nil;
  	dup_counter =0;
} 

bs_tree::~bs_tree()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  	remove_all(T_root);
  	delete T_nil;
} /*>>>*/

int bs_tree::get_dup_count()
{
	int counter = dup_counter;
	return counter;
}

int bs_tree::inorder_tree_walk(int* array) {

	int num = 0;
	if (T_root!=NULL)
		inorder_tree_walk(T_root, array,&num);
	return num;
}

void bs_tree::inorder_tree_walk(bs_tree_node* x, int * array, int * num){

	if(x!=T_nil){
		inorder_tree_walk(x->left,array,num);
		//cout<<x->key<<endl;
		array[(*num)++]= x->key;
		inorder_tree_walk(x->right,array,num);
	}
	else
		return;
}
void bs_tree::insert(int* _array, int n)
{ 
	dup_counter =0;
  	for (int i = 0; i < n; i++)
  	    insert(_array[i]);
}

void bs_tree::insert(int key)
{ 
  	bs_tree_node* z;

  	z = new bs_tree_node;
  	z->key = key;

  	insert(z);
} 

void bs_tree::insert(bs_tree_node* z)
{ /*<<<*/
	bs_tree_node* x;
	bs_tree_node* y;

	y = T_nil;
  	x = T_root;
  	while (x != T_nil)
    {
      y = x;

 		if (z->key < x->key) {
			x = x->left;			
		}
	    else if (z->key > x->key){
			x = x->right;		
		}
		else {
			dup_counter++;
			delete z;
			return;
		}

    }

  	z->p = y;
  	if (y == T_nil)
    	T_root = z;
  	else
    {
      	if (z->key < y->key)
			y->left = z;
      	else if (z->key > y->key)
			y->right = z;
		else {
			dup_counter++;
			delete z;
			return;
		}
    }

  		z->left = T_nil;
  		z->right = T_nil;

} /*>>>*/


void bs_tree::inorder_output(bs_tree_node* x, int level)
{ /*<<<*/
/*
 * in order walk through binary tree
 * -> see book or slides
 */
  	if (x != T_nil) {
      	inorder_output(x->left, level+1);
      	cout << "(" << x->key << "," << level << ")" << endl;
      	inorder_output(x->right, level+1); 
    }
} /*>>>*/

void bs_tree::output(bs_tree_node* x, int r_level)
{ /*<<<*/
/*
 * some structured output
 */
  	list< pair<bs_tree_node*,int> > l_nodes;
  	pair<bs_tree_node*,int> c_node;
  	int c_level;

  	c_level = r_level;
  	l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(x, r_level));

  	while (!l_nodes.empty()) {
      	c_node = *(l_nodes.begin());

      	if (c_level < c_node.second) {
	  		cout << endl;
	  		c_level = c_node.second;
		}

      cout << "(" << c_node.first->key;

      if (c_node.first->p == T_nil)
			cout << ",ROOT) ";
      else
        	cout << ",P:" << c_node.first->p->key << ") ";

      if (c_node.first->left != T_nil)
			l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->left, 
							      c_node.second+1));
      if (c_node.first->right != T_nil)
			l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->right, 
							      c_node.second+1));
      l_nodes.erase(l_nodes.begin());
    }

  	cout << endl;
} /*>>>*/


void bs_tree::remove_all(bs_tree_node* x)
{ /*<<<*/
/*
 * recursively remove all tree elements
 */
  	if (x != T_nil) {
      	remove_all(x->left);
      	remove_all(x->right);

      	delete x;
  	}
} /*>>>*/

bs_tree_node* bs_tree::get_root()
{
	return T_root;
}

bs_tree_node* bs_tree::tree_search(bs_tree_node* x,int k)
{
	if (x==T_nil|| k==x->key)
		return x;
	if (k<x->key)
		return tree_search(x->left, k);
	else 
		return tree_search(x->right, k);
}

bs_tree_node* bs_tree::tree_minimum(bs_tree_node* x)
{
	while(x->left !=T_nil)	
		x = x->left;
	return x;
}
bs_tree_node* bs_tree::tree_maximum(bs_tree_node* x)
{
	while(x->right !=T_nil)	
		x = x->right;
	return x;
}
bs_tree_node* bs_tree::tree_successor(bs_tree_node* x)
{
	bs_tree_node* y;
	if (x->right != T_nil)
		return tree_minimum(x->right);
	y = x->p;
	while (y!=T_nil && x== y->right) {
		x=y;
		y=y->p;
	}
	return y;
}

bs_tree_node* bs_tree::tree_predecessor(bs_tree_node* x)
{
	bs_tree_node* y;
	if (x->left != T_nil)
		return tree_maximum(x->left);
	y = x->p;
	while (y!=T_nil && x== y->left) {
		x=y;
		y=y->p;
	}
	return y;
}

int bs_tree::get_height(bs_tree_node* x)
{
	int h=0;
	int left_height = 0;
	int right_height = 0;
	h = calculate_height(x,h,left_height,right_height);
	return h;
}
void bs_tree::tree_predecessor(bs_tree_node* u,bs_tree_node* v)
{
	if (u->p ==T_nil)
		T_root = v;
	else {
		if (u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
	}
	if (v!=T_nil)
		v->p=u->p;
}

int bs_tree::calculate_height(bs_tree_node* x,int h,int left_height,int right_height)
{
	if (x==T_nil)
		return h;
	else {
		left_height = calculate_height(x->left,h,left_height,right_height);
		right_height = calculate_height(x->right,h,left_height,right_height);
		h = (left_height > right_height ? left_height:right_height) + 1;
	}
	return h;
	
}