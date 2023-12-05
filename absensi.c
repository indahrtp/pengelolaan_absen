/*--------------------------------------------------*/
/* File			: absensi.c						                  */
/* Deskripsi	: Header ADT Buruh					*/
/* Dibuat oleh	: Indah	Ratu Pramudita/231511050	*/
/* Tanggal		: 22/11/2023 (revisi)				*/

#include<stdio.h>

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
