#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#define COUNT 10

typedef struct
{
    char model[20];
    uint8_t maxspeed;
    double price;
}Car;

int compareModelA(const void* t1, const void* t2);
int compareModelB(const void* t1, const void* t2);
int compareSpeedA (const void* c1, const void* c2);
int compareSpeedB (const void* c1, const void* c2);
int compareCostA (const void* c1, const void* c2);
int compareCostB (const void* c1, const void* c2);

int (*getComparator(int n))(const void*, const void*);

int main() {
    srand(time(NULL));
    Car cars[COUNT];

    const char Models[][100] = {"Aa", "Bb", "Cc", "Dd", "Ee", "Ff", "Gg", "Hh", "Ii", "Jj"};
    const int maxSpeeds[10] = {100, 120, 140, 160, 200, 220, 230, 260, 290, 300};
    const double Prices[10] = {1020.00, 6500.50, 100000.00, 88888.88, 50000.00, 32555.55, 175000.00, 650000.00, 950000.00, 320500.00};

    for (int i = 0; i < COUNT; i++)
    {
        strcpy(cars[i].model, Models[rand()%10]);
        cars[i].maxspeed = maxSpeeds[rand()%10];
        cars[i].price = Prices[rand()%10];
    }
    int funcnumber;
    printf("Please enter the way you want to sort them: ");
    while (scanf("%d", &funcnumber))
    {
        qsort(cars, COUNT, sizeof(Car), getComparator(funcnumber));
        for (int i = 0; i < COUNT; i++)
        {
            printf("%d. %s - %d - %.2lf\n", i, cars[i].model, cars[i].maxspeed, cars[i].price);
        }
    }
    return 0;
}

int compareModelA(const void* t1, const void* t2){
    Car* fst = (Car*)t1;
    Car* snd = (Car*)t2;
    char c1 = fst->model[0];
    char c2 = snd->model[0];
    if (c1==c2)
    {
        return 0;
    }
    else if (c1>c2)
    {
        return 1;
    }
    return -1;
}
int compareModelB(const void* t1, const void* t2){
    Car* fst = (Car*)t1;
    Car* snd = (Car*)t2;
    char c1 = fst->model[0];
    char c2 = snd->model[0];
    if (c1==c2)
    {
        return 0;
    }
    else if (c1<c2)
    {
        return 1;
    }
    return -1;
}

int compareSpeedA (const void* c1, const void* c2){
    Car *fst = (Car*)c1;
    Car *snd = (Car*)c2;
    return fst->maxspeed > snd->maxspeed; 
}
int compareSpeedB (const void* c1, const void* c2){
    Car *fst = (Car*)c1;
    Car *snd = (Car*)c2;
    return fst->maxspeed < snd->maxspeed; 
}

int compareCostA (const void* c1, const void* c2){
    Car *fst = (Car*)c1;
    Car *snd = (Car*)c2;
    if (fabs(fst->price - snd->price) < 0.001)
    {
        return 0;
    }
    else if (fst->price > snd->price)
    {
        return 1;
    }
    return -1;   
}
int compareCostB (const void* c1, const void* c2){
    Car *fst = (Car*)c1;
    Car *snd = (Car*)c2;
    if (fabs(fst->price - snd->price) < 0.001)
    {
        return 0;
    }
    else if (fst->price < snd->price)
    {
        return 1;
    }
    return -1;   
}

int (*getComparator(int n))(const void*, const void*){
    if (n == 1)
    {
        return compareModelA;
    }
    else if (n == 2)
    {
        return compareModelB;
    }
    else if (n == 3)
    {
        return compareSpeedA;
    }
    else if (n == 4)
    {
        return compareSpeedB;
    }
    else if (n == 5)
    {
        return compareCostA;
    }
    else if (n == 6)
    {
        return compareCostB;
    }
    else{
        return NULL;
    }

}
