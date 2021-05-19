#ifndef NODEHASH_H
#define NODEHASH_H

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <openssl/evp.h>

/**
 * Binary content of a node
 */
class NodeHash {
	public:
	/**
	 * Hash function used by BTC for Merkle trees (this is applied twice for
	 * BTC)
	 */
	const EVP_MD* (*HashType)() = &EVP_sha256;

	/**
	 * Set binary content from a pre-computed hex string
	 */
	void Set(const std::string&);

	/**
	 * Indicate if the binary content held here should be interpreted as
	 * network-order or as little endian data
	 */
	void SetNetworkOrder(bool);

	/**
	 * Calculate binary content by concatenating two data streams and
	 * double-hashing
	 */
	void Calculate(const std::vector<std::byte>&, const std::vector<std::byte>&);

	/**
	 * Textual representation of binary data stored in this hash
	 */
	std::string String() const;

	/**
	 * Binary data stored in this hash
	 */
	std::vector<std::byte> Raw() const;

	private:

	/**
	 * Translate hex string to an array of bytes
	 */
	static std::vector<std::byte> asRaw(const std::string&);

	/**
	 * Translate an array of bytes to a string of hex characters
	 */
	static std::string asHex(const std::vector<std::byte>);

	/**
	 * Interpret a single hex character as an integer
	 */
	static unsigned int hexDigitToInt(const char);

	/**
	 * Binary data stored in this hash
	 */
	std::vector<std::byte> digest;

	/**
	 * Should this data be interpreted as network-order (big endian) data when
	 * hashing?
	 */
	bool isNetworkOrder;
};

#endif
