/*
 * 输出一个数组的全排列
 */
#include <stdio.h>

#define Max 100

static int num = 1;

void exchange(int *p1, int *p2)
{
	int tmp;
	
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
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

void print_array(int array[], int length)
{
	int j;
 
	for (j = 0; j < length; j++)
		printf("%d ", array[j]);

	printf("\n");
}

void allp(int array[], int s, int e)
{
	int i;

	if(s == e)
	{
		printf("%d:\t", num++);
		print_array(array, e+1);
		return;
	}

	for(i = s; i <= e; i++)
	{
		exchange(&array[i], &array[s]);
		allp(array, s+1, e);
		exchange(&array[i], &array[s]);
	}
}

int main(void)
{
	int array[100];
	int len;
	
	input_array(array, &len);
	allp(array, 0, len-1);

	return 0;
}
