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
#include <fstream>
#include "Book.h"
#include "Book.h" // intentional

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// readBook function
void readBook(std::ifstream& file, seneca::Book* library, size_t size){
	std::string line;
	size_t i = 0;

	// reading books from file
	while (std::getline(file, line)){
		// checking if line is not empty and does not start with #
		if (!line.empty() && line[0] != '#'){
			// checking if there is space in library
			if(i < size){
				library[i] = seneca::Book(line);
				i++;
        	}
        	else{
            	continue;
    		}
		}
	}
	// closing file
    file.close();
}

// ws books.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	seneca::Book library[7];
	size_t numBooks = 7;
	if (argc == 2) {
		// TODO: load the collection of books from the file "argv[1]".
		//       - read one line at a time, and pass it to the Book constructor
		//       - store each book read into the array "library"
		//       - lines that start with "#" are considered comments and should be ignored
		//       - if the file cannot be open, print a message to standard error console and
		//                exit from application with error code "AppErrors::CannotOpenFile"
		
		std::ifstream file(argv[1]);
		if(!file.is_open()){
			std::cerr << "ERROR: Cannot open file [" << argv[1] << "].\n";
		}
		
		// reading books from file
		readBook(file, library, numBooks);
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// TODO: create a lambda expression that fixes the price of a book accoding to the rules
	//       - the expression should receive a single parameter of type "Book&"
	//       - if the book was published in US, multiply the price with "usdToCadRate"
	//            and save the new price in the book object
	//       - if the book was published in UK between 1990 and 1999 (inclussive),
	//            multiply the price with "gbpToCadRate" and save the new price in the book object

	auto fixBookPrice = [&](seneca::Book& book){
		// checking if book was published in US
		if(book.country() == "US"){
			book.price() *= usdToCadRate;
		}
		// checking if book was published in UK between 1990 and 1999
		else if(book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999){
			book.price() *= gbpToCadRate;
		}
	};

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen

	// outputting all books within library
	for(size_t i = 0; i < numBooks; i++){
		std::cout << library[i] << "\n";
	}

	std::cout << "-----------------------------------------\n\n";

	// TODO: iterate over the library and update the price of each book
	//         using the lambda defined above.

	// fixing the prizes for all books within library
	for(size_t i = 0; i < numBooks; i++){
		fixBookPrice(library[i]);
	}

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen

	// outputting all books within library
	for(size_t i = 0; i < numBooks; i++){
		std::cout << library[i] << "\n";
	}

	std::cout << "-----------------------------------------\n";

	return cout;
}
