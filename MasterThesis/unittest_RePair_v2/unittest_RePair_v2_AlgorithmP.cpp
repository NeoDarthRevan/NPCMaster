#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(establishContext, adjacentSymbolsPreviousAndNext)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 1;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(1, indexSymbolLeft);
	ASSERT_EQ(2, indexSymbolRight);
	ASSERT_EQ(3, indexSymbolNext);
}

TEST(establishContext, adjacentSymbolsNoPrevious)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 0;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(-1, indexSymbolPrevious);
	ASSERT_EQ(0, indexSymbolLeft);
	ASSERT_EQ(1, indexSymbolRight);
	ASSERT_EQ(2, indexSymbolNext);
}

TEST(establishContext, adjacentSymbolsNoNext)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(1, indexSymbolPrevious);
	ASSERT_EQ(2, indexSymbolLeft);
	ASSERT_EQ(3, indexSymbolRight);
	ASSERT_EQ(-1, indexSymbolNext);
}

TEST(establishContext, notAdjacentSymbols)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 0;
	index = 1;
	SymbolRecord * empty1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty1);

	symbol = 2;
	index = 2;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 0;
	index = 3;
	SymbolRecord * empty2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty2);

	symbol = 3;
	index = 4;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 0;
	index = 5;
	SymbolRecord * empty3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty3);

	symbol = 4;
	index = 6;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	//Thread empty symbols
	empty1->next = left;
	empty1->previous = previous;
	empty2->next = right;
	empty2->previous = left;
	empty3->next = next;
	empty3->previous = right;

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(2, indexSymbolLeft);
	ASSERT_EQ(4, indexSymbolRight);
	ASSERT_EQ(6, indexSymbolNext);
}

TEST(establishContext, notAdjacentSymbolsLargeGap)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 0;
	index = 1;
	SymbolRecord * empty1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty1);

	symbol = 2;
	index = 2;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 0;
	index = 3;
	SymbolRecord * empty2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty2);

	symbol = 0;
	index = 4;
	SymbolRecord * emptyExtra1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra1);

	symbol = 0;
	index = 5;
	SymbolRecord * emptyExtra2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra2);

	symbol = 0;
	index = 6;
	SymbolRecord * emptyExtra3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra3);

	symbol = 0;
	index = 7;
	SymbolRecord * empty3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty3);

	symbol = 3;
	index = 8;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 0;
	index = 9;
	SymbolRecord * empty4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty4);

	symbol = 4;
	index = 10;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	//Thread empty symbols
	empty1->next = left;
	empty1->previous = previous;
	empty2->next = right;
	empty2->previous = left;
	empty3->next = right;
	empty3->previous = left;
	empty4->next = next;
	empty4->previous = right;

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(2, indexSymbolLeft);
	ASSERT_EQ(8, indexSymbolRight);
	ASSERT_EQ(10, indexSymbolNext);
}

TEST(establishContext, notAdjacentSymbolsLargeGaps)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 6;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 0;
	index = 1;
	SymbolRecord * empty1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty1);

	symbol = 0;
	index = 2;
	SymbolRecord * emptyExtra1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra1);

	symbol = 0;
	index = 3;
	SymbolRecord * emptyExtra2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra2);

	symbol = 0;
	index = 4;
	SymbolRecord * emptyExtra3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra3);

	symbol = 0;
	index = 5;
	SymbolRecord * empty2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty2);

	symbol = 2;
	index = 6;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 0;
	index = 7;
	SymbolRecord * empty3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty3);

	symbol = 0;
	index = 8;
	SymbolRecord * emptyExtra4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra4);

	symbol = 0;
	index = 9;
	SymbolRecord * emptyExtra5 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra5);

	symbol = 0;
	index = 10;
	SymbolRecord * emptyExtra6 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra6);

	symbol = 0;
	index = 11;
	SymbolRecord * empty4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty4);

	symbol = 3;
	index = 12;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 0;
	index = 13;
	SymbolRecord * empty5 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty5);

	symbol = 0;
	index = 14;
	SymbolRecord * emptyExtra7 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra7);

	symbol = 0;
	index = 15;
	SymbolRecord * emptyExtra8 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra8);

	symbol = 0;
	index = 16;
	SymbolRecord * emptyExtra9 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra9);

	symbol = 0;
	index = 17;
	SymbolRecord * empty6 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty6);

	symbol = 4;
	index = 18;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	//Thread empty symbols
	empty1->next = left;
	empty1->previous = previous;
	empty2->next = left;
	empty2->previous = previous;

	empty3->next = right;
	empty3->previous = left;
	empty4->next = right;
	empty4->previous = left;

	empty5->next = next;
	empty5->previous = right;
	empty6->next = next;
	empty6->previous = right;

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(6, indexSymbolLeft);
	ASSERT_EQ(12, indexSymbolRight);
	ASSERT_EQ(18, indexSymbolNext);
}

