/*
=====================================================================
   HEALTHCARE MANAGEMENT SYSTEM (HMS) 
=====================================================================
   This program has 12 Functional Requirements. Each one is divided
   into a separate section, so it's easy to understand which part
   does what.

   1. User & Access (Role based Login)          -> SECTION 1
   2. Patient Registration                       -> SECTION 2
   3. Doctor Management                          -> SECTION 3
   4. Appointment Scheduling                      -> SECTION 4
   5. Medical Records                             -> SECTION 5
   6. Bed/Ward/Cabin Management                   -> SECTION 6
   7. OT Management                               -> SECTION 7
   8. Pharmacy/Inventory                          -> SECTION 8
   9. Billing/Invoicing                           -> SECTION 9
   10. Reports/Dashboard                          -> SECTION 10
   11. Lab/Test Requests                          -> SECTION 11
   12. Test Status Tracking                       -> (inside SECTION 11)
=====================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------------------------------------------------------------
   MAX SIZE values -- limits on how much data can be stored
   --------------------------------------------------------------- */
#define MAX_PATIENTS 100
#define MAX_DOCTORS 20
#define MAX_APPOINTMENTS 200
#define MAX_RECORDS 200
#define MAX_BEDS 20
#define MAX_OT 50
#define MAX_MEDICINES 50
#define MAX_BILLS 100
#define MAX_LABTESTS 100
#define LOW_STOCK_LIMIT 10

/* ---------------------------------------------------------------
   CSV FILE NAMES -- where each module's data gets saved/loaded
   --------------------------------------------------------------- */
#define PATIENTS_FILE "patients.csv"
#define DOCTORS_FILE "doctors.csv"
#define APPOINTMENTS_FILE "appointments.csv"
#define RECORDS_FILE "records.csv"
#define BEDS_FILE "beds.csv"
#define OT_FILE "ot_bookings.csv"
#define MEDICINES_FILE "medicines.csv"
#define BILLS_FILE "bills.csv"
#define LABTESTS_FILE "lab_tests.csv"

/* ---------------------------------------------------------------
   SECTION 1: USER & ACCESS (Role Based Login)
   --------------------------------------------------------------- */
typedef struct
{
    char username[20];
    char password[20];
    char role[20];
} User;

User users[4] = {
    {"admin", "admin123", "Admin"},
    {"doctor1", "doc123", "Doctor"},
    {"reception1", "rec123", "Receptionist"},
    {"pharma1", "pharma123", "Pharmacist"}};

/* ---------------------------------------------------------------
   SECTION 2: PATIENT REGISTRATION
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[100];
    char phone[15];
    int doctorId; /* assigned doctor, -1 means none assigned */
    int active;   /* 1 = registered/valid record */
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

/* ---------------------------------------------------------------
   SECTION 3: DOCTOR MANAGEMENT
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    char name[50];
    char specialization[50];
} Doctor;

Doctor doctors[MAX_DOCTORS];
int doctorCount = 0;

/* ---------------------------------------------------------------
   SECTION 4: APPOINTMENT SCHEDULING
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    int patientId;
    int doctorId;
    char date[15];
    char time[10];
    int status; /* 0 = Booked, 1 = Cancelled */
} Appointment;

Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

/* ---------------------------------------------------------------
   SECTION 5: MEDICAL RECORDS
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    int patientId;
    int doctorId;
    char diagnosis[150];
    char prescription[150];
    char date[15];
} MedicalRecord;

MedicalRecord records[MAX_RECORDS];
int recordCount = 0;

/* ---------------------------------------------------------------
   SECTION 6: BED / WARD / CABIN MANAGEMENT
   --------------------------------------------------------------- */
typedef struct
{
    int bedNo;
    char ward[20];  /* General / ICU / Cabin */
    int isOccupied; /* 0 = free, 1 = occupied */
    int patientId;
    char admitDate[15];
} Bed;

Bed beds[MAX_BEDS];
int bedCount = 0;

/* ---------------------------------------------------------------
   SECTION 7: OT (OPERATION THEATRE) MANAGEMENT
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    int patientId;
    char surgeryType[50];
    char date[15];
    char status[20]; /* Scheduled / Completed / Cancelled */
} OTBooking;

OTBooking otBookings[MAX_OT];
int otCount = 0;

/* ---------------------------------------------------------------
   SECTION 8: PHARMACY / INVENTORY
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    char name[50];
    int stock;
    float price;
} Medicine;

Medicine medicines[MAX_MEDICINES];
int medicineCount = 0;

/* ---------------------------------------------------------------
   SECTION 9: BILLING / INVOICING
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    int patientId;
    float consultationFee;
    float medicineBill;
    float bedBill;
    float otBill;
    float totalBill;
    float paidAmount;
    float dueAmount;
} Bill;

Bill bills[MAX_BILLS];
int billCount = 0;

/* ---------------------------------------------------------------
   SECTION 11 & 12: LAB TEST REQUEST + STATUS TRACKING
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    int patientId;
    char testName[50];
    char status[20]; /* Pending / Completed */
    char result[100];
} LabTest;

LabTest labTests[MAX_LABTESTS];
int labTestCount = 0;

/* =================================================================
   HELPER FUNCTIONS (for taking input easily)
   ================================================================= */
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void getString(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; /* removes the trailing \n */
}

int readInt()
{
    int x;
    scanf("%d", &x);
    clearBuffer();
    return x;
}

float readFloat()
{
    float x;
    scanf("%f", &x);
    clearBuffer();
    return x;
}

void pause()
{
    printf("\nPress Enter to continue...");
    getchar();
}

