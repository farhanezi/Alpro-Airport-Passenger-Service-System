#include "dc_module.h"

// ============================================================
// MODUL PENCARIAN DATA TIKET - DIVIDE & CONQUER
// Tugas Anggota 2 - Airport Passenger Service System
//
// Konsep Divide & Conquer (3 tahap):
//   1. DIVIDE  : Pecah masalah menjadi sub-masalah lebih kecil
//   2. CONQUER : Selesaikan sub-masalah secara rekursif
//   3. COMBINE : Gabungkan solusi sub-masalah menjadi solusi utama
//
// Big O Summary:
//   mergeSort    : O(n log n) - Best / Average / Worst semua sama
//   binarySearch : O(1) Best | O(log n) Average & Worst
// ============================================================


// ============================================================
// MERGE - Bagian COMBINE dari Divide & Conquer
// Big O: O(n) untuk setiap pemanggilan
// Alasan: setiap elemen dikunjungi tepat sekali saat penggabungan
// ============================================================
void merge(Penumpang arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Buat array sementara (alokasi dinamis)
    Penumpang* L = new Penumpang[n1];
    Penumpang* R = new Penumpang[n2];

    // Salin data ke array kiri dan kanan
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // COMBINE: Gabungkan dua sub-array secara ascending berdasarkan nomorTiket
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].nomorTiket <= R[j].nomorTiket) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Salin sisa elemen kiri yang belum dipindah
    while (i < n1) { arr[k] = L[i]; i++; k++; }

    // Salin sisa elemen kanan yang belum dipindah
    while (j < n2) { arr[k] = R[j]; j++; k++; }

    // Bebaskan memori dinamis
    delete[] L;
    delete[] R;
}


// ============================================================
// MERGE SORT - Divide & Conquer
// Urutkan array Penumpang berdasarkan nomorTiket (ascending)
//
// Big O: O(n log n) - Best / Average / Worst SEMUA SAMA
// Alasan:
//   - DIVIDE membagi array menjadi 2 bagian sebanyak log n kali
//   - CONQUER: setiap level membutuhkan O(n) waktu untuk merge
//   - Total: O(n) * O(log n) = O(n log n)
//   - Tidak ada kasus lebih baik karena selalu membagi dua
// ============================================================
void mergeSort(Penumpang arr[], int left, int right) {
    if (left < right) {
        // DIVIDE: Cari titik tengah untuk membagi array menjadi dua
        int mid = left + (right - left) / 2;

        // CONQUER: Rekursif urutkan sub-array kiri
        mergeSort(arr, left, mid);

        // CONQUER: Rekursif urutkan sub-array kanan
        mergeSort(arr, mid + 1, right);

        // COMBINE: Gabungkan dua sub-array yang sudah terurut
        merge(arr, left, mid, right);
    }
    // Base case: jika left >= right, sub-array hanya 1 elemen -> sudah terurut
}


// ============================================================
// BINARY SEARCH - Divide & Conquer
// Cari Penumpang berdasarkan nomorTiket
// PRASYARAT: array HARUS sudah diurutkan dengan mergeSort dulu!
//
// Big O:
//   Best Case  : O(1)     - tiket langsung ada di posisi tengah
//   Average Case: O(log n) - rata-rata butuh log n langkah
//   Worst Case : O(log n) - tiket di ujung atau tidak ada
// Alasan: setiap iterasi ruang pencarian DIBAGI 2 -> log n iterasi maksimal
// ============================================================
int binarySearch(Penumpang arr[], int n, string nomorTiket) {
    int left = 0, right = n - 1;

    while (left <= right) {
        // DIVIDE: Cari indeks tengah dari ruang pencarian saat ini
        int mid = left + (right - left) / 2;

        // CONQUER: Bandingkan elemen tengah dengan target
        if (arr[mid].nomorTiket == nomorTiket) {
            return mid;  // Ditemukan!

        } else if (arr[mid].nomorTiket < nomorTiket) {
            // Target ada di sub-array KANAN -> buang setengah kiri
            left = mid + 1;

        } else {
            // Target ada di sub-array KIRI -> buang setengah kanan
            right = mid - 1;
        }
    }

    return -1;  // Tidak ditemukan
}


