#include "lib_AVL.h"
#include "header.h"


int main( )
{
	avltree at[S] ;
	AVLNode *avl[S];
	AVLNode *searched_node;
	int no_of_keys;
	int list_of_keys[MAX_INPUT_SIZE],list_of_values[MAX_INPUT_SIZE];
	int key,bucket_no,i,value;
	char bf_update_reqd[S];
	char input_filename[100];
	clock_t Start, Time;

	//printf("\nPlease enter the input-filename:");
	//scanf("%s",input_filename);

	FILE *fp_in=fopen("random_input.txt","r");
	fscanf(fp_in,"%d",&no_of_keys);
	for(i=0;i<no_of_keys;i++)
		fscanf(fp_in,"\n%d %d",&list_of_keys[i],&list_of_values[i]);
	fclose(fp_in);
	
	for(i=0;i<S;i++)
		avl[i]=NULL;

	Start = clock();
    for(i=0;i<no_of_keys;i++)
	{
		bucket_no=list_of_keys[i]%S;
		avl[bucket_no] = at[bucket_no].insert (avl[bucket_no], list_of_keys[i],list_of_values[i], &bf_update_reqd[bucket_no] ) ;
		at[bucket_no].create_root (avl[bucket_no]);
	}
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Insertion in AVLhash=%lf\n",Time/(double)CLOCKS_PER_SEC);
	
	/*
	for(i=0;i<S;i++)
	{
		printf("\nHashed AVL tree %d Inorder Traversal:\n",i);
		at[i].display_inorder(avl[i]);
		printf("\n\n");
		printf("\nHashed AVL tree %d Postorder Traversal:\n",i);
		at[i].display_postorder(avl[i]);
		printf("\n\n");
	}
	*/


	Start = clock();
	//search all keys
	for(i=0;i<no_of_keys;i++)
	{
		//fscanf(fp_in,"\n%d %d",&key,&value);
		bucket_no=list_of_keys[i]%S;
		searched_node=at[bucket_no].searchtree(avl[bucket_no],list_of_keys[i]) ;
		//if(searched_node!=NULL)
		//	printf("key %d found at %u in bucket#%d,Value=%d\n",list_of_keys[i],searched_node,bucket_no,searched_node->value);
		//else
		//	printf("key %d not found\n",list_of_keys[i]);
	}
	Time = clock() - Start; // time in micro seconds

	printf("\nTime for Searching in AVLhash=%lf\n",Time/(double)CLOCKS_PER_SEC);
}
