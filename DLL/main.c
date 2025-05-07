/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include <stdio.h>
#include <stdlib.h>
#include "implementasi.h"
#include "halaman.h"

// Deklarasi variabel global
extern ListRiwayat globalRiwayat;
extern ListPeminjaman globalPeminjaman;

int main() {
    // Inisialisasi daftar buku
    ListBuku listBuku;
    CreateListBuku(&listBuku);
    
    // Inisialisasi daftar riwayat
    CreateRiwayat(&globalRiwayat);
    
    // Inisialisasi daftar peminjaman
    CreateListPeminjaman(&globalPeminjaman);
    
    // Tampilkan layar selamat datang
    welcomeScreen();
    
    // Mulai dashboard program utama
    dashboard(&listBuku);
    
    // Pembersihan memori sebelum keluar
    DeleteListBuku(&listBuku);
    DeleteListPeminjaman(&globalPeminjaman);
    
    return 0;
}

