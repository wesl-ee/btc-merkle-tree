#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <iostream>
#include <string>
#include <vector>
#include "MerkleNode.h"

/**
 * Collection of nodes at a given depth in a Merkle tree
 */
typedef std::vector<MerkleNode> MerkleTreeLevel;

/**
 * A full Merkle tree calculated from transactions in one BTC block
 */
class MerkleTree {
	public:

	/**
	 * Construct a Merkle tree given some set of network-order (big endian) hex
	 * strings. BTC transactions are conveniently network-order already.
	 * Changing the order of transactions will change the Merkle root!
	 */
	void FromNetworkOrderHexSeeds(const std::vector<std::string> leaves);

	/**
	 * Recursively walk a (sub)tree to calculate the Merkle root of the current
	 * node
	 */
	void CalculateSubtree(MerkleNode*);

	/**
	 * Summarize the entire tree
	 */
	void Print();

	/*
	 * Summarize a subtree whose root is the first argument
	 */
	void PrintSubtree(MerkleNode* root, unsigned int depth);

	private:

	/*
	 * Organize nodes by their depth
	 */
	std::vector<MerkleTreeLevel> treeLevels;

	/**
	 * The Merkle root is the top-most node of the Merkle tree
	 */
	MerkleNode *merkleRoot;

	/**
	 * Leaves from which the Merkle tree will be constructed
	 */
	std::vector<MerkleNode> leafNodes;

	/**
	 * Build the rest of the tree once leaves are loaded in
	 */
	void construct();
};

#endif
