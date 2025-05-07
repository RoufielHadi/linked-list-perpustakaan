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

// Find a borrower for a specific book
addressPeminjam SearchPeminjamForBuku(ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam) {
    if (listPeminjam == NULL || isEmptyPeminjam(*listPeminjam)) {
        return NULL; // Invalid or empty list
    }
    
    addressPeminjam peminjamNode = listPeminjam->First;
    
    // Search through all borrower nodes
    while (peminjamNode != NULL) {
        if (peminjamNode->bukuDipinjam != NULL && 
            strcmp(peminjamNode->bukuDipinjam->judulBuku, judulBuku) == 0 && 
            strcmp(peminjamNode->namaPeminjam, namaPeminjam) == 0) {
            return peminjamNode;
        }
        peminjamNode = peminjamNode->next;
    }
    
    return NULL; // Borrower not found
}

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

void LakukanUndoOperasi(ListBuku *listBuku, ListPeminjam *listPeminjam, TipeAktivitas tipe, const char *detail) {
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
            // The undo of editing is reverting to the original name/stock
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Mengedit buku '%s' kembali ke '%s' (Stok: %d)\n", 
                       part2, part1, number);
                // Attempt to edit back, but don't force it
                addressBuku bukuNode = SearchBuku(*listBuku, part2);
                if (bukuNode != NULL) {
                    strcpy(bukuNode->judulBuku, part1);
                    bukuNode->stok = number;
                    printf("Buku '%s' berhasil diubah kembali menjadi '%s' (Stok: %d).\n", 
                           part2, part1, number);
                } else {
                    printf("Buku '%s' tidak ditemukan, tidak dapat diubah kembali.\n", part2);
                }
            }
            break;
            
        case HAPUS_BUKU:
            // The undo of deletion is recreating the book
            if (strlen(part1) > 0) {
                printf("Mencoba mengembalikan keadaan: Menambahkan kembali buku '%s'\n", part1);
                // Assume default stock of 1 unless specified
                int newStock = (number > 0) ? number : 1;
                Implementasi_Tambah_Buku(listBuku, part1, newStock);
            }
            break;
            
        case TAMBAH_PEMINJAM:
            // The undo of adding a borrower is removing them
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Menghapus peminjam '%s' dari buku '%s'\n", 
                       part2, part1);
                // Don't actually delete
                printf("Untuk menghapus peminjam, silakan gunakan menu Hapus Data.\n");
            }
            break;
            
        case EDIT_PEMINJAM:
            // The undo of editing a borrower is reverting to the original name
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Mengedit peminjam '%s' kembali ke '%s'\n", 
                       part2, part1);
                // Find borrower and edit name back
                addressPeminjam peminjamNode = SearchPeminjam(*listPeminjam, part2);
                if (peminjamNode != NULL) {
                    strcpy(peminjamNode->namaPeminjam, part1);
                    printf("Peminjam '%s' berhasil diubah kembali menjadi '%s'.\n", part2, part1);
                } else {
                    printf("Peminjam '%s' tidak ditemukan, tidak dapat diubah kembali.\n", part2);
                }
            }
            break;
            
        case HAPUS_PEMINJAM:
            // The undo of deleting a borrower is recreating them
            // Format: "Peminjam '%s' dihapus dari antrian buku '%s'"
            if (strlen(part1) > 0 && strlen(part2) > 0) {
                printf("Mencoba mengembalikan keadaan: Menambahkan kembali peminjam '%s' ke buku '%s'\n", 
                       part1, part2);
                // Try to add borrower back with default priority
                Implementasi_Tambah_Peminjam(listBuku, listPeminjam, part2, part1, 2); // Default priority: Mahasiswa
            }
            break;
            
        // Handling for PINJAM_BUKU and KEMBALI_BUKU would be more complex
        // Potentially requiring database/storage of more state information
        default:
            printf("Operasi undo untuk tipe aktivitas ini belum diimplementasikan.\n");
            break;
    }
}

