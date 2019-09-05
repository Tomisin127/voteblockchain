
#ifndef VOTEBLOCKCHAIN_H_
#define VOTEBLOCKCHAIN_H_
//block chain


class VoteBlockChain{

	private:
	    //initial block of the blockchain
		VoteBlock CreateGenesisBlock();

		//the chain that holds the vote
		vector<VoteBlock> chain;

		int total_vote_count=0;

		int first_candidate_count =0;

		int second_candidate_count =0;

		int invalid_votes=0;

		string candidate1 = "pelumi";

		string candidate2 = "john";

		bool is_able_to_addblock=false;

		map<int,string>first_candidate_name_store;

        map<int,string>second_candidate_name_store;

	public:

	vector<VoteBlock> getchain();

	//constructor
	VoteBlockChain();

	//public functions

	bool isChainValid();

	//demo

	VoteBlock *getlatestblock();

	//add block
	void addBlock(VoterData d);

	void print_vote_count() const;

	int candidate_vote_count(VoterData &t);

	void print_chain();

	//void store_bio_information(const VoterData &d);

	void read_bio_information();

	//friend ostream & operator<<(ostream &gout , const int &);

};
#endif
