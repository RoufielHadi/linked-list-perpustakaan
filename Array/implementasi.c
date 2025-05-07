/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"

// Global variable untuk riwayat
ListRiwayat globalRiwayat;
// Global variable untuk peminjaman
ListPeminjaman globalPeminjaman;

// Fungsi Riwayat
void CreateRiwayat(ListRiwayat *L) {
    L->first = NULL;
    L->last = NULL;
    L->current = NULL;
}

void TambahRiwayat(ListRiwayat *L, TipeAktivitas tipe, const char *detail) {
    addressRiwayat P = (addressRiwayat)malloc(sizeof(Riwayat));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk riwayat.\n");
        return;
    }
    
    P->tipe = tipe;
    strcpy(P->detail, detail);
    P->waktu = time(NULL);
    P->next = NULL;
    
    // Jika ada aktivitas setelah posisi current, hapus semuanya
    if (L->current != NULL && L->current != L->last) {
        addressRiwayat temp = L->current->next;
        addressRiwayat toDelete;
        
        while (temp != NULL) {
            toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        
        L->current->next = NULL;
        L->last = L->current;
    }
    
    // Tambahkan riwayat baru
    if (L->first == NULL) {
        P->prev = NULL;
        L->first = P;
    } else {
        P->prev = L->last;
        L->last->next = P;
    }
    
    L->last = P;
    L->current = P;
}

void TampilkanRiwayat(const ListRiwayat *L) {
    addressRiwayat P = L->first;
    int count = 1;
    
    if (P == NULL) {
        printf("Belum ada riwayat aktivitas.\n");
        return;
    }
    
    printf("Daftar Riwayat Aktivitas:\n");
    printf("=========================\n");
    
    while (P != NULL) {
        struct tm *waktu_lokal = localtime(&P->waktu);
        char waktu_str[30];
        strftime(waktu_str, sizeof(waktu_str), "%d-%m-%Y %H:%M:%S", waktu_lokal);
        
        printf("%d. [%s] ", count++, waktu_str);
        
        switch (P->tipe) {
            case TAMBAH_BUKU:
                printf("Tambah Buku: %s\n", P->detail);
                break;
            case EDIT_BUKU:
                printf("Edit Buku: %s\n", P->detail);
                break;
            case HAPUS_BUKU:
                printf("Hapus Buku: %s\n", P->detail);
                break;
            case TAMBAH_PEMINJAM:
                printf("Tambah Peminjam: %s\n", P->detail);
                break;
            case HAPUS_PEMINJAM:
                printf("Hapus Peminjam: %s\n", P->detail);
                break;
            case EDIT_PEMINJAM:
                printf("Edit Peminjam: %s\n", P->detail);
                break;
            case PINJAM_BUKU:
                printf("Peminjaman Buku: %s\n", P->detail);
                break;
            case KEMBALI_BUKU:
                printf("Pengembalian Buku: %s\n", P->detail);
                break;
        }
        
        // Tandai posisi saat ini
        if (P == L->current) {
            printf("   << Posisi Saat Ini >>\n");
        }
        
        P = P->next;
    }
}

// Fungsi untuk mengekstrak informasi dari string detail
void parseDetail(const char *detail, char *part1, char *part2, int *number) {
    // Inisialisasi nilai default
    if (part1) strcpy(part1, "");
    if (part2) strcpy(part2, "");
    if (number) *number = 0;
    
    // Contoh format detail:
    // "Buku '%s' dihapus" (HAPUS_BUKU)
    // "%s meminjam buku '%s' (Peminjaman diproses, stok sekarang: %d)" (PINJAM_BUKU)
    // "Buku '%s' diubah menjadi '%s' (Stok: %d)" (EDIT_BUKU)
    
    char tempDetail[200];
    strcpy(tempDetail, detail);
    
    // Ekstrak bagian berdasarkan pola
    char *token = strtok(tempDetail, "'");
    if (token != NULL) {
        token = strtok(NULL, "'"); // Mendapatkan string pertama dalam tanda kutip
        if (token != NULL && part1) strcpy(part1, token);
        
        token = strtok(NULL, "'"); // Lompat ke tanda kutip berikutnya
        if (token != NULL) {
            token = strtok(NULL, "'"); // Mendapatkan string kedua dalam tanda kutip
            if (token != NULL && part2) strcpy(part2, token);
        }
    }
    
    // Ekstrak angka jika diperlukan
    if (number) {
        char *numStart = strstr(detail, "Stok sekarang: ");
        if (numStart == NULL) numStart = strstr(detail, "Stok: ");
        
        if (numStart != NULL) {
            numStart = strchr(numStart, ':') + 1;
            while (*numStart == ' ') numStart++;
            sscanf(numStart, "%d", number);
        }
    }
}

