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

    //template Database class
    template <typename T>
    class Database {

        private:

            static std::shared_ptr<Database<T>> m_instance;
            static const int max_entries = 20;
            int m_numOfEntries;
            std::array<std::string, max_entries> m_keys;
            std::array<std::string, max_entries> m_values;
            std::string m_filename;

            Database(const std::string& filename);
            void encryptDecrypt(T& value);

        public:

            static std::shared_ptr<Database> getInstance(const std::string& filename);
            Err_Status GetValue(const std::string& key, T& value);
            Err_Status SetValue(const std::string& key, const T& value);
            ~Database();
    };

    // template struct for string
    template <>
    void Database<std::string>::encryptDecrypt(std::string& value){
        const char secret[]{"secret encryption key"};

        //for each character in value
        for(char& C: value){
            //for each character in secret
            for(char K: secret){
                C = C ^ K;
            }
        }
    }
    
    // template struct for long long
    template <>
    void Database<long long>::encryptDecrypt(long long& value){
        const char secret[]{ "super secret encryption key" };
        //convert value to char
        char* B = reinterpret_cast<char*>(&value);
        //size of long long
        size_t size = sizeof(long long);

        //for each character in value
        for(size_t i = 0; i < size; i++){
            //for each character in secret
            for (char K : secret) {
                B[i] ^= K;
            }
        }
    }
}

#endif // !SENECA_DATABASE_H