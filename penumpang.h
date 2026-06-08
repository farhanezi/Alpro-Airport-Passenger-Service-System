#ifndef PENUMPANG_H
#define PENUMPANG_H

#include <string>
using namespace std;

// ============================================================
// STRUCT UTAMA - WAJIB DISEPAKATI SEMUA ANGGOTA
// Airport Passenger Service System
// Anggota 1 (Queue) | Anggota 2 (Stack+D&C) | Anggota 3 (Parallel)
// ============================================================

struct Penumpang {
    int    id;              // ID unik urutan masuk
    string nama;            // Nama lengkap penumpang
    string nomorTiket;      // Format: "XX-NNNN" cth: "GA-1234" <- kunci sorting & search
    string maskapai;        // Garuda Indonesia, Lion Air, dll.
    string tujuan;          // Kota tujuan penerbangan
    string gateBoarding;    // Gate boarding: "A1", "B3", dll.
    string waktuBoarding;   // Format "HH:MM" cth: "14:30"
    int    durasiLayanan;   // Durasi layanan dalam menit (untuk laporan)
};

#endif // PENUMPANG_H