#include <fstream>
#include <sstream>
#include <iostream>
#include "Driver.h"
#include "User.h"
#include "Product.h"
#include <random>

// Features to Implement:
//  - Bid Simulation
//

// Features to Fix:

Driver::Driver() {}

Driver &Driver::GetInstance()
{
    // This static variable ensures the instance is only created once.
    static Driver instance;

    // Return a reference to the static instance.
    return instance;
}

// Driver Initialization
void Driver::driverStart()
{
    initialize();
    selectRoleMenu();
}

void Driver::initialize()
{
    loadUsersFromFile("Users.csv");
    loadProductsFromFile("Products.csv");
    PrintAllUsers();
    std::cout << "Initialization Complete!" << std::endl;
}

/**
 * @brief Initializes users from Users.csv.
 * 
 * @param filename 
 */
void Driver::loadUsersFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    // Skip the header line
    getline(file, line);

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Split the line by commas
        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }

        std::string name = tokens[0];
        std::string phone = tokens[1];
        std::string address = tokens[2];
        double balance = std::stod(tokens[3]); // Convert balance from string to double
        std::string role = tokens[4];

        if (role == "Buyer")
        {
            Buyer *buyer = new Buyer(name, phone, address, balance);
            addNewBuyerToList(buyer);
        }
        else if (role == "Seller")
        {
            Seller *seller = new Seller(name, phone, address, balance);
            addNewSellerToList(seller);
        }
    }
}

/**
 * @brief Initializes default generic products from Products.csv
 * 
 * @param filename 
 */
void Driver::loadProductsFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    // Skip Header Line
    getline(file, line);

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, this->sellers_.size() - 1); 

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Split line by commas
        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        std ::string product_name = tokens[0];
        ProductCategory product_category = StringtoCategory(tokens[1]);
        bool isActive;

        if (tokens[2] == "True")
        {
            isActive = true;
        }
        else
        {
            isActive = false;
        }

        ProductQuality product_quality = StringtoQuality(tokens[3]);
        double starting_price = std::stod(tokens[4]);

        //int random_index = rand() % int(this->sellers_.size());

        int random_index = dis(gen);

        Electronics *electronic = nullptr;
        Clothing *clothing = nullptr;
        Vehicle *vehicle = nullptr;
        Media *media = nullptr;
        Furniture *furniture = nullptr;

        switch (product_category)
        {
        case ProductCategory ::Electronics:
            electronic = new Electronics(product_name, isActive, product_quality, starting_price);
            electronic->SetProductSeller(this->sellers_.at(random_index));
            this->sellers_.at(random_index)->PutProductSale(electronic);
            this->sellers_.at(random_index)->AddProductToInventory(electronic);
            break;
        case ProductCategory ::Clothing:
            clothing = new Clothing(product_name, isActive, product_quality, starting_price);
            clothing->SetProductSeller(this->sellers_.at(random_index));
            this->sellers_.at(random_index)->PutProductSale(clothing);
            this->sellers_.at(random_index)->AddProductToInventory(clothing);
            break;
        case ProductCategory ::Furniture:
            furniture = new Furniture(product_name, isActive, product_quality, starting_price);
            furniture->SetProductSeller(this->sellers_.at(random_index));
            this->sellers_.at(random_index)->PutProductSale(furniture);
            this->sellers_.at(random_index)->AddProductToInventory(furniture);
            break;
        case ProductCategory ::Media:
            media = new Media(product_name, isActive, product_quality, starting_price);
            media->SetProductSeller(this->sellers_.at(random_index));
            this->sellers_.at(random_index)->PutProductSale(media);
            this->sellers_.at(random_index)->AddProductToInventory(media);
            break;
        case ProductCategory ::Vehicle:
            vehicle = new Vehicle(product_name, isActive, product_quality, starting_price);
            vehicle->SetProductSeller(this->sellers_.at(random_index));
            this->sellers_.at(random_index)->PutProductSale(vehicle);
            this->sellers_.at(random_index)->AddProductToInventory(vehicle);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Displays bidding history for products belonging to a specific category recorded in HistoricalBid.csv
 * 
 * @param filename 
 * @param product_cat 
 */
void Driver :: DisplayBidHistory(const std::string &filename, ProductCategory product_cat){
    std::ifstream file(filename);
    std::string line;

    // Skip the header line
    getline(file, line);

    int counter = 0;

    std :: cout << "Printing bid history for similar products." << std :: endl;

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Split the line by commas
        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.empty() == false){
            std::string product_name = tokens[0];
            ProductCategory pc = StringtoCategory(tokens[1]);
            std::string seller_name = tokens[2];
            std :: string buyer_name = tokens[3];
            double start = std::stod(tokens[4]); 
            double final = std::stod(tokens[5]);

            if (pc == product_cat){
                counter = counter + 1;
                std :: cout << product_name << " with starting price "<< start << " sold by "<< seller_name << " to " << buyer_name << " for final price " << final << std :: endl;
            }
        }
    }

    if (counter == 0){
        std :: cout << "No similar products found in bid history." << std :: endl;
    }
}

