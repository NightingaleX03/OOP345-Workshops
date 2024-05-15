/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include <iostream>
#include <iomanip>

#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

// global variables can change day to day
double g_taxrate;
double g_dailydiscount;

namespace seneca{

    class FoodOrder
    {

    private:
        int m_counter; // counts number of orders for duration of program
        char m_customerName[10]; // 10 char with null
        char m_orderDescription[25];  // 25 char with null
        double m_price; // cost of order
        char m_dailySpecial; // customer ordered special? yes or no

    public:
        FoodOrder(); // constructor
        std::istream& read(std::istream& is); // read function
        void display() const; // display function
    };
}
#endif // FOODORDER_H
