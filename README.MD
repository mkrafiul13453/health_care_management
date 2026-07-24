# Healthcare Management System 

Here are several practical, realistic feature expansions that build directly on top of your C file-handling baseline. These additions fit naturally into the same program architecture and reflect real-world clinical and administrative workflows.

Additional Core Requirements & Features:
1. Patient Admission & Discharge Tracking
Bed & Ward Allocation: Track whether a patient is Inpatient (IPD) or Outpatient (OPD), including assigned Ward/Room number and Bed number.

Discharge Summary & Billing Status: Mark records as Active or Discharged, capture discharge dates, and store payment/clearance status before deleting or archiving files.

2. Appointment & Schedule Management
Doctor Availability Check: Maintain a simple schedule (e.g., Visiting Hours, Max Daily Limit) to prevent overbooking doctors during record insertion.

Follow-up Reminders: Store a Next Follow-Up Date in the medical history field so staff can query which patients are due for checkups today/this week.

3. Structured Medical History & Vital Signs
Chronological Progress Logs: Instead of a single static string for treatment, append timestamped updates (Date, Doctor Note, Prescription, Vitals).

Allergies & Pre-existing Conditions: Add dedicated flags for critical medical alerts (e.g., Penicillin Allergy, Diabetic, Hypertension) to alert staff immediately during lookup.

4. Role-Based Data Access (Basic Authentication)
Staff Login Screen: Simple credential checks (Admin vs. Medical Staff).

Admins: Full access (Insert, Update, Delete, View All).

Doctors/Nurses: Read & Update medical notes/treatments only (cannot delete patient accounts).

5. Data Reporting & Search Analytics
Search by Doctor: Filter and display all patients currently assigned to a specific doctor.

Search by Diagnosis/Condition: Query records to count how many patients are being treated for a specific condition (e.g., "Flu", "Fracture").

Archive & Audit Logs: Instead of permanently deleting records with remove(), flag records as Archived or append deleted entries to an audit_log.txt file for legal compliance.
