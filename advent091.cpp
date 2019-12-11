#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <sstream>
#include <algorithm>
using namespace std;

#define LENGTH 5 
#define ll long long 

#define PLUS 1
#define MULT 2
#define READ 3
#define WRTE 4
#define JMPT 5
#define JMPF 6
#define STLT 7
#define STEQ 8
#define CREL 9
#define HALT 99

class IntcodeComputer {
	public:
	vector<ll> mem;
	ll pc, rc;

	IntcodeComputer(unsigned long memsize, vector<ll>* program) {
		mem = vector<ll>(*program);
		mem.reserve(memsize);
		pc = rc = 0;
	}

	int numArgs(unsigned int op) {
		switch (op) {
			case PLUS:
			case MULT:	return 3;
			case READ:
			case WRTE:	return 1;
			case JMPT:
			case JMPF:	return 2;
			case STLT:
			case STEQ:	return 3;
			case CREL:	return 1;
			case HALT:	return 0;
		}
		return -1; 
	}

	// returns vector with * to values ( careful!! moves the pc to the next opcode )
	vector<ll*> getArgs(unsigned int mode,  unsigned int num_args) {
		vector<ll*> a;

		while (num_args--) {
			int flag = mode % 10;
			mode /= 10;
			ll* val;

			if (flag == 0)
				val = &mem[mem[pc++]];
			else if (flag == 1)
				val = &mem[pc++];
			else if (flag == 2)
				val = &mem[rc + mem[pc++]];

			a.push_back(val);	
		}

		return a;
	}

	//run one op and returns its code
	int run(queue<ll>* in, queue<ll>* out) {
		unsigned int opcode = mem[pc++];				//reads opcode, places increments pc
		unsigned int op = opcode % 100;
		unsigned int mode = opcode / 100;
		unsigned int n_args = numArgs(op);
		vector<ll*> a = getArgs(mode, n_args);

		switch (op) {
			case PLUS:
				*(a[2]) = *(a[0]) + *(a[1]);
				break;
			case MULT:
				*(a[2]) = *(a[0]) * *(a[1]);
				break;
			case READ:
				*(a[0]) = in->front();
				in->pop();
				break;
			case WRTE:
				out->push(*(a[0]));
				break;
			case JMPT:
				pc = *(a[0])? *(a[1]) : pc;
				break;
			case JMPF:
				pc = !*(a[0])? *(a[1]) : pc;
				break;
			case STLT:
				*(a[2]) = *(a[0]) < *(a[1])? 1 : 0;
				break;
			case STEQ:
				*(a[2]) = *(a[0]) == *(a[1])? 1 : 0;
				break;
			case CREL:
				rc += *(a[0]);
				break;
			case HALT:
				break;
		}

		return op;
	}

	~IntcodeComputer() {
	}
};



int main() {
	// read input
	ll x;
	vector<ll> orig;

	while  ( cin >> x ) { orig.push_back(x); }

	//run program
	IntcodeComputer ic(100000, &orig);
	queue<ll> in;
	queue<ll> out;
	int ret;
	in.push(2);
	do {
		ret = ic.run(&in, &out);	
	} while (ret != HALT);
	
	//print out
	while (!out.empty()) {
		cout << out.front() << endl;
		out.pop();
	}
	return 0;
}