TEST(findAllPairs, pairsNotAdjacent_oneNewPairMatches)
{
	AlgorithmP algo;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols = 65;
	Conditions c;
	long firstIndex = 2;

	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array: h i a b j a b i a b k l
	//This gives 2 x iA, 1 x jA, 1 x Aj, 1 x Ai, 1 x Ak
	symbol = 104;//h
	index = 0;
	SymbolRecord * filler1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler1);

	symbol = 105;//i
	index = 1;
	SymbolRecord * filler2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler2);

	symbol = 97;//a
	index = 2;
	SymbolRecord * firstfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(firstfirst);

	symbol = 98;//b
	index = 3;
	SymbolRecord * firstsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(firstsecond);

	symbol = 106;//j
	index = 4;
	SymbolRecord * filler3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler3);

	symbol = 97;//a
	index = 5;
	SymbolRecord * secondfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(secondfirst);

	symbol = 98;//b
	index = 6;
	SymbolRecord * secondsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(secondsecond);

	symbol = 105;//i
	index = 7;
	SymbolRecord * filler4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler4);

	symbol = 97;//a
	index = 8;
	SymbolRecord * thirdfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(thirdfirst);

	symbol = 98;//b
	index = 9;
	SymbolRecord * thirdsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(thirdsecond);

	symbol = 107;//k
	index = 10;
	SymbolRecord * filler5 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler5);

	symbol = 108;//l
	index = 11;
	SymbolRecord * filler6 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler6);

	//Thread pairs
	firstfirst->next = secondfirst;
	secondfirst->previous = firstfirst;
	secondfirst->next = thirdfirst;
	thirdfirst->previous = secondfirst;

	algo.findAllPairs(firstIndex, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);

	ASSERT_FALSE(activePairs[105][65].seenOnce);
	ASSERT_TRUE(activePairs[105][65].pairRecord != NULL);

	ASSERT_TRUE(activePairs[106][65].seenOnce);
	ASSERT_EQ(NULL, activePairs[106][65].pairRecord);

	ASSERT_TRUE(activePairs[65][105].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][105].pairRecord);

	ASSERT_TRUE(activePairs[65][106].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][106].pairRecord);

	ASSERT_TRUE(activePairs[65][107].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][107].pairRecord);
}

TEST(findAllPairs, twoPairsAdjacent_oneNewPairMatches)
{
	AlgorithmP algo;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols = 65;
	Conditions c;
	long firstIndex = 2;

	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array: h i a b a b i a b k l
	//This gives 2 x iA, 1 x AA, 1 x Ai, 1 x Ak
	symbol = 104;//h
	index = 0;
	SymbolRecord * filler1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler1);

	symbol = 105;//i
	index = 1;
	SymbolRecord * filler2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler2);

	symbol = 97;//a
	index = 2;
	SymbolRecord * firstfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(firstfirst);

	symbol = 98;//b
	index = 3;
	SymbolRecord * firstsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(firstsecond);

	symbol = 97;//a
	index = 4;
	SymbolRecord * secondfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(secondfirst);

	symbol = 98;//b
	index = 5;
	SymbolRecord * secondsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(secondsecond);

	symbol = 105;//i
	index = 6;
	SymbolRecord * filler3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler3);

	symbol = 97;//a
	index = 7;
	SymbolRecord * thirdfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(thirdfirst);

	symbol = 98;//b
	index = 8;
	SymbolRecord * thirdsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(thirdsecond);

	symbol = 107;//k
	index = 9;
	SymbolRecord * filler4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler4);

	symbol = 108;//l
	index = 10;
	SymbolRecord * filler5 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler5);

	//Thread pairs
	firstfirst->next = secondfirst;
	secondfirst->previous = firstfirst;
	secondfirst->next = thirdfirst;
	thirdfirst->previous = secondfirst;

	algo.findAllPairs(firstIndex, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);

	ASSERT_FALSE(activePairs[105][65].seenOnce);
	ASSERT_TRUE(activePairs[105][65].pairRecord != NULL);

	ASSERT_TRUE(activePairs[65][65].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][65].pairRecord);

	ASSERT_TRUE(activePairs[65][105].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][105].pairRecord);

	ASSERT_TRUE(activePairs[65][107].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][107].pairRecord);
}

TEST(findAllPairs, fourPairsAdjacent)
{
	AlgorithmP algo;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols = 65;
	Conditions c;
	long firstIndex = 2;

	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array: h i a b a b a b a b k l
	//This gives 2 x iA, 1 x jA, 1 x Aj, 1 x Ai, 1 x Ak
	symbol = 104;//h
	index = 0;
	SymbolRecord * filler1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler1);

	symbol = 105;//i
	index = 1;
	SymbolRecord * filler2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler2);

	symbol = 97;//a
	index = 2;
	SymbolRecord * firstfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(firstfirst);

	symbol = 98;//b
	index = 3;
	SymbolRecord * firstsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(firstsecond);

	symbol = 97;//a
	index = 4;
	SymbolRecord * secondfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(secondfirst);

	symbol = 98;//b
	index = 5;
	SymbolRecord * secondsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(secondsecond);

	symbol = 97;//a
	index = 6;
	SymbolRecord * thirdfirst = new SymbolRecord(symbol, index);
	sequenceArray.push_back(thirdfirst);

	symbol = 98;//b
	index = 7;
	SymbolRecord * thirdsecond = new SymbolRecord(symbol, index);
	sequenceArray.push_back(thirdsecond);

	symbol = 107;//k
	index = 8;
	SymbolRecord * filler3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler3);

	symbol = 108;//l
	index = 9;
	SymbolRecord * filler4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(filler4);

	//Thread pairs
	firstfirst->next = secondfirst;
	secondfirst->previous = firstfirst;
	secondfirst->next = thirdfirst;
	thirdfirst->previous = secondfirst;

	algo.findAllPairs(firstIndex, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);

	ASSERT_TRUE(activePairs[65][65].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][65].pairRecord);

	ASSERT_TRUE(activePairs[105][65].seenOnce);
	ASSERT_EQ(NULL, activePairs[105][65].pairRecord);

	ASSERT_TRUE(activePairs[65][107].seenOnce);
	ASSERT_EQ(NULL, activePairs[65][107].pairRecord);
}