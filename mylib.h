#define Max 1000
#define nowTime clock()/CLOCKS_PER_SEC
#define lChild(i) 2*i
#define rChild(i) 2*i+1
#define parent(i) i/2

void print_array(int array[], int length);
void rand_array(int array[],int length);
void input_array(int array[], int *length);
void insert_sort(int array[], int length);
void bubble_sort(int array[], int length);
void exchange(int *a, int *b);
int partition(int array[], int start, int end);
void quick_sort(int array[], int start, int end);
void merge(int array[], int start, int middle, int end);
void merge_sort(int array[], int start, int end);
void shell_sort(int array[], int length);
void max_heapify(int array[], int length, int root);
void heap_sort(int array[], int length);
void count_sort(int array[], int length, int num);
void radix_sort(int array[], int length);
