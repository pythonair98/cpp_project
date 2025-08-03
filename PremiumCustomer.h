#ifndef PREMIUMCUSTOMER_H
#define PREMIUMCUSTOMER_H

#include "Customer.h"

class PremiumCustomer : public Customer {
private:
    double discountRate;
    double membershipFee;
    std::string membershipLevel;

public:
    // Constructors
    PremiumCustomer();
    PremiumCustomer(int id, const std::string& customerName, const std::string& customerAddress, 
                   double discount = 0.15, const std::string& level = "Gold");
    
    // Destructor
    virtual ~PremiumCustomer();
    
    // Getters
    double getMembershipFee() const;
    std::string getMembershipLevel() const;
    
    // Setters
    void setDiscountRate(double discount);
    void setMembershipFee(double fee);
    void setMembershipLevel(const std::string& level);
    
    // Override virtual functions for polymorphism
    virtual double calculateTotalBill() const override;
    virtual double getDiscountRate() const override;
    virtual void displayCustomerInfo() const override;
    virtual std::string getCustomerType() const override;
    
    // Override file handling methods
    virtual void saveToFile(std::ofstream& file) const override;
    virtual void loadFromFile(std::ifstream& file) override;
    
    // Premium-specific methods
    double calculateDiscountAmount() const;
    bool isEligibleForFreeShipping() const;
    void upgradeMembership();
};

#endif // PREMIUMCUSTOMER_H