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
        size_t start = 0;
        m_title = getInformation(strMovie, start);
        m_yearRelease = std::stoi(getInformation(strMovie, start));
        m_description = getInformation(strMovie, start);
    }

    // overloaded operator to display movie information
    std::ostream& operator<<(std::ostream& os, const Movie& movie){
        os << std::left << std::setw(40) << movie.m_title << " | ";
        os << std::right << std::setw(4) << movie.m_yearRelease << " | ";
        os << movie.m_description << std::endl;
        return os;
    }

    // helper function to get information from each movie
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