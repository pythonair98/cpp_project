#include "Store.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <ctime>

// Constructor
Store::Store() : nextProductID(1), nextCustomerID(1), nextInvoiceID(1) {
    loadAllData();
}

// Destructor
Store::~Store() {
    saveAllData();
    clearAllData();
}

// Helper methods
Product* Store::findProductByID(int productID) {
    for (auto& product : products) {
        if (product->getProductID() == productID) {
            return product;
        }
    }
    return nullptr;
}

Customer* Store::findCustomerByID(int customerID) {
    for (auto& customer : customers) {
        if (customer->getCustomerID() == customerID) {
            return customer;
        }
    }
    return nullptr;
}

std::string Store::getCurrentDate() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string dateStr(dt);
    dateStr.pop_back(); // Remove newline character
    return dateStr;
}

// Product management
void Store::addProduct(const std::string& name, double price, int quantity) {
    if (name.empty() || price < 0 || quantity < 0) {
        std::cout << "❌ Invalid product information!" << std::endl;
        return;
    }
    
    Product* newProduct = new Product(nextProductID++, name, price, quantity);
    products.push_back(newProduct);
    
    std::cout << "✅ Product added successfully!" << std::endl;
    newProduct->displayProduct();
}

void Store::displayAllProducts() const {
    if (products.empty()) {
        std::cout << "\n📦 No products available in the store!" << std::endl;
        return;
    }
    
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 🏪 ALL PRODUCTS IN STORE                                   │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
    
    for (const auto& product : products) {
        product->displayProduct();
        std::cout << std::endl;
    }
}

bool Store::updateProductQuantity(int productID, int newQuantity) {
    Product* product = findProductByID(productID);
    if (product && newQuantity >= 0) {
        product->setAvailableQuantity(newQuantity);
        std::cout << "✅ Product quantity updated successfully!" << std::endl;
        return true;
    }
    std::cout << "❌ Product not found or invalid quantity!" << std::endl;
    return false;
}

// Customer management
void Store::registerCustomer(const std::string& name, const std::string& address, bool isPremium) {
    if (name.empty() || address.empty()) {
        std::cout << "❌ Invalid customer information!" << std::endl;
        return;
    }
    
    Customer* newCustomer;
    if (isPremium) {
        newCustomer = new PremiumCustomer(nextCustomerID++, name, address);
        std::cout << "✅ Premium customer registered successfully!" << std::endl;
    } else {
        newCustomer = new Customer(nextCustomerID++, name, address);
        std::cout << "✅ Regular customer registered successfully!" << std::endl;
    }
    
    customers.push_back(newCustomer);
    newCustomer->displayCustomerInfo();
}

void Store::displayAllCustomers() const {
    if (customers.empty()) {
        std::cout << "\n👥 No customers registered!" << std::endl;
        return;
    }
    
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 👥 ALL REGISTERED CUSTOMERS                                │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
    
    for (const auto& customer : customers) {
        customer->displayCustomerInfo();
        std::cout << std::endl;
    }
}

Customer* Store::getCustomer(int customerID) {
    return findCustomerByID(customerID);
}

// Purchase operations
bool Store::purchaseProduct(int customerID, int productID, int quantity) {
    Customer* customer = findCustomerByID(customerID);
    Product* product = findProductByID(productID);
    
    if (!customer) {
        std::cout << "❌ Customer not found!" << std::endl;
        return false;
    }
    
    if (!product) {
        std::cout << "❌ Product not found!" << std::endl;
        return false;
    }
    
    if (!product->isAvailable(quantity)) {
        std::cout << "❌ Insufficient stock! Available: " << product->getAvailableQuantity() 
                  << ", Requested: " << quantity << std::endl;
        return false;
    }
    
    // Add to customer's cart
    customer->addToCart(product, quantity);
    // Update product quantity
    product->updateQuantity(quantity);
    
    std::cout << "✅ Product added to cart successfully!" << std::endl;
    std::cout << "Product: " << product->getName() << " (Qty: " << quantity << ")" << std::endl;
    std::cout << "Customer: " << customer->getName() << std::endl;
    
    return true;
}

bool Store::returnProduct(int customerID, int productID, int quantity) {
    Customer* customer = findCustomerByID(customerID);
    Product* product = findProductByID(productID);
    
    if (!customer || !product) {
        std::cout << "❌ Customer or product not found!" << std::endl;
        return false;
    }
    
    if (customer->returnProduct(productID, quantity)) {
        product->restockProduct(quantity);
        std::cout << "✅ Product returned successfully!" << std::endl;
        std::cout << "Product: " << product->getName() << " (Qty: " << quantity << ")" << std::endl;
        return true;
    }
    
    std::cout << "❌ Cannot return product. Check your cart!" << std::endl;
    return false;
}