boolean UndoAktivitas(ListRiwayat *L, ListBuku *listBuku, ListPeminjam *listPeminjam) {
    if (L->current == NULL || L->first == NULL) {
        printf("Tidak ada aktivitas yang dapat di-undo.\n");
        return false;
    }
    
    // If we're at the first activity, cannot undo further
    if (L->current == L->first) {
        printf("Sudah di aktivitas pertama, tidak dapat undo lebih lanjut.\n");
        return false;
    }
    
    // Get previous activity
    addressRiwayat prevActivity = L->current->prev;
    if (prevActivity == NULL) {
        printf("Riwayat rusak, tidak dapat menemukan aktivitas sebelumnya.\n");
        return false;
    }
    
    // Move current pointer to previous activity
    L->current = prevActivity;
    
    // Try to perform undo operation based on the activity just undone
    printf("Mencoba melakukan undo aktivitas: ");
    
    switch (L->current->next->tipe) {
        case TAMBAH_BUKU:
            printf("Penambahan Buku\n");
            break;
        case EDIT_BUKU:
            printf("Pengeditan Buku\n");
            break;
        case HAPUS_BUKU:
            printf("Penghapusan Buku\n");
            break;
        case TAMBAH_PEMINJAM:
            printf("Penambahan Peminjam\n");
            break;
        case HAPUS_PEMINJAM:
            printf("Penghapusan Peminjam\n");
            break;
        case EDIT_PEMINJAM:
            printf("Pengeditan Peminjam\n");
            break;
        case PINJAM_BUKU:
            printf("Peminjaman Buku\n");
            break;
        case KEMBALI_BUKU:
            printf("Pengembalian Buku\n");
            break;
    }
    
    // Perform specific undo operation
    LakukanUndoOperasi(listBuku, listPeminjam, L->current->next->tipe, L->current->next->detail);
    
    return true;
}

/* Fungsi Entry (Tambah Data) */
void Implementasi_Tambah_Buku(ListBuku *listBuku, const char *judulBuku, int stokBuku) {
    // Check if the book already exists
    addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
    if (bukuNode != NULL) {
        // Book exists, update stock
        bukuNode->stok += stokBuku;
        printf("Stok buku '%s' ditambah sebanyak %d, stok sekarang: %d\n", 
               judulBuku, stokBuku, bukuNode->stok);
               
        // Record in history
        char detail[200];
        sprintf(detail, "Menambah stok buku '%s' sebanyak %d (Stok sekarang: %d)", 
                judulBuku, stokBuku, bukuNode->stok);
        TambahRiwayat(&globalRiwayat, TAMBAH_BUKU, detail);
    } else {
        // Create new book
        addressBuku newBook = CreateNodeBuku(judulBuku, stokBuku);
        if (newBook == NULL) {
            printf("Gagal menambahkan buku '%s'.\n", judulBuku);
            return;
        }
        
        // Add to list
        InsertLastBuku(listBuku, newBook);
        printf("Buku '%s' berhasil ditambahkan dengan stok %d.\n", judulBuku, stokBuku);
        
        // Record in history
        char detail[200];
        sprintf(detail, "Buku '%s' ditambahkan (Stok: %d)", judulBuku, stokBuku);
        TambahRiwayat(&globalRiwayat, TAMBAH_BUKU, detail);
    }
}

void Implementasi_Tambah_Peminjam(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam, int skalaPrioritas) {
    // Find the book
    addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }
    
    // Check if book has available stock
    if (bukuNode->stok <= 0) {
        printf("Stok buku '%s' habis. Peminjam akan masuk antrian peminjaman.\n", judulBuku);
    }
    
    // Check if borrower already exists in queue for this book
    addressPeminjam existing = NULL;
    addressPeminjam currentPeminjam = listPeminjam->First;
    while (currentPeminjam != NULL) {
        if (currentPeminjam->bukuDipinjam == bukuNode && 
            strcmp(currentPeminjam->namaPeminjam, namaPeminjam) == 0) {
            existing = currentPeminjam;
            break;
        }
        currentPeminjam = currentPeminjam->next;
    }
    
    if (existing != NULL) {
        printf("Peminjam '%s' sudah ada di antrian buku '%s'.\n", namaPeminjam, judulBuku);
        return;
    }
    
    // Add new borrower
    addressPeminjam newBorrower = CreateNodePeminjam(namaPeminjam, skalaPrioritas, bukuNode);
    if (newBorrower == NULL) {
        printf("Gagal menambahkan peminjam '%s'.\n", namaPeminjam);
        return;
    }
    
    // Add to list
    InsertLastPeminjam(listPeminjam, newBorrower);
    
    // Get priority text
    char priorityText[20];
    switch (skalaPrioritas) {
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
    
    printf("Peminjam '%s' (%s) berhasil ditambahkan ke antrian buku '%s'.\n", 
           namaPeminjam, priorityText, judulBuku);
    
    // If book has stock, process the loan immediately
    if (bukuNode->stok > 0) {
        printf("Stok buku '%s' tersedia. Peminjaman dapat diproses.\n", judulBuku);
        printf("Untuk memproses peminjaman, gunakan menu Proses Peminjaman.\n");
    }
    
    // Record in history
    char detail[200];
    sprintf(detail, "Peminjam '%s' (%s) ditambahkan ke antrian buku '%s'", 
            namaPeminjam, priorityText, judulBuku);
    TambahRiwayat(&globalRiwayat, TAMBAH_PEMINJAM, detail);
}

