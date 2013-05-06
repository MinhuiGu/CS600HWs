#include <cstdio>
#include <cstdlib>

#include <matrix.h>
#include <timer.h>
#include <random_generator.h>

void square_matrix_mult_1(int**C, int** A, int**B,int n,int m);
void square_matrix_mult_2(int**C, int** A, int**B,int n,int m);
void square_matrix_mult_2_part(int**C, int** A, int**B,int n,int m,int thread);
void Bij_to_Bji(int** B,int n);
int matrix_sp(int** A,int** B,int i,int j,int n);


int main(int argc, char* argv[])
{ 
  timer t1,t2,t3;
  int n;
  int m;
  
  n = 100;
  m=2;

/*
 * check arguments
 */
  switch (argc) {
    case 2: {
      n = atoi(argv[1]);
      n = (n < 1) ? 1 : n;
	  cout<<"miss argv[2], set thread to be 2\n";
    } break;
	case 3: {
		n = atoi(argv[1]);
	    n = (n < 1) ? 1 : n;
		m = atoi(argv[2]);
	    m = (m < 1) ? 1 : m;
		if (m>8) {
			cout<<"too much thread\n";
			return 1;
		}
	}break;
    default: {
      cout << argv[0] << " [n] [m] " << endl;
      cout << "[n]              n x n  random matrix" << endl;
      cout << endl;
      return 0;
    }
  }
	for (int count=0;count<10;count++) {
		random_generator rg;
  		
		int** C;
		int** A;
		int** B;
		int** C2;
		int** A2;
		int** B2;
		int** C3;
		int** A3;
		int** B3;
		int show =1;
		t1.start();
		C = create_matrix(n);
		A = create_random_matrix(n, rg);
		B = create_random_matrix(n, rg);
		t1.stop();

		cout << "Timer (generate): " << t1 << endl;

		C2=create_matrix(n);
		A2=create_matrix(n);
		B2=create_matrix(n);
		C3=create_matrix(n);
		A3=create_matrix(n);
		B3=create_matrix(n);
		copy_matrix(A, A2,n);
		copy_matrix(B, B2,n);
		copy_matrix(A, A3,n);
		copy_matrix(B, B3,n);

		// cout<<"show result for test? 0->yes, 1->no:";
		// cin>>show;
	
/*
	 * run algorithms
	 */
	  //cout << "Running non-parallel matrix multiplication: " << endl;
	  t1.start();
	  multiply(C, A, B, n);
	  t1.stop();
	  cout << "The Original Timer (multiplication): " << t1 << endl;
 
	  //cout << "SP: " << p_scalarproduct(A[0], B[0], n, m) << endl;

	//	cout << "Running parallel matrix multiplication approach 1: " << endl;

		t2.start();
		square_matrix_mult_1(C2,A2,B2,n,m);
		t2.stop();
		cout << "approach 1 Timer (multiplication): " << t2 << endl;
	
	//	cout << "Running parallel matrix multiplication approach 2: " << endl;
		t3.start();
		square_matrix_mult_2(C3,A3,B3,n,m);
		t3.stop();
		cout << "approach 2 Timer (multiplication): " << t3 << endl<<endl;

		// if (show ==0) {
		// 	cout<<"non-parallel matrix multiplication result:"<<endl;
		// 	output_matrix(C, n);
		// 	cout<<"parallel matrix multiplication approach 1 result:"<<endl;
		// 	output_matrix(C2, n);
		// 	cout<<"parallel matrix multiplication approach 2 result:"<<endl;
		// 	output_matrix(C3, n);
		// }		
/*
	 * free allocated storage
	 */
		delete_matrix(A,n);
		delete_matrix(B,n);
		delete_matrix(C,n);
		delete_matrix(A2,n);
		delete_matrix(B2,n);
		delete_matrix(C2,n);
		delete_matrix(A3,n);
		delete_matrix(B3,n);
		delete_matrix(C3,n);	
	}
  	return 0;
}


void Bij_to_Bji(int** B,int n)
{
	int temp;
	for (int i=0;i<n;i++) {
		for (int j=0;j<i;j++) {
			temp = B[i][j];
			B[i][j] = B[j][i];
			B[j][i] =temp;
		}
	}
}

void square_matrix_mult_1(int**C, int** A, int**B,int n,int m)
{			
	Bij_to_Bji(B,n);
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			C[i][j]=p_scalarproduct(A[i], B[j],n,m);
		}
	}
}

int matrix_sp(int** A,int** B,int i,int j,int n)
{
	int c=0;
	for( int k=0;k<n;k++)
		c=c+A[i][k]*B[k][j];
	return c;
}


void square_matrix_mult_2_part(int**C, int** A, int**B,int n,int m,int thread)
{
	for (int i=(thread*n)/m;i<((thread+1)*n)/m;i++) {
		for (int j=0;j<n;j++) {
			C[i][j] = matrix_sp(A,B,i,j,n);
		}
	}
}

void square_matrix_mult_2(int**C, int** A, int**B,int n,int m)
{
	int temp;
	boost::thread** thrds;
	thrds = new boost::thread*[m];
	
	for (int thre=0;thre<m;thre++) {
		thrds[thre] = new boost::thread(boost::bind(&square_matrix_mult_2_part, 
		                                 C, A, B, n,m, thre));
	}
	
	for (int i = 0; i < m; i++)
    	thrds[i]->join();

	for (int i = 0; i < m; i++)
	  delete thrds[i];
	delete[] thrds;

	
}
  
