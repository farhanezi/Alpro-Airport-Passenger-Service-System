#ifndef PARALLEL_MODULE_H
#define PARALLEL_MODULE_H

#include "penumpang.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <string>
using namespace std;

// ============================================================
// MODUL LAPORAN HARIAN - ALGORITMA PARALEL (Multithreading)
// Tugas Anggota 3
//
// Konsep Multithreading:
//   - Setiap kalkulasi laporan dijalankan di thread terpisah
//   - std::thread untuk manajemen thread (C++11 standard)
//   - std::mutex untuk sinkronisasi akses data bersama
//
// Big O Summary:
//   hitungTotalPenumpang   : O(1)     - langsung dari counter
//   hitungPerMaskapai      : O(n)     - traversal data
//   hitungRataRataLayanan  : O(n)     - traversal data
//   Paralel (3 thread)     : O(n)     - concurrent, waktu ~1/3 sekuensial
// ============================================================

// Struct untuk menyimpan hasil laporan
struct HasilLaporan {
    int totalPenumpang;
    map<string, int> jumlahPerMaskapai;
    double rataRataDurasi;
    bool selesai;

    HasilLaporan() : totalPenumpang(0), rataRataDurasi(0.0), selesai(false) {}
};

// ============================================================
// FUNGSI-FUNGSI LAPORAN (dijalankan di dalam thread)
// ============================================================

// Thread 1: Hitung total penumpang - O(1)
void threadHitungTotal(const Penumpang data[], int n, int& hasil, mutex& mtx);

// Thread 2: Hitung jumlah penumpang per maskapai - O(n)
void threadHitungPerMaskapai(const Penumpang data[], int n,
                              map<string, int>& hasil, mutex& mtx);

// Thread 3: Hitung rata-rata waktu layanan - O(n)
void threadHitungRataRata(const Penumpang data[], int n,
                          double& hasil, mutex& mtx);

// ============================================================
// FUNGSI UTAMA - Jalankan laporan paralel dengan 3 thread
// ============================================================
HasilLaporan jalankanLaporanParalel(const Penumpang data[], int n);

// Tampilkan hasil laporan ke console
void tampilkanHasilLaporan(const HasilLaporan& laporan);

// Entry point - dipanggil dari main menu
void menuLaporanHarian(const Penumpang data[], int n);

#endif // PARALLEL_MODULE_H
