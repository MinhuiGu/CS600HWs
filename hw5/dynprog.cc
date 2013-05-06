#include <cstring>
#include <iostream>
#include <limits.h>

#include <dynprog.h>

using namespace std;

int my_max(int &a, int &b)
{
	return ((a>b)?a:b);
}

int cut_rod_R(int* p,int*c, int n)
{
	if (n==0)
		return 0;
	int q=MY_MIN;
	int k=0;
	for (int i=1; i<=n ;i++) {
		int cut =cut_rod_R(p,c,n-i);
		if (cut<p[n-i]) {
			k=p[i]+cut;
		}
		else {
			k = p[i]-c[i]+cut; 
		}
		q=my_max(q,k);	
	}
	return q;
}


int bottom_up_cut_rod_R(int*p,int* c,int n,int* result)
{
	result[0]=0;
	int q=MY_MIN;	
	int k=0;
	for (int j=1; j<=n; j++) {	
		for (int i=1; i<=j; i++) {
			if (result[j-i] < p[j-i])
				k=p[i]+result[j-i];
			else
				k =p[i]-c[i]+result[j-i];
			q=my_max(q,k);
			result[j]=q;
		}
	}
	return result[n];
}

int memorized_cut_rod_Aux_R(int*p,int* c,int n,int* r)
{
	int q;
	if (r[n]>=0)
		return r[n];
	if (n==0)
		q=0;
	else {
		q=MY_MIN;
		for (int i=1; i<=n; i++) {
			int k=0;
			int cut = memorized_cut_rod_Aux_R(p,c,n-i,r);
			if (cut<p[n-i])
				k = p[i]+cut;
			else
			 	k = p[i]-c[i]+cut;
			q=my_max(q,k);
		}
	}
	r[n]=q;
	return q;
}

int memorized_cut_rod_R(int*p,int* c,int n,int* result)
{
	for (int i=0; i<=n; i++)
		result[i] = MY_MIN;
	return memorized_cut_rod_Aux_R(p,c,n,result);
}

int ext_bottom_up_cut_rod_R(int*p,int* c,int n,int* result,int* solution)
{
	result[0]=0;
	for(int j =1;j<=n;j++) {
		int k;
	 	int q=MY_MIN;
		for (int i=1;i<=j;i++) {
			if(result[j-i]<p[j-i]) 
				k= p[i]+result[j-i];			
			else {
 				k = p[i]-c[i]+result[j-i];
			}
			if (q<k) {
				q=k;
				solution[j]=i;
			}
			result[j]=q;
		}
	}
	return result[n];
}

void print_cut_rod_solution(int*p,int* c,int n,int* result,int* solution)
{
	ext_bottom_up_cut_rod_R(p,c,n,result,solution);
	int k=0;
	cout<<"revenue: "<<result[n]<<endl;
	cout<<"solution: ";				
	while (n>0) {
		cout<<solution[n]<<" ";
		n=n-solution[n];
		// if(solution[n]==0) {
		// 	cout<<"1 "<<endl;
		// 	break;		
		// }

	}	
	cout<<endl;
	return;
}


