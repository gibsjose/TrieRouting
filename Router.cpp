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

    router.PrintLookup();
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

        RoutingTableEntry entry;

        std::string destination;
        unsigned int prefix;
        unsigned int size;
        std::string nextHop;

        while(getline(routingTableFile, line)) {
            // list = StringUtilities::SlitString(line, "|");
            //
            // //For each different entry, choose smallest list (arbitrarily decide ties)
            // //For that list, store destination address, prefix length, and next hop address
            // if(destination == prevDestination) {
            //     if((size < prevSize) || !prevSize) {
            //         entry.destination = destination;
            //         entry.prefix = 0;
            //         entry.nextHop = list.at(2);
            //     }
            // }

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

            std::cout << "Destination = " << destination << std::endl;
            std::cout << "Prefix = " << prefix << std::endl;
            std::cout << "Size = " << size << std::endl;
            std::cout << "Next Hop = " << nextHop << std::endl;
            std::cout << std::endl;
        }

        routingTableFile.close();
    } else {
        throw FileIOException(routingTableFilename, "Unable to open file");
    }
}

void Router::ParseLookup(void) {
    lookupFile.open(lookupFilename);

    if(lookupFile.is_open()) {
        std::string line;
        LookupEntry entry;

        while(getline(lookupFile, line)) {
            entry.address = line;
            lookup.push_back(entry);
        }

        lookupFile.close();
    } else {
        throw FileIOException(lookupFilename, "Unable to open file");
    }
}

void Router::PrintLookup(void) {
    std::cout << "Lookup IPs" << std::endl;
    std::cout << "------------------------" << std::endl;
    for(int i = 0; i < lookup.size(); i++) {
        std::cout << lookup.at(i).address << std::endl;
    }
    std::cout << std::endl;
}
