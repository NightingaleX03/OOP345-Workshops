/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace seneca{

    class Directory : public Resource{
    
        std::vector<Resource*> m_contents;

        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    
    public:
    
        Directory(const std::string& name);
    
        void update_parent_path(const std::string& path) override;
    
        NodeType type() const override;
    
        std::string path() const override;
    
        std::string name() const override;
        
        int count() const override;
    
        size_t size() const override;

        Directory& operator+=(Resource* resource);

        Resource* find(const std::string& name, const std::vector<OpFlags>& flags ={});
        
        ~Directory();
    };
}

#endif