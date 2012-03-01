#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Max 1000
#define nowTime clock()/CLOCKS_PER_SEC

int my_array[Max];

void print_array(int array[], int length)
{
	int j;

	printf("The sorted array is:\n");
 
	for (j = 0; j <= length; j++)
		printf("%d ", array[j]);

	printf("\n");
}

void rand_array(int array[],int length)
{
	int i;

	srand((unsigned) time(0));

	for(i = 0; i <= length; i++)
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
		if(i == Max-1)
		{
			printf("\nArray is full ! \n");
			break;
		}
		i ++;
	} 
	
	if(ret != 1)
	{
		i--;
		printf("%d numbers! \n", i+1);
	}
	
	*length = i;
}

void insert_sort(int array[], int length)
{
	int i, j, key; 
	
	for(j = 1; j <= length; j++)
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

	for(j = 0; j <= length; j++)
	{
		i = length;

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
/***************************** 方法1 ***************************
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


/***************************** 方法2 ****************************
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


/****************************** 方法4 ***************************
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
			for(j = i+inc ; j <= length; j += inc)
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

void heap_sort(int array[], int length)
{

}

void radix_sort(int array[], int length)
{

}

void usage()
{
	printf("Usage : sort -a -n\n\
\t-a, array types\n\
\t\t'i' for input array; 'r' for randam array\n\
\t-n, sort method\n\
\t\t'1' for insert sort\n\
\t\t'2' for bubble sort\n\
\t\t'3' for merge sort\n");
}

int main(int argc, char *argv[])
{
	int length = Max-1, ret, input = 1, method = 1;
	double start, end;

	if(argc != 3)
	{
		usage();
		return 0;
	}
	else 
	{
		if(strcmp(argv[1], "-i"))
			input = 1;
		else
			input = 0;
			
		if(!strcmp(argv[2], "-1"))
			method = 1;
		else if(!strcmp(argv[2], "-2"))
			method = 2;
		else if(!strcmp(argv[2], "-3"))
			method = 3;
		else if(!strcmp(argv[2], "-4"))
			method = 4;
		else if(!strcmp(argv[2], "-5"))
			method = 5;
		else if(!strcmp(argv[2], "-6"))
			method = 6;
		else if(!strcmp(argv[2], "-7"))
			method = 7;
		else
			method = 1;	
	}

	if(input)
		rand_array(my_array, length);
	else
		input_array(my_array, &length);

	start = (double) nowTime;

	switch(method){
	case 1:
		printf("Insert sort:\n");
		insert_sort(my_array, length);	
		break;
	case 2:
		printf("bubble sort:\n");
		bubble_sort(my_array, length);
		break;
	case 3:
		printf("merge sort:\n");
		merge_sort(my_array, 0, length);
		break;
	case 4:
		printf("quick sort:\n");
		quick_sort(my_array, 0, length);
		break;
	case 5:
		printf("shell sort:\n");
		shell_sort(my_array, length);
		break;
	case 6:
		printf("heap sort:\n");
		heap_sort(my_array, length);
		break;
	case 7:
		printf("radix sort:\n");
		radix_sort(my_array, length);
		break;
	}

	end = (double) nowTime;
	printf("Sort Method spens %lfms\n", end - start);

	print_array(my_array, length);

	return 0;
}
