/*
=====================================================================
   HEALTHCARE MANAGEMENT SYSTEM -- SHARED HEADER (hms.h)
=====================================================================
   This header is shared by every source file in the project
   (admin.c, doctor.c, reception.c, pharmacy.c, hms.c).

   It contains:
     - Data structures (Patient, Doctor, Appointment, ...)
     - Size limits and CSV file name constants
     - "extern" declarations of the global data arrays, so that
       every .c file can access the same in-memory data
     - Prototypes of every function, so that any file can call a
       function that is defined in another file

   NOTE: The actual data (patients[], doctors[], ...) and most of
   the business-logic functions are DEFINED once, in admin.c, since
   several roles (Admin, Doctor, Receptionist) share the same
   underlying functions (e.g. bedMenu, billingMenu, viewOTBookings).
   Defining them only once avoids "multiple definition" linker
   errors while keeping the exact same functionality as before.
=====================================================================
*/

#ifndef HMS_H
#define HMS_H

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

/* ---------------------------------------------------------------
   SECTION 3: DOCTOR MANAGEMENT
   --------------------------------------------------------------- */
typedef struct
{
    int id;
    char name[50];
    char specialization[50];
} Doctor;

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

/* =================================================================
   GLOBAL DATA (defined once in admin.c, shared via "extern" here)
   ================================================================= */
extern Patient patients[MAX_PATIENTS];
extern int patientCount;

extern Doctor doctors[MAX_DOCTORS];
extern int doctorCount;

extern Appointment appointments[MAX_APPOINTMENTS];
extern int appointmentCount;

extern MedicalRecord records[MAX_RECORDS];
extern int recordCount;

extern Bed beds[MAX_BEDS];
extern int bedCount;

extern OTBooking otBookings[MAX_OT];
extern int otCount;

extern Medicine medicines[MAX_MEDICINES];
extern int medicineCount;

extern Bill bills[MAX_BILLS];
extern int billCount;

extern LabTest labTests[MAX_LABTESTS];
extern int labTestCount;

/* =================================================================
   HELPER FUNCTIONS (admin.c)
   ================================================================= */
void clearBuffer(void);
void getString(char *buffer, int size);
int readInt(void);
float readFloat(void);
void pause(void);

/* =================================================================
   CSV FILE STORAGE (admin.c)
   ================================================================= */
void savePatientsToCSV(void);
void loadPatientsFromCSV(void);
void saveDoctorsToCSV(void);
void loadDoctorsFromCSV(void);
void saveAppointmentsToCSV(void);
void loadAppointmentsFromCSV(void);
void saveRecordsToCSV(void);
void loadRecordsFromCSV(void);
void saveBedsToCSV(void);
int loadBedsFromCSV(void);
void saveOTToCSV(void);
void loadOTFromCSV(void);
void saveMedicinesToCSV(void);
void loadMedicinesFromCSV(void);
void saveBillsToCSV(void);
void loadBillsFromCSV(void);
void saveLabTestsToCSV(void);
void loadLabTestsFromCSV(void);
void loadAllDataFromCSV(void);

/* =================================================================
   SECTION 2: PATIENT REGISTRATION -- FUNCTIONS (admin.c)
   ================================================================= */
Patient *findPatientById(int id);
void registerPatient(void);
void viewAllPatients(void);

/* =================================================================
   SECTION 3: DOCTOR MANAGEMENT -- FUNCTIONS (admin.c)
   ================================================================= */
Doctor *findDoctorById(int id);
void addDoctor(void);
void viewAllDoctors(void);
void assignDoctorToPatient(void);
void doctorDashboard(void);

/* =================================================================
   SECTION 4: APPOINTMENT SCHEDULING -- FUNCTIONS (admin.c)
   ================================================================= */
void bookAppointment(void);
void cancelAppointment(void);
void viewAppointments(void);

/* =================================================================
   SECTION 5: MEDICAL RECORDS -- FUNCTIONS (admin.c)
   ================================================================= */
void addMedicalRecord(void);
void viewMedicalRecords(void);

/* =================================================================
   SECTION 6: BED / WARD / CABIN MANAGEMENT -- FUNCTIONS (admin.c)
   ================================================================= */
void initBeds(void);
void viewBedStatus(void);
void admitPatient(void);
void dischargePatient(void);

/* =================================================================
   SECTION 7: OT MANAGEMENT -- FUNCTIONS (admin.c)
   ================================================================= */
void bookOT(void);
void updateOTStatus(void);
void viewOTBookings(void);

/* =================================================================
   SECTION 8: PHARMACY / INVENTORY -- FUNCTIONS (admin.c)
   ================================================================= */
Medicine *findMedicineById(int id);
void addMedicine(void);
void viewInventory(void);
void sellMedicine(void);
void addDamagedStock(void);

/* =================================================================
   SECTION 9: BILLING / INVOICING -- FUNCTIONS (admin.c)
   ================================================================= */
void generateBill(void);
void makePayment(void);
void printInvoice(void);
void viewAllBills(void);

/* =================================================================
   SECTION 11 & 12: LAB TEST REQUEST + STATUS TRACKING (admin.c)
   ================================================================= */
void requestLabTest(void);
void updateTestStatus(void);
void viewLabTests(void);

/* =================================================================
   SECTION 10: REPORTS / DASHBOARD (admin.c)
   ================================================================= */
void showDashboard(void);

/* =================================================================
   SHARED SUB-MENUS (admin.c) -- reused by more than one role
   ================================================================= */
void patientMenu(void);
void doctorMenu(void);
void appointmentMenu(void);
void recordMenu(void);
void bedMenu(void);
void otMenu(void);
void pharmacyMenu(void);
void billingMenu(void);
void labMenu(void);

/* =================================================================
   ROLE-BASED MAIN MENUS
   ================================================================= */
void adminMenu(void);        /* defined in admin.c     */
void doctorRoleMenu(void);   /* defined in doctor.c    */
void receptionistMenu(void); /* defined in reception.c */
void pharmacistMenu(void);   /* defined in pharmacy.c  */

#endif /* HMS_H */