#include <stdio.h>

#define N 8

int main()
{
	int a[N] = {4,2,2,6,5,2,4,1};  //42651
	int i,j;
	
	printf("%d",a[0]);
	
	for(i=1;i<N;i++)//被对比的数
	{		
		for(j=0;j<i;j++)//去跟i对比的数
		{
			if(a[j] == a[i])
				break;
			if(j == i-1)//一直对比到这个数的上一个数为止
				printf("%d",a[i]);	
		}	
	}
	
	printf("\n");
	return 0;
}