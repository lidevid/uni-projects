#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Person.h"
#include <iostream>
#include <memory>
#include <map>
#include<string>
#include<vector>
#include <stdexcept>

using namespace std;

class Person;

class Account
{
	int bonus=0; // Aufgabe 2
	int nr;
	int balance;
	int limit;
	map<string, weak_ptr<Person>> persons;
	double fee=0;

public:
	Account(int,int,int,shared_ptr<Person>);

	int get_bonus()const{ return bonus; } //aufgabe 2
	void set_bonus(int n) { bonus = n; } // aufgabe 2
	virtual bool calc_bonus() { return false; } //aufgabe 2


	int get_nr()const;
	vector<string> get_authorized_persons()const;
	size_t number_of_owners()const;
	bool add_authorized_person(shared_ptr<Person>);
	bool transfer(shared_ptr<Account>, int);
	virtual double calc_fee(int) const = 0;
	virtual ostream& print(ostream& o) const; // aufgabe 2 virtual
	ostream& print_help(ostream& o) const;

	virtual ~Account()=default;

};

class GiroAccount :public Account {
	double fee_factor;
public:
	GiroAccount(int, int, int, shared_ptr<Person>, double);
	double calc_fee(int)const;
};

class BusinessAccount :public Account {
	double fee_factor;
public:
	BusinessAccount(int, int, int, shared_ptr<Person>, double);
	double calc_fee(int)const;
};

//AUFGABE 2
class SGiroAccount :public GiroAccount {
public:
	SGiroAccount(int nr, int balance, int limit, shared_ptr<Person> persons, double fee) :
		GiroAccount(nr, balance, limit, persons, fee) {}

	bool calc_bonus() {
		int change = 0;
		for (string p : this->get_authorized_persons())
		{
			if (p.find("la")!=string::npos) {
				change = 1;
				this->set_bonus(change + this->get_bonus());
				return true;
			}
		}
		return false;
	}

	virtual ostream& print(ostream& o) const {
		Account::print(o);
		o << "bonus: "<<Account::get_bonus();
		return o;
	}
};
 // AUFGABE 2
class SBusinessAccount :public BusinessAccount {
public:
	SBusinessAccount(int nr, int balance, int limit, shared_ptr<Person> persons, double fee) :
		BusinessAccount(nr, balance, limit, persons, fee) {}

	virtual bool calc_bonus() override{
		int change = 2;
		this->set_bonus(change + this->get_bonus());
		return true;
	}

	virtual ostream& print(ostream& o) const {
		Account::print(o);
		o << "bonus: " << Account::get_bonus();
		return o;
	}
};

#endif