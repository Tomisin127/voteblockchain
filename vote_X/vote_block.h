//block class
#ifndef VOTEBLOCK_H_
#define VOTEBLOCK_H_

class VoteBlock
{
	private:
	 int index;
	 size_t blockHash;
	 size_t previousHash;
	 size_t generateHash();

	 public:

	 	// constructor

	 	VoteBlock(int idx, VoterData d, size_t prevHash);

	 	//get index
	 	int getIndex();

	 	// get original hash

	 	size_t getHash();

	 	// get previous hash

	 	size_t getpreviousHash();

	 	// transaction data ,this should be in private
	 	VoterData data;

	 	// validate hash

	 	bool isHashValid();



};

#endif
