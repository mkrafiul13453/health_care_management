/*
=====================================================================
   HEALTHCARE MANAGEMENT SYSTEM (HMS)  --  Beginner Friendly C Program
=====================================================================
   এই প্রোগ্রামে ১২টা Functional Requirement আছে। প্রত্যেকটা আলাদা
   section এ ভাগ করা আছে, যাতে সহজে বোঝা যায় কোন অংশ কোন কাজ করছে।

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
   12. Test Status Tracking                       -> (SECTION 11 এর ভিতরেই আছে)
=====================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------------------------------------------------------------
   MAX SIZE গুলো -- কতগুলো data  যাবে তার limit
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
    int doctorId; /* assigned doctor, -1 হলে কেউ assign করা নাই */
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
   HELPER FUNCTIONS (Input নেওয়ার জন্য সহজ function)
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
    buffer[strcspn(buffer, "\n")] = '\0'; /* শেষের \n মুছে দেয় */
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
    printf("\nContinue করতে Enter চাপুন...");
    getchar();
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
        printf("Patient list ভর্তি, আর নেওয়া যাবে না।\n");
        return;
    }
    Patient p;
    p.id = patientCount + 1; /* Unique Patient ID auto generate */
    printf("\n--- নতুন Patient Registration ---\n");
    printf("নাম দিন: ");
    getString(p.name, 50);
    printf("বয়স দিন: ");
    p.age = readInt();
    printf("Gender (Male/Female/Other): ");
    getString(p.gender, 10);
    printf("Disease/সমস্যা লিখুন: ");
    getString(p.disease, 100);
    printf("Phone Number: ");
    getString(p.phone, 15);
    p.doctorId = -1;
    p.active = 1;

    patients[patientCount] = p;
    patientCount++;

    printf("\n✅ Patient Registered সফল হয়েছে। Patient ID = %d\n", p.id);
}

void viewAllPatients()
{
    printf("\n--- সব Patient এর তালিকা ---\n");
    if (patientCount == 0)
    {
        printf("কোনো Patient নেই।\n");
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
        printf("Doctor list ভর্তি।\n");
        return;
    }
    Doctor d;
    d.id = doctorCount + 1;
    printf("\n--- নতুন Doctor যোগ করুন ---\n");
    printf("Doctor এর নাম: ");
    getString(d.name, 50);
    printf("Specialization (যেমন: Cardiologist): ");
    getString(d.specialization, 50);

    doctors[doctorCount] = d;
    doctorCount++;
    printf("\n✅ Doctor যোগ হয়েছে। Doctor ID = %d\n", d.id);
}

void viewAllDoctors()
{
    printf("\n--- সব Doctor এর তালিকা ---\n");
    if (doctorCount == 0)
    {
        printf("কোনো Doctor নেই।\n");
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
    printf("\n--- Patient কে Doctor Assign করুন ---\n");
    printf("Patient ID দিন: ");
    int pid = readInt();
    Patient *p = findPatientById(pid);
    if (!p)
    {
        printf("এই Patient ID পাওয়া যায়নি।\n");
        return;
    }

    printf("Doctor ID দিন: ");
    int did = readInt();
    Doctor *d = findDoctorById(did);
    if (!d)
    {
        printf("এই Doctor ID পাওয়া যায়নি।\n");
        return;
    }

    p->doctorId = did;
    printf("\n✅ %s কে Dr. %s এর সাথে Assign করা হয়েছে।\n", p->name, d->name);
}

void doctorDashboard()
{
    printf("\n--- Doctor Dashboard: Assigned Patients ---\n");
    printf("আপনার Doctor ID দিন: ");
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
        printf("এই Doctor এর কোনো Patient Assign করা নেই।\n");
}

/* =================================================================
   SECTION 4: APPOINTMENT SCHEDULING -- FUNCTIONS
   ================================================================= */
void bookAppointment()
{
    if (appointmentCount >= MAX_APPOINTMENTS)
    {
        printf("Appointment list ভর্তি।\n");
        return;
    }
    Appointment a;
    printf("\n--- নতুন Appointment বুক করুন ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient পাওয়া যায়নি।\n");
        return;
    }

    printf("Doctor ID: ");
    int did = readInt();
    if (!findDoctorById(did))
    {
        printf("Doctor পাওয়া যায়নি।\n");
        return;
    }

    char date[15], time[10];
    printf("Date দিন (DD-MM-YYYY): ");
    getString(date, 15);
    printf("Time দিন (HH:MM): ");
    getString(time, 10);

    /* Double booking check: একই Doctor, একই Date, একই Time */
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].status == 0 &&
            appointments[i].doctorId == did &&
            strcmp(appointments[i].date, date) == 0 &&
            strcmp(appointments[i].time, time) == 0)
        {
            printf("\n❌ এই সময়ে Doctor আগে থেকেই Booked আছে। অন্য সময় বেছে নিন।\n");
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
    printf("\n✅ Appointment Booked হয়েছে। Appointment ID = %d\n", a.id);
}

