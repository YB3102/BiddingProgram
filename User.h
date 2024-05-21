#ifndef USER_H_
#define USER_H_

#include "Product.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class User
{

public:
    struct Message
    {
        static int next_message_id_;
        int message_id_;
        std::string sender_name_;
        std::string recipient_name_;
        std::string message_body_;
        bool responded_ = false; // To track if the message has been responded to

        Message(const std::string &sender, const std::string &recipient, const std::string &messageBody) {
            message_id_ = next_message_id_;
            sender_name_ = sender;
            recipient_name_ = recipient;
            message_body_ = messageBody;
        }

        // Helpers
        std::string getPreview() const {
            std::istringstream iss(message_body_);
            std::string preview;
            std::string word;
            int wordCount = 0;
            while (iss >> word && wordCount < 2) {  // Change 2 to the number of words you want in the preview
                preview += word + " ";
                wordCount++;
            }
            return preview + "...";  // Add ellipsis to indicate it's a preview
        }

        friend std::ostream &operator<<(std::ostream &os, const Message &m)
        {
            std::string s = "";
            if(m.responded_){
                s = "YES";
            }
            else{
                s = "NO";
            }
            os << "----------------------------------" << std::endl;
            os << "Message Sent from: " << m.sender_name_ << std::endl;
            os << "To: " << m.recipient_name_ << std::endl;
            os << "Message:\t" << m.message_body_ << std::endl;
            os << "Responded To? :\t" << s << std::endl;
            os << "----------------------------------" << std::endl;

            return os;
        }
    };

    User();
    User(std ::string name, std ::string phone, std ::string address, double account_balance);

    // getters
    // int GetUserID() const { return user_id_; }
    std ::string GetName() const { return this->name_; }
    std ::string GetPhone() const { return this->phone_; }
    std ::string GetAddress() const { return this->address_; }
    double GetAccountBalance() const { return this->account_balance_; }
    // setters
    void SetName(std::string name) { this->name_ = name; }
    void SetPhone(std::string phone) { this->phone_ = phone; }
    void SetAddress(std::string address) { this->address_ = address; }
    void SetAccountBalance(double balance) { this->account_balance_ = balance; }

    // Methods
    void AddProductToInventory(Product * current_product); //adds a product
    void productOverview();
    std ::vector<Product *> GetMyProducts() { return this->owned_products_; }
    void updateUserInformation(User* user);

    // Messages
    void viewMessages(User * currUser);
    void respondToMessage(Message& message, User * user);
    void sendMessage(const Message& message);
    void updateMessageStatus(Message& message);
    

    /**
     * @brief Removes a product from ownership for a user. Used to finalize bids in program.
     * 
     * @param remove 
     */
    void RemoveOwnedElement(Product* remove) {
        this->owned_products_.erase(std::remove_if(this->owned_products_.begin(), this->owned_products_.end(), [&](Product* ptr) {
            return ptr == remove;
        }), this->owned_products_.end());
    }
    std::vector<Message *> getMessagesForUser() {return this->messages_;}


    friend std::ostream &operator<<(std::ostream &os, const User &u)
    {
        os << "--------------------------------" << std::endl;
        os << "Name:\t" << u.GetName() << std::endl;
        os << "Phone:\t" << u.GetPhone() << std::endl;
        os << "Address:\t" << u.GetAddress() << std::endl;
        os << "Account Balance ($):\t" << u.GetAccountBalance() << std::endl;
        os << "--------------------------------" << std::endl;

        return os;
    }

protected:
    // int user_id_; // needs testing
    // static int next_user_id_;
    std ::string name_;
    std ::string phone_;
    std ::string address_;
    double account_balance_;
    std::vector<Message *> messages_;
    std ::vector<Product *> owned_products_; //all owned products of a user
};

class Buyer : public User
{

public:
    Buyer(std::string name, std::string phone, std::string address, double balance) : User(name, phone, address, balance)
    {
    }

    void BidOnProduct(Product *bidded_product, double bid_amount);

    void ViewCurrentBids(); //views the users current product bids

    void ViewOwnedProducts(); //views the items that the user has won and owns

private:
    std ::vector<Product *> current_bidded_products_; //all products that the user has bidded on
};

class Seller : public User
{

public:
    Seller(std::string name, std::string phone, std::string address, double balance) : User(name, phone, address, balance)
    {
    }

    // Seller Product Management
    void createNewProduct(); //Allows user to create a new product to optionally sell
    void PutProductSale(Product *selected_product); // lists a product for sale
    void SetProductStatus(Product *selected_product, bool status); // changes open/close status of a product
    //void viewSimilarProductSalesHistory(Product *selected_product); //moving this to driver for universality

    // Seller Bidding
    void ListedProductsPrint();                      // lists/prints active products ?
    void ListProductBids(Product *selected_product); // lists all placed bids on a product
    void ListSoldProducts();

    // Helpers
    
    Product *findProduct(int product_id);

private:
    // std ::vector<Product *> seller_products_;
    std ::vector<Product *> products_on_sale_; //products listed on sale by the seller
};

#endif