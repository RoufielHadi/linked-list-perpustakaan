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
#include "queue.h"
#include <time.h>

// Definisi tipe data aktivitas dan riwayat
typedef enum {
    TAMBAH_BUKU,
    EDIT_BUKU,
    HAPUS_BUKU,
    TAMBAH_PEMINJAM,
    HAPUS_PEMINJAM,
    EDIT_PEMINJAM,
    PINJAM_BUKU,
    KEMBALI_BUKU
} TipeAktivitas;

typedef struct riwayat *addressRiwayat;
typedef struct riwayat {
    TipeAktivitas tipe;
    char detail[200];     // Detail aktivitas
    time_t waktu;         // Waktu aktivitas
    addressRiwayat prev;  // Untuk undo
    addressRiwayat next;  // Untuk navigasi
} Riwayat;

typedef struct {
    addressRiwayat first;
    addressRiwayat last;
    addressRiwayat current; // Posisi riwayat saat ini (untuk undo)
} ListRiwayat;

// Deklarasi global
extern ListRiwayat globalRiwayat;
extern ListPeminjaman globalPeminjaman;

/* *** PROTOTYPE *** */

/* *** Fungsi Entry (Tambah Data) *** */
void Implementasi_Tambah_Buku(ListBuku *listBuku, const char *judulBuku, int stokBuku);
/* Tujuan  : Menambahkan buku baru ke dalam linked list jika belum ada */
/* IS      : List buku mungkin kosong atau berisi beberapa buku */
/* FS      : Buku baru ditambahkan ke dalam linked list dengan stok yang ditentukan */

void Implementasi_Tambah_Peminjam(ListBuku *listBuku, const char *judulBuku, const char *namaPeminjam, int skalaPrioritas);
/* Tujuan  : Menambahkan peminjam ke dalam antrian buku tertentu */
/* IS      : Buku sudah ada dalam linked list */
/* FS      : Peminjam baru ditambahkan ke dalam antrian peminjaman buku */

void Implementasi_Tambah_Buku_Ke_Antrian(ListPeminjam *antrian, const char *namaPeminjam, int skalaPrioritas);
/* Tujuan  : Menambahkan peminjam ke dalam antrian dengan prioritas tertentu */
/* IS      : Antrian kosong atau sudah ada beberapa peminjam */
/* FS      : Peminjam dengan prioritas ditambahkan ke dalam antrian */

/* *** Fungsi Delete (Hapus Data) *** */
void Implementasi_Hapus_Buku(ListBuku *listBuku, const char *judulBuku);
/* Tujuan  : Menghapus buku beserta seluruh peminjamnya */
/* IS      : Buku sudah ada dalam linked list */
/* FS      : Buku dan seluruh peminjamnya dihapus dari linked list */

