
#include <rb_tree.h>
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
rb_tree::rb_tree()
{ /*<<<*/
/*
 * create T_nil element
 */
  T_nil = new rb_tree_node();
  T_nil->color = RB_BLACK;
  T_nil->p = T_nil;
  T_nil->left = T_nil;
  T_nil->right = T_nil;

/*
 * root of rb tree
 */
  T_root = T_nil;

	dup_counter = 0;
	case1_counter=0;
	case2_counter=0;
	case3_counter=0;
	left_rotate_counter=0;
	right_rotate_counter=0;
	
} /*>>>*/

rb_tree::~rb_tree()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  remove_all(T_root);

  delete T_nil;
} /*>>>*/


int rb_tree::get_dup_count()
{	
	return dup_counter;
}

int rb_tree::get_case1_count()
{
	return case1_counter;
}

int rb_tree::get_case2_count()
{
	return case2_counter;
}

int rb_tree::get_case3_count()
{
	return case3_counter;
}

int rb_tree::get_left_rotate_count()
{
	return left_rotate_counter;
}

int rb_tree::get_right_rotate_count()
{
	return right_rotate_counter;
}

void rb_tree::insert(int* key_array, int n)
{ /*<<<*/
	dup_counter = 0;
	case1_counter=0;
	case2_counter=0;
	case3_counter=0;
	left_rotate_counter=0;
	right_rotate_counter=0;
	
  for (int i = 0; i < n; i++)
    insert(key_array[i]);
} /*>>>*/

void rb_tree::insert(int key)
{ /*<<<*/
/*
 * wrapper around insert
 * -> creates black node with key
 * -> inserts node
 */
  rb_tree_node* z;
  z = new rb_tree_node;
  z->color = RB_BLACK;
  z->key = key;

  insert(z);
} /*>>>*/

