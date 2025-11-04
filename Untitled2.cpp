#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cstdlib>

using namespace std;

struct User {
    string name;
    string username;
    string password;
    string role;
};

struct MeterReading {
    string customerID;
    string date;
    double previousReading;
    double currentReading;
    double consumption;
    double amountDue;
};

struct Customer {
    string customerID;
    string name;
    string address;
};

// Global variables
vector<User> users;
vector<MeterReading> meterReadings;
vector<Customer> customers;
User currentUser;
const double RATE_PER_UNIT = 15.50;

// Function prototypes
void initializeData();
void displayStartup();
void clearScreen();
bool login();
void displayMainMenu();
void meterReadingEntry();
void viewBillingSummary();
void logout();
double calculateConsumption(double previous, double current);
double calculateAmountDue(double consumption);
string getCurrentDateTime();
void addInnovativeFeature();
void pressAnyKeyToContinue();

int main() {
    initializeData();
    displayStartup();
    
    if (login()) {
        cout << "\nLogin successful! Welcome, " << currentUser.name << " (" << currentUser.role << ")" << endl;
        pressAnyKeyToContinue();
        
        bool continueProgram = true;
        while (continueProgram) {
            clearScreen();
            displayMainMenu();
            
            int choice;
            cout << "\nEnter your choice (1-4): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (choice) {
                case 1:
                    meterReadingEntry();
                    break;
                case 2:
                    viewBillingSummary();
                    break;
                case 3:
                    logout();
                    continueProgram = false;
                    break;
                case 4:
                    addInnovativeFeature();
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
                    pressAnyKeyToContinue();
            }
        }
    }
    
    cout << "\nThank you for using Ceylon Power Company System!" << endl;
    return 0;
}

void initializeData() {
    // Initialize users using push_back (C++98 compatible)
    users.clear();
    
    User u1;
    u1.name = "Administrator";
    u1.username = "Admin";
    u1.password = "Admin123";
    u1.role = "Administrator";
    users.push_back(u1); //U1 stores in user array
    
    User u2;
    u2.name = "Frank Abagnale";
    u2.username = "FrankA"; //attributes of objects
    u2.password = "CPC@#123";
    u2.role = "Meter Reader";
    users.push_back(u2);
    
    User u3;
    u3.name = "Roger Strong";
    u3.username = "RogerS";
    u3.password = "RS#$678";
    u3.role = "Cashier";
    users.push_back(u3);
    
    User u4;
    u4.name = "Paul Morgan";
    u4.username = "Morgan";
    u4.password = "Paul268";
    u4.role = "Manager";
    users.push_back(u4);
    
    // Initialize customers
    customers.clear();
    
    Customer c1;
    c1.customerID = "CUST001";
    c1.name = "John Silva";
    c1.address = "123 Main Street, Colombo";
    customers.push_back(c1);
    
    Customer c2;
    c2.customerID = "CUST002";
    c2.name = "Maria Perera";
    c2.address = "456 Galle Road, Galle";
    customers.push_back(c2);
    
    Customer c3;
    c3.customerID = "CUST003";
    c3.name = "David Fernando";
    c3.address = "789 Kandy Street, Kandy";
    customers.push_back(c3);
    
    // Initialize meter readings
    meterReadings.clear();
    
    MeterReading r1;
    r1.customerID = "CUST001";
    r1.date = "2024-01-15";
    r1.previousReading = 1250.5;
    r1.currentReading = 1350.8;
    r1.consumption = 100.3;
    r1.amountDue = 1554.65;
    meterReadings.push_back(r1);
    
    MeterReading r2;
    r2.customerID = "CUST002";
    r2.date = "2024-01-16";
    r2.previousReading = 890.2;
    r2.currentReading = 1020.5;
    r2.consumption = 130.3;
    r2.amountDue = 2019.65;
    meterReadings.push_back(r2);
}


