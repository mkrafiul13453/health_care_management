#include "hms.h"

/* RECEPTIONIST: limited access*/
void receptionistMenu(void)
{
    int ch;
    do
    {
        printf("\n========== RECEPTIONIST MENU ============\n");
        printf("1. Register Patient\n");
        printf("2. View All Patients\n");
        printf("3. Appointment Scheduling\n");
        printf("4. Bed/Ward/Cabin Management\n");
        printf("5. Book OT\n");
        printf("6. Billing/Invoicing\n");
        printf("0. Logout\n");
        printf("Choose: ");
        ch = readInt();
        switch (ch)
        {
        case 1:
            registerPatient();
            break;
        case 2:
            viewAllPatients();
            break;
        case 3:
            appointmentMenu();
            break;
        case 4:
            bedMenu();
            break;
        case 5:
            bookOT();
            break;
        case 6:
            billingMenu();
            break;
        case 0:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid option, please try again.\n");
        }
    } while (ch != 0);
}