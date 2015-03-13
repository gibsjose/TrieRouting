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

    router.PrintRoutingTable();

    router.BuildTrie();
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

        RoutingTableEntry entry;
        RoutingTableEntry prevEntry;

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

            entry.destination = destination;
            entry.prefix = prefix;
            entry.size = size;
            entry.nextHop = nextHop;

            std::cout << "Destination = " << destination << std::endl;
            std::cout << "Prefix = " << prefix << std::endl;
            std::cout << "Size = " << size << std::endl;
            std::cout << "Next Hop = " << nextHop << std::endl;
            std::cout << std::endl;

            if(prevEntry.Empty() || (entry < prevEntry)) {
                routingTable[destination] = entry;
            }

            prevEntry = entry;
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

void Router::PrintRoutingTable(void) {
    std::map<std::string, RoutingTableEntry>::iterator it;

    for(it = routingTable.begin(); it != routingTable.end(); ++it) {
        it->second.Print();
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

void Router::BuildTrie(void) {

}

void Router::Lookup(void) {

}
