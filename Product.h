#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <limits>
// #include "User.h"

// class User;
class Seller;
class Buyer;

enum class ProductCategory
{
    Electronics,
    Vehicle,
    Furniture,
    Clothing,
    Media,
    defaultval
};

enum class ProductQuality
{
    New,
    Used_VeryGood,
    Used_good,
    Used_okay,
    defaultquality
};

/*define product_ids for various products {
    1 computers, 2 mobiles, 3 peripherals,
    4 cars, 5 motorcycle, 6 heavy,
    7 chairs, 8 tables, 9 decor,
    10 movies, 11 games, 12 books
}
*/

class Product
{

public:
    Product(std ::string product_name, ProductCategory product_category,
            bool isActive, ProductQuality product_quality, double starting_price)
    {
        this->product_id_ = ++this->current_product_; //static product id 
        this->product_category_ = product_category;
        this->product_quality_ = product_quality;
        this->product_name_ = product_name;
        // this -> seller_ = seller;
        this->isActive_ = isActive; //active flag in system
        this->starting_price_ = starting_price; //initial price of product
    }

    Product()
    {
        this->product_id_ = ++this->current_product_;
        this->product_category_ = ProductCategory ::defaultval;
        this->product_quality_ = ProductQuality ::defaultquality;
        this->product_name_ = "";
        this->seller_ = NULL;
        this->isActive_ = false;
        this->starting_price_ = -1;
    };

    // getters

    bool GetIsActive() const{ return this->isActive_; }

    ProductCategory GetProdutCategory() const{ return this->product_category_; }

    ProductQuality GetProductQuality() const{ return this->product_quality_; }

    std ::map<Buyer *, double> GetBidMap() const{ return this->biddersvaluepair_; }

    std ::string GetProductName() const{ return this->product_name_; }

    int GetProductID() const{ return this->product_id_; }

    Seller *GetProductSeller() const{ return this->seller_; }

    Buyer *GetFinalBuyer() const{ return this->final_buyer_; }

    double GetLatestBid() const{ return this->latest_bid_; }

    double GetStartingPrice() const{ return this->starting_price_; }

    // not implementing setters for part 2 yet

    // setters, some of these might not be used

    void SetLatestBid(double latest_bid) { this->latest_bid_ = latest_bid; }

    void SetStartingPrice(double starting_price) { this->starting_price_ = starting_price; }

    void SetFinalBuyer(Buyer *final_buyer) { this->final_buyer_ = final_buyer; }

    void SetIsActive(bool isActive) { this->isActive_ = isActive; }

    void SetProdutCategory(ProductCategory pc) { this->product_category_ = pc; }

    void SetProductQuality(ProductQuality pq) { this->product_quality_ = pq; }

    void SetBidMap(std ::map<Buyer *, double> map) { this->biddersvaluepair_ = map; } // this one may not be used depending on how program is handled

    void SetProductName(std ::string product_name) { this->product_name_ = product_name; }

    void SetProductID(int product_id) { this->product_id_ = product_id; }

    void SetProductSeller(Seller *product_seller) { this->seller_ = product_seller; }

    // getters and setters end

    void AddProductBid(Buyer *buyer, double bid_amount);
    /*{
        this->biddersvaluepair_.insert(std::pair<Buyer *, double>(buyer, bid_amount));
    }*/

    std :: pair<Buyer*, double> maxPair();

    /**
     * @brief Removes a bid from the bidmap
     * 
     * @param bid the bid to be removed
     */
    void clearBid(std :: pair<Buyer*, double> bid){
        auto it = this->biddersvaluepair_.find(bid.first); // Find the buyer pointer in the map
        if (it != this->biddersvaluepair_.end() && it->second == bid.second) {
            // If the buyer pointer is found and the associated value matches the given value
            this->biddersvaluepair_.erase(it); // Remove the element from the map
        }
    }

    void clearMap() {this->biddersvaluepair_.clear();}

    virtual void ProductInfo() const; // write in cpp

    void bidActive() { this->isActive_ = true; } //i actually forgot to use these 2

    void bidClose() { this->isActive_ = false; }

    // sell product to buyer in driver, handle logic there
    // will need to check for buyer balance on sell time even if bid is placed before

    // Product * ProductFactory(std::string product_name, ProductCategory pc, int product_id, Seller* seller, bool isActive);

    friend std::ostream &operator<<(std::ostream &os, const Product &product); //overloaded output stream operator

protected:
    std ::string product_name_;

    ProductCategory product_category_;

    ProductQuality product_quality_;

    Seller *seller_ = NULL;

    Buyer *final_buyer_ = NULL;

    int product_id_;

    static int current_product_;

    bool isActive_ = false; // close/open bool

    std ::map<Buyer *, double> biddersvaluepair_; // bidders, bid value pair

    double latest_bid_ = 0;

    double starting_price_ = 0;
}; // Define the static member variable

// Subclasses for product factory

