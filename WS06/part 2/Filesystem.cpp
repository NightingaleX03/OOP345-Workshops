/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Filesystem.h"

namespace seneca{


    Filesystem::Filesystem(const std::string& file, const std::string& path) {
        
        // create the root directory
        m_root = new Directory(path);
        m_current = m_root;

        // open the file
        std::ifstream inputFile(file);
        if(!inputFile.is_open()){
            throw std::string("Cannot open file '") + file + "'";
        }

        std::string line;

        // read the file
        while (std::getline(inputFile, line)) {
            // trim the line
            line = trim(line);

            if (!line.empty()){
                continue;
            }

            size_t pos = line.find(" | ");
        
            // Directory case
            if (pos == std::string::npos) {
                if (line.back() == '/') {
                    std::string dirPath = trim(line);
                    Directory* current = m_root;
                    size_t start = 0, end;
                    // Create directories
                    while ((end = dirPath.find('/', start)) != std::string::npos) {
                        std::string dirName = dirPath.substr(start, end - start);
                        Directory* subdir = dynamic_cast<Directory*>(current->find(dirName));
                        // If the directory does not exist, create it
                        if (!subdir) {
                            subdir = new Directory(dirName);
                            *current += subdir;
                        }
                        current = subdir;
                        start = end + 1;
                    }
                } else {
                    throw std::runtime_error("Invalid format input file: '" + line + "'");
                }
            } else {
                // File case
                std::string filePath = trim(line.substr(0, pos));
                std::string contents = trim(line.substr(pos + 3));
                Directory* current = m_root;
                size_t start = 0, end;
                // Create directories
                while ((end = filePath.find('/', start)) != std::string::npos) {
                    std::string dirName = filePath.substr(start, end - start);
                    Directory* subdir = dynamic_cast<Directory*>(current->find(dirName));
                    // If the directory does not exist, create it
                    if (!subdir) {
                        subdir = new Directory(dirName);
                        *current += subdir;
                    }
                    current = subdir;
                    start = end + 1;
                }
                // Create file
                std::string fileName = filePath.substr(start);
                File* newFile = new File(fileName, contents);
                *current += newFile;
            }
        }

        inputFile.close();
    }
            
    // move constructor
    Filesystem::Filesystem(Filesystem&& other) noexcept{
        // move the resources
        m_root = other.m_root;
        m_current = other.m_current;
        other.m_root = nullptr;
        other.m_current = nullptr;
    }
    
    // move assignment operator
    Filesystem& Filesystem::operator=(Filesystem&& other) noexcept{
        // check if the object is not the same
        if(this != &other){
            delete m_root;
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_root = nullptr;
            other.m_current = nullptr;
        }
        return *this;
    }

    // add a resource to the directory
    Filesystem& Filesystem::operator+=(Resource* resource){
        // check if the resource is null
        if(m_current){
            *m_current += resource;
        }
        return *this;
    }

    // change the current directory
    Directory* Filesystem::change_directory(const std::string& path){
        // check if the path is empty
        if(path.empty()){
            m_current = m_root;
        }
        else{
            // find the directory
            Directory* directory = dynamic_cast<Directory*>(m_current->find(path));
            if(directory){
                m_current = directory;
            }
            else{
                throw std::string("Couldn't change directory to invalid directory.");
            }
        }

        return m_current;
    }

    // get the current directory
    Directory* Filesystem::get_current_directory() const{
        return m_current;
    }

    // destructor
    Filesystem::~Filesystem(){
        delete m_root;
    }

    // trim the string
    std::string Filesystem::trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");
        return (start != std::string::npos ? str.substr(start, end - start + 1) : "");
    }
}