#include "hms.h"

/* =================================================================
   GLOBAL DATA DEFINITIONS
   ================================================================= */
Patient patients[maxPatient];
int patientCount = 0;

Doctor doctors[maxDoctors];
int doctorCount = 0;

Appointment appointments[maxAppointments];
int appointmentCount = 0;

MedicalRecord records[maxRecords];
int recordCount = 0;

Bed beds[maxBeds];
int bedCount = 0;

OTBooking otBookings[maxOT];
int otCount = 0;

Medicine medicines[maxMedicines];
int medicineCount = 0;

Bill bills[maxBills];
int billCount = 0;

LabTest labTests[maxLabTests];
int labTestCount = 0;

/* =================================================================
   HELPER FUNCTIONS (for taking input easily)
   ================================================================= */
void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void getString(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; 
}

int readInt(void)
{
    int x;
    scanf("%d", &x);
    clearBuffer();
    return x;
}

float readFloat(void)
{
    float x;
    scanf("%f", &x);
    clearBuffer();
    return x;
}

void pause(void)
{
    printf("\nPress Enter to continue...");
    getchar();
}

/* =================================================================
   SECTION 13: CSV FILE STORAGE (SAVE / LOAD)
   ================================================================= */

/* ---------------- Patients ---------------- */
void savePatientsToCSV(void)
{
    FILE *fp = fopen(patientsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", patientsFile);
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

void loadPatientsFromCSV(void)
{
    FILE *fp = fopen(patientsFile, "r");
    if (!fp)
        return; 
    char line[300];
    fgets(line, sizeof(line), fp); 
    patientCount = 0;
    while (patientCount < maxPatient &&
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
void saveDoctorsToCSV(void)
{
    FILE *fp = fopen(doctorsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", doctorsFile);
        return;
    }
    fprintf(fp, "id,name,specialization\n");
    for (int i = 0; i < doctorCount; i++)
    {
        fprintf(fp, "%d,%s,%s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
    }
    fclose(fp);
}

void loadDoctorsFromCSV(void)
{
    FILE *fp = fopen(doctorsFile, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    doctorCount = 0;
    while (doctorCount < maxDoctors &&
           fscanf(fp, "%d,%49[^,],%49[^\n]\n",
                  &doctors[doctorCount].id, doctors[doctorCount].name,
                  doctors[doctorCount].specialization) == 3)
    {
        doctorCount++;
    }
    fclose(fp);
}

/* ---------------- Appointments ---------------- */
void saveAppointmentsToCSV(void)
{
    FILE *fp = fopen(appointmentsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", appointmentsFile);
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

void loadAppointmentsFromCSV(void)
{
    FILE *fp = fopen(appointmentsFile, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    appointmentCount = 0;
    while (appointmentCount < maxAppointments &&
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
void saveRecordsToCSV(void)
{
    FILE *fp = fopen(recordsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", recordsFile);
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

void loadRecordsFromCSV(void)
{
    FILE *fp = fopen(recordsFile, "r");
    if (!fp)
        return;
    char line[400];
    fgets(line, sizeof(line), fp);
    recordCount = 0;
    while (recordCount < maxRecords &&
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
void saveBedsToCSV(void)
{
    FILE *fp = fopen(bedsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", bedsFile);
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

int loadBedsFromCSV(void)
{
    FILE *fp = fopen(bedsFile, "r");
    if (!fp)
        return 0; /* no saved file yet */
    char line[200];
    fgets(line, sizeof(line), fp);
    bedCount = 0;
    while (bedCount < maxBeds &&
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
void saveOTToCSV(void)
{
    FILE *fp = fopen(otFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", otFile);
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

void loadOTFromCSV(void)
{
    FILE *fp = fopen(otFile, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    otCount = 0;
    while (otCount < maxOT &&
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
void saveMedicinesToCSV(void)
{
    FILE *fp = fopen(medicinesFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", medicinesFile);
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

void loadMedicinesFromCSV(void)
{
    FILE *fp = fopen(medicinesFile, "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, sizeof(line), fp);
    medicineCount = 0;
    while (medicineCount < maxMedicines &&
           fscanf(fp, "%d,%49[^,],%d,%f\n",
                  &medicines[medicineCount].id, medicines[medicineCount].name,
                  &medicines[medicineCount].stock, &medicines[medicineCount].price) == 4)
    {
        medicineCount++;
    }
    fclose(fp);
}

/* ---------------- Bills ---------------- */
void saveBillsToCSV(void)
{
    FILE *fp = fopen(billsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", billsFile);
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

void loadBillsFromCSV(void)
{
    FILE *fp = fopen(billsFile, "r");
    if (!fp)
        return;
    char line[300];
    fgets(line, sizeof(line), fp);
    billCount = 0;
    while (billCount < maxBills &&
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
void saveLabTestsToCSV(void)
{
    FILE *fp = fopen(labTestsFile, "w");
    if (!fp)
    {
        printf("Error: could not save %s\n", labTestsFile);
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

void loadLabTestsFromCSV(void)
{
    FILE *fp = fopen(labTestsFile, "r");
    if (!fp)
        return;
    char line[300];
    fgets(line, sizeof(line), fp);
    labTestCount = 0;
    while (labTestCount < maxLabTests &&
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
void loadAllDataFromCSV(void)
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

void registerPatient(void)
{
    if (patientCount >= maxPatient)
    {
        printf("Patient list is full, cannot add more.\n");
        return;
    }
    Patient p;
    p.id = patientCount + 1; 
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

void viewAllPatients(void)
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

void addDoctor(void)
{
    if (doctorCount >= maxDoctors)
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

void viewAllDoctors(void)
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

void assignDoctorToPatient(void)
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

void doctorDashboard(void)
{
    printf("\n--- Doctor Dashboard: Assigned Patients ---\n");
    printf("Enter Doctor ID: ");
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
        printf("No patients assigned.\n");
}

/* =================================================================
   SECTION 4: APPOINTMENT SCHEDULING -- FUNCTIONS
   ================================================================= */
void bookAppointment(void)
{
    if (appointmentCount >= maxAppointments)
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

void cancelAppointment(void)
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

void viewAppointments(void)
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
void addMedicalRecord(void)
{
    if (recordCount >= maxRecords)
    {
        printf("MedicalRecord list is full.\n");
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

void viewMedicalRecords(void)
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
void initBeds(void)
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

void viewBedStatus(void)
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

void admitPatient(void)
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

void dischargePatient(void)
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
void bookOT(void)
{
    if (otCount >= maxOT)
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

void updateOTStatus(void)
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

void viewOTBookings(void)     
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

void addMedicine(void)
{
    if (medicineCount >= maxMedicines)
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

void viewInventory(void)
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

void sellMedicine(void)
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

void addDamagedStock(void)
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
void generateBill(void)
{
    if (billCount >= maxBills)
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

void makePayment(void)
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

void printInvoice(void)
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

void viewAllBills(void)
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
void requestLabTest(void)
{
    if (labTestCount >= maxLabTests)
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

void updateTestStatus(void)
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

void viewLabTests(void)
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
void showDashboard(void)
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
   SHARED SUB-MENUS  (Role Based Access -- part of SECTION 1)
   ================================================================= */
void patientMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Patient Management ----\n");
        printf("1. Register Patient\n2. View All Patients\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            registerPatient();
        else if (choice == 2)
            viewAllPatients();
    } while (choice);
}

void doctorMenu(void)
{
    int cchoiceh;
    do
    {
        printf("\n---- Doctor Management ----\n");
        printf("1. Add Doctor\n2. View All Doctors\n3. Assign Doctor to Patient\n4. Doctor Dashboard\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            addDoctor();
        else if (choice == 2)
            viewAllDoctors();
        else if (choice == 3)
            assignDoctorToPatient();
        else if (choice == 4)
            doctorDashboard();
    } while (choice != 0);
}

void appointmentMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Appointment Scheduling ----\n");
        printf("1. Book Appointment\n2. Cancel Appointment\n3. View All Appointments\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            bookAppointment();
        else if (choice == 2)
            cancelAppointment();
        else if (choice == 3)
            viewAppointments();
    } while (choice != 0);
}

void recordMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Medical Records ----\n");
        printf("1. Add New Record\n2. View Records\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            addMedicalRecord();
        else if (choice == 2)
            viewMedicalRecords();
    } while (choice != 0);
}

void bedMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Bed/Ward/Cabin Management ----\n");
        printf("1. View Bed Status\n2. Admit Patient\n3. Discharge Patient\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice)
            viewBedStatus();
        else if (choice == 2)
            admitPatient();
        else if (choice == 3)
            dischargePatient();
    } while (choice != 0);
}

void otMenu(void)
{
    int choice;
    do
    {
        printf("\n---- OT Management ----\n");
        printf("1. Book OT\n2. Update OT Status\n3. View All OT Bookings\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            bookOT();
        else if (choice == 2)
            updateOTStatus();
        else if (choice == 3)
            viewOTBookings();
    } while (choice != 0);
}

void pharmacyMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Pharmacy / Inventory ----\n");
        printf("1. Add Medicine\n2. View Inventory\n3. Sell Medicine\n4. Damaged Stock Entry\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            addMedicine();
        else if (choice == 2)
            viewInventory();
        else if (choice == 3)
            sellMedicine();
        else if (choice == 4)
            addDamagedStock();
    } while (choice != 0);
}

void billingMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Billing / Invoicing ----\n");
        printf("1. Generate New Bill\n2. Make Payment\n3. Print Invoice\n4. View All Bills\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            generateBill();
        else if (choice == 2)
            makePayment();
        else if (choice == 3)
            printInvoice();
        else if (choice == 4)
            viewAllBills();
    } while (choice != 0);
}

void labMenu(void)
{
    int choice;
    do
    {
        printf("\n---- Lab / Test Requests ----\n");
        printf("1. Request Test\n2. Update Test Status (Pending->Completed)\n3. View All Tests\n0. Go Back\nChoose: ");
        choice = readInt();
        if (choice == 1)
            requestLabTest();
        else if (choice == 2)
            updateTestStatus();
        else if (choice == 3)
            viewLabTests();
    } while (choice != 0);
}

/* =================================================================
   ADMIN ROLE MENU -- has access to everything
   ================================================================= */
void adminMenu(void)
{
    int choice;
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
        choice = readInt();
        switch (choice)
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
    } while (choice != 0);
}