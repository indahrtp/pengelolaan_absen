#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "absensi.h"

int main()
{
	int choice;
	int loginAdm;
	Mahasiswa mhs;
	
	setlocale(LC_TIME, "id_ID.UTF-8");
    FILE *jadwalFile = fopen("jadwal.dat", "r");
    if (jadwalFile == NULL) {
        printf("Error membuka file jadwal.dat\n");
        exit(1);
    }

    int numMatkul = 0;
    Jadwal *jadwal = (Jadwal *)malloc(sizeof(Jadwal));
    if (jadwal == NULL) {
        printf("Error dalam alokasi memori\n");
        exit(1);
    }

    while (fscanf(jadwalFile, "%s %d:%d:%d %d:%d:%d %[^\n]\n", jadwal[numMatkul].hari,
                  &jadwal[numMatkul].jamAwal_hour, &jadwal[numMatkul].jamAwal_min, &jadwal[numMatkul].jamAwal_sec,
                  &jadwal[numMatkul].jamAkhir_hour, &jadwal[numMatkul].jamAkhir_min, &jadwal[numMatkul].jamAkhir_sec,
                  jadwal[numMatkul].matkul) != EOF) {
        numMatkul++;
        
        Jadwal *temp = (Jadwal *)realloc(jadwal, (numMatkul + 1) * sizeof(Jadwal));
        if (temp == NULL) {
            printf("Error dalam alokasi memori\n");
            exit(1);
        } else {
            jadwal = temp;
        }
    }

    fclose(jadwalFile);
    do
    {
	    system("cls");
		printf("\t\t\t-------------------------------------------------------------------------\n");
	    printf("\t\t\t|                              Menu Login                               |\n");
	    printf("\t\t\t-------------------------------------------------------------------------\n\n");
        printf("\n\t\t\t1. Login sebagai Admin\n");
        printf("\t\t\t2. Login sebagai Mahasiswa\n");
        printf("\t\t\t3. Keluar\n");
        printf("\n\t\t\tPilih menu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        	loginAdm = adminLogin();
            if (loginAdm == 1)
            {
            	adminView();
        	}
			else
            {
                printf("\t\t\tLogin admin gagal. Silakan coba lagi.\n");
            }
            break;
        case 2:
        	login(jadwal, numMatkul);
        	break;
        case 3:
            printf("\t\t\tTerima kasih. Program selesai.\n");
            break;
        default:
            printf("\t\t\tPilihan tidak valid. Silakan coba lagi.\n");
            break;
        }

    } while (choice != 3);

    return 0;
}
