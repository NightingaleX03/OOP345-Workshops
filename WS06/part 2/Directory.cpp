/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Directory.h"

namespace seneca{

    // constructor
    Directory::Directory(const std::string& name){
        m_name = name;
    }
    
    // update the parent path
    void Directory::update_parent_path(const std::string& parentPath){
        m_parent_path = parentPath;
        // update the parent path for all resources
        for(auto& resource : m_contents){
            resource->update_parent_path(path());
        }
    }

    // return the type of the directory
    NodeType Directory::type() const{
        return NodeType::DIR;
    }

    // return the path of the directory
    std::string Directory::path() const{
        return m_parent_path + m_name;
    }

    // return the name of the directory
    std::string Directory::name() const{
        return m_name;
    }
    
    // return the number of resources in the directory
    int Directory::count() const{
        return static_cast<int>(m_contents.size());
    }

    // return the size of the directory
    size_t Directory::size() const{
        size_t total = 0;

        // calculate the total size of the directory
        for(auto resource : m_contents){
            total += resource->size();
        }
        return total;
    }

    // add a resource to the directory
    Directory& Directory::operator+=(Resource* resource){

        // check if the resource is null
       for(auto& res : m_contents){
            if(res->name() == resource->name()){
                throw "Duplicate resource name of resource into directory";
            }
        }

        // update the parent path
        resource->update_parent_path(path());
        // add the resource to the directory
        m_contents.push_back(resource);

        // return the directory
        return *this;
    }

    // find a resource in the directory
    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags){
        // check if the resource exists
        bool found = false;

        // find the resource in the directory
        for(auto resource: flags){
            if(resource == OpFlags::RECURSIVE){
                found = true;
                break;
            }
        }

        // return the resource if found
        for(auto& resource : m_contents){
            // check if the resource is found
            if(resource->name() == name){
                return resource;
            }
            // check if the resource is a directory
            if(found && resource->type() == NodeType::DIR){
                Resource* found = dynamic_cast<Directory*>(resource)->find(name, flags);
                if(found){
                    return found;
                }
            }
        }

        // return null if the resource is not found
        return nullptr;
    }
    
    // delete all resources
    Directory::~Directory(){
        for(auto resource : m_contents){
            delete resource;
        }
    }

    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags){
        // Find the resource to delete
        auto it = std::find_if(m_contents.begin(), m_contents.end(),
            [&](Resource* res) { return res->name() == name; });

        // If the resource does not exist, throw an exception
        if (it == m_contents.end()) {
            throw std::invalid_argument(name + " does not exist in " + m_name);
        }

        // If the resource is a directory and the recursive flag is not present, throw an exception
        if ((*it)->type() == NodeType::DIR && std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) {
            throw std::invalid_argument(name + " is a directory. Pass recursive flag to delete directories.");
        }

        delete *it;
        m_contents.erase(it);
    }
        
    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const{
        os << "Total size: " << size() << " bytes" << std::endl;
            for (const auto& resource : m_contents) {
                os << (resource->type() == NodeType::DIR ? "D" : "F") << " | "
                   << std::left << std::setw(15) << resource->name() << " | ";
                if (std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end()) {
                    if (resource->type() == NodeType::DIR) {
                        os << std::right << std::setw(2) << resource->count() << " | ";
                    } else {
                        os << "   | ";
                    }
                    os << std::right << std::setw(10) << resource->size() << " bytes |";
                }
                os << std::endl;
            }
    }

}