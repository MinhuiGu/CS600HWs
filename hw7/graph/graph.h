#ifndef __AM_GRAPH_H__
#define __AM_GRAPH_H__

#include <limits.h>
#include <timer.h>
#include <random_generator.h>


#define WHITE 1
#define GREY 2
#define BLACK 3
#define NO_CYCLE 1
#define HAVE_NEG_WEIGHT_CYCLE 2
#define HAVE_NOT_NEG_WEIGHT_CYCLE 3
#define NIL -1001

class node
{
  public:
	int color;
	/*bellman-ford use*/
	int d,predecessor;
	
};

class graph
{
  protected:
	node* 	vers;
    int**	m_edge;
    int		no_vert,edge,interval;
	int 	circle_weight;
	

  public:
    graph(int);
    ~graph();

	int** get_matrix();
    int get_no_of_vertices()
      { return no_vert; }
	void random_graph(int, int);
	void give_matrix_value(int*);
    void output();
	void DFS_visit(int**,int,int&,int*,int&);
	//void check_circle(int**);
	int  check_circle_for_e(int**,int,int,int);
	int bellman_ford(int**,int,int);
	void floyd_warshall(int ** m,int n);
    void floyd_warshall();
	void output(int **,int);
	void do_relax(int**,int,int);
  protected:
	void init_single_source(int,int);
    void initialize();
    void permutation(int*, int);
	void clear_vcolor();
};



#endif
