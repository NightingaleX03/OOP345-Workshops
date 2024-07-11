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

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

    namespace seneca{

        class Movie{
            // private members
            std::string m_title {};
            size_t m_yearRelease {};
            std::string m_description {};

        public:

            // public members
            Movie(); // default constructor
            Movie(const std::string& strMovie); // constructor with reading lines from each movie using helper function
            const std::string& title() const { return m_title; };


            // overloaded operator to display movie information
            friend std::ostream& operator<<(std::ostream& os, const Movie& movie);


            //templated function
            template<typename T>
            void fixSpelling(T& spellChecker){
                spellChecker(m_description);
                spellChecker(m_title);
            }
        };

    }
#endif // SENECA_MOVIE_H
