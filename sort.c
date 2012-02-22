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
	}

	end = (double) nowTime;
	printf("Sort Method spens %lfms\n", end - start);

	print_array(my_array, length);

	return 0;
}
