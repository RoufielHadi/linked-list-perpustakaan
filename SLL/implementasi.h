/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_H
#define IMPLEMENTASI_H

#include "linked.h"
#include <time.h>

// =====================================================
// ===================== STRUKTUR DATA =================
// =====================================================

// Tipe aktivitas yang dapat dilakukan dalam sistem
typedef enum {
    TAMBAH_BUKU,      // Menambah buku baru
    EDIT_BUKU,        // Mengedit informasi buku
    HAPUS_BUKU,       // Menghapus buku
    TAMBAH_PEMINJAM,  // Menambah peminjam baru
    HAPUS_PEMINJAM,   // Menghapus peminjam
    EDIT_PEMINJAM,    // Mengedit informasi peminjam
    PINJAM_BUKU,      // Meminjam buku
    KEMBALI_BUKU      // Mengembalikan buku
} TipeAktivitas;

// Struktur untuk menyimpan riwayat aktivitas
typedef struct riwayat *addressRiwayat;
typedef struct riwayat {
    TipeAktivitas tipe;    // Jenis aktivitas yang dilakukan
    char detail[200];      // Detail aktivitas
    time_t waktu;          // Waktu aktivitas dilakukan
    addressRiwayat prev;   // Pointer ke aktivitas sebelumnya (untuk undo)
    addressRiwayat next;   // Pointer ke aktivitas selanjutnya
} Riwayat;

// Struktur untuk mengelola list riwayat aktivitas
typedef struct {
    addressRiwayat first;    // Pointer ke aktivitas pertama
    addressRiwayat last;     // Pointer ke aktivitas terakhir
    addressRiwayat current;  // Pointer ke aktivitas saat ini (untuk undo)
} ListRiwayat;

// Variabel global untuk riwayat dan peminjaman
extern ListRiwayat globalRiwayat;
extern ListPeminjaman globalPeminjaman;

// =====================================================
// ===================== OPERASI DASAR =================
// =====================================================

/* *** Fungsi Entry (Tambah Data) *** */
void Implementasi_Tambah_Buku(ListBuku *listBuku, const char *judulBuku, int stokBuku);
/* Tujuan  : Menambahkan buku baru ke dalam list buku */
/* IS      : List buku mungkin kosong atau berisi beberapa buku */
/* FS      : Buku baru ditambahkan ke dalam list dengan stok yang ditentukan */

void Implementasi_Tambah_Peminjam(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam, int skalaPrioritas);
/* Tujuan  : Menambahkan peminjam baru ke dalam list peminjam */
/* IS      : Buku sudah ada dalam list buku */
/* FS      : Peminjam baru ditambahkan ke list peminjam untuk buku tersebut */

/* *** Fungsi Delete (Hapus Data) *** */
void Implementasi_Hapus_Buku(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku);
/* Tujuan  : Menghapus buku beserta seluruh peminjamnya */
/* IS      : Buku sudah ada dalam list buku */
/* FS      : Buku dan seluruh peminjamnya dihapus dari list */

void Implementasi_Hapus_Peminjam(ListPeminjam *listPeminjam, const char *namaPeminjam);
/* Tujuan  : Menghapus peminjam dari list peminjam */
/* IS      : Peminjam yang ingin dihapus sudah ada dalam list */
/* FS      : Peminjam tertentu dihapus dari list peminjam */

