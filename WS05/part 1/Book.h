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
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;
    public:
    // public members
        Book(); // default constructor
        Book(const std::string& strBook); // constructor with reading lines from each book using helper function

        // member functions using lambda expression
        auto title() -> std::string { return m_title; }; 
        auto country() -> const std::string& { return m_country; };
        auto year() -> const size_t { return m_year; };
        auto price() -> double& { return m_price; };

        // overloaded operator to display book information
        friend std::ostream& operator<<(std::ostream& os, const Book& book);

        // helper functions
        std::string getInformation(const std::string& str, size_t& start, const std::string& line = ",");
    };
    
}
#endif // SENECA_BOOK_H