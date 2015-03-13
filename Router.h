#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>

#include "Trie.h"
#include "StringUtilities.h"
#include "Exception.h"

typedef struct RoutingTableEntry {
    std::string destination;
    unsigned int prefix;
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
    void PrintLookup(void);
private:
    std::string routingTableFilename;
    std::string lookupFilename;

    std::ifstream routingTableFile;
    std::ifstream lookupFile;

    std::vector<RoutingTableEntry> routingTable;
    std::vector<LookupEntry> lookup;
};

#endif//ROUTER_H
