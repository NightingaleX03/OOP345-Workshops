/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/


#include "FoodOrder.h"

namespace seneca{

    // constructor to set customerName, description, price and daily special to default values
    FoodOrder::FoodOrder(){
        m_customerName[0] = '\0';
        m_orderDescription[0] = '\0';
        m_price = 0.0;
        m_dailySpecial = 'N';
    }

    void FoodOrder::read(std::istream& is){
        
    }
    void FoodOrder::display() const{

    }
}
