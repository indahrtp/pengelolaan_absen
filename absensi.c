/*--------------------------------------------------*/
/* File        : absensi.c						              */
/* Deskripsi   : Kontrol Program Pengelolaan Absensi*/
/* Dibuat oleh : Indah & Yani                       */
/* Tanggal     : 05/12/2023 (revisi)                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void date()
{
  time_t T = time(NULL);
  struct tm = *localtime(&T);
  printf("\n\n\n");
  printf("\t\t\t\t\t  Date:%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

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
    printf("\n2. Cek Mahasiswa Terdaftar");
    printf("\n3. Hapus Semua Mahasiswa Terdaftar");
    printf("\n4. List Mahasiswa Terdaftar Berdasarkan NIM");
    printf("\n5. Hapus Semua Data Mahasiswa");
    printf("\n0. Kembali\n");

    int pilihan;
    printf("\nMasukkan pilihanmu : ");
    scanf("%d", &pilihan);
    
    switch(pilihan)
      {
        case 1:
            registerStudent();
            break;
        case 2:
            checkListOfStudentsRegistered();
            break;
        case 3:
            deleteAllStudents();
            break;
        case 4:
            getListOfStudentsRegistered();
            break;
        case 5:
            deleteStudentAllData();
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

void registerStudent()
{
  FILE* read;
  FILE* out;
  FILE* out1;
  mahasiswa data;
  int totalData;
  int found = 0;
  char line[100];
  
  printf("\n ---- Form untuk Pendaftaran Mahasiswa ----- \n\n");
  printf("\n Masukkan Nama Mahasiswa: ");
  scanf("%s", data.namaMhs);
  printf("\n Masukkan NIM: ");
  scanf("%s", data.nimMhs);
  printf("\n Masukkan Password: ");
  scanf("%s", data.password);
  getchar();
  printf("\n Masukkan Alamat: ");
  fgets(data.alamat, sizeof(data.alamat), stdin);
  printf("\n Masukkan Jurusan: ");
  scanf("%s", data.jurusan);
  printf("\n Masukkan Prodi: ");
  scanf("%s", data.prodi);

  //Mengecek Apakah ada data yang sama
  read = fopen("mhs.dat", "r");
  if (read)
  {
    while (fgets(line, sizeof(line), read))
      {
        if (strcmp(line, data.nimMhs) == 0)
        {
          found = 1;
          break;
        }
      }
    if (found == 1)
    {
      printf("\nNIM telah terdaftar. Tolong cek kembali NIM");
      getchar();
      getchar();
      fclose(read);
    }
  }
  fclose(read);

  out = fopen("mhs.dat", "a");
  fprintf(out, "%s.dat\n", data.nimMhs);
  fclose(out);

  out1 = fopen(strcat(data.nimMhs, ".dat"), "w");
  if (out1)
  {
    fprintf(out1, "%s\n", data.namaMhs);
    fprintf(out1, "%s\n", data.nimMhs);
    fprintf(out1, "%s\n", data.password);
    fprintf(out1, "%s\n", data.alamat);
    fprintf(out1, "%s\n", data.jurusan);
    fprintf(out1, "%s\n", data.prodi);
    fclose(out1);
  }
  printf("\nRegistrasi berhasil!!"\n);
  printf("\nKetik apapun untuk melanjutkan ...");
  getchar();
  getchar();
}

int getListOfStudentsRegistered()
{
  DIR* di;
  char* ptr1, *ptr2, nama;
  int retn, hasil;
  struct dirent* dir;
  di = opendir(".");
  if (di)
  {
    printf("\n\n--------Daftar Mahasiswa Berdasarkan NIM--------\n\n");
    while ((dir = readdir(di)) != NULL)
      {
        ptr1 = strtok(dir->d_nama, ".");
        ptr2 = strtok(NULL, ".");
        if (ptr2 != NULL)
        {
          retn = strcmp(ptr2, "dat");
          if (retn == 0)
          {
            printf("\n\n");
            printf("%s\t", ptr1);
            printf("\n\n");
          }
        }
      }
    closedir(dir);
  }
}
printf("Klik mana saja untuk melanjutkan ...");
getchar();
getchar();
return 0;

int deleteAllStudents()
{
  printf("\n\n--------Hapus Semua Mahasiswa Terdaftar--------\n\n")
  printf("Menghapus");
  for (int process = 0; process < 25; process++)
    {
      printf(".");
    }
  remove("db.dat");
  remove("application.dat");
  printf("\n\nSemua Mahasiswa Terdaftar Berhasil Dihapus");
  printf("\n\nKlik mana saja untuk melanjutkan ...");
  getchar();
  getchar();
  return 0;
}

int deleteStudentAllData()
{
  system("cls");
  DIR * di;
  char* ptr1, *ptr2;
  char nama[50];
  int retn;
  int status;
  struct dirent* dir;
  di = opendir(".");
  if (di)
  {
    printf("\n\n--------Daftar Data Mahasiswa--------\n\n");
    while((dir = readdir(di)) != NULL)
      {
        ptr1 = strtok(dir->d_name, ".");
        ptr2 = strtok(NULL, ".");
        if (ptr2 != NULL)
        {
          retn = strcmp(ptr2, "dat");
          if (retn == 0)
          {
            printf("\n");
            printf("%s", ptr1);
            printf(".dat");
            printf("\n\n");
          }
        }
      }
    closedir(di);
  }
  printf("\n\nKetikkan nama dari file yang akan dihapus : ");
  scanf("%s", nama);
  status = remove(nama);
  if (status == 0)
    printf("\nFile Berhasil Dihapus!");
  else
  {
    printf("\n\nTerjadi Kesalahan!");
    printf("\n\nMasukan data yang valid");
  }
  printf("\n\nKlik mana saja untuk melanjutkanv...");
  getchar();
  getchar();
  return 0;
}
