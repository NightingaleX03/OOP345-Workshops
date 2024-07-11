/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_FLAGS_H
#define SENECA_FLAGS_H

namespace seneca{
    // Options for displaying the files and directories
    enum class FormatFlags {
        LONG,     // to display in long format
    };

    // Determine the type of filesystem resource
    enum class NodeType {
        DIR,   // Directory
        FILE   // Regular File
    };

    // Options for performing a filesystem operation
    enum class OpFlags {
        RECURSIVE,  // run an operation recursively
    };
}

#endif
