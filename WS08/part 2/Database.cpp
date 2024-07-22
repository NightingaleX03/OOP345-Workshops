/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Database.h"

namespace seneca{

    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::m_instance = nullptr;

    template<typename T>
    Database<T>::Database(const std::string& filename) : m_numOfEntries(0), m_filename(filename) {
        std::cout << "[" << this << "] Database(const std::string&)" << std::endl;
        //open file
        std::ifstream file(filename);
        //if file is open
        if(file){
            std::string key;
            T value;
            //while file is open and there is a key and value
            while( m_numOfEntries < max_entries && file >> key >> value){
                //if number of entries is less than max entries
                    for(char& c : key){
                        if(c == '_'){
                            c = ' ';
                        }
                    }
                    
                    encryptDecrypt(value);
                    //set key, value amd entries
                    m_keys[m_numOfEntries] = key;
                    m_values[m_numOfEntries] = value;
                    m_numOfEntries++;
            }

            //close file
            file.close();
        }
    }   

    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& filename){
        //if instance is null
        if(m_instance == nullptr){
            //create instance
            m_instance = std::shared_ptr<Database<T>>(new Database<T>(filename));
        }

        //return instance
        return m_instance;
    }

    template<typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value){
        //for each entry
        for(int i = 0; i < m_numOfEntries; i++){
            //if key is found
            if(m_keys[i] == key){
                value = m_values[i];
                //return success
                return Err_Status::Err_Success;
            }
        }

        //return not found
        return Err_Status::Err_NotFound;
    }

    template<typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value){
        //if number of entries is less than max entries
        if(m_numOfEntries < max_entries){

            //set key, value and entries
            m_keys[m_numOfEntries] = key;
            m_values[m_numOfEntries] = value;
            m_numOfEntries++;

            //return success
            return Err_Status::Err_Success;

        }

        //return out of memory
        return Err_Status::Err_OutOfMemory;
    }

    template<typename T>
    Database<T>::~Database(){
        std::cout << this << "~Database()" << std::endl;
        std::string filename = m_filename + ".bkp.txt";
		std::ofstream file(filename);

        //for each entry
        for(int i = 0; i < m_numOfEntries; i++){
            encryptDecrypt(m_values[i]);
            file << std::setw(25) << std::left << m_keys[i] << " -> " << m_values[i] << std::endl;
        }

        // close file
        file.close();

    }

    template<>
    void Database<std::string>::encryptDecrypt(std::string& value){
        const char secret[]{"secret encryption key"};

        //for each character in value
        for(char& C: value){
            //for each character in secret
            for(char K: secret){
                C ^=K;
            }
        }
    }

    template<>
    void Database<long long>::encryptDecrypt(long long& value){
        const char secret[]{ "super secret encryption key" };
        //convert value to char
        char* B = reinterpret_cast<char*>(&value);
        //size of long long
        size_t size = sizeof value;

        //for each character in value
        for(size_t i = 0; i < size; i++){
            //for each character in secret
            for (char K : secret) {
                B[i] ^= K;
            }
        }
    }

    template class Database<std::string>;
    template class Database<long long>;
}