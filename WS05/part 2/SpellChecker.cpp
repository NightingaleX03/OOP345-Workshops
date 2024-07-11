/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "SpellChecker.h"

namespace seneca{

    // constructor to read the bad and good words from the file
    SpellChecker::SpellChecker(const char* filename){
        // open the file
        std::ifstream file(filename);

        // check if file is open
        if(file.is_open()){

            std::string bad{};
            std::string good{};
            size_t i = 0;

            // read the bad and good words from the file
            while(file>>bad>>good){
                m_badWords[i] = bad;
                m_goodWords[i] = good;
                i++;
            }
            file.close();
        }
        else{
            throw "Bad file name!"; // throw an exception if file is not open
        }
    }

    // operator to replace the bad words with good words
    void SpellChecker::operator()(std::string& text){
        
        size_t start = 0;
        // loop through the text and replace the bad words with good words
        for(size_t i = 0; i < 6; i++){
            start = 0;

            // find the bad word and replace it with the good word
            while((start = text.find(m_badWords[i],start)) != std::string::npos){
                text.replace(start, m_badWords[i].length(), m_goodWords[i]);
                start += m_goodWords[i].length();
                m_replacementCounts[i]++;
            }
        }
    }

    // function to display the statistics
    void SpellChecker::showStatistics(std::ostream& out) const{
        size_t i = 0;
        out << "Spellchecker Statistics" << std::endl;

        for(auto& bad: m_badWords){
            out << std::setw(15) << bad << ": " << m_replacementCounts[i] << " replacements" << std::endl;
            i++;
        }
    }
}