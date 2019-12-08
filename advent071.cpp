#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <sstream>
using namespace std;

#define MAX 43210
#define MIN 01234
#define LENGTH 5 

vector<int> prog;
unsigned int prog_pos = 0;

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

vector<int*> getArgs(unsigned int mode, unsigned int num_args) {
	vector<int*> a;
	while (num_args--) {
		int flag = mode % 10;
		mode /= 10;
		//							immediate mode		position mode
		int* val = flag? &prog[prog_pos++] : &prog[prog[prog_pos++]]; 
		a.push_back(val);	
	}
	return a;
}

//same and only digits below 5
int testnum(string s) {
	vector<int> count(5,0);
	for (int k = 0; k<LENGTH; k++) {
		if (count[s[k]-'0']++ || s[k] >='5') return 1;
	}
	return 0;
} 

int runOP(stringstream in) {
	while (true) {
		unsigned int opcode = prog[prog_pos++];				//reads opcode, places increments pc
		unsigned int op = opcode % 100;
		unsigned int mode = opcode / 100;
		unsigned int n_args = numArgs(op);
		vector<int*> a = getArgs(mode, n_args);

		switch (op) {
			case 1:  *(a[2]) = *(a[0]) + *(a[1]);					break;
			case 2:  *(a[2]) = *(a[0]) * *(a[1]);					break;
			case 3:  in >> *(a[0]);											break;
			case 4:  return *(a[0]);							break;
			case 5:  prog_pos = *(a[0])? *(a[1]) : prog_pos;					break;
			case 6:  prog_pos = !*(a[0])? *(a[1]) : prog_pos;					break;
			case 7:  *(a[2]) = *(a[0]) < *(a[1])? 1 : 0;								break;
			case 8:  *(a[2]) = *(a[0]) == *(a[1])? 1 : 0;								break;
			case 99: return 1;
		}
	}
}

int main() {
	//ifstream file("in05ex");
	ifstream file("in05alt");
	int x;

	while  ( file >> x ) {
	    prog.push_back(x);
	}
	file.close();	

	int max = INT_MIN;
	char cs[6];
	int in = 0;

	for(int i=MIN;i<=MAX;i++) {
		//get valid phase sequences
		sprintf(cs, "%05d", i);
		string phaseSeq(cs);
		if (testnum(phaseSeq)) continue;

		//run programs in sequence
		for (int j=0;j<5;j++) {
			stringstream runIn;	
			runIn << phaseSeq[j] << in;
			in = runOP(runIn);			// TODO não dá pra passar stringstream??
		}
		cout << in << endl;
		max = in>max? in : max;
	}
	
		
		
	// run program

	return 1;
}
