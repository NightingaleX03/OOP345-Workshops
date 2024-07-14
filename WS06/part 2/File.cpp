/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "File.h"

namespace seneca{

    File::File(const std::string& name, const std::string& contents): m_contents(contents){
        m_name = name;
        m_parent_path = "";
    }

    void File::update_parent_path(const std::string& path){
        m_parent_path = path;
    }

    NodeType File::type() const{
        return NodeType::FILE;
    }
    
    std::string File::path() const{

        return m_parent_path.empty() ? m_name : m_parent_path + "/" + m_name;
    }

    std::string File::name() const{
        return m_name;
    }
    
    int File::count() const{
        return -1;
    }

    size_t File::size() const{
        return m_contents.size();
    }

}