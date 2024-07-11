/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. I've used the help of Chatgpt
to help submit the second part of this workshop

Sarah Mathew
smathew32@myseneca.ca
140903238
*/


#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include <string>
#include "File.h"
#include <fstream>
#include <iostream>

namespace seneca{

    class Filesystem{

        Directory* m_root;
        Directory* m_current;

    public:
        Filesystem(const std::string& file, const std::string& path);

        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        Filesystem(Filesystem&& other) noexcept;
        Filesystem& operator=(Filesystem&& other) noexcept;

        Filesystem& operator+=(Resource*);

        Directory* change_directory(const std::string&);

        Directory* get_current_directory() const;

        ~Filesystem();

        std::string trim(const std::string& str);
    };

}

#endif