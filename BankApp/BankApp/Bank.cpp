#include"Bank.h"

void Bank::create_person(string name, int nr, int balance,  int limit, int mode, double fee_factor) {
	for (auto p : customers)
	{
		if (p.first == name) throw runtime_error("This name already exists");
	}
	for (auto a : accounts)
	{
		if(a.first==nr) throw runtime_error("This Number already exists");
	}

	Person per{ name };
	auto per_ptr = make_shared<Person>(per);
	customers.insert({name,per_ptr});

	auto acc_ptr= per_ptr->create_account(nr,balance,limit,mode,fee_factor);
	accounts.insert({nr,acc_ptr});
}

ostream& Bank::print_customers(ostream& o) const {
	o << "["<<"\n";
	for (auto p : customers)
	{
		 p.second->print(o);
		 o << "\n";
	}
	o << "]";
	return o;
}

ostream& Bank::print_accounts(ostream& o) const {
	o << "[" << "\n";
	for (auto a : accounts)
	{
		a.second->print(o);
		o << "\n";
	}
	o << "]";
	return o;
}

shared_ptr<Person> Bank::get_person(string n) {
	for (auto p : customers)
	{
		if (p.first == n) return p.second;
	}

	throw runtime_error("There is not such a name in Bank");
}

shared_ptr<Account> Bank::get_account(int n) {
	for (auto a : accounts)
	{
		if (a.first == n) return a.second;
	}

	throw runtime_error("There is not such an Account in Bank");
}

bool Bank::remove_person(string n) {
	size_t count = customers.size();

	auto c= customers.find(n);
	c->second.~shared_ptr();
	customers.erase(c);
	if (customers.size() == count) return false;

	for (auto it = accounts.begin(); it != accounts.end();)
	{
		if (it->second->number_of_owners() == 0) it= accounts.erase(it);
		else it++;
	}
	return true;
}

bool Bank::remove_account(int n ) {

	size_t count = accounts.size();

	auto a = accounts.find(n);
	a->second.~shared_ptr();
	accounts.erase(a);
	if (accounts.size() == count) return false;

	for (auto it = customers.begin(); it != customers.end(); )
	{
		if (it->second->number_of_accounts() == 0) it=customers.erase(it);
		else it++;
	}
	return true;
}