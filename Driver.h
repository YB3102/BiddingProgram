#ifndef DRIVER_H_
#define DRIVER_H_

#include "Product.h"
#include "User.h"

class Driver
{

public:
    //Methods to delete to reinforce Singleton! 
    Driver(Driver const &) = delete;
    void operator=(Driver const &) = delete;

    // Initialization
    static Driver &GetInstance();
    void driverStart();
    void initialize();
    void addNewBuyerToList(Buyer * buyer);
    void addNewSellerToList(Seller * seller);    

    // Writing to .csv's
    void addNewBuyerToFile(const Buyer& buyer);
    void addNewSellerToFile(const Seller& seller);
    void addNewProductToFile(const Product& product); //TO-DO
    void addNewBidToFile(std :: string product_name, std :: string product_category, std::string seller_name, std :: string buyer_name, double start, double final);

    // New User Methods
    void selectRoleMenu();
    User * createNewUser(int userType);
    
    // Existing User (Login)
    void loginUser(int userType);
    void updateUserFile();
    
    // User Methods
    void buyerMenu(Buyer * currBuyer);
    void sellerMenu(Seller * currSeller);

    //Buyer helpers
    void DisplayActiveProducts();
    void PlaceBid(Buyer * buyer);

    //Display similar products' history
    void viewSimilarProductSalesHistory(Product *selected_product);

    // Product Methods
    void addNewProductToList(Product * product, Seller * seller); //TO-DO
    
    //Helpers
    Buyer *getBuyer(const std::string name);
    Seller *getSeller(const std::string name);
    std::vector<Buyer *> getBuyersList() { return this->buyers_;};
    std::vector<Seller *> getSellersList() { return this->sellers_;};
    void PrintAllUsers();

    // Driver Bidding Simulation Functionality
    void PrintBids(Seller *seller);

    Product * findProductAll(int product_id);

    //Seller bidding function helpers

    int ChangeProductStatusMenu(Seller * seller); //returns a choice from the menu shown depending on product active status

    void ProductStatusChange(Seller * seller, Product * product, int &choice); //handles logic for changing a product's status
private:
    Driver();
    std::vector<Buyer *> buyers_;
    std::vector<Seller *> sellers_;
    std::vector<Product *> products_;
    void loadUsersFromFile(const std::string &filename);
    void loadProductsFromFile(const std::string &filename);
    void DisplayBidHistory(const std::string &filename, ProductCategory product_cat);
};

#endif