void cancelAppointment()
{
    printf("\n--- Appointment বাতিল করুন ---\n");
    printf("Appointment ID দিন: ");
    int id = readInt();
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].id == id && appointments[i].status == 0)
        {
            appointments[i].status = 1;
            printf("✅ Appointment বাতিল হয়েছে।\n");
            return;
        }
    }
    printf("এই ID তে কোনো Active Appointment পাওয়া যায়নি।\n");
}

void viewAppointments()
{
    printf("\n--- সব Appointment ---\n");
    if (appointmentCount == 0)
    {
        printf("কোনো Appointment নেই।\n");
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
        printf("Record list ভর্তি।\n");
        return;
    }
    MedicalRecord r;
    printf("\n--- নতুন Medical Record যোগ করুন ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient পাওয়া যায়নি।\n");
        return;
    }
    printf("Doctor ID: ");
    int did = readInt();
    if (!findDoctorById(did))
    {
        printf("Doctor পাওয়া যায়নি।\n");
        return;
    }

    r.id = recordCount + 1;
    r.patientId = pid;
    r.doctorId = did;
    printf("Diagnosis লিখুন: ");
    getString(r.diagnosis, 150);
    printf("Prescription লিখুন: ");
    getString(r.prescription, 150);
    printf("Date দিন (DD-MM-YYYY): ");
    getString(r.date, 15);

    records[recordCount] = r;
    recordCount++;
    printf("\n✅ Medical Record যোগ হয়েছে।\n");
}

void viewMedicalRecords()
{
    printf("\n--- Medical Records দেখুন ---\n");
    printf("Patient ID দিন (সব দেখতে 0 দিন): ");
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
        printf("কোনো Record পাওয়া যায়নি।\n");
}

/* =================================================================
   SECTION 6: BED / WARD / CABIN MANAGEMENT -- FUNCTIONS
   ================================================================= */
void initBeds()
{
    /* শুরুতে ২০টা বেড তৈরি হবে: 10 General, 5 ICU, 5 Cabin */
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
    printf("Patient ID দিন: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient পাওয়া যায়নি।\n");
        return;
    }

    char ward[20];
    printf("কোন Ward চান (General/ICU/Cabin): ");
    getString(ward, 20);

    for (int i = 0; i < bedCount; i++)
    {
        if (!beds[i].isOccupied && strcmp(beds[i].ward, ward) == 0)
        {
            beds[i].isOccupied = 1;
            beds[i].patientId = pid;
            printf("Admit Date দিন (DD-MM-YYYY): ");
            getString(beds[i].admitDate, 15);
            printf("\n✅ Patient কে Bed No %d (%s) এ Admit করা হয়েছে।\n",
                   beds[i].bedNo, beds[i].ward);
            return;
        }
    }
    printf("\n❌ দুঃখিত, %s Ward এ কোনো Free Bed নেই।\n", ward);
}

void dischargePatient()
{
    printf("\n--- Patient Discharge ---\n");
    printf("Bed Number দিন: ");
    int bedNo = readInt();
    for (int i = 0; i < bedCount; i++)
    {
        if (beds[i].bedNo == bedNo)
        {
            if (!beds[i].isOccupied)
            {
                printf("এই Bed তো আগে থেকেই Free আছে।\n");
                return;
            }
            beds[i].isOccupied = 0;
            beds[i].patientId = -1;
            strcpy(beds[i].admitDate, "-");
            printf("✅ Patient Discharge করা হয়েছে, Bed No %d এখন Free।\n", bedNo);
            return;
        }
    }
    printf("এই Bed Number পাওয়া যায়নি।\n");
}

/* =================================================================
   SECTION 7: OT MANAGEMENT -- FUNCTIONS
   ================================================================= */
void bookOT()
{
    if (otCount >= MAX_OT)
    {
        printf("OT booking list ভর্তি।\n");
        return;
    }
    OTBooking o;
    printf("\n--- Surgery / OT Booking ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient পাওয়া যায়নি।\n");
        return;
    }

    o.id = otCount + 1;
    o.patientId = pid;
    printf("Surgery Type লিখুন: ");
    getString(o.surgeryType, 50);
    printf("Date দিন (DD-MM-YYYY): ");
    getString(o.date, 15);
    strcpy(o.status, "Scheduled");

    otBookings[otCount] = o;
    otCount++;
    printf("\n✅ OT Booking সম্পন্ন হয়েছে। OT Booking ID = %d\n", o.id);
}

