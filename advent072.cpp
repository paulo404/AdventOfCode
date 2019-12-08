#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <sstream>
#include <algorithm>
using namespace std;

#define LENGTH 5 

int numArgs(unsigned int op) {
	switch (op) {
		//arith
		case 1:
		case 2: return 3;
		//io
		case 3:
		case 4: return 1;
		//jumps
		case 5:
		case 6: return 2;
		case 7:
		case 8: return 3;
		//exit
		case 99: return 0;
	}
	return -1; 
}

vector<int*> getArgs(vector<int> prog, int* pc, unsigned int mode,  unsigned int num_args) {
	vector<int*> a;
	while (num_args--) {
		int flag = mode % 10;
		mode /= 10;
		//							immediate mode		position mode
		int* val = flag? &prog[(*pc)++] : &prog[prog[(*pc)++]]; 
		a.push_back(val);	
	}
	return a;
}


int runProg(vector<int> prog,  int* pc, int* in,  int* out) {
	while (true) {
		unsigned int opcode = prog[(*pc)++];				//reads opcode, places increments pc
		unsigned int op = opcode % 100;
		unsigned int mode = opcode / 100;
		unsigned int n_args = numArgs(op);
		vector<int*> a = getArgs(prog, pc, mode, n_args);

		switch (op) {
			case 1:  *(a[2]) = *(a[0]) + *(a[1]);
		 					 break;
			case 2:  *(a[2]) = *(a[0]) * *(a[1]);
		 					 break;
			case 3:  *(a[0]) = *in;
							 break;
			case 4:  *out = *(a[0]);
							 return 0;	//mada mada da ne
			case 5:  *pc = *(a[0])? *(a[1]) : *pc;
		 					 break;
			case 6:  *pc = !*(a[0])? *(a[1]) : *pc;
		 					 break;
			case 7:  *(a[2]) = *(a[0]) < *(a[1])? 1 : 0;
							 break;
			case 8:  *(a[2]) = *(a[0]) == *(a[1])? 1 : 0;
							 break;
			case 99: return 1;	//finished
		}
	}
}

int main() {
	// read input
	ifstream file("in07alt");
	int x;

	vector<int> orig;
	while  ( file >> x ) {
	    orig.push_back(x);
	}
	file.close();	

	// set control? variables
	int max = INT_MIN;
	vector<int> phase({5,6,7,8,9});
	
	//run programs in sequence
	do {
		//copy code for each amplifier
		vector<vector<int>> program;
		for (int i=0; i<LENGTH;i++) 
			program[i] = vector<int>(orig);

		//set values for run
		vector<int> in(phase);		//first input is the sequence
		vector<int> out(LENGTH, 0);
		vector<int> pc(LENGTH, 0);
		int res = 0;

		//run amplifier sequence until last amplifier stops
		while (true) {
			for (int i=0; i<LENGTH;i++) 
				res = runProg(program[i], &pc[i], &in[i], &out[i]);
			cout << "deu uma" << endl;
			if (res) break;		
			in = vector<int>(out);
		}

		//update max
		int val = out.back();
		max = val>max? val : max;

	} while (next_permutation(phase.begin(), phase.end()));

	cout << max << endl;	

	return 0;
}