boolean UndoAktivitas(ListRiwayat *L, ArrayBuku *arrayBuku) {
    if (L->current == NULL || L->current == L->first) {
        printf("Tidak ada aktivitas yang dapat di-undo.\n");
        return 0;  // false
    }
    
    // Save current activity information
    TipeAktivitas aktivitasSaatIni = L->current->tipe;
    char detailSaatIni[200];
    strcpy(detailSaatIni, L->current->detail);
    
    // Move current to previous activity
    L->current = L->current->prev;
    
    // Undo action based on activity type
    printf("Undo berhasil: Kembali ke aktivitas '%s'\n", L->current->detail);
    
    // Try to perform undo operation
    LakukanUndoOperasi(arrayBuku, aktivitasSaatIni, detailSaatIni);
    
    return 1;  // true
}

void LakukanUndoOperasi(ArrayBuku *arrayBuku, TipeAktivitas tipe, const char *detail) {
    char part1[100] = ""; // Usually the first item (book title or borrower name)
    char part2[100] = ""; // Usually the second item (new title, etc.)
    int number = 0;      // Usually stok
    
    parseDetail(detail, part1, part2, &number);
    
    switch (tipe) {
        case TAMBAH_BUKU:
            // The undo of adding a book is removing it
            if (strlen(part1) > 0) {
                printf("Mencoba mengembalikan keadaan: Menghapus buku '%s'\n", part1);
                // Don't actually delete due to data loss risk
                printf("Untuk menghapus buku, silakan gunakan menu Hapus Data.\n");
            }
            break;
            
        case EDIT_BUKU:
            // The undo of editing would be to edit back to original
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Mengembalikan buku '%s' ke nama aslinya\n", part2);
                printf("Untuk mengedit buku kembali, silakan gunakan menu Edit Data.\n");
            }
            break;
            
        case HAPUS_BUKU:
            // The undo of deleting would be to add back
            if (strlen(part1) > 0) {
                printf("Mencoba mengembalikan keadaan: Menambahkan kembali buku '%s'\n", part1);
                printf("Untuk menambahkan buku kembali, silakan gunakan menu Tambah Data.\n");
            }
            break;
            
        case PINJAM_BUKU:
            // The undo of borrowing would be returning
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Mengembalikan buku '%s' dari peminjam '%s'\n", 
                       part2, part1);
                printf("Untuk mengembalikan buku, silakan gunakan menu Pengembalian Buku.\n");
            }
            break;
            
        case KEMBALI_BUKU:
            // The undo of returning would be borrowing again
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Peminjam '%s' meminjam kembali buku '%s'\n", 
                       part1, part2);
                printf("Untuk meminjam buku kembali, silakan gunakan menu Tambah Peminjam.\n");
            }
            break;
            
        default:
            printf("Operasi undo tidak didukung untuk aktivitas ini.\n");
            break;
    }
}

/* Fungsi Entry (Tambah Data) */
void Implementasi_Tambah_Buku(ArrayBuku *arrayBuku, const char *judulBuku, int stokBuku) {
    // Check if book already exists
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    
    if (index != -1) {
        printf("Buku %s sudah ada dalam daftar.\n", judulBuku);
        return;
    }
    
    // Add the new book
    Tambah_Buku(arrayBuku, (char *)judulBuku, stokBuku, NULL);  // NULL for empty queue
    
    // Add to history
    char detail[200];
    sprintf(detail, "%s (Stok: %d)", judulBuku, stokBuku);
    TambahRiwayat(&globalRiwayat, TAMBAH_BUKU, detail);
    
    printf("Buku %s berhasil ditambahkan dengan stok %d.\n", judulBuku, stokBuku);
}

