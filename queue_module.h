#ifndef QUEUE_MODULE_H
#define QUEUE_MODULE_H

#include "penumpang.h"
#include <iostream>
using namespace std;

// ============================================================
// MODUL ANTRIAN CHECK-IN - QUEUE (Linked List, tanpa STL)
// Tugas Anggota 1
//
// Big O Summary:
//   enqueue : O(1) - tambah di belakang, pointer langsung
//   dequeue : O(1) - hapus dari depan, pointer langsung
//   tampilkanAntrian : O(n) - traversal semua node
// ============================================================

struct QueueNode {
    Penumpang data;
    QueueNode* next;
    QueueNode(Penumpang p) : data(p), next(nullptr) {}
};

class QueueCheckIn {
private:
    QueueNode* front;
    QueueNode* rear;
    int ukuran;

public:
    QueueCheckIn();
    ~QueueCheckIn();

    void enqueue(Penumpang p);        // O(1)
    Penumpang dequeue();              // O(1)
    Penumpang peek() const;           // O(1)
    bool isEmpty() const;
    int getUkuran() const;

    void tambahPenumpang(Penumpang p);
    void panggilPenumpangBerikutnya();
    void tampilkanAntrian() const;
    void tampilkanJumlahMenunggu() const;
};

void menuAntrian(QueueCheckIn& queue);

#endif // QUEUE_MODULE_H
