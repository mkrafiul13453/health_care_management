#include "hms.h"

/* ---------------------------------------------------------------
   SECTION 1: USER & ACCESS (Role Based Login)
   --------------------------------------------------------------- */
static User users[4] = {
    {"admin", "admin123", "Admin"},
    {"doctor1", "doc123", "Doctor"},
    {"reception1", "rec123", "Receptionist"},
    {"pharma1", "pharma123", "Pharmacist"}};

static int login(void)
{
    char uname[20], pass[20];
    printf("Enter UserName: ");
    getString(uname, 20);
    printf("Enter Password: ");
    getString(pass, 20);

    for (int i = 0; i < 4; i++)
    {
        if (strcmp(users[i].userName, uname) == 0 && strcmp(users[i].password, pass) == 0)
        {
            return i;
        }
    }
    return -1;
}

/* =================================================================
   MAIN FUNCTION
   ================================================================= */
int main(void)
{
    
    loadAllDataFromCSV();
    if (loadBedsFromCSV() == 0)
    {
        initBeds(); 
        saveBedsToCSV();
    }

    printf("=====================================================\n");
    printf("      HEALTHCARE MANAGEMENT SYSTEM (HMS)\n");
    printf("=====================================================\n");
    printf("Demo Login Credentials:\n");
    printf("  Admin        -> userName: admin         password: admin123\n");
    printf("  Doctor       -> userName: doctor1       password: doc123\n");
    printf("  Receptionist -> userName: reception1    password: rec123\n");
    printf("  Pharmacist   -> userName: pharma1       password: pharma123\n");
    printf("=====================================================\n\n");

    printf("---- LOGIN ----\n");
    int idx = login();

    if (idx == -1)
    {
        printf("\nInvalid userName/Password. Program is shutting down.\n");
        return 0;
    }

    printf("\nWelcome, %s (Role: %s)\n", users[idx].userName, users[idx].role);

    if (strcmp(users[idx].role, "Admin") == 0)
        adminMenu();
    else if (strcmp(users[idx].role, "Doctor") == 0)
        doctorRoleMenu();
    else if (strcmp(users[idx].role, "Receptionist") == 0)
        receptionistMenu();
    else if (strcmp(users[idx].role, "Pharmacist") == 0)
        pharmacistMenu();

    printf("\nThank you for using HMS.\n");
    return 0;
}