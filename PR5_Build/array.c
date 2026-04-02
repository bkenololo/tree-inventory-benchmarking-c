#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { int id; char species[50]; float gps_lat; float gps_lon; int age; float diameter; } Tree;
typedef struct { Tree* data; int count; int capacity; } TreeArray;

void initArray(TreeArray* arr, int cap) {
    arr->capacity = cap; arr->count = 0;
    arr->data = (Tree*)malloc(arr->capacity * sizeof(Tree));
}

void addTree(TreeArray* arr, Tree newTree) {
    if (arr->count == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (Tree*)realloc(arr->data, arr->capacity * sizeof(Tree));
    }
    arr->data[arr->count++] = newTree;
}

void viewTrees(TreeArray* arr) {
    volatile int dummy = 0; 
    for (int i = 0; i < arr->count; i++) { dummy += arr->data[i].id; }
}

void deleteTree(TreeArray* arr, int targetID) {
    int foundIndex = -1;
    for (int i = 0; i < arr->count; i++) {
        if (arr->data[i].id == targetID) { foundIndex = i; break; }
    }
    if (foundIndex == -1) return;
    for (int i = foundIndex; i < arr->count - 1; i++) { arr->data[i] = arr->data[i + 1]; }
    arr->count--;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    int N = atoi(argv[1]);
    Tree dummyTree = {0, "Pinus", -6.9, 107.6, 10, 45.0};
    TreeArray arr; initArray(&arr, 2);

    clock_t start = clock();
    for (int i = 0; i < N; i++) { dummyTree.id = i; addTree(&arr, dummyTree); }
    double time_add = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    start = clock();
    viewTrees(&arr);
    double time_view = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    start = clock();
    deleteTree(&arr, N/2);
    double time_delete = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    printf("%f,%f,%f\n", time_add, time_view, time_delete);
    return 0;
}
