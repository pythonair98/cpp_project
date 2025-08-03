#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Default constructor
Customer::Customer() : customerID(0), name(""), address("") {}

// Parameterized constructor
Customer::Customer(int id, const std::string& customerName, const std::string& customerAddress)
    : customerID(id), name(customerName), address(customerAddress) {}

// Virtual destructor
Customer::~Customer() {
    clearCart();
}

// Getters
int Customer::getCustomerID() const {
    return customerID;
}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getAddress() const {
    return address;
}

const std::vector<CartItem>& Customer::getShoppingCart() const {
    return shoppingCart;
}

// Setters
void Customer::setCustomerID(int id) {
    customerID = id;
}

void Customer::setName(const std::string& customerName) {
    name = customerName;
}

void Customer::setAddress(const std::string& customerAddress) {
    address = customerAddress;
}

// Shopping cart methods
void Customer::addToCart(Product* product, int quantity) {
    if (!product || quantity <= 0) {
        return;
    }
    
    // Check if product already exists in cart
    for (auto& item : shoppingCart) {
        if (item.product->getProductID() == product->getProductID()) {
            item.quantity += quantity;
            return;
        }
    }
    
    // Add new item to cart
    shoppingCart.emplace_back(product, quantity);
}

void Customer::removeFromCart(int productID) {
    shoppingCart.erase(
        std::remove_if(shoppingCart.begin(), shoppingCart.end(),
            [productID](const CartItem& item) {
                return item.product->getProductID() == productID;
            }),
        shoppingCart.end()
    );
}

void Customer::clearCart() {
    shoppingCart.clear();
}

bool Customer::isCartEmpty() const {
    return shoppingCart.empty();
}

// Bill calculation - virtual for polymorphism
double Customer::calculateTotalBill() const {
    double total = 0.0;
    for (const auto& item : shoppingCart) {
        total += item.product->getPrice() * item.quantity;
    }
    return total;
}

double Customer::getDiscountRate() const {
    return 0.0; // Base customer has no discount
}

// Display methods - virtual for polymorphism
void Customer::displayCustomerInfo() const {
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Customer Information                                        │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ ID: " << std::setw(10) << customerID << " │ Type: " << std::setw(15) << getCustomerType() << " │" << std::endl;
    std::cout << "│ Name: " << std::setw(25) << std::left << name << std::right << "                        │" << std::endl;
    std::cout << "│ Address: " << std::setw(20) << std::left << address << std::right << "                     │" << std::endl;
    std::cout << "│ Discount Rate: " << std::setw(6) << std::fixed << std::setprecision(1) 
              << (getDiscountRate() * 100) << "%                               │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
}

void Customer::displayCart() const {
    if (isCartEmpty()) {
        std::cout << "\n🛒 Shopping cart is empty!" << std::endl;
        return;
    }
    
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Shopping Cart for " << std::setw(20) << std::left << name << std::right << "                  │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
    
    double subtotal = 0.0;
    for (const auto& item : shoppingCart) {
        double itemTotal = item.product->getPrice() * item.quantity;
        subtotal += itemTotal;
        
        std::cout << "│ " << std::setw(20) << std::left << item.product->getName() 
                  << " │ Qty: " << std::setw(3) << item.quantity 
                  << " │ $" << std::setw(8) << std::fixed << std::setprecision(2) << itemTotal << " │" << std::endl;
    }
    
    std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ Subtotal: $" << std::setw(10) << std::fixed << std::setprecision(2) << subtotal << "                               │" << std::endl;
    
    double discountAmount = subtotal * getDiscountRate();
    if (discountAmount > 0) {
        std::cout << "│ Discount (" << std::setw(4) << (getDiscountRate() * 100) << "%): -$" 
                  << std::setw(8) << discountAmount << "                        │" << std::endl;
    }
    
    double total = subtotal - discountAmount;
    std::cout << "│ TOTAL: $" << std::setw(10) << std::fixed << std::setprecision(2) << total << "                                 │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
}

std::string Customer::getCustomerType() const {
    return "Regular";
}

// File handling methods
void Customer::saveToFile(std::ofstream& file) const {
    file << "REGULAR " << customerID << " " << name << " " << address << std::endl;
}

void Customer::loadFromFile(std::ifstream& file) {
    file >> customerID >> name >> address;
}

// Return product functionality
bool Customer::returnProduct(int productID, int quantity) {
    for (auto it = shoppingCart.begin(); it != shoppingCart.end(); ++it) {
        if (it->product->getProductID() == productID) {
            if (it->quantity >= quantity) {
                it->quantity -= quantity;
                if (it->quantity == 0) {
                    shoppingCart.erase(it);
                }
                return true;
            }
        }
    }
    return false;
}