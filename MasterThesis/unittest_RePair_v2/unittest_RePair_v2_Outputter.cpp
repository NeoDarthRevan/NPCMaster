#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(outputter, diddyHuffmanCode)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	string filename = input1;
	ifstream file(filename);

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));

	unordered_map<long, HuffmanNode> huffmanCodes;
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	unordered_map<long, unordered_map<long, long>> huffmanToSymbol;
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);

	out.huffmanEncoding(
		out.addFilenameEnding(input1, ".NPC"),
		sequenceArray,
		huffmanCodes,
		true);

	//Actual test
	string expected1 = "00000100100001110101010100001000";
	string expected2 = "00111001100111111110101000000000";
	string expected3 = "10000000000000000000000000001001";
	
	ifstream ifs;
	ifs.open("Compressed_diddy.txt", ios::binary);
	string result = "";
	string totalResult = "";
	char byte;
	bitset<8> *bits;
	int count = 0;

	if (ifs.is_open())
	{		
		while (ifs.get(byte))
		{
			bits = new bitset<8>(byte);

			for (int i = bits->size() - 1; i >= 0; --i)
			{
				if ((*bits)[i] == 0)
					result += "0";
				else
					result += "1";
			}
			if (result.size() == 32 && count == 0)
			{
				ASSERT_EQ(expected1, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 1)
			{
				ASSERT_EQ(expected2, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 2)
			{
				ASSERT_EQ(expected3, result);
				++count;
				totalResult += result;
				result = "";
			}
			delete bits;
		}
	}
	ASSERT_EQ(expected1 + expected2 +expected3, totalResult);
}

TEST(outputter, diddyHuffmanDictionary)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<vector<CompactPair>> pairs;
	unordered_map <long, unordered_map<long, long>> indices;
	string filename = input1;
	ifstream file(filename);

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);

	unordered_map<long, long> terminalIndices;
	vector<vector<CompactPair>> generationVectors;

	finalDict.generateCompactDictionary(
		dictionary,
		terminals,
		pairs,
		indices,
		terminalIndices,
		generationVectors);

	unordered_map<long, HuffmanNode> huffmanCodes;
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	unordered_map<long, unordered_map<long, long>> huffmanToSymbol;
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);

	string outstring = "testHuffmanDictionary";
	

	out.huffmanDictionary(
		outstring,
		maxLength,
		firstCode,
		numl,
		dictionary,
		indices,
		terminalIndices,
		huffmanToSymbol);

	//Actual test
	string expected1 = "11001010101100111001110011111000";
	string expected2 = "00111000111110010111011111000101";
	string expected3 = "11001011001111010011101100100111";
	string expected4 = "10010011100110000000000000000000";

	ifstream ifs;
	ifs.open(outstring, ios::binary);
	string result = "";
	string totalResult = "";
	char byte;
	bitset<8> *bits;
	int count = 0;

	GammaCode gc;

	if (ifs.is_open())
	{
		while (ifs.get(byte))
		{
			bits = new bitset<8>(byte);

			for (int i = bits->size() - 1; i >= 0; --i)
			{
				if ((*bits)[i] == 0)
					result += "0";
				else
					result += "1";
			}
			if (result.size() == 32 && count == 0)
			{
				ASSERT_EQ(expected1, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 1)
			{
				ASSERT_EQ(expected2, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 2)
			{
				ASSERT_EQ(expected3, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 3)
			{
				ASSERT_EQ(expected4, result);
				++count;
				totalResult += result;
				result = "";
			}
			delete bits;
		}
	}
	ASSERT_EQ(expected1 + expected2 + expected3 + expected4, totalResult);
	vector<long> resultVector;
	string prefix = "";
	gc.decodeGammaString(prefix, totalResult, resultVector, 21);

	ASSERT_EQ(21, resultVector.size());

	ASSERT_EQ(4, resultVector[0]);
	ASSERT_EQ(0, resultVector[1]);
	ASSERT_EQ(2, resultVector[2]);
	ASSERT_EQ(0, resultVector[3]);
	ASSERT_EQ(4, resultVector[4]);
	ASSERT_EQ(4, resultVector[5]);
	ASSERT_EQ(4, resultVector[6]);

	ASSERT_EQ(15, resultVector[7]);
	ASSERT_EQ(8, resultVector[8]);
	ASSERT_EQ(20, resultVector[9]);
	ASSERT_EQ(6, resultVector[10]);

	ASSERT_EQ(9, resultVector[13]);
	ASSERT_EQ(4, resultVector[14]);
	ASSERT_EQ(11, resultVector[15]);
	ASSERT_EQ(13, resultVector[16]);
	ASSERT_EQ(0, resultVector[17]);
	ASSERT_EQ(1, resultVector[18]);
	ASSERT_EQ(19, resultVector[19]);
	ASSERT_EQ(10, resultVector[20]);
}

TEST(outputter, diddyAll)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;

	string input1 = "diddy.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	unordered_map <long, unordered_map<long, long>> indices;
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
																		
	out.all(
		filename,
		firstBlock,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		c);

	string compressedFile = out.addFilenameEnding(filename, ".NPC");
	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");

	ifstream ifs;
	ifs.open(compressedFile, ios::binary);
	ASSERT_TRUE(ifs.is_open());
	ifs.close();

	ifs.open(compressedDictionary, ios::binary);
	ASSERT_TRUE(ifs.is_open());
	ifs.close();
}

TEST(outputter, readAndWriteDictionary_diddy)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;

	string input1 = "diddy.txt";
	string outstring = "testWriteDictionaryDiddy";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<vector<CompactPair>> pairs;
	unordered_map <long, unordered_map<long, long>> indices;
	unordered_map <long, long> terminalIndices;
	vector<vector<CompactPair>> generationVectors;
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);

	finalDict.generateCompactDictionary(dictionary, terminals, pairs, indices, terminalIndices, generationVectors);

	string finalstring = "";
	gc.makeFinalString(pairs, terminals, finalstring, generationVectors);

	out.dictionary(outstring, finalstring, true);

	vector<CompactPair> decodedPairs;
	vector<long> decodedTerms;
	ifstream bitstream(outstring, ios::binary);

	//Read file
	gc.decodeDictionaryFile(decodedPairs, decodedTerms, bitstream);

	bool isInOriginalPairVector;
	for (const auto p : decodedPairs)
	{
		isInOriginalPairVector = false;
		for (const vector<CompactPair> gen : pairs)
		{
			for (const auto p2 : gen)
			{
				if (p2.leftSymbol == p.leftSymbol && p2.rightSymbol == p.rightSymbol)
					isInOriginalPairVector = true;
			}
		}
		ASSERT_TRUE(isInOriginalPairVector);
	}

	int combinedSize = 0;
	for (const vector<CompactPair> gen : pairs)
	{
		combinedSize += gen.size();
	}
	ASSERT_EQ(combinedSize, decodedPairs.size());

	//ASSERT_EQ(terminals, decodedTerms);
}