void updateOTStatus()
{
    printf("\n--- OT Status আপডেট করুন ---\n");
    printf("OT Booking ID দিন: ");
    int id = readInt();
    for (int i = 0; i < otCount; i++)
    {
        if (otBookings[i].id == id)
        {
            printf("নতুন Status দিন (Scheduled/Completed/Cancelled): ");
            getString(otBookings[i].status, 20);
            printf("✅ Status আপডেট হয়েছে।\n");
            return;
        }
    }
    printf("এই ID পাওয়া যায়নি।\n");
}

void viewOTBookings()
{
    printf("\n--- সব OT Booking ---\n");
    if (otCount == 0)
    {
        printf("কোনো OT Booking নেই।\n");
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
        printf("Medicine list ভর্তি।\n");
        return;
    }
    Medicine m;
    m.id = medicineCount + 1;
    printf("\n--- নতুন Medicine যোগ করুন ---\n");
    printf("Medicine এর নাম: ");
    getString(m.name, 50);
    printf("Stock পরিমাণ: ");
    m.stock = readInt();
    printf("Price (প্রতি ইউনিট): ");
    m.price = readFloat();

    medicines[medicineCount] = m;
    medicineCount++;
    printf("\n✅ Medicine যোগ হয়েছে। Medicine ID = %d\n", m.id);
}

