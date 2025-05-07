/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boolean.h"
#include "linked.h"  // Ditambahkan agar `addressPeminjam` dikenali

#define MAX_BUKU 50  // Maksimal jumlah buku dalam array
#define MAXSIZE 100  // Ukuran maksimum array nama

/* *** Tipe Data *** */
typedef char nama[MAXSIZE];

typedef struct {
    nama judulBuku;  // Elemen dalam array untuk judul buku
    int stok;        // Variabel untuk menunjuk jumlah stok dalam buku
    addressPeminjam antrianPeminjam;  // Elemen dalam array untuk menunjuk antrian orang yang meminjam buku tersebut
} buku;

/* Mendefinisikan Tipe Data Array Buku */
typedef struct {
    buku data[MAX_BUKU]; // Array untuk menyimpan buku
    int jumlahBuku;      // Jumlah buku yang ada dalam array
} ArrayBuku;

/* *** PROTOTYPE *** */
void Inisialisasi_Array(ArrayBuku *arr);
/* Tujuan  : Menginisialisasi array agar siap digunakan */
/* IS      : Array belum terisi */
/* FS      : Array memiliki jumlahBuku = 0, siap digunakan */

void Tambah_Buku(ArrayBuku *arr, char *judulBuku, int stok, addressPeminjam antrianPeminjam);
/* Tujuan  : Menambahkan buku ke dalam array beserta stok dan antrian peminjamnya */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Buku baru ditambahkan ke dalam array jika belum penuh */

void Hapus_Buku(ArrayBuku *arr, int index);
/* Tujuan  : Menghapus buku dari array berdasarkan indeks */
/* IS      : Array tidak kosong */
/* FS      : Buku di indeks tertentu dihapus, elemen setelahnya digeser ke kiri */

void Cari_Buku(ArrayBuku *arr, char *judulBuku, int *index);
/* Tujuan  : Mencari buku dalam array berdasarkan judul */
/* IS      : Array tidak kosong */
/* FS      : Jika ditemukan, index diisi dengan posisi buku dalam array, jika tidak -1 */

void Tampilkan_Buku(ArrayBuku arr);
/* Tujuan  : Menampilkan daftar buku beserta stok dan antrian peminjamnya */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Seluruh data buku ditampilkan ke layar */

void Ubah_Judul_Buku(ArrayBuku *arr, int index, char *judulBaru);
/* Tujuan  : Mengubah judul buku yang ada dalam array */
/* IS      : Array tidak kosong, index valid */
/* FS      : Judul buku pada indeks tertentu diperbarui */

void Ubah_Stok_Buku(ArrayBuku *arr, int index, int stokBaru);
/* Tujuan  : Mengubah stok buku yang ada dalam array */
/* IS      : Array tidak kosong, index valid */
/* FS      : Stok buku pada indeks tertentu diperbarui */

void Urutkan_Buku(ArrayBuku *arr);
/* Tujuan  : Mengurutkan daftar buku berdasarkan abjad */
/* IS      : Array tidak kosong */
/* FS      : Buku dalam array tersusun secara alfabetis */

void Hapus_Semua_Buku(ArrayBuku *arr);
/* Tujuan  : Menghapus seluruh buku dari array */
/* IS      : Array berisi beberapa buku */
/* FS      : Array menjadi kosong dengan jumlahBuku = 0 */

#endif

