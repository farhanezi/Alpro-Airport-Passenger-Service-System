#include "queue_module.h"
#include <iostream>
#include <string>
using namespace std;

// CONSTRUCTOR & DESTRUCTOR

QueueCheckIn::QueueCheckIn() : front(nullptr), rear(nullptr), ukuran(0) {}

QueueCheckIn::~QueueCheckIn() {
    while (!isEmpty()) {
        Penumpang tmp = dequeue();
        (void)tmp; // destructor membersihkan semua node
    }
}
// isEmpty  –  O(1)

bool QueueCheckIn::isEmpty() const {
    return front == nullptr;
}
// getUkuran

int QueueCheckIn::getUkuran() const {
    return ukuran;
}

// ENQUEUE

void QueueCheckIn::enqueue(Penumpang p) {
    QueueNode* node = new QueueNode(p);

    if (isEmpty()) {
        front = node;
        rear  = node;
    } else {
        rear->next = node;
        rear       = node;
    }
    ukuran++;
}
// DEQUEUE

Penumpang QueueCheckIn::dequeue() {
    if (isEmpty()) {
        // Kembalikan struct kosong jika antrian kosong
        Penumpang kosong = {0, "", "", "", "", "", "", 0};
        return kosong;
    }

    QueueNode* tmp   = front;
    Penumpang  data  = tmp->data;
    front            = front->next;
    if (front == nullptr) rear = nullptr;
    ukuran--;

    delete tmp;
    return data;
}
// PEEK

Penumpang QueueCheckIn::peek() const {
    if (isEmpty()) {
        Penumpang kosong = {0, "", "", "", "", "", "", 0};
        return kosong;
    }
    return front->data;
}
// TAMBAH PENUMPANG

void QueueCheckIn::tambahPenumpang(Penumpang p) {
    enqueue(p);
    cout << "\n  [OK] Penumpang \"" << p.nama
         << "\" (Tiket: " << p.nomorTiket << ")"
         << " berhasil masuk antrian check-in.\n";
    cout << "  Posisi dalam antrian: " << ukuran << "\n";
}
// PANGGIL PENUMPANG BERIKUTNYA

void QueueCheckIn::panggilPenumpangBerikutnya() {
    if (isEmpty()) {
        cout << "\n  [INFO] Antrian kosong. Tidak ada penumpang yang menunggu.\n";
        return;
    }

    Penumpang p = dequeue();
    cout << "\n  +--------------------------------------------------+\n";
    cout << "  |  [DIPANGGIL] Penumpang menuju konter check-in!  |\n";
    cout << "  +--------------------------------------------------+\n";
    cout << "  ID          : " << p.id           << "\n";
    cout << "  Nama        : " << p.nama         << "\n";
    cout << "  No. Tiket   : " << p.nomorTiket   << "\n";
    cout << "  Maskapai    : " << p.maskapai     << "\n";
    cout << "  Tujuan      : " << p.tujuan       << "\n";
    cout << "  Gate        : " << p.gateBoarding << "\n";
    cout << "  Boarding    : " << p.waktuBoarding << "\n";
    cout << "\n  Sisa antrian: " << ukuran << " penumpang\n";
}
// TAMPILKAN ANTRIAN

void QueueCheckIn::tampilkanAntrian() const {
    if (isEmpty()) {
        cout << "\n  [INFO] Antrian kosong.\n";
        return;
    }

    cout << "\n  ============================================================\n";
    cout << "       ANTRIAN CHECK-IN PENUMPANG BANDARA\n";
    cout << "  ============================================================\n";
    cout << "  No | ID | Nama               | No.Tiket  | Tujuan    | Gate\n";
    cout << "  ---+----+--------------------+-----------+-----------+-----\n";

    QueueNode* cur = front;
    int pos = 1;
    while (cur != nullptr) {
        Penumpang& p = cur->data;

        cout << "  " << pos++;

        // padding kolom
        cout << "  | " << p.id;
        cout << "  | " << p.nama;
        int padNama = 19 - (int)p.nama.length();
        for (int i = 0; i < padNama; i++) cout << " ";

        cout << "| " << p.nomorTiket;
        int padTiket = 10 - (int)p.nomorTiket.length();
        for (int i = 0; i < padTiket; i++) cout << " ";

        cout << "| " << p.tujuan;
        int padTujuan = 10 - (int)p.tujuan.length();
        for (int i = 0; i < padTujuan; i++) cout << " ";

        cout << "| " << p.gateBoarding << "\n";

        cur = cur->next;
    }
    cout << "  ============================================================\n";
    cout << "  Jumlah penumpang menunggu: " << ukuran << "\n";
}

// TAMPILKAN JUMLAH MENUNGGU 

void QueueCheckIn::tampilkanJumlahMenunggu() const {
    cout << "\n  [INFO] Jumlah penumpang dalam antrian check-in: "
         << ukuran << "\n";
}

// MENU ANTRIAN  –  dipanggil dari main.cpp

void menuAntrian(QueueCheckIn& queue) {
    int pilihan;
    do {
        cout << "\n  +----------------------------------------------+\n";
        cout << "  |     MODUL QUEUE - ANTRIAN CHECK-IN          |\n";
        cout << "  +----------------------------------------------+\n";
        cout << "  | 1. Tambah Penumpang ke Antrian               |\n";
        cout << "  | 2. Panggil Penumpang Berikutnya              |\n";
        cout << "  | 3. Tampilkan Seluruh Antrian                 |\n";
        cout << "  | 4. Jumlah Penumpang Menunggu                 |\n";
        cout << "  | 0. Kembali ke Menu Utama                     |\n";
        cout << "  +----------------------------------------------+\n";
        cout << "  Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            Penumpang p;
            p.id = queue.getUkuran() + 1;
            cout << "\n  ===== INPUT DATA PENUMPANG =====\n";
            cout << "  Nama            : "; getline(cin, p.nama);
            cout << "  No. Tiket       : "; getline(cin, p.nomorTiket);
            cout << "  Maskapai        : "; getline(cin, p.maskapai);
            cout << "  Tujuan          : "; getline(cin, p.tujuan);
            cout << "  Gate Boarding   : "; getline(cin, p.gateBoarding);
            cout << "  Waktu (HH:MM)   : "; getline(cin, p.waktuBoarding);
            cout << "  Durasi (menit)  : "; cin >> p.durasiLayanan; cin.ignore();
            queue.tambahPenumpang(p);

        } else if (pilihan == 2) {
            queue.panggilPenumpangBerikutnya();

        } else if (pilihan == 3) {
            queue.tampilkanAntrian();

        } else if (pilihan == 4) {
            queue.tampilkanJumlahMenunggu();

        } else if (pilihan != 0) {
            cout << "\n  [ERROR] Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);
}
