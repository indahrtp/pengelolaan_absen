/*--------------------------------------------------*/
/* File        : absensi.h	    					          */
/* Deskripsi   : Header ADT Buruh				          	*/
/* Dibuat oleh : Indah & Yani                  	    */
/* Tanggal     : 5/12/2023 (revisi)				          */

#ifndef absensi_h
#define absensi_h

typedef struct {
    char namaMhs[50];
    char nimMhs[10];
    char password[10];
    char alamat[100];
    char jurusan[30];
    char prodi[30];
} mahasiswa;

/**/
void adminView();

/**/
int loginAdmin();

/**/
void registerStudent();

/**/
int listStudent();

/**/
int search();

/**/
int deleteStudent();

#endif