class Electronics : public Product
{

public:
    Electronics(std::string product_name, bool isActive, ProductQuality pq, double starting_price)
        : Product(product_name, ProductCategory::Electronics, isActive, pq, starting_price) {}

    void SetMemorySize(int memory_size) { this->memory_size_ = memory_size; }

    void SetStorageSize(int storage_size) { this->storage_size_ = storage_size; }

    void SetProcessorName(std ::string processor_name) { this->processor_name_ = processor_name; }

    int GetMemorySize() { return this->memory_size_; }

    int GetStorageSize() { return this->storage_size_; }

    std ::string GetProcessorName() { return this->processor_name_; }

    void ProductInfo() const override;

protected:
    int memory_size_ = 8;
    int storage_size_ = 128;
    std ::string processor_name_ = "Generic";
};

class Furniture : public Product
{

public:
    Furniture(std::string product_name, bool isActive, ProductQuality pq, double starting_price)
        : Product(product_name, ProductCategory::Furniture, isActive, pq, starting_price) {}

    void SetMaterial(std ::string material)
    {
        this->material_ = material;
    }

    void SetLuxuryRating(int luxury)
    {
        this->luxury_rating_ = luxury;
    }

    std ::string GetMaterial()
    {
        return this->material_;
    }

    int GetLuxuryRating()
    {
        return this->luxury_rating_;
    }

    void ProductInfo() const override;

protected:
    std ::string material_ = "Generic";
    int luxury_rating_ = 3;
};

class Vehicle : public Product
{

public:
    Vehicle(std::string product_name, bool isActive, ProductQuality pq, double starting_price)
        : Product(product_name, ProductCategory::Vehicle, isActive, pq, starting_price) {}

    void SetVehicleType(std ::string vehicle_type)
    {
        this->vehicle_type_ = vehicle_type;
    }

    void SetModelYear(int model_year)
    {
        this->model_year_ = model_year;
    }

    std ::string GetVehicleType()
    {
        return this->vehicle_type_;
    }

    int GetModelYear()
    {
        return this->model_year_;
    }

    void ProductInfo() const override;

protected:
    std ::string vehicle_type_ = "Vehicle";
    int model_year_ = 2000;
};

class Clothing : public Product
{

public:
    Clothing(std::string product_name, bool isActive, ProductQuality pq, double starting_price)
        : Product(product_name, ProductCategory::Clothing, isActive, pq, starting_price) {}

    void SetFabric(std ::string fabric)
    {
        this->fabric_ = fabric;
    }

    void SetSize(std ::string size)
    {
        this->size_ = size;
    }

    std ::string GetFabric()
    {
        return this->fabric_;
    }

    std ::string GetSize()
    {
        return this->size_;
    }

    void ProductInfo() const override;

protected:
    std ::string fabric_ = "Generic";
    std ::string size_ = "Generic";
};

class Media : public Product
{

public:
    Media(std::string product_name, bool isActive, ProductQuality pq, double starting_price)
        : Product(product_name, ProductCategory::Media, isActive, pq, starting_price) {}

    void SetMediaType(std ::string media_type)
    {
        this->media_type_ = media_type;
    }

    void SetAgeRating(std ::string age_rating)
    {
        this->age_rating_ = age_rating;
    }

    std ::string GetMediaType()
    {
        return this->media_type_;
    }

    std ::string GetAgeRating()
    {
        return this->age_rating_;
    }

    void ProductInfo() const override;

protected:
    std ::string media_type_ = "Generic";
    std ::string age_rating_ = "All";
};

// product factory implement

/**
 * @brief Converts product quality enum member to string equivalent
 * 
 * @param pq 
 * @return std 
 */
inline std ::string QualityString(ProductQuality pq)
{
    switch (pq)
    {
    case ProductQuality ::Used_good:
        return "Used and good";
    case ProductQuality ::New:
        return "New";
    case ProductQuality ::Used_okay:
        return "Used and okay";
    case ProductQuality ::Used_VeryGood:
        return "Used and very good";
    default:
        return "Placeholder default.";
    }
}

/**
 * @brief Converts product category enum member to string equivalent
 * 
 * @param pc 
 * @return std 
 */
inline std ::string CategoryString(ProductCategory pc)
{
    switch (pc)
    {
    case ProductCategory::Electronics:
        return "Electronics";
    case ProductCategory::Furniture:
        return "Furniture";
    case ProductCategory::Media:
        return "Media";
    case ProductCategory::Vehicle:
        return "Vehicle";
    case ProductCategory::Clothing:
        return "Clothing";
    default:
        return "Default placeholder.";
    }
}

/**
 * @brief Converts passed string to product category enum equivalent
 * 
 * @param pc 
 * @return ProductCategory 
 */
inline ProductCategory StringtoCategory(std ::string pc)
{
    if (pc == "Electronics")
    {
        return ProductCategory ::Electronics;
    }
    else if (pc == "Clothing")
    {
        return ProductCategory ::Clothing;
    }
    else if (pc == "Media")
    {
        return ProductCategory ::Media;
    }
    else if (pc == "Vehicle")
    {
        return ProductCategory ::Vehicle;
    }
    else if (pc == "Furniture")
    {
        return ProductCategory ::Furniture;
    }
    else
    {
        return ProductCategory ::defaultval;
    }
}

