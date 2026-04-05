#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>

using namespace std;

// ============================================
// STRUCTURE: Employee with 4 fields
// ============================================
struct Employee {
    int empId;           // Field 1: Employee ID
    char name[50];       // Field 2: Employee Name
    double salary;       // Field 3: Salary amount
    bool isFullTime;     // Field 4: Full time status
};

// ============================================
// LIST OF NAMES for random selection
// ============================================
const char* NAMES[] = {
    "John Smith", "Anna Johnson", "Peter Williams",
    "Maria Garcia", "David Brown", "Sarah Davis",
    "James Wilson", "Linda Martinez", "Robert Taylor",
    "Patricia Anderson", "Michael Thomas", "Jennifer Lee",
    "Christopher Moore", "Jessica White", "Daniel Harris"
};
const int NAME_COUNT = 15;

// ============================================
// FUNCTION: Generate random employee
// ============================================
Employee generateRandomEmployee() {
    Employee emp;

    // Random ID between 1000 and 9999
    emp.empId = 1000 + (rand() % 9000);

    // Random name from the list
    int nameIndex = rand() % NAME_COUNT;
    strcpy_s(emp.name, NAMES[nameIndex]);

    // Random salary between 30000.00 and 149999.99
    emp.salary = 30000 + (rand() % 120000) + (rand() % 100) / 100.0;

    // Random full-time status (true = 1, false = 0)
    emp.isFullTime = rand() % 2;

    return emp;
}

// ============================================
// FUNCTION: Display single employee in table format
// ============================================
void displayEmployee(Employee emp, int number) {
    cout << "| " << setw(6) << emp.empId
        << " | " << setw(20) << emp.name
        << " | $ " << setw(9) << fixed << setprecision(2) << emp.salary
        << " | " << setw(8) << (emp.isFullTime ? "Yes" : "No")
        << " |" << endl;
}

// ============================================
// FUNCTION: Display table header
// ============================================
void displayHeader() {
    cout << "\n================================================================================" << endl;
    cout << "| " << setw(6) << "ID"
        << " | " << setw(20) << "Name"
        << " | " << setw(10) << "Salary"
        << " | " << setw(8) << "Full Time"
        << " |" << endl;
    cout << "================================================================================" << endl;
}

// ============================================
// FUNCTION: Display table footer
// ============================================
void displayFooter() {
    cout << "================================================================================" << endl;
}

// ============================================
// MAIN FUNCTION
// ============================================
int main() {
    // Seed random number generator
    srand(time(0));

    cout << "\n========================================" << endl;
    cout << "     BINARY JOURNAL - EMPLOYEE RECORDS" << endl;
    cout << "========================================" << endl;

    // ============================================
    // PART 1: WRITE 10 EMPLOYEES TO BINARY FILE
    // ============================================

    // Open file for writing in binary mode
    ofstream outFile("employees.bin", ios::out | ios::binary);

    // Check if file opened successfully
    if (!outFile) {
        cout << "ERROR: Cannot create file!" << endl;
        return 1;
    }

    cout << "\n[1] Generating 10 random employees..." << endl;

    // Generate and write 10 employees
    Employee employees[10];
    for (int i = 0; i < 10; i++) {
        employees[i] = generateRandomEmployee();
        // Write the employee to binary file
        outFile.write((char*)&employees[i], sizeof(Employee));
    }

    // Close the file
    outFile.close();
    cout << "[OK] 10 employees written to 'employees.bin'" << endl;// ============================================
    // PART 2: READ EMPLOYEES FROM BINARY FILE
    // ============================================

    // Open file for reading in binary mode
    ifstream inFile("employees.bin", ios::in | ios::binary);

    // Check if file opened successfully
    if (!inFile) {
        cout << "ERROR: Cannot open file for reading!" << endl;
        return 1;
    }

    cout << "\n[2] Reading employees from 'employees.bin'..." << endl;

    // Display header
    displayHeader();

    // Read and display all employees
    Employee emp;
    int recordCount = 0;
    while (inFile.read((char*)&emp, sizeof(Employee))) {
        displayEmployee(emp, recordCount + 1);
        recordCount++;
    }

    // Display footer
    displayFooter();

    // Close the file
    inFile.close();

    cout << "\nTotal records read: " << recordCount << endl;

    // ============================================
    // PART 3: GET FILE SIZE IN BYTES
    // ============================================

    // Open file to get size
    inFile.open("employees.bin", ios::in | ios::binary);

    if (inFile) {
        // Move to end of file
        inFile.seekg(0, ios::end);
        // Get current position (which is file size)
        int fileSize = inFile.tellg();
        inFile.close();

        cout << "\n[3] File Information:" << endl;
        cout << "    File name: employees.bin" << endl;
        cout << "    File size: " << fileSize << " bytes" << endl;
        cout << "    Records: " << recordCount << " records" << endl;
        cout << "    Bytes per record: " << (fileSize / recordCount) << " bytes" << endl;
    }

    // ============================================
    // PART 4: EXTRA - SHOW GENERATED DATA SUMMARY
    // ============================================

    cout << "\n========================================" << endl;
    cout << "          PROGRAM COMPLETED" << endl;
    cout << "========================================" << endl;

    return 0;
}