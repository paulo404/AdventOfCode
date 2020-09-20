#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ANSWER 19690720

int main() {
    string sx;
    int x;
	vector<int> prog, orig;

	while  ( !cin.eof() ) {
	    getline(cin, sx, ',');
	    x = stoi(sx);
	    prog.push_back(x);
	}
	
	orig = vector<int>(prog);
	
	// iterate values
	for (int noun = 0; noun < 100; noun++)
	    for (int verb = 0; verb < 100; verb++) {
	        prog = vector<int>(orig);
	        prog[1] = noun;
	        prog[2] = verb;
	        
	        // run program
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
	        
	        if (prog[0] == ANSWER) {
	            cout << noun << " " << verb;
	            return 0;
            }
	    }
	    
	return 1;
}