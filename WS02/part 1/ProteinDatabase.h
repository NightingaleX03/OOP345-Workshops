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
#include <fstream>
#include <cstring>
#include <istream>
#include <string>

#include "TimedTask.h"

#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

namespace seneca{

    class ProteinDatabase
    {
        
        std::string* m_proteins;
        size_t m_numProteins;

    public:
        ProteinDatabase();
        ProteinDatabase(const char* filename);
        ~ProteinDatabase();
        size_t size();
        std::string operator[](size_t);

        // helper functions
        size_t countProtein(const char* filename);
        void storeProteins(const char* filename);
    };
}
#endif // SENECA_PROTEINDATABASE_H
