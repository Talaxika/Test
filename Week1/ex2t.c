#include <stdio.h>
#include <stdarg.h>

unsigned bitsNCount(unsigned count, unsigned bitscnt, ...);

int main(void){

    printf("%d", bitsNCount(2, 2, 4, 3));


    return 0;
}

int countSetBits(int n)
{
    if (n == 0)
        return 0;
 
    else
 
        return (n & 1) + countSetBits(n >> 1);
}

unsigned bitsNCount(unsigned count, unsigned bitscnt, ...){
    int countOfMasks = 0;
    va_list args;
    va_start (args, bitscnt);
    for (int i = 0; i < count; i++)
    {
        unsigned int counter;
        counter = countSetBits(va_arg(args, int));
        
        
        if (counter == bitscnt)
        {
            countOfMasks++;
        }
        printf("counter = %d\n", counter);
        
        
    }
    va_end(args);
    return countOfMasks;
    
}