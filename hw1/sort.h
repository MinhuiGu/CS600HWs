#ifndef __SORT_H__
#define __SORT_H__

#include <random_generator.h>
#include <iostream>

using namespace std;

int string_compare(char*, char*);

void insertion_sort(char**, int, int);
void merge_sort(char**, int, int);

bool check_sorted(char**, int, int);

char** create_sorted_strings(int, int);
char** create_reverse_sorted_strings(int, int);
char** create_random_strings(int, int);

#endif
