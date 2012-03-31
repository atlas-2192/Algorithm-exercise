#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "mylib.h"

int my_array[Max];

void usage()
{
	printf("\
Usage : sort -a -n\n\
	-a, array types\n\
		'i' for input array; 'r' for randam array\n\
	-n, sort method\n\
		'1' for insert sort\n\
		'2' for bubble sort\n\
		'3' for merge sort\n\
		'4' for quick sort\n\
		'5' for	shell sort\n\
		'6' for heap sort\n\
		'7' for	radix sort\n");
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
		merge_sort(my_array, 0, length-1);
		break;
	case 4:
		printf("quick sort:\n");
		quick_sort(my_array, 0, length-1);
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
	default:
		printf("quick sort:\n");
		quick_sort(my_array, 0, length-1);
	}

	end = (double) nowTime;
	printf("Sort Method spens %lfms\n", end - start);

	print_array(my_array, length);

	return 0;
}