/* *** Fungsi Tampilkan Data *** */
void Implementasi_Tampilkan_Semua_Buku(const ListBuku *listBuku, const ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan seluruh buku beserta daftar peminjamnya */
/* IS      : List buku mungkin kosong atau berisi beberapa buku */
/* FS      : Semua data buku dan peminjam ditampilkan ke layar */

void Implementasi_Tampilkan_Buku(const ListBuku *listBuku, const ListPeminjam *listPeminjam, const char *judulBuku);
/* Tujuan  : Menampilkan informasi buku tertentu beserta peminjamnya */
/* IS      : Buku yang dicari sudah ada dalam list buku */
/* FS      : Informasi buku dan daftar peminjamnya ditampilkan ke layar */

/* *** Fungsi Tambahan *** */
int Implementasi_Hitung_Peminjam_Buku(const ListPeminjam *listPeminjam, const char *judulBuku);
/* Tujuan  : Menghitung jumlah peminjam untuk buku tertentu */
/* IS      : Buku sudah ada dalam list buku */
/* FS      : Jumlah peminjam untuk buku tersebut dikembalikan */

int Implementasi_Hitung_Total_Buku(const ListBuku *listBuku);
/* Tujuan  : Menghitung total jumlah buku dalam list */
/* IS      : List buku mungkin kosong atau berisi beberapa buku */
/* FS      : Jumlah total buku dalam list dikembalikan */

int Implementasi_Hitung_Total_Peminjam(const ListPeminjam *listPeminjam);
/* Tujuan  : Menghitung total seluruh peminjam */
/* IS      : List peminjam mungkin kosong atau berisi beberapa peminjam */
/* FS      : Jumlah total peminjam dikembalikan */

/* *** Fungsi Edit Data *** */
void Implementasi_Edit_Buku(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBukuLama, const char *judulBukuBaru, int stokBukuBaru);
/* Tujuan  : Mengubah informasi buku (judul dan stok) */
/* IS      : Buku dengan judulBukuLama ada dalam list */
/* FS      : Informasi buku diubah sesuai dengan parameter baru */

void Implementasi_Edit_Peminjam(ListPeminjam *listPeminjam, const char *namaPeminjamLama, const char *namaPeminjamBaru);
/* Tujuan  : Mengubah nama peminjam */
/* IS      : Peminjam dengan namaPeminjamLama ada dalam list */
/* FS      : Nama peminjam diubah menjadi namaPeminjamBaru */

/* *** Fungsi Pengembalian Buku *** */
void Implementasi_Pengembalian_Buku(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Memproses pengembalian buku */
/* IS      : Buku dan peminjam sudah ada dalam list */
/* FS      : Peminjam dihapus dari list peminjam, stok buku bertambah, 
             dan jika ada antrian, peminjam dengan prioritas tertinggi 
             akan mendapatkan buku */

// =====================================================
// ================= OPERASI RIWAYAT ===================
// =====================================================

void CreateRiwayat(ListRiwayat *L);
/* Tujuan  : Membuat list riwayat kosong */
/* IS      : L sembarang */
/* FS      : L terdefinisi dengan first, last, dan current = NULL */

void TambahRiwayat(ListRiwayat *L, TipeAktivitas tipe, const char *detail);
/* Tujuan  : Menambahkan riwayat aktivitas baru */
/* IS      : L terdefinisi */
/* FS      : Riwayat baru ditambahkan ke list dengan current menunjuk ke riwayat terakhir */

boolean UndoAktivitas(ListRiwayat *L, ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Melakukan undo aktivitas terakhir */
/* IS      : L terdefinisi dan minimal memiliki satu elemen */
/* FS      : Current dipindah ke aktivitas sebelumnya, mengembalikan true jika berhasil */

void TampilkanRiwayat(const ListRiwayat *L);
/* Tujuan  : Menampilkan seluruh riwayat aktivitas */
/* IS      : L terdefinisi */
/* FS      : Seluruh riwayat aktivitas ditampilkan ke layar */

void LakukanUndoOperasi(ListBuku *listBuku, ListPeminjam *listPeminjam, TipeAktivitas tipe, const char *detail);
/* Tujuan  : Melakukan operasi undo berdasarkan tipe aktivitas */
/* IS      : listBuku dan listPeminjam terdefinisi */
/* FS      : Operasi undo dilakukan sesuai dengan tipe aktivitas */

// =====================================================
// ============= OPERASI PEMINJAMAN BUKU ===============
// =====================================================

boolean Implementasi_Proses_Peminjaman(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Memproses peminjaman buku */
/* IS      : Peminjam sudah ada dalam list buku */
/* FS      : Stok buku dikurangi, peminjam dihapus dari list antrian, 
             dan ditambahkan ke list peminjaman */
/* Mengembalikan true jika berhasil, false jika gagal */

void Implementasi_Tampilkan_Peminjaman();
/* Tujuan  : Menampilkan daftar buku yang sedang dipinjam */
/* IS      : List peminjaman mungkin kosong atau berisi beberapa peminjaman */
/* FS      : Semua peminjaman ditampilkan ke layar */

addressPeminjam SearchPeminjamForBuku(ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Mencari peminjam dengan nama tertentu yang meminjam buku tertentu */
/* IS      : listPeminjam terdefinisi */
/* FS      : Mengembalikan address node peminjam jika ditemukan, NULL jika tidak */

#endif