/* =================================================================
   SECTION 13: CSV FILE STORAGE (SAVE / LOAD)
   -----------------------------------------------------------------
   Each module gets its own save*ToCSV() and load*FromCSV() pair.
   save*ToCSV()  -> writes the current in-memory array to a .csv file.
   load*FromCSV()-> reads a .csv file (if it exists) back into the
                    in-memory array when the program starts.
   NOTE: this simple CSV writer/reader assumes text fields (name,
   disease, diagnosis, etc.) do not contain commas.
   ================================================================= */

/* ---------------- Patients ---------------- */
void savePatientsToCSV()
{
    FILE *fp = fopen(PATIENTS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", PATIENTS_FILE);
        return;
    }
    fprintf(fp, "id,name,age,gender,disease,phone,doctorId,active\n");
    for (int i = 0; i < patientCount; i++)
    {
        fprintf(fp, "%d,%s,%d,%s,%s,%s,%d,%d\n",
                patients[i].id, patients[i].name, patients[i].age,
                patients[i].gender, patients[i].disease, patients[i].phone,
                patients[i].doctorId, patients[i].active);
    }
    fclose(fp);
}

void loadPatientsFromCSV()
{
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp)
        return; /* no saved file yet, nothing to load */
    char line[300];
    fgets(line, sizeof(line), fp); /* skip header row */
    patientCount = 0;
    while (patientCount < MAX_PATIENTS &&
           fscanf(fp, "%d,%49[^,],%d,%9[^,],%99[^,],%14[^,],%d,%d\n",
                  &patients[patientCount].id, patients[patientCount].name,
                  &patients[patientCount].age, patients[patientCount].gender,
                  patients[patientCount].disease, patients[patientCount].phone,
                  &patients[patientCount].doctorId, &patients[patientCount].active) == 8)
    {
        patientCount++;
    }
    fclose(fp);
}