void displayStartup() {
    clearScreen();
    cout << "==================================================" << endl;
    cout << "            CEYLON POWER COMPANY " << endl;
    cout << "==================================================" << endl;
    cout << "            ***   CPC   ***" << endl;
    cout << "         Reliable Energy Solutions" << endl;
    cout << "==================================================" << endl;
    cout << "Branch: Colombo Main Branch Sagee Angel " << endl;
    cout << "Date: " << getCurrentDateTime();
    cout << "==================================================" << endl;
    cout << "\nInitializing System... Please wait..." << endl;
    pressAnyKeyToContinue();
}

void clearScreen() {
    system("cls");
}

string getCurrentDateTime() {
    time_t now = time(0);
    string dt = ctime(&now); 
    return dt;
}

bool login() {
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    while (attempts < MAX_ATTEMPTS) {
        clearScreen();
        cout << "==================================================" << endl;
        cout << "               SECURE LOGIN PORTAL" << endl;
        cout << "==================================================" << endl;
        
        string username, password;
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);
        
        // Replace range-based for loop with traditional for loop
        bool loginSuccess = false;
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].username == username && users[i].password == password) {
                currentUser = users[i];
                loginSuccess = true;
                break;
            }
        }
        
        if (loginSuccess) {
            return true;
        }
        
        attempts++;
        cout << "\nIncorrect username/password. Please try again." << endl;
        cout << "Attempts remaining: " << (MAX_ATTEMPTS - attempts) << endl;
        
        if (attempts < MAX_ATTEMPTS) {
            pressAnyKeyToContinue();
        }
    }
    
    cout << "\nMaximum login attempts exceeded. System exiting..." << endl;
    return false;
}

void displayMainMenu() {
    cout << "==================================================" << endl;
    cout << "                 MAIN MENU" << endl;
    cout << "==================================================" << endl;
    cout << "Logged in as: " << currentUser.name << " (" << currentUser.role << ")" << endl;
    cout << "==================================================" << endl;
    cout << "1. Meter Reading Entry" << endl;
    cout << "2. View Billing Summary" << endl;
    cout << "3. Log Out" << endl;
    cout << "4. Energy Savings Tips (Innovative Feature)" << endl;
    cout << "==================================================" << endl;
}

void meterReadingEntry() {
    clearScreen();
    cout << "==================================================" << endl;
    cout << "             METER READING ENTRY" << endl;
    cout << "==================================================" << endl;
    
    MeterReading newReading;
    
    cout << "Enter Customer ID / Meter Number: ";
    getline(cin, newReading.customerID);
    
    cout << "Enter Date of Reading (YYYY-MM-DD): ";
    getline(cin, newReading.date);
     
    cout << "Enter Previous Meter Reading: ";
    cin >> newReading.previousReading;
    
    cout << "Enter Current Meter Reading: ";
    cin >> newReading.currentReading;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (newReading.currentReading < newReading.previousReading) {
        cout << "Error: Current reading cannot be less than previous reading!" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    newReading.consumption = calculateConsumption(newReading.previousReading, newReading.currentReading);
    newReading.amountDue = calculateAmountDue(newReading.consumption);
    
    meterReadings.push_back(newReading);
    
    cout << "\n--- Reading Successfully Recorded ---" << endl;
    cout << "Customer ID: " << newReading.customerID << endl;
    cout << "Consumption: " << fixed << setprecision(2) << newReading.consumption << " units" << endl;
    cout << "Amount Due: Rs. " << fixed << setprecision(2) << newReading.amountDue << endl;
    
    char choice;
    cout << "\nReturn to main menu? (Y/N): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (tolower(choice) == 'n') {
        logout();
        exit(0);
    }
}

