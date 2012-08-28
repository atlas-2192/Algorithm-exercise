#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * shift_and只能处理pattern不超过64位的情况，不过该方法扩展
 * 起来也很简单，只是随着pattern的长度增加，性能也会线性下降
 */
int shift_and(char *text, char *pattern)
{
    int i, len, plen;
    uint64_t map[256], record;

    assert(text && pattern);
    memset(map, 0, 256*sizeof(uint64_t));

    plen = strlen(pattern);
    for (i = 0; i < plen; i++)
        map[pattern[i]] |= 1 << i;

    len = strlen(text);
    record = 0;
    for (i = 0; i < len; i++) {
        record = ((record << 1) | 1) & map[text[i]];
        if (record & (1 << plen - 1))
            return i - plen + 1;
    }

    return -1;
}

int main(void)
{
	int     len;
	char    text[1000];
	char	pattern[20];

	printf("Input the text string to be searched: ");
	fgets(text, 1000, stdin);
	len = strlen(text);
	if (text[len-1] == '\n')
		text[len-1] = '\0';

	printf("Input the seatching pattern string: ");
	fgets(pattern, 20, stdin);
	len = strlen(pattern);
	if (pattern[len-1] == '\n')
		pattern[len-1] = '\0';
	
	printf("Match: %d\n",shift_and(text, pattern));

    return 0;
}
