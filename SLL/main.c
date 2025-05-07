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
#include "linked.h"
#include "implementasi.h"
#include "halaman.h"

// =====================================================
// ===================== VARIABEL ======================
// =====================================================

// Variabel global untuk menyimpan daftar peminjaman
extern ListPeminjaman globalPeminjaman;

// =====================================================
// ===================== FUNGSI MAIN ===================
// =====================================================

int main() {
    // Inisialisasi struktur data
    ListBuku listBuku;
    CreateListBuku(&listBuku);
    
    ListPeminjam listPeminjam;
    CreateListPeminjam(&listPeminjam);
    
    CreateListPeminjaman(&globalPeminjaman);
    
    // Menampilkan tampilan awal program
    welcomeScreen();
    
    // Menjalankan menu utama program
    dashboard(&listBuku, &listPeminjam);
    
    // Membersihkan memori sebelum program berakhir
    DeleteListBuku(&listBuku);
    DeleteListPeminjam(&listPeminjam);
    DeleteListPeminjaman(&globalPeminjaman);
    
    return 0;
}

