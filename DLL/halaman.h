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

/* *** PROTOTYPE *** */

/* *** Fungsi Tampilan Awal *** */
void welcomeScreen();
/* Tujuan  : Menampilkan layar selamat datang */
/* IS      : Layar kosong atau berisi tampilan sebelumnya */
/* FS      : Menampilkan pesan selamat datang dan menunggu input pengguna */

/* *** Fungsi Menu Utama *** */
void dashboard(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu utama */
/* IS      : Program berjalan */
/* FS      : Pengguna dapat memilih opsi yang tersedia dalam menu utama */

/* *** Fungsi Tambah Data *** */
void tambahData(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu tambah data */
/* IS      : List mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat memilih untuk menambah buku atau menambah peminjam */

/* *** Fungsi Edit Data *** */
void editData(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu edit data */
/* IS      : List mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat mengedit nama buku atau peminjam */

/* *** Fungsi Hapus Data *** */
void hapusData(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu hapus data */
/* IS      : List mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat memilih untuk menghapus buku atau peminjam */

/* *** Fungsi Pengembalian Buku *** */
void pengembalianBuku(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu pengembalian buku */
/* IS      : List mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat mengembalikan buku yang telah dipinjam */

/* *** Fungsi Pemrosesan Peminjaman *** */
void prosesPeminjaman(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu pemrosesan peminjaman buku */
/* IS      : List mungkin kosong atau berisi beberapa buku dengan peminjam */
/* FS      : Pengguna dapat memproses peminjaman buku dari peminjam dalam antrian */

/* *** Fungsi Tampilkan Data *** */
void tampilkanData(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu tampilkan data */
/* IS      : List mungkin kosong atau berisi beberapa buku */
/* FS      : Pengguna dapat memilih untuk melihat semua data atau data buku tertentu */

/* *** Fungsi Riwayat *** */
void riwayatDanUndo(ListBuku *listBuku);
/* Tujuan  : Menampilkan menu riwayat aktivitas */
/* IS      : List mungkin kosong atau berisi beberapa aktivitas riwayat */
/* FS      : Pengguna dapat melihat riwayat aktivitas */

#endif

