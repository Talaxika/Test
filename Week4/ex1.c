#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#define ITEMS_COUNT 10

typedef struct 
{
    uint16_t num;
    char desc[250];
    double weight;
    double price;
}Item;

typedef struct Node
{
    Item items;
    struct Node* next;
}Node;

int randfromint(int, int);
double randfromdouble(double, double);
void push(Node** list, Item items);
char *rand_string(char *str, size_t size);
void print_list(Node* list);
double findWeight(Node* list);
Node* minPriceItem(Node* list);


int main() {
    struct Node* head = NULL;
    srand(time(NULL));
    Item items[ITEMS_COUNT];
    int n = ITEMS_COUNT;
    for (int i = 0; i < ITEMS_COUNT; i++)
    {
        items[i].price = randfromdouble(0.10, 100.00);
        items[i].weight = randfromdouble(1.00, 1500.00);
        items[i].num = randfromint(0, 10000);
        for (int j = i+1; j < ITEMS_COUNT; j++)
        {
            while (items[i].num == items[j].num)
            {
                items[i].num = randfromint(0, 10000);
            }
        }
        rand_string(items[i].desc, randfromint(2, 10));
    }

    for (int i = 0; i < ITEMS_COUNT; i++)
    {
        push(&head, items[i]);
    }

    printf("AVG weight = %.2lf\n",findWeight(head));
    Node* thisnode = malloc(sizeof(Node));
    thisnode = minPriceItem(head);
    printf("Cheapest item is item with num %d\n", thisnode->items.num);
    
    
    print_list(head);




    return 0;
}

Node* minPriceItem(Node* list){
    double min = INT_MAX;
    Node* current = list;
    Node* currentmin = list;
    while (current)
    {
        if(min > current->items.price){
            min = current->items.price;
            currentmin = current;
        }
        current = current->next;
    }
    
    return currentmin;

}
double findWeight(Node* list){
    Node* current = list;
    int cnt = 0;
    int sum = 0;
    while (current)
    {
        sum += current->items.weight;
        cnt++;
        current = current->next;
    }
    return sum/cnt;
    
}

void print_list(Node* list){
    Node* current = list;
    int cnt = 1;
    while (current){
        printf("%d. Num-%d Desc-%s Weight-%.2lf Price-%.2lf\n",cnt, current->items.num, current->items.desc, current->items.weight, current->items.price);
        current = current->next;
        cnt++;
    }
    putchar('\n');
}

void push(Node** list, Item item){
    Node* n = malloc(sizeof(Node));
    n->items = item;
    n->next = *list;
    *list = n;
}

char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    const char charsetBig[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int k = randfromint(5, 10);
    if (size) {
        --size;
        for (int j = 0; j < k; j++)
        {
            int key = rand() % (int) (sizeof charset - 1);
            str[0] = charsetBig[key];
            for (size_t n = 1; n < size; n++) 
            {
                int key = rand() % (int) (sizeof charset - 1);
                str[n] = charset[key];
            }
        }
        str[size] = '\0';
    }
    return str;
}

int randfromint(int min, int max) 
{
    int range = (max - min); 
    int div = RAND_MAX / range;
    return min + (rand() / div);
}

double randfromdouble(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