void viewInventory()
{
    printf("\n--- Inventory / Stock তালিকা ---\n");
    if (medicineCount == 0)
    {
        printf("কোনো Medicine নেই।\n");
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
    printf("\n--- Medicine বিক্রি করুন ---\n");
    printf("Medicine ID: ");
    int id = readInt();
    Medicine *m = findMedicineById(id);
    if (!m)
    {
        printf("Medicine পাওয়া যায়নি।\n");
        return;
    }

    printf("কত পরিমাণ বিক্রি করবেন: ");
    int qty = readInt();
    if (qty > m->stock)
    {
        printf("❌ পর্যাপ্ত Stock নেই। বর্তমান Stock: %d\n", m->stock);
        return;
    }
    m->stock -= qty;
    printf("\n✅ বিক্রি সম্পন্ন। মোট দাম: %.2f\n", qty * m->price);

    if (m->stock < LOW_STOCK_LIMIT)
    {
        printf("⚠️  সতর্কতা: %s এর Stock কমে গেছে (%d বাকি)। দ্রুত নতুন Stock আনুন।\n",
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
        printf("Medicine পাওয়া যায়নি।\n");
        return;
    }

    printf("কত পরিমাণ Damaged: ");
    int qty = readInt();
    if (qty > m->stock)
    {
        printf("❌ এত পরিমাণ Stock এ নেই।\n");
        return;
    }
    m->stock -= qty;
    printf("✅ Damaged Stock বাদ দেওয়া হয়েছে। বর্তমান Stock: %d\n", m->stock);
}

/* =================================================================
   SECTION 9: BILLING / INVOICING -- FUNCTIONS
   ================================================================= */
void generateBill()
{
    if (billCount >= MAX_BILLS)
    {
        printf("Bill list ভর্তি।\n");
        return;
    }
    Bill b;
    printf("\n--- নতুন Bill তৈরি করুন ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient পাওয়া যায়নি।\n");
        return;
    }

    b.id = billCount + 1;
    b.patientId = pid;

    printf("Consultation Fee দিন: ");
    b.consultationFee = readFloat();
    printf("Medicine Bill দিন: ");
    b.medicineBill = readFloat();
    printf("Bed/Ward Bill দিন: ");
    b.bedBill = readFloat();
    printf("OT Bill দিন (না থাকলে 0): ");
    b.otBill = readFloat();

    b.totalBill = b.consultationFee + b.medicineBill + b.bedBill + b.otBill;
    b.paidAmount = 0;
    b.dueAmount = b.totalBill;

    bills[billCount] = b;
    billCount++;
    printf("\n✅ Bill তৈরি হয়েছে। Bill ID = %d | Total = %.2f\n", b.id, b.totalBill);
}

void makePayment()
{
    printf("\n--- Payment করুন (Partial Payment ও সাপোর্ট করে) ---\n");
    printf("Bill ID দিন: ");
    int id = readInt();
    for (int i = 0; i < billCount; i++)
    {
        if (bills[i].id == id)
        {
            printf("বর্তমান বকেয়া (Due): %.2f\n", bills[i].dueAmount);
            printf("কত টাকা দিচ্ছেন: ");
            float amt = readFloat();
            if (amt > bills[i].dueAmount)
            {
                printf("❌ এত টাকা বকেয়ার চেয়ে বেশি। সঠিক টাকা দিন।\n");
                return;
            }
            bills[i].paidAmount += amt;
            bills[i].dueAmount -= amt;
            printf("✅ Payment সম্পন্ন। বাকি Due = %.2f\n", bills[i].dueAmount);
            return;
        }
    }
    printf("এই Bill ID পাওয়া যায়নি।\n");
}

void printInvoice()
{
    printf("\n--- Invoice Print করুন ---\n");
    printf("Bill ID দিন: ");
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
    printf("এই Bill ID পাওয়া যায়নি।\n");
}

void viewAllBills()
{
    printf("\n--- সব Bill এর তালিকা ---\n");
    if (billCount == 0)
    {
        printf("কোনো Bill নেই।\n");
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
        printf("Lab Test list ভর্তি।\n");
        return;
    }
    LabTest t;
    printf("\n--- নতুন Lab Test Request ---\n");
    printf("Patient ID: ");
    int pid = readInt();
    if (!findPatientById(pid))
    {
        printf("Patient পাওয়া যায়নি।\n");
        return;
    }

    t.id = labTestCount + 1;
    t.patientId = pid;
    printf("Test এর নাম লিখুন (যেমন: Blood Test): ");
    getString(t.testName, 50);
    strcpy(t.status, "Pending");
    strcpy(t.result, "-");

    labTests[labTestCount] = t;
    labTestCount++;
    printf("\n✅ Lab Test Request করা হয়েছে। Test ID = %d (Status: Pending)\n", t.id);
}

void updateTestStatus()
{
    printf("\n--- Lab Test Status আপডেট করুন ---\n");
    printf("Test ID দিন: ");
    int id = readInt();
    for (int i = 0; i < labTestCount; i++)
    {
        if (labTests[i].id == id)
        {
            strcpy(labTests[i].status, "Completed");
            printf("Test Result লিখুন: ");
            getString(labTests[i].result, 100);
            printf("✅ Test Status 'Completed' করা হয়েছে এবং Result Patient এর সাথে Link করা হয়েছে।\n");
            return;
        }
    }
    printf("এই Test ID পাওয়া যায়নি।\n");
}

void viewLabTests()
{
    printf("\n--- সব Lab Test এর তালিকা ---\n");
    if (labTestCount == 0)
    {
        printf("কোনো Test নেই।\n");
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
    printf("মোট Patient সংখ্যা          : %d\n", patientCount);
    printf("মোট Doctor সংখ্যা           : %d\n", doctorCount);
    printf("মোট Appointment সংখ্যা      : %d\n", appointmentCount);
    printf("মোট Bed সংখ্যা               : %d\n", bedCount);
    printf("Occupied Bed সংখ্যা          : %d\n", occupiedBeds);
    printf("Free Bed সংখ্যা              : %d\n", bedCount - occupiedBeds);
    printf("মোট OT Booking সংখ্যা       : %d\n", otCount);
    printf("Low Stock Medicine সংখ্যা   : %d\n", lowStockCount);
    printf("Pending Lab Test সংখ্যা     : %d\n", pendingTests);
    printf("মোট Collected টাকা          : %.2f\n", totalCollected);
    printf("মোট বকেয়া (Due) টাকা        : %.2f\n", totalDue);
    printf("==================================================\n");
}

/* =================================================================
   MENUS  (Role Based Access -- SECTION 1 এর অংশ)
   ================================================================= */
void patientMenu()
{
    int ch;
    do
    {
        printf("\n---- Patient Management ----\n");
        printf("1. Patient Register করুন\n2. সব Patient দেখুন\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. Doctor যোগ করুন\n2. সব Doctor দেখুন\n3. Patient কে Doctor Assign করুন\n4. Doctor Dashboard\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. Appointment Book করুন\n2. Appointment Cancel করুন\n3. সব Appointment দেখুন\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. নতুন Record যোগ করুন\n2. Record দেখুন\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. Bed Status দেখুন\n2. Patient Admit করুন\n3. Patient Discharge করুন\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. OT Booking করুন\n2. OT Status আপডেট করুন\n3. সব OT Booking দেখুন\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. Medicine যোগ করুন\n2. Inventory দেখুন\n3. Medicine বিক্রি করুন\n4. Damaged Stock Entry\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. নতুন Bill তৈরি করুন\n2. Payment করুন\n3. Invoice Print করুন\n4. সব Bill দেখুন\n0. পিছনে যান\nবেছে নিন: ");
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
        printf("1. Test Request করুন\n2. Test Status আপডেট করুন (Pending->Completed)\n3. সব Test দেখুন\n0. পিছনে যান\nবেছে নিন: ");
        ch = readInt();
        if (ch == 1)
            requestLabTest();
        else if (ch == 2)
            updateTestStatus();
        else if (ch == 3)
            viewLabTests();
    } while (ch != 0);
}

/* ---------------- ADMIN: সবকিছুর Access আছে ---------------- */
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
        printf("বেছে নিন: ");
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
            printf("Logout হচ্ছেন...\n");
            break;
        default:
            printf("ভুল Option, আবার চেষ্টা করুন।\n");
        }
    } while (ch != 0);
}

