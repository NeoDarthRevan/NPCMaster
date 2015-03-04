#include "Huffman.h"


Huffman::Huffman()
{
}


Huffman::~Huffman()
{
}

void Huffman::getFrequencies(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, HuffmanNode *> & frequencies,
	unsigned int &cardinality)
{
	for each (auto symbolRecord in sequenceArray)
	{
		if (symbolRecord->symbol != 0)
		{
			if (!frequencies[symbolRecord->symbol]){
				frequencies[symbolRecord->symbol] = new HuffmanNode(symbolRecord->symbol, 0);
				++cardinality;
			}
			frequencies[symbolRecord->symbol]->frequency++;
		}		
	}
}

void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild)
{
	char zero = '0';
	char one = '1';
	if (leftChild->symbol == 0)
	{
		leftChild->code += zero;
		leftChild->leftChild->code = leftChild->code;
		leftChild->rightChild->code = leftChild->code;

		unravel(leftChild->leftChild, leftChild->rightChild);
		delete leftChild;
	}
	else
	{
		leftChild->code += zero;
	}
	if (rightChild->symbol == 0)
	{
		rightChild->code += one;
		rightChild->leftChild->code = rightChild->code;
		rightChild->rightChild->code = rightChild->code;

		unravel(rightChild->leftChild, rightChild->rightChild);
		delete rightChild;
	}
	else
	{
		rightChild->code += one;
	}
}

void Huffman::sift(
	int currentNodeIndex,
	int heapSize,
	int *codeLengths)
{
	
	int leftChildIndex = ((currentNodeIndex + 1) * 2) - 1;
	int rightChildIndex = (((currentNodeIndex + 1) * 2) + 1) - 1;

	if (leftChildIndex >= heapSize)												//Stop the recursion
		return;

	int parentFrequency = codeLengths[codeLengths[currentNodeIndex]];
	int leftChildFrequency = codeLengths[codeLengths[leftChildIndex]];
	int rightChildFrequency = codeLengths[codeLengths[rightChildIndex]];

	if (rightChildIndex < heapSize &&
		leftChildFrequency > rightChildFrequency)
																				//Right child is smaller than left
	
	{
		if (parentFrequency > rightChildFrequency)
		{
																				//Swap with right child
			int tmpIndex = codeLengths[currentNodeIndex];
			codeLengths[currentNodeIndex] = codeLengths[rightChildIndex];
			codeLengths[rightChildIndex] = tmpIndex;

			sift(rightChildIndex, heapSize, codeLengths);
			
		}
	}
	else if (parentFrequency > leftChildFrequency)
																				//Left is smaller than right or right does not exist, 
																				//and left is smaller than parent
	{
																				//Swap with left child
		int tmpIndex = codeLengths[currentNodeIndex];
		codeLengths[currentNodeIndex] = codeLengths[leftChildIndex];
		codeLengths[leftChildIndex] = tmpIndex;

		sift(leftChildIndex, heapSize, codeLengths);
	}
}

void Huffman::initCodeLengthsArray(
	int cardinality,
	int *codeLengths,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes)
{
	int i = 0;
	for each (auto node in huffmanCodes)
	{
		codeLengths[cardinality + i] = node.second->frequency;
		codeLengths[i] = cardinality + i;										//Index of a symbol Points to the symbol's frequency
		++i;
	}
}

void Huffman::initMinHeap(
	int heapSize,
	int *codeLengths)
{
	int currentNodeIndex = heapSize - 1;										//Last node
	currentNodeIndex = currentNodeIndex / 2;									//Parent of last node

	while (currentNodeIndex >= 0)
	{
		sift(currentNodeIndex, heapSize, codeLengths);
		--currentNodeIndex;
	}
}

void Huffman::collapseHuffmanTree(
	int heapSize,
	int *codeLengths)
{
	int m1;
	int m2;

	while (heapSize > 1)
	{
		//a)
		m1 = codeLengths[0];													//Take symbol with smallest frequency
		codeLengths[0] = codeLengths[heapSize - 1];								//Pull last element to front of heap
		--heapSize;																

		//b)
		sift(0, heapSize, codeLengths);											//Sift the last element down through the heap
		m2 = codeLengths[0];													//Take symbol with next smallest frequency

		//c)
		codeLengths[(heapSize - 1) + 1] = codeLengths[m1] + codeLengths[m2];	//Create new frequency for combination of two smallest frequencies
		codeLengths[0] = (heapSize - 1) + 1;									//"Create" new symbol pointing to the new frequency
		codeLengths[m1] = (heapSize - 1) + 1;									//Point to new symbol
		codeLengths[m2] = (heapSize - 1) + 1;									//Point to new symbol

		//d)
		sift(0, heapSize, codeLengths);											//Sift the new element down through the heap
	}
}

