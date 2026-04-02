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

// --- VERSI 2: DYNAMIC ARRAY ---

// Struktur pembungkus untuk Array Dinamis
typedef struct {
    Tree* data;      // Pointer ke block memori array
    int count;       // Jumlah pohon saat ini
    int capacity;    // Kapasitas maksimal array saat ini
} TreeArray;

// Inisialisasi awal Array
void initArray(TreeArray* arr, int initialCapacity) {
    arr->capacity = initialCapacity;
    arr->count = 0;
    arr->data = (Tree*)malloc(arr->capacity * sizeof(Tree));
}

// Fungsi 1: ADD (Append)
// Time Complexity: O(1) Amortized, tapi bisa O(N) kalau pas array kepenuhan dan butuh realloc
void addTree_Arr(TreeArray* arr, Tree newTree) {
    // Cek apakah array penuh
    if (arr->count == arr->capacity) {
        arr->capacity *= 2; // Gandakan kapasitas
        // realloc akan mencari memori baru yang cukup untuk kapasitas baru
        arr->data = (Tree*)realloc(arr->data, arr->capacity * sizeof(Tree));
        printf("[Sistem] Array penuh, kapasitas digandakan menjadi %d\n", arr->capacity);
    }
    
    // Masukkan data di indeks terakhir
    arr->data[arr->count] = newTree;
    arr->count++;
}

// Fungsi 2: VIEW (Traverse & Print)
// Time Complexity: O(N)
void viewTrees_Arr(TreeArray* arr) {
    if (arr->count == 0) {
        printf("Array kosong!\n");
        return;
    }
    printf("\n--- Data Pohon (Dynamic Array) ---\n");
    for (int i = 0; i < arr->count; i++) {
        printf("ID: %d | Spesies: %s | Umur: %d thn | Dia: %.2f cm\n", 
               arr->data[i].id, arr->data[i].species, arr->data[i].age, arr->data[i].diameter);
    }
}

// Fungsi 3: DELETE (By ID)
// Time Complexity: O(N) karena setelah dihapus, SEMUA elemen di kanannya harus digeser ke kiri
void deleteTree_Arr(TreeArray* arr, int targetID) {
    int foundIndex = -1;
    
    // Cari index pohonnya
    for (int i = 0; i < arr->count; i++) {
        if (arr->data[i].id == targetID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Pohon ID %d tidak ditemukan.\n", targetID);
        return;
    }

    // Geser semua elemen di sebelah kanan index yang dihapus ke arah kiri (maju 1 langkah)
    for (int i = foundIndex; i < arr->count - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->count--; // Kurangi total pohon
    printf("Pohon ID %d berhasil dihapus.\n", targetID);
}