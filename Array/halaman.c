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
void dashboard(ArrayBuku *arrayBuku) {
    int choice;
    
    do {
        clearScreen();
        Implementasi_Tampilkan_Semua_Buku(arrayBuku);
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
                tambahData(arrayBuku);
                break;
            case 2:
                editData(arrayBuku);
                break;
            case 3:
                hapusData(arrayBuku);
                break;
            case 4:
                prosesPeminjaman(arrayBuku);
                break;
            case 5:
                pengembalianBuku(arrayBuku);
                break;
            case 6:
                tampilkanData(arrayBuku);
                break;
            case 7:
                riwayatDanUndo(arrayBuku);
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
void tambahData(ArrayBuku *arrayBuku) {
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
        
        // Tambahkan buku ke dalam array
        Implementasi_Tambah_Buku(arrayBuku, judulBuku, stokBuku);
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
        int index;
        Cari_Buku(arrayBuku, judulBuku, &index);
        if (index == -1) {
            printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        } else if (arrayBuku->data[index].stok <= 0) {
            printf("Stok buku '%s' habis. Tidak dapat ditambahkan ke daftar peminjaman.\n", judulBuku);
        } else {
            // Tambahkan peminjam ke antrian buku
            Implementasi_Tambah_Peminjam(arrayBuku, judulBuku, namaPeminjam, skalaPrioritas);
        }
    } else {
        printf("Pilihan tidak valid!\n");
    }
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Edit Data *** */
void editData(ArrayBuku *arrayBuku) {
    clearScreen();
    puts("************************** EDIT DATA **************************");
    puts("1. Edit Buku");
    puts("2. Edit Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        // Input dan validasi data buku
        char judulBuku[100], judulBukuBaru[100];
        int stokBukuBaru;
        
        printf("Masukkan judul buku yang akan diedit: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        
        printf("Masukkan judul buku baru: ");
        fgets(judulBukuBaru, sizeof(judulBukuBaru), stdin);
        judulBukuBaru[strcspn(judulBukuBaru, "\n")] = 0;  // Remove trailing newline
        
        printf("Masukkan stok buku baru: ");
        scanf("%d", &stokBukuBaru);
        getchar();  // Clear buffer
        
        Implementasi_Edit_Buku(arrayBuku, judulBuku, judulBukuBaru, stokBukuBaru);
    } else if (choice == 2) {
        // Input dan validasi data peminjam
        char judulBuku[100], namaPeminjamLama[100], namaPeminjamBaru[100];
        
        printf("Masukkan judul buku: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        
        printf("Masukkan nama peminjam lama: ");
        fgets(namaPeminjamLama, sizeof(namaPeminjamLama), stdin);
        namaPeminjamLama[strcspn(namaPeminjamLama, "\n")] = 0;  // Remove trailing newline
        
        printf("Masukkan nama peminjam baru: ");
        fgets(namaPeminjamBaru, sizeof(namaPeminjamBaru), stdin);
        namaPeminjamBaru[strcspn(namaPeminjamBaru, "\n")] = 0;  // Remove trailing newline
        Implementasi_Edit_Peminjam(arrayBuku, judulBuku, namaPeminjamLama, namaPeminjamBaru);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Hapus Data *** */
void hapusData(ArrayBuku *arrayBuku) {
    clearScreen();
    puts("************************** HAPUS DATA **************************");
    puts("1. Hapus Buku");
    puts("2. Hapus Peminjam");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        // Input dan validasi data buku
        char judulBuku[100];
        printf("Masukkan judul buku yang akan dihapus: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        
        Implementasi_Hapus_Buku(arrayBuku, judulBuku);
    } else if (choice == 2) {
        // Input dan validasi data peminjam
        char judulBuku[100], namaPeminjam[100];
        printf("Masukkan judul buku: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        
        printf("Masukkan nama peminjam yang akan dihapus: ");
        fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
        namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;  // Remove trailing newline
        
        Implementasi_Hapus_Peminjam(arrayBuku, judulBuku, namaPeminjam);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Tampilkan Data *** */
void tampilkanData(ArrayBuku *arrayBuku) {
    clearScreen();
    puts("************************** TAMPILKAN DATA **************************");
    puts("1. Tampilkan Semua Buku dan Peminjam");
    puts("2. Tampilkan Buku Tertentu");
    puts("3. Tampilkan Daftar Peminjaman Aktif");
    printf("Pilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        Implementasi_Tampilkan_Semua_Buku(arrayBuku);
        printf("\nJumlah Buku: %d\n", Implementasi_Hitung_Total_Buku(arrayBuku));
        printf("Total Peminjam di Semua Buku: %d\n", Implementasi_Hitung_Total_Peminjam(arrayBuku));
    } else if (choice == 2) {
        char judulBuku[100];
        printf("Masukkan judul buku: ");
        fgets(judulBuku, sizeof(judulBuku), stdin);
        judulBuku[strcspn(judulBuku, "\n")] = 0;  // Remove trailing newline
        
        Implementasi_Tampilkan_Buku(arrayBuku, judulBuku);
    } else if (choice == 3) {
        Implementasi_Tampilkan_Peminjaman();
    } else {
        printf("Pilihan tidak valid!\n");
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Pengembalian Buku *** */
void pengembalianBuku(ArrayBuku *arrayBuku) {
    clearScreen();
    puts("************************** PENGEMBALIAN BUKU **************************");
    
    // Validasi peminjaman
    if (isEmptyPeminjaman(globalPeminjaman)) {
        printf("Tidak ada peminjaman buku yang aktif.\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Tampilkan daftar peminjaman aktif
    printf("Daftar Peminjaman Aktif:\n");
    PrintPeminjaman(globalPeminjaman);
    
    // Input data pengembalian
    char judulBuku[100], namaPeminjam[100];
    printf("\nMasukkan judul buku yang akan dikembalikan: ");
    fgets(judulBuku, sizeof(judulBuku), stdin);
    judulBuku[strcspn(judulBuku, "\n")] = 0;  // Menghapus karakter newline
    
    printf("Masukkan nama peminjam yang mengembalikan buku: ");
    fgets(namaPeminjam, sizeof(namaPeminjam), stdin);
    namaPeminjam[strcspn(namaPeminjam, "\n")] = 0;  // Menghapus karakter newline
    
    // Proses pengembalian buku
    Implementasi_Pengembalian_Buku(arrayBuku, judulBuku, namaPeminjam);
    
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

/* *** Fungsi Riwayat *** */
void riwayatDanUndo(ArrayBuku *arrayBuku) {
    clearScreen();
    puts("************************** RIWAYAT AKTIVITAS **************************");
    
    // Tampilkan riwayat aktivitas
    TampilkanRiwayat(&globalRiwayat);
    
    // Tanya apakah ingin melakukan undo
    printf("\nApakah Anda ingin melakukan undo aktivitas terakhir? (1: Ya, 0: Tidak): ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        // Handle input yang bukan angka
        printf("Input tidak valid! Harap masukkan angka.\n");
        // Bersihkan buffer stdin
        while (getchar() != '\n');
    } else {
        getchar(); // Bersihkan buffer
        if (choice == 1) {
            // Lakukan undo
            if (UndoAktivitas(&globalRiwayat, arrayBuku)) {
                printf("Undo berhasil.\n");
            } else {
                printf("Tidak ada aktivitas yang dapat di-undo.\n");
            }
        }
    }
    
    printf("\nTekan Enter untuk kembali ke Menu Utama...");
    getchar();
}

/* *** Fungsi Pemrosesan Peminjaman *** */
void prosesPeminjaman(ArrayBuku *arrayBuku) {
    clearScreen();
    puts("************************** PROSES PEMINJAMAN **************************");
    
    // Validasi daftar buku
    if (arrayBuku->jumlahBuku == 0) {
        printf("Daftar buku kosong.\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Tampilkan semua buku
    Implementasi_Tampilkan_Semua_Buku(arrayBuku);
    
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
                int index;
                Cari_Buku(arrayBuku, judulBuku, &index);
                if (index == -1) {
                    printf("Buku '%s' tidak ditemukan.\n", judulBuku);
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Create a queue object from the array's queue pointer
                Queue antrianPeminjam = {arrayBuku->data[index].antrianPeminjam};
                
                // Tampilkan daftar peminjam buku tersebut
                printf("\nDaftar Peminjam Buku %s:\n", judulBuku);
                if (isEmptyQueue(antrianPeminjam)) {
                    printf("Tidak ada peminjam untuk buku ini.\n");
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                TampilQueue(antrianPeminjam);
                
                // Periksa stok buku
                if (arrayBuku->data[index].stok <= 0) {
                    printf("\nMaaf, stok buku '%s' habis. Tidak dapat memproses peminjaman.\n", judulBuku);
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Ambil peminjam teratas dari antrian berdasarkan prioritas
                addressPeminjam topBorrower = antrianPeminjam.First;
                if (topBorrower == NULL) {
                    printf("Terjadi kesalahan: peminjam teratas tidak ditemukan.\n");
                    printf("Tekan Enter untuk kembali ke menu...");
                    getchar();
                    return;
                }
                
                // Konfirmasi peminjaman
                printf("\nPeminjam teratas dalam antrian: %s (Prioritas: %d)\n", 
                       topBorrower->nama, topBorrower->skalaPrioritas);
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
                    boolean berhasil = Implementasi_Proses_Peminjaman(arrayBuku, judulBuku, topBorrower->nama);
                    
                    if (berhasil) {
                        // Hapus peminjam dari antrian setelah proses peminjaman berhasil
                        Dequeue(&antrianPeminjam, topBorrower->nama);
                        arrayBuku->data[index].antrianPeminjam = antrianPeminjam.First;
                        printf("Peminjam '%s' berhasil dihapus dari antrian.\n", topBorrower->nama);
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
                if (arrayBuku->jumlahBuku == 0) {
                    printf("Daftar buku kosong.\n");
                    break;
                }
                
                // Inisialisasi counter statistik
                int berhasilCount = 0;
                int gagalCount = 0;
                int stokHabisCount = 0;
                
                // Iterasi semua buku
                for (int i = 0; i < arrayBuku->jumlahBuku; i++) {
                    // Create a queue object from the array's queue pointer
                    Queue antrianPeminjam = {arrayBuku->data[i].antrianPeminjam};
                    
                    // Proses hanya jika ada antrian peminjam dan stok tersedia
                    if (!isEmptyQueue(antrianPeminjam)) {
                        if (arrayBuku->data[i].stok <= 0) {
                            printf("\nBuku '%s' tidak dapat diproses karena stok habis.\n", 
                                   arrayBuku->data[i].judulBuku);
                            stokHabisCount++;
                        } else {
                            addressPeminjam topBorrower = antrianPeminjam.First;
                            
                            printf("\nMemproses: Buku '%s', Peminjam '%s'...\n", 
                                   arrayBuku->data[i].judulBuku, topBorrower->nama);
                                   
                            // Proses peminjaman untuk peminjam teratas
                            boolean berhasil = Implementasi_Proses_Peminjaman(
                                arrayBuku, arrayBuku->data[i].judulBuku, topBorrower->nama);
                                
                            if (berhasil) {
                                // Hapus peminjam dari antrian jika berhasil
                                Dequeue(&antrianPeminjam, topBorrower->nama);
                                arrayBuku->data[i].antrianPeminjam = antrianPeminjam.First;
                                berhasilCount++;
                            } else {
                                gagalCount++;
                            }
                        }
                    }
                }
                
                // Tampilkan ringkasan proses
                printf("\n=========================\n");
                printf("Ringkasan Proses:\n");
                printf("- Peminjaman berhasil: %d\n", berhasilCount);
                printf("- Peminjaman gagal: %d\n", gagalCount);
                printf("- Buku dengan stok habis: %d\n", stokHabisCount);
            }
            break;
            
        case 3: // Kembali ke menu utama
            return;
            
        default:
            printf("Pilihan tidak valid!\n");
            break;
    }
    
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

