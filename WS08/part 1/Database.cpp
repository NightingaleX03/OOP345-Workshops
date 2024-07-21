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

    std::shared_ptr<Database> Database::m_instance = nullptr;

    Database::Database(const std::string& filename) : m_numOfEntries(0), m_filename(filename) {
        //open file
        std::ifstream file(filename);
        //if file is open
        if(file){
            std::string key;
            std::string value;
            //while file is open and there is a key and value
            while(file >> key >> value){
                //if number of entries is less than max entries
                if(m_numOfEntries < max_entries){
                    for(char& c : key){
                        if(c == '_'){
                            c = ' ';
                        }
                    }

                    //set key, value amd entries
                    m_keys[m_numOfEntries] = key;
                    m_values[m_numOfEntries] = value;
                    m_numOfEntries++;

                }
            }

            //close file
            file.close();
            std::cout << this << "Database(const std::string&)" << std::endl;
        }
    }   

    std::shared_ptr<Database> Database::getInstance(const std::string& filename){
        //if instance is null
        if(m_instance == nullptr){
            //create instance
            m_instance = std::shared_ptr<Database>(new Database(filename));
        }

        //return instance
        return m_instance;
    }

    Err_Status Database::GetValue(const std::string& key, std::string& value){
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

    Err_Status Database::SetValue(const std::string& key, const std::string& value){
        //if number of entries is less than max entries
        if(m_numOfEntries < max_entries){
            // have temp value to store key
            std::string tempValue = key;

            //replace _ with space
            for(char& c : tempValue){
                if(c == '_'){
                    c = ' ';
                }
            }

            //set key, value and entries
            m_keys[m_numOfEntries] = tempValue;
            m_values[m_numOfEntries] = value;
            m_numOfEntries++;

            //return success
            return Err_Status::Err_Success;

        }

        //return out of memory
        return Err_Status::Err_OutOfMemory;
    }

    Database::~Database(){
        std::cout << this << "~Database()" << std::endl;
        //open file
        std::ofstream file(m_filename);

        //for each entry
        for(int i = 0; i < m_numOfEntries; i++){
            file << std::setw(25) << std::left << m_keys[i] << " -> " << m_values[i] << std::endl;
        }

        // close file
        file.close();

    }
}