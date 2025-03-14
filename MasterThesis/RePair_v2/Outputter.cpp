#include "stdafx.h"
#include "Outputter.h"

using namespace std;

Outputter::Outputter()
{
}


Outputter::~Outputter()
{
}

string Outputter::createName(string inputFile, string addName)
{
	string outFile = "";
	int i = 0;
	int empty = 0;

	outFile += addName;
	outFile += "_";

	while (inputFile[i] != '.')
		outFile += inputFile[i++];	

	while (inputFile[i] != empty)
		outFile += inputFile[i++];

	return outFile;
}

string Outputter::addFilenameEnding(string inputFile, string addName)
{
	inputFile += addName;
	return inputFile;
}

void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite)
{
	int n = bitsToWrite->size() / 8;
	for (int i = n - 1; i>=0; --i) {
		uint8_t byte = 0;
		for (int j = 7; j>=0; --j)
			byte = (byte << 1) | (*bitsToWrite)[i * 8 + j];
		myfile.write((char*)&byte, 1);
	}
}

void Outputter::writeChunkFromString(ofstream &myfile, string chunk)
{
	for (int i = 0; i <= 3; ++i) 
	{
		uint8_t byte = 0;
		for (int j = 0; j <= 7; ++j)
		{
			byte = (byte << 1) | (chunk[i * 8 + j] == '1');
		}
		myfile.write((char*)&byte, 1);
	}
}

void Outputter::huffmanEncoding(
	string outFile,
	ofstream &myfile,
	vector<SymbolRecord *>& sequenceArray,
	dense_hash_map<unsigned long, HuffmanNode> &huffmanCodes,
	bool firstBlock,
	Conditions & c)
{
	bitset<32> *bitsToWrite = new bitset<32>();
	short chunkSize = sizeof(bitset<32>) * CHAR_BIT; //Bitset outputs a certain minimum nr of bytes
	string chunk = "";
	string specialBit = "0";
	string code = "";
	long seqIndex = 0;
	long codeIndex = 0;
	short paddingBits = 0;

	//Write chunks of Huffman codes until an entire block is processed
	while (seqIndex < sequenceArray.size())
	{
		//Start new chunk
		chunk += specialBit;
		while (chunk.size() < chunkSize && seqIndex < sequenceArray.size())
		{
			if (codeIndex == code.size() || code.size() == 0) //Current code is processed but chunk is not full
			{
				while (seqIndex < sequenceArray.size() && sequenceArray[seqIndex]->symbol == 0)
					seqIndex++;
				
				if (seqIndex < sequenceArray.size())
				{
					code = huffmanCodes[sequenceArray[seqIndex++]->symbol].code;
					codeIndex = 0;
				}				
			}

			while (
				chunk.size() < chunkSize && 
				codeIndex < code.size())
				//Process Huffman code for current symbol
			{
				chunk += code[codeIndex++];
			}	
		}

		//Write chunk and reset for next chunk
		//If last symbol then do not write yet as we need to pad the chunk, unless this chunk is full
		if (seqIndex < sequenceArray.size() || chunk.size() == chunkSize)
		{
			writeChunkFromString(myfile, chunk);
			if (c.test)
				c.ts->c_sequence += 4;
			chunk = "";
		}
	}
	//Add the last part of the code for the last symbol to current chunk if necessary
	while (codeIndex != code.size() && code.size() != 0)
	{
		if (chunk.size() == 0)
			chunk += "0";
		chunk += code[codeIndex++];
	}

	//Add padding bits on the last actual chunk if there was not enough code to fill it out
	paddingBits = chunkSize - chunk.size();
	while (chunk.size() < chunkSize)
	{
		chunk += "0";
	}

	//Write the last actual chunk
	writeChunkFromString(myfile, chunk);
	if (c.test)
		c.ts->c_sequence += 4;
	chunk = "";

	//Write padding chunk
	delete bitsToWrite;
	bitsToWrite = new bitset<32>(paddingBits);
	bitsToWrite->set(bitsToWrite->size() - 1, true);
	writeChunk(myfile, bitsToWrite);
	if (c.test)
		c.ts->c_sequence += 4;
	delete bitsToWrite;

	if (firstBlock)
		cout << "created compressed file: " << outFile << endl;
}

