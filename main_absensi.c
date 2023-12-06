#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "absensi.h"

int main()
{
	int choice;
	int login;
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
        	login=adminLogin();
            if (login==1)
            {
            	adminView();
        	}
			else
            {
                printf("\t\t\tLogin admin gagal. Silakan coba lagi.\n");
            }
            break;
        case 2:
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
