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
#include <string.h>
#include "halaman.h"

// Deklarasi extern untuk mengakses global variable dari implementasi.c
extern ListRiwayat globalRiwayat;
extern ListPeminjaman globalPeminjaman;

/* *** Fungsi untuk membersihkan layar *** */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* *** Fungsi Tampilan Awal *** */
void welcomeScreen() {
    clearScreen();
    puts("*************************************************************");
    puts("*                  SELAMAT DATANG DI SISTEM                 *");
    puts("*               MONITORING DAN MANAJEMEN PERPUSTAKAAN       *");
    puts("*************************************************************");
    puts("\nTekan Enter untuk melanjutkan...");
    getchar();
}

/* *** Fungsi Menu Utama *** */
void dashboard(ListBuku *listBuku) {
    int choice;
    do {
        clearScreen();
        Implementasi_Tampilkan_Semua_Buku(listBuku);
        printf("\n\n");
        puts("************************** MENU UTAMA **************************");
        puts("1. Tambah Data");
        puts("2. Edit Data");
        puts("3. Hapus Data");
        puts("4. Proses Peminjaman");
        puts("5. Pengembalian Buku");
        puts("6. Tampilkan Data");
        puts("7. Riwayat");
        puts("8. Keluar");
        printf("Pilihan: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                tambahData(listBuku);
                break;
            case 2:
                editData(listBuku);
                break;
            case 3:
                hapusData(listBuku);
                break;
            case 4:
                prosesPeminjaman(listBuku);
                break;
            case 5:
                pengembalianBuku(listBuku);
                break;
            case 6:
                tampilkanData(listBuku);
                break;
            case 7:
                riwayatDanUndo(listBuku);
                break;
            case 8:
                puts("Terima kasih telah menggunakan program ini!");
                break;
            default:
                puts("Pilihan tidak valid! Silakan coba lagi.");
                break;
        }
    } while (choice != 8);
}

