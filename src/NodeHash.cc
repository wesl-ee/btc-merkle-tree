#include "NodeHash.h"

void NodeHash::Calculate(const std::vector<std::byte> &left, const std::vector<std::byte> &right) {

	std::byte *from, *to;
	unsigned int md_len, md_intermediate_len;

	unsigned char md_value[EVP_MAX_MD_SIZE], md_intermediate[EVP_MAX_MD_SIZE];
	auto mdctx = EVP_MD_CTX_create();

	EVP_DigestInit_ex(mdctx, HashType(), NULL);

	/* Calculate hash of the concatenation of left and right data streams */
	for (auto node : std::initializer_list<std::vector<std::byte>>{left, right}) {
		if (isNetworkOrder)
			std::reverse(node.begin(), node.end());
		EVP_DigestUpdate(mdctx, node.data(), node.size());
	}
	EVP_DigestFinal_ex(mdctx, md_intermediate, &md_intermediate_len);

	/* BTC uses a double-hash to mitigate length-extension attacks */
	EVP_DigestInit_ex(mdctx, HashType(), NULL);
	EVP_DigestUpdate(mdctx, md_intermediate, md_intermediate_len);
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);

	from = (std::byte*)(md_value);
	to = (std::byte*)(md_value + md_len);
	digest = std::vector<std::byte>(from, to);

	if (isNetworkOrder)
		std::reverse(digest.begin(), digest.end());

	EVP_MD_CTX_destroy(mdctx);
}

void NodeHash::SetNetworkOrder(bool b) {
	isNetworkOrder = b;
}

std::string NodeHash::String() const {
	auto ret = digest;
	return asHex(ret);
}

std::vector<std::byte> NodeHash::Raw() const {
	return digest;
}

void NodeHash::Set(const std::string &hex) {
	digest = asRaw(hex);
}

std::vector<std::byte> NodeHash::asRaw(const std::string &from) {
	unsigned int at, lower, higher;
	std::byte digit;
	std::vector<std::byte> ret;

	/* One byte at a time */
	for (at = 0; at < from.length(); at += 2) {
		if (from.size() - at < 2) {
			lower = hexDigitToInt(from.at(at));
			digit = (std::byte)(lower);
		} else {
			higher = hexDigitToInt(from.at(at));
			lower = hexDigitToInt(from.at(at + 1));
			digit = (std::byte)(lower + higher * 16);
		}

		ret.push_back(digit);
	}

	return ret;
}


std::string NodeHash::asHex(const std::vector<std::byte> from) {
	unsigned int first, second;
	std::string hexStr;

	for (auto b : from) {
		first = (unsigned char)b & 15;
		second = ((unsigned char)b & 240) >> 4;

		for (auto &place : std::initializer_list({second, first})) {
			if (place <= 9)
				hexStr += place + '0';
			else
				hexStr += place - 10 + 'A';
		}
	}
	return hexStr;
}

unsigned int NodeHash::hexDigitToInt(const char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return 16;
}