/**
 * @brief Displays all active products for sale in the system.
 * 
 */
void Driver :: DisplayActiveProducts(){

    std :: cout << "Displaying all active products currently in system." << std :: endl;
    for (auto it = this -> sellers_.begin(); it != this->sellers_.end(); ++it){
        
        (*it) -> ListedProductsPrint();
        
    }
}

// void Driver::createNewProduct()
// {
// }

//i don't believe this is needed
void Driver::addNewProductToList(Product * product, Seller * seller)
{
}

/**
 * @brief Adds a new product to Product.csv.
 * 
 * @param product 
 */
void Driver :: addNewProductToFile(const Product &product){

    std :: string isActive;
    if (product.GetIsActive()==true){
        isActive = "True";
    }
    else{
        isActive = "False";
    }
    std::ofstream file("Products.csv", std::ios::app); // Open in append mode
    if (file.is_open())
    {
        file << product.GetProductName() << ","
             << CategoryString(product.GetProdutCategory()) << ","
             << isActive << ","
             << QualityString(product.GetProductQuality()) << ","
             << product.GetStartingPrice() << std :: endl;
    }
    else
    {
        std::cerr << "Failed to open Products.csv for appending" << std::endl;
    }
}

// Driver List / File User Management

/**
 * @brief Adds a new buyer to the Users.csv file
 * 
 * @param buyer 
 */
void Driver::addNewBuyerToFile(const Buyer &buyer)
{
    std::ofstream file("Users.csv", std::ios::app); // Open in append mode
    if (file.is_open())
    {
        file << buyer.GetName() << ","
             << buyer.GetPhone() << ","
             << buyer.GetAddress() << ","
             << buyer.GetAccountBalance() << ","
             << "Buyer" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open Users.csv for appending" << std::endl;
    }
}

/**
 * @brief Adds a new seller to Users.csv
 * 
 * @param seller 
 */
void Driver::addNewSellerToFile(const Seller &seller)
{
    std::ofstream file("Users.csv", std::ios::app); // Open in append mode
    if (file.is_open())
    {
        file << seller.GetName() << ","
             << seller.GetPhone() << ","
             << seller.GetAddress() << ","
             << seller.GetAccountBalance() << ","
             << "Seller" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open Users.csv for appending" << std::endl;
    }
}

/**
 * @brief Adds a new bid log to the HistoricalBid.csv file
 * 
 * @param product_name 
 * @param product_category 
 * @param seller_name 
 * @param buyer_name 
 * @param start 
 */
void Driver::addNewBidToFile(std :: string product_name, std :: string product_category, std::string seller_name, std :: string buyer_name, double start, double final)
{
    std::ofstream file("HistoricalBid.csv", std::ios::app); // Open in append mode
    if (file.is_open())
    {
        file << product_name << ","
             << product_category << ","
             << seller_name << ","
             << buyer_name << ","
             << start << ","
             << final << std::endl;
    }
    else
    {
        std::cerr << "Failed to open HistoricalBid.csv for appending" << std::endl;
    }
}