/**
 * @brief Converts passed string to product quality enum equivalent
 * 
 * @param pq 
 * @return ProductQuality 
 */
inline ProductQuality StringtoQuality(std ::string pq)
{
    if (pq == "New")
    {
        return ProductQuality ::New;
    }
    else if (pq == "Used and okay")
    {
        return ProductQuality ::Used_okay;
    }
    else if (pq == "Used and good")
    {
        return ProductQuality ::Used_good;
    }
    else if (pq == "Used and very good")
    {
        return ProductQuality ::Used_VeryGood;
    }
    else
    {
        return ProductQuality::defaultquality;
    }
}

// only takes productcategory. would have to assign seller using setseller in driver
// prompt the user for the rest during product creation
// assume all input will be valid
/**
 * @brief Product Factory that takes in a category. Asks the user for some inputs.
 *          Returns the subclass product of Product class customized to user specifications.
 * 
 * @param pc 
 * @return Product* 
 */
inline Product *ProductFactory(ProductCategory pc)
{
    std::string name;
    ProductQuality pq;
    std::string quality;
    bool active_status = false;
    std::string active_input;
    double base_price;

    std::cout << "Enter the name of the product: ";
    std::getline(std::cin, name); // Use getline to allow spaces
    std::cout << "+============================+" << std::endl;

    std::cout << "Enter the quality of the product from the following options: New, Used and okay, Used and good, Used and very good" << std::endl;
    std::getline(std::cin, quality);
    pq = StringtoQuality(quality); // Ensure this function gracefully handles invalid inputs
    std::cout << "+============================+" << std::endl;

    std::cout << "Activate the product for bidding on listing time? (Yes/No): ";
    std::getline(std::cin, active_input);
    active_status = (active_input == "Yes" || active_input == "yes");
    std::cout << "+============================+" << std::endl;

    std::cout << "Enter the base starting price for your product: ";
    std::cin >> base_price;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer after reading a numeric value
    std::cout << "+============================+" << std::endl;

    switch (pc)
    {
    case ProductCategory::Electronics:
    {
        int memory, storage;
        std::string processor_name;

        std::cout << "Enter memory size: ";
        std::cin >> memory;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter storage size: ";
        std::cin >> storage;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter processor name: ";
        std::getline(std::cin, processor_name);

        auto factory_electronic = new Electronics(name, active_status, pq, base_price);
        factory_electronic->SetMemorySize(memory);
        factory_electronic->SetStorageSize(storage);
        factory_electronic->SetProcessorName(processor_name);

        return factory_electronic;
    }
    case ProductCategory::Clothing:
    {
        std::string size, fabric;

        std::cout << "Enter clothing size (S, M, L, XL, etc.): ";
        std::getline(std::cin, size);

        std::cout << "Enter fabric type (cotton, polyester, etc.): ";
        std::getline(std::cin, fabric);

        auto factory_clothing = new Clothing(name, active_status, pq, base_price);
        factory_clothing->SetSize(size);
        factory_clothing->SetFabric(fabric);

        return factory_clothing;
    }

    case ProductCategory::Vehicle:
    {
        std::string vehicle_type;
        int model_year;

        std::cout << "Enter vehicle type (car, motorcycle, etc.): ";
        std::getline(std::cin, vehicle_type);

        std::cout << "Enter model year: ";
        std::cin >> model_year;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto factory_vehicle = new Vehicle(name, active_status, pq, base_price);
        factory_vehicle->SetVehicleType(vehicle_type);
        factory_vehicle->SetModelYear(model_year);

        return factory_vehicle;
    }

    case ProductCategory::Media:
    {
        std::string media_type, age_rating;

        std::cout << "Enter media type (Book, CD, Video Game, etc.): ";
        std::getline(std::cin, media_type);

        std::cout << "Enter age rating (All ages, Teen, Mature, etc.): ";
        std::getline(std::cin, age_rating);

        auto factory_media = new Media(name, active_status, pq, base_price);
        factory_media->SetMediaType(media_type);
        factory_media->SetAgeRating(age_rating);

        return factory_media;
    }

    case ProductCategory::Furniture:
    {
        std::string material;
        int luxury_rating;

        std::cout << "Enter furniture material (wood, metal, etc.): ";
        std::getline(std::cin, material);

        std::cout << "Enter luxury rating (1-10): ";
        std::cin >> luxury_rating;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto factory_furniture = new Furniture(name, active_status, pq, base_price);
        factory_furniture->SetMaterial(material);
        factory_furniture->SetLuxuryRating(luxury_rating);

        return factory_furniture;
    }
    default:
        std::cout << "Invalid Product Category." << std::endl;
        return nullptr;
    }
}


#endif