void Huffman::expandHuffmanTree(
	unsigned int cardinality,
	int *codeLengths,
	unsigned int &maxLength)
{
	codeLengths[1] = 0;															//Represents the root with code length one
	maxLength = 0;
	for (int i = 2; i < cardinality * 2; i++)
	{
		codeLengths[i] = codeLengths[codeLengths[i]] + 1;						//Nodes will get codes of length one greater than their parents
		if (codeLengths[i] > maxLength)
			maxLength = codeLengths[i];
	}
}

void Huffman::getCodeLengths(
	unsigned int cardinality,
	int *codeLengths,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
	unsigned int &maxLength)																//Assigns a value to maxLength as an output
{
	int heapSize = cardinality;
	//Phase 1	
	initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);
	initMinHeap(heapSize, codeLengths);
	//Phase 1  - end

	collapseHuffmanTree(heapSize, codeLengths);

	expandHuffmanTree(cardinality, codeLengths, maxLength);
}

string Huffman::codeToString(int intCode, int length)
{
	string stringCode = "";
	for (int i = length - 1; i >= 0; --i)
	{
		int v = intCode & (1 << i);
		if (v == 0)
			stringCode += "0";
		else
			stringCode += "1";
	}
	return stringCode;
}

void Huffman::generateCanonicalHuffmanCodes(
	unsigned int cardinality,
	unsigned int maxLength,
	int *codeLengths,
	unsigned int *firstCode,
	unsigned int *numl,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &huffmanToSymbol)
{
	for (int i = 0; i < maxLength; i++)											//Init codelengths with zero
		numl[i] = 0;
	
	for (int i = cardinality; i < cardinality * 2; i++)							//Count number of codes with same length
		++numl[codeLengths[i] - 1];

	firstCode[maxLength - 1] = 0;

	for (int i = maxLength - 2; i >= 0; --i)									//Calculates value of first code for each code length
		firstCode[i] = (firstCode[i + 1] + numl[i + 1]) / 2;
	
	int *nextCode = new int[maxLength];

	for (int i = 0; i < maxLength; i++)											
		nextCode[i] = firstCode[i];

	int i = 0;
	for each (auto huffmanNode in huffmanCodes)									//For each symbol, look up its code by its length in the nextcode structure 
	{
		int codeLength = codeLengths[cardinality + i];
		string code = codeToString(nextCode[codeLength - 1], codeLength);
		huffmanNode.second->code = code;
		if (!huffmanToSymbol[codeLength])
			huffmanToSymbol[codeLength] = new unordered_map<unsigned int, unsigned int>();
		(*huffmanToSymbol[codeLength])[nextCode[codeLength - 1]] = huffmanNode.first;
		++nextCode[codeLength - 1];
		++i;
	}

	delete[] nextCode;
}

void Huffman::encode(
	vector<SymbolRecord*> &sequenceArray,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
	unsigned int *&firstCode,
	unsigned int *&numl,
	unsigned int &maxLength,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &huffmanToSymbol)
{	
	unsigned int cardinality = 0;
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
	getFrequencies(sequenceArray, huffmanCodes, cardinality);					//+ cardinality of compressed sequence
	int *codeLengths = new int[cardinality * 2];	
	getCodeLengths(cardinality, codeLengths, huffmanCodes, maxLength);

	firstCode = new unsigned int[maxLength];
	numl = new unsigned int[maxLength];
	generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, firstCode, numl, huffmanCodes, huffmanToSymbol);

	delete[] codeLengths;
}

void Huffman::fillBitset(int rawChunk, bitset<32> *chunk)
{
	for (int i = 0; i < 32; i++)
	{
		int v = rawChunk & (1 << i);
		if (v == 0)
			chunk->set(i, false);
		else
			chunk->set(i, true);
	}
}

void Huffman::fillBitset(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, bitset<32> *chunk)
{	
	char rawChunk = rawChunk4;
	
	for (int i = 0; i < 32; i++)
	{
		if (i == 8)
			rawChunk = rawChunk3;
		if (i == 16)
			rawChunk = rawChunk2;
		if (i == 24)
			rawChunk = rawChunk1;

		int v = rawChunk & (1 << (i % 8));					//Read one bit from the current char sized chunk
		if (v == 0)
			chunk->set(i, false);
		else
			chunk->set(i, true);
	}	
}

void Huffman::fillString(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, string &chunk)
{
	char rawChunk = rawChunk1;
	chunk = "";

	for (int i = 0; i < 32; i++)
	{
		if (i == 8)
			rawChunk = rawChunk2;
		if (i == 16)
			rawChunk = rawChunk3;
		if (i == 24)
			rawChunk = rawChunk4;

		int v = rawChunk & (1 << (7 - (i % 8)));									//Read one bit from the current char sized chunk
		if (v == 0)
			chunk += '0';
		else
			chunk += '1';
	}
}

