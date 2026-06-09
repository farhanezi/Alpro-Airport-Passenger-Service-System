#include "queue_module.h"

// ============================================================
// KONSTRUKTOR & DESTRUKTOR
// ============================================================

QueueCheckIn::QueueCheckIn() : front(nullptr), rear(nullptr), ukuran(0) {}

QueueCheckIn::~QueueCheckIn() {
    while (!isEmpty()) dequeue();
}

// ============================================================
// CORE QUEUE OPERATIONS
// ============================================================

// ENQUEUE - Tambah penumpang ke belakang antrian
// Big O: O(1) -> pointer rear langsung, tidak iterasi
void QueueCheckIn::enqueue(Penumpang p) {
    QueueNode* newNode = new QueueNode(p);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    ukuran++;
}

// DEQUEUE - Ambil & hapus penumpang dari depan antrian
// Big O: O(1) -> pointer front langsung
Penumpang QueueCheckIn::dequeue() {
    if (isEmpty()) {
        cout << "  [QUEUE] Antrian kosong.\n";
        Penumpang kosong = {0, "", "", "", "", "", "", 0};
        return kosong;
    }
    QueueNode* temp = front;
    Penumpang data = temp->data;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete temp;
    ukuran--;
    return data;
}

Penumpang QueueCheckIn::peek() const {
    if (isEmpty()) {
        Penumpang kosong = {0, "", "", "", "", "", "", 0};
        return kosong;
    }
    return front->data;
}

bool QueueCheckIn::isEmpty() const {
    return front == nullptr;
}

int QueueCheckIn::getUkuran() const {
    return ukuran;
}

// ============================================================
// FEATURE FUNCTIONS
// ============================================================

void QueueCheckIn::tambahPenumpang(Penumpang p) {
    enqueue(p);
    cout << "  [OK] Penumpang " << p.nama
         << " (Tiket: " << p.nomorTiket << ") berhasil ditambahkan ke antrian.\n";
}

void QueueCheckIn::panggilPenumpangBerikutnya() {
    if (isEmpty()) {
        cout << "  Antrian kosong, tidak ada penumpang yang perlu dipanggil.\n";
        return;
    }
    Penumpang p = dequeue();
    cout << "\n  [DIPANGGIL] " << p.nama << " silahkan menuju counter check-in.\n";
    cout << "  Tiket: " << p.nomorTiket << " | Maskapai: " << p.maskapai
         << " | Gate: " << p.gateBoarding << "\n";
}

void QueueCheckIn::tampilkanAntrian() const {
    if (isEmpty()) {
        cout << "  Antrian check-in kosong.\n";
        return;
    }
    cout << "\n  ========= ANTRIAN CHECK-IN =========\n";
    cout << "  No | Nama                | No. Tiket | Maskapai         | Gate\n";
    cout << "  ---|---------------------|-----------|------------------|-----\n";
    QueueNode* current = front;
    int no = 1;
    while (current != nullptr) {
        Penumpang& p = current->data;
        cout << "  " << no << "  | " << p.nama << "        | "
             << p.nomorTiket << "    | "
             << p.maskapai   << "  | "
             << p.gateBoarding << "\n";
        current = current->next;
        no++;
    }
    cout << "  ====================================\n";
    cout << "  Total antrian: " << ukuran << " penumpang\n";
}

void QueueCheckIn::tampilkanJumlahMenunggu() const {
    cout << "  Jumlah penumpang dalam antrian: " << ukuran << " orang\n";
}

// ============================================================
// MENU FUNCTION - Dipanggil oleh Anggota 3 dari main()
// ============================================================
void menuAntrian(QueueCheckIn& queue) {
    int pilihan;
    do {
        cout << "\n  ====== MODUL ANTRIAN CHECK-IN (QUEUE) ======\n";
        cout << "  1. Tambah penumpang ke antrian\n";
        cout << "  2. Panggil penumpang berikutnya\n";
        cout << "  3. Tampilkan seluruh antrian\n";
        cout << "  4. Tampilkan jumlah penumpang menunggu\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "  Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            Penumpang p;
            cout << "  ID           : "; cin >> p.id;     cin.ignore();
            cout << "  Nama         : "; getline(cin, p.nama);
            cout << "  No. Tiket    : "; getline(cin, p.nomorTiket);
            cout << "  Maskapai     : "; getline(cin, p.maskapai);
            cout << "  Tujuan       : "; getline(cin, p.tujuan);
            cout << "  Gate         : "; getline(cin, p.gateBoarding);
            cout << "  Waktu (HH:MM): "; getline(cin, p.waktuBoarding);
            cout << "  Durasi (mnt) : "; cin >> p.durasiLayanan; cin.ignore();
            queue.tambahPenumpang(p);

        } else if (pilihan == 2) {
            queue.panggilPenumpangBerikutnya();

        } else if (pilihan == 3) {
            queue.tampilkanAntrian();

        } else if (pilihan == 4) {
            queue.tampilkanJumlahMenunggu();

        } else if (pilihan != 0) {
            cout << "  Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);
}