void Store::generateInvoice(int customerID) {
    Customer* customer = findCustomerByID(customerID);
    if (!customer) {
        std::cout << "❌ Customer not found!" << std::endl;
        return;
    }
    
    if (customer->isCartEmpty()) {
        std::cout << "❌ Shopping cart is empty!" << std::endl;
        return;
    }
    
    // Calculate totals using polymorphism
    double subtotal = 0.0;
    for (const auto& item : customer->getShoppingCart()) {
        subtotal += item.product->getPrice() * item.quantity;
    }
    
    double discountAmount = subtotal * customer->getDiscountRate();
    double total = subtotal - discountAmount;
    
    // Create invoice
    Invoice newInvoice(nextInvoiceID++, customerID, customer->getName(),
                      customer->getShoppingCart(), total, discountAmount, getCurrentDate());
    invoices.push_back(newInvoice);
    
    // Display invoice
    displayInvoice(newInvoice.invoiceID);
    
    // Clear customer's cart
    customer->clearCart();
    
    std::cout << "\n💰 Invoice generated successfully! Invoice ID: " << newInvoice.invoiceID << std::endl;
}

void Store::displayInvoice(int invoiceID) const {
    auto it = std::find_if(invoices.begin(), invoices.end(),
        [invoiceID](const Invoice& inv) { return inv.invoiceID == invoiceID; });
    
    if (it == invoices.end()) {
        std::cout << "❌ Invoice not found!" << std::endl;
        return;
    }
    
    const Invoice& invoice = *it;
    
    std::cout << "\n╔═════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                         🧾 INVOICE                          ║" << std::endl;
    std::cout << "╠═════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Invoice ID: " << std::setw(10) << invoice.invoiceID 
              << " │ Date: " << std::setw(25) << std::left << invoice.date << std::right << " ║" << std::endl;
    std::cout << "║ Customer: " << std::setw(25) << std::left << invoice.customerName << std::right 
              << " │ ID: " << std::setw(10) << invoice.customerID << " ║" << std::endl;
    std::cout << "╠═════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ ITEMS PURCHASED:                                            ║" << std::endl;
    std::cout << "╠═════════════════════════════════════════════════════════════╣" << std::endl;
    
    double subtotal = 0.0;
    for (const auto& item : invoice.items) {
        double itemTotal = item.product->getPrice() * item.quantity;
        subtotal += itemTotal;
        
        std::cout << "║ " << std::setw(20) << std::left << item.product->getName()
                  << " │ Qty: " << std::setw(3) << item.quantity
                  << " │ $" << std::setw(8) << std::fixed << std::setprecision(2) << itemTotal << " ║" << std::endl;
    }
    
    std::cout << "╠═════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Subtotal: $" << std::setw(10) << std::fixed << std::setprecision(2) << subtotal 
              << "                                    ║" << std::endl;
    
    if (invoice.discountAmount > 0) {
        double discountRate = (invoice.discountAmount / subtotal) * 100;
        std::cout << "║ Discount (" << std::setw(4) << std::fixed << std::setprecision(1) << discountRate 
                  << "%): -$" << std::setw(8) << std::setprecision(2) << invoice.discountAmount 
                  << "                           ║" << std::endl;
    }
    
    std::cout << "║ TOTAL: $" << std::setw(10) << std::fixed << std::setprecision(2) << invoice.totalAmount 
              << "                                      ║" << std::endl;
    std::cout << "╚═════════════════════════════════════════════════════════════╝" << std::endl;
}

void Store::displayAllInvoices() const {
    if (invoices.empty()) {
        std::cout << "\n🧾 No invoices found!" << std::endl;
        return;
    }
    
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 🧾 ALL INVOICES                                            │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
    
    for (const auto& invoice : invoices) {
        std::cout << "Invoice ID: " << invoice.invoiceID 
                  << " | Customer: " << invoice.customerName 
                  << " | Total: $" << std::fixed << std::setprecision(2) << invoice.totalAmount 
                  << " | Date: " << invoice.date << std::endl;
    }
}

// File handling operations
void Store::saveProductsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Error opening file for writing: " << filename << std::endl;
        return;
    }
    
    file << products.size() << std::endl;
    for (const auto& product : products) {
        product->saveToFile(file);
    }
    
    file.close();
    std::cout << "✅ Products saved to " << filename << std::endl;
}

void Store::loadProductsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "⚠️  Products file not found: " << filename << ". Starting with empty inventory." << std::endl;
        return;
    }
    
    int count;
    file >> count;
    
    for (int i = 0; i < count; i++) {
        Product* product = new Product();
        product->loadFromFile(file);
        products.push_back(product);
        
        if (product->getProductID() >= nextProductID) {
            nextProductID = product->getProductID() + 1;
        }
    }
    
    file.close();
    std::cout << "✅ Loaded " << count << " products from " << filename << std::endl;
}