/**
 * @brief Pushes a new buyer to the driver's buyer list
 * 
 * @param buyer 
 */
void Driver::addNewBuyerToList(Buyer *buyer)
{
    this->buyers_.push_back(buyer);
}

/**
 * @brief Pushes a new seller to the driver's seller list
 * 
 * @param seller 
 */
void Driver::addNewSellerToList(Seller *seller)
{
    this->sellers_.push_back(seller);
}

/**
 * @brief Updates user's information and also their info in the Users.csv file
 * 
 */
void Driver::updateUserFile()
{
    std::ofstream file("Users.csv", std::ofstream::trunc); // Open the file in trunc mode to overwrite it

    if (!file.is_open())
    {
        std::cerr << "Failed to open Users.csv for updating" << std::endl;
        return;
    }

    // Skip header
    // file << "UserID,Name,Phone,Address,Balance,Role" << std::endl;
    file << "Name,Phone,Address,Balance,Role" << std::endl;

    // Iterate over all users and write their updated information to the file
    for (const auto &buyer : buyers_)
    {
        file << buyer->GetName() << "," << buyer->GetPhone() << "," << buyer->GetAddress() << "," << buyer->GetAccountBalance() << ",Buyer" << std::endl;
    }

    for (const auto &seller : sellers_)
    {
        file << seller->GetName() << "," << seller->GetPhone() << "," << seller->GetAddress() << "," << seller->GetAccountBalance() << ",Seller" << std::endl;
    }

    file.close();
    std::cout << "User information updated in file successfully." << std::endl;
}

/**
 * @brief Prints all users in the system
 * 
 */
void Driver::PrintAllUsers()
{
    std::cout << "=====================================================" << std::endl;
    std::cout << "\t---Printing Buyers List---" << std::endl;
    for (Buyer *buyer : this->buyers_)
    {
        std::cout << buyer->GetName() << std::endl;
    }
    std::cout << "\t---Printing Sellers List---" << std::endl;
    for (Seller * seller : this->sellers_)
    {
        std::cout << seller->GetName() << std::endl;
    }
    std::cout << "=====================================================" << std::endl;
}

// Driver Menus

/**
 * @brief Main menu that runs in a loop and lets user select their role.
 * 
 */
void Driver::selectRoleMenu()
{
    bool running = true;

    while (running)
    {
        std::cout << "+==========================Role Selection=========================+" << std::endl;
        std::cout << "1.) New Buyer" << std::endl;
        std::cout << "2.) New Seller" << std::endl;
        std::cout << "3.) Existing Buyer" << std::endl;
        std::cout << "4.) Existing Seller" << std::endl;
        std::cout << "5.) Exit Program" << std::endl;
        std::cout << "+=================================================================+" << std::endl;

        std::cout << "Input Option: ";
        int choice;
        std::cin >> choice;

        // Clearing input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            createNewUser(choice);
        case 2:
            createNewUser(choice);
            break;
        case 3:
            loginUser(choice);
        case 4:
            loginUser(choice);
            break;
        case 5:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid Option. Please try again." << std::endl;
            break;
        }
    }
}

/**
 * @brief Lets a user login using their phone number as the unique ID.
 * 
 * @param userType 
 */
void Driver::loginUser(int userType)
{
    std::cout << "Please enter your phone number: ";
    std::string phoneNumber;
    std::cin >> phoneNumber;

    // Clearing input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (userType == 3)
    { // Existing Buyer
        for (Buyer *buyer : buyers_)
        {
            if (buyer->GetPhone() == phoneNumber)
            {
                std::cout << "Login successful!" << std::endl;
                buyerMenu(buyer);
                return;
            }
        }
    }
    else if (userType == 4)
    { // Existing Seller
        for (Seller *seller : sellers_)
        {
            if (seller->GetPhone() == phoneNumber)
            {
                std::cout << "Login successful!" << std::endl;
                sellerMenu(seller);
                return;
            }
        }
    }

    std::cout << "User not found. Please check the phone number and try again." << std::endl;
}

/**
 * @brief Creates a new user depending on the value of userType. Seller or buyer.
 * 
 * @param userType 
 * @return User* 
 */
