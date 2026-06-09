#ifndef QUEUE_MODULE_H
#define QUEUE_MODULE_H

#include "penumpang.h"
#include <iostream>
using namespace std;

struct QueueNode {
    Penumpang  data;
    QueueNode* next;
    QueueNode(Penumpang p) : data(p), next(nullptr) {}
};

class QueueCheckIn {
private:
    QueueNode* front;
    QueueNode* rear;
    int        ukuran;

public:
    QueueCheckIn();
    ~QueueCheckIn();

    // Operasi dasar
    void      enqueue(Penumpang p);     
    Penumpang dequeue();                 
    Penumpang peek() const;              
    bool      isEmpty() const;
    int       getUkuran() const;

    // Operasi berbasis menu
    void tambahPenumpang(Penumpang p);
    void panggilPenumpangBerikutnya();
    void tampilkanAntrian() const;
    void tampilkanJumlahMenunggu() const;
};

void menuAntrian(QueueCheckIn& queue);

#endif // QUEUE_MODULE_H
