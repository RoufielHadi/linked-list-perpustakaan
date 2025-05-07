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
#include "queue.h"
#define MAX 100

// Data struktur untuk peminjaman yang sedang berlangsung
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

// Struktur untuk Linked List Non Restricted Fitur List Buku di Perpustakaan
typedef struct buku *addressBuku;
typedef struct buku {
    char judulBuku[MAX];  
    int stokBuku;      
    ListPeminjam antrianPeminjam;
    addressBuku next;           
} daftarBuku;

typedef struct {
    addressBuku First;
} ListBuku;

// =====================================================
// ===================== KONSTRUKTOR ===================
// =====================================================
void CreateListBuku(ListBuku *L);
/* Tujuan  : Membuat list buku kosong */
/* IS      : L sembarang */
/* FS      : Terbentuk list buku kosong (First = NULL) */

void DeleteListBuku(ListBuku *L);
/* Tujuan  : Menghapus semua elemen dalam list buku */
/* IS      : L mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list buku dihapus dan didealokasi */

// Konstruktor untuk ListPeminjaman
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
/* Mengembalikan TRUE jika list buku kosong, FALSE jika tidak */

boolean isEmptyPeminjaman(ListPeminjaman L);
/* Tujuan  : Mengecek apakah list peminjaman kosong */
/* Mengembalikan TRUE jika list peminjaman kosong, FALSE jika tidak */

// =====================================================
// ================== OPERASI DASAR ====================
// =====================================================
addressBuku CreateBuku(const char *judulBuku);
/* Tujuan  : Membuat node baru dengan data judul buku */
/* IS      : Judul buku terdefinisi */
/* FS      : Mengembalikan address node baru, atau NULL jika gagal */

addressPeminjaman CreatePeminjaman(const char *judulBuku, const char *namaPeminjam, int skalaPrioritas);
/* Tujuan  : Membuat node baru peminjaman */
/* IS      : Data peminjaman terdefinisi */
/* FS      : Mengembalikan address node baru, atau NULL jika gagal */

void InsertFirstBuku(ListBuku *L, addressBuku P);
/* Tujuan  : Menambahkan elemen P sebagai elemen pertama dalam daftar buku */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen pertama dalam list buku */

void InsertFirstPeminjaman(ListPeminjaman *L, addressPeminjaman P);
/* Tujuan  : Menambahkan elemen P sebagai elemen pertama dalam daftar peminjaman */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen pertama dalam list peminjaman */

void InsertLastBuku(ListBuku *L, addressBuku P);
/* Tujuan  : Menambahkan elemen P sebagai elemen terakhir dalam daftar buku */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen terakhir dalam list buku */

void InsertLastPeminjaman(ListPeminjaman *L, addressPeminjaman P);
/* Tujuan  : Menambahkan elemen P sebagai elemen terakhir dalam daftar peminjaman */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen terakhir dalam list peminjaman */

void InsertAfterBuku(addressBuku pBef, addressBuku PNew);
/* Tujuan  : Menyisipkan elemen PNew setelah elemen pBef dalam daftar buku */
/* IS      : pBef tidak NULL */
/* FS      : PNew menjadi elemen setelah pBef dalam daftar buku */

void DeleteFirstBuku(ListBuku *L);
/* Tujuan  : Menghapus elemen pertama dari daftar buku */
/* IS      : List tidak kosong */
/* FS      : Elemen pertama dalam daftar buku dihapus dan didealokasi */

void DeleteFirstPeminjaman(ListPeminjaman *L);
/* Tujuan  : Menghapus elemen pertama dari daftar peminjaman */
/* IS      : List tidak kosong */
/* FS      : Elemen pertama dalam daftar peminjaman dihapus dan didealokasi */

void DeleteLastBuku(ListBuku *L);
/* Tujuan  : Menghapus elemen terakhir dari daftar buku */
/* IS      : List tidak kosong */
/* FS      : Elemen terakhir dalam daftar buku dihapus dan didealokasi */

void DeleteAfterBuku(addressBuku pBef);
/* Tujuan  : Menghapus elemen setelah pBef dalam daftar buku */
/* IS      : pBef tidak NULL dan memiliki elemen setelahnya */
/* FS      : Elemen setelah pBef dalam daftar buku dihapus dan didealokasi */

void DeAlokasiBuku(addressBuku *P);
/* Tujuan  : Mengembalikan memori dari suatu node buku ke sistem */
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

addressBuku SearchBuku(ListBuku L, const char *judulBuku);
/* Tujuan  : Mencari buku berdasarkan judul dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan address buku jika ditemukan, NULL jika tidak */

addressPeminjaman SearchPeminjaman(ListPeminjaman L, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Mencari peminjaman berdasarkan judul buku dan nama peminjam */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan address peminjaman jika ditemukan, NULL jika tidak */

void PrintBuku(ListBuku L);
/* Tujuan  : Menampilkan semua elemen dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list buku ditampilkan ke layar */

void PrintPeminjaman(ListPeminjaman L);
/* Tujuan  : Menampilkan semua elemen dalam list peminjaman */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list peminjaman ditampilkan ke layar */

ListBuku BalikListBuku(ListBuku L);
/* Tujuan  : Membalik urutan elemen dalam list buku */
/* IS      : List buku mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan list buku dengan urutan terbalik */

#endif

