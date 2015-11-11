#include "lib_BTree_binsearch.h"
#include "header.h"

main()
{
	int i,j,k;
	BtreeNode* myBtreeRoot=new BtreeNode;
	Btree myBtree;
	int key,value;
	int list_of_keys[MAX_INPUT_SIZE],list_of_values[MAX_INPUT_SIZE];
	int no_of_keys;
	char input_filename[100];
	//clock_t Start, Time;
	FILE *fp_sorted=fopen("BTree_sorted.out","w");
	FILE *fp_level=fopen("BTree_level.out","w");
	
	intitialize_node(myBtreeRoot);

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
		myBtreeRoot=myBtree.insert(myBtreeRoot,list_of_keys[i],list_of_values[i]);	
		myBtree.create_root(myBtreeRoot);
		//printf(" [root[0]=%d] [root[1]=%d] [root[2]=%d] children:[",myBtreeRoot->keys[0],myBtreeRoot->keys[1],myBtreeRoot->keys[2]);
		//for(j=0;myBtreeRoot->child_ptrs[j]!=NULL;j++)
		//	printf("%d,%d,%d  ",myBtreeRoot->child_ptrs[j]->keys[0],myBtreeRoot->child_ptrs[j]->keys[1],myBtreeRoot->child_ptrs[j]->keys[2]);
		//printf("]\n\n");
	}
	//Time = clock() - Start; // time in micro seconds
	//printf("\nTime for Insertion in BTREE=%lf\n\n",Time/(double)CLOCKS_PER_SEC);


	//print the tree- levels
	//printf("Btree_level.out\n");
	myBtree.display_level(myBtreeRoot,fp_level);
	//print the tree- levels
	//printf("Btree_sorted.out\n");
	myBtree.display_sorted(myBtreeRoot,fp_sorted);

	/*
	Start = clock();
	//search the keys
	for(i=0;i<no_of_keys;i++)
	{
		value=myBtree.search(myBtreeRoot,list_of_keys[i]);
		if(value==-1)
			printf("\n Key %d not found.",list_of_keys[i]);
		else
			printf("\n Key %d found with value %d",list_of_keys[i],value);	
	}
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Searching in BTREE=%lf\n",Time/(double)CLOCKS_PER_SEC);
	*/
}
