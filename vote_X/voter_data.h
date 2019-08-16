
#ifndef VOTE_DATA_H_
#define VOTE_DATA_H_

using namespace std;
struct VoterData{


	string firstname;
	string lastname;
	time_t timestamp;
	int age;
	string candidate;

	VoterData(){};

	VoterData(string first , string last, time_t time, int ag, string cand )
	{
		firstname = first;
		lastname = last;
		timestamp = time;
		age = ag;
		candidate = cand;
	};

};



#endif // VOTE_DATA_H_
