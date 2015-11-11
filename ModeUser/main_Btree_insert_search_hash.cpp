#include "lib_BTree_binsearch.h"
#include "header.h"

main()
{
	int i,j,k;
	BtreeNode* myBtreeRoot[S];
	Btree myBtree[S];
	int key,value;
	int list_of_keys[MAX_INPUT_SIZE],list_of_values[MAX_INPUT_SIZE];
	int no_of_keys,bucket_no;
	char input_filename[100];
	FILE *fp_sorted=fopen("BTreeHash_sorted.out","w");
	FILE *fp_level=fopen("BTreeHash_level.out","w");
	//clock_t Start, Time;

	for(bucket_no=0;bucket_no<S;bucket_no++)
	{
		myBtreeRoot[bucket_no]=new BtreeNode;	
		intitialize_node(myBtreeRoot[bucket_no]);
	}

	printf("\nPlease enter the input-filename:");
	scanf("%s",input_filename);

	//insert all the keys from the random file
	FILE *fp_in=fopen(input_filename,"r");
	fscanf(fp_in,"%d",&no_of_keys);
	for(i=0;i<no_of_keys;i++)
		fscanf(fp_in,"\n%d %d",&list_of_keys[i],&list_of_values[i]);
	fclose(fp_in);

	//Start = clock();
	for(i=0;i<no_of_keys;i++)
	{
		bucket_no=list_of_keys[i]%S;
		myBtreeRoot[bucket_no]=myBtree[bucket_no].insert(myBtreeRoot[bucket_no],list_of_keys[i],list_of_values[i]);	
		myBtree[bucket_no].create_root(myBtreeRoot[bucket_no]);
		//printf(" [root[0]=%d] [root[1]=%d] [root[2]=%d] children:[",myBtreeRoot[bucket_no]->keys[0],myBtreeRoot[bucket_no]->keys[1],myBtreeRoot[bucket_no]->keys[2]);
		//for(j=0;myBtreeRoot[bucket_no]->child_ptrs[j]!=NULL;j++)
		//	printf("%d,%d,%d  ",myBtreeRoot[bucket_no]->child_ptrs[j]->keys[0],myBtreeRoot[bucket_no]->child_ptrs[j]->keys[1],myBtreeRoot[bucket_no]->child_ptrs[j]->keys[2]);
		//printf("]\n\n");
	}
	//Time = clock() - Start; // time in micro seconds
	//printf("\nTime for Insertion in BTREEhash=%lf\n\n",Time/(double)CLOCKS_PER_SEC);


	for(bucket_no=0;bucket_no<S;bucket_no++)
	{
		//print the tree- levels
		//printf("\nBtree_level.out [bucket# %d]\n",bucket_no);
		myBtree[bucket_no].display_level(myBtreeRoot[bucket_no],fp_level);
		//print the tree- sorted
		fprintf(fp_level,"\n");
		//printf("Btree_sorted.out [bucket# %d]\n",bucket_no);
		myBtree[bucket_no].display_sorted(myBtreeRoot[bucket_no],fp_sorted);
		//printf("\n\n");
		fprintf(fp_sorted,"\n");
	}

	/*
	Start = clock();
	//search the keys
	for(i=0;i<no_of_keys;i++)
	{
		bucket_no=list_of_keys[i]%S;
		value=myBtree[bucket_no].search(myBtreeRoot[bucket_no],list_of_keys[i]);
		//if(value==-1)
		//	printf("\n Key %d not found.",list_of_keys[i]);
		//else
		//	printf("\n Key %d found with value %d",list_of_keys[i],value);	
	}
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Searching in BTREEhash=%lf\n",Time/(double)CLOCKS_PER_SEC);
	*/
}
