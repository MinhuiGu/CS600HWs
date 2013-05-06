#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <random_generator.h>
#include <boost/thread.hpp>

int** create_matrix(int);
int** create_random_matrix(int, random_generator&);
void  delete_matrix(int**, int);

void multiply(int**, int**, int**, int);

int p_scalarproduct(int*, int*, int, int);
void copy_matrix(int** A, int** B,int n);
void output_matrix(int**, int);

#endif
