#ifndef ACCOUNTCOLLECTION_H
#define ACCOUNTCOLLECTION_H

#include"Account.h"

#include<memory>
#include<vector>
using namespace std;
class AccountCollection {
	vector<weak_ptr<Account>> accounts;
public:
	AccountCollection(vector<weak_ptr<Account>> accounts) :accounts{ accounts } {
	}
	 bool calc_boni() {
		 bool check = true;
		for (auto a : accounts) {
			if (a.lock()->calc_bonus()) check=false;
		}
		return check;
	}

};

#endif
