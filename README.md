# 🛒 E-Commerce Store Management System

A comprehensive C++ application implementing an e-commerce store management system with object-oriented programming principles, featuring classes, inheritance, polymorphism, and file handling.

## 🎯 Project Overview

This project demonstrates advanced C++ programming concepts including:
- **Classes and Objects**: Well-designed class hierarchy
- **Inheritance**: Customer and PremiumCustomer classes
- **Polymorphism**: Virtual functions for customer types
- **Dynamic Memory Management**: Pointers and STL containers
- **File Handling**: Persistent data storage using fstream
- **Modern UI**: Beautiful text-based interface with emojis

## 📁 Project Structure

```
ecommerce_store/
├── 📄 Product.h              # Product class header
├── 📄 Product.cpp            # Product class implementation
├── 📄 Customer.h             # Customer base class header
├── 📄 Customer.cpp           # Customer base class implementation
├── 📄 PremiumCustomer.h      # PremiumCustomer derived class header
├── 📄 PremiumCustomer.cpp    # PremiumCustomer derived class implementation
├── 📄 Store.h                # Store management system header
├── 📄 Store.cpp              # Store management system implementation
├── 📄 main.cpp               # Main application with menu interface
├── 📄 Makefile               # Build configuration
├── 📄 README.md              # Project documentation
├── 📄 products.txt           # Product data storage (auto-generated)
├── 📄 customers.txt          # Customer data storage (auto-generated)
└── 📄 invoices.txt           # Invoice data storage (auto-generated)
```

## 🌟 Features

### Core Classes

#### 🏷️ Product Class
- Product ID, name, price, available quantity
- Stock management and availability checking
- Virtual functions for extensibility
- File I/O operations

#### 👤 Customer Class (Base)
- Customer information management
- Dynamic shopping cart implementation
- Virtual functions for polymorphism
- Bill calculation methods

#### 👑 PremiumCustomer Class (Derived)
- Inherits from Customer class
- Discount rate management (15-25% based on membership level)
- Membership levels: Gold, Platinum, Diamond
- Free shipping eligibility
- Enhanced bill calculation with discounts

#### 🏪 Store Class
- Product inventory management
- Customer registration and management
- Purchase and return operations
- Invoice generation and tracking
- Comprehensive file handling
- Store statistics and reporting

### 📋 Menu Operations

1. **📦 Add a Product** - Add new products to inventory
2. **🏪 Display All Products** - View all available products
3. **👤 Register a New Customer** - Register regular or premium customers
4. **👥 Display All Customers** - View all registered customers
5. **🛍️ Purchase a Product** - Add products to customer cart
6. **🔄 Return a Product** - Process product returns
7. **🛒 View Customer Cart** - Display customer shopping cart
8. **🧾 Generate Invoice** - Create and display invoice
9. **📋 Display Invoice** - View specific invoice by ID
10. **📊 Display All Invoices** - List all generated invoices
11. **📈 Store Statistics** - View store performance metrics
12. **💾 Save Data and Exit** - Save all data and exit application

### 🔧 Technical Features

- **Polymorphism**: Virtual functions demonstrate runtime polymorphism
- **Dynamic Arrays**: STL vectors for flexible data management
- **File Persistence**: Automatic save/load functionality
- **Memory Management**: Proper destructor implementation
- **Error Handling**: Comprehensive input validation
- **Modern C++**: STL containers and algorithms

## 🚀 Getting Started

### Prerequisites

- C++ compiler (g++ recommended)
- Make utility (optional, for using Makefile)
- Linux/macOS/Windows environment

### 📥 Installation & Compilation

#### Using Makefile (Recommended)

```bash
# Compile the project
make

# Or compile and run immediately
make run

# For debug version
make debug

# For optimized release version
make release

# Clean build files
make clean

# View all available commands
make help
```

#### Manual Compilation

