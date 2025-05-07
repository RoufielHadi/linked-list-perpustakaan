/*
Author: Roufiel Hadi
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef LINKED_H
#define LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#define MAX 100

// =====================================================
// ===================== STRUKTUR DATA =================
// =====================================================

// Struktur untuk Linked List Non Restricted Fitur List Buku di Perpustakaan
typedef struct buku *addressBuku;
typedef struct buku {
    char judulBuku[MAX];  
    int stok; // Jumlah stok buku yang tersedia
    addressBuku next;           
} daftarBuku;

typedef struct {
    addressBuku First;
    addressBuku Tail;
} ListBuku;

// Struktur untuk Linked List Queue Fitur List Peminjam di Perpustakaan
typedef struct peminjam *addressPeminjam;
typedef struct peminjam {
    char namaPeminjam[MAX];  
    int skalaPrioritas; // 1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum
    addressBuku bukuDipinjam; // Pointer ke buku yang dipinjam
    addressPeminjam next;           
} antrianPeminjam;

typedef struct {
    addressPeminjam First;
    addressPeminjam Tail;
} ListPeminjam;

// Struktur untuk Linked List Peminjaman yang Sedang Berlangsung
typedef struct peminjaman *addressPeminjaman;
typedef struct peminjaman {
    char judulBuku[MAX];  
    char namaPeminjam[MAX];
    int skalaPrioritas; // 1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum
    addressPeminjaman next;
} daftarPeminjaman;

typedef struct {
    addressPeminjaman First;
} ListPeminjaman;

// =====================================================
// ===================== KONSTRUKTOR ===================
// =====================================================
void CreateListBuku(ListBuku *L);
/* Tujuan  : Membuat list buku kosong */
/* IS      : L sembarang */
/* FS      : Terbentuk list buku kosong (First = NULL, Tail = NULL) */

void DeleteListBuku(ListBuku *L);
/* Tujuan  : Menghapus semua elemen dalam list buku */
/* IS      : L mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list buku dihapus dan didealokasi */

void CreateListPeminjam(ListPeminjam *L);
/* Tujuan  : Membuat list peminjam kosong */
/* IS      : L sembarang */
/* FS      : Terbentuk list peminjam kosong (First = NULL, Tail = NULL) */

void DeleteListPeminjam(ListPeminjam *L);
/* Tujuan  : Menghapus semua elemen dalam list peminjam */
/* IS      : L mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list peminjam dihapus dan didealokasi */

void CreateListPeminjaman(ListPeminjaman *L);
/* Tujuan  : Membuat list peminjaman kosong */
/* IS      : L sembarang */
/* FS      : Terbentuk list peminjaman kosong (First = NULL) */

void DeleteListPeminjaman(ListPeminjaman *L);
/* Tujuan  : Menghapus semua elemen dalam list peminjaman */
/* IS      : L mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list peminjaman dihapus dan didealokasi */

// =====================================================
// ===================== VALIDATOR =====================
// =====================================================
boolean isEmptyBuku(ListBuku L);
/* Tujuan  : Mengecek apakah list buku kosong */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan TRUE jika list kosong, FALSE jika tidak */

boolean isEmptyPeminjam(ListPeminjam L);
/* Tujuan  : Mengecek apakah list peminjam kosong */
/* IS      : List peminjam mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan TRUE jika list kosong, FALSE jika tidak */

boolean isEmptyPeminjaman(ListPeminjaman L);
/* Tujuan  : Mengecek apakah list peminjaman kosong */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan TRUE jika list kosong, FALSE jika tidak */

// =====================================================
// ================== OPERASI DASAR ====================
// =====================================================
addressBuku CreateNodeBuku(const char *judulBuku, int stok);
/* Tujuan  : Membuat node baru dengan data buku */
/* IS      : Judul buku dan stok terdefinisi */
/* FS      : Mengembalikan address node baru, atau NULL jika gagal */

addressPeminjam CreateNodePeminjam(const char *namaPeminjam, int skalaPrioritas, addressBuku bukuDipinjam);
/* Tujuan  : Membuat node baru dengan data peminjam */
/* IS      : Nama peminjam, skala prioritas, dan buku dipinjam terdefinisi */
/* FS      : Mengembalikan address node baru, atau NULL jika gagal */

addressPeminjaman CreatePeminjaman(const char *judulBuku, const char *namaPeminjam, int skalaPrioritas);
/* Tujuan  : Membuat node baru peminjaman */
/* IS      : Data peminjaman terdefinisi */
/* FS      : Mengembalikan address node baru, atau NULL jika gagal */

void InsertFirstBuku(ListBuku *L, addressBuku P);
/* Tujuan  : Menambahkan elemen P sebagai elemen pertama dalam list buku */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen pertama dalam list buku */

void InsertFirstPeminjam(ListPeminjam *L, addressPeminjam P);
/* Tujuan  : Menambahkan elemen P sebagai elemen pertama dalam list peminjam */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen pertama dalam list peminjam */

void InsertFirstPeminjaman(ListPeminjaman *L, addressPeminjaman P);
/* Tujuan  : Menambahkan elemen P sebagai elemen pertama dalam daftar peminjaman */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen pertama dalam list peminjaman */

void InsertLastBuku(ListBuku *L, addressBuku P);
/* Tujuan  : Menambahkan elemen P sebagai elemen terakhir dalam list buku */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen terakhir dalam list buku */

void InsertLastPeminjam(ListPeminjam *L, addressPeminjam P);
/* Tujuan  : Menambahkan elemen P sebagai elemen terakhir dalam list peminjam */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen terakhir dalam list peminjam */

