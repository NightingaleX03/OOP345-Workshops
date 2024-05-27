#include "ProteinDatabase.h"
namespace seneca{

    ProteinDatabase::ProteinDatabase(){
        m_numProteins = 0;
        m_proteins = nullptr;
    }
    
    ProteinDatabase::ProteinDatabase(const char* filename){

        m_numProteins = countProtein(filename); // count number of proteins
        if(m_numProteins > 0){
            m_proteins = new std::string[m_numProteins]; // allocate memory
            storeProteins(filename); // store proteins in array
        }
        else{
            m_proteins = nullptr; // set to nullptr
        }

    }
    
    ProteinDatabase::~ProteinDatabase(){
        delete[] m_proteins; // deallocate memory
        m_proteins = nullptr;
    }
    
    size_t ProteinDatabase::size(){
        return m_numProteins; // return number of proteins
    }
    
    std::string ProteinDatabase::operator[](size_t size){
        if (size < m_numProteins){
            return m_proteins[size]; // return protein at index
        }
    }

    size_t ProteinDatabase::countProtein(const char* filename){
        std::ifstream file(filename); // opens file
        size_t count = 0; // temp var for num line

        if(file.is_open()){ // checks if file is open
            std::string line;

            while(std::getline(file, line)){ // reads every line in file

                if(line[0] == '>'){ // checks if line starts with '>'
                    count++;
                }
            }
        } // end of if statement
        else{
            std::cerr << "Error! Unable to open file: " << filename << std::endl; // error statement
        }

        file.close(); // close file
        return count; // return count
    }

    void ProteinDatabase::storeProteins(const char* filename){
        std::ifstream file(filename); // opens file

        if(file.is_open()){ // checks if file is open
            std::string line;
            size_t lineNum = 0;
            bool readingSequence = false;

            while(std::getline(file, line)){ // reads every line in file
                
                if (!line.empty() && line[0] == '>') { // checks if line starts with '>'
                    
                    if(readingSequence){ // checks if reading sequence
                        lineNum++;
                    }
                    readingSequence = true;
                }

                else if(readingSequence){ // checks if reading sequence
                    m_proteins[lineNum] += line;
                }
            }
        } // end of if statement

        else{
            std::cerr << "Error! Unable to open file: " << filename << std::endl; // error statement
        }

        file.close(); // close file
    }

}