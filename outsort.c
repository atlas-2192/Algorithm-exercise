/*
 * Writen by kenby
 */
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_INT ~(1<<31)
#define MIN_INT 1<<31

//#define DEBUG

#ifdef DEBUG
#define debug(...) debug( __VA_ARGS__) 
#else
#define debug(...)
#endif

#define MAX_WAYS 100

typedef struct run_t {
	int *buf;		/* 输入缓冲区 */
	int length;		/* 缓冲区当前有多少个数 */
	int offset;		/* 缓冲区读到了文件的哪个位置 */
	int idx;		/* 缓冲区的指针 */
} run_t;

static unsigned int K;				/* K路合并 */
static unsigned int BUF_PAGES;		/* 缓冲区有多少个page */
static unsigned int PAGE_SIZE;		/* page的大小 */
static unsigned int BUF_SIZE;		/* 缓冲区的大小, BUF_SIZE = BUF_PAGES*PAGE_SIZE */

static int *buffer;					/* 输出缓冲区 */

static char input_prefix[] = "foo_";
static char output_prefix[] = "bar_";

static int ls[MAX_WAYS];			/* loser tree */

void swap(int *p, int *q);
int partition(int *a, int s, int t);
void quick_sort(int *a, int s, int t);
void adjust(run_t ** runs, int n, int s);
void create_loser_tree(run_t **runs, int n);
long get_time_usecs();
void k_merge(run_t** runs, char* input_prefix, int num_runs, int base, int n_merge);
void usage();


int main(int argc, char **argv)
{
	char 				filename[100];
	unsigned int	data_size;
	unsigned int 	num_runs;				/* 这轮迭代时有多少个归并段 */
	unsigned int	num_merges;				/* 这轮迭代后产生多少个归并段 num_merges = num_runs/K */
	unsigned int	run_length;				/* 归并段的长度，指数级增长 */
	unsigned int	num_runs_in_merge;		/* 一般每个merge由K个runs合并而来，但最后一个merge可能少于K个runs */
	int					fd, rv, i, j, bytes;
	struct stat 		sbuf;

	if (argc != 3) {
		usage();
		return 0;
	}
	long start_usecs = get_time_usecs();

	strcpy(filename, argv[1]);
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("can't open file %s\n", filename);
		exit(0);
	}
	rv = fstat(fd, &sbuf);
	data_size = sbuf.st_size;

	K = atoi(argv[2]);
	PAGE_SIZE = 4096;							/* page = 4KB */
	BUF_PAGES = 32;
	BUF_SIZE = PAGE_SIZE*BUF_PAGES;
	num_runs = data_size / PAGE_SIZE;			/* 初始时的归并段数量，每个归并段有4096 byte, 即1024个整数 */
	buffer = (int *)malloc(BUF_SIZE);

	run_length = 1;
	run_t **runs = (run_t **)malloc(sizeof(run_t *)*(K+1));
	for (i = 0; i < K; i++) {
		runs[i] = (run_t *)malloc(sizeof(run_t));
		runs[i]->buf = (int *)calloc(1, BUF_SIZE+4);
	}
	while (num_runs > 1) {
		num_merges = num_runs / K;
		int left_runs = num_runs % K;
		if(left_runs > 0) num_merges++;
		for (i = 0; i < num_merges; i++) {
			num_runs_in_merge = K;
			if ((i+1) == num_merges && left_runs > 0) {
				num_runs_in_merge = left_runs;
			}
			int base = 0;
			printf("Merge %d of %d,%d ways\n", i, num_merges, num_runs_in_merge);
			for (j = 0; j < num_runs_in_merge; j++) {
				if (run_length == 1) {
					base = 1;
					bytes = read(fd, runs[j]->buf, PAGE_SIZE);
					runs[j]->length = bytes/sizeof(int);
					quick_sort(runs[j]->buf, 0, runs[j]->length-1);
				} else {
					snprintf(filename, 20, "%s%d.dat", input_prefix, i*K+j);
					int infd = open(filename, O_RDONLY);
					bytes = read(infd, runs[j]->buf, BUF_SIZE);
					runs[j]->length = bytes/sizeof(int);
					close(infd);	
				}
				runs[j]->idx = 0;
				runs[j]->offset = bytes;
			}
			k_merge(runs, input_prefix, num_runs_in_merge, base, i);
		}

		strcpy(filename, output_prefix);
		strcpy(output_prefix, input_prefix);
		strcpy(input_prefix, filename);

		run_length *= K;
		num_runs = num_merges;
	}

	for (i = 0; i < K; i++) {
		free(runs[i]->buf);
		free(runs[i]);
	}
	free(runs);
	free(buffer);
	close(fd);

	long end_usecs = get_time_usecs();
	double secs = (double)(end_usecs - start_usecs) / (double)1000000;
	printf("Sorting took %.02f seconds.\n", secs);
	printf("sorting result saved in %s%d.dat.\n", input_prefix, 0);

	return 0;
}

