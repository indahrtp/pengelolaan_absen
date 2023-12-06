/*--------------------------------------------------*/
/* File        : absensi.c						              */
/* Deskripsi   : Kontrol Program Pengelolaan Absensi*/
/* Dibuat oleh : Indah & Yani                       */
/* Tanggal     : 05/12/2023 (revisi)                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "absensi.h"

void date()
{
  time_t T = time(NULL);
  struct tm = *localtime(&T);
  printf("\n\n\n");
  printf("\t\t\t\t\t  Date:%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

// Fungsi untuk login admin
int adminLogin()
{
    Admin admin;
    char inputUsername[20];
    char inputPassword[20];

    printf("Masukkan username admin: ");
    scanf("%s", inputUsername);
    printf("Masukkan password admin: ");
    scanf("%s", inputPassword);

    FILE *adminFile = fopen("admin.dat", "r");
    if (!adminFile)
    {
        printf("Error: File admin.dat tidak dapat dibuka.\n");
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
    Mahasiswa data;

    printf("\n ---- Form untuk Pendaftaran Mahasiswa ----- \n\n");
    printf(" Masukkan Nama Mahasiswa: ");
    scanf("%s", data.namaMhs);
	printf(" Masukkan NIM: ");
    scanf("%s", data.nimMhs);
    printf(" Masukkan Password: ");
    scanf("%s", data.password);
    getchar(); // Membersihkan buffer keyboard
    printf(" Masukkan Alamat: ");
    fgets(data.alamat, sizeof(data.alamat), stdin);
    printf(" Masukkan Jurusan: ");
    scanf("%s", data.jurusan);
    printf(" Masukkan Prodi: ");
    scanf("%s", data.prodi);

    FILE *mhsFile = fopen("mhs.dat", "a");
    if (!mhsFile)
    {
        printf("Error: File mhs.dat tidak dapat dibuka.\n");
        return;
    }

    fprintf(mhsFile, "%s|%s|%s|%s|%s|%s\n", data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi);
    fclose(mhsFile);

    printf("Registrasi berhasil!!\n");
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM
void searchMahasiswa()
{
    char searchNIM[10];
    Mahasiswa data;

    printf("Masukkan NIM mahasiswa yang ingin dicari: ");
    scanf("%s", searchNIM);

    FILE *mhsFile = fopen("mhs.dat", "r");
    if (!mhsFile)
    {
        printf("Error: File mhs.dat tidak dapat dibuka.\n");
        return;
    }

    while (fscanf(mhsFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi) == 6)
    {
        if (strcmp(searchNIM, data.nimMhs) == 0)
        {
            printf("\n--- Data Mahasiswa ---\n");
            printf("Nama     : %s\n", data.namaMhs);
            printf("NIM      : %s\n", data.nimMhs);
            printf("Password : %s\n", data.password);
            printf("Alamat   : %s\n", data.alamat);
            printf("Jurusan  : %s\n", data.jurusan);
            printf("Prodi    : %s\n", data.prodi);
            fclose(mhsFile);
            return;
        }
    }

    fclose(mhsFile);
    printf("Mahasiswa dengan NIM %s tidak ditemukan.\n", searchNIM);
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void deleteMahasiswa()
{
    char deleteNIM[10];
    Mahasiswa data;

    printf("Masukkan NIM mahasiswa yang ingin dihapus: ");
    scanf("%s", deleteNIM);

    FILE *mhsFile = fopen("mhs.dat", "r");
    if (!mhsFile)
    {
        printf("Error: File mhs.dat tidak dapat dibuka.\n");
        return;
    }

    // Membuat file temporary untuk menyimpan data selain yang akan dihapus
    FILE *tempFile = fopen("temp.dat", "w");
    if (!tempFile)
    {
        printf("Error: File temp.dat tidak dapat dibuka.\n");
        fclose(mhsFile);
        return;
    }

    int found = 0;

    while (fscanf(mhsFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  data.namaMhs, data.nimMhs, data.password, data.alamat, data.jurusan, data.prodi) == 6)
    {
        if (strcmp(deleteNIM, data.nimMhs) == 0)
        {
            found = 1;
            printf("\n--- Data Mahasiswa yang dihapus ---\n");
            printf("Nama     : %s\n", data.namaMhs);
            printf("NIM      : %s\n", data.nimMhs);
            printf("Password : %s\n", data.password);
            printf("Alamat   : %s\n", data.alamat);
            printf("Jurusan  : %s\n", data.jurusan);
            printf("Prodi    : %s\n", data.prodi);
            printf("\nData mahasiswa dengan NIM %s berhasil dihapus.\n", deleteNIM);
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
        printf("Mahasiswa dengan NIM %s tidak ditemukan.\n", deleteNIM);
    }
}

//Fungsi untuk tampilan admin
int adminView()
{
  int goBack = 0;
  while (1)
  {
    system("cls");
    date();
    printf("\n\n\nPilih satu opsi\n");
    printf("-------------------------------");
    printf("\n1. Registrasi Mahasiswa");
    printf("\n2. Hapus Mahasiswa Terdaftar Berdasarkan NIM");
    printf("\n3. List Mahasiswa Terdaftar Berdasarkan NIM");
    printf("\n4. Cari Mahasiswa Berdasarkan NIM");
    printf("\n5. Hapus Semua Data Mahasiswa");
    printf("\n0. Kembali\n");

    int pilihan;
    printf("\nMasukkan pilihanmu : ");
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
            getListOfStudentsRegistered();
            break;
        case 4:
            searchMahasiswa();
            break;
        case 0;
            goBack = 1;
            break;
        default:
            printf("\nPilihan tidak valid. Masukkan pilihan lagi!");
            getchar();
      }
      if (goBack == 1)
      {
        break;
      }
  }
  return 0;
}