void viewBillingSummary() {
    clearScreen();
    cout << "==================================================" << endl;
    cout << "             BILLING SUMMARY REPORT" << endl;
    cout << "==================================================" << endl;
    
    if (meterReadings.empty()) {
        cout << "No billing records found!" << endl;
    } else {
        cout << setw(12) << left << "Customer ID" 
             << setw(12) << "Date" 
             << setw(12) << "Consumption" 
             << setw(15) << "Amount Due" 
             << endl;
        cout << "--------------------------------------------------" << endl;
        
        double totalConsumption = 0;
        double totalAmount = 0;
        
        // Replace range-based for loop with traditional for loop
        for (size_t i = 0; i < meterReadings.size(); i++) {
            const MeterReading& reading = meterReadings[i];
            cout << setw(12) << left << reading.customerID
                 << setw(12) << reading.date
                 << setw(12) << fixed << setprecision(2) << reading.consumption
                 << "Rs. " << setw(10) << reading.amountDue
                 << endl;
            
            totalConsumption += reading.consumption;
            totalAmount += reading.amountDue;
        }
        
        cout << "--------------------------------------------------" << endl;
        cout << setw(24) << left << "TOTAL:" 
             << setw(12) << fixed << setprecision(2) << totalConsumption
             << "Rs. " << setw(10) << totalAmount
             << endl;
    }
    
    char choice;
    cout << "\nReturn to main menu? (Y/N): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (tolower(choice) == 'n') {
        logout();
        exit(0);
    }
}

double calculateConsumption(double previous, double current) {
    return current - previous;
}

double calculateAmountDue(double consumption) {
    return consumption * RATE_PER_UNIT;
}

void logout() {
    clearScreen();
    cout << "==================================================" << endl;
    cout << "                 LOGOUT SUCCESSFUL" << endl;
    cout << "==================================================" << endl;
    cout << "User: " << currentUser.name << " has been logged out." << endl;
    cout << "Session ended: " << getCurrentDateTime();
    pressAnyKeyToContinue();
}

void addInnovativeFeature() {
    clearScreen();
    cout << "==================================================" << endl;
    cout << "           ENERGY SAVINGS TIPS" << endl;
    cout << "==================================================" << endl;
    cout << "Smart ways to reduce your electricity consumption:\n" << endl;
    
    cout << "1. USE LED BULBS" << endl;
    cout << "   - Save up to 80% on lighting costs" << endl;
    cout << "   - Last 25 times longer than incandescent bulbs\n" << endl;
    
    cout << "2. UNPLUG ELECTRONICS" << endl;
    cout << "   - Phantom loads cost money" << endl;
    cout << "   - Use power strips for easy switching\n" << endl;
    
    cout << "3. OPTIMIZE AC USAGE" << endl;
    cout << "   - Set thermostat to 24°C" << endl;
    cout << "   - Regular maintenance improves efficiency\n" << endl;
    
    cout << "4. ENERGY EFFICIENT APPLIANCES" << endl;
    cout << "   - Look for 5-star energy rating" << endl;
    cout << "   - Can reduce consumption by 30-50%\n" << endl;
    
    cout << "5. WATER HEATING" << endl;
    cout << "   - Set water heater to 60°C" << endl;
    cout << "   - Insulate hot water pipes\n" << endl;
    
    cout << "Estimated Monthly Savings: Rs. 1500 - Rs. 4000" << endl;
    cout << "Carbon Footprint Reduction: 15-30%" << endl;
    
    // Calculate potential savings based on current consumption
    if (!meterReadings.empty()) {
        double avgConsumption = 0;
        for (size_t i = 0; i < meterReadings.size(); i++) {
            avgConsumption += meterReadings[i].consumption;
        }
        avgConsumption /= meterReadings.size();
        
        double potentialSavings = avgConsumption * 0.2 * RATE_PER_UNIT; // 20% savings
        cout << "\nBased on average consumption, you could save: Rs. " 
             << fixed << setprecision(2) << potentialSavings << " per month!" << endl;
    }
    
    pressAnyKeyToContinue();
}

void pressAnyKeyToContinue() {
    cout << "\nPress Enter to continue...";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
