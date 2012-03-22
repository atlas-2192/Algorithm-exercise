#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
* E(q-1) = {k ∈ π*[q-1] && P(k+1) is the prefix of P(q)}
* π[q] = 1 + max{k ∈ E(q-1)}	if E(q-1) != ∅
*      = 0			if E(q-1) == ∅
*/
void comp_prefix(char *str, int *map)
{
	int	len, i, k;

	len = strlen(str);
	map[0] = -1;
	k = -1;

	for(i = 1; i < len; i++)
	{
		while(k > -1 && str[k+1] != str[i])
			k = map[k];
		if(str[k+1] == str[i])
			k++;
		map[i] = k;
	}
}

void kmp_matcher(char *ostr, char *mstr)
{
	int	m, n, i, q;
	int	*map;

	n = strlen(ostr);
	m = strlen(mstr);
	q = -1;

	map = (int *)malloc(sizeof(int)*m);
	comp_prefix(mstr, map);

	for(i = 0; i < n; i++)
	{
		while(q > -1 && mstr[q+1] != ostr[i])
			q = map[q];
		if(mstr[q+1] == ostr[i])
			q++;
		if(q == m-1)
		{
			printf("%d ", i-m+1);
			q = map[q];
		}
	}
	printf("\n");
}


int main()
{
	int len;
	char	ostr[1000];
	char	mstr[20];

	printf("Input the string to be searched: ");
	fgets(ostr, 1000, stdin);
	len = strlen(ostr);
	if(ostr[len-1] == '\n')
		ostr[len-1] = '\0';

	printf("Input the seatching mod: ");
	fgets(mstr, 20, stdin);
	len = strlen(mstr);
	if(mstr[len-1] == '\n')
		mstr[len-1] = '\0';
	
	printf("The matched at (start from 0): ");
	kmp_matcher(ostr, mstr);

	return 0;	
}
