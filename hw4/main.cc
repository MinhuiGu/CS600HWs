#include <cstdio>
#include <cstdlib>

#include <sort.h>
#include <bs_tree.h>
#include <rb_tree.h>
#include <timer.h>
#include <random_generator.h>

int main(int argc, char* argv[])
{ 
	int n,type,times,mode,num;
	int * array_bs;
	int * array_rb;
	int * array_sorted;
	rb_tree_node* rb_root;
	bs_tree_node* bs_root;
	rb_tree* rb;
	bs_tree* bs;
	timer t1,t2;
	
	cout<<"input n: ";
	cin>>n;
	
	cout<<"debugging mode->1  recording result mode->2 :";
	cin>>mode;
	
	if(mode==1||mode==2) {
		if (mode==2) {
			cout<<"run how many times? (for recording result) ";
			cin>>times;	
		} else
			;
	}		
	else {
		cout<<"invalid mode"<<endl;
		return -1;
	}
	
	cout<<"input type: 1->sorted 2->random 3->reverse_sorted: ";
	cin>>type;
		
	if (mode==1) {
		array_sorted = new int[n];
		bs = new class bs_tree;
		rb = new class rb_tree;
		
		/*  create arrays   */
		if(type==1) {
			array_bs=create_sorted(n); 
			/* copy the array to test running performance of both bs tree and rb tree using arrays of the same value*/
			array_rb = new int[n];
			for (int i=0; i<n; i++)
				array_rb[i] = array_bs[i];  
	     }
	     else if(type==2) {
	 		array_bs=create_random(n);  
			array_rb = new int[n];
			for (int i=0; i<n; i++)
				array_rb[i] = array_bs[i];    
	     }
	     else if(type==3) {
	        array_bs=create_reverse_sorted(n);
			array_rb = new int[n];
			for (int i=0; i<n; i++)
				array_rb[i] = array_bs[i];
	     }
	     else {
	         cout<<"wrong type"<<endl;
			return -1;		
		 }

		
		cout<<"**************************************"<<endl;
		cout<<"rb tree debugging output:"<<endl<<endl;
		rb->insert(array_rb,n);
		cout<<"rb tree inserted! the tree: ";		
		//rb->output();
		
		cout<<endl<<"inorder_tree_walk begin"<<endl;
		num = rb->inorder_tree_walk(array_sorted);
		cout<<"inorder_tree_walk done, "<<num<<" nodes in the tree"<<endl;
		// for (int k=0;k<num;k++) {
		// 	cout<<array_sorted[k]<<endl;		
		// }
		cout<<endl<<"print first 5 for debugging:"<<endl;
		for (int k=0;k<5;k++) {
			cout<<array_sorted[k]<<endl;		
		}		
		
		cout<<endl<<"duplicate count:"<<rb->get_dup_count()<<endl;
		cout<<"case1 count:"<<rb->get_case1_count()<<endl;
		cout<<"case2 count:"<<rb->get_case2_count()<<endl;
		cout<<"case3 count:"<<rb->get_case3_count()<<endl;
		cout<<"left_rotate count:"<<rb->get_left_rotate_count()<<endl;
		cout<<"right_rotate count:"<<rb->get_right_rotate_count()<<endl;
		cout<<"traverse from the root:"<<endl;
		rb_root = rb->get_root();
		rb->traverse_test(rb_root);
		cout<<endl;
		cout<<"rb tree height:"<<rb->get_height(rb_root)<<endl;
		cout<<"**************************************"<<endl<<endl;
		
		
		cout<<"**************************************"<<endl;
		cout<<"bs tree debugging output:"<<endl<<endl;
		bs->insert(array_bs,n);
		cout<<"bs tree inserted! the tree: ";
		//bs->output();
		cout<<endl<<"inorder_tree_walk begin"<<endl;
		num = bs->inorder_tree_walk(array_sorted);
		cout<<"inorder_tree_walk done, "<<num<<" nodes in the tree"<<endl;
		// for (int k=0;k<num;k++) {
		// 	cout<<array_sorted[k]<<endl;		
		// }
		cout<<endl<<"print first 5 for debugging:"<<endl;
		for (int k=0;k<5;k++) {
			cout<<array_sorted[k]<<endl;		
		}
		cout<<"the last one(maximun ont): "<<array_sorted[num-1]<<endl;
		bs_root = bs->get_root();
		cout<<endl<<"duplicate count:"<<bs->get_dup_count()<<endl;
		cout<<"bs tree height:"<<bs->get_height(bs_root)<<endl;
		cout<<"max node: "<<bs->tree_maximum(bs_root)->key<<endl;
		cout<<"min node: "<<bs->tree_minimum(bs_root)->key<<endl;
		cout<<" now insert 1024 into the bs tree"<<endl;
		bs->insert(1024);
		cout<<"search result:"<<(bs->tree_search(bs_root ,1024)->key)<<endl;
		cout<<"**************************************"<<endl;
		cout<<"debugging mode end"<<endl;
		
		delete[] array_rb;
		delete[] array_bs;
		delete[] array_sorted;
		delete rb;
		delete bs;
	}
	
	else {

		for (int i =0; i<times;i++) {
			bs = new class bs_tree;
			rb = new class rb_tree;
			
			array_sorted = new int[n];

			if(type==1) {
				array_bs=create_sorted(n); 
				array_rb = new int[n];
				for (int i=0; i<n; i++)
					array_rb[i] = array_bs[i];  
		     }
		     else if(type==2) {
		 		array_bs=create_random(n);  
				array_rb = new int[n];
				for (int i=0; i<n; i++) {			
					array_rb[i] = array_bs[i];    				
				}

		     }
		     else if(type==3) {
		        array_bs=create_reverse_sorted(n);
				array_rb = new int[n];
				for (int i=0; i<n; i++)
					array_rb[i] = array_bs[i];
		     }
		     else {
		         cout<<"wrong type"<<endl;
				return -1;		
			 }
						
			 t1.start();
			rb->insert(array_rb,n);			
			num = rb->inorder_tree_walk(array_sorted);
			t1.stop();
			cout<<"check red-black tree result:"<<check_sorted(array_sorted, 0, num-1);
			cout<<"  n="<<n<<" time:"<<t1<<endl;
			
			t2.start();
			bs->insert(array_bs,n);
			cout<<"done";
			num = bs->inorder_tree_walk(array_sorted);
			t2.stop();
			cout<<"check bi-search tree result:"<<check_sorted(array_sorted, 0, num-1);
			cout<<"  n="<<n<<" time:"<<t2<<endl<<endl;
			
			delete [] array_bs;
			delete [] array_rb;
			delete [] array_sorted;
			delete rb;
			delete bs;
            rb = NULL;
            bs = NULL;
            array_bs=NULL;
            array_rb =NULL;
            array_sorted=NULL;

		}	
	}
	
  	return 0;
}
  
