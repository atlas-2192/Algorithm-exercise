/*
 * 问题：给一组数中，从中选出部分数字，使这些数字的和最接近与给定值sum?
 * 类似与背包问题，递归子结构为:
 * 将数组拍好序放入数组array[n]中，有：
 * 	record[i][j] = max{ record[i-1][j], record[i-1][j-array[i]] + array[i] };
 * 其中record[i][j]意义为在j范围内，从前i个数中选出最大的一个。由于在范围sum内，
 * 数字的和不超过sum，则其中最大的那个即最接近sum的那个。
 * 例如对数字1, 3, 5, 7, 9,求最接近11的和则起record表如下：
 *  i  |array|  0   1   2   3   4   5   6   7   8   9  10  11   
 *-----|-----|--------------------------------------------------
 *  0  |  1  |  0   1   1   1   1   1   1   1   1   1   1   1
 *  1  |  3  |  0   1   1   3   4   4   4   4   4   4   4   4 
 *  2  |  5  |  0   1   1   3   4   5   6   6   8   9   9   9
 *  3  |  7  |  0   1   1   3   4   5   6   7   8   9   10  11 
 *  4  |  9  |  0   1   1   3   4   5   6   7   8   9   10  11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylib.h"

int main(void)
{
	int 	len, sum, i, j, trace;
	int	array[Max];
	int	**record;

	input_array(array, &len);
	quick_sort(array, 0, len-1);
	print_array(array, len);

	setbuf(stdin, NULL);
	printf("Please input the sum: ");
	if(scanf("%d", &sum) !=  1)
	{
		perror("Input error");
		return -1;
	}

	record = (int **) malloc(sizeof(int*)*len);
	for(i = 0; i < len; i++)
	{
		record[i] = (int *) malloc(sizeof(int)*(sum+1));	
		memset(record[i], 0, sizeof(int)*(sum+1));
	}

	if(sum > array[0])
		for(i = array[0]; i <= sum; i++)
			record[0][i] = array[0];

	for(i = 1; i < len; i++)
	{
		for(j = 0; j <= sum; j++)
		{
			if(j >= array[i] && record[i-1][j-array[i]]+array[i] > record[i-1][j])
				record[i][j] = record[i-1][j-array[i]] + array[i];
			else
				record[i][j] = record[i-1][j];
		}
	}
	trace = record[len-1][sum];
	printf("The num that closest to sum '%d' is : %d\n", sum, trace);
	printf("They are :\n");

	j = sum;
	for(i = len-2; i >= 0; i--)
	{
		if(trace <= 0)
			break;
		if(record[i][j] == trace)
			continue;
		j -= array[i+1];
		trace -= array[i+1];
		printf("%d ", array[i+1]);
	}
	if(trace > 0)
		printf("%d\n", trace);
	else
		printf("\n");

	return 0;
}
