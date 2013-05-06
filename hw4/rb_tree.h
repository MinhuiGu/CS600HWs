#ifndef __RB_TREE_H__
#define __RB_TREE_H__

enum rb_tree_color 
{
  RB_RED,
  RB_BLACK
};

struct rb_tree_node 
{
  int		key;
  int		color;
  rb_tree_node*	left;
  rb_tree_node*	right;
  rb_tree_node*	p;
};

class rb_tree
{ 
  protected:
    rb_tree_node*	T_nil;
    rb_tree_node*	T_root;
	int		dup_counter;
	int		case1_counter;
	int		case2_counter;
	int		case3_counter;
	int		left_rotate_counter;
	int		right_rotate_counter;
	int		black_num;	

  public:
    rb_tree();
    ~rb_tree();

	rb_tree_node* get_root();
    void insert(int*, int);
    void insert(int);
    int inorder_tree_walk(int*);
	void inorder_tree_walk(rb_tree_node*, int *,int *);
	int get_dup_count();
	int get_case1_count();
	int get_case2_count();
	int get_case3_count();
	int get_right_rotate_count();
	int get_left_rotate_count();
	void traverse_test(rb_tree_node*);
	int get_height(rb_tree_node*);	
    void inorder_output()
      { inorder_output(T_root, 1); }
    void output()
      { output(T_root, 1); }

  protected:
	int calculate_height(rb_tree_node*,int ,int,int);
    void insert(rb_tree_node*);
    void insert_fixup(rb_tree_node*&);
	void traverse(rb_tree_node*,int );
    void remove_all(rb_tree_node*);

    void left_rotate(rb_tree_node*);
    void right_rotate(rb_tree_node*);

    void inorder_output(rb_tree_node*, int);
    void output(rb_tree_node*, int);
};


#endif