// ============================================================
// HELPER: Tampilkan data tiket dalam tabel
// Big O: O(n) -> traversal seluruh array
// ============================================================
void tampilkanDataTiket(Penumpang arr[], int n) {
    cout << "\n  No | No. Tiket | Nama                | Maskapai           | Tujuan\n";
    cout << "  ---|-----------|---------------------|--------------------|----------\n";
    for (int i = 0; i < n; i++) {
        cout << "  " << (i + 1) << "  | "
             << arr[i].nomorTiket << "    | "
             << arr[i].nama       << "   | "
             << arr[i].maskapai   << " | "
             << arr[i].tujuan     << "\n";
    }
    cout << "  Total: " << n << " penumpang\n";
}


// ============================================================
// HELPER: Salin isi array sumber ke array tujuan
// Big O: O(n) -> copy satu per satu
// ============================================================
void salinArray(Penumpang src[], Penumpang dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}


// ============================================================
// MENU FUNCTION - Dipanggil oleh Anggota 3 dari main()
// ============================================================
void menuPencarianData(Penumpang dataAll[], int jumlahData) {
    // Buat salinan agar data asli tidak berubah
    Penumpang* dataSorted = new Penumpang[jumlahData];
    salinArray(dataAll, dataSorted, jumlahData);
    bool sudahDiSort = false;

    int pilihan;
    do {
        cout << "\n  ====== MODUL PENCARIAN DATA TIKET (D&C) ======\n";
        cout << "  1. Urutkan data tiket (Merge Sort)\n";
        cout << "  2. Cari penumpang by nomor tiket (Binary Search)\n";
        cout << "  3. Tampilkan semua data tiket\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "  Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "\n  -- Menjalankan Merge Sort (D&C) --\n";
            cout << "  Tahapan Divide & Conquer:\n";
            cout << "  1. DIVIDE  : Array dibagi menjadi 2 sub-array di titik tengah\n";
            cout << "  2. CONQUER : Setiap sub-array diurutkan secara rekursif\n";
            cout << "  3. COMBINE : Sub-array digabung kembali dalam urutan ascending\n";
            cout << "  Big O: O(n log n) - konsisten di semua kasus\n\n";

            mergeSort(dataSorted, 0, jumlahData - 1);
            sudahDiSort = true;
            cout << "  [OK] Data berhasil diurutkan berdasarkan nomor tiket!\n";
            tampilkanDataTiket(dataSorted, jumlahData);

        } else if (pilihan == 2) {
            if (!sudahDiSort) {
                cout << "  [!] Data belum diurutkan. Menjalankan Merge Sort otomatis...\n";
                mergeSort(dataSorted, 0, jumlahData - 1);
                sudahDiSort = true;
                cout << "  [OK] Data berhasil diurutkan.\n";
            }

            string cari;
            cout << "  Masukkan nomor tiket (contoh: GA-1234): ";
            getline(cin, cari);

            cout << "\n  -- Menjalankan Binary Search --\n";
            cout << "  Target: " << cari << "\n";
            cout << "  Proses: Ruang pencarian dibagi 2 tiap iterasi (O(log n))\n";

            int hasil = binarySearch(dataSorted, jumlahData, cari);

            if (hasil != -1) {
                Penumpang& p = dataSorted[hasil];
                cout << "\n  [FOUND] Tiket ditemukan di indeks " << hasil << "!\n";
                cout << "  +------- HASIL PENCARIAN --------+\n";
                cout << "  | Nama          : " << p.nama          << "\n";
                cout << "  | No. Tiket     : " << p.nomorTiket    << "\n";
                cout << "  | Maskapai      : " << p.maskapai      << "\n";
                cout << "  | Tujuan        : " << p.tujuan        << "\n";
                cout << "  | Gate          : " << p.gateBoarding  << "\n";
                cout << "  | Waktu Boarding: " << p.waktuBoarding << "\n";
                cout << "  | Durasi Layanan: " << p.durasiLayanan << " menit\n";
                cout << "  +--------------------------------+\n";
            } else {
                cout << "  [NOT FOUND] Tiket \"" << cari << "\" tidak ditemukan dalam data.\n";
            }

        } else if (pilihan == 3) {
            if (!sudahDiSort) {
                cout << "  (Menampilkan data belum terurut)\n";
            }
            tampilkanDataTiket(dataSorted, jumlahData);

        } else if (pilihan != 0) {
            cout << "  Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    delete[] dataSorted;
}