void Store::saveCustomersToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Error opening file for writing: " << filename << std::endl;
        return;
    }
    
    file << customers.size() << std::endl;
    for (const auto& customer : customers) {
        customer->saveToFile(file);
    }
    
    file.close();
    std::cout << "✅ Customers saved to " << filename << std::endl;
}

void Store::loadCustomersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "⚠️  Customers file not found: " << filename << ". Starting with no customers." << std::endl;
        return;
    }
    
    int count;
    file >> count;
    
    for (int i = 0; i < count; i++) {
        std::string customerType;
        file >> customerType;
        
        Customer* customer;
        if (customerType == "PREMIUM") {
            customer = new PremiumCustomer();
        } else {
            customer = new Customer();
        }
        
        customer->loadFromFile(file);
        customers.push_back(customer);
        
        if (customer->getCustomerID() >= nextCustomerID) {
            nextCustomerID = customer->getCustomerID() + 1;
        }
    }
    
    file.close();
    std::cout << "✅ Loaded " << count << " customers from " << filename << std::endl;
}

void Store::saveInvoicesToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Error opening file for writing: " << filename << std::endl;
        return;
    }
    
    file << invoices.size() << std::endl;
    for (const auto& invoice : invoices) {
        file << invoice.invoiceID << " " << invoice.customerID << " " 
             << invoice.customerName << " " << invoice.totalAmount << " " 
             << invoice.discountAmount << " " << invoice.date << " "
             << invoice.items.size() << std::endl;
        
        for (const auto& item : invoice.items) {
            file << item.product->getProductID() << " " << item.quantity << std::endl;
        }
    }
    
    file.close();
    std::cout << "✅ Invoices saved to " << filename << std::endl;
}

void Store::loadInvoicesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "⚠️  Invoices file not found: " << filename << ". Starting with no invoices." << std::endl;
        return;
    }
    
    int count;
    file >> count;
    
    for (int i = 0; i < count; i++) {
        int invoiceID, customerID, itemCount;
        std::string customerName, date;
        double totalAmount, discountAmount;
        
        file >> invoiceID >> customerID >> customerName >> totalAmount 
             >> discountAmount >> date >> itemCount;
        
        std::vector<CartItem> items;
        for (int j = 0; j < itemCount; j++) {
            int productID, quantity;
            file >> productID >> quantity;
            
            Product* product = findProductByID(productID);
            if (product) {
                items.emplace_back(product, quantity);
            }
        }
        
        invoices.emplace_back(invoiceID, customerID, customerName, items, 
                             totalAmount, discountAmount, date);
        
        if (invoiceID >= nextInvoiceID) {
            nextInvoiceID = invoiceID + 1;
        }
    }
    
    file.close();
    std::cout << "✅ Loaded " << count << " invoices from " << filename << std::endl;
}

// Utility methods
void Store::saveAllData() const {
    std::cout << "\n💾 Saving all data..." << std::endl;
    saveProductsToFile("products.txt");
    saveCustomersToFile("customers.txt");
    saveInvoicesToFile("invoices.txt");
    std::cout << "✅ All data saved successfully!" << std::endl;
}

void Store::loadAllData() {
    std::cout << "📂 Loading saved data..." << std::endl;
    loadProductsFromFile("products.txt");
    loadCustomersFromFile("customers.txt");
    loadInvoicesFromFile("invoices.txt");
    std::cout << "✅ Data loading complete!" << std::endl;
}

void Store::clearAllData() {
    for (auto& product : products) {
        delete product;
    }
    products.clear();
    
    for (auto& customer : customers) {
        delete customer;
    }
    customers.clear();
    
    invoices.clear();
}

// Statistics
double Store::getTotalRevenue() const {
    double total = 0.0;
    for (const auto& invoice : invoices) {
        total += invoice.totalAmount;
    }
    return total;
}

Product* Store::getMostSoldProduct() const {
    // This is a simplified implementation
    if (!products.empty()) {
        return products[0]; // Return first product as placeholder
    }
    return nullptr;
}

void Store::displayStatistics() const {
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 📊 STORE STATISTICS                                        │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ Total Products: " << std::setw(10) << products.size() << "                            │" << std::endl;
    std::cout << "│ Total Customers: " << std::setw(9) << customers.size() << "                            │" << std::endl;
    std::cout << "│ Total Invoices: " << std::setw(10) << invoices.size() << "                            │" << std::endl;
    std::cout << "│ Total Revenue: $" << std::setw(10) << std::fixed << std::setprecision(2) 
              << getTotalRevenue() << "                           │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
}