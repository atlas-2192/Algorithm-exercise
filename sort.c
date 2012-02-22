#include <stdio.h>
#include <time.h>

#define Max 100
#define nowTime clock()/CLOCKS_PER_SEC

void printArray(int array[], int length)
{
	int j;

	printf("The sorted array is:\n");
 
	for (j = 0; j <= length; j++)
		printf("%d ", array[j]);

	printf("\n");
}

void insertSort(int array[], int length)
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

void bubbleSort(int array[], int length)
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

int main(void)
{
	int length = 0, ret;
	int array[Max];
	double start, end;

	printf("Please input numbers and end with 'SPACE' + ';' ==>\n");

	while(ret = scanf("%d", &array[length]) == 1)
	{
		if(length == Max-1)
		{
			printf("\nArray is full ! \n");
			break;
		}
		length ++;
	} 
	
	if(ret != 1)
	{
		length--;
		printf("%d numbers! \n", length+1);
	}

	start = (double) nowTime;

	//insertSort(array, length);	
	bubbleSort(array, length);

	end = (double) nowTime;
	
	printf("Sort Method spens %lfms\n", end - start);

	printArray(array, length);

	return 0;
}
