#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

void push(struct Node** head, int data);
void printList(struct Node *head);
void insertNth(Node** list,int skipcount, int newElem);
Node* create_node(int data);
void listFree(Node** list);

int main() {
    struct Node *head = NULL;
    unsigned int n;
    printf("Enter numbers count: ");
    scanf("%d", &n);
    int currdata;
    while (n--)
    {
        scanf("%d", &currdata);
        push(&head, currdata);
    }
    printList(head);
    insertNth(&head, 2, 10);
    printList(head);
    
    listFree(&head);
    return 0;
}   
void listFree(Node** list){
    Node* current = *list, *prev;
    Node* start = *list;
    while (current != start){
        prev = current;
        current = current->next;
        free(prev);
    }
    *list = NULL;
}

Node* create_node(int newElem){
    Node* node = malloc(sizeof(Node));
    node->data = newElem;
    node->next = NULL;
    return node;
}

void insertNth(Node** list,int skipcount, int newElem){
    Node* node = create_node(newElem);
    if (skipcount == 0 || *list == NULL){
        *list = node;
        return;
    }
    Node* current = *list;
    Node* prev = current;
    while (skipcount--){
        prev = current;
        current = current->next;
    }
    prev->next = node;
    node->next = current;
}

void push(struct Node **head, int data)
{
    struct Node *ptr1 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = *head;
    ptr1->data = data;
    ptr1->next = *head;
 
    if (*head != NULL)
    {
        while (temp->next != *head)
            temp = temp->next;
        temp->next = ptr1;
    }
    else
        ptr1->next = ptr1;
 
    *head = ptr1;
}

void printList(struct Node *head)
{
    struct Node *temp = head;
    if (head != NULL)
    {
        do
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        while (temp != head);
    }
}
