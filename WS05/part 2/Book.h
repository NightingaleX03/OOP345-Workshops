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
#include <string>
#include <fstream>

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

namespace seneca{

    class Book{
        // private members
        std::string m_author {};
        std::string m_title {};
        std::string m_country {};
        size_t m_year {0};
        double m_price = 0.0;
        std::string m_description {};
    public:
    // public members
        Book(); // default constructor
        Book(const std::string& strBook); // constructor with reading lines from each book using helper function

        // member functions using lambda expression
        const std::string& title() const { return m_title; };
        const std::string& country() const { return m_country; };
        const size_t year() const { return m_year; };
        double& price(){ return m_price; };

        // overloaded operator to display book information
        friend std::ostream& operator<<(std::ostream& os, const Book& book);

        //templated function
        template<typename T>
        void fixSpelling(T& spellChecker){
            spellChecker(m_description);
        }
    };
    
}
#endif // SENECA_BOOK_H