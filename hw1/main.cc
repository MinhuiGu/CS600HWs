/*************************************************************************
	> File Name: main.cc
	> Author: Minhui Gu
	> 
	> Created Time: Sun 27 Jan 2013 12:40:09 PM EST
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include "sort.h"
#include "timer.h"
#include "random_generator.h"

#include<iostream>
using namespace std;


void my_strs_cpy(char** dest,char** src,int n, int l); 
void insert_sort(char ** st,int n,int l);
void merge(char** st,int p,int q,int r,int len);
void merge_sort(char ** st,int p,int r,int len);


int main(int argc, char* argv[])
{
	char ** str_for_insert; //strings for insert sort
	char ** str_for_merge; //strings for merge sort
	timer t;
	int num=0,type_flag=0,insert_flag=0,merge_flag=0,len=0;
	
	cout<<"input the number size of the strings:\n";
	cin>>num;
	cout<<"input the length of each string:\n";
	cin>>len;
	cout<<"choose the string type: random_strings-1, sorted_strings-2, reversed_sort_strings-3\n";
	cin>>type_flag;
	
	str_for_insert = new char*[num];
	str_for_merge = new char*[num];
	
	/*generate the needed strings*/
	if(type_flag==1) {

		/*use provided function to generate strings for insert sort*/
		str_for_insert = create_random_strings(num,len); 
		/*copy the strings for merge sort*/
		my_strs_cpy(str_for_merge,str_for_insert,num,len); 
		
	}
	else if(type_flag==2) {
		str_for_insert = create_sorted_strings(num,len);
		my_strs_cpy(str_for_merge,str_for_insert,num,len);
	}
	else if(type_flag==3) {
		str_for_insert = create_reverse_sorted_strings(num,len);
		my_strs_cpy(str_for_merge,str_for_insert,num,len);
	}
	else {
		cout<<"no such type\n";
		return -1;
	}
	
	cout<<"strings generated\nDo insert sort? yes-1, no-2\n";
	cin>>insert_flag;
	cout<<"Do insert sort? yes-1, no-2\n";
	cin>>merge_flag;
	
	/*Do insert sort if is specified*/
	if (insert_flag==1) {
		t.start();
		insert_sort(str_for_insert,num,len);
		t.stop();
		cout<<"insert sort:\n";
		/* outputs real, user, and system time */
		cout << "time: " << t << endl;
		cout<<"check result:"<<check_sorted(str_for_insert,0,num-1)<<endl;		
	}
	else 
		;
		
	/*Do merge sort if is specified*/		
	if (merge_flag==1) {
		t.start();
		merge_sort(str_for_merge,0,num-1,len);
		t.stop();
		cout<<"insert sort:\n";
		/* outputs real, user, and system time */
		cout << "time: " << t << endl;
		cout<<"check result:"<<check_sorted(str_for_merge,0,num-1)<<endl;
	}
	else 
		;
		
	return 0;

}

/*copy n strings which has length l from char **src to char ** dest */
void my_strs_cpy(char** dest,char** src,int n, int l)
{ 
	for (int k =0; k<n;k++) {
		dest[k] = new char[l];
		for (int s =0;s<l;s++) {
			dest[k][s] = src[k][s];
		}
	}	
}

/*do to insert sort for char** st which points to r strings that have the length l*/
void insert_sort(char ** st,int n,int l)
{
	char* key;
	int i,j;
	for(i =1;i<n;i++) {
		key=st[i];
		j=i-1;
		while ((j>=0)&&(string_compare(key,st[j])<0)) {
			st[j+1]=st[j];
			j=j-1;
		}
		st[j+1]=key;
	}
}

/*merge two sorted strings to one string, is used in merge_sort function*/
void merge(char** st,int p,int q,int r,int len)
{
	int n1,n2,i,j,k;
	n1 = q-p+1;
	n2 = r-q;
	char** L;
	L = new char*[n1];
	char** R;
	R = new char*[n2];
	int d;
	
	/*generate two sub string-arrays*/
	for (d = 0;d<n1;d++) {
		L[d] = new char[len];
		L[d]=st[p+d];
	}
	for (d=0;d<(r-q);d++) {
		R[d] = new char[len];
		R[d]=st[q+1+d];
	}
	
	/*merge two sorted arrays*/
	for(k=p,i=0,j=0;k<=r;k++) {
		if(i<n1&&j<n2) {
			if(string_compare(L[i],R[j])<=0) {
				st[k]=L[i];
				i++;
			}
			else {
				st[k]=R[j];
				j++;
			}
		}
		else if(i>=n1) {
			st[k]=R[j];
			j++;
		}
		else if(j>=n2) {
			st[k]=L[i];
			i++;
		}
	}
}

/*do merge sort for char** which porints to r strings that have the length l*/
void merge_sort(char ** st,int p,int r,int len)
{
	int q =0;
	if(p<r) {
		/*devide the string arrays*/
		q = (p+r)/2;
		/*merge the left half arrays*/
		merge_sort(st,p,q,len);
		/*merge the right half arrays*/ 
		merge_sort(st,q+1,r,len);
		/*merge two sorted arrays*/
		merge(st,p,q,r,len);
	}
	else
		return;
}

