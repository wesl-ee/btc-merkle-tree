Bitcoin Merkle Tree
===================

Illustrative C++ code showing how to construct a Merkle tree from a given group
of Bitcoin transaction hashes.

Executive Summary
-----------------

In the header of any Bitcoin block there is a field called the "Merkle root".
This is the root node of a [Merkle
tree](https://en.bitcoinwiki.org/wiki/Merkle_tree) constructed from each
transaction in the block. Merkle trees allow peers to verify that a given
transaction occured within a block without needing to run a full network node.

The use of Merkle trees in BTC is explained briefly in Chapter 8 ("Simplified
Payment Verification") of the [Bitcoin
whitepaper](https://bitcoin.org/bitcoin.pdf).

Building
--------

Please ensure CMake and OpenSSL are installed.

```
git clone 'https://github.com/wesleycoakley/btc-merkle-tree.git'
cd btc-merkle-tree
mkdir build; cd build
cmake ..
make
./btc-merkle-tree # (Edit TX IDs in `include/main.h`)
```

Method
------

For any given depth `D` of a BTC Merkle tree with `N` nodes, the nodes in the
`D - 1` layer are created by grouping the `N` nodes into pairs and
double-hashing the concatenation of their contents using SHA-256. If `N` is odd
the last pair is concatenated with itself and then double-hashed. The leaves of
a Merkle tree for a given block are the IDs of all transactions in the block.

The Merkle root, which is the top-most node of this tree, can be calculated by
performing this calculation for each depth.

License
-------

MIT License (available under `/LICENSE`)
