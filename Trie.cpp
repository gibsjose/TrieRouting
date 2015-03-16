#include "Trie.h"
#include "StringUtilities.h"
#include "BitHacks.h"

uint32_t DecodeAddress(const std::string & address) {
    uint32_t decoded = 0;

    std::vector<std::string> addressStrings;
    char * addressData = (char *)malloc(4 * sizeof(char));

    addressStrings = StringUtilities::SplitString(address, ".");

    for(int i = 0; i < 4; i++) {
        char tmp = (char)atoi(addressStrings.at(i).c_str());
        addressData[3 - i] = tmp;
    }

    memcpy(&decoded, addressData, 4);

    free(addressData);

    return decoded;
}

// int main(int argc, char * argv[]) {
//     Trie trie;
//
//     trie.Insert("127.0.0.1", 24, 4, "255.255.255.255");
//     trie.Insert("127.0.0.1", 24, 2, "0.0.0.0");
//     trie.Insert("127.0.0.1", 24, 1, "10.10.10.10");
//     trie.Insert("192.168.0.1", 6, 4, "10.0.0.0");
//
//     std::string nextHop1 = trie.Get("127.0.0.1");
//     std::string nextHop2 = trie.Get("192.168.0.1");
//     std::string nextHop3 = trie.Get("0.0.0.0");
//
//     std::cout << "Next hop for 127.0.0.1 is " << nextHop1 << std::endl;
//     std::cout << "Next hop for 192.168.0.1 is " << nextHop2 << std::endl;
//     std::cout << "Next hop for 0.0.0.0 is " << nextHop3 << std::endl;
// }

//Insert an an entry into the Trie, overriding if more optimal
void Trie::Insert(const std::string & destination, const unsigned int prefix, const unsigned int size, const std::string & nextHop) {

    TrieNode * current = &root;

    //Convert destination address into integer
    uint32_t addr = DecodeAddress(destination);

    uint32_t mask = 0x80000000; //100000000000...

    //Advance nodes for each bit in prefix
    for(int i = 0; i < prefix; i++) {
        uint32_t bit = addr & mask;

        //Bit is '1'
        if(bit) {
            //std::cout << "1";
            if(current->GetOne() == NULL) {
                current->SetOne(new TrieNode());
            }

            current = current->GetOne();
        }

        //Bit is '0'
        else {
            //std::cout << "0";
            if(current->GetZero() == NULL) {
                current->SetZero(new TrieNode());
            }

            current = current->GetZero();
        }

        //Update mask
        mask = mask >> 1;
    }

    //First time inserting
    if(current->GetData().empty()) {
        current->SetData(nextHop);
        current->SetSize(size);
    }

    //Already data here, decide to swap or not
    else {
        //Replace if this size is smaller
        if(current->GetSize() > size) {
            current->SetData(nextHop);
            current->SetSize(size);
        }
    }
}

//Retreive the next hop address based on an input IP address
std::string Trie::Get(std::string address) {

    TrieNode * current = &root;

    //Decode address
    uint32_t addr = DecodeAddress(address);

    uint32_t mask = 0x80000000;

    std::string lastDataSeen = "NoMatch";

    for(int i = 0; i < 32; i++) {
        uint32_t bit = addr & mask;

        //Bit is '1'
        if(bit) {
            if(!current->GetData().empty()) {
                lastDataSeen = current->GetData();
            }

            current = current->GetOne();
        }

        //Bit is '0'
        else {
            if(!current->GetData().empty()) {
                lastDataSeen = current->GetData();
            }

            current = current->GetZero();
        }

        //Return last data seen if have fallen off trie
        if(current == NULL) {
            return lastDataSeen;
        }

        //Update mask
        mask = mask >> 1;
    }

    return lastDataSeen;
}
