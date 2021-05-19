#include "MerkleNode.h"

MerkleNode::MerkleNode() {
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

std::string MerkleNode::Content() {
	return hash.String();
}

MerkleNode *MerkleNode::Right() {
	return right;
}

MerkleNode *MerkleNode::Left() {
	return left;
}

void MerkleNode::SetNetworkOrder(bool b) {
	hash.SetNetworkOrder(b);
}

MerkleNode::MerkleNode(const std::string digest) {
	left = nullptr;
	right = nullptr;

	hash.Set(digest);
}

void MerkleNode::SetParent(MerkleNode *p) {
	parent = p;
}

std::vector<std::byte> MerkleNode::RawDigest() {
	return hash.Raw();
}

void MerkleNode::CalculateFromChildren() {
	hash.Calculate(left->RawDigest(), right->RawDigest());
}

void MerkleNode::MakeParentOf(MerkleNode *l, MerkleNode *r) {
	l->SetParent(this);
	r->SetParent(this);
	left = l;
	right = r;
}