void Implementasi_Hapus_Peminjam(ListBuku *listBuku, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Menghapus peminjam dari antrian buku tertentu */
/* IS      : Buku dan peminjam yang ingin dihapus sudah ada dalam linked list */
/* FS      : Peminjam tertentu dihapus dari antrian peminjaman buku */

/* *** Fungsi Tampilkan Data *** */
void Implementasi_Tampilkan_Semua_Buku(const ListBuku *listBuku);
/* Tujuan  : Menampilkan seluruh buku beserta daftar peminjamnya */
/* IS      : List buku mungkin kosong atau berisi beberapa buku */
/* FS      : Semua data buku dan peminjam ditampilkan */

void Implementasi_Tampilkan_Buku(const ListBuku *listBuku, const char *judulBuku);
/* Tujuan  : Menampilkan peminjam dari buku tertentu */
/* IS      : Buku yang dicari sudah ada dalam linked list */
/* FS      : Daftar peminjam dari buku yang dicari ditampilkan */

/* *** Fungsi Tambahan *** */
int Implementasi_Hitung_Peminjam_Buku(const ListBuku *listBuku, const char *judulBuku);
/* Tujuan  : Menghitung jumlah peminjam di satu buku */
/* IS      : Buku sudah ada dalam linked list */
/* FS      : Jumlah peminjam dalam buku dikembalikan sebagai output */

int Implementasi_Hitung_Total_Buku(const ListBuku *listBuku);
/* Tujuan  : Menghitung total jumlah buku dalam linked list */
/* IS      : List buku mungkin kosong atau berisi beberapa buku */
/* FS      : Jumlah buku dalam linked list dikembalikan sebagai output */

int Implementasi_Hitung_Total_Peminjam(const ListBuku *listBuku);
/* Tujuan  : Menghitung total seluruh peminjam dari semua buku */
/* IS      : List buku mungkin kosong atau berisi beberapa buku dengan peminjamnya */
/* FS      : Jumlah seluruh peminjam dalam semua buku dikembalikan sebagai output */

/* *** Fungsi Edit Data *** */
void Implementasi_Edit_Buku(ListBuku *L, const char *judulBukuLama, const char *judulBukuBaru, int stokBukuBaru);
/* Tujuan  : Mengubah nama buku dan stok buku */
/* IS      : Buku dengan judulBukuLama ada dalam list */
/* FS      : Nama buku diubah menjadi judulBukuBaru dan stok buku diubah menjadi stokBukuBaru */

void Implementasi_Edit_Peminjam(ListBuku *L, const char *judulBuku, const char *namaPeminjamLama, const char *namaPeminjamBaru);
/* Tujuan  : Mengubah nama peminjam dalam suatu buku */
/* IS      : Buku dan peminjam dengan namaPeminjamLama ada dalam list */
/* FS      : Nama peminjam diubah menjadi namaPeminjamBaru */

/* *** Fungsi Tambahan untuk Pengembalian Buku *** */
void Implementasi_Pengembalian_Buku(ListBuku *L, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Mengembalikan buku dan memperbarui antrian peminjam */
/* IS      : Buku dan peminjam sudah ada dalam list */
/* FS      : Peminjam yang mengembalikan buku dihapus dari list peminjaman, 
             stok buku bertambah, dan jika ada antrian, peminjam dengan prioritas tertinggi akan 
             mendapatkan buku berikutnya */

// Fungsi untuk Riwayat
void CreateRiwayat(ListRiwayat *L);
/* Tujuan  : Membuat list riwayat kosong */
/* IS      : L sembarang */
/* FS      : L terdefinisi dengan first, last, dan current = NULL */

void TambahRiwayat(ListRiwayat *L, TipeAktivitas tipe, const char *detail);
/* Tujuan  : Menambahkan riwayat aktivitas baru ke dalam list */
/* IS      : L terdefinisi */
/* FS      : Riwayat baru ditambahkan ke list dengan current menunjuk ke riwayat terakhir */

boolean UndoAktivitas(ListRiwayat *L, ListBuku *LB);
/* Tujuan  : Melakukan undo aktivitas terakhir */
/* IS      : L terdefinisi dan minimal memiliki satu elemen */
/* FS      : Current dipindah ke aktivitas sebelumnya, mengembalikan true jika berhasil */

void TampilkanRiwayat(const ListRiwayat *L);
/* Tujuan  : Menampilkan seluruh riwayat aktivitas */
/* IS      : L terdefinisi */
/* FS      : Seluruh riwayat aktivitas ditampilkan dengan aktivitas terbaru di akhir */

void LakukanUndoOperasi(ListBuku *LB, TipeAktivitas tipe, const char *detail);
/* Tujuan  : Mencoba melakukan operasi undo berdasarkan tipe aktivitas */
/* IS      : LB terdefinisi, tipe dan detail adalah informasi aktivitas yang akan di-undo */
/* FS      : Informasi cara undo ditampilkan ke layar */

/* *** Fungsi Tambahan untuk Pemrosesan Peminjaman Buku *** */
boolean Implementasi_Proses_Peminjaman(ListBuku *L, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Memproses peminjaman buku secara eksplisit */
/* IS      : Peminjam sudah ada dalam antrian buku */
/* FS      : Stok buku dikurangi 1, peminjam dihapus dari antrian, 
             peminjam ditambahkan ke list peminjaman */
/* Mengembalikan nilai true jika berhasil, false jika gagal */

/* *** Fungsi Tambahan untuk List Peminjaman *** */
void Implementasi_Tampilkan_Peminjaman();
/* Tujuan  : Menampilkan daftar buku yang sedang dipinjam */
/* IS      : List peminjaman mungkin kosong atau berisi beberapa peminjaman */
/* FS      : Semua peminjaman ditampilkan ke layar */

#endif