void Outputter::writeBuffer(
	ofstream &myfile,
	string &gammaCodes,
	string &stringToWrite,
	Conditions &c)
{
	while (gammaCodes.size() >= 32)											//Write as much as possible to file
	{
		stringToWrite = gammaCodes.substr(0, 32);
		gammaCodes = gammaCodes.substr(32, string::npos);

		writeChunkFromString(myfile, stringToWrite);			//Write 4 bytes of the sequence of gamma codes
		if (c.test)
			c.ts->c_huffmanDictionary += 4;
	}
}

void Outputter::huffmanDictionary(
	string outFile,
	ofstream &myfile,
	long maxLength,
	long *firstCode,
	long *numl,
	vector<unsigned long> terminalVector,
	dense_hash_map<unsigned long, Pair> &dictionary,
	dense_hash_map<unsigned long, unsigned long> &indices,
	dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> &huffmanToSymbol,
	Conditions &c)
{
	GammaCode gc;
	Dictionary dict;

	string gammaCodes = "";
	string toWrite = "";
	string stringToWrite;

	
	gammaCodes += gc.getGammaCode(maxLength);									//Write this many "items"
	
	writeBuffer(
		myfile,
		gammaCodes,
		stringToWrite,
		c);

	for (long i = 0; i < maxLength; i++)
	{
		toWrite = gc.getGammaCode(numl[i]);
		
		gammaCodes += toWrite;													//Convert number of codes of this length to gamma code
																				//and append to the string of codes we want to write.
		toWrite = gc.getGammaCode(firstCode[i]);
		
		gammaCodes += toWrite;													//Convert the value of the first code as well

		for (int j = 0; j < numl[i]; j++)
		{
			long symbol = huffmanToSymbol[i + 1][firstCode[i] + j];
			long index;
			if (symbol >= initialSymbolValue)
			{
				index = indices[symbol];
			}
			else
				index = dict.findTerminalIndex(terminalVector, symbol);
			
			toWrite = gc.getGammaCode(index);
			gammaCodes += toWrite;	//Write the index corresponding to a specific huffman code (as gamma code)

			writeBuffer(
				myfile,
				gammaCodes,
				stringToWrite,
				c);
		}

		writeBuffer(
			myfile,
			gammaCodes,
			stringToWrite,
			c);
	}
	if (gammaCodes.size() != 0)
	{
		while (gammaCodes.size() < 32)
		{
			gammaCodes += '0';
		}
		writeChunkFromString(myfile, gammaCodes);						//Write the last gamma codes and possibly padding
		if (c.test)
			c.ts->c_huffmanDictionary += 4;
	}
}

void Outputter::compressedFile(
	string inputFile,
	vector<SymbolRecord>& sequenceArray,
	bool firstBlock)
{
	ofstream myfile;
	string outFile = createName(inputFile, "CompressedNoHuffman");

	if (firstBlock)
		myfile.open(outFile, ios::trunc);
	else
		myfile.open(outFile, ios::app);

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i].symbol != 0)
			myfile << sequenceArray[i].symbol;
	}
	myfile << UINT_MAX;
	myfile.close();

	if (firstBlock)
		cout << "created compressed file (no Huffman): " << outFile << endl;
}

void Outputter::dictionary(
	string outFile,
	ofstream &myfile,
	string& output,
	bool firstBlock,
	Conditions &c)
{
	string stringToWrite, rest;
	rest.assign(output);

	//Write as much as possible to file
	while (rest.size() >= 32)
	{ 
		//Write 4 bytes of the sequence of gamma codes
		stringToWrite = rest.substr(0, 32);
		rest = rest.substr(32, string::npos);
		writeChunkFromString(myfile, stringToWrite);
		if (c.test)
			c.ts->c_dictionary += 4;
	}

	//Write the last bit, if any is left
	if (rest != "")
	{
		while (rest.size() < 32)
		{
			rest += '0';
		}
		writeChunkFromString(myfile, rest);
		if (c.test)
			c.ts->c_dictionary += 4;
	}

	if (firstBlock)
		cout << "created dictionary file: " << outFile << endl;
}