void Implementasi_Tambah_Peminjam(ArrayBuku *arrayBuku, const char *judulBuku, const char *namaPeminjam, int skalaPrioritas) {
    // Find book
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Check if borrower already exists in the queue
    if (arrayBuku->data[index].antrianPeminjam != NULL) {
        addressPeminjam peminjam = SearchPeminjam((ListPeminjam){arrayBuku->data[index].antrianPeminjam}, namaPeminjam);
        if (peminjam != NULL) {
            printf("Peminjam %s sudah ada dalam antrian buku %s.\n", namaPeminjam, judulBuku);
            return;
        }
    }

    // Create queue if it doesn't exist
    if (arrayBuku->data[index].antrianPeminjam == NULL) {
        ListPeminjam queue;
        CreateQueue(&queue);
        arrayBuku->data[index].antrianPeminjam = queue.First;
    }

    // Add borrower to the book's queue
    ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
    Enqueue(&queue, namaPeminjam, skalaPrioritas);
    arrayBuku->data[index].antrianPeminjam = queue.First;
    
    // Add to history
    char detail[200];
    sprintf(detail, "%s masuk antrian buku '%s' dengan prioritas %d", namaPeminjam, judulBuku, skalaPrioritas);
    TambahRiwayat(&globalRiwayat, TAMBAH_PEMINJAM, detail);
    
    // Display message based on priority
    if (skalaPrioritas == 1) { // Dosen has highest priority
        printf("Peminjam %s (Dosen) berhasil ditambahkan ke antrian buku %s dengan prioritas tertinggi.\n", 
              namaPeminjam, judulBuku);
    } else if (skalaPrioritas == 2) { // Student has second priority
        printf("Peminjam %s (Mahasiswa) berhasil ditambahkan ke antrian buku %s dengan prioritas kedua.\n", 
              namaPeminjam, judulBuku);
    } else { // General public (3)
        printf("Peminjam %s (Masyarakat Umum) berhasil ditambahkan ke antrian buku %s dengan prioritas terendah.\n", 
              namaPeminjam, judulBuku);
    }
    
    printf("Peminjaman perlu diproses lebih lanjut melalui menu 'Proses Peminjaman'.\n");
}

/* Fungsi Delete (Hapus Data) */
void Implementasi_Hapus_Buku(ArrayBuku *arrayBuku, const char *judulBuku) {
    if (arrayBuku->jumlahBuku == 0) {
        printf("Daftar buku kosong.\n");
        return;
    }

    // Find the book
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Delete all borrowers in the queue
    if (arrayBuku->data[index].antrianPeminjam != NULL) {
        ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
        DeleteListPeminjam(&queue);
    }

    // Delete the book from array
    Hapus_Buku(arrayBuku, index);

    // Add to history
    char detail[200];
    sprintf(detail, "Buku '%s' dihapus", judulBuku);
    TambahRiwayat(&globalRiwayat, HAPUS_BUKU, detail);

    printf("Buku %s dan semua peminjamnya berhasil dihapus.\n", judulBuku);
}

void Implementasi_Hapus_Peminjam(ArrayBuku *arrayBuku, const char *judulBuku, const char *namaPeminjam) {
    // Find book
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Check if the borrower exists in the queue
    if (arrayBuku->data[index].antrianPeminjam == NULL) {
        printf("Tidak ada antrian peminjam untuk buku %s.\n", judulBuku);
        return;
    }
    
    ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
    
    // Find borrower to delete
    addressPeminjam peminjam = SearchPeminjam(queue, namaPeminjam);
    if (peminjam == NULL) {
        printf("Peminjam %s tidak ditemukan dalam antrian buku %s.\n", namaPeminjam, judulBuku);
        return;
    }

    // Remove borrower from queue
    Dequeue(&queue, namaPeminjam);
    arrayBuku->data[index].antrianPeminjam = queue.First;
    
    // Add to history
    char detail[200];
    sprintf(detail, "Peminjam '%s' dihapus dari buku '%s'", namaPeminjam, judulBuku);
    TambahRiwayat(&globalRiwayat, HAPUS_PEMINJAM, detail);
    
    printf("Peminjam %s berhasil dihapus dari antrian buku %s.\n", namaPeminjam, judulBuku);
}

