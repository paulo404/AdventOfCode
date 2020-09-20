#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<int> prog;
unsigned int prog_pos = 0;

int numArgs(unsigned int op) {
	switch (op) {
		case 1:
		case 2: return 3;
		case 3:
		case 4: return 1;
		case 99: return 0;
	}
	return -1; 
}

// probably should've returned pointers instead of indexes
vector<int> getArgs(unsigned int mode, unsigned int num_args) {
	vector<int> a;
	while (num_args-- > 1) {
		int flag = mode % 10;
		mode /= 10;
		//							immediate mode		position mode
		int val = flag? prog[prog_pos++] : prog[prog[prog_pos++]]; 
		a.push_back(val);	
	}
	a.push_back(prog[prog_pos++]);			//final argument (write) is always imediate, despite what they say
	return a;
}


int main() {
	ifstream file("in05alt");
	int x;

	while  ( file >> x ) {
	    prog.push_back(x);
	}

	file.close();	
	
	// run program
	while (true) {
		unsigned int opcode = prog[prog_pos++];
		unsigned int op = opcode % 100;
		unsigned int mode = opcode / 100;
		unsigned int n_args = numArgs(op);
		vector<int> a = getArgs(mode, n_args);
		
		switch (op) {
			case 1:  prog[a[2]] = a[0] + a[1];					break;
			case 2:  prog[a[2]] = a[0] * a[1];					break;
			case 3:  cin >> prog[a[0]];									break;
			case 4:  cout << prog[a[0]] << endl;				break;
			case 99: return 1;
		}
	}

	return 1;
}
