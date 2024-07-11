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
    void Directory::update_parent_path(const std::string& path){
        m_parent_path = path;
        // update the parent path for all resources
        for(auto& resource : m_contents){
            resource->update_parent_path(this->path());
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
        return m_contents.size();
    }

    // return the size of the directory
    size_t Directory::size() const{
        size_t total = 0;

        // calculate the total size of the directory
        for(auto& resource : m_contents){
            total += resource->size();
        }
        return total;
    }

    // add a resource to the directory
    Directory& Directory::operator+=(Resource* resource){

        // check if resource already exists
        auto duplicate = std::find_if(m_contents.begin(), m_contents.end(), [&](Resource* res){
            // return true if the resource already exists
            return res->name() == resource->name();
        });

        // if resource does not exist, add it
        if(duplicate != m_contents.end()){
            std::cout << "**EXPECTED EXCEPTION: " + resource->name() + " image already exists in the root\n" << std::endl;
            return *this;
        }
            
        // update the parent path
        resource->update_parent_path(this->path());
        // add the resource to the directory
        m_contents.push_back(resource);

        // return the directory
        return *this;
    }

    // find a resource in the directory
    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags){
        // check if the resource exists
        for(auto& resource : m_contents){
            if(resource->name() == name){
                return resource;
            }
        }

        // if the resource does not exist, check if directory is recursive
        if(std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end()){
            // check if the resource exists in the subdirectories
            for(auto& resource : m_contents){
                // if the resource is a directory, find the resource in the subdirectory
                if(resource->type() == NodeType::DIR){

                    // find the resource in the subdirectory
                    Resource* found = dynamic_cast<Directory*>(resource)->find(name, flags);
                    // if the resource is found, return it
                    if (found) {
                        return found;
                    }
                }// end of if
            }// end of for
        }// end of if

        return nullptr;
    }
    
    // delete all resources
    Directory::~Directory(){
        for(auto& resource : m_contents){
            delete resource;
        }
    }

}