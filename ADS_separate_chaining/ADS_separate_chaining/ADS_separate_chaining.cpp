#include"ADS_set.h"
#include <iostream>;
using namespace std;

int main() {

	ADS_set<int>ss{15,30,45,7,22,5,20,3,18,33};
	ss.dump(cout);	



	return 0;
}