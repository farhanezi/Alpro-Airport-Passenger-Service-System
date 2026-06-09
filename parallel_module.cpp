#include "parallel_module.h"
#include <chrono>

// ============================================================
// MODUL LAPORAN HARIAN - ALGORITMA PARALEL (Multithreading)
// Tugas Anggota 3 - Airport Passenger Service System
//
// Implementasi menggunakan std::thread (C++11) dan std::mutex
// untuk sinkronisasi. Tiga thread berjalan secara bersamaan:
//   Thread 1 -> Hitung total penumpang          (O(1))
//   Thread 2 -> Hitung penumpang per maskapai   (O(n))
//   Thread 3 -> Hitung rata-rata durasi layanan (O(n))
//
// Keunggulan Paralel vs Sekuensial:
//   - Sekuensial: T1 + T2 + T3 = 3x waktu
//   - Paralel   : max(T1, T2, T3) ≈ 1x waktu
//   - Speed-up  : mendekati 3x lipat (teorema Amdahl)
// ============================================================


// ============================================================
// THREAD 1: Hitung Total Penumpang
// Big O: O(1) - hanya membaca nilai n yang sudah diketahui
// Mutex: digunakan untuk menulis hasil ke variabel shared
// ============================================================
void threadHitungTotal(const Penumpang data[], int n, int& hasil, mutex& mtx) {
    // Simulasi komputasi (realistis untuk dataset besar)
    int total = n;  // O(1) - sudah ada di parameter

    // Lock mutex sebelum menulis ke variabel shared
    lock_guard<mutex> lock(mtx);
    hasil = total;
    cout << "  [Thread 1] Selesai: Total penumpang = " << hasil << "\n";
}


// ============================================================
// THREAD 2: Hitung Penumpang Per Maskapai
// Big O: O(n) - traversal seluruh data satu kali
// Mutex: digunakan saat menulis ke map hasil (shared resource)
// ============================================================
void threadHitungPerMaskapai(const Penumpang data[], int n,
                              map<string, int>& hasil, mutex& mtx) {
    // Hitung lokal dulu (tanpa kunci) untuk efisiensi
    map<string, int> lokalCount;
    for (int i = 0; i < n; i++) {
        lokalCount[data[i].maskapai]++;
    }

    // Lock mutex sebelum menulis hasil ke variabel shared
    lock_guard<mutex> lock(mtx);
    hasil = lokalCount;
    cout << "  [Thread 2] Selesai: Ditemukan "
         << hasil.size() << " maskapai berbeda\n";
}


// ============================================================
// THREAD 3: Hitung Rata-Rata Durasi Layanan
// Big O: O(n) - traversal seluruh data satu kali
// Mutex: digunakan saat menulis hasil ke variabel shared
// ============================================================
void threadHitungRataRata(const Penumpang data[], int n,
                           double& hasil, mutex& mtx) {
    if (n == 0) {
        lock_guard<mutex> lock(mtx);
        hasil = 0.0;
        return;
    }

    // Hitung lokal dulu (tanpa kunci)
    long long totalDurasi = 0;
    for (int i = 0; i < n; i++) {
        totalDurasi += data[i].durasiLayanan;
    }
    double rataRata = static_cast<double>(totalDurasi) / n;

    // Lock mutex sebelum menulis ke variabel shared
    lock_guard<mutex> lock(mtx);
    hasil = rataRata;
    cout << "  [Thread 3] Selesai: Rata-rata durasi = "
         << hasil << " menit\n";
}


// ============================================================
// FUNGSI UTAMA: Jalankan Laporan Paralel
// Membuat 3 thread, jalankan bersamaan, tunggu semua selesai
// ============================================================
HasilLaporan jalankanLaporanParalel(const Penumpang data[], int n) {
    HasilLaporan laporan;
    mutex mtx;  // Satu mutex bersama untuk perlindungan data

    cout << "\n  +----- MEMULAI PEMROSESAN PARALEL -----+\n";
    cout << "  | 3 thread diluncurkan secara bersamaan |\n";
    cout << "  +---------------------------------------+\n\n";

    // Catat waktu mulai
    auto waktuMulai = chrono::high_resolution_clock::now();

    // ---- Buat dan Luncurkan 3 Thread ----
    thread t1(threadHitungTotal,
              data, n,
              ref(laporan.totalPenumpang),
              ref(mtx));

    thread t2(threadHitungPerMaskapai,
              data, n,
              ref(laporan.jumlahPerMaskapai),
              ref(mtx));

    thread t3(threadHitungRataRata,
              data, n,
              ref(laporan.rataRataDurasi),
              ref(mtx));

    // ---- Tunggu semua thread selesai (join) ----
    // join() memastikan main thread menunggu sampai t1, t2, t3 selesai
    t1.join();
    t2.join();
    t3.join();

    // Catat waktu selesai
    auto waktuSelesai = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>
                  (waktuSelesai - waktuMulai).count();

    cout << "\n  [INFO] Semua thread selesai.\n";
    cout << "  [INFO] Waktu eksekusi paralel: "
         << durasi << " mikrodetik\n";

    laporan.selesai = true;
    return laporan;
}


