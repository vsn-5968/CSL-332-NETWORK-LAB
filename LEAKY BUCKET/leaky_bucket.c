#include <stdio.h>
void main()
{
	int in,out,bsize,n,bucket=0;
	printf("Enter the bucket size: ");
	scanf("%d",&bsize);
	printf("Enter the number of inputs: ");
	scanf("%d",&n);
	printf("Enter the outgoing packet rate: ");
	scanf("%d",&out);
	while(n!=0)
	{
		printf("\nEnter the incoming packet size: ");
		scanf("%d",&in);
		if(in<=(bsize-bucket))
		{
			bucket+=in;
			printf("\nBucket status: %d out of %d",bucket,bsize);
		}
		else
		{
			printf("\nDropped packets: %d \n ",in - (bsize-bucket));
			bucket=bsize;
			printf("\nBucket status: %d out of %d",bucket,bsize);
		}
		bucket=bucket-out;
		printf("\nAfter outgoing, bucket status : %d out of %d\n",bucket,bsize);
    		n--;                                                                                                                                                        
	}
}
