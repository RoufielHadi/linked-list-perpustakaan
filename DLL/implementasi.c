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

void LakukanUndoOperasi(ListBuku *LB, TipeAktivitas tipe, const char *detail) {
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

boolean UndoAktivitas(ListRiwayat *L, ListBuku *LB) {
    if (L->current == NULL || L->current == L->first) {
        printf("Tidak ada aktivitas yang dapat di-undo.\n");
        return 0;  // false
    }
    
    // Simpan informasi aktivitas yang akan di-undo
    TipeAktivitas aktivitasSaatIni = L->current->tipe;
    char detailSaatIni[200];
    strcpy(detailSaatIni, L->current->detail);
    
    // Pindah current ke aktivitas sebelumnya
    L->current = L->current->prev;
    
    // Tindakan undo berdasarkan tipe aktivitas
    printf("Undo berhasil: Kembali ke aktivitas '%s'\n", L->current->detail);
    
    // Coba lakukan operasi undo
    LakukanUndoOperasi(LB, aktivitasSaatIni, detailSaatIni);
    
    return 1;  // true
}

/* Fungsi Entry (Tambah Data) */
void Implementasi_Tambah_Buku(ListBuku *L, const char *judulBuku, int stokBuku) {
    // Cek apakah buku sudah ada
    if (SearchBuku(*L, (char *)judulBuku) != NULL) {
        printf("Buku %s sudah ada dalam daftar.\n", judulBuku);
        return;
    }

    // Buat buku baru
    addressBuku newBuku = CreateBuku((char *)judulBuku);
    if (newBuku == NULL) {
        printf("Gagal menambahkan buku %s.\n", judulBuku);
        return;
    }

    // Set stok buku
    newBuku->stokBuku = stokBuku;
    // Inisialisasi antrian peminjam
    CreateQueue(&newBuku->antrianPeminjam);

    // Tambahkan ke list
    InsertLastBuku(L, newBuku);
    
    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "%s (Stok: %d)", judulBuku, stokBuku);
    TambahRiwayat(&globalRiwayat, TAMBAH_BUKU, detail);
    
    printf("Buku %s berhasil ditambahkan dengan stok %d.\n", judulBuku, stokBuku);
}

void Implementasi_Tambah_Peminjam(ListBuku *L, const char *judulBuku, const char *namaPeminjam, int skalaPrioritas) {
    // Cari buku
    addressBuku buku = SearchBuku(*L, judulBuku);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Cek apakah peminjam dengan nama tersebut sudah ada dalam antrian
    if (SearchPeminjam(buku->antrianPeminjam, namaPeminjam) != NULL) {
        printf("Peminjam %s sudah ada dalam antrian buku %s.\n", namaPeminjam, judulBuku);
        return;
    }

    // Tambahkan peminjam ke dalam antrian buku berdasarkan prioritas
    Enqueue(&buku->antrianPeminjam, namaPeminjam, skalaPrioritas);
    
    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "%s masuk antrian buku '%s' dengan prioritas %d", namaPeminjam, judulBuku, skalaPrioritas);
    TambahRiwayat(&globalRiwayat, TAMBAH_PEMINJAM, detail);
    
    // Tampilkan pesan berdasarkan prioritas
    if (skalaPrioritas == 1) { // Dosen memiliki prioritas tertinggi
        printf("Peminjam %s (Dosen) berhasil ditambahkan ke antrian buku %s dengan prioritas tertinggi.\n", 
              namaPeminjam, judulBuku);
    } else if (skalaPrioritas == 2) { // Mahasiswa memiliki prioritas kedua
        printf("Peminjam %s (Mahasiswa) berhasil ditambahkan ke antrian buku %s dengan prioritas kedua.\n", 
              namaPeminjam, judulBuku);
    } else { // Masyarakat Umum (3)
        printf("Peminjam %s (Masyarakat Umum) berhasil ditambahkan ke antrian buku %s dengan prioritas terendah.\n", 
              namaPeminjam, judulBuku);
    }
    
    printf("Peminjaman perlu diproses lebih lanjut melalui menu 'Proses Peminjaman'.\n");
}

