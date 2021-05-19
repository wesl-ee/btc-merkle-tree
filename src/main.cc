#include "main.h"

int main(int, char **) {
	auto tree = MerkleTree();
	tree.FromNetworkOrderHexSeeds(TX_IDS);
	tree.Print();
}