/* Fungsi Delete (Hapus Data) */
void Implementasi_Hapus_Buku(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku) {
    // Find the book
    addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }
    
    // First, remove all borrowers for this book
    addressPeminjam currentPeminjam = listPeminjam->First;
    addressPeminjam prevPeminjam = NULL;
    addressPeminjam nextPeminjam;
    
    while (currentPeminjam != NULL) {
        nextPeminjam = currentPeminjam->next;
        
        if (currentPeminjam->bukuDipinjam == bukuNode) {
            // Remove this borrower
            if (prevPeminjam == NULL) {
                // It's the first node
                listPeminjam->First = nextPeminjam;
                if (listPeminjam->Tail == currentPeminjam) {
                    listPeminjam->Tail = NULL;
                }
            } else {
                prevPeminjam->next = nextPeminjam;
                if (listPeminjam->Tail == currentPeminjam) {
                    listPeminjam->Tail = prevPeminjam;
                }
            }
            
            // Free the node
            free(currentPeminjam);
            currentPeminjam = nextPeminjam;
            continue;
        }
        
        prevPeminjam = currentPeminjam;
        currentPeminjam = nextPeminjam;
    }
    
    // Now remove the book itself
    if (bukuNode == listBuku->First) {
        // It's the first node
        listBuku->First = bukuNode->next;
        if (listBuku->Tail == bukuNode) {
            listBuku->Tail = NULL;
        }
    } else {
        // Find the previous node
        addressBuku prevBuku = listBuku->First;
        while (prevBuku != NULL && prevBuku->next != bukuNode) {
            prevBuku = prevBuku->next;
        }
        
        if (prevBuku != NULL) {
            prevBuku->next = bukuNode->next;
            if (listBuku->Tail == bukuNode) {
                listBuku->Tail = prevBuku;
            }
        }
    }
    
    // Free the node
    int stokBuku = bukuNode->stok;
    free(bukuNode);
    
    printf("Buku '%s' beserta seluruh antrian peminjamnya berhasil dihapus.\n", judulBuku);
    
    // Record in history
    char detail[200];
    sprintf(detail, "Buku '%s' dihapus (Stok: %d)", judulBuku, stokBuku);
    TambahRiwayat(&globalRiwayat, HAPUS_BUKU, detail);
}

void Implementasi_Hapus_Peminjam(ListPeminjam *listPeminjam, const char *namaPeminjam) {
    if (isEmptyPeminjam(*listPeminjam)) {
        printf("Daftar peminjam kosong.\n");
        return;
    }
    
    addressPeminjam currentPeminjam = listPeminjam->First;
    addressPeminjam prevPeminjam = NULL;
    boolean found = false;
    
    // Find the borrower
    while (currentPeminjam != NULL) {
        if (strcmp(currentPeminjam->namaPeminjam, namaPeminjam) == 0) {
            found = true;
            break;
        }
        prevPeminjam = currentPeminjam;
        currentPeminjam = currentPeminjam->next;
    }
    
    if (!found) {
        printf("Peminjam '%s' tidak ditemukan.\n", namaPeminjam);
        return;
    }
    
    // Get the book title for the history record
    char judulBuku[MAX] = "Tidak Ada";
    if (currentPeminjam->bukuDipinjam != NULL) {
        strcpy(judulBuku, currentPeminjam->bukuDipinjam->judulBuku);
    }
    
    // Remove the borrower
    if (prevPeminjam == NULL) {
        // It's the first node
        listPeminjam->First = currentPeminjam->next;
        if (listPeminjam->Tail == currentPeminjam) {
            listPeminjam->Tail = NULL;
        }
    } else {
        prevPeminjam->next = currentPeminjam->next;
        if (listPeminjam->Tail == currentPeminjam) {
            listPeminjam->Tail = prevPeminjam;
        }
    }
    
    // Free the node
    free(currentPeminjam);
    
    printf("Peminjam '%s' berhasil dihapus dari antrian buku '%s'.\n", namaPeminjam, judulBuku);
    
    // Record in history
    char detail[200];
    sprintf(detail, "Peminjam '%s' dihapus dari antrian buku '%s'", namaPeminjam, judulBuku);
    TambahRiwayat(&globalRiwayat, HAPUS_PEMINJAM, detail);
}