void k_merge(run_t** runs, char* input_prefix, int num_runs, int base, int n_merge)
{
	int bp, bytes, output_fd;
	int live_runs = num_runs;
	run_t *mr;
	char filename[20];

	bp = 0;
	create_loser_tree(runs, num_runs);

	snprintf(filename, 100, "%s%d.dat", output_prefix, n_merge);
	output_fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC, 
			S_IRWXU|S_IRWXG);
	if (output_fd < 0) {
		printf("create file %s fail\n", filename);
		exit(0);
	}

	while (live_runs > 0) {
		mr = runs[ls[0]];
		buffer[bp++] = mr->buf[mr->idx++];
		// 输出缓冲区已满
		if (bp*4 == BUF_SIZE) {
			bytes = write(output_fd, buffer, BUF_SIZE);
			bp = 0;
		}
		// mr的输入缓冲区用完
		if (mr->idx == mr->length) {
			snprintf(filename, 20, "%s%d.dat", input_prefix, ls[0]+n_merge*K);
			if (base) {
				mr->buf[mr->idx] = MAX_INT;
				live_runs--;
			} else {
				int fd = open(filename, O_RDONLY);
				lseek(fd, mr->offset, SEEK_SET);
				bytes = read(fd, mr->buf, BUF_SIZE);
				close(fd);
				if (bytes == 0) {
					mr->buf[mr->idx] = MAX_INT;
					live_runs--;
				}
				else {
					mr->length = bytes/sizeof(int);
					mr->offset += bytes;
					mr->idx = 0;
				}
			}
		}
		adjust(runs, num_runs, ls[0]);
	}
	bytes = write(output_fd, buffer, bp*4);
	if (bytes != bp*4) {
		printf("!!!!!! Write Error !!!!!!!!!\n");
		exit(0);
	}
	close(output_fd);
}

long get_time_usecs()
{
	struct timeval time;
	struct timezone tz;
	memset(&tz, '\0', sizeof(struct timezone));
	gettimeofday(&time, &tz);
	long usecs = time.tv_sec*1000000 + time.tv_usec;

	return usecs;
}

void swap(int *p, int *q)
{
	int		tmp;

	tmp = *p;
	*p = *q;
	*q = tmp;
}

int partition(int *a, int s, int t)
{
	int		i, j;	/* i用来遍历a[s]...a[t-1], j指向大于x部分的第一个元素 */

	for (i = j = s; i < t; i++) {
		if (a[i] < a[t]) {
			swap(a+i, a+j);
			j++;
		}
	}
	swap(a+j, a+t);

	return j;
}

void quick_sort(int *a, int s, int t)
{
	int 	p;

	if (s < t) {
		p = partition(a, s, t);
		quick_sort(a, s, p-1);
		quick_sort(a, p+1, t);
	}
}

void adjust(run_t ** runs, int n, int s)
{
	int t, tmp;

	t = (s+n)/2;
	while (t > 0) {
		if (s == -1) {
			break;
		}
		if (ls[t] == -1 || runs[s]->buf[runs[s]->idx] > runs[ls[t]]->buf[runs[ls[t]]->idx]) {
			tmp = s;
			s = ls[t];
			ls[t] = tmp;
		}
		t >>= 1;
	}
	ls[0] = s;
}

void create_loser_tree(run_t **runs, int n)
{
	int		i;

	for (i = 0; i < n; i++) {
		ls[i] = -1;
	}
	for (i = n-1; i >= 0; i--) {
		adjust(runs, n, i);
	}
}

void usage()
{
	printf("sort <filename> <K-ways>\n");
	printf("\tfilename: filename of file to be sorted\n");
	printf("\tK-ways: how many ways to merge\n");
	exit(1);
}

