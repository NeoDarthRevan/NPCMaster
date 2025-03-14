#pragma once
class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	int Algorithm::run(
		string &filename,
		ifstream & file,
		Conditions &c,
		Initializer &init,
		AlgorithmP &algP,
		MyTimer &t,
		int blockSize,
		dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		dense_hash_map<unsigned long, Pair> & dictionary,
		unsigned long & symbols);
};

