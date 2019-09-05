
//ALL FUNCTIONS HERE

// creating the functions and constructor

//accepts the voting index, the vote data and the previous hash of the previous vote
VoteBlock::VoteBlock(int idx, VoterData d , size_t prevHash)
{
	index = idx ;
	data = d;
	previousHash = prevHash;
	blockHash = generateHash();
}

// private functions
size_t VoteBlock::generateHash(){

	//creating string of transaction data
	string toHashS = to_string(data.age) + data.candidate +data.firstname +data.lastname +to_string(data.timestamp);

	//2 hashes to combine
	hash<string> tDataHash;// hashes transaction data string
	hash<string> prevHash;// re-hashes previous hash(for combination)

	//combine hashes and get size_t for block hash

	return tDataHash(toHashS) ^ (prevHash(to_string(previousHash)) << 1);
};

//public functions

int VoteBlock::getIndex()
{
	return index;
}

size_t VoteBlock::getHash()
{
	return blockHash;
}

size_t VoteBlock::getpreviousHash()
{
	return previousHash;
}


bool VoteBlock::isHashValid()
{
	return generateHash() == getHash();
}



int VoteBlockChain::candidate_vote_count(VoterData &t)
	{

	 	if (t.candidate==candidate1)
	 	{
	 		first_candidate_count +=1;


		}
		else if(t.candidate == candidate2)
		{
			second_candidate_count +=1;
		}

		else
		{
			cout << "THIS CANDIDATE DOES NOT EXIST" <<endl;
			invalid_votes += 1;
	 	}
	}



//read the bio in the map
void VoteBlockChain::read_bio_information()
	{
		//read out the voters first name

		map<int, string>::iterator rt;

		for(rt=voter_name_store.begin(); rt!=voter_name_store.end(); ++rt)
			{

			cout << "size of the map: " << voter_name_store.size() <<endl;
			//cout << "content of the map : " << voter_name_store <<endl;
			cout <<  "the key : "<< rt->first <<endl;
			cout << "the value : " << rt->second <<endl;

			}

	}

//print info in the block
void VoteBlockChain::print_chain()
	{
		vector<VoteBlock>::iterator it;

		for(it =chain.begin(); it !=chain.end() ; ++it)
		{
			cout << endl;
			VoteBlock current= *it;
			cout << " BLOCK=======================" <<endl;
			//cout << " index: " << current.getindex() <<endl;
			cout << "first name : "<< current.data.firstname <<endl;
			cout << "last name : " <<current.data.lastname <<endl;
			cout << " voted candidate : " << current.data.candidate <<endl;
			cout << "time stamp : " << current.data.timestamp <<endl;
			cout << " hash: " << current.getHash() <<endl;
			cout << " previous hash: " << current.getpreviousHash() << endl;
			cout << " Is block valid: " << current.isHashValid() <<endl;
			cout << "age : " << current.data.age <<endl;

			cout <<endl;
		}
	}
// block chain constructor

VoteBlockChain::VoteBlockChain()
{

	VoteBlock genesis = CreateGenesisBlock();

	chain.push_back(genesis);

	//cout << " total vote count : " << total_vote_count <<  endl;
}

vector<VoteBlock> VoteBlockChain::getchain()
{
	return chain;
}

// create genesis block function

VoteBlock VoteBlockChain::CreateGenesisBlock()
{
	time_t current;

	// setup initial info on the genesis block
	VoterData d("GENESIS", "BLOCK", time(&current),0, "GENESIS");

	//creating string of voter data
	string toHashS = to_string(d.age) + d.candidate +d.firstname +d.lastname +to_string(d.timestamp);

	//2 hases combine

	hash<string> tDataHash;// hashes voter data string
	hash<string>prevHash;// rehashes previous hash(for combination)

	size_t Hash = tDataHash(toHashS) ^ (prevHash(to_string(0)) <<1);
	//geneis block doesnt contain anything yet

	VoteBlock genesis(0, d, Hash);

	return genesis;

}
// bad!! only for demo

VoteBlock *VoteBlockChain::getlatestblock()
{
	return &chain.back();
}






void VoteBlockChain::addBlock(VoterData d)
{
	is_able_to_addblock=true;

	// getting the index of the block in the chain
	int index = (int)chain.size();

	//set the number of vote subtract from the genesis block
	total_vote_count =index;

	size_t previousHash = (int)chain.size() >0 ? getlatestblock()->getHash() : 0;


	if (d.age >=18 and is_able_to_addblock==true)
	{
		VoteBlock newBlock(index, d, previousHash);

		chain.push_back(newBlock);

		voter_name_store.insert({index, d.firstname});

		map<int,string>::iterator dt;

		//cout << "size of the map :" << voter_name_store.size() <<endl;

		for (dt= voter_name_store.begin(); dt!=voter_name_store.end(); ++dt)
		{

		}
	}
	else
	{
		is_able_to_addblock=false;
		cout << "THIS VOTER IS UNDER-AGED" << endl;
	}
	//cout << "chain length : " << chain.size() <<endl;
}




bool VoteBlockChain::isChainValid()
{

	vector<VoteBlock>::iterator it;

	for(it = chain.begin(); it !=chain.end(); ++it)
	{
		VoteBlock currentBlock = *it;

		if (!currentBlock.isHashValid())
		{
			// INVALID HASH!!!
			return false;
		}

		if(it != chain.begin())
		{
			VoteBlock previousBlock = *(it-1);

			if (currentBlock.getpreviousHash() != previousBlock.getHash())
			{

				// INVALID HASH
				return false;
			}
		}
	}
	return true;
}

void VoteBlockChain::print_vote_count()const
{
	cout << "present vote count is : " <<  total_vote_count <<endl;

	cout << "first candidate vote count is : " << first_candidate_count <<endl;

	cout << "second candidate vote count is : " << second_candidate_count <<endl;
}

