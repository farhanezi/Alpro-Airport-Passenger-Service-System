# Airport Passenger Service System

**Mata Kuliah:** Algoritma dan Pemrograman  
**Topik Proyek:** No. 7 — Airport Passenger Service System  
**Bahasa:** C++ (Native, tanpa STL container)  

---

## Deskripsi Sistem

Sistem manajemen layanan penumpang bandara yang mengimplementasikan empat struktur data dan algoritma utama:

| Modul | Algoritma | Fitur |
|-------|-----------|-------|
| Antrian Check-in | **Queue** (Linked List) | Enqueue, Dequeue, Tampilkan antrian |
| Riwayat Boarding | **Stack** (Linked List) | Push, Pop, Peek, Undo |
| Pencarian Tiket | **Divide & Conquer** | Merge Sort + Binary Search |
| Laporan Harian | **Algoritma Paralel** | 3 thread dengan `std::thread` + `std::mutex` |

---

## Struktur File

```
Alpro-Airport-Passenger-Service-System/
├── penumpang.h          # Struct data penumpang (shared semua modul)
├── queue_module.h/.cpp  # Modul Antrian Check-in (Anggota 1)
├── stack_module.h/.cpp  # Modul Riwayat Boarding (Anggota 2)
├── dc_module.h/.cpp     # Modul Pencarian Tiket (Anggota 2)
├── parallel_module.h/.cpp # Modul Laporan Paralel (Anggota 3)
├── main.cpp             # Integrasi & menu utama (Anggota 3)
├── Makefile             # Build system
└── README.md            # Dokumentasi ini
```

---

## Cara Kompilasi & Menjalankan

### Menggunakan Makefile (direkomendasikan)
```bash
make
./airport_system
```

### Kompilasi Manual (jika `make` tidak tersedia)
```bash
g++ -std=c++11 -pthread -o airport_system \
    main.cpp queue_module.cpp stack_module.cpp \
    dc_module.cpp parallel_module.cpp
./airport_system
```

> **Catatan:** Flag `-pthread` wajib karena Modul 4 menggunakan `std::thread`.

---

## Detail Implementasi per Modul

### Modul 1 — Antrian Check-in (Queue)

Implementasi queue dengan linked list tanpa STL. Node dialokasikan secara dinamis, pointer `front` dan `rear` masing-masing menunjuk ke ujung antrian.

**Operasi Utama:**
- `enqueue(p)` — Tambah penumpang ke belakang: **O(1)**
- `dequeue()` — Ambil & hapus dari depan: **O(1)**
- `tampilkanAntrian()` — Traversal semua node: **O(n)**

---

### Modul 2 — Riwayat Boarding (Stack)

Stack berbasis linked list dengan LIFO (*Last In First Out*). Digunakan untuk menyimpan riwayat penumpang yang sudah boarding, dengan kemampuan undo.

**Operasi Utama:**
- `push(p)` — Tambah di atas stack: **O(1)**
- `pop()` — Ambil & hapus dari atas: **O(1)**
- `peek()` — Lihat atas tanpa hapus: **O(1)**
- `undoPelayananTerakhir()` — Pop + laporan: **O(1)**

---

### Modul 3 — Pencarian Data Tiket (Divide & Conquer)

Mengimplementasikan Merge Sort dan Binary Search menggunakan paradigma Divide & Conquer.

**Merge Sort** — Tiga tahap D&C:
1. **DIVIDE:** Bagi array di titik tengah `mid = (left + right) / 2`
2. **CONQUER:** Rekursif sort sub-array kiri dan kanan
3. **COMBINE:** Gabungkan dua sub-array terurut

**Kompleksitas Merge Sort:** O(n log n) — Best / Average / Worst **sama semua** (tidak ada short-circuit).

**Binary Search** — Ruang pencarian dibagi 2 tiap iterasi:
- **Best Case:** O(1) — target tepat di indeks tengah
- **Average/Worst:** O(log n) — target di ujung atau tidak ada

---

### Modul 4 — Laporan Harian (Algoritma Paralel)

Menggunakan `std::thread` (C++11) untuk menjalankan tiga kalkulasi laporan secara bersamaan. `std::mutex` dengan `lock_guard` mencegah *race condition* saat menulis ke variabel bersama.

```
Thread 1  ──────────────────────────── [O(1)]  hitung total
Thread 2  ────────────────────────────────── [O(n)]  hitung per maskapai
Thread 3  ───────────────────────────────────── [O(n)]  hitung rata-rata
           ↑                                          ↑
        launch                                     join()
```

**Perbandingan:**
| Mode | Waktu Total |
|------|------------|
| Sekuensial | T1 + T2 + T3 |
| Paralel (3 thread) | max(T1, T2, T3) |

---

## Analisis Big O Keseluruhan

| Operasi | Kompleksitas |
|---------|-------------|
| Enqueue / Dequeue | O(1) |
| Push / Pop / Peek | O(1) |
| Merge Sort | O(n log n) |
| Binary Search | O(log n) setelah sort |
| Laporan Paralel | O(n) dengan 3 thread |

---

## Pembagian Tugas

| Anggota | Tugas | Bobot |
|---------|-------|-------|
| Anggota 1 | Queue (Antrian Check-in) + Big O | 30% |
| Anggota 2 | Stack (Riwayat Boarding) + Divide & Conquer | 40% |
| Anggota 3 | Algoritma Paralel (Multithreading) + Integrasi `main.cpp` | 30% |

---

## Dikerjakan Bersama

- Desain `struct Penumpang` (`penumpang.h`)
- Sistem menu utama (`main.cpp` — Anggota 3, review bersama)
- Testing & bug fix lintas modul
- Video demonstrasi (rekam bersama, maks 5 menit)
