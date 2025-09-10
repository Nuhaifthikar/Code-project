#include <iostream>
#include <fstream>
#include <iomanip>
#include<map>
#include <string>

using namespace std;

// Constants
const int MAX_PRODUCTS = 10;
const double POINTS_PER_LKR =0.1;
const string CUSTOMER_FILE = "customers.txt";

// Data structures
struct Product {
    string name;
    double price;
};

struct Customer {
    string name;
    int id;
    double points;
};

// Global variables
Product products[MAX_PRODUCTS];
map<int, Customer> customers;

// Function prototypes
void loadProducts();
void loadCustomers();
void saveCustomers();
void displayMenu();
void handlePurchase();
void handleRewardRedemption();
void viewCustomerPoints();
void addCustomer();
void listProducts();
bool isValidProductIndex(int index);
bool isValidCustomerId(int id);

// Main function
int main() {
    loadProducts();
    loadCustomers();

    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
        case 1: handlePurchase(); break;
        case 2: handleRewardRedemption(); break;
        case 3: viewCustomerPoints(); break;
        case 4: addCustomer(); break;
        case 5: listProducts(); break;
        case 0: saveCustomers(); cout << "Exiting. All data saved.\n"; break;
        default: cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

// Load products
void loadProducts() {
    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        products[i].name = "Product" + to_string(i + 1);
        products[i].price = 10.0 * (i + 1); // Example prices
    }
}

// Load customers from file
void loadCustomers() {
    ifstream infile(CUSTOMER_FILE);
    if (infile.is_open()) 
    {
        Customer cus;
        while (infile >> cus.id >> ws && getline(infile, cus.name) >> cus.points) 
        {
            customers[cus.id] = cus;
        }
        infile.close();
    }
}

// Save customers to file
void saveCustomers() {
    ofstream outfile(CUSTOMER_FILE);
    for (const auto& kv : customers) 
    {
        const Customer& c = kv.second;
        outfile << c.id << endl << c.name << endl << c.points << endl;
    }
    outfile.close();
}

// Display menu
void displayMenu() 
{
    cout << "~~ELEGANCE BOUTIQUE~~";
    cout << "\n    fashion store   \n";
    cout << "        Menu";
    cout << "\n------------------------\n";
    cout << "1. Make a purchase\n";
    cout << "2. Redeem points\n";
    cout << "3. View customer points\n";
    cout << "4. Add new customer\n";
    cout << "5. List products\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

// Handle purchase
void handlePurchase() {
    int customerId, productIndex;
    double amount;

    cout << "Enter customer ID: ";
    cin >> customerId;
    cout << "Enter product index (1 to " << MAX_PRODUCTS << "): ";
    cin >> productIndex;

    if (!isValidProductIndex(productIndex)) {
        cout << "Invalid product index!\n";
        return;
    }

    cout << "Enter purchase amount: ";
    cin >> amount;

    double pointsEarned = amount * POINTS_PER_LKR;

    if (isValidCustomerId(customerId)) {
        customers[customerId].points += pointsEarned;
        cout << "Customer purchase completed. Points earned: " << pointsEarned << endl;
    }
    else {
        cout << "Customer not found!\n";
    }
    cout << "-----------------------------" << endl;
}

// Handle reward redemption
void handleRewardRedemption() {
    int customerId;
    double discount;

    cout << "Enter customer ID: ";
    cin >> customerId;

    if (isValidCustomerId(customerId)) {
        cout << "Enter discount amount to redeem: ";
        cin >> discount;

        if (customers[customerId].points >= discount) 
        {
            customers[customerId].points -= discount;
            cout << "Discount applied. Remaining points: " << customers[customerId].points << endl;
        }
        else {
            cout << "Insufficient points!\n";
        }
    }
    else {
        cout << "Customer not found!\n";
    }
    cout << "-----------------------------" << endl;
}

// View customer points
void viewCustomerPoints() {
    int customerId;

    cout << "Enter customer ID: ";
    cin >> customerId;

    if (isValidCustomerId(customerId)) {
        cout << "Customer Name : " << customers[customerId].name << endl;
        cout << "Earned Points : " << customers[customerId].points << endl;
    }
    else {
        cout << "Customer not found!\n";
    }
    cout << "-----------------------------" << endl;
}

// Add new customer
void addCustomer() {
    Customer cus;
    cout << "Enter customer ID: ";
    cin >> cus.id;

    if (isValidCustomerId(cus.id)) 
    {
        cout << "Customer ID already exists!\n";
        return;
    }

    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, cus.name);
    cus.points = 0;

    customers[cus.id] = cus;
    cout << "Customer added successfully!\n";
    cout << "-----------------------------" << endl;
}

// List products
void listProducts() 
{
    for (int i = 0; i < MAX_PRODUCTS; ++i) 
    {
        cout << i + 1 << ". " << products[i].name << " Lkr" << products[i].price << endl;
    }
}

// Validate product index
bool isValidProductIndex(int index) 
{
    return (index >= 1 && index <= MAX_PRODUCTS);
}

// Validate customer ID
bool isValidCustomerId(int id) 
{
    return (customers.find(id) != customers.end());
}

