#ifndef STORE_H
#define STORE_H

#include <vector>
#include <string>
#include <fstream>
#include "Product.h"
#include "Customer.h"
#include "PremiumCustomer.h"

struct Invoice {
    int invoiceID;
    int customerID;
    std::string customerName;
    std::vector<CartItem> items;
    double totalAmount;
    double discountAmount;
    std::string date;
    
    Invoice(int id, int custId, const std::string& custName, 
            const std::vector<CartItem>& cartItems, double total, double discount, const std::string& invoiceDate)
        : invoiceID(id), customerID(custId), customerName(custName), 
          items(cartItems), totalAmount(total), discountAmount(discount), date(invoiceDate) {}
};

class Store {
private:
    std::vector<Product*> products;
    std::vector<Customer*> customers;
    std::vector<Invoice> invoices;
    int nextProductID;
    int nextCustomerID;
    int nextInvoiceID;
    
    // Helper methods
    Product* findProductByID(int productID);
    Customer* findCustomerByID(int customerID);
    std::string getCurrentDate();

public:
    // Constructor and destructor
    Store();
    ~Store();
    
    // Product management
    void addProduct(const std::string& name, double price, int quantity);
    void displayAllProducts() const;
    bool updateProductQuantity(int productID, int newQuantity);
    
    // Customer management
    void registerCustomer(const std::string& name, const std::string& address, bool isPremium = false);
    void displayAllCustomers() const;
    Customer* getCustomer(int customerID);
    
    // Purchase operations
    bool purchaseProduct(int customerID, int productID, int quantity);
    bool returnProduct(int customerID, int productID, int quantity);
    void generateInvoice(int customerID);
    void displayInvoice(int invoiceID) const;
    void displayAllInvoices() const;
    
    // File handling operations
    void saveProductsToFile(const std::string& filename) const;
    void loadProductsFromFile(const std::string& filename);
    void saveCustomersToFile(const std::string& filename) const;
    void loadCustomersFromFile(const std::string& filename);
    void saveInvoicesToFile(const std::string& filename) const;
    void loadInvoicesFromFile(const std::string& filename);
    
    // Utility methods
    void saveAllData() const;
    void loadAllData();
    void clearAllData();
    
    // Statistics
    double getTotalRevenue() const;
    Product* getMostSoldProduct() const;
    void displayStatistics() const;
};

#endif // STORE_H