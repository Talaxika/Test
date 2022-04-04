#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define COUNT 10

typedef struct 
{
    double a;
    double b;
}point_t;


typedef struct 
{
    point_t A;
    point_t B;

}rectangle_t;

typedef struct Node
{
    rectangle_t rectangle;
    struct Node* next;
}Node;

double cmp(double a, double b);
double getArea(double a, double b);
double randfromdouble(double min, double max);
void push(Node** list, rectangle_t rectangle);
double areaRects(Node* list);
void print_list(Node* list);
void listFree(Node** list);
void filterRects(Node** list, double min, double max);
void deleteNth(Node** list, size_t n);
Node* sortedMerge(Node* listA, Node* listB, double(*cmp)(double, double));
void frontBackSplit(Node* list, Node** front, Node** back);
void mergeSort(Node** list, double(*cmp)(double, double));

int main() {
    struct  Node* head = NULL;
    srand(time(NULL));
    rectangle_t rectangles[COUNT];
    
    for (int i = 0; i < COUNT; i++)
    {
        
        rectangles[i].A.a = randfromdouble(-10.0, 10.0);
        rectangles[i].A.b = randfromdouble(-10.0, 10.0);
        rectangles[i].B.a = randfromdouble(-10.0, 10.0);
        rectangles[i].B.b = randfromdouble(-10.0, 10.0);
    }
    for (int i = 0; i < COUNT; i++)
    {
        push(&head, rectangles[i]);
    }

    areaRects(head);
    print_list(head);
    filterRects(&head, -20, 20);
    print_list(head);
    mergeSort(&head, cmp);
    print_list(head);



    listFree(&head);
    return 0;
}

void print_list(Node* list){
    Node* current = list;
    int cnt = 1;
    while (current){
        printf("%d. pointA - (%.2lf, %.2lf) pointB - (%.2lf, %.2lf)\n",cnt, current->rectangle.A.a, current->rectangle.A.b, current->rectangle.B.a, current->rectangle.B.b);
        current = current->next;
        cnt++;
    }
    putchar('\n');
}

double randfromdouble(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void push(Node** list, rectangle_t rectangle){
    Node* n = malloc(sizeof(Node));
    n->rectangle = rectangle;
    n->next = *list;
    *list = n;
}

double areaRects(Node* list){
    Node* current = list;
    double area;
    double sideA, sideB;
    int i = 1;
    while (current)
    {
        sideA = fabs(current->rectangle.A.a - (current->rectangle.B.a));
        sideB = fabs(current->rectangle.A.b - (current->rectangle.B.b));
        area = sideA*sideB;
        printf("%d. %.2lf\n",i ,area);
        current = current->next;
        i++;
    }
    putchar('\n');
}

void filterRects(Node** list, double min, double max){
    Node* current = *list;
    Node* prev = current;

    double area;
    double sideA, sideB;
    int n = 0;
    while (current)
    {
        sideA = fabs(current->rectangle.A.a - (current->rectangle.B.a));
        sideB = fabs(current->rectangle.A.b - (current->rectangle.B.b));
        area = sideA*sideB;
        if(area < min || area > max){
            deleteNth(list, n);
        }
        current = current->next;
        n++;
    }
}

void deleteNth(Node** list, size_t n){
    if (*list == NULL){
        return;
    }
    if (n == 0){
        Node* temp = *list;
        *list = (*list)->next;
        free(temp);
        return;
    }
    Node* current = *list;
    Node* prev = current;
    while (current && n--) {
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    free(current);
}

void listFree(Node** list){
    Node *current = *list, *prev;
    while (current){
        prev = current;
        current = current->next;
        free(prev);
    }
    *list = NULL;
}
double cmp(double a, double b){
    return b - a;
}

Node* sortedMerge(Node* listA, Node* listB, double(*cmp)(double, double)){
    Node* sorted = NULL;
    if (listA == NULL){
        return listB;
    }
    if (listB == NULL){
        return listA;
    }
    if (cmp(fabs(listA->rectangle.A.a - (listA->rectangle.B.a))*fabs(listA->rectangle.A.b - (listA->rectangle.B.b)), fabs(listB->rectangle.A.a - (listB->rectangle.B.a))*fabs(listB->rectangle.A.b - (listB->rectangle.B.b))) > 0){
        sorted = listA;
        sorted->next = sortedMerge(listA->next, listB, cmp);
    } else {
        sorted = listB;
        sorted->next = sortedMerge(listA, listB->next, cmp);
    }
    return sorted;
}


void frontBackSplit(Node* list, Node** front, Node** back){
    Node* slow = list;
    Node* fast = list->next;
    while (fast != NULL){
        fast = fast->next;
        if (fast  != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = list;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSort(Node** list, double(*cmp)(double, double)){
    if (*list == NULL || (*list)->next == NULL){
        return;
    }
    Node *front = NULL, *back = NULL;
    frontBackSplit(*list, &front, &back);
    mergeSort(&front, cmp);
    mergeSort(&back, cmp);
    *list = sortedMerge(front, back, cmp);
}