/* Fungsi Tampilkan Data */
void Implementasi_Tampilkan_Semua_Buku(const ArrayBuku *arrayBuku) {
    if (arrayBuku->jumlahBuku == 0) {
        printf("Daftar buku kosong.\n");
        return;
    }

    for (int i = 0; i < arrayBuku->jumlahBuku; i++) {
        printf("\nBuku: %s\n", arrayBuku->data[i].judulBuku);
        printf("Stok Buku: %d\n", arrayBuku->data[i].stok);
        
        // Display borrowers queue
        ListPeminjam queue = {arrayBuku->data[i].antrianPeminjam};
        printf("Jumlah Peminjam: %d\n", NbElmtQueue(queue));
        printf("Daftar Peminjam:\n");

        if (isEmptyQueue(queue)) {
            printf("- Tidak ada peminjam\n");
        } else {
            TampilQueue(queue);
        }
    }
}

void Implementasi_Tampilkan_Buku(const ArrayBuku *arrayBuku, const char *judulBuku) {
    // Find book
    int index;
    Cari_Buku((ArrayBuku*)arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    printf("\nBuku: %s\n", arrayBuku->data[index].judulBuku);
    printf("Stok Buku: %d\n", arrayBuku->data[index].stok);
    
    // Display borrowers queue
    ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
    printf("Jumlah Peminjam: %d\n", NbElmtQueue(queue));

    if (isEmptyQueue(queue)) {
        printf("- Tidak ada peminjam\n");
    } else {
        TampilQueue(queue);
    }
}

/* Fungsi Tambahan */
int Implementasi_Hitung_Peminjam_Buku(const ArrayBuku *arrayBuku, const char *judulBuku) {
    // Find book
    int index;
    Cari_Buku((ArrayBuku*)arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return 0;
    }
    
    // Count borrowers in queue
    ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
    return NbElmtQueue(queue);
}

int Implementasi_Hitung_Total_Buku(const ArrayBuku *arrayBuku) {
    return arrayBuku->jumlahBuku;
}

int Implementasi_Hitung_Total_Peminjam(const ArrayBuku *arrayBuku) {
    int total = 0;
    
    for (int i = 0; i < arrayBuku->jumlahBuku; i++) {
        ListPeminjam queue = {arrayBuku->data[i].antrianPeminjam};
        total += NbElmtQueue(queue);
    }

    return total;
}

/* Fungsi Edit Data */
void Implementasi_Edit_Buku(ArrayBuku *arrayBuku, const char *judulBukuLama, const char *judulBukuBaru, int stokBukuBaru) {
    if (arrayBuku->jumlahBuku == 0) {
        printf("Daftar buku kosong.\n");
        return;
    }

    // Find the book to edit
    int indexLama;
    Cari_Buku(arrayBuku, (char *)judulBukuLama, &indexLama);
    if (indexLama == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBukuLama);
        return;
    }

    // Check if new title already exists
    if (strcmp(judulBukuLama, judulBukuBaru) != 0) {
        int indexBaru;
        Cari_Buku(arrayBuku, (char *)judulBukuBaru, &indexBaru);
        if (indexBaru != -1) {
            printf("Buku %s sudah ada dalam daftar.\n", judulBukuBaru);
            return;
        }
    }

    // Edit book title and stock
    Ubah_Judul_Buku(arrayBuku, indexLama, (char *)judulBukuBaru);
    Ubah_Stok_Buku(arrayBuku, indexLama, stokBukuBaru);
    
    // Add to history
    char detail[200];
    sprintf(detail, "Buku '%s' diubah menjadi '%s' (Stok: %d)", judulBukuLama, judulBukuBaru, stokBukuBaru);
    TambahRiwayat(&globalRiwayat, EDIT_BUKU, detail);
    
    printf("Nama buku berhasil diubah dari %s menjadi %s dan stok buku diubah menjadi %d.\n", 
           judulBukuLama, judulBukuBaru, stokBukuBaru);
}

