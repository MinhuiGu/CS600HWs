#ifndef __SORT_H__
#define __SORT_H__

#include <random_generator.h>

/*
 * compute vector length
 * and access d-th digit
 */
int ivector_length(int*, int);
int length_digit(int, int);

/*
 * naive insertion sort implementation
 */
void insertion_sort(int**, int, int, int);

/*
 * check functions
 */
bool check_sorted(int**, int, int, int);

/*
 * integer vector handling
 */
int** create_ivector(int, int);
int** create_sorted_ivector(int, int);
int** create_reverse_sorted_ivector(int, int);
int** create_random_ivector(int, int, bool=false);

void remove_ivector(int**&, int);



#endif
