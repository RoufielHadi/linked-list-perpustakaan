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

#include "linked.h"
#include "implementasi.h"

// =====================================================
// ===================== TAMPILAN ======================
// =====================================================

void welcomeScreen();
/* Tujuan  : Menampilkan layar selamat datang */
/* IS      : Layar kosong atau berisi tampilan sebelumnya */
/* FS      : Menampilkan pesan selamat datang dan menunggu input pengguna */

// =====================================================
// ===================== MENU UTAMA ====================
// =====================================================

void dashboard(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu utama program */
/* IS      : Program berjalan */
/* FS      : Pengguna dapat memilih opsi yang tersedia dalam menu utama */

// =====================================================
// ================= OPERASI DATA BUKU =================
// =====================================================

void tambahData(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu untuk menambah data */
/* IS      : List mungkin kosong atau berisi beberapa data */
/* FS      : Pengguna dapat memilih untuk menambah buku atau peminjam */

void editData(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu untuk mengedit data */
/* IS      : List mungkin kosong atau berisi beberapa data */
/* FS      : Pengguna dapat mengedit informasi buku atau peminjam */

void hapusData(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu untuk menghapus data */
/* IS      : List mungkin kosong atau berisi beberapa data */
/* FS      : Pengguna dapat memilih untuk menghapus buku atau peminjam */

// =====================================================
// ============= OPERASI PEMINJAMAN BUKU ===============
// =====================================================

void pengembalianBuku(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu pengembalian buku */
/* IS      : List mungkin kosong atau berisi beberapa data */
/* FS      : Pengguna dapat mengembalikan buku yang telah dipinjam */

void prosesPeminjaman(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu pemrosesan peminjaman buku */
/* IS      : List mungkin kosong atau berisi beberapa data */
/* FS      : Pengguna dapat memproses peminjaman buku dari antrian peminjam */

// =====================================================
// ================= TAMPILAN DATA =====================
// =====================================================

void tampilkanData(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu untuk melihat data */
/* IS      : List mungkin kosong atau berisi beberapa data */
/* FS      : Pengguna dapat memilih untuk melihat semua data atau data tertentu */

// =====================================================
// ================= OPERASI RIWAYAT ===================
// =====================================================

void riwayatDanUndo(ListBuku *listBuku, ListPeminjam *listPeminjam);
/* Tujuan  : Menampilkan menu riwayat aktivitas */
/* IS      : List mungkin kosong atau berisi beberapa aktivitas */
/* FS      : Pengguna dapat melihat riwayat aktivitas dan melakukan undo */

#endif

