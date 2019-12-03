#include <iostream>


using namespace std;

int main() {
	int sum = 0;
	int x;


	while (cin >> x) {
	    int fuel = x / 3 - 2;
	
    	int fuelcost = fuel;
    	int sum2 = 0;
    	do {
    	    int fuel4fuel = fuelcost / 3 - 2;
    	    fuelcost = (fuel4fuel > 0) ? fuel4fuel : 0;
    	    sum2 += fuelcost;
    	    
    	} while (fuelcost);
	    
	    
		sum += fuel + sum2; //? fuel : 0;
		
	}
	
	
	

	cout << sum;

	return 0;
}