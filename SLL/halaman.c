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
void dashboard(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    int choice;
    do {
        clearScreen();
        Implementasi_Tampilkan_Semua_Buku(listBuku, listPeminjam);
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
                tambahData(listBuku, listPeminjam);
                break;
            case 2:
                editData(listBuku, listPeminjam);
                break;
            case 3:
                hapusData(listBuku, listPeminjam);
                break;
            case 4:
                prosesPeminjaman(listBuku, listPeminjam);
                break;
            case 5:
                pengembalianBuku(listBuku, listPeminjam);
                break;
            case 6:
                tampilkanData(listBuku, listPeminjam);
                break;
            case 7:
                riwayatDanUndo(listBuku, listPeminjam);
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
void tambahData(ListBuku *listBuku, ListPeminjam *listPeminjam) {
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
        addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
        if (bukuNode == NULL) {
            printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        } else if (bukuNode->stok <= 0) {
            printf("Stok buku '%s' habis. Peminjam akan masuk antrian peminjaman.\n", judulBuku);
            Implementasi_Tambah_Peminjam(listBuku, listPeminjam, judulBuku, namaPeminjam, skalaPrioritas);
        } else {
            // Tambahkan peminjam ke list buku
            Implementasi_Tambah_Peminjam(listBuku, listPeminjam, judulBuku, namaPeminjam, skalaPrioritas);
        }
    } else {
        printf("Pilihan tidak valid!\n");
    }
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Edit Data *** */
void editData(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    clearScreen();
    puts("************************** EDIT DATA **************************");
    puts("1. Edit Buku");
    puts("2. Edit Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        // Input data buku yang akan diedit
        char judulBukuLama[100], judulBukuBaru[100];
        int stokBukuBaru;
        
        printf("Masukkan judul buku yang akan diedit: ");
        fgets(judulBukuLama, sizeof(judulBukuLama), stdin);
        judulBukuLama[strcspn(judulBukuLama, "\n")] = 0;
        
        printf("Masukkan judul buku baru: ");
        fgets(judulBukuBaru, sizeof(judulBukuBaru), stdin);
        judulBukuBaru[strcspn(judulBukuBaru, "\n")] = 0;
        
        printf("Masukkan stok buku baru: ");
        scanf("%d", &stokBukuBaru);
        getchar();
        
        Implementasi_Edit_Buku(listBuku, listPeminjam, judulBukuLama, judulBukuBaru, stokBukuBaru);
    } else if (choice == 2) {
        // Input data peminjam yang akan diedit
        char namaPeminjamLama[100], namaPeminjamBaru[100];
        
        printf("Masukkan nama peminjam yang akan diedit: ");
        fgets(namaPeminjamLama, sizeof(namaPeminjamLama), stdin);
        namaPeminjamLama[strcspn(namaPeminjamLama, "\n")] = 0;
        
        printf("Masukkan nama peminjam baru: ");
        fgets(namaPeminjamBaru, sizeof(namaPeminjamBaru), stdin);
        namaPeminjamBaru[strcspn(namaPeminjamBaru, "\n")] = 0;
        
        Implementasi_Edit_Peminjam(listPeminjam, namaPeminjamLama, namaPeminjamBaru);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Hapus Data *** */
void hapusData(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    clearScreen();
    puts("************************** HAPUS DATA **************************");
    puts("1. Hapus Buku");
    puts("2. Hapus Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        // Input data buku yang akan dihapus
        char judulBuku[100];
        
        printf("Masukkan judul buku yang akan dihapus: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;
        
        Implementasi_Hapus_Buku(listBuku, listPeminjam, judulBuku);
    } else if (choice == 2) {
        // Input data peminjam yang akan dihapus
        char namaPeminjam[100];
        
        printf("Masukkan nama peminjam yang akan dihapus: ");
        fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
        namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;
        
        Implementasi_Hapus_Peminjam(listPeminjam, namaPeminjam);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Tampilkan Data *** */
void tampilkanData(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    clearScreen();
    puts("************************** TAMPILKAN DATA **************************");
    puts("1. Tampilkan Semua Data");
    puts("2. Tampilkan Data Buku Tertentu");
    puts("3. Tampilkan Data Peminjaman Aktif");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        // Tampilkan semua data
        clearScreen();
        puts("*** SEMUA DATA BUKU DAN PEMINJAM ***\n");
        Implementasi_Tampilkan_Semua_Buku(listBuku, listPeminjam);
        printf("\nJumlah Buku: %d\n", Implementasi_Hitung_Total_Buku(listBuku));
        printf("Total Peminjam di Semua Buku: %d\n", Implementasi_Hitung_Total_Peminjam(listPeminjam));
    } else if (choice == 2) {
        // Tampilkan data buku tertentu
        char judulBuku[100];
        printf("Masukkan judul buku: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
        
        clearScreen();
        puts("*** DATA BUKU YANG DIPILIH ***\n");
        Implementasi_Tampilkan_Buku(listBuku, listPeminjam, judulBuku);
    } else if (choice == 3) {
        // Tampilkan data peminjaman aktif
        clearScreen();
        puts("*** DATA PEMINJAMAN AKTIF ***\n");
        Implementasi_Tampilkan_Peminjaman();
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Pengembalian Buku *** */
void pengembalianBuku(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    clearScreen();
    puts("************************** PENGEMBALIAN BUKU **************************");
    
    // Tampilkan peminjaman aktif
    Implementasi_Tampilkan_Peminjaman();
    
    if (isEmptyPeminjaman(globalPeminjaman)) {
        printf("\nTidak ada peminjaman aktif yang dapat dikembalikan.\n");
    } else {
        char judulBuku[100], namaPeminjam[100];
        
        printf("\nMasukkan judul buku yang akan dikembalikan: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
        
        printf("Masukkan nama peminjam: ");
        fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
        namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;  // Menghapus karakter newline
        
        Implementasi_Pengembalian_Buku(listBuku, listPeminjam, judulBuku, namaPeminjam);
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Riwayat dan Undo *** */
void riwayatDanUndo(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    clearScreen();
    puts("************************** RIWAYAT AKTIVITAS **************************");
    
    TampilkanRiwayat(&globalRiwayat);
    
    printf("\nApakah Anda ingin melakukan undo aktivitas terakhir? (y/n): ");
    char choice;
    scanf("%c", &choice);
    getchar();
    
    if (choice == 'y' || choice == 'Y') {
        boolean undoStatus = UndoAktivitas(&globalRiwayat, listBuku, listPeminjam);
        if (undoStatus) {
            printf("\nRiwayat berhasil diundo. Gunakan menu yang sesuai untuk melihat status terbaru.\n");
        } else {
            printf("\nTidak ada aktivitas yang dapat di-undo.\n");
        }
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Pemrosesan Peminjaman *** */
void prosesPeminjaman(ListBuku *listBuku, ListPeminjam *listPeminjam) {
    clearScreen();
    puts("************************** PROSES PEMINJAMAN **************************");
    
    if (isEmptyBuku(*listBuku)) {
        printf("Daftar buku kosong.\n");
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    printf("List Buku dan Peminjam:\n");
    Implementasi_Tampilkan_Semua_Buku(listBuku, listPeminjam);
    
    char judulBuku[100];
    
    printf("\nMasukkan judul buku untuk memproses peminjaman: ");
    fgets(judulBuku, sizeof(judulBuku), stdin);
    judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
    
    // Find the book
    addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Check if book has stock
    if (bukuNode->stok <= 0) {
        printf("Stok buku '%s' habis. Tidak dapat memproses peminjaman.\n", judulBuku);
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Display borrowers for this book
    int countPeminjam = 0;
    addressPeminjam firstBorrowerForBook = NULL;
    
    addressPeminjam currentPeminjam = listPeminjam->First;
    while (currentPeminjam != NULL) {
        if (currentPeminjam->bukuDipinjam == bukuNode) {
            countPeminjam++;
            
            // Get priority text
            char priorityText[20];
            switch (currentPeminjam->skalaPrioritas) {
                case 1:
                    strcpy(priorityText, "Dosen");
                    break;
                case 2:
                    strcpy(priorityText, "Mahasiswa");
                    break;
                case 3:
                    strcpy(priorityText, "Masyarakat Umum");
                    break;
                default:
                    strcpy(priorityText, "Tidak Diketahui");
            }
            
            printf("%d. Peminjam: \"%s\" (Prioritas: %s)\n", 
                   countPeminjam, currentPeminjam->namaPeminjam, priorityText);
            
            // Remember the first borrower we encounter for this book
            // (which will be the highest priority one, since the list is now sorted by priority)
            if (firstBorrowerForBook == NULL) {
                firstBorrowerForBook = currentPeminjam;
            }
        }
        currentPeminjam = currentPeminjam->next;
    }
    
    if (countPeminjam == 0) {
        printf("Tidak ada peminjam dalam antrian untuk buku '%s'.\n", judulBuku);
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Get priority text for the first borrower (highest priority)
    char priorityText[20];
    switch (firstBorrowerForBook->skalaPrioritas) {
        case 1:
            strcpy(priorityText, "Dosen");
            break;
        case 2:
            strcpy(priorityText, "Mahasiswa");
            break;
        case 3:
            strcpy(priorityText, "Masyarakat Umum");
            break;
        default:
            strcpy(priorityText, "Tidak Diketahui");
    }
    
    printf("\nBerdasarkan prioritas, peminjam '%s' (%s) dapat meminjam buku '%s'.\n", 
           firstBorrowerForBook->namaPeminjam, priorityText, judulBuku);
    printf("Proses peminjaman? (y/n): ");
    char choice;
    scanf("%c", &choice);
    getchar();
    
    if (choice == 'y' || choice == 'Y') {
        boolean berhasil = Implementasi_Proses_Peminjaman(listBuku, listPeminjam, judulBuku, firstBorrowerForBook->namaPeminjam);
        if (!berhasil) {
            printf("Peminjaman gagal diproses.\n");
        }
    } else {
        printf("Peminjaman dibatalkan.\n");
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