User *Driver::createNewUser(int userType)
{
    std::string name;
    std::string phone;
    std::string address;
    double account_balance = 1000.00; // Default account balance

    std::cout << "+===========================User Creation=========================+" << std::endl;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    std::cout << "---Please enter your name---" << std::endl;
    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "---Please enter your phone number---" << std::endl;
    std::cout << "Phone Number: ";
    std::getline(std::cin, phone);

    std::cout << "---Please enter your home address---" << std::endl;
    std::cout << "Home Address: ";
    std::getline(std::cin, address);

    std::cout << "---As a new user, you are given a starting account balance of: $1000---" << std::endl;
    std::cout << "+=================================================================+" << std::endl;

    if (userType == 1)
    {
        Buyer *newBuyer = new Buyer(name, phone, address, account_balance);
        addNewBuyerToList(newBuyer);
        addNewBuyerToFile(*newBuyer);
        buyerMenu(newBuyer);
        return newBuyer;
    }
    else if (userType == 2)
    {
        Seller *newSeller = new Seller(name, phone, address, account_balance);
        addNewSellerToList(newSeller);
        addNewSellerToFile(*newSeller);
        sellerMenu(newSeller);
        return newSeller;
    }
    else
    {
        std::cout << "User creation failed!" << std::endl;
        return nullptr;
    }
}

// Driver User / Product Management

/**
 * @brief Menu for buyer that runs in a loop. Has all the options as desired from document.
 * 
 * @param currBuyer 
 */
void Driver::buyerMenu(Buyer *currBuyer)
{
    bool running = true;
    while (running)
    {
        std::cout << "Welcome: " << currBuyer->GetName() << "!" << std::endl;
        std::cout << "+=====Buyer Options=====+" << std::endl;
        std::cout << "\t1. View active products for sale." << std::endl;
        std::cout << "\t2. Place a bid on an active product for sale." << std::endl;
        std::cout << "\t3. View all placed bids that are currently active." << std::endl;
        std::cout << "\t4. View information of all purchased products." << std::endl;
        std::cout << "\t5. View and respond to my Messages" << std::endl;
        std::cout << "\t6. View my Account Balance" << std::endl;
        std::cout << "\t7. Update My User Information" << std::endl;
        std::cout << "\t8. Return to Main Menu" << std::endl;
        std::cout << "\t9. Exit" << std::endl;
        std::cout << "+========================+" << std::endl;

        std::cout << "Your choice: ";
        int choice;
        std::cin >> choice;

        // Clearing input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            this -> DisplayActiveProducts();
            break;
        case 2:
            // Implement functionality for options 1 and 2
            //ask for pid
            //will need a make bid function
            this -> PlaceBid(currBuyer);
            break;
        case 3:
            // Implement functionality for option 3
            currBuyer->ViewCurrentBids();
            break;
        case 4:
            currBuyer->ViewOwnedProducts();
            break;
        case 5:
            currBuyer->viewMessages(currBuyer);
            break;
        case 6:
            std::cout << "Current Account Balance: $" << currBuyer->GetAccountBalance() << std::endl;
            break;
        case 7:
            currBuyer->updateUserInformation(currBuyer);
            updateUserFile();
            break;
        case 8:
            std::cout << "Returning to main menu..." << std::endl;
            running = false; // Exit the loop to return to the main menu
            break;
        case 9:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            exit(0); // Exit the application
        default:
            std::cout << "Invalid Option. Please try again." << std::endl;
            break;
        }
    }
}

/**
 * @brief Menu for seller that runs in a loop. Has all the options as desired from document.
 * 
 * @param currSeller 
 */