void InsertLastPeminjaman(ListPeminjaman *L, addressPeminjaman P);
/* Tujuan  : Menambahkan elemen P sebagai elemen terakhir dalam daftar peminjaman */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen terakhir dalam list peminjaman */

void InsertAfterBuku(addressBuku pBef, addressBuku PNew);
/* Tujuan  : Menyisipkan elemen PNew setelah elemen pBef dalam list buku */
/* IS      : pBef tidak NULL */
/* FS      : PNew menjadi elemen setelah pBef dalam list buku */

void InsertAfterPeminjam(addressPeminjam pBef, addressPeminjam PNew);
/* Tujuan  : Menyisipkan elemen PNew setelah elemen pBef dalam list peminjam */
/* IS      : pBef tidak NULL */
/* FS      : PNew menjadi elemen setelah pBef dalam list peminjam */

void DeleteFirstBuku(ListBuku *L);
/* Tujuan  : Menghapus elemen pertama dari list buku */
/* IS      : List tidak kosong */
/* FS      : Elemen pertama dalam list buku dihapus dan didealokasi */

void DeleteFirstPeminjam(ListPeminjam *L);
/* Tujuan  : Menghapus elemen pertama dari list peminjam */
/* IS      : List tidak kosong */
/* FS      : Elemen pertama dalam list peminjam dihapus dan didealokasi */

void DeleteFirstPeminjaman(ListPeminjaman *L);
/* Tujuan  : Menghapus elemen pertama dari daftar peminjaman */
/* IS      : List tidak kosong */
/* FS      : Elemen pertama dalam daftar peminjaman dihapus dan didealokasi */

void DeleteLastBuku(ListBuku *L);
/* Tujuan  : Menghapus elemen terakhir dari list buku */
/* IS      : List tidak kosong */
/* FS      : Elemen terakhir dalam list buku dihapus dan didealokasi */

void DeleteLastPeminjam(ListPeminjam *L);
/* Tujuan  : Menghapus elemen terakhir dari list peminjam */
/* IS      : List tidak kosong */
/* FS      : Elemen terakhir dalam list peminjam dihapus dan didealokasi */

void DeleteAfterBuku(addressBuku pBef);
/* Tujuan  : Menghapus elemen setelah pBef dalam list buku */
/* IS      : pBef tidak NULL dan memiliki elemen setelahnya */
/* FS      : Elemen setelah pBef dalam list buku dihapus dan didealokasi */

void DeleteAfterPeminjam(addressPeminjam pBef);
/* Tujuan  : Menghapus elemen setelah pBef dalam list peminjam */
/* IS      : pBef tidak NULL dan memiliki elemen setelahnya */
/* FS      : Elemen setelah pBef dalam list peminjam dihapus dan didealokasi */

void DeAlokasiBuku(addressBuku *P);
/* Tujuan  : Mengembalikan memori dari suatu node buku ke sistem */
/* IS      : P terdefinisi */
/* FS      : Memori yang ditempati oleh P dikembalikan ke sistem */

void DeAlokasiPeminjam(addressPeminjam *P);
/* Tujuan  : Mengembalikan memori dari suatu node peminjam ke sistem */
/* IS      : P terdefinisi */
/* FS      : Memori yang ditempati oleh P dikembalikan ke sistem */

void DeAlokasiPeminjaman(addressPeminjaman *P);
/* Tujuan  : Mengembalikan memori dari suatu node peminjaman ke sistem */
/* IS      : P terdefinisi */
/* FS      : Memori yang ditempati oleh P dikembalikan ke sistem */

// =====================================================
// ================= OPERASI TAMBAHAN =================
// =====================================================
int NbElmtBuku(ListBuku L);
/* Tujuan  : Menghitung jumlah elemen dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan jumlah elemen dalam list buku */

int NbElmtPeminjam(ListPeminjam L);
/* Tujuan  : Menghitung jumlah elemen dalam list peminjam */
/* IS      : List peminjam mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan jumlah elemen dalam list peminjam */

addressBuku SearchBuku(ListBuku L, const char *judulBuku);
/* Tujuan  : Mencari buku berdasarkan judul dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan address buku jika ditemukan, NULL jika tidak */

addressPeminjam SearchPeminjam(ListPeminjam L, const char *namaPeminjam);
/* Tujuan  : Mencari peminjam berdasarkan nama dalam list peminjam */
/* IS      : List peminjam mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan address peminjam jika ditemukan, NULL jika tidak */

addressPeminjaman SearchPeminjaman(ListPeminjaman L, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Mencari peminjaman berdasarkan judul buku dan nama peminjam */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan address peminjaman jika ditemukan, NULL jika tidak */

void PrintBuku(ListBuku L);
/* Tujuan  : Menampilkan semua elemen buku dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Semua elemen buku dalam list buku ditampilkan ke layar */

void PrintPeminjam(ListPeminjam L);
/* Tujuan  : Menampilkan semua elemen peminjam dalam list peminjam */
/* IS      : List peminjam mungkin kosong atau berisi elemen */
/* FS      : Semua elemen peminjam dalam list peminjam ditampilkan ke layar */

void PrintPeminjaman(ListPeminjaman L);
/* Tujuan  : Menampilkan semua elemen peminjaman dalam list peminjaman */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Semua elemen peminjaman dalam list peminjaman ditampilkan ke layar */

ListBuku BalikListBuku(ListBuku L);
/* Tujuan  : Membalik urutan elemen dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan list buku dengan urutan elemen terbalik */

ListPeminjam BalikListPeminjam(ListPeminjam L);
/* Tujuan  : Membalik urutan elemen dalam list peminjam */
/* IS      : List peminjam mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan list peminjam dengan urutan elemen terbalik */

#endif

