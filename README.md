# Inventory and Stock Management System

A beginner-friendly console-based Inventory and Stock Management System developed using C++ and CMake.

## Features

- Add new products with ID, name, price, and quantity
- Display all available products
- Search for products using their ID
- Update product names and prices
- Add stock when new items arrive
- Sell products and automatically reduce stock
- Delete products from inventory
- Display low-stock products (5 or fewer items)
- Calculate the total inventory value
- Save and load product data using file handling

## Technologies Used

- **Language:** C++
- **Build System:** CMake
- **C++ Standard:** C++17
- **Data Storage:** Text file (`products.txt`)

## Project Structure

```text
InventoryManagementSystem/
├── CMakeLists.txt
├── Product.h
├── Product.cpp
├── Inventory.h
├── Inventory.cpp
├── main.cpp
└── README.md
```

The `products.txt` file is created automatically when the program saves inventory data.

## Requirements

Install the following software before running the project:

- A C++17-compatible compiler, such as GCC/MinGW or MSVC
- CMake version 3.16 or newer

## How to Build and Run

### 1. Open the project folder

Open a terminal or PowerShell in the `InventoryManagementSystem` directory.

### 2. Configure the project

```bash
cmake -S . -B build
```

### 3. Build the application

```bash
cmake --build build
```

### 4. Run the application

For a typical MinGW or single-configuration build:

```powershell
.\build\inventory.exe
```

For a Visual Studio multi-configuration build:

```powershell
.\build\Debug\inventory.exe
```

Use the executable path appropriate for your CMake generator.

## How to Use

After starting the application, select an option from the menu:

1. Add Product
2. Display All Products
3. Search Product
4. Update Product
5. Add Stock
6. Sell Product
7. Delete Product
8. Show Low Stock
9. Show Total Inventory Value
0. Exit

