#include <iostream>
#include <fstream>

#include "Router.h"

//Sample router table entries:
// 1.0.0.0/24|7018 15169|12.0.1.63
// 1.0.4.0/24|8492 6939 7545 56203|85.114.0.217
// 1.0.4.0/24|13030 6939 7545 56203|213.144.128.203
//
// {Destination Address/Prefix}|{AS Path}|{Next Location to Route to}

//Main
int main(int argc, char * argv[]) {
    Router router;

    router.Initialize(argc, argv);
    router.ParseRoutingTable();
    router.ParseLookup();
    router.Lookup();
}

void Router::Initialize(int argc, char ** argv) {
    if((argc - 1) < 2) {
        std::cout << "@usage: ./Router <routing table> <lookup IPs>" << std::endl;
        exit(1);
    }

    routingTableFilename.append(argv[1]);
    lookupFilename.append(argv[2]);
}

void Router::ParseRoutingTable(void) {
    routingTableFile.open(routingTableFilename);

    if(routingTableFile.is_open()) {
        std::string line;
        std::vector<std::string> list;
        std::vector<std::string> subList;

        std::string destination;
        unsigned int prefix;
        unsigned int size;
        std::string nextHop;

        while(getline(routingTableFile, line)) {
            list = StringUtilities::SplitString(line, "|");

            //Destination and Prefix
            subList = StringUtilities::SplitString(list.at(0), "/");
            destination = subList.at(0);
            prefix = atoi(subList.at(1).c_str());

            //AS Paths
            subList = StringUtilities::SplitString(list.at(1), " ");
            size = subList.size();

            //Next Hop
            nextHop = list.at(2);

            //Insert the entry in the trie
            trie.Insert(destination, prefix, size, nextHop);
        }

        //Close the file
        routingTableFile.close();
    } else {
        throw FileIOException(routingTableFilename, "Unable to open file");
    }
}

void Router::ParseLookup(void) {
    lookupFile.open(lookupFilename);

    if(lookupFile.is_open()) {
        std::string line;

        while(getline(lookupFile, line)) {
            lookup.push_back(line);
        }

        lookupFile.close();
    } else {
        throw FileIOException(lookupFilename, "Unable to open file");
    }
}

void Router::Lookup(void) {
    for(int i = 0; i < lookup.size(); i++) {
        std::cout << lookup.at(i) << "\t" << trie.Get(lookup.at(i)) << std::endl;
    }
}
