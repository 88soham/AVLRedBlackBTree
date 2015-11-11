#include "header.h"
#include <map>


main()
{   
	int i,key,value;
	int list_of_keys[MAX_INPUT_SIZE],list_of_values[MAX_INPUT_SIZE];
	int no_of_keys,bucket_no;
	char flag_found;
	clock_t Start, Time;

	map<int,int> mapRB_hash[S];
	map<int,int>::iterator start_hash[S];
	map<int,int>::iterator search;

	for(bucket_no=0;bucket_no<S;bucket_no++)
		start_hash[bucket_no]=mapRB_hash[bucket_no].begin();

	
	char input_filename[100];

	printf("\nPlease enter the input-filename:");
	scanf("%s",input_filename);

	FILE *fp_in=fopen(input_filename,"r");
	fscanf(fp_in,"%d",&no_of_keys);
	for(i=0;i<no_of_keys;i++)
		fscanf(fp_in,"\n%d %d",&list_of_keys[i],&list_of_values[i]);
	fclose(fp_in);

	Start = clock();
	//insert all the keys from the file
	for(i=0;i<no_of_keys;i++)
	{
		bucket_no=list_of_keys[i]%S;  
		mapRB_hash[bucket_no].insert(start_hash[bucket_no], pair<int,int>(list_of_keys[i],list_of_values[i]));
	}
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Insertion in RBhash=%lf\n",Time/(double)CLOCKS_PER_SEC);

	/*
	for(bucket_no=0;bucket_no<S;bucket_no++)
	{
		printf("\nRed Black Tree Hashed [bucket#%d]",bucket_no);
		for(start_hash[bucket_no]=mapRB_hash[bucket_no].begin();start_hash[bucket_no]!=mapRB_hash[bucket_no].end();start_hash[bucket_no]++)
			printf("%d ",(*start_hash[bucket_no]).first);
	}
	*/
           
	Start = clock();                     
	for(i=0;i<no_of_keys;i++)
	{
		bucket_no=list_of_keys[i]%S;
		search=mapRB_hash[bucket_no].find(list_of_keys[i]);
		//if(search->second!=0)
		//	printf("\nKey %d is found in RB Tree [bucket#%d], Value=%d",search->first,bucket_no,search->second); 
		//else		
		//	printf("\nKey %d is not found in RB Tree",list_of_keys[i]); 
	}	
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Searching in RBhash=%lf\n",Time/(double)CLOCKS_PER_SEC);   
}
