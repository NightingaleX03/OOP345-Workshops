/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Book.h"

namespace seneca{

    // default constructor
    Book::Book(): m_author(""), m_title(""), m_country(""), m_year(0), m_price(0.0), m_description(""){
    }
    
    // constructor with reading lines from each book using helper function
    Book::Book(const std::string& strBook){
        size_t start = 0;
        m_author = getInformation(strBook, start);
        m_title = getInformation(strBook, start);
        m_country = getInformation(strBook, start);
        m_year = std::stoi(getInformation(strBook, start));
        m_price = std::stod(getInformation(strBook, start));
        m_description = getInformation(strBook, start);
    }

    // overloaded operator to display book information 
    std::ostream& operator<<(std::ostream& os, const Book& book){
        os << std::left << std::setw(20) << book.m_author << " | ";
        os << std::left << std::setw(22) << book.m_title << " | ";
        os << std::left << std::setw(5) << book.m_country << " | ";
        os << std::right << std::setw(4) << book.m_year << " | ";
        os << std::right << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | ";
        os << book.m_description << std::endl;
        return os;
    }

    // helper function to get information from each book
    std::string getInformation(const std::string& str, size_t& start, const std::string& line){
        // get the information from the string
        size_t end = line.find(line, start);
        std::string info = str.substr(start, (end == std::string::npos) ? end : end - start);

        // update the start position
        start = (end == std::string::npos) ? end : end + 1;

        // remove any leading or trailing spaces
        size_t startRead = info.find_first_not_of(" ");
        size_t endRead = info.find_last_not_of(" ");
        info = (startRead == std::string::npos) ? "" : info.substr(startRead, endRead - startRead + 1);
    
        // return the information
        return info;
    }

    
}
