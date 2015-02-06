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

TEST(removeSymbolThreadingPointers, bothPreviousAndNextPointers)
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
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	indexSymbolLeft = 2;
	algP.removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(removeSymbolThreadingPointers, onlyPreviousPointer)
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
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	indexSymbolLeft = 4;
	algP.removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	ASSERT_EQ(scdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, scdPairLeft->previous);
	ASSERT_EQ(nullptr, trdPairLeft->previous);
	ASSERT_EQ(nullptr, trdPairLeft->next);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(removeSymbolThreadingPointers, onlyNextPointer)
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
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	indexSymbolLeft = 0;
	algP.removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	ASSERT_EQ(nullptr, fstPairLeft->next);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(scdPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, trdPairLeft->next);
	ASSERT_EQ(trdPairLeft, scdPairLeft->next);
}

TEST(updatePairRecord, countMoreThanTwoMiddlePair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;
	
	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	unsigned int symbol;
	long index;

	
	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord = 
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		scdPairLeft->index,
		scdPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
}

TEST(updatePairRecord, countMoreThanTwoFirstPair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	unsigned int symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[fstPairLeft->symbol][fstPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		fstPairLeft->index,
		fstPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
}

TEST(updatePairRecord, countMoreThanTwoLastPair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	unsigned int symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[trdPairLeft->symbol][trdPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		trdPairLeft->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
}

TEST(updatePairRecord, countTwoFirstPair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	unsigned int symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);
	
	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 2;

	tracker = &activePairs[fstPairLeft->symbol][fstPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		fstPairLeft->index,
		fstPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(nullptr, tracker);
	ASSERT_EQ(nullptr, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord);
}

TEST(removeFromPriorityQueueList, middleOfList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();
	PairRecord * pair3 = new PairRecord();

	priorityQueue[1] = pair1;
	pair1->nextPair = pair2;
	pair1->previousPair = nullptr;
	pair2->nextPair = pair3;
	pair2->previousPair = pair1;
	pair3->previousPair = pair2;
	pair3->nextPair = nullptr;

	pair2->count = 3;

	tracker->pairRecord = pair2;

	algP.removeFromPriorityQueueList(tracker, priorityQueue);

	ASSERT_EQ(pair3, pair1->nextPair);
	ASSERT_EQ(pair1, pair3->previousPair);
	ASSERT_EQ(nullptr, pair2->previousPair);
	ASSERT_EQ(nullptr, pair2->nextPair);
}

TEST(removeFromPriorityQueueList, firstInList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();
	PairRecord * pair3 = new PairRecord();

	priorityQueue[1] = pair1;
	pair1->nextPair = pair2;
	pair1->previousPair = nullptr;
	pair2->nextPair = pair3;
	pair2->previousPair = pair1;
	pair3->previousPair = pair2;
	pair3->nextPair = nullptr;

	pair1->count = 3;

	tracker->pairRecord = pair1;

	algP.removeFromPriorityQueueList(tracker, priorityQueue);

	ASSERT_EQ(nullptr, pair1->nextPair);
	ASSERT_EQ(nullptr, pair1->previousPair);
	ASSERT_EQ(pair2, pair3->previousPair);
	ASSERT_EQ(nullptr, pair2->previousPair);
	ASSERT_EQ(pair3, pair2->nextPair);
	ASSERT_EQ(pair2, priorityQueue[1]);
}

TEST(removeFromPriorityQueueList, lastInList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();
	PairRecord * pair3 = new PairRecord();

	priorityQueue[1] = pair1;
	pair1->nextPair = pair2;
	pair1->previousPair = nullptr;
	pair2->nextPair = pair3;
	pair2->previousPair = pair1;
	pair3->previousPair = pair2;
	pair3->nextPair = nullptr;

	pair1->count = 3;

	tracker->pairRecord = pair3;

	algP.removeFromPriorityQueueList(tracker, priorityQueue);

	ASSERT_EQ(pair2, pair1->nextPair);
	ASSERT_EQ(nullptr, pair1->previousPair);
	ASSERT_EQ(nullptr, pair3->previousPair);
	ASSERT_EQ(pair1, pair2->previousPair);
	ASSERT_EQ(nullptr, pair2->nextPair);
	ASSERT_EQ(pair1, priorityQueue[1]);
}