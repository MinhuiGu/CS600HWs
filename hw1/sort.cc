#include <cstdio>
#include <cstdlib>

#include <sort.h>

int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
        return -1;
      else
        return 1;
    }
} /*>>>*/

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (string_compare(A[i-1], A[i]) > 0)
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of strings
 */
char** create_sorted_strings(int n, int m)
{
  char** st_array;

  st_array = new char*[n];

/* set first string */
  st_array[0] = new char[m+1];
  for (int j = 0; j < m; j++)
    st_array[0][j] = 'a';
  st_array[0][m] = 0;

  for (int i = 1; i < n; i++)
    {
      st_array[i] = new char[m+1];

/* copy old string over */
      for (int j = 0; j <= m; j++)
	st_array[i][j] = st_array[i-1][j];
/* add +1 to the string, check for carry */
      st_array[i][m-1]++;
      for (int j = m-1; j > 0; j--)
	{
	  if (st_array[i][j] > 'z')
	    {
	      st_array[i][j] = 'a';
	      st_array[i][j-1]++;
	    }
	  else
	    break;
	}
    }

  return st_array;
}

char** create_reverse_sorted_strings(int n, int m)
{
  char** st_array;

  st_array = new char*[n];

/* set last string */
  st_array[n-1] = new char[m+1];
  for (int j = 0; j < m; j++)
    st_array[n-1][j] = 'a';
  st_array[n-1][m] = 0;

  for (int i = n-2; i >= 0; i--)
    {
      st_array[i] = new char[m+1];

/* copy old string over */
      for (int j = 0; j <= m; j++)
	st_array[i][j] = st_array[i+1][j];
/* add +1 to the string, check for carry */
      st_array[i][m-1]++;
      for (int j = m-1; j > 0; j--)
	{
	  if (st_array[i][j] > 'z')
	    {
	      st_array[i][j] = 'a';
	      st_array[i][j-1]++;
	    }
	  else
	    break;
	}
    }

  return st_array;
}

char** create_random_strings(int n, int m)
{
  random_generator rg;
  char** st_array;

  st_array = new char*[n];
  for (int i = 0; i < n; i++)
    st_array[i] = rg.random_string_m(m, 26);

  return st_array;
}