void Implementasi_Edit_Peminjam(ArrayBuku *arrayBuku, const char *judulBuku, const char *namaPeminjamLama, const char *namaPeminjamBaru) {
    // Find book
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Check if queue exists
    if (arrayBuku->data[index].antrianPeminjam == NULL) {
        printf("Tidak ada antrian peminjam untuk buku %s.\n", judulBuku);
        return;
    }
    
    // Access the queue
    ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
    
    // Find borrower to edit
    addressPeminjam peminjam = SearchPeminjam(queue, namaPeminjamLama);
    if (peminjam == NULL) {
        printf("Peminjam %s tidak ditemukan di antrian buku %s.\n", namaPeminjamLama, judulBuku);
        return;
    }

    // Check if new name is already used
    if (strcmp(namaPeminjamLama, namaPeminjamBaru) != 0 && 
        SearchPeminjam(queue, namaPeminjamBaru) != NULL) {
        printf("Peminjam %s sudah ada di antrian buku %s.\n", namaPeminjamBaru, judulBuku);
        return;
    }

    // Update borrower name
    strcpy(peminjam->nama, namaPeminjamBaru);
    
    // Add to history
    char detail[200];
    sprintf(detail, "Peminjam '%s' diubah menjadi '%s' pada buku '%s'", namaPeminjamLama, namaPeminjamBaru, judulBuku);
    TambahRiwayat(&globalRiwayat, EDIT_PEMINJAM, detail);
    
    printf("Nama peminjam berhasil diubah dari %s menjadi %s di antrian buku %s.\n", 
           namaPeminjamLama, namaPeminjamBaru, judulBuku);
}

void Implementasi_Tampilkan_Peminjaman() {
    PrintPeminjaman(globalPeminjaman);
}

boolean Implementasi_Proses_Peminjaman(ArrayBuku *arrayBuku, const char *judulBuku, const char *namaPeminjam) {
    // Validate parameters to prevent NULL pointer
    if (arrayBuku == NULL || judulBuku == NULL || namaPeminjam == NULL) {
        printf("Error: Parameter tidak valid dalam fungsi pemrosesan peminjaman.\n");
        return 0; // false
    }
    
    // Validate empty strings
    if (strlen(judulBuku) == 0 || strlen(namaPeminjam) == 0) {
        printf("Error: Judul buku atau nama peminjam tidak boleh kosong.\n");
        return 0; // false
    }

    // Find book
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    if (index == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return 0; // false
    }

    // Check if borrower exists in the queue
    ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
    addressPeminjam peminjam = SearchPeminjam(queue, namaPeminjam);
    if (peminjam == NULL) {
        printf("Peminjam '%s' tidak ditemukan dalam antrian buku '%s'.\n", namaPeminjam, judulBuku);
        return 0; // false
    }

    // Check book stock
    if (arrayBuku->data[index].stok <= 0) {
        printf("Stok buku '%s' habis, tidak dapat memproses peminjaman.\n", judulBuku);
        return 0; // false
    }

    // Decrease book stock
    arrayBuku->data[index].stok--;
    
    // Add borrower to active borrowing list
    addressPeminjaman newPeminjaman = CreatePeminjaman(judulBuku, namaPeminjam, peminjam->skalaPrioritas);
    if (newPeminjaman == NULL) {
        printf("Gagal membuat data peminjaman.\n");
        arrayBuku->data[index].stok++; // Restore stock if failed
        return 0; // false
    }
    
    // Add to borrowing list
    InsertLastPeminjaman(&globalPeminjaman, newPeminjaman);
    
    // Add to history
    char detail[200];
    sprintf(detail, "%s meminjam buku '%s' (Peminjaman diproses, stok sekarang: %d)", 
            namaPeminjam, judulBuku, arrayBuku->data[index].stok);
    TambahRiwayat(&globalRiwayat, PINJAM_BUKU, detail);
    
    printf("Peminjaman buku '%s' oleh '%s' berhasil diproses. Stok buku sekarang: %d\n", 
           judulBuku, namaPeminjam, arrayBuku->data[index].stok);
           
    return 1; // true
}