/* ---------------- DOCTOR: সীমিত Access ---------------- */
void doctorRoleMenu()
{
    int ch;
    do
    {
        printf("\n================ DOCTOR MENU ================\n");
        printf("1. Assigned Patients দেখুন (Dashboard)\n");
        printf("2. Medical Record যোগ করুন\n");
        printf("3. Medical Record দেখুন\n");
        printf("4. Lab Test Request করুন\n");
        printf("5. OT Booking দেখুন\n");
        printf("0. Logout\n");
        printf("বেছে নিন: ");
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
            printf("Logout হচ্ছেন...\n");
            break;
        default:
            printf("ভুল Option, আবার চেষ্টা করুন।\n");
        }
    } while (ch != 0);
}

/* ---------------- RECEPTIONIST: সীমিত Access ---------------- */
void receptionistMenu()
{
    int ch;
    do
    {
        printf("\n============ RECEPTIONIST MENU ============\n");
        printf("1. Patient Register করুন\n");
        printf("2. সব Patient দেখুন\n");
        printf("3. Appointment Scheduling\n");
        printf("4. Bed/Ward/Cabin Management\n");
        printf("5. OT Booking করুন\n");
        printf("6. Billing/Invoicing\n");
        printf("0. Logout\n");
        printf("বেছে নিন: ");
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
            printf("Logout হচ্ছেন...\n");
            break;
        default:
            printf("ভুল Option, আবার চেষ্টা করুন।\n");
        }
    } while (ch != 0);
}

/* ---------------- PHARMACIST: শুধু Pharmacy Access ---------------- */
void pharmacistMenu()
{
    int ch;
    do
    {
        printf("\n============ PHARMACIST MENU ============\n");
        printf("1. Medicine যোগ করুন\n");
        printf("2. Inventory দেখুন\n");
        printf("3. Medicine বিক্রি করুন\n");
        printf("4. Damaged Stock Entry\n");
        printf("0. Logout\n");
        printf("বেছে নিন: ");
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
            printf("Logout হচ্ছেন...\n");
            break;
        default:
            printf("ভুল Option, আবার চেষ্টা করুন।\n");
        }
    } while (ch != 0);
}

/* =================================================================
   LOGIN FUNCTION  (SECTION 1)
   ================================================================= */
int login()
{
    char uname[20], pass[20];
    printf("Username দিন: ");
    getString(uname, 20);
    printf("Password দিন: ");
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
    
    initBeds(); /* প্রোগ্রাম শুরু হলে ২০টা Bed তৈরি হয়ে যায় */

    printf("=====================================================\n");
    printf("      HEALTHCARE MANAGEMENT SYSTEM (HMS)\n");
    printf("=====================================================\n");
    printf("Demo Login তথ্য:\n");
    printf("  Admin        -> username: admin        password: admin123\n");
    printf("  Doctor       -> username: doctor1       password: doc123\n");
    printf("  Receptionist -> username: reception1    password: rec123\n");
    printf("  Pharmacist   -> username: pharma1       password: pharma123\n");
    printf("=====================================================\n\n");

    printf("---- LOGIN ----\n");
    int idx = login();

    if (idx == -1)
    {
        printf("\n❌ ভুল Username/Password। প্রোগ্রাম বন্ধ হচ্ছে।\n");
        return 0;
    }

    printf("\n✅ স্বাগতম, %s (Role: %s)\n", users[idx].username, users[idx].role);

    if (strcmp(users[idx].role, "Admin") == 0)
        adminMenu();
    else if (strcmp(users[idx].role, "Doctor") == 0)
        doctorRoleMenu();
    else if (strcmp(users[idx].role, "Receptionist") == 0)
        receptionistMenu();
    else if (strcmp(users[idx].role, "Pharmacist") == 0)
        pharmacistMenu();

    printf("\nধন্যবাদ, HMS ব্যবহার করার জন্য।\n");
    return 0;
}