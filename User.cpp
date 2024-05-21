#include "User.h"
#include "Product.h"
#include <limits>
#include <algorithm>

// int User::next_user_id_ = 0;

User::User()
{
    // this->user_id_ = next_user_id_++;
    this->name_ = "New Default User";
    this->phone_ = "1-800-588-2305";
    this->address_ = "Middle Earth";
    this->account_balance_ = 1000;
}

User::User(std ::string name, std ::string phone, std ::string address, double account_balance)
{
    // this->user_id_ = next_user_id_++;
    this->name_ = name;
    this->phone_ = phone;
    this->address_ = address;
    this->account_balance_ = account_balance;
}

void User::updateUserInformation(User *user)
{
    if (user == nullptr)
    {
        std::cerr << "Error: User pointer is null." << std::endl;
        return;
    }

    // Print current user details
    std::cout << "Current User Details:" << std::endl;
    std::cout << *user << std::endl; // Utilizing the overloaded operator<< for User

    bool running = true;
    while (running)
    {
        std::cout << "+======Update User Information======+" << std::endl;
        std::cout << "1. Update Name" << std::endl;
        std::cout << "2. Update Phone Number" << std::endl;
        std::cout << "3. Update Address" << std::endl;
        std::cout << "4. Exit Update Menu" << std::endl;
        std::cout << "+==================================+" << std::endl;

        std::cout << "Choose an option to update: ";
        int choice;
        std::cin >> choice;

        // Clearing input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string input;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new name: ";
            std::getline(std::cin, input);
            user->SetName(input);
            std::cout << "Name updated successfully." << std::endl;
            break;
        case 2:
            std::cout << "Enter new phone number: ";
            std::getline(std::cin, input);
            user->SetPhone(input);
            std::cout << "Phone number updated successfully." << std::endl;
            break;
        case 3:
            std::cout << "Enter new address: ";
            std::getline(std::cin, input);
            user->SetAddress(input);
            std::cout << "Address updated successfully." << std::endl;
            break;
        case 4:
            running = false;
            std::cout << "Exiting Update Menu." << std::endl;
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
}

void User::productOverview()
{
    std::cout << "+========YOUR LIST OF PRODUCTS========+" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std :: cout << "Currently owned products:" << std :: endl;
    for (Product *p : this->owned_products_)
    { // Assuming GetSellerProducts() returns a vector of Product pointers
        if (p != nullptr)
        {                                                                 // Check if the product pointer is not null
            if (p -> GetFinalBuyer() == NULL){
                std::cout << *p << std::endl;                                 
                std::cout << "--------------------------------" << std::endl; 
            }
        }
    }
    std::cout << "+=====================================+" << std::endl;
}


// Buyer User Methods

void Buyer::BidOnProduct(Product *bidded_product, double bid_amount)
{

    bidded_product->AddProductBid(this, bid_amount);
    this->current_bidded_products_.push_back(bidded_product);
}

void Buyer ::ViewCurrentBids()
{
    for (auto it = this->current_bidded_products_.begin(); it != this->current_bidded_products_.end(); ++it)
    {
        if ((*it)->GetIsActive() == true && (*it)->GetFinalBuyer() == NULL)
        {
            std ::cout << "Buyer " << this->GetName() << " placed an active bid on " << (*it)->GetProductName() << " for amount: $" << (*it)->GetBidMap()[this] << std ::endl;
        }
    }
}

void Buyer ::ViewOwnedProducts()
{
    for (auto it = this->current_bidded_products_.begin(); it != this->current_bidded_products_.end(); ++it)
    {
        if ((*it)->GetIsActive() == false && (*it)->GetFinalBuyer() == this)
        {
            std ::cout << "Buyer " << this->GetName() << " owns the product " << (*it)->GetProductName() << " for amount: $" << (*it)->GetBidMap()[this] << std ::endl;
        }
    }
}

// Seller User Methods

void Seller::createNewProduct()
{
    std::cout << "+=====Create New Product=====+" << std::endl;
    std::cout << "\t1. Electronics" << std::endl;
    std::cout << "\t2. Vehicle" << std::endl;
    std::cout << "\t3. Furniture" << std::endl;
    std::cout << "\t4. Clothing" << std::endl;
    std::cout << "\t5. Media" << std::endl;
    std::cout << "\t6. Other" << std::endl;
    std::cout << "\t7. Exit" << std::endl;
    std::cout << "+============================+" << std::endl;

    std::cout << "Select Product Category: ";
    int choice;
    std::cin >> choice;

    // Clearing input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ProductCategory category;
    switch (choice)
    {
    case 1:
        category = ProductCategory::Electronics;
        break;
    case 2:
        category = ProductCategory::Vehicle;
        break;
    case 3:
        category = ProductCategory::Furniture;
        break;
    case 4:
        category = ProductCategory::Clothing;
        break;
    case 5:
        category = ProductCategory::Media;
        break;
    case 6:
        category = ProductCategory::defaultval;
        break;
    case 7:
        return;
    default:
        std::cout << "Invalid Option. Please try again." << std::endl;
        return;
    }

    // Create a new product using the factory function
    Product *newProduct = ProductFactory(category);

    if (newProduct != nullptr)
    {
        // Add the new product to the seller's inventory
        AddProductToInventory(newProduct);
        newProduct -> SetProductSeller(this);
        std::cout << "Product added to your inventory." << std::endl;

        if(newProduct -> GetIsActive() == true){
            this->PutProductSale(newProduct);
            std::cout << "Product put on sale." << std::endl;
        }
    }
}

void Seller::PutProductSale(Product *current_product)
{
    this->products_on_sale_.push_back(current_product);
}

void User ::AddProductToInventory(Product *current_product)
{
    this->owned_products_.push_back(current_product);
}

void Seller::SetProductStatus(Product *current_product, bool isActive)
{
    current_product->SetIsActive(isActive);
}

/*void Seller::viewSimilarProductSalesHistory(Product *selected_product)
{
    // TO-DO
}*/

void Seller :: ListSoldProducts(){
    std :: cout << "Listing sold products:" << std :: endl;
    for (auto it = this->products_on_sale_.begin(); it != this->products_on_sale_.end(); ++it)
    {

        if ((*it)->GetIsActive() == false && (*it)->GetFinalBuyer() != nullptr)
        {
            (*it)->ProductInfo();
        }
        std ::cout << std ::endl;
    }
}

void Seller ::ListedProductsPrint()
{
    //std ::cout << "Listing active seller products: " << std ::endl;
    for (auto it = this->products_on_sale_.begin(); it != this->products_on_sale_.end(); ++it)
    {

        if ((*it)->GetIsActive() == true)
        {
            (*it)->ProductInfo();
        }
        std ::cout << std ::endl;
    }
}

void Seller::ListProductBids(Product *selected_product)
{
    std ::map<Buyer *, double> product_bids = selected_product->GetBidMap();

    int count = 1;

    for (auto it = product_bids.begin(); it != product_bids.end(); ++it)
    {
        Buyer *buyer = it->first;
        double bid_amount = it->second;

        std ::cout << "Bid " << count << " placed by " << buyer->GetName() << ": " << bid_amount << std ::endl;

        count = count + 1;
    }
}



Product *Seller::findProduct(int product_id)
{
    for (Product *product : this->products_on_sale_)
    { // Assuming seller_products_ holds pointers to Product objects
        if (product->GetProductID() == product_id)
        {
            return product;
        }
    }
    return nullptr; // If no product is found with the given name
}

// Messages
int User::Message::next_message_id_ = 0;

void User::viewMessages(User* currUser) {
    // Print Messages
    std::vector<Message*> messages = getMessagesForUser();
    std::cout << "+=========Message Inbox=========+" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    for (size_t i = 0; i < messages.size(); ++i) {
        std::cout << "Message " << i + 1 << ": ";
        std::cout << messages.at(i)->getPreview() << std::endl;  // Use getPreview for message preview
        std::cout << "---------------------------------" << std::endl;
    }
    std::cout << "+=====================x=========+" << std::endl;

    // User input: Respond to a select message or close
    std::cout << "\nSelect a message to respond to or enter 0 to exit: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice > 0 && choice <= messages.size()) {
        respondToMessage(*messages[choice - 1], currUser);
    }
}

void User::respondToMessage(Message& message, User * currUser){
    std::cout << "Responding to message from " << message.sender_name_ << ":\n"
              << message.message_body_ << "\n\n"
              << "Type your response:\n";

    std::string response;
    std::getline(std::cin, response);

    // Create and send a new message as a response
    std::string name = currUser->GetName();
    Message responseMessage(name, message.sender_name_, response);
    sendMessage(responseMessage);

    // Mark the original message as responded
    message.responded_ = true;
    updateMessageStatus(message);
}

void User::sendMessage(const Message& message) {
    Message* newMessage = new Message(message.sender_name_, message.recipient_name_, message.message_body_);
    newMessage->responded_ = message.responded_; 
    this->messages_.push_back(newMessage);
    std::cout << "Message sent successfully.\n";
}

void User::updateMessageStatus(Message& message) {
    for (auto& msg : messages_) {
        if (msg->message_id_ == message.message_id_) { 
            msg->responded_ = message.responded_;
            std::cout << "Message status updated.\n";
            break;
        }
    }
}