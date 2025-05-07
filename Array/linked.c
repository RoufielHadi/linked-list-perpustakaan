/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "linked.h"

// ================== IMPLEMENTASI QUEUE ====================
void CreateQueue(Queue *Q) {
    Q->First = NULL;
}

boolean isEmptyQueue(Queue Q) {
    return (Q.First == NULL);
}

addressPeminjam CreatePeminjam(const char *namaPeminjam, int skalaPrioritas) {
    addressPeminjam P = (addressPeminjam)malloc(sizeof(Peminjam));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk peminjam.\n");
        return NULL;
    }
    strcpy(P->nama, namaPeminjam);
    P->skalaPrioritas = skalaPrioritas;
    P->next = NULL;
    return P;
}

void DeAlokasiPeminjam(addressPeminjam *P) {
    if (*P != NULL) {
        free(*P);
        *P = NULL;
    }
}

addressPeminjam SearchPeminjam(Queue Q, const char *namaPeminjam) {
    addressPeminjam P = Q.First;
    while (P != NULL) {
        if (strcmp(P->nama, namaPeminjam) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void TampilQueue(Queue Q) {
    addressPeminjam P = Q.First;
    int count = 1;
    while (P != NULL) {
        printf("%d. %s (Prioritas: %d)\n", count++, P->nama, P->skalaPrioritas);
        P = P->next;
    }
}

void PrintQueue(Queue Q) {
    addressPeminjam P = Q.First;
    if (P == NULL) {
        printf("Antrian peminjam kosong.\n");
    } else {
        printf("Daftar Antrian Peminjam:\n");
        printf("=========================\n");
        int count = 1;
        while (P != NULL) {
            printf("%d. Peminjam: %s (Prioritas: %d)\n", 
                   count++, P->nama, P->skalaPrioritas);
            P = P->next;
        }
    }
}

void EnqueueWithPriority(Queue *Q, addressPeminjam P) {
    if (P == NULL) return;
    
    // Jika antrian kosong atau prioritas P lebih tinggi dari elemen pertama
    if (isEmptyQueue(*Q) || P->skalaPrioritas < Q->First->skalaPrioritas) {
        P->next = Q->First;
        Q->First = P;
        return;
    }
    
    // Cari posisi yang tepat berdasarkan prioritas
    addressPeminjam current = Q->First;
    while (current->next != NULL && current->next->skalaPrioritas <= P->skalaPrioritas) {
        current = current->next;
    }
    
    // Sisipkan P di posisi yang tepat
    P->next = current->next;
    current->next = P;
}

addressPeminjam DequeueFirst(Queue *Q) {
    if (isEmptyQueue(*Q)) {
        return NULL;
    }
    
    addressPeminjam temp = Q->First;
    Q->First = Q->First->next;
    temp->next = NULL;
    return temp;
}

void DeleteListPeminjam(Queue *Q) {
    addressPeminjam temp;
    while (Q->First != NULL) {
        temp = Q->First;
        Q->First = Q->First->next;
        free(temp);
    }
}

int NbElmtQueue(Queue Q) {
    int count = 0;
    addressPeminjam P = Q.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

void Enqueue(Queue *Q, const char *namaPeminjam, int skalaPrioritas) {
    addressPeminjam P = CreatePeminjam(namaPeminjam, skalaPrioritas);
    if (P == NULL) return;
    
    EnqueueWithPriority(Q, P);
}

void Dequeue(Queue *Q, const char *namaPeminjam) {
    if (isEmptyQueue(*Q)) {
        return;
    }
    
    // Jika elemen pertama adalah yang dicari
    if (strcmp(Q->First->nama, namaPeminjam) == 0) {
        addressPeminjam temp = Q->First;
        Q->First = Q->First->next;
        free(temp);
        return;
    }
    
    // Cari elemen dalam antrian
    addressPeminjam prev = Q->First;
    addressPeminjam curr = prev->next;
    
    while (curr != NULL) {
        if (strcmp(curr->nama, namaPeminjam) == 0) {
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
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
boolean isEmptyPeminjaman(ListPeminjaman L) {
    return (L.First == NULL);
}

// ================== OPERASI DASAR ====================
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

