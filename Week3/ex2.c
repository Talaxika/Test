#include <stdio.h>
#include <errno.h>
#include <string.h>

//run command -gcc ex2.c -o ex2; ./ex2 myfile.txt output.hex -TB

int main(int argc, char* argv[]) {
    FILE* fpr = fopen(argv[1], "r");
    FILE* fpwr = fopen(argv[2], "wb");

    if (NULL == fpr || NULL == fpwr)
    {
        perror("Error info");
        return 1;
    }

    char buffer[200];
    char upper[200] = "65535";
    while ((fgets(buffer, 200, fpr)) != NULL)
    {
        int result = strcmp(buffer, upper);
        if (buffer < 0 || result > 0)
        {
            fprintf(stderr, "Wrong input.");
            return 1;
        }
               
        fputs(buffer, fpwr);
    }
    

    if(fclose(fpr) == -1 || fclose(fpwr) == -1){
        fprintf(stderr, "File problem\n");
        return 1;
    }

    return 0;
}
