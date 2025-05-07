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
    L->Tail = NULL;
}

void DeleteListBuku(ListBuku *L) {
    addressBuku temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
    L->Tail = NULL;
}

void CreateListPeminjam(ListPeminjam *L) {
    L->First = NULL;
    L->Tail = NULL;
}

void DeleteListPeminjam(ListPeminjam *L) {
    addressPeminjam temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
    L->Tail = NULL;
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

boolean isEmptyPeminjam(ListPeminjam L) {
    return (L.First == NULL);
}

boolean isEmptyPeminjaman(ListPeminjaman L) {
    return (L.First == NULL);
}

// ================== OPERASI DASAR ====================
addressBuku CreateNodeBuku(const char *judulBuku, int stok) {
    addressBuku P = (addressBuku)malloc(sizeof(daftarBuku));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk node buku.\n");
        return NULL;
    }
    strcpy(P->judulBuku, judulBuku);
    P->stok = stok;
    P->next = NULL;
    return P;
}

addressPeminjam CreateNodePeminjam(const char *namaPeminjam, int skalaPrioritas, addressBuku bukuDipinjam) {
    addressPeminjam P = (addressPeminjam)malloc(sizeof(antrianPeminjam));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk node peminjam.\n");
        return NULL;
    }
    strcpy(P->namaPeminjam, namaPeminjam);
    P->skalaPrioritas = skalaPrioritas;
    P->bukuDipinjam = bukuDipinjam;
    P->next = NULL;
    return P;
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

void InsertFirstBuku(ListBuku *L, addressBuku P) {
    if (P != NULL) {
        if (isEmptyBuku(*L)) {
            L->First = P;
            L->Tail = P;
        } else {
            P->next = L->First;
            L->First = P;
        }
    }
}

void InsertFirstPeminjam(ListPeminjam *L, addressPeminjam P) {
    if (P != NULL) {
        // Use the priority-based insertion logic from InsertLastPeminjam
        // which now handles sorting by priority
        InsertLastPeminjam(L, P);
    }
}

void InsertFirstPeminjaman(ListPeminjaman *L, addressPeminjaman P) {
    if (P != NULL) {
        P->next = L->First;
        L->First = P;
    }
}

void InsertLastBuku(ListBuku *L, addressBuku P) {
    if (P != NULL) {
        if (isEmptyBuku(*L)) {
            L->First = P;
            L->Tail = P;
        } else {
            L->Tail->next = P;
            L->Tail = P;
        }
    }
}

