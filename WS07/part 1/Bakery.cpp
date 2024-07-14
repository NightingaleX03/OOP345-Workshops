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
            type = (line.substr(0,8) == "BREAD") ? BakedType::BREAD : BakedType::PASTERY;
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
        //display the header
        os << "Type           Description            Shelf   Stock      Price\n";
        os << "****************************************************************\n";
        //display the goods
        for(const auto& good : m_goods){
            os << good << std::endl;
        }
    }

    //overload the << operator
    std::ostream& operator<<(std::ostream& os, const BakedGood& goods){
        os << std::setw(10) << std::left << (goods.type == BakedType::BREAD ? "BREAD" : "PASTERY") << " * " <<
        std::setw(20) << std::left << goods.description << " * " << 
        std::setw(5) << std::right << goods.shelfLife << " * " <<
        std::setw(5) <<std::right << goods.stock << " * " << 
        std::setw(5) << std::right << goods.price << " * ";

        return os;
    }
}