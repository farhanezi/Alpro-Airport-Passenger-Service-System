// ============================================================
// MAIN.CPP - AIRPORT PASSENGER SERVICE SYSTEM
// Sistem Layanan Penumpang Bandara
//
// Mata Kuliah : Algoritma dan Pemrograman
// Topik       : Airport Passenger Service System (No. 7)
//
// Anggota 3   : [Nama Anggota 3] - Algoritma Paralel + Integrasi
// Anggota 1   : [Nama Anggota 1] - Queue (Antrian Check-in)
// Anggota 2   : [Nama Anggota 2] - Stack + Divide & Conquer
//
// Struktur Modul:
//   queue_module    -> Antrian check-in penumpang
//   stack_module    -> Riwayat boarding (LIFO)
//   dc_module       -> Pencarian data tiket (Merge Sort + Binary Search)
//   parallel_module -> Laporan harian (3 thread paralel)
// ============================================================

#include <iostream>
#include <string>
#include "penumpang.h"
#include "queue_module.h"
#include "stack_module.h"
#include "dc_module.h"
#include "parallel_module.h"
using namespace std;

// ============================================================
// KONSTANTA & DATA GLOBAL
// ============================================================
const int MAX_DATA = 100;

// Array data master semua penumpang (untuk D&C dan Laporan)
Penumpang dataMaster[MAX_DATA];
int jumlahData = 0;

// ============================================================
// DATA DUMMY untuk demonstrasi
// ============================================================
void inisialisasiDataDummy() {
    dataMaster[0] = {1, "Budi Santoso",    "GA-1023", "Garuda Indonesia", "Jakarta",  "A1", "07:30", 5};
    dataMaster[1] = {2, "Siti Rahayu",     "JT-0045", "Lion Air",         "Surabaya", "B2", "08:15", 4};
    dataMaster[2] = {3, "Ahmad Fauzi",     "GA-0891", "Garuda Indonesia", "Bali",     "A3", "09:00", 6};
    dataMaster[3] = {4, "Dewi Lestari",    "QG-2210", "Citilink",         "Medan",    "C1", "09:45", 3};
    dataMaster[4] = {5, "Rudi Hermawan",   "ID-1337", "Batik Air",        "Makassar", "D2", "10:30", 7};
    dataMaster[5] = {6, "Fitri Handayani", "JT-0178", "Lion Air",         "Lombok",   "B4", "11:00", 5};
    dataMaster[6] = {7, "Hendra Wijaya",   "GA-0312", "Garuda Indonesia", "Jogja",    "A2", "13:20", 4};
    dataMaster[7] = {8, "Nur Azizah",      "SJ-0099", "Sriwijaya Air",    "Padang",   "E1", "14:00", 8};
    jumlahData = 8;
}

// Tambahkan penumpang baru ke data master
void tambahKeMaster(Penumpang p) {
    if (jumlahData < MAX_DATA) {
        dataMaster[jumlahData++] = p;
    } else {
        cout << "  [!] Kapasitas data master penuh.\n";
    }
}

// ============================================================
// HEADER TAMPILAN
// ============================================================
void tampilkanHeader() {
    cout << "\n";
    cout << "  =====================================================\n";
    cout << "  ||    AIRPORT PASSENGER SERVICE SYSTEM           ||\n";
    cout << "  ||    Sistem Layanan Penumpang Bandara            ||\n";
    cout << "  =====================================================\n";
    cout << "  || Mahasiswa : Kelompok [Nomor Kelompok]         ||\n";
    cout << "  || Matkul    : Algoritma dan Pemrograman         ||\n";
    cout << "  =====================================================\n";
}

void tampilkanMenuUtama() {
    cout << "\n";
    cout << "  +-------------------------------------------+\n";
    cout << "  |           MENU UTAMA                      |\n";
    cout << "  +-------------------------------------------+\n";
    cout << "  | 1. Antrian Check-in      [Queue]          |\n";
    cout << "  | 2. Riwayat Boarding      [Stack]          |\n";
    cout << "  | 3. Pencarian Data Tiket  [Divide&Conquer] |\n";
    cout << "  | 4. Laporan Harian        [Paralel]        |\n";
    cout << "  | 5. Tambah Penumpang ke Data Master        |\n";
    cout << "  | 6. Tampilkan Semua Data Master            |\n";
    cout << "  | 7. Analisis Big O Semua Modul             |\n";
    cout << "  | 0. Keluar                                 |\n";
    cout << "  +-------------------------------------------+\n";
    cout << "  Pilih menu: ";
}

