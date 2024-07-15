/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Bakery.h"

namespace seneca{

    //constructor
    Bakery::Bakery(const char* filename){
        std::ifstream file(filename);
        //check if file is open
        if(!file){
            throw std::runtime_error("Unable to open file");
        
        }

        std::string line;
        
        //read file line by line
        while(std::getline(file, line)){
            BakedType type;
            //check if the line is bread or pastery
            std::string sub = line.substr(0,8);
            sub.erase(sub.find_last_not_of(" \n\r\t")+1);
            sub.erase(0, sub.find_first_not_of(" \n\r\t"));

            type =  (sub == "Bread") ? BakedType::BREAD : BakedType::PASTERY;
            //get the description, shelf life, stock and price
            std::string description = line.substr(8, 20);
            int shelfLife = std::stoi(line.substr(28, 14));
            int stock = std::stoi(line.substr(42, 8));
            double price = std::stod(line.substr(50, 6));

            //trim the description
            description.erase(description.find_last_not_of(" \n\r\t")+1);
            description.erase(0, description.find_first_not_of(" \n\r\t"));

            //create a BakedGood object and push it into the vector
            BakedGood good{type, description, shelfLife, stock, price};
            m_goods.push_back(good);
        }
        
    }

    //display the goods
    void Bakery::showGoods(std::ostream& os) const{
        double total = 0.0;
        int totalStock = 0;

        //display the goods
        std::for_each(m_goods.begin(), m_goods.end(), [&os, &total, &totalStock](const BakedGood& good){
            os << good << std::endl;
            total += good.price;
            totalStock += good.stock;
        });

        os << "Total Stock: " << totalStock << "\n";
        os << "Total Price: " << std::fixed << std::setprecision(2) << total << "\n";
    }

    //overload the << operator
    std::ostream& operator<<(std::ostream& os, const BakedGood& goods){
        os << "* " << std::setw(10) << std::left << (goods.type == BakedType::BREAD ? "Bread" : "Pastry") << " * " <<
        std::setw(20) << std::left << goods.description << " * " << 
        std::setw(5) << std::left << goods.shelfLife << " * " <<
        std::setw(5) <<std::left << goods.stock << " * " << 
        std::setw(8) << std::right << std::fixed << std::setprecision(2) << goods.price << " * ";

        return os;
    }

    //sort the bakery
    void Bakery::sortBakery(const std::string& order){
        //sort the bakery based on the description
        if(order == "Description"){
            std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b){
                return a.description < b.description;
            });
        }
        //sort the bakery based on the price
        else if(order == "Price"){
            std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b){
                return a.price < b.price;
            });
        }
        //sort the bakery based on the shelf life
        else if(order == "Shelf"){
            std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b){
                return a.shelfLife < b.shelfLife;
            });
        }
        //sort the bakery based on the stock
        else if(order == "Stock"){
            std::sort(m_goods.begin(), m_goods.end(), [](const BakedGood& a, const BakedGood& b){
                return a.stock < b.stock;
            });
        }
    }

    //combine two bakeries
    std::vector<BakedGood>  Bakery::combine(const Bakery& other){
        std::vector<BakedGood> goods = m_goods;
        std::vector<BakedGood> otherGoods = other.m_goods;

        //sort the goods based on the price seperately
        std::sort(otherGoods.begin(), otherGoods.end(), [](const BakedGood& a, const BakedGood& b){
            return a.price < b.price;
        });

        //sort the goods based on the price seperately
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b){
            return a.price < b.price;
        });

        //create a vector to store the combined goods
        std::vector<BakedGood> combined; 
        combined.reserve(goods.size() + otherGoods.size());

        //merge the two vectors
        std::merge(goods.begin(), goods.end(), otherGoods.begin(), otherGoods.end(), std::back_inserter(combined), [](const BakedGood& a, const BakedGood& b){
            return a.price < b.price;
        });
       
        return combined;
    }

    //check if a good is in stock
    bool  Bakery::inStock(const std::string& desc, BakedType type) const{
        //find the good
        auto it = std::find_if(m_goods.begin(), m_goods.end(), [&desc, &type](const BakedGood& good){
            return good.description == desc && good.type == type;
        });

        //return true if the good is in stock
        return it != m_goods.end();
    }

    //return a list of out of stock goods
    std::list<BakedGood>  Bakery::outOfStock(BakedType type) const{
        std::list<BakedGood> outOfStock;
        //copy the out of stock goods to the list
        std::copy_if(m_goods.begin(), m_goods.end(), std::back_inserter(outOfStock), [&type](const BakedGood& good){
            return good.type == type && good.stock == 0;
        });

        //sort the list based on the description
        outOfStock.sort([](const BakedGood& a, const BakedGood& b){
            return a.price < b.price;
        });

        return outOfStock;
    }
}