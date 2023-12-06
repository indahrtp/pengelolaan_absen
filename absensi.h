/*--------------------------------------------------*/
/* File        : absensi.h	    					*/
/* Deskripsi   : Header ADT Buruh				    */
/* Dibuat oleh : Indah & Yani                  	    */
/* Tanggal     : 5/12/2023 (revisi)				    */

#ifndef absensi_h
#define absensi_h

// Struktur untuk data mahasiswa
typedef struct {
    char namaMhs[50];
    char nimMhs[10];
    char password[10];
    char alamat[100];
    char jurusan[30];
    char prodi[50];
} Mahasiswa;

// Struktur untuk data admin
typedef struct {
    char username[20];
    char password[20];
} Admin;

// Fungsi untuk login admin
int adminLogin();

//Fungsi untuk tampilan admin
int adminView();

// Prosedur untuk register mahasiswa
void registerMahasiswa();

// Prosedur untuk mencari mahasiswa berdasarkan NIM
void searchMahasiswa();

// Prosedur untuk menampilkan data mahasiswa keseluruhan pada file mhs.dat
void displayAllMahasiswa();

// Prosedur untuk menghapus data mahasiswa berdasarkan NIM
void deleteMahasiswa();

#endif
