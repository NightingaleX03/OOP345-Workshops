/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include <iostream>

#ifndef FOODORDER_H
#define FOODORDER_H

namespace seneca{

    // global variables can change day to day
    double g_taxrate;
    double g_dailydiscount;

    class FoodOrder
    {

    private:
        char m_customerName[11]; // 10 char with null
        char m_orderDescription[26];  // 25 char with null
        double m_price; // cost of order
        char m_dailySpecial; // customer ordered special? yes or no

    public:
        FoodOrder();
        void read(std::istream& is);
        void display() const;
    };

}
#endif // FOODORDER_H
