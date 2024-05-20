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
        m_orderDescription = nullptr; // set to null
        m_price = 0.0;
        m_dailySpecial = 'N';
    }

    // destructor 
    FoodOrder::~FoodOrder(){
        delete[] m_orderDescription; // deallocate memory
        m_orderDescription = nullptr; // set to null
    } 

    // copy constructor
    FoodOrder::FoodOrder(const FoodOrder& other): m_price(other.m_price), m_dailySpecial(other.m_dailySpecial){ // use constructor to fill info
        strcpy(m_customerName, other.m_customerName); // copy customer name

            // allocating description memory
            if (other.m_orderDescription != nullptr) {
                m_orderDescription = new char[strlen(other.m_orderDescription) + 1];
                strcpy(m_orderDescription, other.m_orderDescription); // copy description
            }
    }

    // copy assignment operator
    FoodOrder& FoodOrder::operator=(const FoodOrder& other){
        if(this != &other){ 

            // deallocate memory
            if (m_orderDescription != nullptr) {
                delete[] m_orderDescription; 
                m_orderDescription = nullptr; // set to null
            }

            // other values entered into object
            strcpy(m_customerName, other.m_customerName);
            m_price = other.m_price;
            m_dailySpecial = other.m_dailySpecial;

            // allocating description memory
            if (other.m_orderDescription != nullptr) {
                m_orderDescription = new char[strlen(other.m_orderDescription) + 1];
                strcpy(m_orderDescription, other.m_orderDescription); // copy description
            }
        }

        return *this; // return object
    }
    

    std::istream& FoodOrder::read(std::istream& is){
        char temp[25];
        if(is){ // if function is in good state it will read file
            if (m_orderDescription != nullptr) {
                delete[] m_orderDescription; // deallocate memory
            }

            m_orderDescription = nullptr; // set to null
            m_counter++;

            is.getline(m_customerName, 10, ',');
            is.getline(temp, 25, ',');
            is >> m_price;
            is.ignore();
            is >> m_dailySpecial;
            is.ignore();

            m_orderDescription = new char[strlen(temp) + 1]; 
            strcpy(m_orderDescription, temp); // copy description
        }

        return is; // return is object
    }

    void FoodOrder::display() const{
        static int counter = 1; // static counter to keep track of number of orders

        double tax = m_price * (1 + g_taxrate); // calculate tax
        float discount =  tax - g_dailydiscount; // calculate discount
        std::cout << std::left << std::setw(2) << counter << ". "; 

        if(m_customerName[0] == '\0'){ // if customer name is not available there was no order placed
            std::cout <<"No Order" << std::endl;
        }
        
        else{
            std::cout 
                << std::setw(10) << m_customerName << "|" // display customer name
                << std::setw(25) << m_orderDescription << "|" // display order description
                << std::setw(12) << std::fixed << std::setprecision(2) << tax << "|"; // display price with tax

            if (m_dailySpecial == 'Y') { // if daily special is ordered apply discount
                std::cout << std::right << std::setw(13) << discount; // price displayed with discount
            } 

            std::cout << std::endl;
        }

        counter++; // increment counter
    } // end of display function
}