/*
 * 找出超过总数1/4的那个数
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int findid(int *array, int len);

int main(void)
{
	int 	len, id;
	int	array[Max];

	input_array(array, &len);

	id = findid(array, len);
	printf("The one over 1/4 is: %d\n", id);

	return 0;
}

int findid(int *array, int len)
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
/*			if(isin(array[i]))
			{
				if(isin(candidate))
					ntimes = 0;
				else
					ntimes--;
				continue;
			}
*/
			if(candidate == array[i])
				ntimes += 3;
			else
				ntimes--;
		}
	}
	
	return candidate;
}
