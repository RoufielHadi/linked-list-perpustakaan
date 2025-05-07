/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "linked.h"

// ===================== KONSTRUKTOR =====================
void CreateListBuku(ListBuku *L) {
    L->First = NULL;
}

void DeleteListBuku(ListBuku *L) {
    addressBuku temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

// Konstruktor untuk ListPeminjaman
void CreateListPeminjaman(ListPeminjaman *L) {
    L->First = NULL;
}

void DeleteListPeminjaman(ListPeminjaman *L) {
    addressPeminjaman temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

// ===================== VALIDATOR =====================
boolean isEmptyBuku(ListBuku L) {
    return (L.First == NULL);
}

boolean isEmptyPeminjaman(ListPeminjaman L) {
    return (L.First == NULL);
}

// ================== OPERASI DASAR ====================
addressBuku CreateBuku(const char *judulBuku) {
    addressBuku P = (addressBuku)malloc(sizeof(daftarBuku));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk buku.\n");
        return NULL;
    }
    strcpy(P->judulBuku, judulBuku);
    P->stokBuku = 0;  // Stok default diatur ke 0
    CreateQueue(&P->antrianPeminjam);  // Inisialisasi antrian peminjam
    P->next = NULL;
    return P;
}

void InsertFirstBuku(ListBuku *L, addressBuku P) {
    if (P != NULL) {
        P->next = L->First;
        L->First = P;
    }
}

void InsertLastBuku(ListBuku *L, addressBuku P) {
    if (P != NULL) {
        if (isEmptyBuku(*L)) {
            L->First = P;
        } else {
            addressBuku temp = L->First;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = P;
        }
    }
}

void InsertAfterBuku(addressBuku pBef, addressBuku PNew) {
    if (pBef != NULL && PNew != NULL) {
        PNew->next = pBef->next;
        pBef->next = PNew;
    }
}

void DeleteFirstBuku(ListBuku *L) {
    if (!isEmptyBuku(*L)) {
        addressBuku temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

void DeleteLastBuku(ListBuku *L) {
    if (!isEmptyBuku(*L)) {
        if (L->First->next == NULL) {
            free(L->First);
            L->First = NULL;
        } else {
            addressBuku temp = L->First;
            while (temp->next->next != NULL) {
                temp = temp->next;
            }
            free(temp->next);
            temp->next = NULL;
        }
    }
}

void DeleteAfterBuku(addressBuku pBef) {
    if (pBef != NULL && pBef->next != NULL) {
        addressBuku temp = pBef->next;
        pBef->next = temp->next;
        free(temp);
    }
}

void DeAlokasiBuku(addressBuku *P) {
    if (*P != NULL) {
        free(*P);
        *P = NULL;
    }
}

int NbElmtBuku(ListBuku L) {
    int count = 0;
    addressBuku P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

addressBuku SearchBuku(ListBuku L, const char *judulBuku) {
    addressBuku P = L.First;
    while (P != NULL) {
        if (strcmp(P->judulBuku, judulBuku) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void PrintBuku(ListBuku L) {
    addressBuku P = L.First;
    if (P == NULL) {
        printf("List buku kosong.\n");
    } else {
        printf("Daftar Buku:\n");
        while (P != NULL) {
            printf("- %s (Stok: %d)\n", P->judulBuku, P->stokBuku);
            P = P->next;
        }
    }
}

ListBuku BalikListBuku(ListBuku L) {
    ListBuku reversed;
    CreateListBuku(&reversed);
    addressBuku P = L.First;
    while (P != NULL) {
        addressBuku newBuku = CreateBuku(P->judulBuku);
        InsertFirstBuku(&reversed, newBuku);
        P = P->next;
    }
    return reversed;
}

addressPeminjaman CreatePeminjaman(const char *judulBuku, const char *namaPeminjam, int skalaPrioritas) {
    addressPeminjaman P = (addressPeminjaman)malloc(sizeof(daftarPeminjaman));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk peminjaman.\n");
        return NULL;
    }
    strcpy(P->judulBuku, judulBuku);
    strcpy(P->namaPeminjam, namaPeminjam);
    P->skalaPrioritas = skalaPrioritas;
    P->next = NULL;
    return P;
}

void InsertFirstPeminjaman(ListPeminjaman *L, addressPeminjaman P) {
    if (P != NULL) {
        P->next = L->First;
        L->First = P;
    }
}

void InsertLastPeminjaman(ListPeminjaman *L, addressPeminjaman P) {
    if (P != NULL) {
        if (isEmptyPeminjaman(*L)) {
            L->First = P;
        } else {
            addressPeminjaman temp = L->First;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = P;
        }
    }
}

void DeleteFirstPeminjaman(ListPeminjaman *L) {
    if (!isEmptyPeminjaman(*L)) {
        addressPeminjaman temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

void DeAlokasiPeminjaman(addressPeminjaman *P) {
    if (*P != NULL) {
        free(*P);
        *P = NULL;
    }
}

addressPeminjaman SearchPeminjaman(ListPeminjaman L, const char *judulBuku, const char *namaPeminjam) {
    addressPeminjaman P = L.First;
    while (P != NULL) {
        if (strcmp(P->judulBuku, judulBuku) == 0 && strcmp(P->namaPeminjam, namaPeminjam) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void PrintPeminjaman(ListPeminjaman L) {
    addressPeminjaman P = L.First;
    if (P == NULL) {
        printf("List peminjaman kosong.\n");
    } else {
        printf("Daftar Peminjaman Aktif:\n");
        printf("=========================\n");
        int count = 1;
        while (P != NULL) {
            printf("%d. Buku: \"%s\" - Peminjam: %s (Prioritas: %d)\n", 
                   count++, P->judulBuku, P->namaPeminjam, P->skalaPrioritas);
            P = P->next;
        }
    }
}