void Huffman::decodeDictionary(
	ifstream &bitstream,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> *symbolIndices)
	//Outputs symbolIndices
{
	GammaCode gc;
	//void GammaCode::gammaToInt (string &prefix, string gamma, vector<unsigned int> actual, unsigned int count);
	if (bitstream.is_open())
	{
		char rawChunk1 = 0;
		char rawChunk2 = 0;
		char rawChunk3 = 0;
		char rawChunk4 = 0;
		string chunk = "";
		string prefix = "";
		unsigned int maxLength = 0;
		unsigned int symbolsToRead = 0;
		unsigned int firstCode = 0;
		unsigned int lastCode = 0;
		vector<unsigned int> intValues;
		symbolsToRead = 1;
		
		while (intValues.size() < symbolsToRead)									//TODO: move this to helper function!!!!!!!!!!!!!!!!!!!!!11
		{
			if (!bitstream.eof())
			{
				bitstream.get(rawChunk1);
				bitstream.get(rawChunk2);
				bitstream.get(rawChunk3);
				bitstream.get(rawChunk4);
				fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);
			}
			else
				chunk = "";

			gc.decodeGammaString(prefix, chunk, intValues, symbolsToRead);
		}

		maxLength = intValues[0];
		intValues.clear();													

		//symbolIndices: code length -> Huffman code -> index
		for (unsigned int i = 0; i < maxLength; i++)
		{
			//Read the number of codes of length i + 1 and the first code of that length
			symbolsToRead = 2;
			while (intValues.size() < symbolsToRead)
			{
				if (!bitstream.eof())
				{
					bitstream.get(rawChunk1);
					bitstream.get(rawChunk2);
					bitstream.get(rawChunk3);
					bitstream.get(rawChunk4);
					fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);
				}
				else
					chunk = "";
				
				gc.decodeGammaString(prefix, chunk, intValues, symbolsToRead);
			}

			symbolsToRead = intValues[0];								
			firstCode = intValues[1];
			if (symbolsToRead > 0)
				lastCode = firstCode + symbolsToRead - 1;						//Find the last code for this size of code,
																				//this is used for efficiency when resetting intValues below
			intValues.clear();													//Reset the vector holding values already used

			//Read the corresponding i + 1 sequence indexes
			while (intValues.size() < symbolsToRead)
			{
				if (!bitstream.eof())
				{
					bitstream.get(rawChunk1);
					bitstream.get(rawChunk2);
					bitstream.get(rawChunk3);
					bitstream.get(rawChunk4);
					fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);
				}
				else
					chunk = "";
				gc.decodeGammaString(prefix, chunk, intValues, symbolsToRead);
			}

			//Add sequence indexes to dictionary based on Huffman code length
			while (intValues.size() > 0)
			{
				(*symbolIndices)[i + 1][lastCode] = intValues[intValues.size() - 1];
				--lastCode;
				intValues.pop_back();											//Remove index we already processed
			}
		}
	}
}

void Huffman::decode(
	unsigned int *firstCode,
	string filename,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> *symbolIndices,
	vector<unsigned int> &symbolIndexSequence)
{
	ifstream bitstream(filename, ios::binary);
	if (bitstream.is_open())
	{
		int length = 0;
		int value;
		char rawChunk1 = 0;
		char rawChunk2 = 0;
		char rawChunk3 = 0;
		char rawChunk4 = 0;
		bitset<32> *chunk = new bitset<32>();
		bitset<32> *nextChunk = new bitset<32>();
		int bitIndexMax = 30;		
		int currentBitIndex = bitIndexMax;
		int padding = 0;
		bool endOfBlock = false;

		bitstream.get(rawChunk1);													//Read first chunk
		bitstream.get(rawChunk2);
		bitstream.get(rawChunk3);
		bitstream.get(rawChunk4);
		fillBitset(rawChunk1, rawChunk2, rawChunk3, rawChunk4, nextChunk);

		while (!endOfBlock)
		{
			//Read chunks of data from file
			for (int i = 0; i < 32; i++)
			{
				chunk->set(i, nextChunk->test(i));
			}
			
			bitstream.get(rawChunk1);													
			bitstream.get(rawChunk2);
			bitstream.get(rawChunk3);
			bitstream.get(rawChunk4);
			fillBitset(rawChunk1, rawChunk2, rawChunk3, rawChunk4, nextChunk);

			currentBitIndex = bitIndexMax;

			if (nextChunk->test(bitIndexMax + 1))									//Last chunk
			{
				endOfBlock = true;

				//read number of padding bits from last block
				nextChunk->set(bitIndexMax + 1, false);
				padding = nextChunk->to_ulong();
			}
			
			while (currentBitIndex >= padding)
			{
				//Canonical Huffman decoding, init for new symbol
				if (length == 0)
				{
					length = 1;
					value = (*chunk)[currentBitIndex];
					--currentBitIndex;
				}				

				while (value < firstCode[length - 1] && currentBitIndex >= padding)		//Read bits until we find a symbol
				{
					value = 2 * value + (*chunk)[currentBitIndex];
					--currentBitIndex;
					++length;
				}

				if (value >= firstCode[length - 1])
				{
					unsigned int symbolIndex = (*symbolIndices)[length][value];
					symbolIndexSequence.push_back(symbolIndex);
					length = 0;
					value = 0;
				}
			}
		}
		delete chunk;
		delete nextChunk;
	}
}