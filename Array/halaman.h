/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef HALAMAN_H
#define HALAMAN_H

#include "implementasi.h"
#include "array.h"

/* *** PROTOTYPE *** */

/* *** Fungsi Tampilan Awal *** */
void welcomeScreen();
/* Tujuan  : Menampilkan layar selamat datang */
/* IS      : Layar kosong atau berisi tampilan sebelumnya */
/* FS      : Menampilkan pesan selamat datang dan menunggu input pengguna */

/* *** Fungsi Menu Utama *** */
void dashboard(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu utama */
/* IS      : Program berjalan */
/* FS      : Pengguna dapat memilih opsi yang tersedia dalam menu utama */

/* *** Fungsi Tambah Data *** */
void tambahData(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu tambah data */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat memilih untuk menambah buku atau menambah peminjam */

/* *** Fungsi Edit Data *** */
void editData(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu edit data */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat mengedit judul buku, stok, atau peminjam */

/* *** Fungsi Hapus Data *** */
void hapusData(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu hapus data */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat memilih untuk menghapus buku atau peminjam */

/* *** Fungsi Pengembalian Buku *** */
void pengembalianBuku(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu pengembalian buku */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat mengembalikan buku yang telah dipinjam */

/* *** Fungsi Pemrosesan Peminjaman *** */
void prosesPeminjaman(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu pemrosesan peminjaman buku */
/* IS      : Array mungkin kosong atau berisi beberapa buku dengan peminjam */
/* FS      : Pengguna dapat memproses peminjaman buku dari peminjam dalam antrian */

/* *** Fungsi Tampilkan Data *** */
void tampilkanData(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu tampilkan data */
/* IS      : Array mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat memilih untuk melihat semua data atau data buku tertentu */

/* *** Fungsi Riwayat *** */
void riwayatDanUndo(ArrayBuku *arrayBuku);
/* Tujuan  : Menampilkan menu riwayat aktivitas */
/* IS      : Array mungkin kosong atau berisi beberapa aktivitas riwayat */
/* FS      : Pengguna dapat melihat riwayat aktivitas */

#endif

