/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "queue.h"
#include <stdlib.h>

// Memeriksa apakah queue kosong
boolean isEmptyQueue(ListPeminjam Q) {
    return (Q.front == NULL);
}

// Membuat queue kosong
void CreateQueue(ListPeminjam *Q) {
    Q->front = NULL;
    Q->rear = NULL;
}

// Menghapus node queue dari memori
void DeAlokasiQueue(addressPeminjam *p) {
    if (*p != NULL) {
        free(*p);
        *p = NULL;
    }
}

// Menambahkan elemen baru ke dalam queue dengan prioritas
void Enqueue(ListPeminjam *Q, const char *nama, int skalaPrioritas) {
    addressPeminjam PNew = (addressPeminjam)malloc(sizeof(daftarPeminjam));
    if (PNew == NULL) {
        printf("Gagal mengalokasikan memori untuk peminjam.\n");
        return;
    }
    strcpy(PNew->namaPeminjam, nama);
    PNew->skalaPrioritas = skalaPrioritas;
    PNew->next = NULL;

    // Jika queue kosong, elemen pertama langsung jadi front dan rear
    if (isEmptyQueue(*Q)) {
        Q->front = PNew;
        Q->rear = PNew;
    } else {
        addressPeminjam temp = Q->front;
        addressPeminjam prev = NULL;

        // Menyisipkan berdasarkan prioritas
        while (temp != NULL && temp->skalaPrioritas <= skalaPrioritas) {
            prev = temp;
            temp = temp->next;
        }

        // Menyisipkan elemen di posisi yang sesuai
        if (prev == NULL) {  // Insert at the front
            PNew->next = Q->front;
            Q->front = PNew;
        } else if (temp == NULL) {  // Insert at the rear
            prev->next = PNew;
            Q->rear = PNew;
        } else {  // Insert in the middle
            prev->next = PNew;
            PNew->next = temp;
        }
    }
}

// Menghapus elemen dari depan queue dan menyimpannya ke X
void Dequeue(ListPeminjam *Q, const char *namaPeminjam) {
    if (isEmptyQueue(*Q)) {
        printf("Antrian kosong.\n");
        return;
    }

    addressPeminjam prev = NULL;
    addressPeminjam curr = Q->front;

    // Mencari peminjam dengan nama yang sesuai
    while (curr != NULL && strcmp(curr->namaPeminjam, namaPeminjam) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Peminjam %s tidak ditemukan dalam antrian.\n", namaPeminjam);
        return;
    }

    // Jika peminjam ditemukan di awal queue
    if (prev == NULL) {
        Q->front = curr->next;
        if (Q->front == NULL) {
            Q->rear = NULL;
        }
    } else {
        // Jika peminjam ditemukan di tengah atau akhir queue
        prev->next = curr->next;
        if (curr == Q->rear) {
            Q->rear = prev;
        }
    }

    DeAlokasiQueue(&curr);
}

// Mengembalikan jumlah elemen dalam queue
int NbElmtQueue(ListPeminjam Q) {
    int count = 0;
    addressPeminjam P = Q.front;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

// Menampilkan isi queue dari depan ke belakang
void TampilQueue(ListPeminjam Q) {
    addressPeminjam P = Q.front;
    if (P == NULL) {
        printf("Queue kosong.\n");
    } else {
        printf("Isi Queue:\n");
        while (P != NULL) {
            printf("%s (Prioritas: %d) -> ", P->namaPeminjam, P->skalaPrioritas);
            P = P->next;
        }
        printf("NULL\n");
    }
}

// Mengembalikan nilai elemen terdepan tanpa menghapusnya
char *Front(ListPeminjam Q) {
    if (!isEmptyQueue(Q)) {
        return Q.front->namaPeminjam;
    }
    return NULL;
}

// Mengembalikan nilai elemen terakhir dalam queue tanpa menghapusnya
char *Rear(ListPeminjam Q) {
    if (!isEmptyQueue(Q)) {
        return Q.rear->namaPeminjam;
    }
    return NULL;
}

// Menambahkan elemen Dosen (prioritas pertama) ke dalam queue
void EnqueueDosen(ListPeminjam *Q, const char *nama) {
    Enqueue(Q, nama, 1);  // Dosen memiliki prioritas tertinggi
}

// Menambahkan elemen Mahasiswa (prioritas kedua) ke dalam queue
void EnqueueMahasiswa(ListPeminjam *Q, const char *nama) {
    Enqueue(Q, nama, 2);  // Mahasiswa memiliki prioritas kedua
}

// Menambahkan elemen Masyarakat Umum (prioritas ketiga) ke dalam queue
void EnqueueMasyarakat(ListPeminjam *Q, const char *nama) {
    Enqueue(Q, nama, 3);  // Masyarakat Umum memiliki prioritas ketiga
}

// Mencari peminjam berdasarkan nama dalam queue
addressPeminjam SearchPeminjam(ListPeminjam Q, const char *namaPeminjam) {
    addressPeminjam P = Q.front;
    while (P != NULL) {
        if (strcmp(P->namaPeminjam, namaPeminjam) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Menghapus semua elemen dalam queue peminjam
void DeleteListPeminjam(ListPeminjam *Q) {
    addressPeminjam temp;
    while (!isEmptyQueue(*Q)) {
        temp = Q->front;
        Q->front = Q->front->next;
        DeAlokasiQueue(&temp);
    }
    Q->front = NULL;
    Q->rear = NULL;
}