void Outputter::writeDictionaryChunk(ofstream &myfile, string &inchunk, bitset<32> *&bitsToWrite)
{
	//DEBUG
	string chunk = inchunk.substr(0, 32);
	inchunk = inchunk.substr(32, string::npos);
	for (int i = 0; i < 32; i++)
	{
		if (chunk[i] == '1')
			bitsToWrite->set(31 - i, true);
		else
			bitsToWrite->set(31 - i, false);
	}

	writeChunk(myfile, bitsToWrite);
}

void Outputter::dictionary2(
	string outFile,
	ofstream &myfile,
	vector<vector<unsigned long>>& pairVectors,
	dense_hash_map<unsigned long, Pair>& dictionary,
	vector<unsigned long>& terminalVector,
	bool firstBlock,
	Conditions &c)
{
	bitset<32> *bitsToWrite = new bitset<32>();
	GammaCode gc;
	string output;

	//Set terminal header
	output = gc.getGammaCode(terminalVector.size());

	//Write terminals
	for (int i = 0; i < terminalVector.size(); ++i)
	{
		output += gc.getGammaCode(terminalVector[i]);
		while (output.size() >= 32)
		{
			writeDictionaryChunk(myfile, output, bitsToWrite);
			if (c.test)
				c.ts->c_dictionary += 4;
		}

	}

	//Then a header w/ number of generations
	output += gc.getGammaCode(pairVectors.size());
	while (output.size() >= 32)
	{
		writeDictionaryChunk(myfile, output, bitsToWrite);
		if (c.test)
			c.ts->c_dictionary += 4;
	}


	//Then for each generation
	int maxIndex = terminalVector.size() - 1;
	for (int gen = 0; gen < pairVectors.size(); ++gen)
	{
		//Header is size of generation + max possible index found in that generation
		output += gc.getGammaCode(pairVectors[gen].size()) + gc.getGammaCode(maxIndex);
		while (output.size() >= 32)
		{
			writeDictionaryChunk(myfile, output, bitsToWrite);
			if (c.test)
				c.ts->c_dictionary += 4;
		}

		//Write first left element
		output += gc.getGammaCode(dictionary[pairVectors[gen][0]].leftSymbol);
		while (output.size() >= 32)
		{
			writeDictionaryChunk(myfile, output, bitsToWrite);
			if (c.test)
				c.ts->c_dictionary += 4;
		}

		//Write differences between remaining lefts
		for (int i = 1; i < pairVectors[gen].size(); ++i)
		{
			output += gc.getGammaCode((dictionary[pairVectors[gen][i]].leftSymbol - dictionary[pairVectors[gen][i - 1]].leftSymbol));
			while (output.size() >= 32)
			{
				writeDictionaryChunk(myfile, output, bitsToWrite);
				if (c.test)
					c.ts->c_dictionary += 4;
			}
		}

		//Write rights
		int binarySize = 1 + floor(log2(maxIndex));
		for (int i = 0; i < pairVectors[gen].size(); ++i)
		{
			string binary = gc.getBinaryCode(dictionary[pairVectors[gen][i]].rightSymbol);
			while (binary.size() < binarySize)
				binary = '0' + binary;
			output += binary;
			while (output.size() >= 32)
			{
				writeDictionaryChunk(myfile, output, bitsToWrite);
				if (c.test)
					c.ts->c_dictionary += 4;
			}
		}

		//Increase maxindex by the size of the generation
		maxIndex += pairVectors[gen].size();
	}
	if (output.size() != 0)
	{
		while (output.size() < 32)
		{
			output += '0';
		}
		writeDictionaryChunk(myfile, output, bitsToWrite);						//Write the last gamma codes and possibly padding
		if (c.test)
			c.ts->c_dictionary += 4;
	}
}

