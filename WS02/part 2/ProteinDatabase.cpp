/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "ProteinDatabase.h"
namespace seneca{

    // constructor
    ProteinDatabase::ProteinDatabase(): m_proteins(nullptr), m_numProteins(0){}
    
    ProteinDatabase::ProteinDatabase(const char* filename): m_proteins(nullptr), m_numProteins(0){
        m_numProteins = countProtein(filename); // count number of proteins
        if(m_numProteins > 0){
            m_proteins = new std::string[m_numProteins]; // allocate memory
            storeProteins(filename); // store proteins in array
        }

    }

    ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) : m_proteins(other.m_proteins), m_numProteins(other.m_numProteins) {
        other.m_proteins = nullptr;
        other.m_numProteins = 0;
    }
    
    std::string ProteinDatabase::operator[](size_t size){
        if (size < m_numProteins){
            return m_proteins[size]; // return protein at index
        }
        else{
            return ""; // return empty string
        }
    }

    // move assignment operator
    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& other) {
        if(this != &other){
            delete[] m_proteins; // deallocate memory
            m_proteins = other.m_proteins;
            m_numProteins = other.m_numProteins; 
            other.m_proteins = nullptr; 
            other.m_numProteins = 0; 
        }
        return *this; // return object
    }

    size_t ProteinDatabase::countProtein(const char* filename){
        std::ifstream file(filename); // opens file
        size_t count = 0; // temp var for num line

        if(file.is_open()){ // checks if file is open
            std::string line;

            while(std::getline(file, line)){ // reads every line in file
                if(!line.empty() && line[0] == '>'){ // checks if line starts with '>'
                    count++;
                }
            }
            file.close(); // close file
        } // end of if statement
        else{
            std::cerr << "Error! Unable to open file: " << filename << std::endl; // error statement
        }

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

                else if(readingSequence && lineNum < m_numProteins){ // checks if reading sequence
                    m_proteins[lineNum] += line;
                }
            }
            file.close(); // close file
        } // end of if statement

        else{
            std::cerr << "Error! Unable to open file: " << filename << std::endl; // error statement
        }
    }

}