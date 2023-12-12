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

// Struktur untuk data absensi
typedef struct {
    char hari[15];
    char tanggal[15];
    int jamAbsen;
    int menitAbsen;
    char status[10];
    int presentase;
} Absensi;

typedef struct {
    char hari[100];
    int jamAwal_hour, jamAwal_min, jamAwal_sec;
    int jamAkhir_hour, jamAkhir_min, jamAkhir_sec;
    char matkul[100];
} Jadwal;

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

void recapAbsensi();

void login(Jadwal *jadwal, int numMatkul);

void absensi(char nim[], Mahasiswa *mahasiswas, int numMahasiswas, Jadwal *jadwal, int numMatkul);

void saveAbsensi(char nim[], char tanggal[], char waktu[], char status[], char matkul[]);

void readAbsensi(char nim[]);

int findMahasiswaIndex(char nim[], Mahasiswa *mahasiswas, int numMahasiswas);

int isAbsensiAlreadyDone(char nim[], char matkul[], char currentDate[]);

void printCurrentMatkul(Jadwal *jadwal, int currentMatkulIndex);

void studentView(char nim[], Mahasiswa *mahasiswas, int numMahasiswas, Jadwal *jadwal, int numMatkul);

int validasiNIM(const char *nim);

#endif
