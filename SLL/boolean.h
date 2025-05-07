/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef BOOLEAN_H
#define BOOLEAN_H

// =====================================================
// ===================== TIPE BOOLEAN ==================
// =====================================================

// Mendefinisikan tipe boolean berdasarkan compiler yang digunakan
#ifdef _MSC_VER
    // Menggunakan tipe boolean dari Windows untuk compiler Microsoft
    #include <windows.h>
#else
    // Mendefinisikan tipe boolean untuk compiler non-Microsoft
    typedef enum { false, true } boolean;
#endif

#endif

