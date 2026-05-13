#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>

using namespace std;

struct BakeryProduct
{
    string itemName;
    double itemPrice;
};

struct Customer
{
    string username;
    string password;
};

void displayBakeryProducts(const vector<BakeryProduct> &products);
double calculateTotalCost(const vector<BakeryProduct> &products, const vector<int> &selectedItems);
void printReceipt(const vector<BakeryProduct> &products, const vector<int> &selectedItems, double totalCost);
void signOut(bool &isLoggedIn);
void storeReceipt(const vector<BakeryProduct> &products, const vector<int> &selectedItems, double totalCost);
void waitForEnterKey();
bool isValidProductSelection(int choice, const vector<BakeryProduct> &products);
bool registerCustomer(vector<Customer> &customers);
bool loginCustomer(vector<Customer> &customers, string &loggedInUser);

int main()
{
    bool isLoggedIn = false;
    vector<Customer> customers;

    while (true)
    {
        string loggedInUser;

        ifstream customerFile("customers.txt");
        if (customerFile.is_open())
        {
            Customer customer;
            while (customerFile >> customer.username >> customer.password)
            {
                customers.push_back(customer);
            }
            customerFile.close();
        }

        string choice;
        cout << "Bakery Management System\n";
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        if (choice == "1")
        {
            if (registerCustomer(customers))
            {
                cout << "Registration successful. You can now log in.\n";
                waitForEnterKey();
            }
            else
            {
                cout << "Registration failed. Please try again.\n";
                waitForEnterKey();
            }
        }
        else if (choice == "2")
        {
            if (loginCustomer(customers, loggedInUser))
            {
                isLoggedIn = true;
            }
            else
            {
                cout << "Login failed. Please try again.\n";
                waitForEnterKey();
            }
        }
        else if (choice == "3")
        {
            ofstream customerFile("customers.txt");
            if (customerFile.is_open())
            {
                for (const Customer &customer : customers)
                {
                    customerFile << customer.username << " " << customer.password << endl;
                }
                customerFile.close();
            }
            cout << "Exiting Bakery Management System. Have a good day!\n";
            return 0;
        }
        else
        {
            cout << "Invalid option. Please try again.\n";
        }

        while (isLoggedIn)
        {
            vector<BakeryProduct> products = {
                {"Bread", 5.00},
                {"Cinnamon Roll", 3.00},
                {"Croissant", 9.00},
                {"Donut", 8.00},
                {"Cake", 11.00},
                {"Cupcake", 3.00},
                {"Chocolate Chip Cookies", 20.00},
                {"Red Velvet Cake", 16.00},
                
            };

            vector<int> selectedItems;
            int choice;

            while (true)
            {
                system("cls");

                cout << "\nBakery Menu:\n";
                displayBakeryProducts(products);

                cout << "Select a product (1-" << products.size() << "), 'C' to calculate the bill\n  'H' for help\n 'G' to log out\n  'X' to exit:\n ";
                char option;
                cin >> option;

                if (option == 'C' || option == 'c')
                {
                    double totalCost = calculateTotalCost(products, selectedItems);
                    printReceipt(products, selectedItems, totalCost);
                    storeReceipt(products, selectedItems, totalCost);
                    selectedItems.clear();
                    cout << "Press 5 to continue...";
                    cin.ignore();
                    cin.get();
                }
                else if (option == 'H' || option == 'h')
                {
                   {
    system("cls");

    cout << "\nHelp:\n";
    // ... (help instructions)
    cout << "\nHelp:\n";
                    cout << "1. Enter the product number to select it.\n";
                    cout << "2. Enter 'C' to calculate and print the bill.\n";
                    cout << "3. Enter 'G' to log out and return to the login screen.\n";
                    cout << "4. Enter 'X' to exit the program.\n";
                    cout << "Press any key to return to the main menu...";
                    cout << "5. To add more products to your order, simply enter the product numbers one by one.\n";
                    cout << "6. To remove a product from your order, enter its number again.\n";
                    cout << "7. Your selected products will be displayed on the receipt.\n";
                    cout << "8. The 'Total Cost' represents the sum of the prices of all selected products.\n";
                    cout << "9. Once your order is complete, press 'C' to view and save your receipt.\n";
                    cout << "10. You can always return to the main menu by pressing any key after reading the instructions.\n";
                    cout << "Press any key to return to the main menu...";

    cout << "Press any key to return to the main menu...";
    cin.ignore(); // Add this line
    cin.get();
}
                }
                else if (option == 'G' || option == 'g')
                {
                    signOut(isLoggedIn);
                    break;
                }
                else if (option == 'X' || option == 'x')
                {
                    cout << "Exiting Bakery Management System. Have a good day!\n";
                    return 0;
                }
                else if (isdigit(option))
                {
                    choice = option - '0';
                    if (isValidProductSelection(choice, products))
                    {
                        selectedItems.push_back(choice);
                        cout << "The product has been added to the order.\n";
                        cout << "Please press enter to add another product if you want to buy more.\n";
                        cin.ignore();
                        cin.get();
                    }
                    else
                    {
                        cout << "Invalid product number. Please try again.\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                    }
                }
                else
                {
                    cout << "Invalid input. Please try again.\n";
                    waitForEnterKey();
                }
            }
        }
    }

    return 0;
}

void displayBakeryProducts(const vector<BakeryProduct> &products)
{
    for (int i = 0; i < products.size(); ++i)
    {
        cout << i + 1 << ". " << products[i].itemName << " - $" << products[i].itemPrice << endl;
    }
}

double calculateTotalCost(const vector<BakeryProduct> &products, const vector<int> &selectedItems)
{
    double totalCost = 0.0;
    for (int item : selectedItems)
    {
        totalCost += products[item - 1].itemPrice;
    }
    return totalCost;
}

void printReceipt(const vector<BakeryProduct> &products, const vector<int> &selectedItems, double totalCost)
{
    system("cls");

    cout << "\n Bakery Receipt \n";
    cout << "Selected Products:\n";
    for (int item : selectedItems)
    {
        cout << products[item - 1].itemName << " - $" << products[item - 1].itemPrice << endl;
    }
    cout << "-------------------------\n";
    cout << "Total Cost: $" << totalCost << endl;

    cout << "\nPress Enter to continue...";
    char key;
    cin.ignore();
    cin.get(key);
}

void waitForEnterKey()
{
    cout << "Press Enter to continue...";
    char key;
    cin.ignore();
    cin.get(key);
}

void signOut(bool &isLoggedIn)
{
    isLoggedIn = false;
    system("cls");
}

void storeReceipt(const vector<BakeryProduct> &products, const vector<int> &selectedItems, double totalCost)
{
    ofstream receiptFile("receipt.txt");
    if (receiptFile.is_open())
    {
        receiptFile << "\nBakery Receipt \n";
        receiptFile << "Selected Products:\n";
        for (int item : selectedItems)
        {
            receiptFile << products[item - 1].itemName << " - $" << products[item - 1].itemPrice << endl;
        }
        receiptFile << "-------------------------\n";
        receiptFile << "Total Cost: $" << totalCost << endl;
        receiptFile.close();
        cout << "Receipt has been saved to 'receipt.txt'.\n";
    }
    else
    {
        cout << "Error: Unable to save the receipt to a file.\n";
    }
}

bool isValidProductSelection(int choice, const vector<BakeryProduct> &products)
{
    return (choice >= 1 && choice <= products.size());
}

bool registerCustomer(vector<Customer> &customers)
{
    Customer newCustomer;
    cout << "Enter a username: ";
    cin >> newCustomer.username;
    cout << "Enter a password: ";
    cin >> newCustomer.password;

    for (const Customer &customer : customers)
    {
        if (customer.username == newCustomer.username)
        {
            cout << "Username already exists. Registration failed.\n";
            return false;
        }
    }

    customers.push_back(newCustomer);
    return true;
}

bool loginCustomer(vector<Customer> &customers, string &loggedInUser)
{
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (const Customer &customer : customers)
    {
        if (customer.username == username && customer.password == password)
        {
            loggedInUser = username;
            cout << "Login successful. Welcome, " << loggedInUser << "!\n";
            return true;
        }
    }

    cout << "Login failed. Invalid username or password.\n";
    return false;
}
