/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"
#define MAX 100

// Struktur untuk Linked List Non Restricted Fitur List Peminjam
typedef struct peminjam *addressPeminjam;
typedef struct peminjam {
    char namaPeminjam[MAX];
    int skalaPrioritas; // 1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum
    addressPeminjam next;
} daftarPeminjam;

typedef struct {
    addressPeminjam front;
    addressPeminjam rear;
} ListPeminjam;

/* *** Konstruktor & Destructor *** */
boolean isEmptyQueue(ListPeminjam Q);
/* Tujuan  : Memeriksa apakah queue kosong */
/* Queue kosong jika front == NULL */

void CreateQueue(ListPeminjam *Q);
/* Tujuan  : Membuat queue kosong */
/* IS      : Q belum terdefinisi */
/* FS      : Q terdefinisi dengan front dan rear = NULL */

void DeAlokasiQueue(addressPeminjam *p);
/* Tujuan  : Menghapus node queue dari memori (dealokasi) */
/* IS      : p terdefinisi */
/* FS      : p dikembalikan ke sistem (dealokasi) */

void DeleteListPeminjam(ListPeminjam *Q);
/* Tujuan  : Menghapus semua elemen dalam queue peminjam */
/* IS      : Q mungkin kosong atau berisi elemen */
/* FS      : Semua elemen dalam Q dihapus dan Q menjadi kosong */

/* *** Operasi Enqueue (Menambahkan Elemen) *** */
void Enqueue(ListPeminjam *Q, const char *nama, int skalaPrioritas);
/* Tujuan  : Menambahkan elemen baru ke belakang queue dengan prioritas */
/* IS      : Queue mungkin kosong */
/* FS      : Elemen baru ditambahkan di belakang queue sesuai prioritas */

/* *** Operasi Dequeue (Menghapus Elemen) *** */
void Dequeue(ListPeminjam *Q, const char *namaPeminjam);
/* Tujuan  : Menghapus peminjam dengan nama tertentu dari queue */
/* IS      : Queue mungkin kosong atau berisi beberapa peminjam */
/* FS      : Peminjam dengan nama yang sesuai dihapus dari queue jika ditemukan */

/* *** Operasi Tambahan *** */
int NbElmtQueue(ListPeminjam Q);
/* Tujuan  : Mengembalikan jumlah elemen dalam queue */
/* Jika queue kosong, mengembalikan 0 */

void TampilQueue(ListPeminjam Q);
/* Tujuan  : Menampilkan isi queue dari depan ke belakang */
/* Format  : "elemen1 -> elemen2 -> ... -> NULL" */

char *Front(ListPeminjam Q);
/* Tujuan  : Mengembalikan nilai elemen terdepan tanpa menghapusnya */
/* IS      : Queue tidak kosong */
/* FS      : Mengembalikan nilai front->namaPeminjam */

char *Rear(ListPeminjam Q);
/* Tujuan  : Mengembalikan nilai elemen terakhir dalam queue tanpa menghapusnya */
/* IS      : Queue tidak kosong */
/* FS      : Mengembalikan nilai rear->namaPeminjam */

void EnqueueDosen(ListPeminjam *Q, const char *nama);
/* Tujuan  : Menambahkan elemen Dosen (prioritas pertama) ke dalam queue */

void EnqueueMahasiswa(ListPeminjam *Q, const char *nama);
/* Tujuan  : Menambahkan elemen Mahasiswa (prioritas kedua) ke dalam queue */

void EnqueueMasyarakat(ListPeminjam *Q, const char *nama);
/* Tujuan  : Menambahkan elemen Masyarakat Umum (prioritas ketiga) ke dalam queue */

addressPeminjam SearchPeminjam(ListPeminjam Q, const char *namaPeminjam);
/* Tujuan  : Mencari peminjam berdasarkan nama dalam queue */
/* IS      : Queue mungkin kosong atau berisi beberapa peminjam */
/* FS      : Mengembalikan address peminjam jika ditemukan, NULL jika tidak */

#endif

