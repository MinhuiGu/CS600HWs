#include <cstdio>
#include <cstdlib>
#include <boost/thread.hpp>
#include "timer.h"
#include "random_generator.h"
#include <iostream>
using namespace std;

void mod_insert_sort(int * arr, int p, int q);
void merge(int * arr,int* L,int * R,int p,int q,int r);
void merge_sort_4thread(int* arr, int n);
void merge_sort_2thread(int* arr, int n);

int main(int argc, char* argv[])
{
	//random_generator rg;
	int * array;
	int * temp1,*temp2;
	timer t1,t2,t3;
	int n;

	cout<<"input the array size:";
	cin>>n;
	srand(time(NULL));
	array = new int[n];
	temp1 = new int[n];
	temp2 = new int[n];
	for (int i=0;i<n;i++) {
		//rg>>array[i];
		//array[i]=array[i]%10000;
		array[i] = 1+rand()%100000;
		temp1[i] = array[i];
		temp2[i] = array[i];
	}

	// for (int i=0;i<n;i++)
	// 	cout<<array[i]<<endl;		
	// cout<<endl;
	
	t1.start();
	mod_insert_sort(array, 0,n-1);	
	t1.stop();
	// for (int i=0;i<n;i++)
	// 	cout<<array[i]<<endl;
	// cout<<endl;	
 	cout<<t1<<endl;

	t2.start();	
	merge_sort_2thread(temp1,n);
	t2.stop();	
	// for (int i=0;i<n;i++)
	// 	cout<<temp1[i]<<endl;	
	// cout<<endl;	
	cout<<t2<<endl;

	t3.start();			
	merge_sort_4thread(temp2,n);
	t3.stop();		
	// for (int i=0;i<n;i++)
	// 	cout<<temp2[i]<<endl;
	// cout<<endl;
	cout<<t3<<endl;
			
	delete[] array;
	delete[] temp1;
	delete[] temp2;		
	return 0;
	

}
void mod_insert_sort(int * arr, int p, int q)
{
	int temp=0;
	int i,j;
	for (i=p+1;i<=q;i++) {
		temp = arr[i];
		j=i-1;
		while((j>=p)&&(temp<arr[j])) {
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;
	}
}

void merge(int * arr,int* L,int * R,int p,int q,int r)
{
	int n1,n2,i,j,k;
	n1 = q-p+1;
	n2 = r-q;
	/*generate two sub arrays*/
	for (i = 0;i<n1;i++) {
		L[i]=arr[p+i];
	}
	for (i=0;i<n2;i++) {
		R[i]=arr[q+1+i];
	}
	
	/*merge two sorted arrays*/
	for(k=p,i=0,j=0;k<=r;k++) {
		if(i<n1&&j<n2) {
			if(L[i]<R[j]) {
				arr[k]=L[i];
				i++;
			}
			else {
				arr[k]=R[j];
				j++;
			}
		}
		else if(i>=n1) {
			arr[k]=R[j];
			j++;
		}
		else if(j>=n2) {
			arr[k]=L[i];
			i++;
		}
	}
}

void merge_sort_2thread(int* arr, int n)
{
	boost::thread** thrds;
	int *L,*R;
	
	thrds = new boost::thread*[2];
	
	//thrds = new boost:thread* [2];
	thrds[0] = new boost::thread(boost::bind(&mod_insert_sort,arr,0,n/2));
	thrds[1] = new boost::thread(boost::bind(&mod_insert_sort,arr,n/2+1,n-1));
	
	thrds[0]->join();
	thrds[1]->join();
	
	L = new int[n+1];
	R = new int[n+1];
	merge(arr,L,R,0,n/2,n-1);
	delete[] L;
	delete[] R;
  	delete thrds[0];
  	delete thrds[1];
  	delete[] thrds;	
		
}

void merge_sort_4thread(int* arr, int n)
{
	boost::thread** thrds;
	int *L,*R;
	
	//thrds = new boost:thread* [4];
	thrds = new boost::thread*[4];
	thrds[0] = new boost::thread(boost::bind(&mod_insert_sort,arr,0,n/4));
	thrds[1] = new boost::thread(boost::bind(&mod_insert_sort,arr,n/4+1,n/2));	
	thrds[2] = new boost::thread(boost::bind(&mod_insert_sort,arr,n/2+1,3*n/4));
	thrds[3] = new boost::thread(boost::bind(&mod_insert_sort,arr,3*n/4+1,n-1));

	thrds[0]->join();
	thrds[1]->join();	
	thrds[2]->join();
	thrds[3]->join();
	
	L = new int[n+1];
	R = new int[n+1];	
	merge(arr,L,R,0,n/4,n/2);
	merge(arr,L,R,n/2+1,3*n/4,n-1);	
	merge(arr,L,R,0,n/2,n-1);

	delete thrds[0];
  	delete thrds[1];
  	delete thrds[2];
  	delete thrds[3];
  	delete[] thrds;
	delete[] L;
	delete[] R;

}


