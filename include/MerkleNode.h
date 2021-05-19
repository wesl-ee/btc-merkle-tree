#ifndef MERKLENODE_H
#define MERKLENODE_H

#include <string>
#include <vector>
#include <iostream>
#include "NodeHash.h"

/**
 * A single node in a Merkle tree at any depth
 */
class MerkleNode {
	public:

	/**
	 * Create an empty node
	 */
	MerkleNode();

	/**
	 * Create a leaf with a pre-computed hash in hex representation
	 */
	MerkleNode(const std::string hex);

	/**
	 * Assign this node as the parent of the left and right nodes
	 */
	void MakeParentOf(MerkleNode *left, MerkleNode *right);

	/**
	 * Textual representation of node's binary content
	 */
	std::string Content();

	/**
	 * Given the left and right child, compute this node's binary content
	 */
	void CalculateFromChildren();

	/**
	 * Left child
	 */
	MerkleNode *Left();

	/**
	 * Right child
	 */
	MerkleNode *Right();

	/**
	 * Raw binary content of node
	 */
	std::vector<std::byte> RawDigest();

	/**
	 * Parent this node to a given parent
	 */
	void SetParent(MerkleNode *p);

	/**
	 * Indicate that this node's content is represented in network (big endian)
	 * order
	 */
	void SetNetworkOrder(bool);

	private:

	/**
	 * Binary content of node
	 */
	NodeHash hash;

	/**
	 * Left child
	 */
	MerkleNode *left;

	/**
	 * Right child
	 */
	MerkleNode *right;

	/**
	 * Parented node
	 */
	MerkleNode *parent;
};

#endif
