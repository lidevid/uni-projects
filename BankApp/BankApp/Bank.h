#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "Person.h"
#include <iostream>
#include <memory>
#include<vector>
#include <map>
#include<string>

using namespace std;


class Bank
{
	map<string, shared_ptr<Person>> customers;
	map<int, shared_ptr<Account>> accounts;
public:
	Bank()=default; // mb mit 0 konstruktor
	void create_person(string , int , int , int , int , double );
	ostream& print_customers(ostream& o) const;
	ostream& print_accounts(ostream& o) const;
	shared_ptr<Person> get_person(string );
	shared_ptr<Account> get_account(int );
	bool remove_person(string );
	bool remove_account(int );
};

#endif // ! BANK_H

