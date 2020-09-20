#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string sx;
    int x;
	vector<int> prog;

	while  ( !cin.eof() ) {
	    getline(cin, sx, ',');
	    x = stoi(sx);
	    prog.push_back(x);
	}
		
	for (int i = 0; prog[i]; i+=4) {
        int op = prog[i];
        if (op == 99) break;
        
        int arg1 = prog[prog[i+1]];
        int arg2 = prog[prog[i+2]];
        int sto  = prog[i+3];
        
        
        if (op == 1) 
            prog[sto] = arg1 + arg2;
        else if (op == 2)
            prog[sto] = arg1 * arg2;
        else
            cout << "fudeu mermao" << endl;
        
	}
	

	cout << prog[0];

	return 0;
}