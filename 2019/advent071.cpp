#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <sstream>
#include <algorithm>
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


int runOP(int* in) {
	int i = 0;
	while (true) {
		unsigned int opcode = prog[prog_pos++];				//reads opcode, places increments pc
		unsigned int op = opcode % 100;
		unsigned int mode = opcode / 100;
		unsigned int n_args = numArgs(op);
		vector<int*> a = getArgs(mode, n_args);

		switch (op) {
			case 1:  *(a[2]) = *(a[0]) + *(a[1]);					break;
			case 2:  *(a[2]) = *(a[0]) * *(a[1]);					break;
			case 3:  *(a[0]) = in[i++];											break;
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
	ifstream file("in07alt");
	int x;

	while  ( file >> x ) {
	    prog.push_back(x);
	}
	file.close();	

	int max = INT_MIN;
	int in = 0;
	vector<int> orig(prog);
	string s = "01234";
	
	do {
		//run programs in sequence
		//cout << "permutation:" << s << endl;
		in = 0;
		for (int j=0;j<5;j++) {
			prog_pos = 0;
			prog = vector<int>(orig);
			//cout << "phase:" << s[j]-'0' << " in:" << in << endl;
			int invet[2] = {s[j]-'0', in};
			in = runOP(invet);			
		}
		//cout << in << endl;
		max = in>max? in : max;
	} while (next_permutation(s.begin(), s.end()));

	cout << max << endl;	

	return 1;
}
