#include <stdio.h>
#include <string.h>



int main() {

    char number[500];
    scanf("%s", number);
    
    for (int i = 0; i < strlen(number); i+=2)
    {
        if (number[i] >= '0' && number[i]<= '9')
        {
            number[i] += ('A' - '0');
        }
    }for (int i = 1; i < strlen(number); i+=2)
    {
        if (number[i] == '0')
        {
            number[i] = '!';
        }
        else if (number[i] == '1')
        {
            number[i] = '#';
        }
        else if (number[i] == '2')
        {
            number[i] = '/';
        }
        else if (number[i] == '3')
        {
            number[i] = '~';
        }
        else if (number[i] == '4')
        {
            number[i] = '=';
        }
        else if (number[i] == '5')
        {
            number[i] = '\'';
        }
        else if (number[i] == '6')
        {
            number[i] = '\\';
        }
        else if (number[i] == '7')
        {
            number[i] = '>';
        }
        else if (number[i] == '8')
        {
            number[i] = '.';
        }

        else if (number[i] == '9')
        {
            number[i] = ',';
        }
        
    }
    
    printf("%s", number);
    return 0;
}
