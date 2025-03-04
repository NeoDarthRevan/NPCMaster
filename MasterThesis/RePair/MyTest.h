#include "stdafx.h"
using namespace std;

#pragma once
class MyTest
{
public:
	MyTest();
	~MyTest();

	void Dictionary(string msg, unique_ptr<dense_hash_map<long, Pair>>& dictionary);
	void SequenceWithIndex(string msg, unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray);
	void Sequence(string msg, unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray);
	void ActivePairs(string msg, unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs);
	void ActivePairsDetails(string msg, unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs);
	void PriorityQueue(string msg, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void Context(
		string msg,
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext);
	string SequenceToString(unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray);
};

