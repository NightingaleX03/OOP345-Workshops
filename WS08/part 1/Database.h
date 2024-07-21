/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/


#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <string>
#include <array>
#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip>

namespace seneca {

    enum class Err_Status{
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    class Database {

        private:

            static std::shared_ptr<Database> m_instance;
            static const int max_entries = 20;
            int m_numOfEntries;
            std::array<std::string, max_entries> m_keys;
            std::array<std::string, max_entries> m_values;
            std::string m_filename;

            Database(const std::string& filename);

        public:

            static std::shared_ptr<Database> getInstance(const std::string& filename);
            Err_Status GetValue(const std::string& key, std::string& value);
            Err_Status SetValue(const std::string& key, const std::string& value);
            ~Database();
    };
}

#endif // !SENECA_DATABASE_H