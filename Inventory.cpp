#include "Inventory.h"

#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

Inventory::Inventory() {
    filename = "products.txt";
    loadFromFile();
}

int Inventory::findProductIndex(int id) const {
    for (int i = 0; i < static_cast<int>(products.size()); i++) {
        if (products[i].getId() == id) {
            return i;
        }
    }

    return -1;
}

void Inventory::loadFromFile() {
    ifstream file(filename);

    if (!file) {
        return;
    }

    int id, quantity;
    double price;
    string name;

    while (file >> id >> quoted(name) >> price >> quantity) {
        products.emplace_back(id, name, price, quantity);
    }

    file.close();
}

void Inventory::saveToFile() const {
    ofstream file(filename);

    for (const Product& product : products) {
        file << product.getId() << ' '
             << quoted(product.getName()) << ' '
             << product.getPrice() << ' '
             << product.getQuantity() << '\n';
    }

    file.close();
}

void Inventory::addProduct() {
    int id, quantity;
    double price;
    string name;

    cout << "Enter product ID: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (id <= 0 || findProductIndex(id) != -1) {
        cout << "Invalid or duplicate product ID.\n";
        return;
    }

    cout << "Enter product name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter price: ";
    if (!(cin >> price) || price < 0) {
        cout << "Invalid price.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter initial quantity: ";
    if (!(cin >> quantity) || quantity < 0) {
        cout << "Invalid quantity.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    products.emplace_back(id, name, price, quantity);
    saveToFile();

    cout << "Product added successfully.\n";
}

void Inventory::displayProducts() const {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << '\n'
         << left << setw(8) << "ID"
         << setw(22) << "Name"
         << right << setw(12) << "Price"
         << setw(12) << "Quantity" << '\n';

    cout << string(54, '-') << '\n';

    for (const Product& product : products) {
        product.display();
    }
}

void Inventory::searchProduct() const {
    int id;

    cout << "Enter product ID: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProductIndex(id);

    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "\nProduct found:\n";
    cout << left << setw(8) << "ID"
         << setw(22) << "Name"
         << right << setw(12) << "Price"
         << setw(12) << "Quantity" << '\n';

    products[index].display();
}

void Inventory::updateProduct() {
    int id;

    cout << "Enter product ID to update: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProductIndex(id);

    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    string name;
    double price;

    cout << "Enter new product name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter new price: ";
    if (!(cin >> price) || price < 0) {
        cout << "Invalid price.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    products[index].setName(name);
    products[index].setPrice(price);

    saveToFile();
    cout << "Product updated successfully.\n";
}

void Inventory::addStock() {
    int id, amount;

    cout << "Enter product ID: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProductIndex(id);

    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter quantity to add: ";
    if (!(cin >> amount) || amount <= 0) {
        cout << "Enter a positive quantity.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    products[index].addStock(amount);
    saveToFile();

    cout << "Stock added successfully.\n";
}

void Inventory::sellProduct() {
    int id, amount;

    cout << "Enter product ID: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProductIndex(id);

    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter quantity to sell: ";
    if (!(cin >> amount) || amount <= 0) {
        cout << "Enter a positive quantity.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (products[index].sellStock(amount)) {
        saveToFile();
        cout << "Sale recorded. Stock updated.\n";
    } else {
        cout << "Not enough stock available.\n";
    }
}

void Inventory::deleteProduct() {
    int id;

    cout << "Enter product ID to delete: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProductIndex(id);

    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    products.erase(products.begin() + index);
    saveToFile();

    cout << "Product deleted successfully.\n";
}

void Inventory::showLowStock() const {
    const int LOW_STOCK_LIMIT = 5;
    bool found = false;

    cout << "\nProducts with 5 or fewer items:\n";

    for (const Product& product : products) {
        if (product.getQuantity() <= LOW_STOCK_LIMIT) {
            if (!found) {
                cout << left << setw(8) << "ID"
                     << setw(22) << "Name"
                     << right << setw(12) << "Price"
                     << setw(12) << "Quantity" << '\n';
            }

            product.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No low-stock products.\n";
    }
}

void Inventory::showTotalValue() const {
    double total = 0;

    for (const Product& product : products) {
        total += product.getPrice() * product.getQuantity();
    }

    cout << fixed << setprecision(2);
    cout << "Total inventory value: " << total << '\n';
}

void Inventory::run() {
    int choice;

    do {
        cout << "\n===== INVENTORY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Add Stock\n";
        cout << "6. Sell Product\n";
        cout << "7. Delete Product\n";
        cout << "8. Show Low Stock\n";
        cout << "9. Show Total Inventory Value\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                addStock();
                break;
            case 6:
                sellProduct();
                break;
            case 7:
                deleteProduct();
                break;
            case 8:
                showLowStock();
                break;
            case 9:
                showTotalValue();
                break;
            case 0:
                saveToFile();
                cout << "Inventory saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}