/* Fungsi Delete (Hapus Data) */
void Implementasi_Hapus_Buku(ListBuku *L, const char *judulBuku) {
    if (isEmptyBuku(*L)) {
        printf("Daftar buku kosong.\n");
        return;
    }

    addressBuku prev = NULL;
    addressBuku curr = L->First;

    // Cari buku
    while (curr != NULL && strcmp(curr->judulBuku, judulBuku) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Hapus semua peminjam di buku tersebut
    DeleteListPeminjam(&(curr->antrianPeminjam));

    // Hapus buku dari list
    if (prev == NULL) {
        DeleteFirstBuku(L);
    } else {
        DeleteAfterBuku(prev);
    }

    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "Buku '%s' dihapus", judulBuku);
    TambahRiwayat(&globalRiwayat, HAPUS_BUKU, detail);

    printf("Buku %s dan semua peminjamnya berhasil dihapus.\n", judulBuku);
}

void Implementasi_Hapus_Peminjam(ListBuku *L, const char *judulBuku, const char *namaPeminjam) {
    // Cari buku
    addressBuku buku = SearchBuku(*L, (char *)judulBuku);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Cari peminjam yang akan dihapus
    addressPeminjam peminjam = SearchPeminjam(buku->antrianPeminjam, (char *)namaPeminjam);
    if (peminjam == NULL) {
        printf("Peminjam %s tidak ditemukan dalam antrian buku %s.\n", namaPeminjam, judulBuku);
        return;
    }

    // Hapus peminjam dari antrian
    Dequeue(&buku->antrianPeminjam, namaPeminjam);
    
    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "Peminjam '%s' dihapus dari buku '%s'", namaPeminjam, judulBuku);
    TambahRiwayat(&globalRiwayat, HAPUS_PEMINJAM, detail);
    
    printf("Peminjam %s berhasil dihapus dari antrian buku %s.\n", namaPeminjam, judulBuku);
}

/* Fungsi Tampilkan Data */
void Implementasi_Tampilkan_Semua_Buku(const ListBuku *L) {
    if (isEmptyBuku(*L)) {
        printf("Daftar buku kosong.\n");
        return;
    }

    addressBuku buku = L->First;
    while (buku != NULL) {
        printf("\nBuku: %s\n", buku->judulBuku);
        printf("Stok Buku: %d\n", buku->stokBuku);
        printf("Jumlah Peminjam: %d\n", NbElmtQueue(buku->antrianPeminjam));
        printf("Daftar Peminjam:\n");

        if (isEmptyQueue(buku->antrianPeminjam)) {
            printf("- Tidak ada peminjam\n");
        } else {
            TampilQueue(buku->antrianPeminjam);
        }

        buku = buku->next;
    }
}

void Implementasi_Tampilkan_Buku(const ListBuku *L, const char *judulBuku) {
    addressBuku buku = SearchBuku(*L, (char *)judulBuku);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    printf("\nBuku: %s\n", buku->judulBuku);
    printf("Stok Buku: %d\n", buku->stokBuku);
    printf("Jumlah Peminjam: %d\n", NbElmtQueue(buku->antrianPeminjam));

    if (isEmptyQueue(buku->antrianPeminjam)) {
        printf("- Tidak ada peminjam\n");
    } else {
        TampilQueue(buku->antrianPeminjam);
    }
}

/* Fungsi Tambahan */
int Implementasi_Hitung_Peminjam_Buku(const ListBuku *L, const char *judulBuku) {
    addressBuku buku = SearchBuku(*L, (char *)judulBuku);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return 0;
    }
    return NbElmtQueue(buku->antrianPeminjam);
}

int Implementasi_Hitung_Total_Buku(const ListBuku *L) {
    return NbElmtBuku(*L);
}

int Implementasi_Hitung_Total_Peminjam(const ListBuku *L) {
    int total = 0;
    addressBuku buku = L->First;

    while (buku != NULL) {
        total += NbElmtQueue(buku->antrianPeminjam);
        buku = buku->next;
    }

    return total;
}

/* Fungsi Edit Data */
void Implementasi_Edit_Buku(ListBuku *L, const char *judulBukuLama, const char *judulBukuBaru, int stokBukuBaru) {
    if (isEmptyBuku(*L)) {
        printf("Daftar buku kosong.\n");
        return;
    }

    // Cari buku yang akan diedit
    addressBuku buku = SearchBuku(*L, (char *)judulBukuLama);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBukuLama);
        return;
    }

    // Cek apakah judul baru sudah digunakan
    if (strcmp(judulBukuLama, judulBukuBaru) != 0 && SearchBuku(*L, (char *)judulBukuBaru) != NULL) {
        printf("Buku %s sudah ada dalam daftar.\n", judulBukuBaru);
        return;
    }

    // Edit nama dan stok buku
    strcpy(buku->judulBuku, judulBukuBaru);
    buku->stokBuku = stokBukuBaru;
    
    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "Buku '%s' diubah menjadi '%s' (Stok: %d)", judulBukuLama, judulBukuBaru, stokBukuBaru);
    TambahRiwayat(&globalRiwayat, EDIT_BUKU, detail);
    
    printf("Nama buku berhasil diubah dari %s menjadi %s dan stok buku diubah menjadi %d.\n", 
           judulBukuLama, judulBukuBaru, stokBukuBaru);
}

