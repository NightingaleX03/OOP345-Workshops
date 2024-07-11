/*
I declare that this submission is the result of my own work and I only copied the code that
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Movie.h"

namespace seneca{

    // default constructor
    Movie::Movie(): m_title(""), m_yearRelease(0), m_description(""){
    }

    // constructor with reading lines from each movie using helper function
    Movie::Movie(const std::string& strMovie){
        size_t start =0;
        size_t end= strMovie.find(',');

        m_title=strMovie.substr(start,(end-start));
        m_title.erase(0,strMovie.find_first_not_of(" \t\r\n"));
        m_title.erase(m_title.find_last_not_of(" \t\r\n") + 1);

        start=end + 1;
        end=strMovie.find(',',start);


        m_yearRelease=stod(strMovie.substr(start,(end-start)));


        start=end + 1;
        end=strMovie.find('\n',start);


        m_description= strMovie.substr(start,(end-start));
        m_description.erase(0, m_description.find_first_not_of(" \t\r\n"));
        m_description.erase(m_description.find_last_not_of(" \t\r\n")+1);
    }

    // overloaded operator to display movie information
    std::ostream& operator<<(std::ostream& os, const Movie& movie){
        os << std::right << std::setw(40) << movie.m_title << " | ";
        os << std::right << std::setw(4) << movie.m_yearRelease << " | ";
        os << movie.m_description << std::endl;
        return os;
    }

}