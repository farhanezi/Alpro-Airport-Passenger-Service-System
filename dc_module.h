#ifndef DC_MODULE_H
#define DC_MODULE_H

#include "penumpang.h"
#include <iostream>
using namespace std;

// ============================================================
// MODUL PENCARIAN DATA TIKET - DIVIDE & CONQUER
// Tugas Anggota 2
//
// Konsep Divide & Conquer (3 tahap):
//   1. DIVIDE  : Pecah masalah menjadi sub-masalah lebih kecil
//   2. CONQUER : Selesaikan sub-masalah secara rekursif
//   3. COMBINE : Gabungkan solusi sub-masalah menjadi solusi utama
//
// Diimplementasikan pada:
//   - Merge Sort : urut data tiket
//   - Binary Search : cari tiket by nomorTiket
//
// Big O Summary:
//   mergeSort    : O(n log n) - Best / Average / Worst (semua sama)
//   binarySearch : O(1) Best | O(log n) Average & Worst
// ============================================================

// --- MERGE SORT ---
// Urutkan array Penumpang berdasarkan nomorTiket (ascending)
void merge(Penumpang arr[], int left, int mid, int right);
void mergeSort(Penumpang arr[], int left, int right);

// --- BINARY SEARCH ---
// Cari Penumpang berdasarkan nomorTiket
// PRASYARAT: array HARUS sudah diurutkan dengan mergeSort dulu!
// Return: index jika ditemukan, -1 jika tidak
int binarySearch(Penumpang arr[], int n, string nomorTiket);

// --- HELPER ---
void tampilkanDataTiket(Penumpang arr[], int n);
void salinArray(Penumpang src[], Penumpang dst[], int n);

// Entry point untuk Anggota 3 (dipanggil dari main menu)
void menuPencarianData(Penumpang dataAll[], int jumlahData);

#endif // DC_MODULE_H