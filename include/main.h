#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include "MerkleTree.h"

/**
 * https://www.blockchain.com/btc/block/82747
 *
 * Merkle root
 * 5dc7e96501429df25873a43ad70bd8d9dedf2a432e330236eff600dcebcbdd03
 */
const static std::vector<std::string> TX_IDS = {
	"a0ee4c9066af0916e110391c7c7b33a4513de8cb94c304e305704aa4c9d11947",
	"10cf9efc4356ddc616a8cf5628ee8a3564e37a9cd9f4c7d103a88c15ddf6d2c0",
	"fdf09e486960fb4b649f9838c6bf076d321abae1a8d16795605edc70dfbafc3a",
	"ce7c126f69752425d638451c455b6dab2304004659bc4742139013abc415be53",
	"df56fe9d32474bfbb94d8e6c6d8a83739bbfbe6e6f017e642f40f2cadb1a203c",
	"501ff48af15c99c75334c0416bba672ffa3644789985ad5574a388547f3d9d9b"
};

#endif