```bash
# Compile all source files
g++ -std=c++11 -Wall -Wextra -g -o ecommerce_store main.cpp Product.cpp Customer.cpp PremiumCustomer.cpp Store.cpp

# Run the application
./ecommerce_store
```

### 🎮 Running the Application

1. **Launch the application**:
   ```bash
   ./ecommerce_store
   ```

2. **Choose to add sample data** (recommended for first-time users):
   - Select 'y' when prompted to add demo products and customers

3. **Navigate the menu**:
   - Use numbers 1-12 to select menu options
   - Follow the prompts for each operation

4. **Sample Workflow**:
   - Add products to inventory
   - Register customers (regular and premium)
   - Make purchases for customers
   - Generate invoices to see discount calculations
   - View statistics and reports

## 💡 Usage Examples

### Adding a Product
```
Enter product name: Gaming Mouse
Enter product price: $59.99
Enter available quantity: 25
✅ Product added successfully!
```

### Registering a Premium Customer
```
Enter customer name: Alice Johnson
Enter customer address: 789 Tech Street
Customer type:
1. Regular Customer
2. Premium Customer
Enter choice (1-2): 2
✅ Premium customer registered successfully!
```

### Making a Purchase
```
Enter customer ID: 2
Enter product ID: 1
Enter quantity: 1
✅ Product added to cart successfully!
```

### Generating Invoice with Discount
The system automatically applies discounts for premium customers:
- **Gold**: 15% discount
- **Platinum**: 20% discount  
- **Diamond**: 25% discount

## 📊 Object-Oriented Programming Concepts Demonstrated

### 1. **Classes and Objects**
- Well-designed classes with proper encapsulation
- Clear separation of data and methods
- Constructors and destructors

### 2. **Inheritance**
- `PremiumCustomer` inherits from `Customer`
- Code reuse and extension
- Protected member access

### 3. **Polymorphism**
- Virtual functions in base classes
- Runtime polymorphism with customer types
- Function overriding in derived classes

### 4. **Dynamic Memory Management**
- Proper use of pointers
- STL containers for dynamic arrays
- Memory cleanup in destructors

### 5. **File Handling**
- Reading from and writing to files
- Data persistence across sessions
- Error handling for file operations

## 🔧 Customization

### Adding New Product Types
Extend the `Product` class or create derived classes for specific product categories.

### Implementing New Customer Types
Create additional customer classes inheriting from `Customer` base class.

### Extending Functionality
- Add new menu options in `main.cpp`
- Implement additional store operations in `Store` class
- Enhance reporting and statistics features

## 🐛 Troubleshooting

### Common Issues

1. **Compilation Errors**:
   - Ensure all header files are in the same directory
   - Check for C++11 compatibility

2. **File Access Issues**:
   - Verify write permissions in the project directory
   - Data files are created automatically on first run

3. **Menu Navigation**:
   - Use numbers 1-12 for menu selection
   - Invalid inputs are handled gracefully

### 🧹 Cleaning Data

```bash
# Remove all data files (use with caution)
make clean-data

# Or manually
rm -f *.txt
```

## 🎓 Learning Objectives

This project demonstrates:
- Advanced C++ programming concepts
- Object-oriented design principles
- File I/O operations
- Dynamic memory management
- STL usage and algorithms
- User interface design
- Real-world application structure

## 📝 Notes

- Data is automatically saved when exiting through the menu
- The system supports unlimited products, customers, and invoices
- All operations include proper error handling and validation
- Premium customer discounts are calculated automatically
- File format is human-readable for debugging purposes

## 🔮 Future Enhancements

Potential improvements could include:
- Database integration
- GUI interface
- Network functionality
- Advanced reporting features
- Product categorization
- Inventory alerts
- Customer loyalty programs

---

**🎉 Enjoy exploring this comprehensive E-Commerce Store Management System!** 

Feel free to modify and extend the codebase for learning purposes or real-world applications.