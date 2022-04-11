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
