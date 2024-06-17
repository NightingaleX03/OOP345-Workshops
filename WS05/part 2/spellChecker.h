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

#ifndef SENECA_SPELLCHECK_H
#define SENECA_SPELLCHECK_H

    namespace seneca{
        class SpellChecker{
            std::string m_badWords[6];
            std::string m_goodWords[6];
            int m_replacementCounts[6] = {0};

        public:
            SpellChecker(const char* filename);
            void operator()(std::string& text);
            void showStatistics(std::ostream& out) const;
        };
    }

#endif // SENECA_SPELLCHECK_H
