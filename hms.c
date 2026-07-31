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
        if (strcmp(users[i].username, uname) == 0 && strcmp(users[i].password, pass) == 0)
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
    /* Load all previously saved data from CSV files (if any exist) */
    loadAllDataFromCSV();
    if (loadBedsFromCSV() == 0)
    {
        initBeds(); /* first run: no beds.csv yet, create default beds */
        saveBedsToCSV();
    }

    printf("=====================================================\n");
    printf("      HEALTHCARE MANAGEMENT SYSTEM (HMS)\n");
    printf("=====================================================\n");
    printf("Demo Login Credentials:\n");
    printf("  Admin        -> username: admin        password: admin123\n");
    printf("  Doctor       -> username: doctor1       password: doc123\n");
    printf("  Receptionist -> username: reception1    password: rec123\n");
    printf("  Pharmacist   -> username: pharma1       password: pharma123\n");
    printf("=====================================================\n\n");

    printf("---- LOGIN ----\n");
    int idx = login();

    if (idx == -1)
    {
        printf("\nInvalid Username/Password. Program is shutting down.\n");
        return 0;
    }

    printf("\nWelcome, %s (Role: %s)\n", users[idx].username, users[idx].role);

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