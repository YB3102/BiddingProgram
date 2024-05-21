#include "Product.h"
#include "User.h"

int Product :: current_product_ = 0; //static id starting from 1 for all products


/**
 * @brief Adds a pair product bid to the product bid map.
 * 
 * @param buyer 
 * @param bid_amount 
 */
void Product :: AddProductBid(Buyer * buyer, double bid_amount){

    if (buyer -> GetAccountBalance() >= bid_amount && this->isActive_ == true && buyer != NULL){
        this->biddersvaluepair_.insert(std::pair<Buyer *, double>(buyer, bid_amount));
    }

    else{
        std :: cout << "Balance insufficient or bidding closed." << std :: endl;
    }
}

/**
 * @brief Returns the pair of highest bid amount from the bid map.
 * 
 * @return std::pair<Buyer *, double> 
 */
std::pair<Buyer *, double> Product :: maxPair(){
    std::pair<Buyer *, double> entryWithMaxValue 
        = std::make_pair(nullptr, 0); 
 
    std::map<Buyer *, double>::iterator currentEntry; 
    for (currentEntry = this->biddersvaluepair_.begin(); 
        currentEntry != this->biddersvaluepair_.end(); 
        ++currentEntry) { 
 
        // If this entry's value is more 
        // than the max value 
        // Set this entry as the max 
        if (currentEntry->second 
            > entryWithMaxValue.second) { 
 
            entryWithMaxValue 
                = std::make_pair( 
                    currentEntry->first, 
                    currentEntry->second); 
        } 
    } 
 
    return entryWithMaxValue; 
}

/**
 * @brief Prints the product info of a product. Virtual function to enable overloading for subclasses.
 * 
 */
void Product :: ProductInfo() const{

    std :: cout << "Product ID: " << this -> product_id_ << std :: endl;
    std :: cout << "Product Name: " << this -> product_name_ << std :: endl;
    std :: cout << "Product Category: " << CategoryString(this->product_category_) << std :: endl;
    std :: cout << "Product Quality: " << QualityString(this -> product_quality_) << std :: endl;
    std :: cout << "Product Seller name: " << this -> seller_ ->GetName() << std :: endl;

    if(this->final_buyer_ != NULL){
        std :: cout << "Product Buyer name: " << this -> final_buyer_ -> GetName() << std :: endl;
    }

    if(isActive_ == false){
        std :: cout << "Product is not active for bids currently." << std :: endl;
    }
    else{
        std :: cout << "Product is accepting bids." << std :: endl;
    }

    std :: cout << "Latest bid price: $ " << this -> latest_bid_ << std :: endl;

    std :: cout << "Starting price: $" << this -> starting_price_ << std :: endl;
    
}

void Electronics :: ProductInfo() const {
    Product :: ProductInfo();

    std :: cout << "Memory Size: " << this -> memory_size_ << std :: endl;
    std :: cout << "Storage Size: " << this -> storage_size_ << std :: endl;
    std :: cout<< "Processor: " << this -> processor_name_ << std :: endl;
}

void Furniture :: ProductInfo() const {
    Product :: ProductInfo();

    std :: cout << "Material: " << this -> material_ << std :: endl;
    std :: cout << "Luxury rating: " << this -> luxury_rating_ << std :: endl;
}

void Clothing :: ProductInfo() const {
    Product :: ProductInfo();

    std :: cout << "Fabric material: " << this -> fabric_ << std :: endl;
    std :: cout << "Clothing Size: " << this -> size_ << std :: endl;
}

void Vehicle :: ProductInfo() const {
    Product :: ProductInfo();

    std :: cout << "Vehicle type: " << this -> vehicle_type_ << std :: endl;
    std :: cout << "Model year: " << this -> model_year_ << std :: endl;
}

void Media :: ProductInfo() const {
    Product :: ProductInfo();

    std :: cout << "Media type: " << this -> media_type_ << std :: endl;
    std :: cout << "Age rating: " << this -> age_rating_ << std :: endl;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << "Product ID: " << product.product_id_ << "\n"
       << "Name: " << product.product_name_ << "\n"
       << "Category: " << CategoryString(product.product_category_) << "\n"
       << "Quality: " << QualityString(product.product_quality_) << "\n"
       << "Active: " << (product.isActive_ ? "Yes" : "No") << "\n"
       << "Starting Price: $" << product.starting_price_;

    // Include any additional details relevant for the product (product type)

    return os; // Return the ostream object to allow chaining
}