// ============================================================
// MENU: TAMBAH PENUMPANG KE DATA MASTER
// ============================================================
void menuTambahDataMaster() {
    if (jumlahData >= MAX_DATA) {
        cout << "  [!] Data master sudah penuh (maks " << MAX_DATA << ").\n";
        return;
    }
    Penumpang p;
    p.id = jumlahData + 1;
    cout << "\n  ===== TAMBAH PENUMPANG BARU =====\n";
    cout << "  Nama         : "; getline(cin, p.nama);
    cout << "  No. Tiket    : "; getline(cin, p.nomorTiket);
    cout << "  Maskapai     : "; getline(cin, p.maskapai);
    cout << "  Tujuan       : "; getline(cin, p.tujuan);
    cout << "  Gate         : "; getline(cin, p.gateBoarding);
    cout << "  Waktu (HH:MM): "; getline(cin, p.waktuBoarding);
    cout << "  Durasi (mnt) : "; cin >> p.durasiLayanan; cin.ignore();
    tambahKeMaster(p);
    cout << "  [OK] Penumpang berhasil ditambahkan. (ID: " << p.id << ")\n";
}

// ============================================================
// TAMPILKAN DATA MASTER
// ============================================================
void tampilkanDataMaster() {
    if (jumlahData == 0) {
        cout << "  Belum ada data penumpang.\n";
        return;
    }
    cout << "\n  ===== DATA MASTER PENUMPANG (" << jumlahData << " orang) =====\n";
    cout << "  ID | Nama                | No.Tiket  | Maskapai           | Tujuan    | Gate | Waktu | Dur\n";
    cout << "  ---|---------------------|-----------|--------------------|-----------|----|-------|----\n";
    for (int i = 0; i < jumlahData; i++) {
        Penumpang& p = dataMaster[i];
        cout << "  " << p.id << "  | "
             << p.nama         << " | "
             << p.nomorTiket   << "  | "
             << p.maskapai     << " | "
             << p.tujuan       << " | "
             << p.gateBoarding << " | "
             << p.waktuBoarding << " | "
             << p.durasiLayanan << "m\n";
    }
}

