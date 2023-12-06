/*--------------------------------------------------*/
/* File        : absensi.c			    			*/
/* Deskripsi   : Kontrol Program Pengelolaan Absensi*/
/* Dibuat oleh : Indah & Yani                       */
/* Tanggal     : 05/12/2023 (revisi)                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "absensi.h"

//void date()
//{
//  time_t T = time(NULL);
//  struct tm = *localtime(&T);
//  printf("\n\n\n");
//  printf("\t\t\t\t\t  Date:%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
//}

int validasiNIM(const char *nim)
{
    FILE* read = fopen("mhs.dat", "r");
    Mahasiswa data;
    char nimsekarang[10];
    if (read)
    {
        
        while (fscanf(read, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi) == 6)
        {
            if (strcmp(data.nimMhs, nim) == 0)
            {
                fclose(read);
                return 1; // NIM sudah terdaftar
            }
        }
        fclose(read);
    }
    return 0; // NIM belum terdaftar
}

// Fungsi untuk login admin
int adminLogin()
{
    system("cls");
	Admin admin;
    char inputUsername[20];
    char inputPassword[20];

    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|                Login Admin                 |\n");
    printf("\t\t\t----------------------------------------------\n\n");
    printf("\t\t\t Masukkan username admin: ");
    scanf("%s", inputUsername);
    printf("\t\t\t Masukkan password admin: ");
    scanf("%s", inputPassword);

    FILE *adminFile = fopen("admin.dat", "r");
    if (!adminFile)
    {
        printf("\n\t\t\tError: File admin.dat tidak dapat dibuka.\n");
        return 0;
    }

    while (fscanf(adminFile, "%[^|]|%[^\n]\n", admin.username, admin.password) == 2)
    {
        if (strcmp(inputUsername, admin.username) == 0 && strcmp(inputPassword, admin.password) == 0)
        {
            fclose(adminFile);
            return 1; // Login berhasil
        }
    }

    fclose(adminFile);
    return 0; // Login gagal
}

// Fungsi untuk register mahasiswa
void registerMahasiswa()
{
    system("cls");
	Mahasiswa data;
	int validasi;

    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|         Registrasi Data Mahasiswa           |\n");
    printf("\t\t\t----------------------------------------------\n\n");
    printf("\t\t\t Masukkan Nama Mahasiswa: ");
    scanf("%s", data.namaMhs);
    do
    {
        printf("\t\t\t Masukkan NIM: ");
        scanf("%s", data.nimMhs);
        
        validasi = validasiNIM(data.nimMhs);
        if (validasi == 1)
        {
            printf("\n\t\t\t NIM telah terdaftar. Mohon inputkan NIM lain.\n");
        }

    } while (validasi == 1);
    printf("%d", validasi);
    printf("\t\t\t Masukkan Password: ");
    scanf("%s", data.password);
    getchar(); // Membersihkan buffer keyboard
    printf("\t\t\t Masukkan Alamat: ");
    fgets(data.alamat, sizeof(data.alamat), stdin);
    printf("\t\t\t Masukkan Jurusan: ");
    scanf("%s", data.jurusan);
    printf("\t\t\t Masukkan Prodi: ");
    scanf("%s", data.prodi);

    FILE *mhsFile = fopen("mhs.dat", "a");
    if (!mhsFile)
    {
        printf("\t\t\tError: File mhs.dat tidak dapat dibuka.\n");
        return;
    }

    fprintf(mhsFile, "%s|%s|%s|%s|%s|%s\n", data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi);
    fclose(mhsFile);

    printf("\t\t\t Registrasi berhasil!!\n");
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
	while (getchar() != '\n'); // Membersihkan buffer input
	getchar();
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM
void searchMahasiswa()
{
    system("cls");
	char searchNIM[10];
    Mahasiswa data;

	printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|               Cari Mahasiswa               |\n");
    printf("\t\t\t----------------------------------------------\n\n");
    printf("\t\t\tMasukkan NIM mahasiswa yang ingin dicari: ");
    scanf("%s", searchNIM);

    FILE *mhsFile = fopen("mhs.dat", "r");
    if (!mhsFile)
    {
        printf("\t\t\tError: File mhs.dat tidak dapat dibuka.\n");
        return;
    }

    while (fscanf(mhsFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi) == 6)
    {
        if (strcmp(searchNIM, data.nimMhs) == 0)
        {
		    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
		    printf("\t\t\t|           Data Mahasiswa Ditemukan          |\n");
		    printf("\t\t\t----------------------------------------------\n\n");
	            printf("\t\t\tNama     : %s\n", data.namaMhs);
	            printf("\t\t\tNIM      : %s\n", data.nimMhs);
	            printf("\t\t\tPassword : %s\n", data.password);
	            printf("\t\t\tAlamat   : %s\n", data.alamat);
	            printf("\t\t\tJurusan  : %s\n", data.jurusan);
	            printf("\t\t\tProdi    : %s\n", data.prodi);
//	            fclose(mhsFile);
	//            return;
        }
    }

    fclose(mhsFile);
    
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
	while (getchar() != '\n'); // Membersihkan buffer input
	getchar();
    printf("\t\t\tMahasiswa dengan NIM %s tidak ditemukan.\n", searchNIM);
    
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void deleteMahasiswa()
{
    system("cls");
	char deleteNIM[10];
    Mahasiswa data;

    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|              Hapus Mahasiswa               |\n");
    printf("\t\t\t----------------------------------------------\n\n");
	printf("\t\t\tMasukkan NIM mahasiswa yang ingin dihapus: ");
    scanf("%s", deleteNIM);

    FILE *mhsFile = fopen("mhs.dat", "r");
    if (!mhsFile)
    {
        printf("\t\t\tError: File mhs.dat tidak dapat dibuka.\n");
//        return;
    }

    // Membuat file temporary untuk menyimpan data selain yang akan dihapus
    FILE *tempFile = fopen("temp.dat", "w");
    if (!tempFile)
    {
        printf("\t\t\tError: File temp.dat tidak dapat dibuka.\n");
        fclose(mhsFile);
//        return;
    }

    int found = 0;

    while (fscanf(mhsFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi) == 6)
    {
        if (strcmp(deleteNIM, data.nimMhs) == 0)
        {
            found = 1;
		    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
		    printf("\t\t\t|            Hapus Data Mahasiswa             |\n");
		    printf("\t\t\t----------------------------------------------\n\n");
            printf("\t\t\tNama     : %s\n", data.namaMhs);
            printf("\t\t\tNIM      : %s\n", data.nimMhs);
            printf("\t\t\tPassword : %s\n", data.password);
            printf("\t\t\tAlamat   : %s\n", data.alamat);
            printf("\t\t\tJurusan  : %s\n", data.jurusan);
            printf("\t\t\tProdi    : %s\n", data.prodi);
            printf("\n\t\t\tData mahasiswa dengan NIM %s berhasil dihapus.\n", deleteNIM);
        }
        else
        {
            fprintf(tempFile, "%s|%s|%s|%s|%s|%s\n", data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi);
        }
    }

    fclose(mhsFile);
    fclose(tempFile);

    // Menghapus file mhs.dat
    remove("mhs.dat");

    // Mengganti nama file temporary menjadi mhs.dat
    rename("temp.dat", "mhs.dat");

    if (!found)
    {
        printf("\t\t\tMahasiswa dengan NIM %s tidak ditemukan.\n", deleteNIM);
    }
    
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
    while (getchar() != '\n'); // Membersihkan buffer input
	getchar();
}

void displayAllMahasiswa() {
    system("cls");
    Mahasiswa data;

    FILE *mhsFile = fopen("mhs.dat", "r");
    if (!mhsFile) {
        printf("\t\t\tError: File mhs.dat tidak dapat dibuka.\n");
        return;
    }

    printf("\t\t\t--------------------------------------------------------\n");
    printf("\t\t\t|              Semua Data Mahasiswa                    |\n");
    printf("\t\t\t--------------------------------------------------------\n\n");

    while (fscanf(mhsFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi) == 6) {
        printf("\t\t\tNama     : %s\n", data.namaMhs);
        printf("\t\t\tNIM      : %s\n", data.nimMhs);
        printf("\t\t\tPassword : %s\n", data.password);
        printf("\t\t\tAlamat   : %s\n", data.alamat);
        printf("\t\t\tJurusan  : %s\n", data.jurusan);
        printf("\t\t\tProdi    : %s\n", data.prodi);
        printf("\t\t\t--------------------------------------------------------\n");
    }

    fclose(mhsFile);
}


//Fungsi untuk tampilan admin
int adminView()
{
  system("cls");
  int goBack = 0;
  while (1)
  {
    system("cls");
//    date();
    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|                Menu Admin                   |\n");
    printf("\t\t\t----------------------------------------------\n\n");
    printf("\t\t\t1. Registrasi Mahasiswa\n");
    printf("\t\t\t2. Hapus Mahasiswa Terdaftar Berdasarkan NIM\n");
    printf("\t\t\t3. List Mahasiswa Terdaftar Berdasarkan NIM\n");
    printf("\t\t\t4. Cari Mahasiswa Berdasarkan NIM\n");
    printf("\t\t\t0. Kembali\n");

    int pilihan;
    printf("\t\t\tMasukkan pilihanmu : ");
    scanf("%d", &pilihan);
    
    switch(pilihan)
      {
        case 1:
            registerMahasiswa();
            break;
        case 2:
            deleteMahasiswa();
            break;
        case 3:
            displayAllMahasiswa();
            break;
        case 4:
            searchMahasiswa();
            break;
        case 0:
            goBack = 1;
            break;
        default:
            printf("\t\t\t\nPilihan tidak valid. Masukkan pilihan lagi!");
            getchar();
      }
      if (goBack == 1)
      {
        break;
      }
  }
  return 0;
}