/* Fungsi Tampilkan Data */
void Implementasi_Tampilkan_Semua_Buku(const ListBuku *listBuku, const ListPeminjam *listPeminjam) {
    if (isEmptyBuku(*listBuku)) {
        printf("Daftar buku kosong.\n");
        return;
    }
    
    printf("Daftar Buku dan Peminjam:\n");
    printf("=========================\n");
    
    int countBuku = 0;
    addressBuku currentBuku = listBuku->First;
    
    while (currentBuku != NULL) {
        countBuku++;
        printf("%d. Judul: \"%s\" (Stok: %d)\n", countBuku, currentBuku->judulBuku, currentBuku->stok);
        
        // Find all borrowers for this book
        int countPeminjam = 0;
        addressPeminjam currentPeminjam = listPeminjam->First;
        
        while (currentPeminjam != NULL) {
            if (currentPeminjam->bukuDipinjam == currentBuku) {
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
                
                printf("   %d.%d Peminjam: \"%s\" (Prioritas: %s)\n", 
                       countBuku, countPeminjam, currentPeminjam->namaPeminjam, priorityText);
            }
            currentPeminjam = currentPeminjam->next;
        }
        
        if (countPeminjam == 0) {
            printf("   Tidak ada peminjam dalam antrian.\n");
        }
        
        currentBuku = currentBuku->next;
    }
}

void Implementasi_Tampilkan_Buku(const ListBuku *listBuku, const ListPeminjam *listPeminjam, const char *judulBuku) {
    // Find the book
    addressBuku bukuNode = NULL;
    addressBuku currentBuku = listBuku->First;
    
    while (currentBuku != NULL) {
        if (strcmp(currentBuku->judulBuku, judulBuku) == 0) {
            bukuNode = currentBuku;
            break;
        }
        currentBuku = currentBuku->next;
    }
    
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }
    
    printf("Detail Buku:\n");
    printf("=========================\n");
    printf("Judul: \"%s\"\n", bukuNode->judulBuku);
    printf("Stok: %d\n", bukuNode->stok);
    
    // Find all borrowers for this book
    printf("\nDaftar Peminjam:\n");
    printf("=========================\n");
    
    int countPeminjam = 0;
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
        }
        currentPeminjam = currentPeminjam->next;
    }
    
    if (countPeminjam == 0) {
        printf("Tidak ada peminjam dalam antrian.\n");
    }
}

/* Fungsi Tambahan */
int Implementasi_Hitung_Peminjam_Buku(const ListPeminjam *listPeminjam, const char *judulBuku) {
    if (isEmptyPeminjam(*listPeminjam)) {
        return 0;
    }
    
    int count = 0;
    addressPeminjam currentPeminjam = listPeminjam->First;
    
    while (currentPeminjam != NULL) {
        if (currentPeminjam->bukuDipinjam != NULL && 
            strcmp(currentPeminjam->bukuDipinjam->judulBuku, judulBuku) == 0) {
            count++;
        }
        currentPeminjam = currentPeminjam->next;
    }
    
    return count;
}

int Implementasi_Hitung_Total_Buku(const ListBuku *listBuku) {
    if (isEmptyBuku(*listBuku)) {
        return 0;
    }
    
    int count = 0;
    addressBuku currentBuku = listBuku->First;
    
    while (currentBuku != NULL) {
        count++;
        currentBuku = currentBuku->next;
    }
    
    return count;
}

int Implementasi_Hitung_Total_Peminjam(const ListPeminjam *listPeminjam) {
    if (isEmptyPeminjam(*listPeminjam)) {
        return 0;
    }
    
    int count = 0;
    addressPeminjam currentPeminjam = listPeminjam->First;
    
    while (currentPeminjam != NULL) {
        count++;
        currentPeminjam = currentPeminjam->next;
    }
    
    return count;
}