void Implementasi_Edit_Peminjam(ListBuku *L, const char *judulBuku, const char *namaPeminjamLama, const char *namaPeminjamBaru) {
    // Cari buku
    addressBuku buku = SearchBuku(*L, (char *)judulBuku);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Cari peminjam yang akan diedit
    addressPeminjam peminjam = SearchPeminjam(buku->antrianPeminjam, (char *)namaPeminjamLama);
    if (peminjam == NULL) {
        printf("Peminjam %s tidak ditemukan di antrian buku %s.\n", namaPeminjamLama, judulBuku);
        return;
    }

    // Cek apakah nama baru sudah digunakan
    if (strcmp(namaPeminjamLama, namaPeminjamBaru) != 0 && 
        SearchPeminjam(buku->antrianPeminjam, (char *)namaPeminjamBaru) != NULL) {
        printf("Peminjam %s sudah ada di antrian buku %s.\n", namaPeminjamBaru, judulBuku);
        return;
    }

    // Edit nama peminjam
    strcpy(peminjam->namaPeminjam, namaPeminjamBaru);
    
    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "Peminjam '%s' diubah menjadi '%s' pada buku '%s'", namaPeminjamLama, namaPeminjamBaru, judulBuku);
    TambahRiwayat(&globalRiwayat, EDIT_PEMINJAM, detail);
    
    printf("Nama peminjam berhasil diubah dari %s menjadi %s di antrian buku %s.\n", 
           namaPeminjamLama, namaPeminjamBaru, judulBuku);
}

void Implementasi_Tampilkan_Peminjaman() {
    PrintPeminjaman(globalPeminjaman);
}

boolean Implementasi_Proses_Peminjaman(ListBuku *L, const char *judulBuku, const char *namaPeminjam) {
    // Validasi parameter untuk mencegah NULL pointer
    if (L == NULL || judulBuku == NULL || namaPeminjam == NULL) {
        printf("Error: Parameter tidak valid dalam fungsi pemrosesan peminjaman.\n");
        return 0; // false
    }
    
    // Validasi string kosong
    if (strlen(judulBuku) == 0 || strlen(namaPeminjam) == 0) {
        printf("Error: Judul buku atau nama peminjam tidak boleh kosong.\n");
        return 0; // false
    }

    // Cari buku
    addressBuku buku = SearchBuku(*L, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return 0; // false
    }

    // Cari peminjam dalam antrian
    addressPeminjam peminjam = SearchPeminjam(buku->antrianPeminjam, namaPeminjam);
    if (peminjam == NULL) {
        printf("Peminjam '%s' tidak ditemukan dalam antrian buku '%s'.\n", namaPeminjam, judulBuku);
        return 0; // false
    }

    // Periksa stok buku
    if (buku->stokBuku <= 0) {
        printf("Stok buku '%s' habis, tidak dapat memproses peminjaman.\n", judulBuku);
        return 0; // false
    }

    // Kurangi stok buku
    buku->stokBuku--;
    
    // Tambahkan peminjam ke list peminjaman aktif
    addressPeminjaman newPeminjaman = CreatePeminjaman(judulBuku, namaPeminjam, peminjam->skalaPrioritas);
    if (newPeminjaman == NULL) {
        printf("Gagal membuat data peminjaman.\n");
        buku->stokBuku++; // Kembalikan stok jika gagal
        return 0; // false
    }
    
    // Masukkan ke daftar peminjaman
    InsertLastPeminjaman(&globalPeminjaman, newPeminjaman);
    
    // Tambahkan ke riwayat aktivitas
    char detail[200];
    sprintf(detail, "%s meminjam buku '%s' (Peminjaman diproses, stok sekarang: %d)", 
            namaPeminjam, judulBuku, buku->stokBuku);
    TambahRiwayat(&globalRiwayat, PINJAM_BUKU, detail);
    
    printf("Peminjaman buku '%s' oleh '%s' berhasil diproses. Stok buku sekarang: %d\n", 
           judulBuku, namaPeminjam, buku->stokBuku);
           
    return 1; // true
}

