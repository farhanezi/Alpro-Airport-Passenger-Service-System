#ifndef STACK_MODULE_H
#define STACK_MODULE_H

#include "penumpang.h"
#include <iostream>
using namespace std;

// ============================================================
// MODUL RIWAYAT BOARDING - STACK (Linked List, tanpa STL)
// Tugas Anggota 2
//
// Big O Summary:
//   push  : O(1) - tambah di atas, selalu konstan
//   pop   : O(1) - hapus dari atas, selalu konstan
//   peek  : O(1) - lihat atas, selalu konstan
//   tampilkanRiwayat : O(n) - harus traversal semua node
// ============================================================

struct StackNode {
    Penumpang data;
    StackNode* next;

    StackNode(Penumpang p) : data(p), next(nullptr) {}
};

class StackRiwayat {
private:
    StackNode* top;
    int ukuran;

public:
    StackRiwayat();
    ~StackRiwayat();

    // Core LIFO operations
    void push(Penumpang p);       // O(1)
    Penumpang pop();              // O(1)
    Penumpang peek() const;       // O(1)
    bool isEmpty() const;
    int getUkuran() const;

    // Feature functions (dipanggil dari menu)
    void simpanBoardingSelesai(Penumpang p);
    void tampilkanBoardingTerakhir() const;
    void tampilkanRiwayatBoarding() const;
    void undoPelayananTerakhir();
};

// Entry point untuk Anggota 3 (dipanggil dari main menu)
void menuRiwayatBoarding(StackRiwayat& stack);

#endif // STACK_MODULE_H