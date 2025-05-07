/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "array.h"
#include <stdlib.h>
#include <stdbool.h>  // Pastikan boolean tersedia jika tidak ada di "boolean.h"

/* *** Konstruktor *** */
void Inisialisasi_Array(ArrayBuku *arr) {
    arr->jumlahBuku = 0;
}

/* *** Operator *** */
void Tambah_Buku(ArrayBuku *arr, char *judulBuku, int stok, addressPeminjam antrianPeminjam) {
    if (arr->jumlahBuku < MAX_BUKU) {
        strncpy(arr->data[arr->jumlahBuku].judulBuku, judulBuku, MAXSIZE - 1);
        arr->data[arr->jumlahBuku].judulBuku[MAXSIZE - 1] = '\0';  // Pastikan string berakhir null
        arr->data[arr->jumlahBuku].stok = stok;
        arr->data[arr->jumlahBuku].antrianPeminjam = antrianPeminjam;
        arr->jumlahBuku++;
    } else {
        printf("Array penuh, tidak bisa menambahkan buku baru.\n");
    }
}

void Hapus_Buku(ArrayBuku *arr, int index) {
    if (index >= 0 && index < arr->jumlahBuku) {
        for (int i = index; i < arr->jumlahBuku - 1; i++) {
            arr->data[i] = arr->data[i + 1];
        }
        arr->jumlahBuku--;
    } else {
        printf("Indeks tidak valid.\n");
    }
}

void Cari_Buku(ArrayBuku *arr, char *judulBuku, int *index) {
    *index = -1;
    for (int i = 0; i < arr->jumlahBuku; i++) {
        if (strcmp(arr->data[i].judulBuku, judulBuku) == 0) {
            *index = i;
            return;
        }
    }
}

void Tampilkan_Buku(ArrayBuku arr) {
    if (arr.jumlahBuku == 0) {
        printf("Array kosong.\n");
    } else {
        for (int i = 0; i < arr.jumlahBuku; i++) {
            printf("Buku: %s (Stok: %d)\n", arr.data[i].judulBuku, arr.data[i].stok);
            // Jika ingin menampilkan antrian peminjam, tambahkan kode di sini
        }
    }
}

void Ubah_Judul_Buku(ArrayBuku *arr, int index, char *judulBaru) {
    if (index >= 0 && index < arr->jumlahBuku) {
        strncpy(arr->data[index].judulBuku, judulBaru, MAXSIZE - 1);
        arr->data[index].judulBuku[MAXSIZE - 1] = '\0';
    } else {
        printf("Indeks tidak valid.\n");
    }
}

void Ubah_Stok_Buku(ArrayBuku *arr, int index, int stokBaru) {
    if (index >= 0 && index < arr->jumlahBuku) {
        arr->data[index].stok = stokBaru;
    } else {
        printf("Indeks tidak valid.\n");
    }
}

void Urutkan_Buku(ArrayBuku *arr) {
    for (int i = 0; i < arr->jumlahBuku - 1; i++) {
        for (int j = i + 1; j < arr->jumlahBuku; j++) {
            if (strcmp(arr->data[i].judulBuku, arr->data[j].judulBuku) > 0) {
                buku temp = arr->data[i];
                arr->data[i] = arr->data[j];
                arr->data[j] = temp;
            }
        }
    }
}

void Hapus_Semua_Buku(ArrayBuku *arr) {
    arr->jumlahBuku = 0;
}


