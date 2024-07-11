/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"
#include <string>

namespace seneca{

    class File : public Resource{
    
        std::string m_contents;

        File(const File&) = delete;
        File& operator=(const File&) = delete;
        File(File&&) = delete;
        File& operator=(File&&) = delete;
    
    public:
    
       File(const std::string& name, const std::string& contents);
    
        void update_parent_path(const std::string&) override;
    
        NodeType type() const override;
    
        std::string path() const override;
    
        std::string name() const override;
        
        int count() const override;
    
        size_t size() const override;

        ~File() = default;
    };
}
#endif