/* ---------------- Doctors ---------------- */
void saveDoctorsToCSV()
{
    FILE *fp = fopen(DOCTORS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", DOCTORS_FILE);
        return;
    }
    fprintf(fp, "id,name,specialization\n");
    for (int i = 0; i < doctorCount; i++)
    {
        fprintf(fp, "%d,%s,%s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
    }
    fclose(fp);
}

void loadDoctorsFromCSV()
{
    FILE *fp = fopen(DOCTORS_FILE, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    doctorCount = 0;
    while (doctorCount < MAX_DOCTORS &&
           fscanf(fp, "%d,%49[^,],%49[^\n]\n",
                  &doctors[doctorCount].id, doctors[doctorCount].name,
                  doctors[doctorCount].specialization) == 3)
    {
        doctorCount++;
    }
    fclose(fp);
}

/* ---------------- Appointments ---------------- */
void saveAppointmentsToCSV()
{
    FILE *fp = fopen(APPOINTMENTS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", APPOINTMENTS_FILE);
        return;
    }
    fprintf(fp, "id,patientId,doctorId,date,time,status\n");
    for (int i = 0; i < appointmentCount; i++)
    {
        fprintf(fp, "%d,%d,%d,%s,%s,%d\n",
                appointments[i].id, appointments[i].patientId, appointments[i].doctorId,
                appointments[i].date, appointments[i].time, appointments[i].status);
    }
    fclose(fp);
}

void loadAppointmentsFromCSV()
{
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    appointmentCount = 0;
    while (appointmentCount < MAX_APPOINTMENTS &&
           fscanf(fp, "%d,%d,%d,%14[^,],%9[^,],%d\n",
                  &appointments[appointmentCount].id, &appointments[appointmentCount].patientId,
                  &appointments[appointmentCount].doctorId, appointments[appointmentCount].date,
                  appointments[appointmentCount].time, &appointments[appointmentCount].status) == 6)
    {
        appointmentCount++;
    }
    fclose(fp);
}

/* ---------------- Medical Records ---------------- */
void saveRecordsToCSV()
{
    FILE *fp = fopen(RECORDS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", RECORDS_FILE);
        return;
    }
    fprintf(fp, "id,patientId,doctorId,diagnosis,prescription,date\n");
    for (int i = 0; i < recordCount; i++)
    {
        fprintf(fp, "%d,%d,%d,%s,%s,%s\n",
                records[i].id, records[i].patientId, records[i].doctorId,
                records[i].diagnosis, records[i].prescription, records[i].date);
    }
    fclose(fp);
}

void loadRecordsFromCSV()
{
    FILE *fp = fopen(RECORDS_FILE, "r");
    if (!fp)
        return;
    char line[400];
    fgets(line, sizeof(line), fp);
    recordCount = 0;
    while (recordCount < MAX_RECORDS &&
           fscanf(fp, "%d,%d,%d,%149[^,],%149[^,],%14[^\n]\n",
                  &records[recordCount].id, &records[recordCount].patientId,
                  &records[recordCount].doctorId, records[recordCount].diagnosis,
                  records[recordCount].prescription, records[recordCount].date) == 6)
    {
        recordCount++;
    }
    fclose(fp);
}

/* ---------------- Beds ---------------- */
void saveBedsToCSV()
{
    FILE *fp = fopen(BEDS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", BEDS_FILE);
        return;
    }
    fprintf(fp, "bedNo,ward,isOccupied,patientId,admitDate\n");
    for (int i = 0; i < bedCount; i++)
    {
        fprintf(fp, "%d,%s,%d,%d,%s\n",
                beds[i].bedNo, beds[i].ward, beds[i].isOccupied,
                beds[i].patientId, beds[i].admitDate);
    }
    fclose(fp);
}

int loadBedsFromCSV()
{
    FILE *fp = fopen(BEDS_FILE, "r");
    if (!fp)
        return 0; /* no saved file yet */
    char line[200];
    fgets(line, sizeof(line), fp);
    bedCount = 0;
    while (bedCount < MAX_BEDS &&
           fscanf(fp, "%d,%19[^,],%d,%d,%14[^\n]\n",
                  &beds[bedCount].bedNo, beds[bedCount].ward,
                  &beds[bedCount].isOccupied, &beds[bedCount].patientId,
                  beds[bedCount].admitDate) == 5)
    {
        bedCount++;
    }
    fclose(fp);
    return bedCount;
}

/* ---------------- OT Bookings ---------------- */
void saveOTToCSV()
{
    FILE *fp = fopen(OT_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", OT_FILE);
        return;
    }
    fprintf(fp, "id,patientId,surgeryType,date,status\n");
    for (int i = 0; i < otCount; i++)
    {
        fprintf(fp, "%d,%d,%s,%s,%s\n",
                otBookings[i].id, otBookings[i].patientId, otBookings[i].surgeryType,
                otBookings[i].date, otBookings[i].status);
    }
    fclose(fp);
}

void loadOTFromCSV()
{
    FILE *fp = fopen(OT_FILE, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    otCount = 0;
    while (otCount < MAX_OT &&
           fscanf(fp, "%d,%d,%49[^,],%14[^,],%19[^\n]\n",
                  &otBookings[otCount].id, &otBookings[otCount].patientId,
                  otBookings[otCount].surgeryType, otBookings[otCount].date,
                  otBookings[otCount].status) == 5)
    {
        otCount++;
    }
    fclose(fp);
}

/* ---------------- Medicines / Inventory ---------------- */
void saveMedicinesToCSV()
{
    FILE *fp = fopen(MEDICINES_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", MEDICINES_FILE);
        return;
    }
    fprintf(fp, "id,name,stock,price\n");
    for (int i = 0; i < medicineCount; i++)
    {
        fprintf(fp, "%d,%s,%d,%.2f\n",
                medicines[i].id, medicines[i].name, medicines[i].stock, medicines[i].price);
    }
    fclose(fp);
}

void loadMedicinesFromCSV()
{
    FILE *fp = fopen(MEDICINES_FILE, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    medicineCount = 0;
    while (medicineCount < MAX_MEDICINES &&
           fscanf(fp, "%d,%49[^,],%d,%f\n",
                  &medicines[medicineCount].id, medicines[medicineCount].name,
                  &medicines[medicineCount].stock, &medicines[medicineCount].price) == 4)
    {
        medicineCount++;
    }
    fclose(fp);
}

/* ---------------- Bills ---------------- */
void saveBillsToCSV()
{
    FILE *fp = fopen(BILLS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", BILLS_FILE);
        return;
    }
    fprintf(fp, "id,patientId,consultationFee,medicineBill,bedBill,otBill,totalBill,paidAmount,dueAmount\n");
    for (int i = 0; i < billCount; i++)
    {
        fprintf(fp, "%d,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                bills[i].id, bills[i].patientId, bills[i].consultationFee,
                bills[i].medicineBill, bills[i].bedBill, bills[i].otBill,
                bills[i].totalBill, bills[i].paidAmount, bills[i].dueAmount);
    }
    fclose(fp);
}

void loadBillsFromCSV()
{
    FILE *fp = fopen(BILLS_FILE, "r");
    if (!fp)
        return;
    char line[300];
    fgets(line, sizeof(line), fp);
    billCount = 0;
    while (billCount < MAX_BILLS &&
           fscanf(fp, "%d,%d,%f,%f,%f,%f,%f,%f,%f\n",
                  &bills[billCount].id, &bills[billCount].patientId,
                  &bills[billCount].consultationFee, &bills[billCount].medicineBill,
                  &bills[billCount].bedBill, &bills[billCount].otBill,
                  &bills[billCount].totalBill, &bills[billCount].paidAmount,
                  &bills[billCount].dueAmount) == 9)
    {
        billCount++;
    }
    fclose(fp);
}

/* ---------------- Lab Tests ---------------- */
void saveLabTestsToCSV()
{
    FILE *fp = fopen(LABTESTS_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", LABTESTS_FILE);
        return;
    }
    fprintf(fp, "id,patientId,testName,status,result\n");
    for (int i = 0; i < labTestCount; i++)
    {
        fprintf(fp, "%d,%d,%s,%s,%s\n",
                labTests[i].id, labTests[i].patientId, labTests[i].testName,
                labTests[i].status, labTests[i].result);
    }
    fclose(fp);
}

void loadLabTestsFromCSV()
{
    FILE *fp = fopen(LABTESTS_FILE, "r");
    if (!fp)
        return;
    char line[300];
    fgets(line, sizeof(line), fp);
    labTestCount = 0;
    while (labTestCount < MAX_LABTESTS &&
           fscanf(fp, "%d,%d,%49[^,],%19[^,],%99[^\n]\n",
                  &labTests[labTestCount].id, &labTests[labTestCount].patientId,
                  labTests[labTestCount].testName, labTests[labTestCount].status,
                  labTests[labTestCount].result) == 5)
    {
        labTestCount++;
    }
    fclose(fp);
}

/* ---------------- Load everything at program startup ---------------- */
void loadAllDataFromCSV()
{
    loadPatientsFromCSV();
    loadDoctorsFromCSV();
    loadAppointmentsFromCSV();
    loadRecordsFromCSV();
    loadOTFromCSV();
    loadMedicinesFromCSV();
    loadBillsFromCSV();
    loadLabTestsFromCSV();
    /* beds are handled separately in main(), since if no beds.csv
       exists yet the default 20 beds need to be created first */
}

/* =================================================================
   SECTION 2: PATIENT REGISTRATION -- FUNCTIONS
   ================================================================= */
Patient *findPatientById(int id)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].active && patients[i].id == id)
            return &patients[i];
    }
    return NULL;
}

