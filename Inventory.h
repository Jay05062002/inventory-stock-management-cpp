#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <vector>
#include <string>
using namespace std;

class Inventory {
private:
    vector<Product> products;
    string filename;

    int findProductIndex(int id) const;
    void loadFromFile();
    void saveToFile() const;

public:
    Inventory();

    void addProduct();
    void displayProducts() const;
    void searchProduct() const;
    void updateProduct();
    void addStock();
    void sellProduct();
    void deleteProduct();
    void showLowStock() const;
    void showTotalValue() const;

    void run();
};

#endif