/* Fungsi Edit Data */
void Implementasi_Edit_Buku(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBukuLama, const char *judulBukuBaru, int stokBukuBaru) {
    // Find the book
    addressBuku bukuNode = SearchBuku(*listBuku, judulBukuLama);
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBukuLama);
        return;
    }
    
    // Check if the new title is already used (if changing title)
    if (strcmp(judulBukuLama, judulBukuBaru) != 0) {
        addressBuku existing = SearchBuku(*listBuku, judulBukuBaru);
        if (existing != NULL) {
            printf("Judul buku '%s' sudah digunakan.\n", judulBukuBaru);
            return;
        }
    }
    
    // Record the old values for history
    int stokLama = bukuNode->stok;
    
    // Update the book
    strcpy(bukuNode->judulBuku, judulBukuBaru);
    bukuNode->stok = stokBukuBaru;
    
    printf("Buku '%s' berhasil diubah menjadi '%s' dengan stok %d.\n", 
           judulBukuLama, judulBukuBaru, stokBukuBaru);
    
    // Record in history
    char detail[200];
    sprintf(detail, "Buku '%s' diubah menjadi '%s' (Stok: %d -> %d)", 
            judulBukuLama, judulBukuBaru, stokLama, stokBukuBaru);
    TambahRiwayat(&globalRiwayat, EDIT_BUKU, detail);
}

void Implementasi_Edit_Peminjam(ListPeminjam *listPeminjam, const char *namaPeminjamLama, const char *namaPeminjamBaru) {
    if (isEmptyPeminjam(*listPeminjam)) {
        printf("Daftar peminjam kosong.\n");
        return;
    }
    
    // Find the borrower
    addressPeminjam peminjamNode = SearchPeminjam(*listPeminjam, namaPeminjamLama);
    if (peminjamNode == NULL) {
        printf("Peminjam '%s' tidak ditemukan.\n", namaPeminjamLama);
        return;
    }
    
    // Check if the new name is already used (if changing name)
    if (strcmp(namaPeminjamLama, namaPeminjamBaru) != 0) {
        addressPeminjam existing = SearchPeminjam(*listPeminjam, namaPeminjamBaru);
        if (existing != NULL) {
            printf("Nama peminjam '%s' sudah digunakan.\n", namaPeminjamBaru);
            return;
        }
    }
    
    // Get the book title for the history record
    char judulBuku[MAX] = "Tidak Ada";
    if (peminjamNode->bukuDipinjam != NULL) {
        strcpy(judulBuku, peminjamNode->bukuDipinjam->judulBuku);
    }
    
    // Update the borrower
    strcpy(peminjamNode->namaPeminjam, namaPeminjamBaru);
    
    printf("Nama peminjam berhasil diubah dari '%s' menjadi '%s'.\n", 
           namaPeminjamLama, namaPeminjamBaru);
    
    // Record in history
    char detail[200];
    sprintf(detail, "Peminjam '%s' diubah menjadi '%s' untuk buku '%s'", 
            namaPeminjamLama, namaPeminjamBaru, judulBuku);
    TambahRiwayat(&globalRiwayat, EDIT_PEMINJAM, detail);
}

void Implementasi_Tampilkan_Peminjaman() {
    PrintPeminjaman(globalPeminjaman);
}

boolean Implementasi_Proses_Peminjaman(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam) {
    // Find the book
    addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return false;
    }
    
    // Check if book has stock
    if (bukuNode->stok <= 0) {
        printf("Stok buku '%s' habis. Tidak dapat memproses peminjaman.\n", judulBuku);
        return false;
    }
    
    // Find the borrower
    addressPeminjam peminjamNode = NULL;
    addressPeminjam currentPeminjam = listPeminjam->First;
    addressPeminjam prevPeminjam = NULL;
    
    while (currentPeminjam != NULL) {
        if (currentPeminjam->bukuDipinjam == bukuNode && 
            strcmp(currentPeminjam->namaPeminjam, namaPeminjam) == 0) {
            peminjamNode = currentPeminjam;
            break;
        }
        prevPeminjam = currentPeminjam;
        currentPeminjam = currentPeminjam->next;
    }
    
    if (peminjamNode == NULL) {
        printf("Peminjam '%s' tidak ditemukan dalam antrian buku '%s'.\n", namaPeminjam, judulBuku);
        return false;
    }
    
    // Process the loan
    // 1. Decrease book stock
    bukuNode->stok--;
    
    // 2. Remove borrower from queue
    if (prevPeminjam == NULL) {
        // It's the first node
        listPeminjam->First = peminjamNode->next;
        if (listPeminjam->Tail == peminjamNode) {
            listPeminjam->Tail = NULL;
        }
    } else {
        prevPeminjam->next = peminjamNode->next;
        if (listPeminjam->Tail == peminjamNode) {
            listPeminjam->Tail = prevPeminjam;
        }
    }
    
    // 3. Add to active loans
    addressPeminjaman newLoan = CreatePeminjaman(judulBuku, namaPeminjam, peminjamNode->skalaPrioritas);
    if (newLoan == NULL) {
        printf("Gagal mencatat peminjaman. Peminjaman dibatalkan.\n");
        
        // Restore book stock
        bukuNode->stok++;
        
        // Restore borrower to queue
        if (prevPeminjam == NULL) {
            peminjamNode->next = listPeminjam->First;
            listPeminjam->First = peminjamNode;
            if (listPeminjam->Tail == NULL) {
                listPeminjam->Tail = peminjamNode;
            }
        } else {
            peminjamNode->next = prevPeminjam->next;
            prevPeminjam->next = peminjamNode;
            if (prevPeminjam == listPeminjam->Tail) {
                listPeminjam->Tail = peminjamNode;
            }
        }
        
        return false;
    }
    
    // Free the borrower node
    free(peminjamNode);
    
    // Add to active loans
    InsertFirstPeminjaman(&globalPeminjaman, newLoan);
    
    // Get priority text
    char priorityText[20];
    switch (newLoan->skalaPrioritas) {
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
    
    printf("Peminjaman buku '%s' oleh '%s' (%s) berhasil diproses.\n", 
           judulBuku, namaPeminjam, priorityText);
    printf("Stok buku sekarang: %d\n", bukuNode->stok);
    
    // Record in history
    char detail[200];
    sprintf(detail, "%s (%s) meminjam buku '%s' (Stok sekarang: %d)", 
            namaPeminjam, priorityText, judulBuku, bukuNode->stok);
    TambahRiwayat(&globalRiwayat, PINJAM_BUKU, detail);
    
    return true;
}

