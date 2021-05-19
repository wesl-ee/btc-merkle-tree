#include "MerkleTree.h"

void MerkleTree::FromNetworkOrderHexSeeds(const std::vector<std::string> leaves) {
	/* Construct the bottom level (just leaves) */
	for (auto &leafVal : leaves) {
		auto curr = MerkleNode(leafVal);
		curr.SetNetworkOrder(true);
		leafNodes.push_back(curr);
	}

	/* Build the rest of the tree */
	construct();
}

void MerkleTree::construct() {
	merkleRoot = nullptr;

	/* Seed the tree's bottom level with leaves */
	treeLevels = std::vector<MerkleTreeLevel>();
	treeLevels.push_back(leafNodes);

	MerkleNode *left, *right;
	for (auto currLevel = &treeLevels.at(0); currLevel->size() > 1; ) {
		bool oddLevel = false;
		MerkleTreeLevel nextLevel;
		/* Construct parent nodes until we reach root */
		auto it = currLevel->begin();
		while (!(it == currLevel->end() || oddLevel)) {
			/* Consider a pair of adjacent nodes */
			left = &(*it++);
			right = &(*it++);

			/* ...give them a parent */
			nextLevel.push_back(MerkleNode());
			MerkleNode *parent = &nextLevel.back();

			/* Pair left element with itself if otherwise unpaired */
			if (right == &(*currLevel->end())) {
				oddLevel = true;
				right = left;
			}

			/* Parent these adjacent nodes to a node in the above level */
			parent->MakeParentOf(left, right);
		}

		/* Finalize this level of the tree and start on next one */
		treeLevels.push_back(nextLevel);
		currLevel = &treeLevels.back();
	}

	/* The top-most element will always be the merkle root */
	merkleRoot = &treeLevels.back().back();

	/* Calculate the hash of the merkle root recursively */
	CalculateSubtree(merkleRoot);
}

void MerkleTree::CalculateSubtree(MerkleNode *node) {
	if (node->Left() == nullptr)
		return;

	CalculateSubtree(node->Left());
	CalculateSubtree(node->Right());

	node->CalculateFromChildren();
}

void MerkleTree::PrintSubtree(MerkleNode *node, unsigned int level) {
	std::string leader;

	/* Indentation */
	leader += std::string(level * 2, ' ');
	leader += "+ ";

	std::cout << leader << node->Content() << std::endl;

	/* Walk child trees */
	if (node->Left() != nullptr)
		PrintSubtree(node->Left(), level + 1);
	if (node->Right() != nullptr && node->Right() != node->Left())
		PrintSubtree(node->Right(), level + 1);
	return;
}

void MerkleTree::Print() {
	/* Render tree from the top-most node */
	PrintSubtree(merkleRoot, 0);
}