void Implementasi_Pengembalian_Buku(ListBuku *L, const char *judulBuku, const char *namaPeminjam) {
    // Cari buku
    addressBuku buku = SearchBuku(*L, judulBuku);
    if (buku == NULL) {
        printf("Buku %s tidak ditemukan.\n", judulBuku);
        return;
    }

    // Cari peminjaman dalam daftar peminjaman aktif
    addressPeminjaman peminjaman = SearchPeminjaman(globalPeminjaman, judulBuku, namaPeminjam);
    if (peminjaman == NULL) {
        // Jika tidak ditemukan di daftar peminjaman aktif, periksa juga di antrian
        addressPeminjam peminjam = SearchPeminjam(buku->antrianPeminjam, namaPeminjam);
        if (peminjam != NULL) {
            printf("Peminjam %s belum meminjam buku %s, masih dalam antrian peminjaman.\n", namaPeminjam, judulBuku);
        } else {
            printf("Peminjam %s tidak ditemukan dalam daftar peminjaman buku %s.\n", namaPeminjam, judulBuku);
        }
        return;
    }

    // Hapus dari daftar peminjaman aktif
    // Karena tidak ada DeletePeminjaman yang mencari berdasarkan judul dan nama, kita harus iterasi manual
    if (globalPeminjaman.First != NULL) {
        if (strcmp(globalPeminjaman.First->judulBuku, judulBuku) == 0 && 
            strcmp(globalPeminjaman.First->namaPeminjam, namaPeminjam) == 0) {
            // Peminjaman ada di posisi pertama
            DeleteFirstPeminjaman(&globalPeminjaman);
        } else {
            // Cari posisi peminjaman
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
                // Hapus node peminjaman
                prev->next = curr->next;
                free(curr);
            }
        }
    }
    
    // Tambah stok buku
    buku->stokBuku++;
    
    // Tambahkan ke riwayat
    char detail[200];
    sprintf(detail, "%s mengembalikan buku '%s' (Stok sekarang: %d)", 
            namaPeminjam, judulBuku, buku->stokBuku);
    TambahRiwayat(&globalRiwayat, KEMBALI_BUKU, detail);
    
    printf("Buku %s telah dikembalikan oleh %s. Stok buku sekarang: %d\n", 
           judulBuku, namaPeminjam, buku->stokBuku);

    // Cek apakah ada peminjam berikutnya dalam antrian yang dapat diproses
    if (!isEmptyQueue(buku->antrianPeminjam)) {
        // Peminjam dengan prioritas tertinggi ada di front karena sudah diurutkan saat Enqueue
        addressPeminjam nextBorrower = buku->antrianPeminjam.front;
        
        if (nextBorrower != NULL) {
            printf("Peminjam %s dengan prioritas %d akan mendapatkan buku %s selanjutnya.\n", 
                   nextBorrower->namaPeminjam, nextBorrower->skalaPrioritas, judulBuku);
            
            printf("Memproses peminjaman secara otomatis...\n");
            
            // Kurangi stok buku
            buku->stokBuku--;
            
            // Tambahkan ke list peminjaman
            addressPeminjaman newPeminjaman = CreatePeminjaman(judulBuku, nextBorrower->namaPeminjam, nextBorrower->skalaPrioritas);
            if (newPeminjaman != NULL) {
                InsertLastPeminjaman(&globalPeminjaman, newPeminjaman);
            }
            
            // Hapus dari antrian
            Dequeue(&buku->antrianPeminjam, nextBorrower->namaPeminjam);
            
            // Tambahkan ke riwayat proses peminjaman otomatis dari antrian
            char detailPinjam[200];
            sprintf(detailPinjam, "%s meminjam buku '%s' (dari antrian, stok sekarang: %d)", 
                    nextBorrower->namaPeminjam, judulBuku, buku->stokBuku);
            TambahRiwayat(&globalRiwayat, PINJAM_BUKU, detailPinjam);
            
            printf("Peminjaman untuk %s berhasil diproses. Stok buku sekarang: %d\n", 
                   nextBorrower->namaPeminjam, buku->stokBuku);
        }
    }
}