void Driver::sellerMenu(Seller *currSeller)
{   
    std :: string find_choice;
    ProductCategory pc;
    bool running = true;
    while (running)
    {
        std::cout << "Welcome: " << currSeller->GetName() << "!" << std::endl;
        std::cout << "+=====Seller Options=====+" << std::endl;
        std::cout << "\t1. Put a Product on Sale" << std::endl;
        std::cout << "\t2. Change an existing Product's Sale Status" << std::endl;
        std::cout << "\t3. View Other Similar Sold Products' Bid History" << std::endl;
        std::cout << "\t4. View my Products" << std::endl;
        std::cout << "\t5. View my Messages" << std::endl;
        std::cout << "\t6. View my Account Balance" << std::endl;
        std::cout << "\t7. Update My User Information" << std::endl;
        std::cout << "\t8. Return to Main Menu" << std::endl;
        std::cout << "\t9. Exit" << std::endl;
        std::cout << "+========================+" << std::endl;

        std::cout << "Your choice: ";
        int choice;
        std::cin >> choice;

        // Clearing input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            std::cout << "====Create New Product to Sell or Sell Existing Product?====" << std::endl;
            std::cout << "\t1. Create New Product" << std::endl;
            std::cout << "\t2. List an existing Product from My Inventory" << std::endl;
            std::cout << "+========================+" << std::endl;
            std::cout << "Your choice: ";
            int choice_1;
            std::cin >> choice_1;
            if(choice_1 == 1){
                currSeller->createNewProduct();
            }
            else if (choice_1 == 2){
                currSeller->productOverview(); //need to do something about this!
            }
            else{
                std::cout << " Invalid Option " << std::endl;
            }
        }
        break;
        case 2:
            // Implement functionality for options 1 and 2
            this -> ChangeProductStatusMenu(currSeller);
            break;
        case 3:
            // Implement functionality for option 3
            std :: cout << "Please enter the product category of the products whose bid history you wish to view." << std :: endl;
            std::cout << "+=====Create New Product=====+" << std::endl;
            std::cout << "\t1Electronics" << std::endl;
            std::cout << "\tVehicle" << std::endl;
            std::cout << "\tFurniture" << std::endl;
            std::cout << "\tClothing" << std::endl;
            std::cout << "\tMedia" << std::endl;
            std::cout << "\tOther" << std::endl;
            std::cout << "\tExit" << std::endl;
            std::cout << "+============================+" << std::endl;

            std::cout << "Select Product Category. Enter the full word: ";
            std :: cin >> find_choice;
            pc = StringtoCategory(find_choice); // Ensure this function gracefully handles invalid inputs

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            this -> DisplayBidHistory("HistoricalBid.csv", pc);

            break;
        case 4:
            currSeller->productOverview(); //list owned
            currSeller -> ListSoldProducts(); //list sold
            break;
        case 5:
            currSeller->viewMessages(currSeller);
            break;
        case 6:
            std::cout << "Current Account Balance: $" << currSeller->GetAccountBalance() << std::endl;
            break;
        case 7:
            currSeller->updateUserInformation(currSeller);
            updateUserFile();
            break;
        case 8:
            std::cout << "Returning to main menu..." << std::endl;
            running = false; // Exit the loop to return to the main menu
            break;
        case 9:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            exit(0); // Exit the application
        default:
            std::cout << "Invalid Option. Please try again." << std::endl;
            break;
        }
    }
}

// Bidding!

/**
 * @brief Find the specific product and whether it is active from every product in the system with the passed product_id as identifier.
 *          Returns null otherwise.
 * 
 * @param product_id 
 * @return Product* 
 */
Product * Driver :: findProductAll(int product_id){

    Product * return_pointer = nullptr;
    for (auto it = this -> sellers_.begin(); it != this->sellers_.end(); ++it){
        
        return_pointer = (*it)->findProduct(product_id);

        if(return_pointer != nullptr){
            std :: cout << "Product found in active sales." << std :: endl;
            return return_pointer;
        }
    }
    std :: cout << "Product not in active sales." << std :: endl;
    return nullptr;
}

/**
 * @brief Function for user to place a bid on their desired product from product_id.
 * 
 * @param bidder 
 */
