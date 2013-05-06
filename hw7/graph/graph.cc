#include <graph.h>
#include <list>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

/*
 * constructor/destructor
 */

void graph::clear_vcolor()
{
	for (int i=0;i<no_vert;i++) {
		vers[i].color = WHITE;
	}	
}

graph::graph(int n)
{ /*<<<*/
  no_vert = (n > 0) ? n : 1;
  edge = 0;
  interval = 0;
	//circle_flag=0;
  
  vers = new node[no_vert];

/*
 * allocate adjacency matrix
 */
  m_edge = new int*[no_vert];
  for (int i = 0; i < no_vert; i++)
    m_edge[i] = new int[no_vert];

  initialize();
} /*>>>*/

graph::~graph()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  for (int i = 0; i < no_vert; i++)
    delete[] m_edge[i];
  delete[] m_edge;

  delete[] vers;
} /*>>>*/


void graph::initialize()
{ /*<<<*/
/*
 * initialize adjacency matrix
 * -> use infinity to allow 0 weight edges
 */
  clear_vcolor();
	
  for (int i = 0; i < no_vert; i++)
    for (int j = 0; j < no_vert; j++)
      m_edge[i][j] = INT_MAX;

} /*>>>*/



void graph::give_matrix_value(int* perm) {
	for (int i=0;i<no_vert-1;i++) {
		m_edge[perm[i]][perm[i+1]] =  2*(1 + (int) ((float)interval * (rand() / (RAND_MAX + 1.0))))-(int)interval;
	}
	
}

/*check all the existent circle in the m_edge*/
// void graph::check_circle(int** m)
// {
// 	int* cir_recorder;
// 	int flag=0;
// 	cir_recorder = new int[no_vert];
// 	for (int i=0;i<no_vert;i++) 
// 		cir_recorder[i]=INT_MIN;
// 	int counter=0;
// 	clear_vcolor();	
// 	for (int i=0;i<no_vert;i++) {		
// 		if (vers[i].color==WHITE) {
// 			//cout<<"start a new visit from "<<i<<endl;
// 			DFS_visit(m,i,counter,cir_recorder,flag);
// 		}
// 	}	
// 	clear_vcolor();
// 	delete[] cir_recorder;
// 	
// }

void graph::DFS_visit(int** m,int i,int& counter,int* cir_recorder,int& flag) 
{
	vers[i].color=GREY;
	cir_recorder[counter++]=i;	
	for (int j=0;j<no_vert;j++) {
		if (m[i][j]!=INT_MAX) {
			if (vers[j].color==GREY) {
				cir_recorder[counter]=j;
				int temp;
				for (temp=0;temp<counter;temp++) {
					if (cir_recorder[temp]==j)
						break;
				}
				cout<<"detected a circle: ";
				circle_weight=0;
				for (int t=temp;t<counter;t++) {
					cout<<cir_recorder[t]<<"->";
					circle_weight += m[cir_recorder[t]][cir_recorder[t+1]];
				}
				cout<<cir_recorder[counter]<<endl;
				cout<<"circle weight = "<<circle_weight<<endl;
				if (circle_weight<0)
					flag=HAVE_NEG_WEIGHT_CYCLE;
				else if (flag!= HAVE_NEG_WEIGHT_CYCLE)
					flag=HAVE_NOT_NEG_WEIGHT_CYCLE;
			}
			if(vers[j].color==WHITE) {
				DFS_visit(m,j,counter,cir_recorder,flag);
			}
		}
	}
	counter--;
	vers[i].color=WHITE;
}

