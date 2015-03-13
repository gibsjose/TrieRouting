#Lab 7 Notes:

###Router
* Routing Table
    * Entry Example:
    ```
    16.15.0.0/16 | 34   303     115     24 | 1.2.3.4
    ```

    Format:
    ```
    {DEST ADDR PREFIX}  | {'AS PATH': NETWORK ID OF INTERMEDIATE NODES}  | {NEXT LOCATION TO ROUTE TO}
    ```

    `DEST ADDR PREFIX`: Any address with first 16 bits matching this prefix

    * Can have multiple entries with the same prefix:
    ```
    16.15.0.0/16 | 4343    11    24 | 3.4.5.6
    ```

        * This is a shorter path, which is better!

* Forwarding Table
    * Chooses the entry with the shortest path from the routing table for each prefix
    * No longer need AS Path in forwarding table (was only used to select from routing table)
    * Need:
        * Destination prefix
        * Next hop
    * Data Structure:
        * **'Trie'**
        * Similar to a normal tree
        * Each node will have:
            * Left *
            * Right *
            * Data
        * All could be empty...

        * Ex: Prefix: (16.15....), only convert first 16 because it is .../16, if it was /18, would take first 18 bits
            * `00010000 00001111 ...`

        * Bits are labels on edges from root, choosing between `0` and `1` each step based on prefix address in binary

        * In **last** node, that is where we store `NEXT HOP` information (ex: `3.4.5.6`)

        * Ex 2:

        Prefix 00       -> A
        Prefix 001      -> B
        Prefix 00101    -> C
        Prefix 111      -> D
        Prefix 110      -> E
        Prefix 1101     -> F

        * Selection from Trie
            1. Follow until you fall off the tree and back up until you hit an address
            2. If you fall off and there is no answer to back up to, then there is no answer

        * Multibit Trie
        * Must choose a 'stride length'
        * Ex: Stride length = 2, then take 2 bits at a time
        * If odd length prefix and even length stride, then both paths from parent result in node
            * Results in collisions... (ex: E and F)
            * Should *really* have `F`, not `E`: Interested in more specific match (matches more bits)
            * Therefore, always take whichever has longer prefix length
