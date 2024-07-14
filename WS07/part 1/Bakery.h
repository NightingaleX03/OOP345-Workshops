/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

namespace seneca{

    enum class BakedType{
        BREAD,PASTERY
    };

    struct BakedGood{
        BakedType type;
        std::string description;
        int shelfLife;
        int stock;
        double price;
    };

    class Bakery{
        std::vector<BakedGood> m_goods;
        std::string m_filename;

        public:
            Bakery(const char* filename);
            void showGoods(std::ostream& os) const;
    };
    
    std::ostream& operator<<(std::ostream& os, const BakedGood& goods);
}

#endif