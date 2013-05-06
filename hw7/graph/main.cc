#include <cstdio>
#include <cstdlib>

#include <graph.h>
#include <timer.h>
#include <random_generator.h>

int main(int argc, char* argv[])
{ 
  	int vertices,edges,interval;
	graph * gra;
	cout<<"input vertices number: ";
	cin>>vertices;
	
	cout<<"input edeges number "<<"[range:"<<vertices-1<<","<<vertices*(vertices-1)<<"]: ";
	cin>>edges;
	if (edges<vertices-1 || edges>(vertices*(vertices-1))) {
		cout<<"invalid edges number"<<endl;
		return 1;		
	}
	cout<<"input interval "<<"[range:0,"<<INT_MAX/edges<<"]: ";
	cin>>interval;
	if (interval<0 ||interval>INT_MAX/edges) {
		cout<<"invalid interval"<<endl;
		return 1;		
	}

	gra = new class graph(vertices);
	gra->random_graph(edges,interval); 
	gra->floyd_warshall();
	cout<<endl;
	gra->output();

/*for manual test only*/
	// int ** matrix;
	// graph * gra2;
	// int o=5;
	// matrix = new int*[o];
	// gra2 = new class graph(o);
	// for (int i=0;i<o;i++)
	// 	matrix[i] = new int[o];
	// for (int i=0;i<o;i++)
	// 	for (int j=0;j<o;j++)
	// 	matrix[i][j]=INT_MAX;
	// matrix[1][0]=3;
	// matrix[1][2]=1;
	// matrix[1][4]=8;
	// matrix[2][3]=-2;
	// matrix[3][1]=4;
	// gra2->bellman_ford(matrix,1,o);
	// int result = gra2->check_circle_for_e(matrix,o,1,2);
	// 
	// if (result ==HAVE_NEG_WEIGHT_CYCLE) {
	// 	cout<<"result:"<<"circle exist with negative weight for edge: "<<1<<" "<<2<<endl<<endl;								
	// }
	// else if (result == HAVE_NOT_NEG_WEIGHT_CYCLE)
	// 	cout<<"result:"<<"circle exist with positive weight for edge: "<<1<<" "<<2<<endl<<endl;	
	// else 
	// 	cout<<"result:"<<"no circle exist for edge: "<<1<<" "<<2<<endl<<endl;		
	// gra2->output(matrix,o);
	// for (int i =0;i<o;i++)
	// 	delete[] matrix[i];
		
	delete gra;
	//delete gra2;
 	return 0;
}
  
