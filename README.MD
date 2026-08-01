# 🏥 Healthcare Management System (HMS)

A console-based **Healthcare Management System** developed in **C Language** using **File Handling**. This project is designed to simulate the core operations of a hospital by managing patients, doctors, appointments, medical records, beds, medicines, billing, and administrative tasks.

The system demonstrates structured programming concepts, modular design, and persistent data storage using text files.

---

## 📌 Project Overview

The Healthcare Management System provides a simple yet practical solution for managing hospital operations. It allows administrators and medical staff to efficiently handle patient information, appointments, treatments, hospital resources, and billing while maintaining data persistence through file handling.

---

# ✨ Features

## 👤 Patient Management

- Register new patients
- Update patient information
- Search patients by ID
- View all patient records
- Archive/Delete patient records
- Store patient contact information

---

## 🏥 Patient Admission & Discharge

- Support both:
  - OPD (Outpatient)
  - IPD (Inpatient)
- Ward allocation
- Room assignment
- Bed allocation
- Admission date
- Discharge date
- Patient status:
  - Active
  - Discharged
- Billing clearance status before discharge

---

## 👨‍⚕️ Doctor Management

- Add new doctors
- Update doctor information
- Search doctor by ID
- View all doctors
- Department management
- Doctor specialization
- Visiting hours
- Maximum daily appointment limit

---

## 📅 Appointment Management

- Book appointments
- Prevent doctor overbooking
- View appointments
- Cancel appointments
- Search appointments
- Track follow-up dates
- Appointment scheduling

---

## 📋 Medical Records

Maintain complete patient medical history including:

- Diagnosis
- Treatment
- Prescription
- Vital signs
- Progress notes
- Timestamped doctor updates
- Follow-up date
- Assigned doctor

### Critical Medical Alerts

- Drug allergies
- Penicillin allergy
- Diabetes
- Hypertension
- Other pre-existing conditions

---

## 🛏 Bed Management

- Add hospital beds
- Track occupied beds
- Track available beds
- Assign beds to patients
- Release beds after discharge

---

## 💊 Medicine Management

- Add medicines
- Update medicine information
- Medicine stock management
- Medicine pricing
- Search medicines
- View available inventory

---

## 💰 Billing System

- Generate patient bills
- Calculate total cost
- Store payment status
- Billing history
- Clearance verification before discharge

---

## 🔐 Role-Based Authentication

### 👑 Administrator

- Full system access
- Add records
- Update records
- Delete records
- View all data
- Manage users

### 👨‍⚕️ Doctor / Nurse

- Login authentication
- View patient records
- Update medical notes
- Add prescriptions
- Cannot delete patient records

---

## 📊 Reports & Analytics

Generate reports such as:

- All registered patients
- Patients by assigned doctor
- Patients by diagnosis
- Medicine inventory report
- Appointment report
- Bed occupancy report
- Billing report

---

## 🔍 Search System

Search by:

- Patient ID
- Patient Name
- Doctor ID
- Doctor Name
- Diagnosis
- Disease
- Appointment ID
- Medicine Name

---

## 📁 Archive & Audit Log

Instead of permanently deleting records:

- Archive patient records
- Maintain audit logs
- Record deleted entries
- Preserve legal history


# 🛠 Technologies Used

- C Programming Language
- Standard C Library
- File Handling
- Structures
- Functions
- Modular Programming
- Arrays
- String Handling

---

# 📚 Concepts Demonstrated

- Structured Programming
- Modular Design
- File Handling
- CRUD Operations
- Authentication
- Searching Algorithms
- Data Validation
- Record Management
- Hospital Workflow Simulation

---


# 📖 Future Improvements

- Graphical User Interface (GUI)
- MySQL / SQLite Database Integration
- Barcode-based Patient Identification
- QR Code Support
- SMS / Email Appointment Reminders
- Pharmacy Billing
- Laboratory Management
- Multi-user Networking
- Cloud Backup
- Report Export (PDF / Excel)

---

## ⭐ Key Highlights

- Console-Based Hospital Management System
- Persistent File Storage
- Patient Admission & Discharge Tracking
- Appointment Scheduling
- Medical History Management
- Role-Based Authentication
- Billing & Medicine Management
- Bed Allocation
- Reporting & Analytics
- Archive & Audit Logging
- Beginner-Friendly C Project