void rb_tree::insert(rb_tree_node* z)
{ /*<<<*/
/*
 * binary tree type insert 
 * -> search position, insert new node
 * -> fix properties after insert
 */
  rb_tree_node* x;
  rb_tree_node* y;

  y = T_nil;
  x = T_root;
  while (x != T_nil)
    {
      y = x;

      if (z->key < x->key)
	x = x->left;
      else if (z->key > x->key)
	x = x->right;
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
  z->color = RB_RED;

/*
 * after binary tree type insert we need to fix RB tree properties
 * -> update the info file
 */
  insert_fixup(z);
} /*>>>*/

int rb_tree::inorder_tree_walk(int* array) {

	int num = 0;
	if (T_root!=NULL)
		inorder_tree_walk(T_root, array,&num);
	return num;
}

void rb_tree::inorder_tree_walk(rb_tree_node* x, int * array,int *num){
	
	if(x!=T_nil){
		inorder_tree_walk(x->left,array,num);
		//cout<<x->key<<endl;
		array[(*num)++]= x->key;
		inorder_tree_walk(x->right,array,num);
	}
	else
		return;
}

void rb_tree::insert_fixup(rb_tree_node*& z)
{ /*<<<*/
/*
 * fix RB tree properties, after inserting a node
 * -> see book/slides for details on the cases
 */
  rb_tree_node* y;

  while (z->p->color == RB_RED)
    {
      if (z->p == z->p->p->left)
	{
	  y = z->p->p->right;

	  if (y->color == RB_RED)
	    {
	      z->p->color = RB_BLACK;		// Case 1
	      y->color = RB_BLACK;
	      z->p->p->color = RB_RED;
	      z = z->p->p;
		case1_counter++;
	    }
	  else
	    {
	      if (z == z->p->right)
		{
		  z = z->p;			// Case 2
		  case2_counter++;
		  left_rotate(z);
		}

	      z->p->color = RB_BLACK;		// Case 3
	      z->p->p->color = RB_RED;
		  case3_counter++;
	      right_rotate(z->p->p);
	    }
	}
      else
	{

	  y = z->p->p->left;

	  if (y->color == RB_RED)
	    {
		case1_counter++;
	      z->p->color = RB_BLACK;		// Case 1
	      y->color = RB_BLACK;
	      z->p->p->color = RB_RED;
	      z = z->p->p;
	    }
	  else
	    {
	      if (z == z->p->left)
		{
		  case2_counter++;
		  z = z->p;			// Case 2
		  right_rotate(z);
		}
		  case3_counter++;
	      z->p->color = RB_BLACK;		// Case 3
	      z->p->p->color = RB_RED;
	      left_rotate(z->p->p);
	    }
	}
    }

  T_root->color = RB_BLACK;
} /*>>>*/


void rb_tree::left_rotate(rb_tree_node* x)
{ /*<<<*/
/*
 * rotate left -> see book/slides
 */
  rb_tree_node* y;
left_rotate_counter++;
  y = x->right;			// set y
  x->right = y->left;		// turn y's left subtree into x's right subtree
  if (y->left != T_nil)
    y->left->p = x;

  y->p = x->p;			// link x's parent to y
  if (x->p == T_nil)
    T_root = y;
  else
    {
      if (x == x->p->left)
	x->p->left = y;
      else
	x->p->right = y;
    }

  y->left = x;			// put x on y's left
  x->p = y;
} /*>>>*/

void rb_tree::right_rotate(rb_tree_node* x)
{ /*<<<*/
/*
 * rotate right -> see book/slides
 */
  rb_tree_node* y;
	right_rotate_counter++;
  y = x->left;			// set y
  x->left = y->right;		// turn y's right subtree into x's left subtree
  if (y->right != T_nil)
    y->right->p = x;

  y->p = x->p;			// link x's parent to y
  if (x->p == T_nil)
    T_root = y;
  else
    {
      if (x == x->p->right)
	x->p->right = y;
      else
	x->p->left = y;
    }

  y->right = x;			// put x on y's right
  x->p = y;
} /*>>>*/

void rb_tree::inorder_output(rb_tree_node* x, int level)
{ /*<<<*/
/*
 * in order walk through binary tree
 * -> see book or slides
 */
  if (x != T_nil)
    {
      inorder_output(x->left, level+1);
      cout << "(" << x->key << "," << level << "," 
	   << ((x->color == RB_RED) ? "R" : "B") << ")" << endl;
      inorder_output(x->right, level+1); 
    }
} /*>>>*/

void rb_tree::output(rb_tree_node* x, int r_level)
{ /*<<<*/
/*
 * some structured output
 */
  list< pair<rb_tree_node*,int> > l_nodes;
  pair<rb_tree_node*,int> c_node;
  int c_level;

  c_level = r_level;
  l_nodes.insert(l_nodes.end(), pair<rb_tree_node*,int>(x, r_level));

  while (!l_nodes.empty())
    {
      c_node = *(l_nodes.begin());

      if (c_level < c_node.second)
	{
	  cout << endl;
	  c_level = c_node.second;
	}

      cout << "(" << c_node.first->key << "," 
	   << ((c_node.first->color == RB_RED) ? "R" : "B");

      if (c_node.first->p == T_nil)
	cout << ",ROOT) ";
      else
        cout << ",P:" << c_node.first->p->key << ") ";

      if (c_node.first->left != T_nil)
	l_nodes.insert(l_nodes.end(), pair<rb_tree_node*,int>(c_node.first->left, 
							      c_node.second+1));
      if (c_node.first->right != T_nil)
	l_nodes.insert(l_nodes.end(), pair<rb_tree_node*,int>(c_node.first->right, 
							      c_node.second+1));
      l_nodes.erase(l_nodes.begin());
    }

  cout << endl;
} /*>>>*/

void rb_tree::remove_all(rb_tree_node* x)
{ /*<<<*/
/*
 * recursively remove all tree elements
 */
  if (x != T_nil)
    {
      remove_all(x->left);
      remove_all(x->right);

      delete x;
    }
} /*>>>*/

rb_tree_node* rb_tree::get_root()
{
	return T_root;
}

void rb_tree::traverse_test(rb_tree_node* x)
{
	black_num = 0;
	traverse(x,black_num);
}

void rb_tree::traverse(rb_tree_node* x,int black_num)
{
	if (x!=T_nil) {
		if (x->color==RB_BLACK)
			black_num++;
		traverse(x->left,black_num);
		traverse(x->right,black_num);
	}
	else {
		cout<<"black node number:"<<black_num<<endl;
		return;		
	}
}

int rb_tree::get_height(rb_tree_node* x)
{
	int h=0;
	int left_height = 0;
	int right_height = 0;
	h = calculate_height(x,h,left_height,right_height);
	return h;
}

int rb_tree::calculate_height(rb_tree_node* x,int h,int left_height,int right_height)
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

