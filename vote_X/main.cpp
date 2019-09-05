#include <iostream>
#include <cmath>
#include <cstdlib>
#include <Vector>
#include <ctime>
#include <fstream>
#include <cctype>
#include <map>
#include <iterator>

#include "voter_data.h"
#include "vote_block.h"
#include "vote_block_chain.h"
#include "all_functions.h"


using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */





int main(int argc, char** argv) {
	
	cout << " x " <<endl;
	 /* 
	 VoteBlockChain blk;
	
	time_t data1time;
	VoterData data1("paul", "raimi", time(&data1time), 19, "james");
	blk.addBlock(data1);
	
	time_t data2time;
	VoterData data2("leon", "ray", time(&data2time), 9, "kath");
	blk.addBlock(data2);
	
	time_t data3time;
	VoterData data3("patrick", "drew", time(&data3time), 9, "anabella");
	blk.addBlock(data3);
	
	cout << endl;
	blk.print_chain();
	blk.print_vote_count();
	
	*/
	
	cout << "THIS PROGRAM IS A BLOCKCHAIN THAT RECORDS VOTING INFORMATION IN A PUBLIC LEDGER\n" <<endl;
	cout << "candidate1-> pelumi and candidate2-> john\n\n\n" <<endl;
	cout << "enter your first name: (enter q to quit) \n" <<endl;
	
	
	//the block chain data
	VoteBlockChain dat;
		
		
	while(cin.get() !='q')
	{		
		

		//time of vote
		time_t datatime;
		
				
		//each voter block info
		VoterData info;
		
		cin>>info.firstname;
		
		
		
		cout << "enter your last name: " <<endl;
		cin>>info.lastname;
		
		cout << "enter your age: " <<endl;
		cin>>info.age;
		
		cout << "enter the candidate you vote for " <<endl;
		cin>>info.candidate;
		
		//add the voter info and choice of candidate in vote blockchain
		dat.addBlock(info);
		
		dat.candidate_vote_count(info);
		
		cout << endl;
		
		//data.print_vote_count();
		dat.print_chain();
		
		dat.print_vote_count();
		
		//store the first name in a map
		//dat.store_bio_information(info);
		
		//return a pair and then read the information store in that pair
	//	operator<<(cout,dat.read_bio_information());
	
		dat.read_bio_information();
		
		cout << endl;
		
		/*ofstream myfile;	
		myfile.open("data.txt");
	
		myfile << "user data bio" << " :::::age: " <<info.age << " ,"  << "firstname: " << " ," <<
		info.firstname << " lastname: "<< info.lastname << " timestamp :" << info.timestamp <<
		"CANDIDATE OF CHOICE: "<< info.candidate << endl;

		myfile.close();
		
		// if it as reach the end of the loop, display the start message again
		cout <<" enter your name , surname, age and the candidate you wanna vote (enter q to quit) " << endl;
		*/
		if (cin.get()=='q')
			break;
		
		
		cout << "enter your first name: (enter q to quit) " <<endl;
		cout << "candidate1-> pelumi and candidate2-> john" <<endl;	
		
	} 
	return 0;
}
