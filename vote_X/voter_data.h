
using namespace std;

struct VoterData{


	string firstname;
	string lastname;
	time_t timestamp;
	double age;
	string candidate;

	VoterData(){};

	VoterData(string first , string last, time_t time, double ag, string cand )
	{
		firstname = first;
		lastname = last;
		timestamp = time;
		age = ag;
		candidate = cand;
	};

};



