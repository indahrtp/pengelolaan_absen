#include <stdio.h>
#include "absensi.h"

int main()
{
    int choice;

    do
    {
        printf("\n ---- Menu Login ---- \n");
        printf("1. Login sebagai Admin\n");
        printf("2. Login sebagai Mahasiswa\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (adminLogin())
            {
            	viewAdmin()
        	}
			else
            {
                printf("Login admin gagal. Silakan coba lagi.\n");
            }
            break;
        case 2:
        	break;
        case 3:
            printf("Terima kasih. Program selesai.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            break;
        }

    } while (choice != 3);

    return 0;
}
