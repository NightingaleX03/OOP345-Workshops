#include "SpellChecker.h"

namespace seneca{

    // constructor to read the bad and good words from the file
    SpellChecker::SpellChecker(const char* filename){
        // open the file
        std::ifstream file(filename);

        // check if file is open
        if(file.is_open()){
            std::string line;
            size_t i = 0;

            // read the bad and good words from the file
            while(i < 5 && std::getline(file, line)){
                m_badWords[i] = line.substr(0, line.find(' '));
                m_goodWords[i] = line.substr(line.find(' ') + 1);
                i++;
            }
        }
    }

    // operator to replace the bad words with good words
    void SpellChecker::operator()(std::string& text){
        // loop through the bad words
        for(int i = 0; i < 6; i++){
            // replace the bad words with good words
            const std::string& bad = m_badWords[i];
            const std::string& good = m_goodWords[i];
            size_t pos = 0;
            int count = 0;

            // loop through the text and replace the bad words with good words
            while((pos = text.find(bad, pos)) != std::string::npos){
                text.replace(pos, bad.size(), good);
                pos += good.size();
                count++;
            }

            // update the replacement count
            m_replacementCounts[i] += count;
        }
    }

    // function to display the statistics
    void SpellChecker::showStatistics(std::ostream& out) const{
        for(int i = 0; i < 6; i++){
            out << std::setw(15) << m_badWords[i] << " : " << m_replacementCounts[i] << std::endl;
        }
    }
}