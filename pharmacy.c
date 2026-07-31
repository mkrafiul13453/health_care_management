

#include "hms.h"


void pharmacistMenu(void)
{
    int ch;
    do
    {
        printf("\n============ PHARMACIST MENU ============\n");
        printf("1. Add Medicine\n");
        printf("2. View Inventory\n");
        printf("3. Sell Medicine\n");
        printf("4. Damaged Stock Entry\n");
        printf("0. Logout\n");
        printf("Choose: ");
        ch = readInt();
        switch (ch)
        {
        case 1:
            addMedicine();
            break;
        case 2:
            viewInventory();
            break;
        case 3:
            sellMedicine();
            break;
        case 4:
            addDamagedStock();
            break;
        case 0:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid option, please try again.\n");
        }
    } while (ch != 0);
}