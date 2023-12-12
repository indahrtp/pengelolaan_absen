/*--------------------------------------------------*/
/* File        : absensi.c			    			*/
/* Deskripsi   : Kontrol Program Pengelolaan Absensi*/
/* Dibuat oleh : Indah & Yani                       */
/* Tanggal     : 05/12/2023 (revisi)                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include "absensi.h"


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
    int i = 0;
    while (1) {
        char c = getch(); // Menggunakan getch() dari <conio.h> untuk menyembunyikan karakter
        if (c == 13) { // 13 adalah kode ASCII untuk tombol "Enter"
            inputPassword[i] = '\0';
            break;
        } else if (c == 8 && i > 0) { // 8 adalah kode ASCII untuk tombol "Backspace"
            printf("\b \b"); // Untuk menghapus karakter dari tampilan konsol
            i--;
        } else if (c != 8) {
            inputPassword[i] = c;
            putchar('*'); // Mengganti karakter yang ditampilkan dengan '*'
            i++;
        }
    }

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

void buatFileNIM(const char *nim)
{
    char filename[15];
    sprintf(filename, "%s.dat", nim);
    FILE *nimFile = fopen(filename, "w");

    if (!nimFile)
    {
        printf("Error: File %s tidak dapat dibuat.\n", filename);
        return;
    }

    fclose(nimFile);
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
    getchar(); // Membersihkan buffer keyboard
    printf("\t\t\t Masukkan Nama Mahasiswa: ");
    fgets(data.namaMhs, sizeof(data.namaMhs), stdin);
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
    printf("\t\t\t Masukkan Password: ");
    scanf("%s", data.password);
    getchar(); // Membersihkan buffer keyboard
    printf("\t\t\t Masukkan Alamat: ");
    fgets(data.alamat, sizeof(data.alamat), stdin);
    printf("\t\t\t Masukkan Jurusan: ");
    fgets(data.jurusan, sizeof(data.jurusan), stdin);
    printf("\t\t\t Masukkan Prodi: ");
    fgets(data.prodi, sizeof(data.prodi), stdin);
	
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
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
	while (getchar() != '\n'); // Membersihkan buffer input
	getchar();
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

void login(Jadwal *jadwal, int numMatkul) {
    char nim[100];
    char password[100];

    system("cls");
    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|               Login Mahasiswa              |\n");
    printf("\t\t\t----------------------------------------------\n\n");
    printf("\t\t\t Masukkan NIM: ");
    scanf("%s", nim);
    printf("\t\t\t Masukkan password: ");
    int i = 0;
    while (1) {
        char c = getch(); // Menggunakan getch() dari <conio.h> untuk menyembunyikan karakter
        if (c == 13) { // 13 adalah kode ASCII untuk tombol "Enter"
            password[i] = '\0';
            break;
        } else if (c == 8 && i > 0) { // 8 adalah kode ASCII untuk tombol "Backspace"
            printf("\b \b"); // Untuk menghapus karakter dari tampilan konsol
            i--;
        } else if (c != 8) {
            password[i] = c;
            putchar('*'); // Mengganti karakter yang ditampilkan dengan '*'
            i++;
        }
    }

    FILE *file = fopen("mhs.dat", "r");
    if (file == NULL) {
        printf("Error membuka file mhs.dat\n");
        exit(1);
    }

    int numMahasiswas = 0;
    Mahasiswa *mahasiswas = (Mahasiswa *)malloc(sizeof(Mahasiswa));
    if (mahasiswas == NULL) {
        printf("Error dalam alokasi memori\n");
        exit(1);
    }

    int found = 0;

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", mahasiswas[numMahasiswas].namaMhs,
                  mahasiswas[numMahasiswas].nimMhs, mahasiswas[numMahasiswas].password,
                  mahasiswas[numMahasiswas].alamat, mahasiswas[numMahasiswas].jurusan,
                  mahasiswas[numMahasiswas].prodi) != EOF) {
        numMahasiswas++;

        Mahasiswa *temp = (Mahasiswa *)realloc(mahasiswas, (numMahasiswas + 1) * sizeof(Mahasiswa));
        if (temp == NULL) {
            printf("Error dalam alokasi memori\n");
            exit(1);
        } else {
            mahasiswas = temp;
        }

        if (strcmp(nim, mahasiswas[numMahasiswas - 1].nimMhs) == 0 &&
            strcmp(password, mahasiswas[numMahasiswas - 1].password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);
    printf("%d", found);

    if (found) {
        studentView(nim, mahasiswas, numMahasiswas, jadwal, numMatkul);
    } else {
        printf("Login gagal. NIM atau password salah.\n");
    }

    free(mahasiswas);
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
	while (getchar() != '\n'); // Membersihkan buffer input
	getchar();
}


void absensi(char nim[], Mahasiswa *mahasiswas, int numMahasiswas, Jadwal *jadwal, int numMatkul) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char currentDay[100];
    strftime(currentDay, sizeof(currentDay), "%A", tm_info);

    int currentHour = tm_info->tm_hour;
    int currentMin = tm_info->tm_min;

    int i;
    int mahasiswaIndex = findMahasiswaIndex(nim, mahasiswas, numMahasiswas);

    char currentDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", tm_info);

    char waktu[9];
    strftime(waktu, sizeof(waktu), "%T", tm_info);

    int validasi;

    for (i = 0; i < numMatkul; i++) {
        if (strcmp(currentDay, jadwal[i].hari) == 0) {
            if ((currentHour > jadwal[i].jamAwal_hour || (currentHour == jadwal[i].jamAwal_hour && currentMin >= jadwal[i].jamAwal_min)) &&
                (currentHour < jadwal[i].jamAkhir_hour || (currentHour == jadwal[i].jamAkhir_hour && currentMin <= jadwal[i].jamAkhir_min))) {

                validasi = isAbsensiAlreadyDone(nim, jadwal[i].matkul, currentDate);

                if (validasi == 1) {
                    printf("\n\t\t\tMahasiswa %s telah melakukan absensi matkul %s pada tanggal %s.\n", mahasiswas[mahasiswaIndex].namaMhs, jadwal[i].matkul, currentDate);
                    printf("\t\t\tAnda masih dalam rentang waktu mata kuliah %s.\n", jadwal[i].matkul);
                    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
					while (getchar() != '\n'); // Membersihkan buffer input
					getchar();
					return;
                }

                char status[100];
                system("cls");
			    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
			    printf("\t\t\t|                Absensi Mahasiswa                  |\n");
			    printf("\t\t\t----------------------------------------------\n");
			    printf("\t\t\tAbsensi untuk mata kuliah %s\n", jadwal[i].matkul);
			    printf("\t\t\t----------------------------------------------\n");
			    printf("\t\t\t1. Hadir\n");
			    printf("\t\t\t2. Sakit\n");
			    printf("\t\t\t3. Izin\n");
			    
			    printf("\t\t\t Mark Absensi : ");
                int selectedOption;
                scanf("%d", &selectedOption);

                int minutesLate = (currentHour - jadwal[i].jamAwal_hour) * 60 + (currentMin - jadwal[i].jamAwal_min);

                switch (selectedOption) {
                    case 1:
                        if (minutesLate > 15) {
                            strcpy(status, "Telat");
                        } else {
                            strcpy(status, "Hadir");
                        }
                        break;
                    case 2:
                        strcpy(status, "Sakit");
                        break;
                    case 3:
                        strcpy(status, "Izin");
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                        return;
                }

                saveAbsensi(nim, currentDate, waktu, status, jadwal[i].matkul);

                printf("\t\t\tAbsensi berhasil disimpan.\n");
                printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
				while (getchar() != '\n'); // Membersihkan buffer input
				getchar();
                return;
            }
        }
    }

    printf("\t\t\tTidak ada mata kuliah yang sesuai dengan jadwal saat ini.\n");
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
	while (getchar() != '\n'); // Membersihkan buffer input
	getchar();
}

void saveAbsensi(char nim[], char tanggal[], char waktu[], char status[], char matkul[]) {
    char fileName[100];
    sprintf(fileName, "%s.dat", nim);

    FILE *absensiFile = fopen(fileName, "a");
    if (absensiFile == NULL) {
        printf("Error membuka file absensi\n");
        exit(1);
    }

    int result = fprintf(absensiFile, "%s %s %s %s\n", tanggal, waktu, status, matkul);
    if (result < 0) {
        printf("Error menulis ke file absensi\n");
        exit(1);
    }

    fclose(absensiFile);
}

void readAbsensi(char nim[]) {
    char fileName[100];
    sprintf(fileName, "%s.dat", nim);

    FILE *absensiFile = fopen(fileName, "r");
    if (absensiFile == NULL) {
        printf("Error membuka file absensi\n");
        exit(1);
    }

    char currentTanggal[11];
    char status[100];
    char currentMatkul[100];
    while (fscanf(absensiFile, "%s %s %[^\n]\n", currentTanggal, status, currentMatkul) != EOF) {
        printf("%s - %s - %s\n", currentTanggal, status, currentMatkul);
    }

    fclose(absensiFile);
}

int findMahasiswaIndex(char nim[], Mahasiswa *mahasiswas, int numMahasiswas) {
    int i;
    for (i = 0; i < numMahasiswas; i++) {
        if (strcmp(nim, mahasiswas[i].nimMhs) == 0) {
            return i;
        }
    }
    return -1;
}

int isAbsensiAlreadyDone(char nim[], char matkul[], char currentDate[]) {
    char fileName[100];
    sprintf(fileName, "%s.dat", nim);

    FILE *absensiFile = fopen(fileName, "r");
    if (absensiFile == NULL) {
        return 0;
    }

    char currentMatkul[100];
    char currentTanggal[11];
    char status[100];

    while (fscanf(absensiFile, "%s %s %[^\n]\n", currentTanggal, status, currentMatkul) != EOF) {
        if (strcmp(currentMatkul, matkul) == 0 && strcmp(currentTanggal, currentDate) == 0) {
            fclose(absensiFile);
            return 1;
        }
    }

    fclose(absensiFile);
    return 0;
}

void printCurrentMatkul(Jadwal *jadwal, int currentMatkulIndex) {
    printf("Sedang berlangsung mata kuliah %s pada jam %02d:%02d - %02d:%02d\n", jadwal[currentMatkulIndex].matkul,
           jadwal[currentMatkulIndex].jamAwal_hour, jadwal[currentMatkulIndex].jamAwal_min,
           jadwal[currentMatkulIndex].jamAkhir_hour, jadwal[currentMatkulIndex].jamAkhir_min);
}

void tampilRiwayatAbsensi(const char *nim) {
	Absensi absensi;
	Jadwal jadwal;
    char filename[15];
    
    sprintf(filename, "%s.dat", nim);
    FILE *absenFile = fopen(filename, "r");

    if (!absenFile) {
        printf("Error: File %s tidak dapat dibuka.\n", filename);
        return;
    }
	
	system("cls");
    printf("\n\n\n\n\t\t\t----------------------------------------------\n");
    printf("\t\t\t|         Riwayat Absensi Mahasiswa          |\n");
    printf("\t\t\t----------------------------------------------\n\n");
    printf("\t\t\t%-12s%-10s%-10s\n", "Tanggal", "Status", "Mata Kuliah");
    printf("\t\t\t----------------------------------------------\n");

    while (fscanf(absenFile, "%s %s %[^\n]", absensi.tanggal, absensi.status, jadwal.matkul) == 3) {
        printf("\t\t\t%-12s%-10s%-10s\n", absensi.tanggal, absensi.status, jadwal.matkul);
    }

    fclose(absenFile);
    printf("\n\n\t\t\tTekan tombol apa pun untuk melanjutkan...\n");
    while (getchar() != '\n'); // Membersihkan buffer input
    getchar();
}

void studentView(char nim[], Mahasiswa *mahasiswas, int numMahasiswas, Jadwal *jadwal, int numMatkul) {
    system("cls");
    int goBack = 0;
    int pilihan;

    while (1) {
        system("cls");
        printf("\n\n\n\n\t\t\t----------------------------------------------\n");
        printf("\t\t\t|                Absensi Mahasiswa                  |\n");
        printf("\t\t\t----------------------------------------------\n\n");
        printf("\t\t\t1. Absensi\n");
        printf("\t\t\t2. Lihat Riwayat Absen\n");
        printf("\t\t\t0. Kembali\n");

        printf("\t\t\tMasukkan pilihanmu : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                absensi(nim, mahasiswas, numMahasiswas, jadwal, numMatkul);
                break;
            case 2:
                tampilRiwayatAbsensi(nim);
                break;
            case 0:
                goBack = 1;
                break;
            default:
                printf("\t\t\t\nPilihan tidak valid. Masukkan pilihan lagi!");
                getchar();
        }

        if (goBack == 1) {
            break;
        }
    }
}
