#include "stack_module.h"

// ============================================================
// KONSTRUKTOR & DESTRUKTOR
// ============================================================

StackRiwayat::StackRiwayat() : top(nullptr), ukuran(0) {}

StackRiwayat::~StackRiwayat() {
    while (!isEmpty()) pop();
}

// ============================================================
// CORE STACK OPERATIONS
// ============================================================

// PUSH - Tambah penumpang ke atas stack
// Big O: O(1) -> Best / Average / Worst semua konstan
// Alasan: hanya update pointer, tidak tergantung ukuran stack
void StackRiwayat::push(Penumpang p) {
    StackNode* newNode = new StackNode(p);
    newNode->next = top;
    top = newNode;
    ukuran++;
}

// POP - Ambil & hapus penumpang dari atas stack
// Big O: O(1) -> Best / Average / Worst semua konstan
// Alasan: hanya update pointer top, tidak iterasi
Penumpang StackRiwayat::pop() {
    if (isEmpty()) {
        cout << "  [STACK] Stack kosong, tidak ada yang bisa di-pop.\n";
        Penumpang kosong = {0, "", "", "", "", "", "", 0};
        return kosong;
    }
    StackNode* temp = top;
    Penumpang data = temp->data;
    top = top->next;
    delete temp;
    ukuran--;
    return data;
}

// PEEK - Lihat penumpang teratas tanpa menghapus
// Big O: O(1)
Penumpang StackRiwayat::peek() const {
    if (isEmpty()) {
        Penumpang kosong = {0, "", "", "", "", "", "", 0};
        return kosong;
    }
    return top->data;
}

bool StackRiwayat::isEmpty() const {
    return top == nullptr;
}

int StackRiwayat::getUkuran() const {
    return ukuran;
}

// ============================================================
// FEATURE FUNCTIONS
// ============================================================

// Simpan penumpang yang baru selesai boarding
void StackRiwayat::simpanBoardingSelesai(Penumpang p) {
    push(p);
    cout << "  [OK] Penumpang " << p.nama
         << " (Tiket: " << p.nomorTiket << ") "
         << "berhasil disimpan ke riwayat boarding.\n";
}

// Tampilkan info penumpang terakhir yang boarding
void StackRiwayat::tampilkanBoardingTerakhir() const {
    if (isEmpty()) {
        cout << "  Belum ada riwayat boarding.\n";
        return;
    }
    Penumpang p = top->data;
    cout << "\n  +----- PENUMPANG TERAKHIR BOARDING -----+\n";
    cout << "  | Nama          : " << p.nama          << "\n";
    cout << "  | No. Tiket     : " << p.nomorTiket    << "\n";
    cout << "  | Maskapai      : " << p.maskapai      << "\n";
    cout << "  | Tujuan        : " << p.tujuan        << "\n";
    cout << "  | Gate          : " << p.gateBoarding  << "\n";
    cout << "  | Waktu Boarding: " << p.waktuBoarding << "\n";
    cout << "  | Durasi Layanan: " << p.durasiLayanan << " menit\n";
    cout << "  +----------------------------------------+\n";
}

// Tampilkan seluruh riwayat boarding (LIFO order)
// Big O: O(n) -> traversal semua node
void StackRiwayat::tampilkanRiwayatBoarding() const {
    if (isEmpty()) {
        cout << "  Riwayat boarding masih kosong.\n";
        return;
    }
    cout << "\n  ========= RIWAYAT BOARDING PENUMPANG =========\n";
    cout << "  (Urutan: paling atas = paling baru)\n";
    cout << "  No | Nama                | No. Tiket | Maskapai       | Waktu\n";
    cout << "  ---|---------------------|-----------|----------------|------\n";

    StackNode* current = top;
    int no = 1;
    while (current != nullptr) {
        Penumpang& p = current->data;
        // Format output sederhana tanpa iomanip
        cout << "  " << no << "  | " << p.nama << "        | "
             << p.nomorTiket << "    | "
             << p.maskapai << "   | "
             << p.waktuBoarding << "\n";
        current = current->next;
        no++;
    }
    cout << "  ==============================================\n";
    cout << "  Total riwayat: " << ukuran << " penumpang\n";
}

// Undo pelayanan terakhir (pop dari stack)
void StackRiwayat::undoPelayananTerakhir() {
    if (isEmpty()) {
        cout << "  [UNDO] Tidak ada pelayanan yang bisa di-undo.\n";
        return;
    }
    Penumpang p = pop();
    cout << "  [UNDO] Pelayanan penumpang \"" << p.nama
         << "\" (Tiket: " << p.nomorTiket << ") berhasil dibatalkan.\n";
    cout << "  >> Penumpang perlu diproses ulang.\n";
}

// ============================================================
// MENU FUNCTION - Dipanggil oleh Anggota 3 dari main()
// ============================================================
void menuRiwayatBoarding(StackRiwayat& stack) {
    int pilihan;
    do {
        cout << "\n  ====== MODUL RIWAYAT BOARDING (STACK) ======\n";
        cout << "  1. Input penumpang selesai boarding\n";
        cout << "  2. Tampilkan boarding terakhir (Peek)\n";
        cout << "  3. Pop & tampilkan riwayat boarding terakhir\n";
        cout << "  4. Undo pelayanan terakhir\n";
        cout << "  5. Tampilkan seluruh riwayat boarding\n";
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
            stack.simpanBoardingSelesai(p);

        } else if (pilihan == 2) {
            stack.tampilkanBoardingTerakhir();

        } else if (pilihan == 3) {
            Penumpang p = stack.pop();
            if (p.id != 0) {
                cout << "  [POP] Diambil dari stack: " << p.nama
                     << " (Tiket: " << p.nomorTiket << ")\n";
            }

        } else if (pilihan == 4) {
            stack.undoPelayananTerakhir();

        } else if (pilihan == 5) {
            stack.tampilkanRiwayatBoarding();

        } else if (pilihan != 0) {
            cout << "  Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);
}