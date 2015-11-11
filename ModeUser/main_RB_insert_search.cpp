#include <map>
#include "header.h"


main()
{  
	int i,key,value;
	int list_of_keys[MAX_INPUT_SIZE],list_of_values[MAX_INPUT_SIZE];
	int no_of_keys;
	clock_t Start, Time;

    map<int,int> mapRB;
    map<int,int>::iterator start;
	map<int,int>::iterator search;

    start=mapRB.begin();
	
	
	char input_filename[100];

	printf("\nPlease enter the input-filename:");
	scanf("%s",input_filename);

	//read input from file	
	FILE *fp_in=fopen(input_filename,"r");
	fscanf(fp_in,"%d",&no_of_keys);
	for(i=0;i<no_of_keys;i++)
		fscanf(fp_in,"\n%d %d",&list_of_keys[i],&list_of_values[i]);
	fclose(fp_in);

	Start = clock();
	//insert all the keys from the file
	for(i=0;i<no_of_keys;i++)
		mapRB.insert(start,pair<int,int>(list_of_keys[i],list_of_values[i]));
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Insertion in RB=%lf\n",Time/(double)CLOCKS_PER_SEC);
	
	/*
	//printed in inorder
	printf("\nRed Black Tree");
    for(start=mapRB.begin();start!=mapRB.end();start++)
    	printf(" %d",(*start).first);

	printf("\n");
	*/


	Start = clock();
	for(i=0;i<no_of_keys;i++)
	{
        search=mapRB.find(list_of_keys[i]);
        //if(search->second!=0)
        //    printf("\nKey %d has been found in the Red-Black Tree, Value=%d",search->first,search->second);
        //else
        //    printf("\nKey has not been found in the Red-Black Tree");
    }
	Time = clock() - Start; // time in micro seconds
	printf("\nTime for Searching in RB=%lf\n",Time/(double)CLOCKS_PER_SEC);
}
