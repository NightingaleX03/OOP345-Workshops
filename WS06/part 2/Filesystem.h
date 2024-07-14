/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

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
#include <sstream>
#include <algorithm>

namespace seneca{

    class Filesystem{

        Directory* m_root;
        Directory* m_current;

        std::string trim(const std::string& str);

    public:
        Filesystem(const std::string& file, const std::string& path = "");

        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        Filesystem(Filesystem&& other) noexcept;
        Filesystem& operator=(Filesystem&& other) noexcept;

        Filesystem& operator+=(Resource* resource);

        Directory* change_directory(const std::string& path = "");

        Directory* get_current_directory() const;

        ~Filesystem();

    };

}

#endif