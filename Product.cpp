#include "Product.h"
#include <iomanip>
using namespace std;

Product::Product() {
    id = 0;
    name = "";
    price = 0.0;
    quantity = 0;
}

Product::Product(int id, string name, double price, int quantity) {
    this->id = id;
    this->name = name;
    this->price = price;
    this->quantity = quantity;
}

int Product::getId() const {
    return id;
}

string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setName(string name) {
    this->name = name;
}

void Product::setPrice(double price) {
    this->price = price;
}

void Product::addStock(int amount) {
    if (amount > 0) {
        quantity += amount;
    }
}

bool Product::sellStock(int amount) {
    if (amount <= 0 || amount > quantity) {
        return false;
    }

    quantity -= amount;
    return true;
}

void Product::display() const {
    cout << left << setw(8) << id
         << setw(22) << name
         << right << setw(12) << fixed << setprecision(2) << price
         << setw(12) << quantity << '\n';
}