void Outputter::all(
	string filename,
	bool firstBlock,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long, Pair>& dictionary,
	unordered_set<unsigned long>& terminals,
	Conditions& c)
{

	//Create names for output files
	string compressedFilename = this->addFilenameEnding(filename, ".NPC");
	string compressedDictionaryName = this->addFilenameEnding(filename, ".dict.NPC");

	ofstream ofs_compressed;
	if (firstBlock)
		ofs_compressed.open(compressedFilename, ios::binary | ios::trunc);
	else
		ofs_compressed.open(compressedFilename, ios::binary | ios::app);

	ofstream ofs_dictionary;
	if (firstBlock)
		ofs_dictionary.open(compressedDictionaryName, ios::binary | ios::trunc);
	else
		ofs_dictionary.open(compressedDictionaryName, ios::binary | ios::app);

	//Do Huffman encoding
	Huffman h;
	dense_hash_map<unsigned long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);

	//Generate Huffman codes
	if (c.test) //Carry over data structures
	{
		c.ts->addMemory("huffEncSeq", c.ts->m_repair_sequenceArray_current);
		c.ts->addMemory("huffEncDictionary", c.ts->m_repair_dictionary_max);
		c.ts->addMemory("huffEncTerminals", c.ts->m_repair_terminals_max);
	}
	if (c.test)
	{
		c.ts->testTimer.start();
	}

	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol, c);
	if (c.test)
	{
		c.ts->testTimer.stop();
		c.ts->t_huffmanEncoding += c.ts->testTimer.getTimeNano();
	}

	//Encode sequence array and write it to file
	if (c.test)
	{
		c.ts->testTimer.start();
	}

	this->huffmanEncoding(
		compressedFilename,
		ofs_compressed,
		sequenceArray,
		huffmanCodes,
		firstBlock,
		c);
	if (c.test)
	{
		c.ts->testTimer.stop();
		c.ts->t_encodeSequence += c.ts->testTimer.getTimeNano();
	}

	//Encode generations for dictionary
	Dictionary finalDict;
	vector<vector<unsigned long>> pairs;
	dense_hash_map<unsigned long, unsigned long> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	vector<unsigned long> terminalVector;

	if (c.test) //Carry over data structures
	{
		c.ts->addMemory("norDicSeq", c.ts->m_huffEnc_sequenceArray_current);
		c.ts->addMemory("norDicDictionary", c.ts->m_huffEnc_dictionary_max);
		c.ts->addMemory("norDicFirstCodes", c.ts->m_huffEnc_firstCodes_max);
		c.ts->addMemory("norDicNrOfCodes", c.ts->m_huffEnc_nrOfCodes_max);
		c.ts->addMemory("norDicHuffmanToSymbol", c.ts->m_huffEnc_huffmanToSymbol_max);
		c.ts->addMemory("norDicTerminals", c.ts->m_huffEnc_terminals_max);
	}
	if (c.test)
	{
		c.ts->testTimer.start();
	}

	finalDict.generateCompactDictionary(
		dictionary,
		terminals,
		terminalVector,
		pairs,
		indices, 
		c);	
	if (c.test)
	{
		c.ts->testTimer.stop();
		c.ts->t_setupDictionary += c.ts->testTimer.getTimeNano();
	}

	//Write dictionary to file
	GammaCode gc;
	string output = "";

	if (c.test)
	{
		c.ts->testTimer.start();
	}

	this->dictionary2(
		compressedDictionaryName,		
		ofs_dictionary,
		pairs,
		dictionary,
		terminalVector,
		firstBlock,
		c);

	if (c.test)
	{
		c.ts->testTimer.stop();
		c.ts->t_writeDictionary += c.ts->testTimer.getTimeNano();
	}

	//Write Huffman dictionary to file
	if (c.test) //Carry over data structures
	{
		c.ts->addMemory("huffDicDictionary", c.ts->m_norDic_dictionary_max);
		c.ts->addMemory("huffDicTerminalVector", c.ts->m_norDic_terminalVector_max);
		c.ts->addMemory("huffDicFirstCodes", c.ts->m_norDic_firstCodes_max);
		c.ts->addMemory("huffDicNrOfCodes", c.ts->m_norDic_nrOfCodes_max);
		c.ts->addMemory("huffDicIndices", c.ts->m_norDic_indices_max);
		c.ts->addMemory("huffDicHuffmanToSymbol", c.ts->m_norDic_huffmanToSymbol_max);		
	}
	if (c.test)
	{
		c.ts->testTimer.start();
	}

	this->huffmanDictionary(
		compressedDictionaryName,
		ofs_dictionary,
		maxLength,
		firstCode,
		numl,
		terminalVector,
		dictionary,
		indices,
		huffmanToSymbol,
		c);
	if (c.test)
	{
		c.ts->testTimer.stop();
		c.ts->t_writeHuffmanDictionary += c.ts->testTimer.getTimeNano();
	}

	ofs_compressed.close();
	ofs_dictionary.close();

	//Clean up
	delete[] firstCode;
	delete[] numl;
}