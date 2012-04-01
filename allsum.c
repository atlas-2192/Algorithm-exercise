/*
 * 问题：给定一个含有n个元素的整形数组a，再给定一个和sum，求出数组中满足给定和的所有元素组合
 * 解法：
 *    把sum看成一个包裹的容量，数组的元素看成石头的重量，题目可以转化为求石头的组合，使组合
 * 内的石头刚好放进包裹里。递归解法：包裹容量为sum，先把一块重量为 m 的石头放进去，剩下包裹
 * 容量为 (sum - m), 接下来递归地求在包裹容量为(sum - m)的前提下，有多少种石头的组合。
 * 算法：
 * 1 先把石头的重量按照从小到大排序
 * 2 用一个flag数组标记当前放入包裹的石头
 * 3 优先选择重量大的石头放入包裹，可以减少递归的次数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylib.h"

int len, *flag, count;

/* 从数组a[0]...a[t]找出和等于sum的组合 */
void how_many_sum(int *a, int sum, int t)  
{  
	int i, success;  
   
	if (sum == 0) 
	{  
		count++;
//		printf("找到一个组合\n");  
		for (i = 0; i < len; i++)
		{  
			if (flag[i]) 
				printf("%d ", a[i]);  
		}  
		printf("\n");  
		return;  
	}  
   
	success = 0;  
	for (i = t; i >= 0; i--)
	{  
		if (flag[i] == 0 && (sum - a[i]) >= 0)
		{  
			flag[i] = 1;  
//			printf("把%d放入包裹，剩下容量为%d\n", a[i], sum-a[i]);  
			how_many_sum(a, sum - a[i], i-1);  
//			printf("丢弃%d\n", a[i]);  
			flag[i] = 0;  
			success = 1;  
		}  
	} 

//	if (success == 0) 
//		printf("无解\n");  
}  

int main(void)
{
	int 	sum, i, j, trace;
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

	flag = malloc(sizeof(int)*len);
	memset(flag, 0, sizeof(int)*len);
	how_many_sum(array, sum, len-1);
	printf("There are %d result in all.\n", count);

	free(flag);
	return 0;
}