void registerPatient()
{
    if (patientCount >= MAX_PATIENTS)
    {
        printf("Patient list is full, cannot add more.\n");
        return;
    }
    Patient p;
    p.id = patientCount + 1; /* Unique Patient ID auto generate */
    printf("\n--- New Patient Registration ---\n");
    printf("Enter name: ");
    getString(p.name, 50);
    printf("Enter age: ");
    p.age = readInt();
    printf("Gender (Male/Female/Other): ");
    getString(p.gender, 10);
    printf("Enter disease/problem: ");
    getString(p.disease, 100);
    printf("Phone Number: ");
    getString(p.phone, 15);
    p.doctorId = -1;
    p.active = 1;

    patients[patientCount] = p;
    patientCount++;
    savePatientsToCSV();

    printf("\nPatient Registered successfully. Patient ID = %d\n", p.id);
}

void viewAllPatients()
{
    printf("\n--- List of All Patients ---\n");
    if (patientCount == 0)
    {
        printf("No patients found.\n");
        return;
    }
    printf("%-5s %-20s %-5s %-10s %-20s %-12s %-10s\n",
           "ID", "Name", "Age", "Gender", "Disease", "Phone", "DoctorID");
    for (int i = 0; i < patientCount; i++)
    {
        if (!patients[i].active)
            continue;
        printf("%-5d %-20s %-5d %-10s %-20s %-12s %-10d\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].disease, patients[i].phone,
               patients[i].doctorId);
    }
}

/* =================================================================
   SECTION 3: DOCTOR MANAGEMENT -- FUNCTIONS
   ================================================================= */
Doctor *findDoctorById(int id)
{
    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].id == id)
            return &doctors[i];
    }
    return NULL;
}

void addDoctor()
{
    if (doctorCount >= MAX_DOCTORS)
    {
        printf("Doctor list is full.\n");
        return;
    }
    Doctor d;
    d.id = doctorCount + 1;
    printf("\n--- Add New Doctor ---\n");
    printf("Doctor's name: ");
    getString(d.name, 50);
    printf("Specialization (e.g. Cardiologist): ");
    getString(d.specialization, 50);

    doctors[doctorCount] = d;
    doctorCount++;
    saveDoctorsToCSV();
    printf("\nDoctor added. Doctor ID = %d\n", d.id);
}

void viewAllDoctors()
{
    printf("\n--- List of All Doctors ---\n");
    if (doctorCount == 0)
    {
        printf("No doctors found.\n");
        return;
    }
    printf("%-5s %-20s %-20s\n", "ID", "Name", "Specialization");
    for (int i = 0; i < doctorCount; i++)
    {
        printf("%-5d %-20s %-20s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
    }
}

void assignDoctorToPatient()
{
    printf("\n--- Assign Doctor to Patient ---\n");
    printf("Enter Patient ID: ");
    int pid = readInt();
    Patient *p = findPatientById(pid);
    if (!p)
    {
        printf("Patient ID not found.\n");
        return;
    }

    printf("Enter Doctor ID: ");
    int did = readInt();
    Doctor *d = findDoctorById(did);
    if (!d)
    {
        printf("Doctor ID not found.\n");
        return;
    }

    p->doctorId = did;
    savePatientsToCSV();
    printf("\n%s has been assigned to Dr. %s.\n", p->name, d->name);
}

void doctorDashboard()
{
    printf("\n--- Doctor Dashboard: Assigned Patients ---\n");
    printf("Enter your Doctor ID: ");
    int did = readInt();
    int found = 0;
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].active && patients[i].doctorId == did)
        {
            printf("Patient ID: %d | Name: %s | Disease: %s\n",
                   patients[i].id, patients[i].name, patients[i].disease);
            found = 1;
        }
    }
    if (!found)
        printf("No patients assigned to this doctor.\n");
}

/* =================================================================
   SECTION 4: APPOINTMENT SCHEDULING -- FUNCTIONS
   ================================================================= */
void bookAppointment()
{
    if (appointmentCount >= MAX_APPOINTMENTS)
    {
        printf("Appointment list is full.\n");
        return;
    }
    Appointment a;
    printf("\n--- Book a New Appointment ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient not found.\n");
        return;
    }

    printf("Doctor ID: ");
    int did = readInt();
    if (!findDoctorById(did))
    {
        printf("Doctor not found.\n");
        return;
    }

    char date[15], time[10];
    printf("Enter Date (DD-MM-YYYY): ");
    getString(date, 15);
    printf("Enter Time (HH:MM): ");
    getString(time, 10);

    /* Double booking check: same doctor, same date, same time */
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].status == 0 &&
            appointments[i].doctorId == did &&
            strcmp(appointments[i].date, date) == 0 &&
            strcmp(appointments[i].time, time) == 0)
        {
            printf("\nDoctor is already booked at this time. Please choose another time.\n");
            return;
        }
    }

    a.id = appointmentCount + 1;
    a.patientId = pid;
    a.doctorId = did;
    strcpy(a.date, date);
    strcpy(a.time, time);
    a.status = 0;

    appointments[appointmentCount] = a;
    appointmentCount++;
    saveAppointmentsToCSV();
    printf("\nAppointment Booked. Appointment ID = %d\n", a.id);
}

void cancelAppointment()
{
    printf("\n--- Cancel Appointment ---\n");
    printf("Enter Appointment ID: ");
    int id = readInt();
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].id == id && appointments[i].status == 0)
        {
            appointments[i].status = 1;
            saveAppointmentsToCSV();
            printf("Appointment cancelled.\n");
            return;
        }
    }
    printf("No active appointment found with this ID.\n");
}

