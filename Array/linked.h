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

// Definisi struktur untuk queue
typedef struct peminjam *addressPeminjam;
typedef struct peminjam {
    char nama[100];
    int skalaPrioritas;   // 1: Dosen, 2: Mahasiswa, 3: Masyarakat Umum
    addressPeminjam next;
} Peminjam;

typedef struct {
    addressPeminjam First;
} Queue;

typedef Queue ListPeminjam;

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

// Prototype fungsi queue
void CreateQueue(Queue *Q);
boolean isEmptyQueue(Queue Q);
void Enqueue(Queue *Q, const char *nama, int skalaPrioritas);
void Dequeue(Queue *Q, const char *nama);
void TampilQueue(Queue Q);
addressPeminjam SearchPeminjam(Queue Q, const char *nama);
int NbElmtQueue(Queue Q);
void DeleteListPeminjam(Queue *Q);
void PrintQueue(Queue Q);
addressPeminjam CreatePeminjam(const char *namaPeminjam, int skalaPrioritas);
void DeAlokasiPeminjam(addressPeminjam *P);
void EnqueueWithPriority(Queue *Q, addressPeminjam P);
addressPeminjam DequeueFirst(Queue *Q);

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
boolean isEmptyPeminjaman(ListPeminjaman L);
/* Tujuan  : Mengecek apakah list peminjaman kosong */
/* Mengembalikan TRUE jika list peminjaman kosong, FALSE jika tidak */

// =====================================================
// ================== OPERASI DASAR ====================
// =====================================================
addressPeminjaman CreatePeminjaman(const char *judulBuku, const char *namaPeminjam, int skalaPrioritas);
/* Tujuan  : Membuat node baru peminjaman */
/* IS      : Data peminjaman terdefinisi */
/* FS      : Mengembalikan address node baru, atau NULL jika gagal */

void InsertFirstPeminjaman(ListPeminjaman *L, addressPeminjaman P);
/* Tujuan  : Menambahkan elemen P sebagai elemen pertama dalam daftar peminjaman */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen pertama dalam list peminjaman */

void InsertLastPeminjaman(ListPeminjaman *L, addressPeminjaman P);
/* Tujuan  : Menambahkan elemen P sebagai elemen terakhir dalam daftar peminjaman */
/* IS      : L mungkin kosong */
/* FS      : P menjadi elemen terakhir dalam list peminjaman */

void DeleteFirstPeminjaman(ListPeminjaman *L);
/* Tujuan  : Menghapus elemen pertama dari daftar peminjaman */
/* IS      : List tidak kosong */
/* FS      : Elemen pertama dalam daftar peminjaman dihapus dan didealokasi */

void DeAlokasiPeminjaman(addressPeminjaman *P);
/* Tujuan  : Mengembalikan memori dari suatu node peminjaman ke sistem */
/* IS      : P terdefinisi */
/* FS      : Memori yang ditempati oleh P dikembalikan ke sistem */

// =====================================================
// ================= OPERASI TAMBAHAN =================
// =====================================================
addressPeminjaman SearchPeminjaman(ListPeminjaman L, const char *judulBuku, const char *namaPeminjam);
/* Tujuan  : Mencari peminjaman berdasarkan judul buku dan nama peminjam */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Mengembalikan address peminjaman jika ditemukan, NULL jika tidak */

void PrintPeminjaman(ListPeminjaman L);
/* Tujuan  : Menampilkan semua elemen dalam list peminjaman */
/* IS      : List peminjaman mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam list peminjaman ditampilkan ke layar */

#endif