void Implementasi_Pengembalian_Buku(ArrayBuku *arrayBuku, const char *judulBuku, const char *namaPeminjam) {
    // Find book
    int index;
    Cari_Buku(arrayBuku, (char *)judulBuku, &index);
    
    if (index == -1) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Find borrowing in active borrowing list
    addressPeminjaman peminjaman = SearchPeminjaman(globalPeminjaman, judulBuku, namaPeminjam);
    if (peminjaman == NULL) {
        // If not found in active borrowing list, also check the queue
        if (arrayBuku->data[index].antrianPeminjam != NULL) {
            ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
            addressPeminjam peminjam = SearchPeminjam(queue, namaPeminjam);
            if (peminjam != NULL) {
                printf("Peminjam %s belum meminjam buku %s, masih dalam antrian peminjaman.\n", namaPeminjam, judulBuku);
            } else {
                printf("Peminjam %s tidak ditemukan dalam daftar peminjaman buku %s.\n", namaPeminjam, judulBuku);
            }
        } else {
            printf("Peminjam %s tidak ditemukan dalam daftar peminjaman buku %s.\n", namaPeminjam, judulBuku);
        }
        return;
    }

    // Remove from active borrowing list
    // Since there's no DeletePeminjaman that searches by title and name, we have to iterate manually
    if (globalPeminjaman.First != NULL) {
        if (strcmp(globalPeminjaman.First->judulBuku, judulBuku) == 0 && 
            strcmp(globalPeminjaman.First->namaPeminjam, namaPeminjam) == 0) {
            // Borrowing is at first position
            DeleteFirstPeminjaman(&globalPeminjaman);
        } else {
            // Find borrowing position
            addressPeminjaman prev = globalPeminjaman.First;
            addressPeminjaman curr = prev->next;
            boolean found = 0; // false
            
            while (curr != NULL && !found) {
                if (strcmp(curr->judulBuku, judulBuku) == 0 && 
                    strcmp(curr->namaPeminjam, namaPeminjam) == 0) {
                    found = 1; // true
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
            
            if (found) {
                // Delete borrowing node
                prev->next = curr->next;
                free(curr);
            }
        }
    }
    
    // Increase book stock
    arrayBuku->data[index].stok++;
    
    // Add to history
    char detail[200];
    sprintf(detail, "%s mengembalikan buku '%s' (Stok sekarang: %d)", 
            namaPeminjam, judulBuku, arrayBuku->data[index].stok);
    TambahRiwayat(&globalRiwayat, KEMBALI_BUKU, detail);
    
    printf("Buku %s telah dikembalikan oleh %s. Stok buku sekarang: %d\n", 
           judulBuku, namaPeminjam, arrayBuku->data[index].stok);

    // Check if there's a next borrower in the queue who can be processed
    if (arrayBuku->data[index].antrianPeminjam != NULL) {
        // Borrower with highest priority is at front because it was already sorted when Enqueue
        ListPeminjam queue = {arrayBuku->data[index].antrianPeminjam};
        addressPeminjam nextBorrower = queue.First;
        
        if (nextBorrower != NULL) {
            printf("Peminjam %s dengan prioritas %d akan mendapatkan buku %s selanjutnya.\n", 
                   nextBorrower->nama, nextBorrower->skalaPrioritas, judulBuku);
            
            printf("Memproses peminjaman secara otomatis...\n");
            
            // Decrease book stock
            arrayBuku->data[index].stok--;
            
            // Add to borrowing list
            addressPeminjaman newPeminjaman = CreatePeminjaman(judulBuku, nextBorrower->nama, nextBorrower->skalaPrioritas);
            if (newPeminjaman != NULL) {
                InsertLastPeminjaman(&globalPeminjaman, newPeminjaman);
            }
            
            // Remove from queue
            Dequeue(&queue, nextBorrower->nama);
            arrayBuku->data[index].antrianPeminjam = queue.First;
            
            // Add to history of automatic borrowing process from queue
            char detailPinjam[200];
            sprintf(detailPinjam, "%s meminjam buku '%s' (dari antrian, stok sekarang: %d)", 
                    nextBorrower->nama, judulBuku, arrayBuku->data[index].stok);
            TambahRiwayat(&globalRiwayat, PINJAM_BUKU, detailPinjam);
            
            printf("Peminjaman untuk %s berhasil diproses. Stok buku sekarang: %d\n", 
                   nextBorrower->nama, arrayBuku->data[index].stok);
        }
    }
}