// ============================================================
// TAMPILKAN HASIL LAPORAN
// ============================================================
void tampilkanHasilLaporan(const HasilLaporan& laporan) {
    if (!laporan.selesai) {
        cout << "  [ERROR] Laporan belum diproses.\n";
        return;
    }

    cout << "\n";
    cout << "  ================================================\n";
    cout << "       LAPORAN HARIAN - AIRPORT PASSENGER\n";
    cout << "         SISTEM LAYANAN PENUMPANG BANDARA\n";
    cout << "  ================================================\n\n";

    // --- Bagian 1: Total Penumpang ---
    cout << "  [1] TOTAL PENUMPANG HARI INI\n";
    cout << "  --------------------------------\n";
    cout << "      Total : " << laporan.totalPenumpang << " penumpang\n\n";

    // --- Bagian 2: Per Maskapai ---
    cout << "  [2] JUMLAH PENUMPANG PER MASKAPAI\n";
    cout << "  --------------------------------\n";
    if (laporan.jumlahPerMaskapai.empty()) {
        cout << "      Tidak ada data.\n";
    } else {
        for (const auto& entry : laporan.jumlahPerMaskapai) {
            cout << "      " << entry.first << " : "
                 << entry.second << " penumpang\n";
        }
    }
    cout << "\n";

    // --- Bagian 3: Rata-Rata Durasi ---
    cout << "  [3] RATA-RATA WAKTU LAYANAN\n";
    cout << "  --------------------------------\n";
    // Format manual 2 desimal tanpa iomanip
    int bulat  = (int)laporan.rataRataDurasi;
    int desimal = (int)((laporan.rataRataDurasi - bulat) * 100);
    cout << "      Rata-rata : " << bulat << "."
         << (desimal < 10 ? "0" : "") << desimal
         << " menit per penumpang\n\n";

    cout << "  ================================================\n";
    cout << "  Laporan dihasilkan oleh 3 thread secara paralel.\n";
    cout << "  ================================================\n";
}


// ============================================================
// MENU FUNCTION - Entry point dipanggil dari main()
// ============================================================
void menuLaporanHarian(const Penumpang data[], int n) {
    int pilihan;
    HasilLaporan laporanTerakhir;

    do {
        cout << "\n  ====== MODUL LAPORAN HARIAN (PARALEL) ======\n";
        cout << "  1. Proses laporan harian (3 thread paralel)\n";
        cout << "  2. Tampilkan hasil laporan terakhir\n";
        cout << "  3. Penjelasan konsep Algoritma Paralel\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "  Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            if (n == 0) {
                cout << "  [!] Belum ada data penumpang untuk diproses.\n";
            } else {
                laporanTerakhir = jalankanLaporanParalel(data, n);
                tampilkanHasilLaporan(laporanTerakhir);
            }

        } else if (pilihan == 2) {
            if (!laporanTerakhir.selesai) {
                cout << "  [!] Belum ada laporan yang diproses. Pilih opsi 1 terlebih dahulu.\n";
            } else {
                tampilkanHasilLaporan(laporanTerakhir);
            }

        } else if (pilihan == 3) {
            cout << "\n  ===== KONSEP ALGORITMA PARALEL (MULTITHREADING) =====\n\n";
            cout << "  Definisi:\n";
            cout << "    Multithreading adalah teknik menjalankan beberapa\n";
            cout << "    pekerjaan (thread) secara bersamaan dalam satu proses.\n\n";
            cout << "  Implementasi dalam sistem ini:\n";
            cout << "    Thread 1 -> hitungTotalPenumpang()     : O(1)\n";
            cout << "    Thread 2 -> hitungPerMaskapai()        : O(n)\n";
            cout << "    Thread 3 -> hitungRataRataDurasi()     : O(n)\n\n";
            cout << "  Sinkronisasi:\n";
            cout << "    std::mutex digunakan untuk mencegah race condition\n";
            cout << "    saat beberapa thread menulis ke variabel yang sama.\n";
            cout << "    lock_guard<mutex> otomatis unlock saat keluar scope.\n\n";
            cout << "  Perbandingan Sekuensial vs Paralel:\n";
            cout << "    Sekuensial : T_total = T1 + T2 + T3\n";
            cout << "    Paralel    : T_total = max(T1, T2, T3)\n";
            cout << "    Speed-up   : mendekati 3x untuk 3 thread\n\n";
            cout << "  Big O (Paralel):\n";
            cout << "    Best Case  : O(1) - jika data sangat kecil\n";
            cout << "    Average    : O(n) - bottleneck di Thread 2 & 3\n";
            cout << "    Worst Case : O(n) - semua thread harus traversal\n";
            cout << "  ====================================================\n";

        } else if (pilihan != 0) {
            cout << "  Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);
}
