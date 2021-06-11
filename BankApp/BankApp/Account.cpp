#include "Account.h"


Account::Account(int nr, int limit, int balance, shared_ptr<Person> p) :nr{ nr }, limit{ limit },
balance{ balance }
{
	this->add_authorized_person(p);
	if (nr <= 0) throw runtime_error("Nummerr<0");
	if (limit < 0) throw runtime_error("Limit < 0");
	if (balance < (-limit)) throw runtime_error("Balance < dispo");
}

int Account::get_nr()const {
	return nr;
}

// return the list of the only authorized persons
vector<string> Account::get_authorized_persons()const {
	vector<string> str;
	for (auto p : persons)
	{
		if (!p.second.expired()) str.push_back(p.first);
	}
	return str;
}

size_t Account::number_of_owners()const {
	size_t count = 0;
	for (auto p : persons)
	{
		if (!p.second.expired()) ++count;
	}
	return count;
}

bool Account::add_authorized_person(shared_ptr<Person> p) { 
	for (auto pp : persons)
	{
		if (pp.second.lock() == p) {
			return false;
		}
	}
	
	persons.insert({ p->get_name(),p });
	return true; 
}

bool Account::transfer(shared_ptr<Account> target, int x) {
	int new_balance = this->balance - x;
	if (new_balance >= -limit) {
		this->balance -= x;
		target->balance += x;

		target->fee += target->calc_fee(x);
		this->fee += this->calc_fee(x);
		return true;
	}

	return false;
}

ostream& Account::print(ostream& o)const {
	size_t count = 0;
	o << "Nr.: " << nr << ", [" << balance << '/' << limit << "], Fees:" << fee << ", Owners: {";
	for(auto p: persons) if (p.second.expired()) count++;

	for (auto p : persons)
	{
		if (count < persons.size() - 1 ) {
			if (!p.second.expired()) {
				o << "[Name: " << p.first << ", {";

				for (size_t i = 0; i < p.second.lock()->get_accounts_nrs().size(); i++)
				{
					o << p.second.lock()->get_accounts_nrs().at(i);
					if(i< p.second.lock()->get_accounts_nrs().size()-1) o<<", ";
				}
				o << "}],";
			}
			count++;
		}
		else {
			if (!p.second.expired()) {
				o << "[Name: " << p.first << ", {";
				for (size_t i = 0; i < p.second.lock()->get_accounts_nrs().size(); i++)
				{
					o << p.second.lock()->get_accounts_nrs().at(i);
					if (i < p.second.lock()->get_accounts_nrs().size() - 1) o << ", ";
				}
				o << "}]";
			}
		}
	}
	o << '}';
	return o;
}

ostream& Account::print_help(ostream& o) const {

	o << "[" << balance << "/" << limit << "], Fees: " << fee << ", Owners:{";
	for (size_t i = 0; i < this->get_authorized_persons().size(); i++) {
		o << this->get_authorized_persons().at(i);
		if (i < this->get_authorized_persons().size() - 1)o << ",";
	}
	o << "}]";
	return o;
}
//GIRO ACCOUNT

GiroAccount::GiroAccount(int nr, int balance, int limit, shared_ptr<Person>p, double fee) :
	Account(nr, balance, limit, p), fee_factor{ fee }
{
	if (fee < 0) throw runtime_error("Fee<0");
}

double GiroAccount::calc_fee(int)const {
	return fee_factor;
}

//BusinessAccount

BusinessAccount::BusinessAccount(int nr, int balance, int limit, shared_ptr<Person>p, double fee) :
	Account(nr,balance,limit,p), fee_factor{fee}
{
	if (fee < 0) throw runtime_error("Fee<0");
}

double BusinessAccount::calc_fee(int x) const {
	return fee_factor * x;
}