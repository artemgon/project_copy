#include "domain.h"

int main()
{
    try {
        shared_ptr<Product> guitar = make_shared<Product>("Guitar", 1400, 10);
        shared_ptr<DiscountedProduct> electricBass = make_shared<DiscountedProduct>("Electric Bass Guitar", 2300, 10, 15);
        cout << guitar->GetInfo();
        cout << electricBass->GetInfo();
        ShoppingCart cart;
        cart.addProduct(guitar);
        cart.addProduct(electricBass);
        cout << "Products in the cart:\n";
        cart.getProducts();
        User user(1, "Artem");
        user.addToCart(guitar, cart);
        user.addToCart(electricBass, cart);
        user.placeOrder(cart);
        user.viewOrderHistory();
    }
    catch (const std::exception& e) {
        cout << "An error occurred: " << e.what() << endl;
    }
	return 0;
}