void viewAppointments()
{
    printf("\n--- All Appointments ---\n");
    if (appointmentCount == 0)
    {
        printf("No appointments found.\n");
        return;
    }
    printf("%-5s %-10s %-10s %-12s %-8s %-10s\n",
           "ID", "PatientID", "DoctorID", "Date", "Time", "Status");
    for (int i = 0; i < appointmentCount; i++)
    {
        printf("%-5d %-10d %-10d %-12s %-8s %-10s\n",
               appointments[i].id, appointments[i].patientId, appointments[i].doctorId,
               appointments[i].date, appointments[i].time,
               appointments[i].status == 0 ? "Booked" : "Cancelled");
    }
}

/* =================================================================
   SECTION 5: MEDICAL RECORDS -- FUNCTIONS
   ================================================================= */
void addMedicalRecord()
{
    if (recordCount >= MAX_RECORDS)
    {
        printf("Record list is full.\n");
        return;
    }
    MedicalRecord r;
    printf("\n--- Add New Medical Record ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient not found.\n");
        return;
    }
    printf("Doctor ID: ");
    int did = readInt();
    if (!findDoctorById(did))
    {
        printf("Doctor not found.\n");
        return;
    }

    r.id = recordCount + 1;
    r.patientId = pid;
    r.doctorId = did;
    printf("Enter Diagnosis: ");
    getString(r.diagnosis, 150);
    printf("Enter Prescription: ");
    getString(r.prescription, 150);
    printf("Enter Date (DD-MM-YYYY): ");
    getString(r.date, 15);

    records[recordCount] = r;
    recordCount++;
    saveRecordsToCSV();
    printf("\nMedical Record added.\n");
}

void viewMedicalRecords()
{
    printf("\n--- View Medical Records ---\n");
    printf("Enter Patient ID (enter 0 to view all): ");
    int pid = readInt();
    int found = 0;
    for (int i = 0; i < recordCount; i++)
    {
        if (pid == 0 || records[i].patientId == pid)
        {
            printf("\nRecord ID: %d | Patient ID: %d | Doctor ID: %d | Date: %s\n",
                   records[i].id, records[i].patientId, records[i].doctorId, records[i].date);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Prescription: %s\n", records[i].prescription);
            found = 1;
        }
    }
    if (!found)
        printf("No records found.\n");
}

/* =================================================================
   SECTION 6: BED / WARD / CABIN MANAGEMENT -- FUNCTIONS
   ================================================================= */
void initBeds()
{
    /* At startup 20 beds are created: 10 General, 5 ICU, 5 Cabin */
    int i;
    for (i = 0; i < 10; i++)
    {
        beds[bedCount].bedNo = bedCount + 1;
        strcpy(beds[bedCount].ward, "General");
        beds[bedCount].isOccupied = 0;
        beds[bedCount].patientId = -1;
        strcpy(beds[bedCount].admitDate, "-");
        bedCount++;
    }
    for (i = 0; i < 5; i++)
    {
        beds[bedCount].bedNo = bedCount + 1;
        strcpy(beds[bedCount].ward, "ICU");
        beds[bedCount].isOccupied = 0;
        beds[bedCount].patientId = -1;
        strcpy(beds[bedCount].admitDate, "-");
        bedCount++;
    }
    for (i = 0; i < 5; i++)
    {
        beds[bedCount].bedNo = bedCount + 1;
        strcpy(beds[bedCount].ward, "Cabin");
        beds[bedCount].isOccupied = 0;
        beds[bedCount].patientId = -1;
        strcpy(beds[bedCount].admitDate, "-");
        bedCount++;
    }
}

void viewBedStatus()
{
    printf("\n--- Bed Status (Real Time) ---\n");
    printf("%-6s %-10s %-10s %-10s %-12s\n", "BedNo", "Ward", "Status", "PatientID", "AdmitDate");
    for (int i = 0; i < bedCount; i++)
    {
        printf("%-6d %-10s %-10s %-10d %-12s\n",
               beds[i].bedNo, beds[i].ward,
               beds[i].isOccupied ? "Occupied" : "Free",
               beds[i].patientId, beds[i].admitDate);
    }
}

void admitPatient()
{
    printf("\n--- Patient Admission ---\n");
    printf("Enter Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient not found.\n");
        return;
    }

    char ward[20];
    printf("Which Ward do you want (General/ICU/Cabin): ");
    getString(ward, 20);

    for (int i = 0; i < bedCount; i++)
    {
        if (!beds[i].isOccupied && strcmp(beds[i].ward, ward) == 0)
        {
            beds[i].isOccupied = 1;
            beds[i].patientId = pid;
            printf("Enter Admit Date (DD-MM-YYYY): ");
            getString(beds[i].admitDate, 15);
            saveBedsToCSV();
            printf("\nPatient admitted to Bed No %d (%s).\n",
                   beds[i].bedNo, beds[i].ward);
            return;
        }
    }
    printf("\nSorry, no free bed available in %s Ward.\n", ward);
}

void dischargePatient()
{
    printf("\n--- Patient Discharge ---\n");
    printf("Enter Bed Number: ");
    int bedNo = readInt();
    for (int i = 0; i < bedCount; i++)
    {
        if (beds[i].bedNo == bedNo)
        {
            if (!beds[i].isOccupied)
            {
                printf("This bed is already free.\n");
                return;
            }
            beds[i].isOccupied = 0;
            beds[i].patientId = -1;
            strcpy(beds[i].admitDate, "-");
            saveBedsToCSV();
            printf("Patient discharged, Bed No %d is now free.\n", bedNo);
            return;
        }
    }
    printf("Bed number not found.\n");
}

/* =================================================================
   SECTION 7: OT MANAGEMENT -- FUNCTIONS
   ================================================================= */
