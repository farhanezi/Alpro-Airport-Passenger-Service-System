#include <iostream>
#include <string>
using namespace std;

//  STRUKTUR DATA
struct Passenger {
    int    id;
    string name;
    string flight;
    string seat;
    Passenger* next;
};

struct PassengerQueue {
    Passenger* front;
    Passenger* rear;
    int        size;
};
//  INISIALISASI

void initQueue(PassengerQueue& q) {
    q.front = nullptr;
    q.rear  = nullptr;
    q.size  = 0;
}

bool isEmpty(const PassengerQueue& q) {
    return q.front == nullptr;
}

//  ENQUEUE

void enqueue(PassengerQueue& q, int id,
             const string& name,
             const string& flight,
             const string& seat)
{
    Passenger* p = new Passenger();
    p->id     = id;
    p->name   = name;
    p->flight = flight;
    p->seat   = seat;
    p->next   = nullptr;

    if (isEmpty(q)) {
        q.front = p;
        q.rear  = p;
    } else {
        q.rear->next = p;
        q.rear       = p;
    }
    q.size++;

    cout << "\n[OK] Penumpang \"" << name
         << "\" berhasil masuk antrian check-in.\n";
}

//  DEQUEUE

void dequeue(PassengerQueue& q) {
    if (isEmpty(q)) {
        cout << "\n[INFO] Antrian kosong. Tidak ada penumpang yang menunggu.\n";
        return;
    }

    Passenger* served = q.front;
    q.front = q.front->next;
    if (q.front == nullptr) q.rear = nullptr;
    q.size--;

    cout << "\n[DILAYANI] Penumpang dipanggil ke konter check-in:\n";
    cout << "  ID      : " << served->id     << "\n";
    cout << "  Nama    : " << served->name   << "\n";
    cout << "  Flight  : " << served->flight << "\n";
    cout << "  Kursi   : " << served->seat   << "\n";
    cout << "  Sisa antrian: " << q.size << " penumpang\n";

    delete served;
}

//  TAMPILKAN SELURUH ANTRIAN

void displayQueue(const PassengerQueue& q) {
    if (isEmpty(q)) {
        cout << "\n[INFO] Antrian kosong.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "   ANTRIAN CHECK-IN PENUMPANG BANDARA\n";
    cout << "========================================\n";
    cout << "No  | ID   | Nama               | Flight | Kursi\n";
    cout << "----+------+--------------------+--------+------\n";

    Passenger* cur = q.front;
    int pos = 1;
    while (cur != nullptr) {
        cout << " " << pos++ << "  | " << cur->id << "  | ";

        // padding nama
        cout << cur->name;
        int pad = 19 - (int)cur->name.length();
        for (int i = 0; i < pad; i++) cout << " ";

        cout << "| " << cur->flight << "   | " << cur->seat << "\n";
        cur = cur->next;
    }
    cout << "========================================\n";
    cout << "Jumlah penumpang menunggu: " << q.size << "\n";
}

//  JUMLAH PENUMPANG MENUNGGU 

void countPassengers(const PassengerQueue& q) {
    cout << "\n[INFO] Jumlah penumpang dalam antrian: " << q.size << "\n";
}

//  HAPUS SELURUH ANTRIAN

void clearQueue(PassengerQueue& q) {
    while (!isEmpty(q)) {
        Passenger* tmp = q.front;
        q.front = q.front->next;
        delete tmp;
    }
    q.rear = nullptr;
    q.size = 0;
}

//  MENU QUEUE
void menuQueue() {
    PassengerQueue q;
    initQueue(q);
    int nextId = 1001;
    int choice;

    do {
        cout << "\n+--------------------------------------+\n";
        cout << "|   MODUL QUEUE - CHECK-IN PENUMPANG  |\n";
        cout << "+--------------------------------------+\n";
        cout << "| 1. Tambah Penumpang ke Antrian       |\n";
        cout << "| 2. Panggil Penumpang Berikutnya      |\n";
        cout << "| 3. Tampilkan Seluruh Antrian         |\n";
        cout << "| 4. Jumlah Penumpang Menunggu         |\n";
        cout << "| 0. Keluar                            |\n";
        cout << "+--------------------------------------+\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name, flight, seat;
            cout << "Nama penumpang   : "; getline(cin, name);
            cout << "Nomor penerbangan: "; getline(cin, flight);
            cout << "Nomor kursi      : "; getline(cin, seat);
            enqueue(q, nextId++, name, flight, seat);

        } else if (choice == 2) {
            dequeue(q);

        } else if (choice == 3) {
            displayQueue(q);

        } else if (choice == 4) {
            countPassengers(q);

        } else if (choice != 0) {
            cout << "\n[ERROR] Pilihan tidak valid.\n";
        }

    } while (choice != 0);

    clearQueue(q);
}

//  MAIN

int main() {
    cout << "==========================================\n";
    cout << "   AIRPORT PASSENGER SERVICE SYSTEM\n";
    cout << "   Topik 7 | Modul Queue - Check-in\n";
    cout << "==========================================\n";

    menuQueue();

    cout << "\nTerima kasih.\n";
    return 0;
}