void Driver :: PlaceBid(Buyer * bidder){
    std::cout << "Please enter the product ID of the active product you wish to bid on." << std :: endl;
    std::cout << "Your choice:" << std :: endl;
    int choice = 0;

    std :: cin >> choice;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Product * bid_product = this->findProductAll(choice);

    std :: cout << bid_product -> GetProductName() << std :: endl;

    std :: cout << bid_product << std :: endl;

    if(bid_product == nullptr){
        std :: cout << "Valid product not found. Returning." << std :: endl;
        return;
    }

    if(bid_product->GetProductSeller()->GetPhone() == bidder -> GetPhone()){
        std :: cout << "You can't bid on your own product User! Time for jail." << std :: endl;
        return; 
    }

    std::cout << "Product info is as follows:" << std :: endl;
    bid_product->ProductInfo();

    std::cout << "Please enter the amount you wish to bid on the product." << std :: endl;
    int bid_amount;
    std::cin >> bid_amount;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (bid_amount < 0 || bid_amount > bidder -> GetAccountBalance()){
        std :: cout << "Amount invalid or insufficient account balance. Returning." << std :: endl;
        return;
    }

    bidder->BidOnProduct(bid_product, bid_amount);
    bid_product->SetLatestBid(bid_amount);

    std :: cout << "Bid placed successfully!" << std :: endl;

    return;
}

/**
 * @brief Menu to deal with seller adjusting a product's status from the main menu loop. Takes the seller as a pointer.
 * 
 * @param seller 
 * @return int 
 */
int Driver :: ChangeProductStatusMenu(Seller * seller){

    std :: cout << "Enter the product ID for your product that you wish to change the status of:" << std :: endl;
    int pid = 0;
    std :: cin >> pid;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //bool running = true;

    Product * change_product = this -> findProductAll(pid);

    if(change_product == nullptr){
        std :: cout << "Valid product not found. Returning." << std :: endl;
        return -1;
    }

    bool product_status = change_product->GetIsActive();

    int choice = -1;

    while(choice != -3){
        product_status = change_product->GetIsActive();
        std::cout << "Update Product "<< change_product -> GetProductName() << " status: " << std::endl;
            std::cout << "+=====Product Options=====+" << std::endl;
            if (product_status == true){
                std :: cout << "Product is currently still active for bidding." << std :: endl;
                std :: cout << "\t1. Show all bids and the highest current bid." << std :: endl;
                std :: cout << "\t2. Show product info." << std :: endl;
                std :: cout << "\t3. Close bidding and declare winner." << std :: endl;
                std :: cout << "\t4. Deactive product and cancel bidding." << std :: endl;
                std :: cout << "\t5. Return to previous menu." << std :: endl;
                std :: cout << "Please enter your choice number." << std :: endl;
                std :: cin >> choice;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                this -> ProductStatusChange(seller, change_product, choice);
            }

            else{
                std :: cout << "Product is currently inactive for bidding." << std :: endl;
                std :: cout << "\t1. Activate bidding." << std :: endl; //need to check if already has been sold / already has a final buyer
                std :: cout << "\t2. Show product info." << std :: endl;
                std :: cout << "\t3. Return to previous menu." << std :: endl;
                std :: cout << "Please enter your choice number." << std :: endl;
                std :: cin >> choice;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                this -> ProductStatusChange(seller, change_product, choice);
            }
            std::cout << "+========================+" << std::endl;
    }
    return choice;
}

/**
 * @brief Helper for product status change for seller. Handles cases such as finalizing a bid, and deactivating a product.
 * 
 * @param seller 
 * @param product 
 * @param choice 
 */
