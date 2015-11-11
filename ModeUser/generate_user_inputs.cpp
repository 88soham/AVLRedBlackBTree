#include "header.h"

#define MAX_KEY 10000
#define MAX_VAL 100

main()
{
	int i,n,rand_key,rand_val;
	int *input;
	FILE* fp_out=fopen("user_input.txt","w");	

	srand((unsigned)time(NULL));

	printf("\n Enter the number of keys:");
	scanf("%d",&n);
	fprintf(fp_out,"%d",n);

	for(i=0;i<n;i++)
	{
		rand_key=rand()%MAX_KEY;
		rand_val=rand()%MAX_VAL;

		fprintf(fp_out,"\n%d %d",rand_key,rand_val);		
	}

	fclose(fp_out);
}
