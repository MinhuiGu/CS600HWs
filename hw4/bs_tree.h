#ifndef __BS_TREE_H__
#define __BS_TREE_H__


struct bs_tree_node 
{
  int key;
  bs_tree_node*	left;
  bs_tree_node*	right;
  bs_tree_node*	p;
};

class bs_tree
{ 
  protected:
    bs_tree_node*	T_nil;
    bs_tree_node*	T_root;
	int		dup_counter;
	
  public:
    bs_tree();
    ~bs_tree();

    void insert(int*, int);
    void insert(int);
    int inorder_tree_walk(int*);
	void inorder_tree_walk(bs_tree_node*, int *,int*);
	int get_dup_count();
	bs_tree_node* tree_search(bs_tree_node* ,int);
	bs_tree_node* tree_minimum(bs_tree_node*);	
	bs_tree_node* tree_maximum(bs_tree_node*);	
	bs_tree_node* tree_successor(bs_tree_node*);	
	bs_tree_node* tree_predecessor(bs_tree_node*);
	void tree_predecessor(bs_tree_node*,bs_tree_node*);
	bs_tree_node* get_root();
		
	int get_height(bs_tree_node*);
	int calculate_height(bs_tree_node*,int ,int,int);
		
	void inorder_output()
      { inorder_output(T_root, 1); }
    void output()
      { output(T_root, 1); }

  protected:
    void insert(bs_tree_node*);
    void remove_all(bs_tree_node*);

    void inorder_output(bs_tree_node*, int);
    void output(bs_tree_node*, int);
};


#endif
