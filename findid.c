/*
 * 找出超过总数1/4的那个数(两种方法）
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

#define  Method1

int findid1(int *array, int len);
void findid2(int *array, int len, int *result);

int main(void)
{
	int 	len;
	int	id;
#ifndef Method1 
	int	*ids;
#endif
	int	array[Max];

	input_array(array, &len);

#ifdef Method1
	id = findid1(array, len);
#else
	ids = malloc(sizeof(int)*3);
	memset(id, 0, sizeof(int)*3);  
	findid2(array, len, ids);
	id = ids[0];
#endif
	printf("The one over 1/4 is: %d\n", id);

	return 0;
}

int findid1(int *array, int len)
{
	int candidate, i, ntimes;
	int test[3], count[3];

	//首先排除最后三个数的干扰
	test[0] = array[len-3];
	test[1] = array[len-2];
	test[2] = array[len-1];
	count[0] = count[1] = count[2] = 1;

	for(i = 0; i < len-3; i++)
	{
		if(array[i] == test[0])
			count[0]++;
		else if(array[i] == test[1])
			count[1]++;
		else if(array[i] == test[2])
			count[2]++;
	}

	if(count[0] > len/4)
		return test[0];
	else if(count[1] > len/4)
		return test[1];
	else if(count[2] > len/4)
		return test[2];

	for(i = ntimes = 0; i < len; i++)
	{
		if(ntimes == 0)
		{
			candidate = array[i];
			ntimes = 3;
		}
		else
		{
			if(candidate == array[i])
				ntimes += 3;
			else
				ntimes--;
		}
	}
	
	return candidate;
}

void findid2(int * ID,int n, int *result)
{  
  /* 
    n       帖子总数， 
    ID      用户ID列表 
    result  储存3个当前遍历到的不同ID 
    nTimes  储存对应ID已遍历到的个数被抵消后的值 
  */  
	int i;  
	int nTimes[] = {0,0,0};  

	for(i=0;i<n;i++)
 	{  
		if(nTimes[0] == 0 && ID[i] != result[1] && ID[i] != result[2])
		{  
			nTimes[0] = 1;  
			result[0] = ID[i];  
		}  
		else if(nTimes[1] == 0 && ID[i] != result[0] && ID[i] != result[2])
		{  
          		nTimes[1] = 1;  
      		    	result[1] = ID[i];  
    		}  
      		else if(nTimes[2] == 0 && ID[i] != result[0] && ID[i] != result[1])
		{  
  		        nTimes[2] = 1;  
  		        result[2] = ID[i];  
  		} 
  		else if(ID[i] != result[0] && ID[i] != result[1] && ID[i] != result[2] )
		{
			nTimes[0] -= 1;  
  		   	nTimes[1] -= 1;  
  			nTimes[2] -= 1;  
  		}
		else if(ID[i] == result[0])
		{  
  			nTimes[0] += 1;  
		}
		else if(ID[i] == result[1])
		{  
 	        	nTimes[1] += 1;  
    		}
		else if(ID[i] == result[2])
		{  
           		nTimes[2] += 1;  
      		}
	}
} 
