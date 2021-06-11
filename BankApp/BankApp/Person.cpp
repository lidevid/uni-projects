#include "Person.h"

Person::Person(string s): name{s}
{
	if (s.empty()) throw runtime_error("Empty name");
}

string Person::get_name()const {
	return name;
}

shared_ptr<Account> Person::create_account(int nr, int balance, int limit, int mode, double fee_factor) {
	if(mode==0){
		GiroAccount g ( nr, balance, limit, get_shared(), fee_factor );
		auto ptr = make_shared<GiroAccount>(g);
		accounts.insert({ nr,ptr });
		return ptr;
	}
	if(mode==1){
		BusinessAccount g (nr, balance, limit, get_shared(), fee_factor);
		auto ptr = make_shared<BusinessAccount>(g);
		accounts.insert({ nr,ptr });
		return ptr;
	}												// mode 2,3 for AUFGABE 2
	if (mode == 2) {									
		SGiroAccount g(nr, balance, limit, get_shared(), fee_factor);
		auto ptr = make_shared<SGiroAccount>(g);
		accounts.insert({ nr,ptr });
		return ptr;
	}
	if (mode == 3) {
		SBusinessAccount g(nr, balance, limit, get_shared(), fee_factor);
		auto ptr = make_shared<SBusinessAccount>(g);
		accounts.insert({ nr,ptr });
		return ptr;
	}

	else throw runtime_error("Not 1 or 0");
}

size_t Person::number_of_accounts() const {   // return number of acc
	size_t count = 0;
	for (auto a : accounts)
	{
		if (!a.second.expired()) ++count;  // should be not expired!!!! but it is
	}
	return count;
}

vector<int> Person::get_accounts_nrs()const {    // return vector of account numbers
	vector<int> str;
	for (auto a : accounts)
	{
		if (!a.second.expired()) str.push_back(a.first); // should be not expires!!! but it is
	}
	return str;
}

bool Person::share_account(shared_ptr<Person> other, int nr) {   // makes other authorized if he is not.
	
	for (auto a : accounts)
	{
		if (a.first == nr) {
			for (string s : a.second.lock()->get_authorized_persons()) // check if other is authorized, yes->false
			{
				if (s == other->name) return false;
			}

			for (string s : a.second.lock()->get_authorized_persons()) // check if this is authorized, no->false
			{
				if (s != this->name) return false;
			}

			a.second.lock()->add_authorized_person(other);
			other->accounts.insert({ nr,a.second });   // mb not needed
			return true;
		}
	}
	return false;
}

ostream& Person::print(ostream& o) const {
	size_t count = 0;
	o << "Name: " << name << ", {";

	for (auto a : accounts)
	{
		if (!a.second.expired()) {
			o << "[Nr.: " << a.first << ", "; 
			a.second.lock()->print_help(o);
			if (count < accounts.size() - 1) {
				o << ", ";
			}
			count++;
		}
	}
	o << '}';
	return o;
}