/*generate a random graph*/
void graph::random_graph(int edges, int w)
{
	int e=edges,path_counter;
	interval = w;
	int *perm;
	int temp=0;
	
	/*generate path_counter random paths first*/
	path_counter = edges/(no_vert-1);

	while (path_counter > 0) {
		e= e-no_vert+1;
		perm = new int[no_vert];

		permutation(perm,no_vert);
		
		// for (int i=0;i<no_vert;i++) 
		// 	cout<<perm[i]<<" ";
		// cout<<endl;		
		path_counter--;	
			
		for (int i=0;i<no_vert-1;i++) {
			if (m_edge[perm[i]][perm[i+1]]==INT_MAX) {
				m_edge[perm[i]][perm[i+1]] =  1 + (int) (2*(float)interval * (rand() / (RAND_MAX + 1.0)))-(int)interval;								
			}
			else 
				e++;
		}			
		delete[] perm;
		perm = NULL;
	}

	/*generate the missing edges so as to generate enough edges*/
	//cout<<"edges left:"<<e<<endl;
	while (e>0) {
		for (int i=0;i<no_vert && e>0;i++)
			for(int j=0;j<no_vert && e>0;j++) {
				if(m_edge[i][j]==INT_MAX && i!=j) {
					/* to ensure the edge to be random*/
					temp = 1+ (int)( (float)100.0 * (rand() / (RAND_MAX + 1.0)));
					if (temp>50) {
						m_edge[i][j] =  1 + (int) (2*(float)interval * (rand() / (RAND_MAX + 1.0)))-(int)interval;
						e--;
						cout<<endl<<"now find circle for edge:"<<i<<" "<<j<<endl;
						int result=NO_CYCLE;
						result = check_circle_for_e(m_edge,no_vert,i,j);
						if (result ==HAVE_NEG_WEIGHT_CYCLE) {
							cout<<"result:"<<"circle exist with negative weight for edge: "<<i<<" "<<j<<endl<<endl;								
						}
						else if (result == HAVE_NOT_NEG_WEIGHT_CYCLE)
							cout<<"result:"<<"circle exist with positive weight for edge: "<<i<<" "<<j<<endl<<endl;	
						else 
							cout<<"result:"<<"no circle exist for edge: "<<i<<" "<<j<<endl<<endl;						
					}
				}
			}

	}
	//check_circle();
	
}

int** graph::get_matrix()
{
	int ** matrix;
	matrix = new int*[no_vert];
	for (int i=0;i<no_vert;i++)
		matrix[i] = new int[no_vert];
	for (int i=0;i<no_vert;i++)
		for (int j=0;j<no_vert;j++)
		matrix[i][j]=m_edge[i][j];
	return matrix;
}


void graph::do_relax(int **m, int u,int v)
{
	if (vers[v].d > vers[u].d+m[u][v]) {
		vers[v].d = vers[u].d+m[u][v];
		vers[v].predecessor = u;
	}
}


void graph::init_single_source(int s,int n)
{
	for (int i=0;i<n;i++) {
		vers[i].d=INT_MAX;
		vers[i].predecessor=INT_MIN;
	}
	vers[s].d=0;
}

/*bellman ford*/
int graph::bellman_ford(int** m, int s,int n)
{
	init_single_source(s,n);
	for(int k=0;k<n-1;k++){
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				if(m[i][j]!=INT_MAX) {
					do_relax(m,i,j);
				}	
			}
		}
	}

	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++){
			if(m[i][j]!=INT_MAX && i!=j) {
				if (vers[j].d >vers[i].d+m[i][j]) {
					cout<<"negative-weight cycles are reachable from source vertice: "<<s<<endl;
					return 1;
				}
			}	
		}
	}
	cout<<"no negative-weight cycles are reachable from: "<<s<<endl;
	return 0;
}

/* floyd_warshall for the graph with the matrix m_edge only*/
void graph::floyd_warshall() 
{
	floyd_warshall(m_edge,no_vert);
}

