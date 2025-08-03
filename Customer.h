#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <fstream>
#include "Product.h"

struct CartItem {
    Product* product;
    int quantity;
    
    CartItem(Product* prod, int qty) : product(prod), quantity(qty) {}
};

class Customer {
protected:
    int customerID;
    std::string name;
    std::string address;
    std::vector<CartItem> shoppingCart;

public:
    // Constructors
    Customer();
    Customer(int id, const std::string& customerName, const std::string& customerAddress);
    
    // Virtual destructor for proper inheritance
    virtual ~Customer();
    
    // Getters
    int getCustomerID() const;
    std::string getName() const;
    std::string getAddress() const;
    const std::vector<CartItem>& getShoppingCart() const;
    
    // Setters
    void setCustomerID(int id);
    void setName(const std::string& customerName);
    void setAddress(const std::string& customerAddress);
    
    // Shopping cart methods
    virtual void addToCart(Product* product, int quantity);
    void removeFromCart(int productID);
    void clearCart();
    bool isCartEmpty() const;
    
    // Bill calculation - virtual for polymorphism
    virtual double calculateTotalBill() const;
    virtual double getDiscountRate() const;
    
    // Display methods - virtual for polymorphism
    virtual void displayCustomerInfo() const;
    virtual void displayCart() const;
    virtual std::string getCustomerType() const;
    
    // File handling methods
    virtual void saveToFile(std::ofstream& file) const;
    virtual void loadFromFile(std::ifstream& file);
    
    // Return product functionality
    bool returnProduct(int productID, int quantity);
};

#endif // CUSTOMER_H