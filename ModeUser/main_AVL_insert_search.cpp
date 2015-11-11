#include "lib_AVL.h"
#include "header.h"

int main( )
{
	avltree at;	
	AVLNode *avl=NULL;
	AVLNode *searched_node;
	int i,key,a,value;
	int list_of_keys[MAX_INPUT_SIZE],list_of_values[MAX_INPUT_SIZE];
	int no_of_keys;
	char bf_update_reqd;
	char input_filename[100];
	//clock_t Start, Time;
	FILE *fp_inorder=fopen("AVL_inorder.out","w");
	FILE *fp_postorder=fopen("AVL_postorder.out","w");

	printf("\nPlease enter the input-filename:");
	scanf("%s",input_filename);

	//read input from file	
	FILE *fp_in=fopen(input_filename,"r");
	fscanf(fp_in,"%d",&no_of_keys);
	for(i=0;i<no_of_keys;i++)
		fscanf(fp_in,"\n%d %d",&list_of_keys[i],&list_of_values[i]);
	fclose(fp_in);

	//Start = clock();
	//insert all the keys from the file
	for(i=0;i<no_of_keys;i++)
	{
		avl=at.insert(avl,list_of_keys[i],list_of_values[i],&bf_update_reqd);
		at.create_root (avl) ;
	}
	//Time = clock() - Start; // time in micro seconds
	//printf("\nTime for Insertion in AVL=%lf\n",Time/(double)CLOCKS_PER_SEC);

	
	//printf("\nAVL_inorder.out:\n");
	at.display_inorder(avl,fp_inorder);
	//printf("\n\n");
	//printf("\nAVL_postorder.out:\n");
	at.display_postorder(avl,fp_postorder);
	//printf("\n\n");
	

	/*Start = clock();
	//search all keys
	for(i=0;i<no_of_keys;i++)
	{
		searched_node=at.searchtree(avl,list_of_keys[i]) ;
		if(searched_node!=NULL)
			printf("key %d found at %u, Value=%d\n",list_of_keys[i],searched_node,searched_node->value);
		else
		if(searched_node==NULL)
			printf("key %d not found\n",list_of_keys[i]);
	}
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Searching in AVL=%lf\n",Time/(double)CLOCKS_PER_SEC);
	*/
	
	return 0;
}
