#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>
#include <map>

#include "Trie.h"
#include "StringUtilities.h"
#include "Exception.h"

class Router {
public:
    Router(void) {}
    void Initialize(int, char **);
    void ParseRoutingTable(void);
    void ParseLookup(void);
    void PrintLookup(void);
    void Lookup(void);

private:
    std::string routingTableFilename;
    std::string lookupFilename;

    std::ifstream routingTableFile;
    std::ifstream lookupFile;

    Trie trie;
    std::vector<std::string> lookup;
};

#endif//ROUTER_H
