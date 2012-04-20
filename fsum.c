/*
 * 输入两个整数 n 和 m,从数列1,2,3.......n 中随意取几个数,使其和等于 m ,要求将其中所有的可能组合列出来.
 * 解：
 * 	类似于背包思想，如果选了一个数i，则递归的求除去i之外，和为m-i的组合
 *	算法时间复杂度为O(2^n)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump(int aux[], int n)
{
	int i;
	for(i=0; i<n; i++)
		if (aux[i])
			printf("%3d", i+1);
	printf("\n");
}

void helper(int dest, int idx, int aux[], int n)
{
	if (dest == 0)
		dump(aux, n);
	if (dest <= 0 || idx==n) 
		return;
	helper(dest, idx+1, aux, n);
	aux[idx] = 1;
	helper(dest-idx-1, idx+1, aux, n);
	aux[idx] = 0;
}

void findCombination(int n, int m)
{
	if (n>m)
		findCombination(m, m);
	int aux[n];
	memset(aux, 0, n*sizeof(int));
	helper(m, 0, aux, n);
}

int main(int argc, char **argv)
{
	int m,n;

	if(argc != 3)
		return -1;
	n = atoi(argv[1]);
	m = atoi(argv[2]);	
	
	findCombination(n, m);

	return 0;
}
