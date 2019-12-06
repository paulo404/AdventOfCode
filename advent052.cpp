#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

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
	//cout << "fudeu\n";
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


int main() {
	//ifstream file("in05ex");
	ifstream file("in05alt");
	int x;

	while  ( file >> x ) {
	    prog.push_back(x);
	}

	file.close();	
	
	// run program
	while (true) {
		//cout<<"pos"<<prog_pos<<"\n";	
		unsigned int opcode = prog[prog_pos++];				//reads opcode, places increments pc
		unsigned int op = opcode % 100;
		unsigned int mode = opcode / 100;
		//cout<<"aqui\n";
		unsigned int n_args = numArgs(op);
		//cout<<"na:"<<n_args<<endl;
		//int write = !(op == 5 || op == 6 || op == 99);
		vector<int*> a = getArgs(mode, n_args);

		//cout<<"op"<<op<<"\n";	
		switch (op) {
			case 1:  *(a[2]) = *(a[0]) + *(a[1]);					break;
			case 2:  *(a[2]) = *(a[0]) * *(a[1]);					break;
			case 3:  cin >> *(a[0]);											break;
			case 4:  cout << *(a[0]) << endl;							break;
			case 5:  prog_pos = *(a[0])? *(a[1]) : prog_pos;					break;
			case 6:  prog_pos = !*(a[0])? *(a[1]) : prog_pos;					break;
			case 7:  *(a[2]) = *(a[0]) < *(a[1])? 1 : 0;								break;
			case 8:  *(a[2]) = *(a[0]) == *(a[1])? 1 : 0;								break;
			case 99: return 1;
		}
		//cout<<"opcompleted\n";
	}

	return 1;
}
