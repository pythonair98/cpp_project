#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>

class Product {
private:
    int productID;
    std::string name;
    double price;
    int availableQuantity;

public:
    // Constructors
    Product();
    Product(int id, const std::string& productName, double productPrice, int quantity);
    
    // Destructor
    virtual ~Product();
    
    // Getters
    int getProductID() const;
    std::string getName() const;
    double getPrice() const;
    int getAvailableQuantity() const;
    
    // Setters
    void setProductID(int id);
    void setName(const std::string& productName);
    void setPrice(double productPrice);
    void setAvailableQuantity(int quantity);
    
    // Core methods
    bool isAvailable(int requestedQuantity) const;
    void updateQuantity(int soldQuantity);
    void restockProduct(int additionalQuantity);
    
    // Virtual function for polymorphism
    virtual void displayProduct() const;
    virtual double calculateDiscountedPrice() const;
    
    // File handling methods
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
    
    // Operators
    bool operator==(const Product& other) const;
};

#endif // PRODUCT_H