void bookOT()
{
    if (otCount >= MAX_OT)
    {
        printf("OT booking list is full.\n");
        return;
    }
    OTBooking o;
    printf("\n--- Surgery / OT Booking ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient not found.\n");
        return;
    }

    o.id = otCount + 1;
    o.patientId = pid;
    printf("Enter Surgery Type: ");
    getString(o.surgeryType, 50);
    printf("Enter Date (DD-MM-YYYY): ");
    getString(o.date, 15);
    strcpy(o.status, "Scheduled");

    otBookings[otCount] = o;
    otCount++;
    saveOTToCSV();
    printf("\nOT Booking completed. OT Booking ID = %d\n", o.id);
}

void updateOTStatus()
{
    printf("\n--- Update OT Status ---\n");
    printf("Enter OT Booking ID: ");
    int id = readInt();
    for (int i = 0; i < otCount; i++)
    {
        if (otBookings[i].id == id)
        {
            printf("Enter new Status (Scheduled/Completed/Cancelled): ");
            getString(otBookings[i].status, 20);
            saveOTToCSV();
            printf("Status updated.\n");
            return;
        }
    }
    printf("ID not found.\n");
}

void viewOTBookings()
{
    printf("\n--- All OT Bookings ---\n");
    if (otCount == 0)
    {
        printf("No OT bookings found.\n");
        return;
    }
    printf("%-5s %-10s %-20s %-12s %-12s\n", "ID", "PatientID", "SurgeryType", "Date", "Status");
    for (int i = 0; i < otCount; i++)
    {
        printf("%-5d %-10d %-20s %-12s %-12s\n",
               otBookings[i].id, otBookings[i].patientId, otBookings[i].surgeryType,
               otBookings[i].date, otBookings[i].status);
    }
}

/* =================================================================
   SECTION 8: PHARMACY / INVENTORY -- FUNCTIONS
   ================================================================= */
Medicine *findMedicineById(int id)
{
    for (int i = 0; i < medicineCount; i++)
    {
        if (medicines[i].id == id)
            return &medicines[i];
    }
    return NULL;
}

void addMedicine()
{
    if (medicineCount >= MAX_MEDICINES)
    {
        printf("Medicine list is full.\n");
        return;
    }
    Medicine m;
    m.id = medicineCount + 1;
    printf("\n--- Add New Medicine ---\n");
    printf("Medicine name: ");
    getString(m.name, 50);
    printf("Stock quantity: ");
    m.stock = readInt();
    printf("Price (per unit): ");
    m.price = readFloat();

    medicines[medicineCount] = m;
    medicineCount++;
    saveMedicinesToCSV();
    printf("\nMedicine added. Medicine ID = %d\n", m.id);
}

void viewInventory()
{
    printf("\n--- Inventory / Stock List ---\n");
    if (medicineCount == 0)
    {
        printf("No medicines found.\n");
        return;
    }
    printf("%-5s %-20s %-10s %-10s %-10s\n", "ID", "Name", "Stock", "Price", "Alert");
    for (int i = 0; i < medicineCount; i++)
    {
        printf("%-5d %-20s %-10d %-10.2f %-10s\n",
               medicines[i].id, medicines[i].name, medicines[i].stock, medicines[i].price,
               medicines[i].stock < LOW_STOCK_LIMIT ? "LOW STOCK!" : "OK");
    }
}

void sellMedicine()
{
    printf("\n--- Sell Medicine ---\n");
    printf("Medicine ID: ");
    int id = readInt();
    Medicine *m = findMedicineById(id);
    if (!m)
    {
        printf("Medicine not found.\n");
        return;
    }

    printf("Enter quantity to sell: ");
    int qty = readInt();
    if (qty > m->stock)
    {
        printf("Not enough stock available. Current stock: %d\n", m->stock);
        return;
    }
    m->stock -= qty;
    saveMedicinesToCSV();
    printf("\nSale completed. Total price: %.2f\n", qty * m->price);

    if (m->stock < LOW_STOCK_LIMIT)
    {
        printf("Warning: Stock for %s is running low (%d remaining). Please restock soon.\n",
               m->name, m->stock);
    }
}

void addDamagedStock()
{
    printf("\n--- Damaged Stock Entry ---\n");
    printf("Medicine ID: ");
    int id = readInt();
    Medicine *m = findMedicineById(id);
    if (!m)
    {
        printf("Medicine not found.\n");
        return;
    }

    printf("Enter damaged quantity: ");
    int qty = readInt();
    if (qty > m->stock)
    {
        printf("Not enough stock for this amount.\n");
        return;
    }
    m->stock -= qty;
    saveMedicinesToCSV();
    printf("Damaged stock removed. Current stock: %d\n", m->stock);
}

/* =================================================================
   SECTION 9: BILLING / INVOICING -- FUNCTIONS
   ================================================================= */
void generateBill()
{
    if (billCount >= MAX_BILLS)
    {
        printf("Bill list is full.\n");
        return;
    }
    Bill b;
    printf("\n--- Generate New Bill ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient not found.\n");
        return;
    }

    b.id = billCount + 1;
    b.patientId = pid;

    printf("Enter Consultation Fee: ");
    b.consultationFee = readFloat();
    printf("Enter Medicine Bill: ");
    b.medicineBill = readFloat();
    printf("Enter Bed/Ward Bill: ");
    b.bedBill = readFloat();
    printf("Enter OT Bill (0 if none): ");
    b.otBill = readFloat();

    b.totalBill = b.consultationFee + b.medicineBill + b.bedBill + b.otBill;
    b.paidAmount = 0;
    b.dueAmount = b.totalBill;

    bills[billCount] = b;
    billCount++;
    saveBillsToCSV();
    printf("\nBill generated. Bill ID = %d | Total = %.2f\n", b.id, b.totalBill);
}

