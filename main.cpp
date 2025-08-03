#include <iostream>
#include <string>
#include <limits>
#include "Store.h"

class ECommerceApp {
private:
    Store store;
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void pauseExecution() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    
    void displayMainMenu() {
        std::cout << "\n╔═══════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║           🛒 E-COMMERCE STORE MANAGEMENT SYSTEM              ║" << std::endl;
        std::cout << "╠═══════════════════════════════════════════════════════════════╣" << std::endl;
        std::cout << "║  1. 📦 Add a Product                                         ║" << std::endl;
        std::cout << "║  2. 🏪 Display All Products                                  ║" << std::endl;
        std::cout << "║  3. 👤 Register a New Customer                               ║" << std::endl;
        std::cout << "║  4. 👥 Display All Customers                                 ║" << std::endl;
        std::cout << "║  5. 🛍️  Purchase a Product                                   ║" << std::endl;
        std::cout << "║  6. 🔄 Return a Product                                      ║" << std::endl;
        std::cout << "║  7. 🛒 View Customer Cart                                    ║" << std::endl;
        std::cout << "║  8. 🧾 Generate Invoice                                      ║" << std::endl;
        std::cout << "║  9. 📋 Display Invoice                                       ║" << std::endl;
        std::cout << "║ 10. 📊 Display All Invoices                                 ║" << std::endl;
        std::cout << "║ 11. 📈 Store Statistics                                     ║" << std::endl;
        std::cout << "║ 12. 💾 Save Data and Exit                                   ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "Enter your choice (1-12): ";
    }
    
    void addProductMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 📦 ADD NEW PRODUCT                                         │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        std::string name;
        double price;
        int quantity;
        
        std::cout << "Enter product name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        
        std::cout << "Enter product price: $";
        std::cin >> price;
        
        std::cout << "Enter available quantity: ";
        std::cin >> quantity;
        
        store.addProduct(name, price, quantity);
    }
    
    void registerCustomerMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 👤 REGISTER NEW CUSTOMER                                   │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        std::string name, address;
        int customerType;
        
        std::cout << "Enter customer name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        
        std::cout << "Enter customer address: ";
        std::getline(std::cin, address);
        
        std::cout << "Customer type:\n1. Regular Customer\n2. Premium Customer\nEnter choice (1-2): ";
        std::cin >> customerType;
        
        bool isPremium = (customerType == 2);
        store.registerCustomer(name, address, isPremium);
    }
    
    void purchaseProductMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 🛍️ PURCHASE PRODUCT                                        │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        int customerID, productID, quantity;
        
        std::cout << "Enter customer ID: ";
        std::cin >> customerID;
        
        std::cout << "Enter product ID: ";
        std::cin >> productID;
        
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        
        store.purchaseProduct(customerID, productID, quantity);
    }
    
    void returnProductMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 🔄 RETURN PRODUCT                                          │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        int customerID, productID, quantity;
        
        std::cout << "Enter customer ID: ";
        std::cin >> customerID;
        
        std::cout << "Enter product ID: ";
        std::cin >> productID;
        
        std::cout << "Enter quantity to return: ";
        std::cin >> quantity;
        
        store.returnProduct(customerID, productID, quantity);
    }
    
    void viewCustomerCartMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 🛒 VIEW CUSTOMER CART                                      │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        int customerID;
        std::cout << "Enter customer ID: ";
        std::cin >> customerID;
        
        Customer* customer = store.getCustomer(customerID);
        if (customer) {
            customer->displayCustomerInfo();
            customer->displayCart();
        } else {
            std::cout << "❌ Customer not found!" << std::endl;
        }
    }
    
    void generateInvoiceMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 🧾 GENERATE INVOICE                                        │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        int customerID;
        std::cout << "Enter customer ID: ";
        std::cin >> customerID;
        
        store.generateInvoice(customerID);
    }
    
    void displayInvoiceMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ 📋 DISPLAY INVOICE                                         │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        int invoiceID;
        std::cout << "Enter invoice ID: ";
        std::cin >> invoiceID;
        
        store.displayInvoice(invoiceID);
    }
    
public:
    void run() {
        int choice;
        bool running = true;
        
        std::cout << "╔═══════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║        🎉 WELCOME TO E-COMMERCE STORE MANAGEMENT! 🎉        ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════════════════════╝" << std::endl;
        pauseExecution();
        
        while (running) {
            clearScreen();
            displayMainMenu();
            
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    addProductMenu();
                    break;
                    
                case 2:
                    store.displayAllProducts();
                    break;
                    
                case 3:
                    registerCustomerMenu();
                    break;
                    
                case 4:
                    store.displayAllCustomers();
                    break;
                    
                case 5:
                    purchaseProductMenu();
                    break;
                    
                case 6:
                    returnProductMenu();
                    break;
                    
                case 7:
                    viewCustomerCartMenu();
                    break;
                    
                case 8:
                    generateInvoiceMenu();
                    break;
                    
                case 9:
                    displayInvoiceMenu();
                    break;
                    
                case 10:
                    store.displayAllInvoices();
                    break;
                    
                case 11:
                    store.displayStatistics();
                    break;
                    
                case 12:
                    std::cout << "\n💾 Saving data and exiting..." << std::endl;
                    store.saveAllData();
                    std::cout << "👋 Thank you for using E-Commerce Store Management System!" << std::endl;
                    running = false;
                    break;
                    
                default:
                    std::cout << "❌ Invalid choice! Please enter a number between 1 and 12." << std::endl;
                    break;
            }
            
            if (running) {
                pauseExecution();
            }
        }
    }
};

// Demo function to add sample data
void addSampleData(Store& store) {
    std::cout << "\n🎯 Adding sample data for demonstration..." << std::endl;
    
    // Add sample products
    store.addProduct("Gaming_Laptop", 1299.99, 10);
    store.addProduct("Wireless_Mouse", 29.99, 50);
    store.addProduct("Mechanical_Keyboard", 89.99, 25);
    store.addProduct("4K_Monitor", 349.99, 15);
    store.addProduct("Webcam_HD", 79.99, 30);
    
    // Register sample customers
    store.registerCustomer("John_Doe", "123_Main_St", false);
    store.registerCustomer("Jane_Smith", "456_Oak_Ave", true);
    store.registerCustomer("Bob_Johnson", "789_Pine_Rd", true);
    
    std::cout << "✅ Sample data added successfully!" << std::endl;
}

int main() {
    try {
        Store demoStore;
        
        std::cout << "🎯 Would you like to add sample data for testing? (y/n): ";
        char choice;
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            addSampleData(demoStore);
            std::cout << "\nPress Enter to continue to the main application...";
            std::cin.ignore();
            std::cin.get();
        }
        
        ECommerceApp app;
        app.run();
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}