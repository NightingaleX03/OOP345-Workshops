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
        m_counter = 0;
        m_customerName[0] = '\0';
        m_orderDescription[0] = '\0';
        m_price = 0.0;
        m_dailySpecial = 'N';
    }

    std::istream& FoodOrder::read(std::istream& is){

        if(&is == &std::cin){ // if function is in good state it will read file
            m_counter++;
            is.getline(m_customerName, 11, ',');
            is.getline(m_orderDescription, 26, ',');
            is >> m_price;
            is.ignore();
            is >> m_dailySpecial;
            is.ignore();
        }

        return is; // return is object
    }

    void FoodOrder::display() const{

        if(m_customerName[0] == '\0'){ // if customer name is not available there was no order placed
            std::cout << "COUNTER. No Order" << std::endl;
        }
        
        else{
            std::cout << std::left << std::setw(2) << "COUNTER. " 
                << std::left << std::setw(10) << m_customerName << " | " // display customer name
                << std::left << std::setw(25) << m_orderDescription << " | " // display order description
                << std::left << std::setw(12) << "$" << std::setprecision(2) << m_price * (1 + g_taxrate); // display price with tax

            if (m_dailySpecial == 'Y') { // if daily special is ordered apply discount
                std::cout << "$" << std::right << std::setw(12) << std::setprecision(2) << m_price * (1 + g_taxrate) * (1 - g_dailydiscount) << std::endl; // price displayed with discount
            } 
        }
    } // end of display function
}
