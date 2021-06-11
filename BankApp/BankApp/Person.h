#ifndef PERSON_H
#define PERSON_H

#include "Account.h"
#include <iostream>
#include<vector>
#include <map>
#include<string>
#include <stdexcept>
#include <memory>

using namespace std;

class Account;

class Person: public enable_shared_from_this<Person>
{
	string name;
	map<int, weak_ptr<Account>> accounts;

public:
	Person(string);
	shared_ptr<Account> create_account(int, int, int, int, double);
	string get_name()const;
	size_t number_of_accounts() const;
	vector<int> get_accounts_nrs()const;
	bool share_account(shared_ptr<Person>, int);
	ostream& print(ostream& o) const;

	shared_ptr<Person> get_shared() { return shared_from_this(); }
};

#endif // !PERSON_H
