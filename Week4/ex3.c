#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void *func(void *arg)
{
    int i = 0, n = 0, min, index;
    char* filename = (char*)arg;
    FILE *fp = fopen(filename, "r");
    int size = ftell(fp);
    n = size/sizeof(int);
    if (NULL == fp)
    {
        perror("file open problem");
        exit(-1);
    }
    int *arr = (int*) malloc(size);

    while ((!feof(fp)))
    {
        fread((arr+i), sizeof(int), 1, fp);
    }

    fclose(fp);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (*(arr+j) > *(arr+min))
            {
                swap(&arr[min], &arr[i]);
            }
            
        }
    }
    FILE *fpw = fopen(filename, "wb");
    if (NULL == fpw)
    {
        perror("error fopen write");
        exit(-1);
    }
    
    for (int i = 0; i < n; i++)
    {
        fwrite((arr+i), sizeof(int), 1, fpw);
    }
    fclose(fpw);
    free(arr);
}

int main()
{
    FILE* fp = fopen("file.txt", "w");
    if (NULL == fp)
    {
        perror("file open");
        exit(-1);
    }
    

    int N, M;
    char buff[10];
    int num;
    scanf("%d %d", &N, &M);
    pthread_t threads[N];
    int *arr = (int *)malloc(sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%s, %d", buff, &num);
        for (int j = 0; j < M; j++)
        {
            int currnum;
            scanf("%d", currnum);
            arr[j] = currnum;
            fwrite((arr+j), sizeof(int), 1, fp);
            for (int i = 0; i < N; i++)
            {
                if (pthread_create(&threads[i], NULL, func, fp) != 0)
                {
                    perror("create thread problem");
                    return EXIT_FAILURE;
                }
            }
            for (int i = 0; i < N; i++)
            {
                if (pthread_join(threads[i], NULL) != 0)
                {
                    perror("thread join problem");
                    return EXIT_FAILURE;
                }
            }
        }
    }
    fclose(fp);
    return 0;
}