void Driver :: ProductStatusChange(Seller * seller, Product * product, int &choice){

    std :: pair <Buyer *, double> highestBid = std::make_pair(nullptr, 0);
    Buyer *highest_bidder = nullptr;
    double highest_amount = 0;

    std :: pair <Buyer *, double> highestBid3 = std::make_pair(nullptr, 0);
    Buyer *highest_bidder3 = nullptr;
    double highest_amount3 = 0;

    bool product_status = product -> GetIsActive();

    if ( product_status == true){

        switch(choice){
            case 1: 
                std :: cout << "All bids on the current active product:" << std :: endl;
                seller -> ListProductBids(product);
                highestBid = product -> maxPair();
                highest_bidder = highestBid.first;
                highest_amount = highestBid.second;

                std :: cout << "Highest bid made by " << highest_bidder->GetName() << " for amount: $" << highest_amount << std :: endl; 
                break;
            case 2:
                std :: cout << "Displaying product info: " << std :: endl;
                
                product -> ProductInfo();
                break;
            case 3: {
                //closing bid logic
                std :: cout << "Declaring bid closed and selling the product to highest bidder if bid appropriate." << std :: endl;
                highestBid3 = product -> maxPair();
                highest_bidder3 = highestBid3.first;
                highest_amount3 = highestBid3.second;

                //run in a loop until a valid pair is found to bid the product off to
                while(highest_bidder3!= nullptr && (highest_bidder3-> GetAccountBalance() < highest_amount3 || highest_bidder3->GetPhone() == seller->GetPhone())){
                    product->clearBid(highestBid3);
                    highestBid3 = product -> maxPair();
                    highest_bidder3 = highestBid3.first;
                    highest_amount3 = highestBid3.second;
                }

                //if none found, then reset the product and set to inactive
                if (highest_bidder3 == nullptr || highest_amount3 < product -> GetStartingPrice()){
                    std :: cout << "No proper bidder found. Clearing all bids and setting product inactive." << std :: endl;
                    product -> SetLatestBid(0);
                    product -> SetIsActive(false);
                    product -> clearMap();
                    return;
                }

                //handle setting ownership to the new buyer from the seller
                product -> SetFinalBuyer(highest_bidder3);
                product -> SetIsActive(false);
                highest_bidder3->AddProductToInventory(product);
                seller -> RemoveOwnedElement(product);

                this -> addNewBidToFile(product->GetProductName(), CategoryString(product->GetProdutCategory()), seller->GetName(),
                                        highest_bidder3->GetName(), product->GetStartingPrice(), highest_amount3); //writing bid to file

                // account balance handling                        
                highest_bidder3->SetAccountBalance(highest_bidder3->GetAccountBalance() - highest_amount3);
                seller -> SetAccountBalance(seller -> GetAccountBalance() + highest_amount3);
                std :: cout << "Product successfully sold!" << std :: endl;

                //MESSAGING TIME WOO!
                
                // After determining the highest bidder and completing the sale process...

                // Create a message body
                std::string messageBody1 = "Congratulations, you've won the bid for " + product->GetProductName() + ". Please contact us for the next steps.";

                // Using sendMessage to send a message from the seller to the buyer
                User::Message saleMessage1(seller->GetName(), highest_bidder3->GetName(), messageBody1);
                highest_bidder3->sendMessage(saleMessage1);


                // Create a message body
                std::string messageBody2 = "Congratulations, you've sold product " + product->GetProductName() + ". Please contact us for the next steps.";

                // Using sendMessage to send a message from the seller to the buyer
                User::Message saleMessage2(seller->GetName(), highest_bidder3->GetName(), messageBody2);
                seller->sendMessage(saleMessage2);

                std::cout << "A message has been sent to the buyer regarding the next steps." << std::endl;

                choice = -3;
                return;
                break;
            }
            case 4:
                //force deactive product and clear all bids
                product -> SetLatestBid(0);
                product -> SetIsActive(false);
                product -> clearMap();
                std :: cout << "Product has been deactivated and all bids have been cleared." << std :: endl;
                return;
                break;

            case 5:
                std :: cout << "Exiting the menu." << std :: endl;
                choice = -3;
                break;
            
            default:
                std :: cout << "No updates made. Terminating." << std :: endl; 
                break;
        }
    }

    else{
        switch(choice){
            case 1: 
                std :: cout << "Activating product if not sold." << std :: endl;
                if(product -> GetFinalBuyer() == nullptr){ //only activate if not owned by a buyer
                    product -> SetIsActive(true);
                }
                break;
            case 2:
                std :: cout << "Displaying product info: " << std :: endl;
                
                product -> ProductInfo();
                break;

            case 3:
                std :: cout << "Exiting the menu." << std :: endl;
                choice = -3;
                break;
            
            default:
                std :: cout << "No updates made. Terminating." << std :: endl; 
                break;
        }
    }

    
}
