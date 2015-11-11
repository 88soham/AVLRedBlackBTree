#include "header.h"

main()
{
	int i,n,rand_pos;
	int *input;
	FILE* fp_out=fopen("random_input.txt","w");	

	srand((unsigned)(time(NULL)));

	printf("\n Enter the number of keys:");
	scanf("%d",&n);

	input=(int *)malloc(n*sizeof(int));

	for(i=0;i<n;i++)
		input[i]=-1;

	for(i=0;i<n;)
	{
		rand_pos=rand()%n;
		
		if(input[rand_pos]==-1)
		{
			input[rand_pos]=i+1;
			i++;
			//printf("\n%d",i);
		}			
	}

	fprintf(fp_out,"%d",n);
	for(i=0;i<n;i++)
		fprintf(fp_out,"\n%d %d",input[i],2*input[i]);

	fclose(fp_out);
}
