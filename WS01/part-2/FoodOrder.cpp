/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/


#include "FoodOrder.h"

// initalizing global variables
double g_taxrate = 0.0;
double g_dailydiscount = 0.0;

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

        if(is.good()){ // if function is in good state it will read file
            char orderType;
            is >> orderType; // take order type
            is.ignore(); // ignore comma

            m_counter++;
            is.getline(m_customerName, 10, ',');
            is.getline(m_orderDescription, 25, ',');
            is >> m_price;
            is.ignore();
            is >> m_dailySpecial;
            is.ignore();
        }

        return is; // return is object
    }

    void FoodOrder::display() const{
        static int counter = 1; // static counter to keep track of number of orders
        if(m_customerName[0] == '\0'){ // if customer name is not available there was no order placed
            std::cout << counter + " . No Order" << std::endl;
        }
        
        else{
            std::cout << counter << ". " 
                << std::left << std::setw(10) << m_customerName << "|" // display customer name
                << std::left << std::setw(25) << m_orderDescription << "|" // display order description
                << std::left << std::setw(12) << std::fixed << std::setprecision(2) << m_price * (1 + g_taxrate); // display price with tax

            if (m_dailySpecial == 'Y') { // if daily special is ordered apply discount
                std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(2) << m_price * (1 + g_taxrate) * (1 - g_dailydiscount); // price displayed with discount
            } 

            std::cout << std::endl;
        }

        counter++; // increment counter
    } // end of display function
}