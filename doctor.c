#include "hms.h"

/* ---------------- DOCTOR: limited access ---------------- */
void doctorRoleMenu(void)
{
    int choice;
    do
    {
        printf("\n================ DOCTOR MENU ================\n");
        printf("1. View Assigned Patients (Dashboard)\n");
        printf("2. Add Medical Record\n");
        printf("3. View Medical Records\n");
        printf("4. Request Lab Test\n");
        printf("5. View OT Bookings\n");
        printf("0. Logout\n");
        printf("Choose: ");
        choice = readInt();
        switch (choice)
        {
        case 1:
            doctorDashboard();
            break;
        case 2:
            addMedicalRecord();
            break;
        case 3:
            viewMedicalRecords();
            break;
        case 4:
            requestLabTest();
            break;
        case 5:
            viewOTBookings();
            break;
        case 0:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid option, please try again.\n");
        }
    } while (choice != 0);
}