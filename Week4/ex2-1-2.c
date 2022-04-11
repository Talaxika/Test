//PART 1 --------------------------------

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{

    int sum = 0;
    if (argc == 1)
    {
        printf("Wrong input.");
        exit(-1);
    }

    for (int i = 1; i < argc; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork problems");
            exit(-1);
        }
        else if (pid == 0)
        {
            int k = 0;
            for (int i = 1; i < argc; i++)
            {
                char *filename = argv[i];
                FILE *file = fopen(filename, "r");
                if (!file)
                {
                    perror("File open");
                    exit(-1);
                }
                int size = ftell(file);
                int *arr = (int *)malloc(size);

                while ((!feof(file)))
                {
                    fread((arr + k), sizeof(int), 1, file);
                    
                }
                for (int i = 0; i < k; i++)
                {
                    sum+= arr[i];
                }
                
                fclose(file);
            
                free(arr);
            }
            printf("Sum = %d\n", sum);
            
            exit(0);
        }
        for (int i = 1; i < argc; i++)
        {
            wait(NULL);
        }
    }

    return 0;
}



//PART 2 ---------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *func(void *arg)
{
    
    int sum = 0;
    int j = 0, n = 0;
    char *filename = (char *)arg;
    FILE *fp = fopen(filename, "rb");
    int size = ftell(fp);
    n = size / sizeof(int);
    if (NULL == fp)
    {
        perror("file open problem");
        exit(-1);
    }
    int *arr = (int *)malloc(size);

    while ((!feof(fp)))
    {
        fread((arr + j), sizeof(int), 1, fp);
    }

    for (int i = 0; i < j; i++)
    {
        sum+= arr[j];
    }
    printf("Sum = %d\n", sum);
    fclose(fp);
    
    free(arr);
}

int main(int argc, char *argv[])
{
    pthread_t threads[argc - 1];

    for (int i = 1; i < argc; i++)
    {
        if (pthread_create(&threads[i], NULL, func, argv[i]) != 0)
        {
            perror("create thread problem");
            return EXIT_FAILURE;
        }
    }
    for (int i = 1; i < argc - 1; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("thread join problem");
            return EXIT_FAILURE;
        }
    }

    return 0;
}

