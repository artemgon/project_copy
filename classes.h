#ifndef classes_products_s
#define classes_products_s
#include "libs.h"

class Product
{
protected:
	string name;
	double price;
	int quantity;
public:
	Product(const string name, double price, int quantity) : name(name), price(price), quantity(quantity) {}
	virtual ~Product() = default;

	virtual string getName() const
	{
		return name;
	}
	virtual double getPrice() const
	{
		return price;
	}
	virtual int getQuantity() const
	{
		return quantity;
	}
	virtual void updatePrice(double newPrice)
	{
		price = newPrice;
	}
	virtual void updateQuantity(int newQuantity)
	{
		quantity = newQuantity;
	}

	virtual string GetInfo() const
	{
		return "Product: " + name + "\nPrice: " + to_string(price) + "\nQuantity: " + to_string(quantity) + "\n";
	}

};


class DiscountedProduct : public Product
{
private:
	double discount;
public:
	DiscountedProduct(const string name, double price, int quantity, double discount) : Product(name, price, quantity), discount(discount) {}
	double getPrice() const override
	{
		return price * (1 - discount / 100);
	}
	void setDiscount(double newDiscount)
	{
		discount = newDiscount;
	}

	virtual string getInfo() const
	{
		return "Product: " + name + "\nPrice: " + to_string(price) + "\nQuantity: " + to_string(quantity) + "\nDiscount: " + to_string(discount) + "%" + "\nDiscounted price:" + to_string(getPrice()) + "\n";
	}
};

class Category
{
private:
	string name;
	vector<shared_ptr<Product>> products;
public:
	Category(const string& name) : name(name) {}


	void addProduct(const shared_ptr<Product>& product)
	{
		products.push_back(product);
	}
	void removeProduct(const string productName)
	{
		products.erase(remove_if(products.begin(), products.end(), [&productName](const shared_ptr<Product>& product)
			{
				return product->getName() == productName;
			}),
			products.end());

	}
	void listProducts() const
	{
		cout << "Category: " << name << endl;
		for (const auto& product : products)
		{
			cout << product->GetInfo() << endl;
		}
	}
	int getProductCount() const
	{
		return products.size();
	}

};

class ShoppingCart {
private:
	vector<shared_ptr<Product>> products;
	double totalAmount;

public:
	ShoppingCart() : totalAmount(0.0) {}

	void addProduct(const shared_ptr<Product>& product) {
		products.push_back(product);
		totalAmount += product->getPrice() * product->getQuantity();
	}

	void removeProduct(const shared_ptr<Product>& product) {
		auto it = remove_if(products.begin(), products.end(), [&product](const shared_ptr<Product>& p) {
			return p->getName() == product->getName();
			});

		if (it != products.end()) {
			totalAmount -= product->getPrice() * product->getQuantity();
			products.erase(it, products.end());
		}
		else {
			cout << "Product not found in the cart." << endl;
		}
	}

	double calculateTotal() const {
		return totalAmount;
	}
	vector<shared_ptr<Product>> getProducts() const {
		return products;
	}
};

class Order {
private:
	int orderId;
	vector<shared_ptr<Product>> products;
	double totalAmount;
	string status;

public:
	Order(int id) : orderId(id), totalAmount(0.0), status("In process") {}

	void createOrder(const ShoppingCart& cart) {
		products = cart.getProducts();
		totalAmount = cart.calculateTotal();
	}

	void updateStatus(const string& newStatus) {
		status = newStatus;
	}

	string getOrderDetails() const {
		string details = "Order ID: " + to_string(orderId) + "\nStatus: " + status + "\nTotal Amount: " + to_string(totalAmount) + "\nProducts:\n";
		for (const auto& product : products) {
			details += product->GetInfo() + "\n";
		}
		return details;
	}
};

#include <string>
#include <vector>

class User {
private:
	int userId;
	string name;
	vector<Order> orderHistory;

public:
	User(int id, const string& userName) : userId(id), name(userName) {}

	void viewOrderHistory() const {
		cout << "Order History for " << name << ":\n";
		for (const auto& order : orderHistory) {
			cout << order.getOrderDetails() << endl;
		}
	}

	void placeOrder(ShoppingCart& cart) {
		static int orderIdCounter = 1;
		Order newOrder(orderIdCounter++);
		newOrder.createOrder(cart);
		orderHistory.push_back(newOrder);
	}

	void addToCart(const shared_ptr<Product>& product, ShoppingCart& cart) {
		cart.addProduct(product);
	}
};

#endif 