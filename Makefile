# Makefile for E-Commerce Store Management System

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = ecommerce_store

# Source files
SOURCES = main.cpp Product.cpp Customer.cpp PremiumCustomer.cpp Store.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files (for dependency tracking)
HEADERS = Product.h Customer.h PremiumCustomer.h Store.h

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✅ Build successful! Executable: $(TARGET)"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Cleaned build files"

# Clean data files (use with caution)
clean-data:
	rm -f *.txt
	@echo "🗑️  Cleaned data files"

# Install/Setup (create directories if needed)
install:
	@echo "📁 Setting up project structure..."
	@mkdir -p build
	@echo "✅ Project setup complete"

# Run the application
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -O0
debug: $(TARGET)
	@echo "🐛 Debug build complete"

# Release build
release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)
	@echo "🚀 Release build complete"

# Help message
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove build files"
	@echo "  clean-data - Remove data files (*.txt)"
	@echo "  install  - Setup project structure"
	@echo "  run      - Build and run the application"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build optimized release version"
	@echo "  help     - Show this help message"

# Prevent make from treating these as file targets
.PHONY: all clean clean-data install run debug release help