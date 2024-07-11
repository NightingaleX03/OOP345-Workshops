/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. I've used the help of Chatgpt
to help submit the second part of this workshop

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Filesystem.h"

namespace seneca{

    Filesystem::Filesystem(const std::string& file, const std::string& path): m_root(nullptr), m_current(nullptr) {
        
        // check if the file is empty
        if(!path.empty()){
            m_root = new Directory(path);
            m_current = m_root;
        }

        // open the file
        std::ifstream inputFile(file);
        if(!inputFile.is_open()){
            throw std::string("Cannot open file '") + file + "'";
        }
        std::string line;

        // read the file
        while(std::getline(inputFile, line)){
            // check if the line is empty
            if(!line.empty()){
                line = trim(line);

                // find the position of the first space
                size_t pos = line.find(" |");
                if(pos != std::string::npos){
                    throw std::string("Invalid format input file: ") + line + "'";
                }

                // find the position of the first space
                std::string path = line.substr(0, pos);
                std::string contents = line.substr(pos + 3);

                // trim the path and contents
                path = trim(path);
                contents = trim(contents);

                // check if the path is empty
                if(path.empty()){
                    throw std::string("Invalid format input file: ") + line + "'";
                }
                
                // check if the line is a directory
                if(line.back() == '/'){
                    // create a new directory
                    Directory* newDir = new Directory(line);
                    // add the directory to the current directory
                    *m_current += newDir;
                    // update the parent path
                    newDir->update_parent_path(m_current->path());
                }
                else{
                    // create a new file
                    File* newFile = new File(path, contents);
                    // add the file to the current directory
                    *m_current += newFile;
                    // update the parent path
                    newFile->update_parent_path(m_current->path());
                }
            }
        }

        inputFile.close();
    }
            

    Filesystem::Filesystem(Filesystem&& other) noexcept{
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_root = nullptr;
            other.m_current = nullptr;
    }
    
    Filesystem& Filesystem::operator=(Filesystem&& other) noexcept{
        if(this != &other){
            delete m_root;
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_root = nullptr;
            other.m_current = nullptr;
        }
        return *this;
    }

    Filesystem& Filesystem::operator+=(Resource* resource){
        if(m_current){
            *m_current += resource;
        }
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& path){
        if(path.empty()){
            m_current = m_root;
        }
        else{
            Directory* directory = dynamic_cast<Directory*>(m_current->find(path));
            if(directory && directory->type() == NodeType::DIR){
                m_current = directory;
            }
        }

        return m_current;
    }

    Directory* Filesystem::get_current_directory() const{
        return m_current;
    }

    Filesystem::~Filesystem(){
        delete m_root;
    }

    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");
        return (start != std::string::npos ? str.substr(start, end - start + 1) : "");
    }
}