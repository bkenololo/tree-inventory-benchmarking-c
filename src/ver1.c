#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data utama untuk Pohon
typedef struct {
    int id;
    char species[50];
    float gps_lat;
    float gps_lon;
    int age;
    float diameter;
} Tree;

// --- VERSI 1: LINKED LIST ---

// Definisi Node
typedef struct Node {
    Tree data;
    struct Node* next;
} Node;

// Fungsi 1: ADD (Append ke akhir list)
// Time Complexity: O(N) karena harus jalan ke ujung list
void addTree_LL(Node** head, Tree newTree) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Alokasi memori dinamis 1 node
    newNode->data = newTree;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode; // Kalau list masih kosong
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next; // Traverse ke node paling ujung
    }
    temp->next = newNode;
}

// Fungsi 2: VIEW (Traverse & Print)
// Time Complexity: O(N)
void viewTrees_LL(Node* head) {
    if (head == NULL) {
        printf("Linked List kosong!\n");
        return;
    }
    Node* temp = head;
    printf("\n--- Data Pohon (Linked List) ---\n");
    while (temp != NULL) {
        printf("ID: %d | Spesies: %s | Umur: %d thn | Dia: %.2f cm\n", 
               temp->data.id, temp->data.species, temp->data.age, temp->data.diameter);
        temp = temp->next;
    }
}

// Fungsi 3: DELETE (By ID)
// Time Complexity: O(N) untuk nyari, O(1) untuk mutus pointer
void deleteTree_LL(Node** head, int targetID) {
    if (*head == NULL) return;

    Node* temp = *head;
    Node* prev = NULL;

    // Kalau yang mau dihapus adalah elemen pertama (Head)
    if (temp != NULL && temp->data.id == targetID) {
        *head = temp->next; // Pindah head ke elemen kedua
        free(temp);         // Bebaskan memori
        printf("Pohon ID %d berhasil dihapus.\n", targetID);
        return;
    }

    // Traverse untuk nyari ID-nya
    while (temp != NULL && temp->data.id != targetID) {
        prev = temp;
        temp = temp->next;
    }

    // Kalau ID nggak ketemu
    if (temp == NULL) {
        printf("Pohon ID %d tidak ditemukan.\n", targetID);
        return;
    }

    // Putus pointer dan sambung ke elemen berikutnya
    prev->next = temp->next;
    free(temp); // Dealokasi memori
    printf("Pohon ID %d berhasil dihapus.\n", targetID);
}