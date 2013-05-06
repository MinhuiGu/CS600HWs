#ifndef __DYNPROG_H__
#define __DYNPROG_H__

#define MY_MIN -1

int my_max(int &a, int &b);
int cut_rod_R(int* p, int* c, int n);
int bottom_up_cut_rod_R(int*p,int* c,int n,int* result);
int memorized_cut_rod_Aux_R(int*p,int* c,int n,int* r);
int memorized_cut_rod_R(int*p,int* c,int n,int* result);
int ext_bottom_up_cut_rod_R(int*p,int* c,int n,int* result,int* solution);
void print_cut_rod_solution(int*p,int* c,int n,int* result,int* solution);
#endif
