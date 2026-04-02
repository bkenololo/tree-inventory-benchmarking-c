#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { int id; char species[50]; float gps_lat; float gps_lon; int age; float diameter; } Tree;
typedef struct Node { Tree data; struct Node* next; } Node;

void addTree(Node** head, Tree newTree) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newTree; newNode->next = NULL;
    if (*head == NULL) { *head = newNode; return; }
    Node* temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

void viewTrees(Node* head) {
    Node* temp = head;
    volatile int dummy = 0;
    while (temp != NULL) { dummy += temp->data.id; temp = temp->next; }
}

void deleteTree(Node** head, int targetID) {
    if (*head == NULL) return;
    Node* temp = *head; Node* prev = NULL;
    if (temp != NULL && temp->data.id == targetID) { *head = temp->next; free(temp); return; }
    while (temp != NULL && temp->data.id != targetID) { prev = temp; temp = temp->next; }
    if (temp == NULL) return;
    prev->next = temp->next; free(temp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    int N = atoi(argv[1]);
    Tree dummyTree = {0, "Pinus", -6.9, 107.6, 10, 45.0};
    Node* head = NULL;

    clock_t start = clock();
    for (int i = 0; i < N; i++) { dummyTree.id = i; addTree(&head, dummyTree); }
    double time_add = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    start = clock();
    viewTrees(head);
    double time_view = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    start = clock();
    deleteTree(&head, N/2);
    double time_delete = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    printf("%f,%f,%f\n", time_add, time_view, time_delete);
    return 0;
}