void makePayment()
{
    printf("\n--- Make Payment (Partial Payment supported) ---\n");
    printf("Enter Bill ID: ");
    int id = readInt();
    for (int i = 0; i < billCount; i++)
    {
        if (bills[i].id == id)
        {
            printf("Current Due Amount: %.2f\n", bills[i].dueAmount);
            printf("Enter amount being paid: ");
            float amt = readFloat();
            if (amt > bills[i].dueAmount)
            {
                printf("Amount exceeds the due amount. Please enter a correct amount.\n");
                return;
            }
            bills[i].paidAmount += amt;
            bills[i].dueAmount -= amt;
            saveBillsToCSV();
            printf("Payment completed. Remaining Due = %.2f\n", bills[i].dueAmount);
            return;
        }
    }
    printf("Bill ID not found.\n");
}

void printInvoice()
{
    printf("\n--- Print Invoice ---\n");
    printf("Enter Bill ID: ");
    int id = readInt();
    for (int i = 0; i < billCount; i++)
    {
        if (bills[i].id == id)
        {
            Patient *p = findPatientById(bills[i].patientId);
            printf("\n========== INVOICE ==========\n");
            printf("Bill ID       : %d\n", bills[i].id);
            printf("Patient Name  : %s\n", p ? p->name : "Unknown");
            printf("------------------------------\n");
            printf("Consultation  : %.2f\n", bills[i].consultationFee);
            printf("Medicine      : %.2f\n", bills[i].medicineBill);
            printf("Bed/Ward      : %.2f\n", bills[i].bedBill);
            printf("OT            : %.2f\n", bills[i].otBill);
            printf("------------------------------\n");
            printf("Total Bill    : %.2f\n", bills[i].totalBill);
            printf("Paid          : %.2f\n", bills[i].paidAmount);
            printf("Due           : %.2f\n", bills[i].dueAmount);
            printf("Status        : %s\n", bills[i].dueAmount <= 0 ? "PAID" : "DUE");
            printf("==============================\n");
            return;
        }
    }
    printf("Bill ID not found.\n");
}

void viewAllBills()
{
    printf("\n--- List of All Bills ---\n");
    if (billCount == 0)
    {
        printf("No bills found.\n");
        return;
    }
    printf("%-5s %-10s %-10s %-10s %-10s %-8s\n",
           "ID", "PatientID", "Total", "Paid", "Due", "Status");
    for (int i = 0; i < billCount; i++)
    {
        printf("%-5d %-10d %-10.2f %-10.2f %-10.2f %-8s\n",
               bills[i].id, bills[i].patientId, bills[i].totalBill,
               bills[i].paidAmount, bills[i].dueAmount,
               bills[i].dueAmount <= 0 ? "PAID" : "DUE");
    }
}

/* =================================================================
   SECTION 11 & 12: LAB TEST REQUEST + STATUS TRACKING -- FUNCTIONS
   ================================================================= */
void requestLabTest()
{
    if (labTestCount >= MAX_LABTESTS)
    {
        printf("Lab Test list is full.\n");
        return;
    }
    LabTest t;
    printf("\n--- New Lab Test Request ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient not found.\n");
        return;
    }

    t.id = labTestCount + 1;
    t.patientId = pid;
    printf("Enter Test name (e.g. Blood Test): ");
    getString(t.testName, 50);
    strcpy(t.status, "Pending");
    strcpy(t.result, "-");

    labTests[labTestCount] = t;
    labTestCount++;
    saveLabTestsToCSV();
    printf("\nLab Test Requested. Test ID = %d (Status: Pending)\n", t.id);
}

void updateTestStatus()
{
    printf("\n--- Update Lab Test Status ---\n");
    printf("Enter Test ID: ");
    int id = readInt();
    for (int i = 0; i < labTestCount; i++)
    {
        if (labTests[i].id == id)
        {
            strcpy(labTests[i].status, "Completed");
            printf("Enter Test Result: ");
            getString(labTests[i].result, 100);
            saveLabTestsToCSV();
            printf("Test Status set to 'Completed' and Result linked to the patient.\n");
            return;
        }
    }
    printf("Test ID not found.\n");
}

void viewLabTests()
{
    printf("\n--- List of All Lab Tests ---\n");
    if (labTestCount == 0)
    {
        printf("No tests found.\n");
        return;
    }
    printf("%-5s %-10s %-20s %-12s %-20s\n", "ID", "PatientID", "TestName", "Status", "Result");
    for (int i = 0; i < labTestCount; i++)
    {
        printf("%-5d %-10d %-20s %-12s %-20s\n",
               labTests[i].id, labTests[i].patientId, labTests[i].testName,
               labTests[i].status, labTests[i].result);
    }
}

/* =================================================================
   SECTION 10: REPORTS / DASHBOARD
   ================================================================= */
void showDashboard()
{
    int occupiedBeds = 0, lowStockCount = 0, pendingTests = 0;
    float totalCollected = 0, totalDue = 0;

    for (int i = 0; i < bedCount; i++)
        if (beds[i].isOccupied)
            occupiedBeds++;
    for (int i = 0; i < medicineCount; i++)
        if (medicines[i].stock < LOW_STOCK_LIMIT)
            lowStockCount++;
    for (int i = 0; i < labTestCount; i++)
        if (strcmp(labTests[i].status, "Pending") == 0)
            pendingTests++;
    for (int i = 0; i < billCount; i++)
    {
        totalCollected += bills[i].paidAmount;
        totalDue += bills[i].dueAmount;
    }

    printf("\n============== DASHBOARD / REPORT ==============\n");
    printf("Total Patients               : %d\n", patientCount);
    printf("Total Doctors                : %d\n", doctorCount);
    printf("Total Appointments           : %d\n", appointmentCount);
    printf("Total Beds                   : %d\n", bedCount);
    printf("Occupied Beds                : %d\n", occupiedBeds);
    printf("Free Beds                    : %d\n", bedCount - occupiedBeds);
    printf("Total OT Bookings            : %d\n", otCount);
    printf("Low Stock Medicines          : %d\n", lowStockCount);
    printf("Pending Lab Tests            : %d\n", pendingTests);
    printf("Total Collected Amount       : %.2f\n", totalCollected);
    printf("Total Due Amount             : %.2f\n", totalDue);
    printf("==================================================\n");
}