// ============================================================
// ANALISIS BIG O SEMUA MODUL
// ============================================================
void tampilkanAnalisisBigO() {
    cout << "\n";
    cout << "  ============================================================\n";
    cout << "       ANALISIS KOMPLEKSITAS BIG O - SEMUA MODUL\n";
    cout << "  ============================================================\n\n";

    cout << "  [MODUL 1] ANTRIAN CHECK-IN (Queue)\n";
    cout << "  ------------------------------------------------------------\n";
    cout << "  Operasi     | Best   | Average | Worst  | Keterangan\n";
    cout << "  ------------|--------|---------|--------|-------------------\n";
    cout << "  Enqueue     | O(1)   | O(1)    | O(1)   | Pointer rear\n";
    cout << "  Dequeue     | O(1)   | O(1)    | O(1)   | Pointer front\n";
    cout << "  Peek/Front  | O(1)   | O(1)    | O(1)   | Akses langsung\n";
    cout << "  Tampilkan   | O(n)   | O(n)    | O(n)   | Traversal semua\n\n";

    cout << "  [MODUL 2] RIWAYAT BOARDING (Stack)\n";
    cout << "  ------------------------------------------------------------\n";
    cout << "  Operasi     | Best   | Average | Worst  | Keterangan\n";
    cout << "  ------------|--------|---------|--------|-------------------\n";
    cout << "  Push        | O(1)   | O(1)    | O(1)   | Tambah di atas\n";
    cout << "  Pop         | O(1)   | O(1)    | O(1)   | Hapus dari atas\n";
    cout << "  Peek/Top    | O(1)   | O(1)    | O(1)   | Akses langsung\n";
    cout << "  Tampilkan   | O(n)   | O(n)    | O(n)   | Traversal semua\n\n";

    cout << "  [MODUL 3] PENCARIAN DATA TIKET (Divide & Conquer)\n";
    cout << "  ------------------------------------------------------------\n";
    cout << "  Operasi     | Best     | Average  | Worst    | Keterangan\n";
    cout << "  ------------|----------|----------|----------|---------------\n";
    cout << "  Merge Sort  | O(nlogn) | O(nlogn) | O(nlogn) | Selalu sama\n";
    cout << "  BinarySearch| O(1)     | O(log n) | O(log n) | Bagi 2 tiap iter\n\n";
    cout << "  Penjelasan Merge Sort:\n";
    cout << "    - DIVIDE  : Bagi array menjadi 2 sub-array -> log n level\n";
    cout << "    - CONQUER : Sort rekursif tiap sub-array\n";
    cout << "    - COMBINE : Gabungkan 2 sub-array -> O(n) per level\n";
    cout << "    - Total   : O(n) x O(log n) = O(n log n)\n";
    cout << "    - Tidak ada best/worst karena selalu membagi dua\n\n";
    cout << "  Penjelasan Binary Search:\n";
    cout << "    - Best Case  : Target tepat di tengah -> O(1)\n";
    cout << "    - Worst Case : Target di ujung/tidak ada -> O(log n)\n";
    cout << "    - Setiap iterasi ruang pencarian dibagi 2\n\n";

    cout << "  [MODUL 4] LAPORAN HARIAN (Algoritma Paralel)\n";
    cout << "  ------------------------------------------------------------\n";
    cout << "  Operasi       | Best   | Average | Worst  | Keterangan\n";
    cout << "  --------------|--------|---------|--------|------------------\n";
    cout << "  TotalPenumpang| O(1)   | O(1)    | O(1)   | Langsung dari n\n";
    cout << "  PerMaskapai   | O(n)   | O(n)    | O(n)   | Traversal data\n";
    cout << "  RataRata      | O(n)   | O(n)    | O(n)   | Traversal data\n";
    cout << "  Paralel(3 thr)| O(n)   | O(n)    | O(n)   | max(T1,T2,T3)\n\n";
    cout << "  Keunggulan Paralel:\n";
    cout << "    Sekuensial : T_total = T1 + T2 + T3 (berurutan)\n";
    cout << "    Paralel    : T_total = max(T1, T2, T3) ~ 3x lebih cepat\n";
    cout << "    Bottleneck : Thread 2 & 3 sama-sama O(n), Thread 1 O(1)\n\n";

    cout << "  ============================================================\n";
    cout << "  RINGKASAN KOMPLEKSITAS KESELURUHAN SISTEM:\n";
    cout << "    - Operasi dasar (en/dequeue, push/pop): O(1)\n";
    cout << "    - Sorting data tiket: O(n log n)\n";
    cout << "    - Pencarian tiket: O(log n) setelah sort\n";
    cout << "    - Laporan paralel: O(n) dengan 3 thread\n";
    cout << "  ============================================================\n";
}

// ============================================================
// FUNGSI MAIN
// ============================================================
int main() {
    // Inisialisasi modul
    QueueCheckIn  antrianCheckIn;
    StackRiwayat  riwayatBoarding;

    // Load data dummy
    inisialisasiDataDummy();

    // Pre-load data dummy ke antrian dan stack untuk demo
    for (int i = 0; i < 3 && i < jumlahData; i++) {
        antrianCheckIn.tambahPenumpang(dataMaster[i]);
    }
    for (int i = 3; i < 6 && i < jumlahData; i++) {
        riwayatBoarding.simpanBoardingSelesai(dataMaster[i]);
    }

    tampilkanHeader();
    cout << "\n  [INFO] Data dummy berhasil dimuat (" << jumlahData << " penumpang).\n";

    int pilihan;
    do {
        tampilkanMenuUtama();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                // Modul Anggota 1 - Queue
                menuAntrian(antrianCheckIn);
                break;

            case 2:
                // Modul Anggota 2 - Stack
                menuRiwayatBoarding(riwayatBoarding);
                break;

            case 3:
                // Modul Anggota 2 - Divide & Conquer
                menuPencarianData(dataMaster, jumlahData);
                break;

            case 4:
                // Modul Anggota 3 - Algoritma Paralel
                menuLaporanHarian(dataMaster, jumlahData);
                break;

            case 5:
                menuTambahDataMaster();
                break;

            case 6:
                tampilkanDataMaster();
                break;

            case 7:
                tampilkanAnalisisBigO();
                break;

            case 0:
                cout << "\n  Terima kasih telah menggunakan Airport Passenger Service System.\n";
                cout << "  Selamat tinggal!\n\n";
                break;

            default:
                cout << "  [!] Pilihan tidak valid. Silakan pilih 0-7.\n";
        }

    } while (pilihan != 0);

    return 0;
}