/* floyd_warshall for testing*/
void graph::floyd_warshall(int ** m,int n)
{
	int ** d;
	int ** p;
	p=new int*[n];
	d=new int*[n];
	for (int i=0;i<n;i++) {
		d[i]=new int[n];
		p[i]=new int[n];
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			d[i][j]=m[i][j];
			if(i==j||m[i][j]==INT_MAX)
				p[i][j]=NIL;
			else
				p[i][j]=i;
		}
	}
	cout<<"shortest weight matrix D(0):"<<endl;
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if(d[i][j]==INT_MAX)
				printf("%10s ","Inf");
			else
				printf("%10d ",d[i][j]);
		}
		cout<<endl;
	}
	
	cout<<"predecessor matrix PI(0):"<<endl;
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if(p[i][j]==NIL)
				printf("%10s ","NIL");
			else
				printf("%10d ",p[i][j]);
		}
		cout<<endl;
	}
	
	for (int k=0;k<n;k++) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++){
				if(i==j) {
					d[i][j]=INT_MAX;
					p[i][j]=NIL;	
				}else {
					if ((d[i][j]>d[i][k]+d[k][j]) && d[i][k]!=INT_MAX && d[k][j]!=INT_MAX ) {
						d[i][j]=d[i][k]+d[k][j];
						p[i][j]=k;
					}	
				}

			}
		}
	}
	
	cout<<"shortest weight matrix D(n):"<<endl;
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if(d[i][j]==INT_MAX)
				printf("%10s ","Inf");
			else
				printf("%10d ",d[i][j]);
		}
		cout<<endl;
	}
	
	cout<<"predecessor matrix PI(n):"<<endl;
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if(p[i][j]==NIL)
				printf("%10s ","NIL");
			else
				printf("%10d ",p[i][j]);
		}
		cout<<endl;
	}
	
	for (int i=0;i<n;i++) {
		delete[] d[i];
		delete[] p[i];
	}
	delete[] d;
	delete[] p;
	
	
}

/*check whether a circle exist in a graph having v vertices,for the edge (i,j), m is the adjacent matrix of the graph*/
int graph::check_circle_for_e(int** m, int v,int i,int j)
{
	int* cir_recorder;
	int flag=NO_CYCLE;
	cir_recorder = new int[v];
	for (int k=0;k<v;k++) 
		cir_recorder[k]=INT_MIN;
	int counter=0;
	clear_vcolor();	
	vers[i].color=GREY;
	cir_recorder[counter++]=i;
	DFS_visit(m,j,counter,cir_recorder,flag);	
	delete[] cir_recorder;
	 if (flag==NO_CYCLE)
	 	return NO_CYCLE;
	 else if (flag==HAVE_NEG_WEIGHT_CYCLE)
		return HAVE_NEG_WEIGHT_CYCLE;
	 else
		return HAVE_NOT_NEG_WEIGHT_CYCLE;
}

/*provided code*/
void graph::permutation(int* perm, int n)
{ /*<<<*/
  random_generator rg;
  int p_tmp, p_pos;

  for (int i = 0; i < n; i++)
    perm[i] = i;
  
  for (int i = 0; i < n; i++)
    {
      rg >> p_pos;
      p_pos = (p_pos % (n - i)) + i;

      p_tmp = perm[i];
      perm[i] = perm[p_pos];
      perm[p_pos] = p_tmp;
    }
} /*>>>*/

/*out put the matrix of m_edge*/
void graph::output()
{ /*<<<*/
  cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
	if (m_edge[i][j] == INT_MAX)
	  cout << "Inf\t";
	else
	  cout << m_edge[i][j] << "\t";
      cout << "]" << endl;
    }
  cout << "]" << endl;
} /*>>>*/

/*output a specified matrix m, for the purpose of testing*/
void graph::output(int ** m,int n)
{ /*<<<*/
  cout << "[";
  for (int i = 0; i < n; i++)
    {
      cout << "[\t";
      for (int j = 0; j < n; j++)
	if (m[i][j] == INT_MAX)
	  cout << "Inf\t";
	else
	  cout << m[i][j] << "\t";
      cout << "]" << endl;
    }
  cout << "]" << endl;
} /*>>>*/
