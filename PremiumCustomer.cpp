#include "PremiumCustomer.h"
#include <iostream>
#include <iomanip>

// Default constructor
PremiumCustomer::PremiumCustomer() 
    : Customer(), discountRate(0.15), membershipFee(50.0), membershipLevel("Gold") {}

// Parameterized constructor
PremiumCustomer::PremiumCustomer(int id, const std::string& customerName, 
                                const std::string& customerAddress, double discount, const std::string& level)
    : Customer(id, customerName, customerAddress), discountRate(discount), 
      membershipFee(50.0), membershipLevel(level) {
    
    // Set membership fee based on level
    if (level == "Platinum") {
        membershipFee = 100.0;
        discountRate = 0.20;
    } else if (level == "Diamond") {
        membershipFee = 200.0;
        discountRate = 0.25;
    } else {
        membershipFee = 50.0;
        discountRate = 0.15;
    }
}

// Destructor
PremiumCustomer::~PremiumCustomer() {}

// Getters
double PremiumCustomer::getMembershipFee() const {
    return membershipFee;
}

std::string PremiumCustomer::getMembershipLevel() const {
    return membershipLevel;
}

// Setters
void PremiumCustomer::setDiscountRate(double discount) {
    if (discount >= 0.0 && discount <= 1.0) {
        discountRate = discount;
    }
}

void PremiumCustomer::setMembershipFee(double fee) {
    if (fee >= 0.0) {
        membershipFee = fee;
    }
}

void PremiumCustomer::setMembershipLevel(const std::string& level) {
    membershipLevel = level;
    
    // Update discount rate and fee based on level
    if (level == "Platinum") {
        membershipFee = 100.0;
        discountRate = 0.20;
    } else if (level == "Diamond") {
        membershipFee = 200.0;
        discountRate = 0.25;
    } else {
        membershipLevel = "Gold";
        membershipFee = 50.0;
        discountRate = 0.15;
    }
}

// Override virtual functions for polymorphism
double PremiumCustomer::calculateTotalBill() const {
    double subtotal = 0.0;
    for (const auto& item : shoppingCart) {
        subtotal += item.product->getPrice() * item.quantity;
    }
    
    double discountAmount = subtotal * discountRate;
    return subtotal - discountAmount;
}

double PremiumCustomer::getDiscountRate() const {
    return discountRate;
}

void PremiumCustomer::displayCustomerInfo() const {
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 🌟 PREMIUM Customer Information                             │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ ID: " << std::setw(10) << customerID << " │ Type: " << std::setw(15) << getCustomerType() << " │" << std::endl;
    std::cout << "│ Name: " << std::setw(25) << std::left << name << std::right << "                        │" << std::endl;
    std::cout << "│ Address: " << std::setw(20) << std::left << address << std::right << "                     │" << std::endl;
    std::cout << "│ Membership Level: " << std::setw(10) << std::left << membershipLevel << std::right << "                       │" << std::endl;
    std::cout << "│ Discount Rate: " << std::setw(6) << std::fixed << std::setprecision(1) 
              << (discountRate * 100) << "%                               │" << std::endl;
    std::cout << "│ Membership Fee: $" << std::setw(8) << std::fixed << std::setprecision(2) 
              << membershipFee << "                             │" << std::endl;
    
    if (isEligibleForFreeShipping()) {
        std::cout << "│ ✅ FREE SHIPPING ELIGIBLE                               │" << std::endl;
    }
    
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
}

std::string PremiumCustomer::getCustomerType() const {
    return "Premium (" + membershipLevel + ")";
}

// Override file handling methods
void PremiumCustomer::saveToFile(std::ofstream& file) const {
    file << "PREMIUM " << customerID << " " << name << " " << address << " " 
         << discountRate << " " << membershipFee << " " << membershipLevel << std::endl;
}

void PremiumCustomer::loadFromFile(std::ifstream& file) {
    file >> customerID >> name >> address >> discountRate >> membershipFee >> membershipLevel;
}

// Premium-specific methods
double PremiumCustomer::calculateDiscountAmount() const {
    double subtotal = 0.0;
    for (const auto& item : shoppingCart) {
        subtotal += item.product->getPrice() * item.quantity;
    }
    return subtotal * discountRate;
}

bool PremiumCustomer::isEligibleForFreeShipping() const {
    return membershipLevel == "Platinum" || membershipLevel == "Diamond";
}

void PremiumCustomer::upgradeMembership() {
    if (membershipLevel == "Gold") {
        setMembershipLevel("Platinum");
        std::cout << "🎉 Congratulations! You've been upgraded to Platinum membership!" << std::endl;
    } else if (membershipLevel == "Platinum") {
        setMembershipLevel("Diamond");
        std::cout << "🎉 Congratulations! You've been upgraded to Diamond membership!" << std::endl;
    } else {
        std::cout << "You already have the highest membership level (Diamond)!" << std::endl;
    }
}