void InsertLastPeminjam(ListPeminjam *L, addressPeminjam P) {
    if (P != NULL) {
        if (isEmptyPeminjam(*L)) {
            // If list is empty, make P the first and only element
            L->First = P;
            L->Tail = P;
            P->next = NULL;
        } else {
            // Priority queue: lower skalaPrioritas value = higher priority
            addressPeminjam curr = L->First;
            addressPeminjam prev = NULL;
            
            // Find the position where P should be inserted based on priority
            // First by priority level (skalaPrioritas)
            // Then by FIFO for same priority (maintain order of arrival)
            while (curr != NULL && curr->skalaPrioritas <= P->skalaPrioritas) {
                prev = curr;
                curr = curr->next;
            }
            
            if (prev == NULL) {
                // Insert at the beginning (higher priority than first node)
                P->next = L->First;
                L->First = P;
                
                // If this was an empty list, also update the tail
                if (L->Tail == NULL) {
                    L->Tail = P;
                }
            } else {
                // Insert in the middle or at the end
                P->next = curr;
                prev->next = P;
                
                // If inserting at the end, update the tail
                if (curr == NULL) {
                    L->Tail = P;
                }
            }
        }
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

void InsertAfterBuku(addressBuku pBef, addressBuku PNew) {
    if (pBef != NULL && PNew != NULL) {
        PNew->next = pBef->next;
        pBef->next = PNew;
    }
}

void InsertAfterPeminjam(addressPeminjam pBef, addressPeminjam PNew) {
    if (pBef != NULL && PNew != NULL) {
        PNew->next = pBef->next;
        pBef->next = PNew;
    }
}

void DeleteFirstBuku(ListBuku *L) {
    if (!isEmptyBuku(*L)) {
        addressBuku temp = L->First;
        
        if (L->First == L->Tail) {
            // Jika hanya ada satu elemen
            L->First = NULL;
            L->Tail = NULL;
        } else {
            L->First = L->First->next;
        }
        
        free(temp);
    }
}

void DeleteFirstPeminjam(ListPeminjam *L) {
    if (!isEmptyPeminjam(*L)) {
        addressPeminjam temp = L->First;
        
        if (L->First == L->Tail) {
            // Jika hanya ada satu elemen
            L->First = NULL;
            L->Tail = NULL;
        } else {
            L->First = L->First->next;
        }
        
        free(temp);
    }
}

void DeleteFirstPeminjaman(ListPeminjaman *L) {
    if (!isEmptyPeminjaman(*L)) {
        addressPeminjaman temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

void DeleteLastBuku(ListBuku *L) {
    if (!isEmptyBuku(*L)) {
        if (L->First == L->Tail) {
            // Jika hanya ada satu elemen
            free(L->First);
            L->First = NULL;
            L->Tail = NULL;
        } else {
            addressBuku temp = L->First;
            // Mencari elemen sebelum elemen terakhir
            while (temp->next != L->Tail) {
                temp = temp->next;
            }
            
            free(L->Tail);
            L->Tail = temp;
            L->Tail->next = NULL;
        }
    }
}

void DeleteLastPeminjam(ListPeminjam *L) {
    if (!isEmptyPeminjam(*L)) {
        if (L->First == L->Tail) {
            // Jika hanya ada satu elemen
            free(L->First);
            L->First = NULL;
            L->Tail = NULL;
        } else {
            addressPeminjam temp = L->First;
            // Mencari elemen sebelum elemen terakhir
            while (temp->next != L->Tail) {
                temp = temp->next;
            }
            
            free(L->Tail);
            L->Tail = temp;
            L->Tail->next = NULL;
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

void DeleteAfterPeminjam(addressPeminjam pBef) {
    if (pBef != NULL && pBef->next != NULL) {
        addressPeminjam temp = pBef->next;
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

void DeAlokasiPeminjam(addressPeminjam *P) {
    if (*P != NULL) {
        free(*P);
        *P = NULL;
    }
}

void DeAlokasiPeminjaman(addressPeminjaman *P) {
    if (*P != NULL) {
        free(*P);
        *P = NULL;
    }
}

// ================= OPERASI TAMBAHAN =================
int NbElmtBuku(ListBuku L) {
    int count = 0;
    addressBuku P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

int NbElmtPeminjam(ListPeminjam L) {
    int count = 0;
    addressPeminjam P = L.First;
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

addressPeminjam SearchPeminjam(ListPeminjam L, const char *namaPeminjam) {
    addressPeminjam P = L.First;
    while (P != NULL) {
        if (strcmp(P->namaPeminjam, namaPeminjam) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
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

void PrintBuku(ListBuku L) {
    addressBuku P = L.First;
    if (P == NULL) {
        printf("List buku kosong.\n");
    } else {
        printf("Daftar Buku:\n");
        printf("=========================\n");
        int count = 1;
        while (P != NULL) {
            printf("%d. Judul: \"%s\" (Stok: %d)\n", count++, P->judulBuku, P->stok);
            P = P->next;
        }
    }
}

void PrintPeminjam(ListPeminjam L) {
    addressPeminjam P = L.First;
    if (P == NULL) {
        printf("List peminjam kosong.\n");
    } else {
        printf("Daftar Peminjam:\n");
        printf("=========================\n");
        int count = 1;
        while (P != NULL) {
            printf("%d. Nama: \"%s\" (Prioritas: %d) - Meminjam: \"%s\"\n", 
                count++, 
                P->namaPeminjam, 
                P->skalaPrioritas,
                P->bukuDipinjam != NULL ? P->bukuDipinjam->judulBuku : "Tidak ada");
            P = P->next;
        }
    }
}

void PrintPeminjaman(ListPeminjaman L) {
    addressPeminjaman P = L.First;
    if (P == NULL) {
        printf("Tidak ada peminjaman yang sedang berlangsung.\n");
    } else {
        printf("Daftar Peminjaman Yang Sedang Berlangsung:\n");
        printf("=========================\n");
        int count = 1;
        while (P != NULL) {
            printf("%d. Judul: \"%s\" - Peminjam: \"%s\" (Prioritas: %d)\n", 
                count++, 
                P->judulBuku, 
                P->namaPeminjam, 
                P->skalaPrioritas);
            P = P->next;
        }
    }
}

ListBuku BalikListBuku(ListBuku L) {
    ListBuku reversed;
    CreateListBuku(&reversed);
    
    addressBuku P = L.First;
    while (P != NULL) {
        addressBuku newNode = CreateNodeBuku(P->judulBuku, P->stok);
        InsertFirstBuku(&reversed, newNode);
        P = P->next;
    }
    
    return reversed;
}

ListPeminjam BalikListPeminjam(ListPeminjam L) {
    ListPeminjam reversed;
    CreateListPeminjam(&reversed);
    
    addressPeminjam P = L.First;
    while (P != NULL) {
        addressPeminjam newNode = CreateNodePeminjam(P->namaPeminjam, P->skalaPrioritas, P->bukuDipinjam);
        InsertFirstPeminjam(&reversed, newNode);
        P = P->next;
    }
    
    return reversed;
}