/* =================================================================
   MENUS  (Role Based Access -- part of SECTION 1)
   ================================================================= */
void patientMenu()
{
    int ch;
    do
    {
        printf("\n---- Patient Management ----\n");
        printf("1. Register Patient\n2. View All Patients\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            registerPatient();
        else if (ch == 2)
            viewAllPatients();
    } while (ch != 0);
}

void doctorMenu()
{
    int ch;
    do
    {
        printf("\n---- Doctor Management ----\n");
        printf("1. Add Doctor\n2. View All Doctors\n3. Assign Doctor to Patient\n4. Doctor Dashboard\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            addDoctor();
        else if (ch == 2)
            viewAllDoctors();
        else if (ch == 3)
            assignDoctorToPatient();
        else if (ch == 4)
            doctorDashboard();
    } while (ch != 0);
}

void appointmentMenu()
{
    int ch;
    do
    {
        printf("\n---- Appointment Scheduling ----\n");
        printf("1. Book Appointment\n2. Cancel Appointment\n3. View All Appointments\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            bookAppointment();
        else if (ch == 2)
            cancelAppointment();
        else if (ch == 3)
            viewAppointments();
    } while (ch != 0);
}

void recordMenu()
{
    int ch;
    do
    {
        printf("\n---- Medical Records ----\n");
        printf("1. Add New Record\n2. View Records\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            addMedicalRecord();
        else if (ch == 2)
            viewMedicalRecords();
    } while (ch != 0);
}

void bedMenu()
{
    int ch;
    do
    {
        printf("\n---- Bed/Ward/Cabin Management ----\n");
        printf("1. View Bed Status\n2. Admit Patient\n3. Discharge Patient\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            viewBedStatus();
        else if (ch == 2)
            admitPatient();
        else if (ch == 3)
            dischargePatient();
    } while (ch != 0);
}

void otMenu()
{
    int ch;
    do
    {
        printf("\n---- OT Management ----\n");
        printf("1. Book OT\n2. Update OT Status\n3. View All OT Bookings\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            bookOT();
        else if (ch == 2)
            updateOTStatus();
        else if (ch == 3)
            viewOTBookings();
    } while (ch != 0);
}

void pharmacyMenu()
{
    int ch;
    do
    {
        printf("\n---- Pharmacy / Inventory ----\n");
        printf("1. Add Medicine\n2. View Inventory\n3. Sell Medicine\n4. Damaged Stock Entry\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            addMedicine();
        else if (ch == 2)
            viewInventory();
        else if (ch == 3)
            sellMedicine();
        else if (ch == 4)
            addDamagedStock();
    } while (ch != 0);
}

void billingMenu()
{
    int ch;
    do
    {
        printf("\n---- Billing / Invoicing ----\n");
        printf("1. Generate New Bill\n2. Make Payment\n3. Print Invoice\n4. View All Bills\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            generateBill();
        else if (ch == 2)
            makePayment();
        else if (ch == 3)
            printInvoice();
        else if (ch == 4)
            viewAllBills();
    } while (ch != 0);
}

void labMenu()
{
    int ch;
    do
    {
        printf("\n---- Lab / Test Requests ----\n");
        printf("1. Request Test\n2. Update Test Status (Pending->Completed)\n3. View All Tests\n0. Go Back\nChoose: ");
        ch = readInt();
        if (ch == 1)
            requestLabTest();
        else if (ch == 2)
            updateTestStatus();
        else if (ch == 3)
            viewLabTests();
    } while (ch != 0);
}

/* ---------------- ADMIN: has access to everything ---------------- */
void adminMenu()
{
    int ch;
    do
    {
        printf("\n================ ADMIN MENU ================\n");
        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Appointment Scheduling\n");
        printf("4. Medical Records\n");
        printf("5. Bed/Ward/Cabin Management\n");
        printf("6. OT Management\n");
        printf("7. Pharmacy/Inventory\n");
        printf("8. Billing/Invoicing\n");
        printf("9. Lab/Test Requests\n");
        printf("10. Reports/Dashboard\n");
        printf("0. Logout\n");
        printf("Choose: ");
        ch = readInt();
        switch (ch)
        {
        case 1:
            patientMenu();
            break;
        case 2:
            doctorMenu();
            break;
        case 3:
            appointmentMenu();
            break;
        case 4:
            recordMenu();
            break;
        case 5:
            bedMenu();
            break;
        case 6:
            otMenu();
            break;
        case 7:
            pharmacyMenu();
            break;
        case 8:
            billingMenu();
            break;
        case 9:
            labMenu();
            break;
        case 10:
            showDashboard();
            break;
        case 0:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid option, please try again.\n");
        }
    } while (ch != 0);
}

/* ---------------- DOCTOR: limited access ---------------- */
void doctorRoleMenu()
{
    int ch;
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
        ch = readInt();
        switch (ch)
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
    } while (ch != 0);
}

/* ---------------- RECEPTIONIST: limited access ---------------- */
void receptionistMenu()
{
    int ch;
    do
    {
        printf("\n============ RECEPTIONIST MENU ============\n");
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

/* ---------------- PHARMACIST: Pharmacy access only ---------------- */
void pharmacistMenu()
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

/* =================================================================
   LOGIN FUNCTION  (SECTION 1)
   ================================================================= */
int login()
{
    char uname[20], pass[20];
    printf("Enter Username: ");
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
int main()
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