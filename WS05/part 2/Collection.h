/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H


namespace seneca{

    // templated class 
    template<typename T>
    class Collection{
        // private members
        std::string m_name;
        std::vector<T> m_items;
        size_t m_size;
        void (*m_observer)(const Collection&, const T&);
    
    public:

        // public members
        Collection(const std::string& name);
        // destructor
        ~Collection();

        // deleted copy constructor and assignment operator
        Collection(const Collection<T>&) = delete;
        Collection<T>& operator=(const Collection<T>&) = delete;

        const std::string& name() const;
        size_t size() const;

        // member function to set observer
        void setObserver(void (*observer)(const Collection<T>&, const T&));
        // overloaded operator to add item to collection
        Collection<T>& operator+=(const T& item);
        T& operator[](size_t idx) const;
        T* operator[](const std::string& title) const;

        // friend operator to display collection
        friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection);
    };

    //template constructor 
    template<typename T>
    Collection<T>::Collection(const std::string& name): m_name(name), m_size(0), m_observer(nullptr){
    }

    //template destructor
    template<typename T>
    Collection<T>::~Collection(){
    }

    //template member functions
    template<typename T>
    const std::string& Collection<T>::name() const{
        return m_name;
    }

    template<typename T>
    size_t Collection<T>::size() const{
        // return size
        return m_size;
    }

    template<typename T>
    void setObserver(void (*observer)(const Collection<T>&, const T&)){
        // set observer
        m_observer = observer;
    }

    template<typename T>
    Collection<T>& Collection<T>::operator+=(const T& item){
        // add item to collection
        m_items.push_back(item);
        m_size++;
        if(m_observer != nullptr){
            m_observer(*this, item);
        }

        // return collection
        return *this;
    }

    template<typename T>
    T& Collection<T>::operator[](size_t idx) const{
        // return item at index
        if(idx < m_size){
            return m_items[idx];
        }
    }

    template<typename T>
    T* Collection<T>::operator[](const std::string& title) const{
        // return item with title
        for(size_t i = 0; i < m_size; i++){
            if(m_items[i].title() == title){
                return &m_items[i];
            }
        }
        // return nullptr if not found
        return nullptr;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& collection){
        // display collection
        os << "------------------------------------------" << std::endl;
        os << collection.name() << " Collection" << std::endl;
        os << "------------------------------------------" << std::endl;
        for(size_t i = 0; i < collection.size(); i++){
            os << collection[i];
        }
        os << "------------------------------------------" << std::endl;
        return os;
    }

}
#endif // SENECA_COLLECTION_H
