#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "mylib.h"

void print_array(int array[], int length)
{
	int j;

	printf("The sorted array is:\n");
 
	for (j = 0; j < length; j++)
		printf("%d ", array[j]);

	printf("\n");
}

void rand_array(int array[],int length)
{
	int i;

	srand((unsigned) time(0));

	for(i = 0; i < length; i++)
	{
		array[i] = rand() % 10000;
	} 
}

void input_array(int array[], int *length)
{
	int i = 0, ret;
	printf("Please input numbers and end with a SPACE + Non-numberic char ==>\n");

	while(ret = scanf("%d", &array[i]) == 1)
	{
		i++;
		if(i == Max)
		{
			printf("\nArray is full ! \n");
			break;
		}
	} 
	
	if(ret != 1)
		printf("%d numbers! \n", i);
	
	*length = i;
}

void insert_sort(int array[], int length)
{
	int i, j, key; 
	
	for(j = 1; j < length; j++)
	{
		i = j-1;
		key = array[j];
		
		while(i >= 0 && array[i] > key)
		{
			array[i+1] = array[i];
			i--;
		}
		
		array[i+1] = key;
	}
}

void bubble_sort(int array[], int length)
{
	int i, j, tmp;

	for(j = 0; j < length; j++)
	{
		i = length-1;

		while(i > j)
		{
			if(array[i] < array[i-1])
			{
				tmp = array[i];
				array[i] = array[i-1];
				array[i-1] = tmp;
			}
			
			i--;
		} 
	}
}

void exchange(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int array[], int start, int end)
{
/**************************** Method 1 *************************
**  每一轮迭代开始时，middle = array[start], 对于i小于        **
**  start，array[i]小于等于middle；对于i大于end，             **
**  array[i]大于等于middle；终止时，start == end，此时，      **
**  start左边小于等于middle,start右边大于等于middle，start    **
**  处为middle                                                **
****************************************************************

	while(start < end)
	{
		//中间数在start位置
		while(start < end && array[end] >= array[start])
			end--;
		exchange(&array[start], &array[end]);

		//中间数在end位置
		while(start < end && array[start] <= array[end])
			start++;
		exchange(&array[start], &array[end]);
	}

	return start;

*****************************************************************/


/**************************** Method 2 **************************
** 每一轮迭代开始时，middle = array[start],对于i <= start,     **
** array[i] <= middle; 对于i > end, array[i] >= middle; 终止时 **
** start == end, 此时，array[start] <= middle, 再交换middle和  **
** array[i]即可                                                **
****************************************************************/

	int mid = start;

	while(start < end)
	{
		while(start < end && array[end] >= array[mid])
			end--;

		while(start < end && array[start] <= array[mid])
			start++;

		exchange(&array[start], &array[end]);
	}

	exchange(&array[start], &array[mid]);

	return start;

/****************************************************************/


/************************** Method 3 ****************************
** 每次迭代时均满足以下条件：1）如果start <= k <= i,则array[k] **
** <= middle; 2）如果i+1 <= k <= j-1，则array[k] > x; 3）如果  **
** k == r,则array[k] = middle；终止时，k = end，此时将middle   **
** 与array[i+1]交换即可                                        **
*****************************************************************

	int i, j;
	i = start - 1;
	middle = array[end];

	for(j = start; j < end; j++)
	{
		if(array[j] <= middle)
		{
			i++;
			exchange(&array[i], &array[j]);
		}
	}

	exchange(&array[end], &array[i+1]);

	return i+1;

****************************************************************/


/*************************** Method 4 ***************************
** 每次迭代开始时，middle = array[end],对于k <= i,array[k] <=  **
** middle; 对于k >= j, array[k] >= middle; 终止时，i>=j，此时  **
** j左边的均小于等于middle，右边大于等于middle                 **
*****************************************************************

	int i = start - 1;
	int j = end + 1; 
	int middle = array[start];
	
	while(true)
	{
		do{
			j--;
		}while(array[j] >= middle)

		do{
			i++;
		}while(array[i] >= middle)

		if(i < j)
			exchange(&array[i], &array[j]);
		else
			return j;
	}

****************************************************************/
}

void quick_sort(int array[], int start, int end)
{
	int position;
	
	if(start < end)
	{
		position = partition(array, start, end);
		quick_sort(array, start, position-1);
		quick_sort(array, position+1, end);
	}
	
}

void merge(int array[], int start, int middle, int end)
{
	int i, j, k;
	int array1[middle-start+1+1];
	int array2[end-middle+1];

	for(i = 0; i <= middle-start; i++)
		array1[i] = array[start+i];

	for(i = 0; i < end-middle; i++)
		array2[i] = array[middle+1+i];

	array1[middle-start+1] = array2[end-middle] = 2147483647; //Max int value

	for(i = start, j = 0, k = 0; i <= end; i++)
	{
		if(array1[j] > array2[k])
		{
			array[i] = array2[k];
			k++;
		}
		else
		{
			array[i] = array1[j];
			j++;
		} 
	}
}

void merge_sort(int array[], int start, int end)
{
	int middle;

	if(start < end)
	{
		middle = (start + end) / 2;	
		merge_sort(array, start, middle);
		merge_sort(array, middle + 1, end);
		merge(array, start, middle, end);
	}
}

void shell_sort(int array[], int length)
{
	int i, j, k, inc, key;
	
	//从length/2为初始跨度分组
	for(inc = length/2; inc > 0; inc /= 2)
	{
		//跨度长度个分组
		for(i = 0; i < inc; i++)
		{
			//为每个分组进行插入排序
			for(j = i+inc ; j < length; j += inc)
			{
				k = j - inc;
				key = array[j];

				while(k >= 0 && array[k] > key)
				{
					array[k+inc] = array[k];
					k -= inc;	
				}
				array[k+inc] = key;	
			}
		}  
	}
	
}

void max_heapify(int array[], int length, int root)
{
	int max, l, r;
	
	while(root <= length)
	{
		l = lChild(root);
		r = rChild(root);

		if(l <= length && array[root-1] < array[l-1])
			max = l;
		else
			max = root;

		if(r <= length && array[max-1] < array[r-1])
			max = r;

		if(root != max)
		{
			exchange(&array[root-1], &array[max-1]);
			root = max;
		}
		else
			break;
	}
}

void heap_sort(int array[], int length)
{
	int i;

	for(i = length/2; i > 0; i--)
		max_heapify(array, length, i);

	for(i = length-1; i > 0; i--)
	{
		exchange(&array[0], &array[i]);
		max_heapify(array, i, 1);
	}
}

void count_sort(int array[], int length, int num)
{
	int j, index, dv, re;
	int count[10];
	int brray[length];

	for(j=1, dv=10; j<num; j++)
		dv *= 10;
	re = dv/10;

	for(j=0; j<10; j++)
		count[j] = 0;

	for(j=0; j<length; j++)
	{
		index = (array[j]%dv)/re;
		count[index]++; 
	}
	
	for(j=1; j<10; j++)
		count[j] += count[j-1];

	for(j=length-1; j>=0 ; j--)
	{
		index = (array[j]%dv)/re;
		brray[count[index]-1] = array[j];
		count[index]--;
	}

	for(j=0; j<length; j++)
		array[j] = brray[j];
}  

void radix_sort(int array[], int length)
{
	int i;

	for(i=1; i<5; i++)
	{
		count_sort(array, length, i);
	}
}