/* *** Fungsi Tambah Data *** */
void tambahData(ListBuku *listBuku) {
    clearScreen();
    puts("************************** TAMBAH DATA **************************");
    puts("1. Tambah Buku");
    puts("2. Tambah Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        // Input dan validasi data buku baru
        char judulBuku[100];
        int stokBuku;
        printf("Masukkan judul buku: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
        
        // Validasi stok buku
        char stokInput[20];
        int valid = 0;
        while (!valid) {
            printf("Masukkan jumlah stok buku: ");
            fgets(stokInput, sizeof(stokInput), stdin);
            stokInput[strcspn(stokInput, "\n")] = 0;  // Menghapus karakter newline
            
            // Validasi input stok: harus berupa angka positif
            int i, isValid = 1;
            for (i = 0; stokInput[i] != '\0'; i++) {
                if (stokInput[i] < '0' || stokInput[i] > '9') {
                    isValid = 0;
                    break;
                }
            }
            
            if (!isValid || strlen(stokInput) == 0) {
                printf("Error: Stok buku harus berupa angka positif!\n");
                continue;
            }
            
            stokBuku = atoi(stokInput);
            if (stokBuku <= 0) {
                printf("Error: Stok buku harus lebih dari 0!\n");
                continue;
            }
            
            valid = 1;
        }
        
        // Tambahkan buku ke dalam list
        Implementasi_Tambah_Buku(listBuku, judulBuku, stokBuku);
    } else if (choice == 2) {
        // Input dan validasi data peminjam baru
        char judulBuku[100], namaPeminjam[100];
        int skalaPrioritas;
        
        printf("Masukkan judul buku: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
        
        printf("Masukkan nama peminjam: ");
        fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
        namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;  // Menghapus karakter newline
        
        // Validasi skala prioritas
        int valid = 0;
        while (!valid) {
            printf("Masukkan skala prioritas peminjam (1: Dosen, 2: Mahasiswa, 3: Masyarakat Umum): ");
            char prioritasInput[10];
            fgets(prioritasInput, sizeof(prioritasInput), stdin);
            prioritasInput[strcspn(prioritasInput, "\n")] = 0;  // Menghapus karakter newline
            
            // Validasi: harus berupa angka
            int i, isValid = 1;
            for (i = 0; prioritasInput[i] != '\0'; i++) {
                if (prioritasInput[i] < '0' || prioritasInput[i] > '9') {
                    isValid = 0;
                    break;
                }
            }
            
            if (!isValid || strlen(prioritasInput) == 0) {
                printf("Error: Skala prioritas harus berupa angka!\n");
                continue;
            }
            
            skalaPrioritas = atoi(prioritasInput);
            if (skalaPrioritas < 1 || skalaPrioritas > 3) {
                printf("Error: Skala prioritas harus 1, 2, atau 3!\n");
                continue;
            }
            
            valid = 1;
        }
        
        // Cek ketersediaan buku
        addressBuku buku = SearchBuku(*listBuku, judulBuku);
        if (buku == NULL) {
            printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        } else if (buku->stokBuku <= 0) {
            printf("Stok buku '%s' habis. Tidak dapat ditambahkan ke daftar peminjaman.\n", judulBuku);
        } else {
            // Tambahkan peminjam ke antrian buku
            Implementasi_Tambah_Peminjam(listBuku, judulBuku, namaPeminjam, skalaPrioritas);
        }
    } else {
        printf("Pilihan tidak valid!\n");
    }
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Edit Data *** */
void editData(ListBuku *listBuku) {
    clearScreen();
    puts("************************** EDIT DATA **************************");
    puts("1. Edit Nama Buku");
    puts("2. Edit Nama Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        char judulBukuLama[100], judulBukuBaru[100];
        int stokBukuBaru;
        printf("Masukkan judul buku yang akan diedit: ");
        fgets(judulBukuLama, sizeof(judulBukuLama), stdin);
        judulBukuLama[strcspn(judulBukuLama, "\n")] = 0;  // Remove trailing newline
        printf("Masukkan judul buku baru: ");
        fgets(judulBukuBaru, sizeof(judulBukuBaru), stdin);
        judulBukuBaru[strcspn(judulBukuBaru, "\n")] = 0;  // Remove trailing newline
        printf("Masukkan stok buku baru: ");
        scanf("%d", &stokBukuBaru);
        Implementasi_Edit_Buku(listBuku, judulBukuLama, judulBukuBaru, stokBukuBaru);
    } else if (choice == 2) {
        char judulBuku[100], namaPeminjamLama[100], namaPeminjamBaru[100];
        printf("Masukkan judul buku tempat peminjam berada: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        printf("Masukkan nama peminjam yang akan diedit: ");
        fgets(namaPeminjamLama, sizeof(namaPeminjamLama), stdin);
        namaPeminjamLama[strcspn(namaPeminjamLama, "\n")] = 0;  // Remove trailing newline
        printf("Masukkan nama peminjam baru: ");
        fgets(namaPeminjamBaru, sizeof(namaPeminjamBaru), stdin);
        namaPeminjamBaru[strcspn(namaPeminjamBaru, "\n")] = 0;  // Remove trailing newline
        Implementasi_Edit_Peminjam(listBuku, judulBuku, namaPeminjamLama, namaPeminjamBaru);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Hapus Data *** */
void hapusData(ListBuku *listBuku) {
    clearScreen();
    puts("************************** HAPUS DATA **************************");
    puts("1. Hapus Buku");
    puts("2. Hapus Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        char judulBuku[100];
        printf("Masukkan judul buku yang akan dihapus: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        Implementasi_Hapus_Buku(listBuku, judulBuku);
    } else if (choice == 2) {
        char judulBuku[100], namaPeminjam[100];
        printf("Masukkan judul buku tempat peminjam berada: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        printf("Masukkan nama peminjam yang akan dihapus: ");
        fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
        namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;  // Remove trailing newline
        Implementasi_Hapus_Peminjam(listBuku, judulBuku, namaPeminjam);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Tampilkan Data *** */
void tampilkanData(ListBuku *listBuku) {
    clearScreen();
    puts("************************** TAMPILKAN DATA **************************");
    puts("1. Tampilkan Semua Data Buku");
    puts("2. Tampilkan Data Buku Tertentu");
    puts("3. Statistik Data");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        Implementasi_Tampilkan_Semua_Buku(listBuku);
    } else if (choice == 2) {
        char judulBuku[100];
        printf("Masukkan judul buku yang ingin ditampilkan: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        Implementasi_Tampilkan_Buku(listBuku, judulBuku);
    } else if (choice == 3) {
        printf("\nStatistik Data:\n");
        printf("Jumlah Buku: %d\n", Implementasi_Hitung_Total_Buku(listBuku));
        printf("Total Peminjam di Semua Buku: %d\n", Implementasi_Hitung_Total_Peminjam(listBuku));
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Pengembalian Buku *** */
void pengembalianBuku(ListBuku *listBuku) {
    clearScreen();
    puts("************************** PENGEMBALIAN BUKU **************************");
    
    // Tampilkan daftar peminjaman aktif
    Implementasi_Tampilkan_Peminjaman();
    
    // Cek apakah ada peminjaman aktif
    if (isEmptyPeminjaman(globalPeminjaman)) {
        printf("\nTidak ada peminjaman aktif yang perlu dikembalikan.\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Input data pengembalian
    char judulBuku[100], namaPeminjam[100];
    printf("\nMasukkan judul buku yang akan dikembalikan: ");
    fgets(judulBuku, sizeof(judulBuku), stdin);
    judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
    
    printf("Masukkan nama peminjam yang mengembalikan buku: ");
    fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
    namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;  // Menghapus karakter newline
    
    // Proses pengembalian buku
    Implementasi_Pengembalian_Buku(listBuku, judulBuku, namaPeminjam);
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Riwayat *** */
void riwayatDanUndo(ListBuku *listBuku) {
    clearScreen();
    puts("************************** RIWAYAT AKTIVITAS **************************");
    
    // Tampilkan riwayat aktivitas
    TampilkanRiwayat(&globalRiwayat);
    
    printf("\nTekan Enter untuk kembali ke Menu Utama...");
    getchar();
}

/* *** Fungsi Pemrosesan Peminjaman *** */
void prosesPeminjaman(ListBuku *listBuku) {
    clearScreen();
    puts("************************** PROSES PEMINJAMAN **************************");
    
    // Validasi daftar buku
    if (isEmptyBuku(*listBuku)) {
        printf("Daftar buku kosong.\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Tampilkan semua buku
    Implementasi_Tampilkan_Semua_Buku(listBuku);
    
    // Tampilkan opsi pemrosesan
    printf("\nOpsi pemrosesan peminjaman:\n");
    printf("1. Proses peminjam teratas dari antrian buku tertentu\n");
    printf("2. Proses semua peminjam teratas dari semua buku\n");
    printf("3. Kembali ke menu utama\n");
    printf("Pilihan: ");
    
    // Input pilihan pengguna
    int pilihan;
    if (scanf("%d", &pilihan) != 1) {
        // Handle input yang bukan angka
        printf("Input tidak valid! Harap masukkan angka.\n");
        // Bersihkan buffer stdin
        while (getchar() != '\n');
        printf("Tekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    getchar(); // Bersihkan buffer setelah scanf
    
    switch (pilihan) {
        case 1: // Proses peminjam teratas dari buku tertentu
            {
                // Input judul buku
                char judulBuku[100];
                printf("\nMasukkan judul buku yang akan diproses: ");
                fgets(judulBuku, sizeof(judulBuku), stdin);
                judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
                
                // Validasi input - cek jika input kosong
                if (strlen(judulBuku) == 0) {
                    printf("Judul buku tidak boleh kosong!\n");
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Cari buku
                addressBuku buku = SearchBuku(*listBuku, judulBuku);
                if (buku == NULL) {
                    printf("Buku '%s' tidak ditemukan.\n", judulBuku);
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Tampilkan daftar peminjam buku tersebut
                printf("\nDaftar Peminjam Buku %s:\n", judulBuku);
                if (isEmptyQueue(buku->antrianPeminjam)) {
                    printf("Tidak ada peminjam untuk buku ini.\n");
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                TampilQueue(buku->antrianPeminjam);
                
                // Periksa stok buku
                if (buku->stokBuku <= 0) {
                    printf("\nMaaf, stok buku '%s' habis. Tidak dapat memproses peminjaman.\n", judulBuku);
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Ambil peminjam teratas dari antrian berdasarkan prioritas
                addressPeminjam topBorrower = buku->antrianPeminjam.front;
                if (topBorrower == NULL) {
                    printf("Terjadi kesalahan: peminjam teratas tidak ditemukan.\n");
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Konfirmasi peminjaman
                printf("\nPeminjam teratas dalam antrian: %s (Prioritas: %d)\n", 
                       topBorrower->namaPeminjam, topBorrower->skalaPrioritas);
                printf("Apakah Anda ingin memproses peminjaman ini? (1: Ya, 0: Tidak): ");
                
                int konfirmasi;
                if (scanf("%d", &konfirmasi) != 1) {
                    // Handle input yang bukan angka
                    printf("Input tidak valid! Harap masukkan angka.\n");
                    // Bersihkan buffer stdin
                    while (getchar() != '\n');
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                getchar(); // Bersihkan buffer setelah scanf
                
                // Proses peminjaman jika dikonfirmasi
                if (konfirmasi == 1) {
                    boolean berhasil = Implementasi_Proses_Peminjaman(listBuku, judulBuku, topBorrower->namaPeminjam);
                    
                    if (berhasil) {
                        // Hapus peminjam dari antrian setelah proses peminjaman berhasil
                        Dequeue(&buku->antrianPeminjam, topBorrower->namaPeminjam);
                        printf("Peminjam '%s' berhasil dihapus dari antrian.\n", topBorrower->namaPeminjam);
                    } else {
                        printf("Terjadi kesalahan saat memproses peminjaman.\n");
                    }
                } else {
                    printf("Pemrosesan peminjaman dibatalkan.\n");
                }
            }
            break;
            
        case 2: // Proses semua peminjam teratas dari semua buku
            {
                // Validasi daftar buku
                if (isEmptyBuku(*listBuku)) {
                    printf("Daftar buku kosong.\n");
                    break;
                }
                
                // Inisialisasi counter statistik
                int berhasilCount = 0;
                int gagalCount = 0;
                int stokHabisCount = 0;
                addressBuku bukuCurrent = listBuku->First;
                
                // Iterasi semua buku
                while (bukuCurrent != NULL) {
                    // Proses hanya jika ada antrian peminjam dan stok tersedia
                    if (!isEmptyQueue(bukuCurrent->antrianPeminjam)) {
                        if (bukuCurrent->stokBuku <= 0) {
                            printf("\nBuku '%s' tidak dapat diproses karena stok habis.\n", 
                                   bukuCurrent->judulBuku);
                            stokHabisCount++;
                        } else {
                            addressPeminjam topBorrower = bukuCurrent->antrianPeminjam.front;
                            
                            printf("\nMemproses: Buku '%s', Peminjam '%s'...\n", 
                                   bukuCurrent->judulBuku, topBorrower->namaPeminjam);
                                   
                            // Proses peminjaman untuk peminjam teratas
                            boolean berhasil = Implementasi_Proses_Peminjaman(
                                listBuku, bukuCurrent->judulBuku, topBorrower->namaPeminjam);
                                
                            if (berhasil) {
                                // Hapus peminjam dari antrian jika berhasil
                                Dequeue(&bukuCurrent->antrianPeminjam, topBorrower->namaPeminjam);
                                berhasilCount++;
                            } else {
                                gagalCount++;
                            }
                        }
                    }
                    bukuCurrent = bukuCurrent->next;
                }
                
                // Tampilkan ringkasan proses
                printf("\nRingkasan proses batch:\n");
                printf("- Berhasil diproses: %d peminjaman\n", berhasilCount);
                printf("- Gagal diproses: %d peminjaman\n", gagalCount);
                printf("- Tidak dapat diproses karena stok habis: %d buku\n", stokHabisCount);
                
                if (berhasilCount == 0 && gagalCount == 0 && stokHabisCount == 0) {
                    printf("Tidak ada peminjaman yang dapat diproses. Pastikan ada peminjam dalam antrian dan stok buku tersedia.\n");
                }
            }
            break;
            
        case 3: // Kembali ke menu utama
            return;
            
        default:
            printf("Pilihan tidak valid! Silakan coba lagi.\n");
            break;
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