void Implementasi_Pengembalian_Buku(ListBuku *listBuku, ListPeminjam *listPeminjam, const char *judulBuku, const char *namaPeminjam) {
    // Find the book
    addressBuku bukuNode = SearchBuku(*listBuku, judulBuku);
    if (bukuNode == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }
    
    // Find the loan
    addressPeminjaman peminjaman = SearchPeminjaman(globalPeminjaman, judulBuku, namaPeminjam);
    if (peminjaman == NULL) {
        printf("Peminjaman buku '%s' oleh '%s' tidak ditemukan.\n", judulBuku, namaPeminjam);
        return;
    }
    
    // Process the return
    // 1. Increase book stock
    bukuNode->stok++;
    
    // 2. Remove from active loans
    addressPeminjaman currentPeminjaman = globalPeminjaman.First;
    addressPeminjaman prevPeminjaman = NULL;
    
    while (currentPeminjaman != NULL) {
        if (currentPeminjaman == peminjaman) {
            if (prevPeminjaman == NULL) {
                // It's the first node
                globalPeminjaman.First = currentPeminjaman->next;
            } else {
                prevPeminjaman->next = currentPeminjaman->next;
            }
            
            // Free the node
            free(currentPeminjaman);
            break;
        }
        
        prevPeminjaman = currentPeminjaman;
        currentPeminjaman = currentPeminjaman->next;
    }
    
    printf("Pengembalian buku '%s' oleh '%s' berhasil diproses.\n", judulBuku, namaPeminjam);
    printf("Stok buku sekarang: %d\n", bukuNode->stok);
    
    // Record in history
    char detail[200];
    sprintf(detail, "%s mengembalikan buku '%s' (Stok sekarang: %d)", 
            namaPeminjam, judulBuku, bukuNode->stok);
    TambahRiwayat(&globalRiwayat, KEMBALI_BUKU, detail);
    
    // Check if there are any borrowers in queue who can be processed
    // With priority queue, just find the first borrower for this book
    addressPeminjam firstBorrowerForBook = NULL;
    
    // Since the list is now sorted by priority, we can just loop through
    // and take the first borrower we find for this book
    addressPeminjam currentPeminjam = listPeminjam->First;
    while (currentPeminjam != NULL) {
        if (currentPeminjam->bukuDipinjam == bukuNode) {
            firstBorrowerForBook = currentPeminjam;
            break;
        }
        currentPeminjam = currentPeminjam->next;
    }
    
    if (firstBorrowerForBook != NULL) {
        // Get priority text
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
        
        printf("\nBuku '%s' sekarang tersedia dan dapat dipinjam oleh '%s' (%s).\n", 
               judulBuku, firstBorrowerForBook->namaPeminjam, priorityText);
        printf("Gunakan menu 'Proses Peminjaman' untuk memproses peminjaman ini.\n");
    }
}

