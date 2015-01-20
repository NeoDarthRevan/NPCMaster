#include "stdafx.h"

using namespace std;

#pragma once
class Initializer
{
public:
	Initializer();
	~Initializer();

	void SequenceArray(string filename,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>& activePairs,
		Conditions& c);
	void PriorityQueue(int priorityQueueSize,
		unique_ptr<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		Conditions& c);
	void setupPairRecord(
		unsigned int leftSymbol,
		unsigned int rightSymbol,
		int offset,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>& activePairs);
};

