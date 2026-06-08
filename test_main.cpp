// ============================================================
// TEST FILE - Anggota 2
// Jalankan ini untuk verifikasi Stack & D&C bekerja
// Setelah OK, kirim penumpang.h + stack_module.* + dc_module.*
// ke Anggota 3 untuk diintegrasikan ke main.cpp
// ============================================================

#include <iostream>
#include "penumpang.h"
#include "stack_module.h"
#include "dc_module.h"
using namespace std;

// Data dummy bandara untuk testing
Penumpang buatDataDummy(int jumlah, Penumpang arr[]) {
    // 8 penumpang dummy
    arr[0] = {1, "Budi Santoso",    "GA-1023", "Garuda Indonesia","Jakarta",  "A1", "07:30", 5};
    arr[1] = {2, "Siti Rahayu",     "JT-0045", "Lion Air",        "Surabaya", "B2", "08:15", 4};
    arr[2] = {3, "Ahmad Fauzi",     "GA-0891", "Garuda Indonesia","Bali",     "A3", "09:00", 6};
    arr[3] = {4, "Dewi Lestari",    "QG-2210", "Citilink",        "Medan",    "C1", "09:45", 3};
    arr[4] = {5, "Rudi Hermawan",   "ID-1337", "Batik Air",       "Makassar", "D2", "10:30", 7};
    arr[5] = {6, "Fitri Handayani", "JT-0178", "Lion Air",        "Lombok",   "B4", "11:00", 5};
    arr[6] = {7, "Hendra Wijaya",   "GA-0312", "Garuda Indonesia","Jogja",    "A2", "13:20", 4};
    arr[7] = {8, "Nur Azizah",      "SJ-0099", "Sriwijaya Air",   "Padang",   "E1", "14:00", 8};
    return arr[0];
}

int main() {
    cout << "============================================\n";
    cout << " TEST MODUL ANGGOTA 2 - Airport System\n";
    cout << "============================================\n\n";

    // --- Inisialisasi data dummy ---
    const int N = 8;
    Penumpang data[N];
    buatDataDummy(N, data);

    // ============================================================
    // TEST 1: STACK MODULE
    // ============================================================
    cout << "=== TEST 1: STACK (Riwayat Boarding) ===\n";
    StackRiwayat stack;

    // Push beberapa penumpang
    cout << "\n-- Push 3 penumpang selesai boarding --\n";
    stack.simpanBoardingSelesai(data[0]);
    stack.simpanBoardingSelesai(data[1]);
    stack.simpanBoardingSelesai(data[2]);

    // Tampilkan terakhir
    cout << "\n-- Peek: boarding terakhir --\n";
    stack.tampilkanBoardingTerakhir();

    // Tampilkan semua riwayat
    cout << "\n-- Tampilkan semua riwayat --\n";
    stack.tampilkanRiwayatBoarding();

    // Undo
    cout << "\n-- Undo pelayanan terakhir --\n";
    stack.undoPelayananTerakhir();

    // Cek setelah undo
    cout << "\n-- Riwayat setelah undo --\n";
    stack.tampilkanRiwayatBoarding();

    // ============================================================
    // TEST 2: MERGE SORT
    // ============================================================
    cout << "\n=== TEST 2: MERGE SORT (Divide & Conquer) ===\n";

    // Tampilkan sebelum sort
    cout << "\n-- Data SEBELUM Merge Sort --\n";
    tampilkanDataTiket(data, N);

    // Sort
    Penumpang sorted[N];
    salinArray(data, sorted, N);
    mergeSort(sorted, 0, N - 1);

    // Tampilkan setelah sort
    cout << "\n-- Data SESUDAH Merge Sort (by No. Tiket) --\n";
    tampilkanDataTiket(sorted, N);

    // ============================================================
    // TEST 3: BINARY SEARCH
    // ============================================================
    cout << "\n=== TEST 3: BINARY SEARCH (Divide & Conquer) ===\n";

    string cariTiket = "JT-0178";
    cout << "Mencari tiket: " << cariTiket << "\n";
    int hasil = binarySearch(sorted, N, cariTiket);
    if (hasil != -1) {
        cout << "[FOUND] Ditemukan di indeks " << hasil << ": "
             << sorted[hasil].nama << " -> " << sorted[hasil].maskapai << "\n";
    } else {
        cout << "[NOT FOUND]\n";
    }

    // Cari tiket yang tidak ada
    string cariTiket2 = "XX-9999";
    cout << "Mencari tiket: " << cariTiket2 << "\n";
    int hasil2 = binarySearch(sorted, N, cariTiket2);
    if (hasil2 != -1) {
        cout << "[FOUND]\n";
    } else {
        cout << "[NOT FOUND] " << cariTiket2 << " tidak ada di data.\n";
    }

    cout << "\n============================================\n";
    cout << " SEMUA TEST SELESAI - Modul siap diintegrasikan!\n";
    cout << " Kirim ke Anggota 3:\n";
    cout << "   penumpang.h\n";
    cout << "   stack_module.h + stack_module.cpp\n";
    cout << "   dc_module.h    + dc_module.cpp\n";
    cout << "============================================\n";

    return 0;
}