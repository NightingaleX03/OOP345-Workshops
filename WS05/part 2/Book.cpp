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
        size_t start =0;
        size_t end= strBook.find(',');

        m_author=strBook.substr(start,(end-start));
        m_author.erase(0,strBook.find_first_not_of(" \t\r\n"));

        start=end + 1;
        end=strBook.find(',',start);

        m_title=strBook.substr(start,(end-start));
        m_title.erase(0, m_title.find_first_not_of(" \t\r\n"));
        m_title.erase(m_title.find_last_not_of(" \t\r\n")+1);

        start=end + 1;
        end=strBook.find(',',start);

        m_country=strBook.substr(start,(end-start));
        m_country.erase(0,m_country.find_first_not_of(" \t\r\n"));
        m_country.erase(m_country.find_last_not_of(" \t\r\n")+1);

        start=end + 1;
        end=strBook.find(',',start);

        m_price=stod(strBook.substr(start,(end-start)));

        start=end + 1;
        end=strBook.find(',',start);

        m_year=stoi(strBook.substr(start,(end-start)));

        start=end + 1;
        end=strBook.find('\n',start);


        m_description= strBook.substr(start,(end-start));
        m_description.erase(0, m_description.find_first_not_of(" \t\r\n"));
        m_description.erase(m_description.find_last_not_of(" \t\r\n")+1);
    }

    // overloaded operator to display book information 
    std::ostream& operator<<(std::ostream& os, const Book& book){
        os << std::right << std::setw(20) << book.m_author << " | ";
        os << std::right << std::setw(22) << book.m_title << " | ";
        os << std::right << std::setw(5) << book.m_country << " | ";
        os << std::right << std::setw(4) << book.m_year << " | ";
        os << std::right << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | ";
        os << book.m_description << std::endl;
        return os;
    }
    
}
