/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/


#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <vector>
#include <string>

namespace seneca {

    // Collection class template
    template<typename T>
    class Collection {
        std::string m_name {};
        T* m_items {};
        size_t m_size {};
        void (*m_observer)(const Collection<T>&, const T&);

    public:
        // constructor
        Collection(const std::string& name){
            m_name = name;
            m_items = nullptr;
            m_size = 0;
            m_observer = nullptr;
        }
        // destructor
        virtual ~Collection(){
            delete[] m_items;
        }

        // deleted copy constructor and assignment operator
        Collection(const Collection&)=delete;
        Collection& operator=(const Collection&)= delete;
        Collection(Collection&& collection) = delete;
        Collection& operator=(Collection&& collection) = delete;

        // member functions
        const std::string& name() const{
            return m_name;
        }
        size_t size() const{
            return m_size;
        }

        //operator functions
        void setObserver(void (*observer)(const Collection<T>&, const T&)){
            m_observer = observer;
        }

        //overloaded operator
        Collection<T>& operator+=(const T& item){
            bool exists = false;
            T* temp;

            //check if item already exists
            for(size_t i = 0; i < m_size; i++){
                if(m_items[i].title() == item.title()){
                    exists = true;
                }
            }

            //if item does not exist, add it to the collection
            if(!exists){
                temp = new T[m_size + 1];
                for(size_t i = 0; i < m_size; i++){
                    temp[i] = m_items[i];
                }

                temp[m_size] = item;

                delete[] m_items;
                m_items = temp;
                m_size++;

                if(m_observer){
                    m_observer(*this, item);
                }
            }
            //return the collection
            return *this;
        }

        //overloaded operator
        T& operator[](size_t idx) const{
            //check if index is out of range
            if (idx >= m_size) {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) +"] items.");
            }
            return m_items[idx];
        }

        //overloaded operator
        T* operator[](const std::string& title) const{

            T* item = nullptr;

            //find the item with the title
            for(size_t i = 0; i < m_size; i++){
                if(m_items[i].title() == title){
                    item = &m_items[i];
                }
            }
            
            return item;
        }
    };

    //templated function
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& collection){
        //display the collection
        for(size_t i = 0; i < collection.size(); i++){
            os << collection[i];
        }
        return os;
    }
}

#endif // SENECA_COLLECTION_H
