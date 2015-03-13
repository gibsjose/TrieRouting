#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>
#include <map>

#include "Trie.h"
#include "StringUtilities.h"
#include "Exception.h"

typedef struct RoutingTableEntry {
    RoutingTableEntry(void) {
        destination.clear();
        prefix = 0;
        size = 0;
        nextHop.clear();
    }

    void Print(void) {
        std::cout << "Destination = " << destination << std::endl;
        std::cout << "Prefix = " << prefix << std::endl;
        std::cout << "Size = " << size << std::endl;
        std::cout << "Next Hop = " << nextHop << std::endl;
        std::cout << std::endl;
    }

    bool Empty(void) {
        if(destination.empty() && (prefix == 0) && (size == 0) && nextHop.empty()) {
            return true;
        } else {
            return false;
        }
    }

    //Operator overloading
    inline bool operator< (const RoutingTableEntry& rhs){return (size < rhs.size);}

    std::string destination;
    unsigned int prefix;
    unsigned int size;
    std::string nextHop;
} RoutingTableEntry;

typedef struct LookupEntry {
    std::string address;
} LookupEntry;

class Router {
public:
    Router(void) {}
    void Initialize(int, char **);
    void ParseRoutingTable(void);
    void ParseLookup(void);
    void PrintRoutingTable(void);
    void PrintLookup(void);
    void BuildTrie(void);
    void Lookup(void);

private:
    std::string routingTableFilename;
    std::string lookupFilename;

    std::ifstream routingTableFile;
    std::ifstream lookupFile;

    std::map<std::string, RoutingTableEntry> routingTable;
    std::vector<LookupEntry> lookup;
};

#endif//ROUTER_H
