#include "Product.h"
#include <iostream>
#include <iomanip>

// Default constructor
Product::Product() : productID(0), name(""), price(0.0), availableQuantity(0) {}

// Parameterized constructor
Product::Product(int id, const std::string& productName, double productPrice, int quantity)
    : productID(id), name(productName), price(productPrice), availableQuantity(quantity) {}

// Destructor
Product::~Product() {}

// Getters
int Product::getProductID() const {
    return productID;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getAvailableQuantity() const {
    return availableQuantity;
}

// Setters
void Product::setProductID(int id) {
    productID = id;
}

void Product::setName(const std::string& productName) {
    name = productName;
}

void Product::setPrice(double productPrice) {
    if (productPrice >= 0) {
        price = productPrice;
    }
}

void Product::setAvailableQuantity(int quantity) {
    if (quantity >= 0) {
        availableQuantity = quantity;
    }
}

// Core methods
bool Product::isAvailable(int requestedQuantity) const {
    return availableQuantity >= requestedQuantity && requestedQuantity > 0;
}

void Product::updateQuantity(int soldQuantity) {
    if (soldQuantity <= availableQuantity) {
        availableQuantity -= soldQuantity;
    }
}

void Product::restockProduct(int additionalQuantity) {
    if (additionalQuantity > 0) {
        availableQuantity += additionalQuantity;
    }
}

// Virtual function for polymorphism
void Product::displayProduct() const {
    std::cout << "┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Product ID: " << std::setw(10) << productID 
              << " │ Name: " << std::setw(20) << std::left << name << std::right << " │" << std::endl;
    std::cout << "│ Price: $" << std::setw(10) << std::fixed << std::setprecision(2) << price 
              << " │ Available: " << std::setw(15) << availableQuantity << " │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
}

double Product::calculateDiscountedPrice() const {
    return price; // Base implementation returns original price
}

// File handling methods
void Product::saveToFile(std::ofstream& file) const {
    file << productID << " " << name << " " << price << " " << availableQuantity << std::endl;
}

void Product::loadFromFile(std::ifstream& file) {
    file >> productID >> name >> price >> availableQuantity;
}

// Operators
bool Product::operator==(const Product& other) const {
    return productID == other.productID;
}