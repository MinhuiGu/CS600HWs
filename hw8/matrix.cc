

#include <matrix.h>

using namespace std;

int** create_matrix(int n)
{
  int** matrix;

  if (n < 1) 
    return 0;

  matrix = new int*[n];
  for (int i = 0; i < n; i++)
    matrix[i] = new int[n];

  return matrix;
}

void copy_matrix(int** A, int** B,int n)
{
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			B[i][j]=A[i][j];
}

int** create_random_matrix(int n, random_generator& rg)
{
  int** matrix;

  if (n < 1) 
    return 0;

  matrix = new int*[n];
  for (int i = 0; i < n; i++)
    {
      matrix[i] = new int[n];
      for (int j = 0; j < n; j++)
        rg >> matrix[i][j];
    }

  return matrix;
}

void delete_matrix(int** matrix, int n)
{ 
/* 
 * to be implemented by you!
 */
	for (int i=0;i<n;i++)
		delete[] matrix[i];
	delete[] matrix;
}

/*
 * non-parallel matrix multiplication
 */
void multiply(int** C, int** A, int** B, int n)
{ 
  if ((C == A) || (C == B))
    { 
      cout << "ERROR: C equals A or B!" << endl;
      return;
    }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      {
        C[i][j] = 0;
	for (int k = 0; k < n; k++)
	  C[i][j] += A[i][k] * B[k][j];
      }
} 

void p_scalarproduct_t(int* c, int* a, int* b, 
                       int s, int e, boost::mutex* lock)
{ 
  int tmp;

  tmp = 0;
  for (int k = s; k < e; k++)
    tmp += a[k] * b[k];

  lock->lock();
  *c = *c + tmp;
  lock->unlock();

} 

int p_scalarproduct(int* a, int* b, int n, int m)
{ 
  int c;
  boost::mutex lock;
  boost::thread** thrds;

  c = 0;

/* create threads and bind to p_merge_sort_t */
  thrds = new boost::thread*[m];
  for (int i = 0; i < m; i++)
    thrds[i] = new boost::thread(boost::bind(&p_scalarproduct_t, 
                                 &c, a, b, i*n/m, (i+1)*n/m, &lock));
/* join threads */
  for (int i = 0; i < m; i++)
    thrds[i]->join();

/* cleanup */
  for (int i = 0; i < m; i++)
    delete thrds[i];
  delete[] thrds;

  return c;
} 

void output_matrix(int** matrix, int n)
{ 
  cout << "[";
  for (int i = 0; i < n; i++)
    {
      cout << "[ ";
      for (int j = 0; j < n; j++)
        cout << matrix[i][j] << " ";
      cout << "]" << endl;
    }
  cout << "]" << endl;
}
