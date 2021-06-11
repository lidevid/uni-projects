#include "Bank.h"
#include"AccountCollection.h"
#include<iostream>
using namespace std;

int main()
{
	Bank bank;
	bank.create_person("Niklas B", 1, 2000, 0, 0, 0.05);
	bank.create_person("Mateo R", 2, 0, 100, 1, 0.03);
	bank.print_customers(cout);
	cout << "\n";
	bank.print_accounts(cout);
	cout << "\n";

	auto acc_one = bank.get_account(1);
	auto acc_two = bank.get_account(2);

	auto nik = bank.get_person("Niklas B");
	auto mat = bank.get_person("Mateo R");

	acc_one->transfer(acc_two, 500);
	bank.print_customers(cout);
	cout << "\n";
	bank.print_accounts(cout);
	cout << "\n";

	mat->share_account(nik, 2);
	bank.print_customers(cout);
	cout << "\n";
	bank.print_accounts(cout);
	cout << "\n";

	acc_two->transfer(acc_one, 601);
	bank.print_customers(cout);
	cout << "\n";
	bank.print_accounts(cout);
	cout << "\n"<<"STOP"<<"\n";

	bank.remove_account(2);
	bank.print_customers(cout);
	cout << "\n";
	bank.print_accounts(cout);
	cout << "\n";

	bank.remove_person("Niklas B");
	bank.print_customers(cout);
	cout << "\n";
	bank.print_accounts(cout);
	cout << "\n";
	cout << "Aufgabe 2" << "\n";

	Bank bank2;
	bank2.create_person("Niklas B", 1, 2000, 0, 3, 0.05);
	bank2.create_person("Temp", 2, 2000, 0, 0, 0.05);

	auto p_nik= bank2.get_person("Niklas B");
	auto p_temp = bank2.get_person("Temp");
	p_temp->share_account(p_nik, 2);

	bank2.remove_person("Temp");

	bank2.create_person("Matteo R", 3, 1000, 0, 2, 0.03);
	auto p_mat = bank2.get_person("Matteo R");

	auto account1 = bank2.get_account(1);
	auto account2 = bank2.get_account(2);
	auto account3 = bank2.get_account(3);

	cout<<account1->calc_bonus();
	cout<<account2->calc_bonus();
	cout<<account3->calc_bonus();
	cout << "\n";
	bank2.print_accounts(cout);
	cout << "\n";

	p_mat->share_account(p_nik, 3);

	cout << account1->calc_bonus();
	cout << account2->calc_bonus();
	cout << account3->calc_bonus();
	cout << "\n";
	bank2.print_accounts(cout);
	cout << "\n";
	cout << "Aufgabe 3" << "\n";

	Bank bank3;
	bank3.create_person("Niklas B", 1, 2000, 0, 1, 0.05);
	auto perm_nik = bank3.get_person("Niklas B"); 

	bank3.create_person("Temp", 2, 2000, 0, 3, 0.05);  // 1st temp person
	auto temp=bank3.get_person("Temp");
	temp->share_account(perm_nik, 2);
	bank3.remove_person("Temp");

	bank3.create_person("Temp1", 3, 2000, 0, 0, 0.05);  // 2nd temp person
	auto temp1 = bank3.get_person("Temp1");
	temp1->share_account(perm_nik, 3);
	bank3.remove_person("Temp1");

	bank3.create_person("Temp2", 4, 2000, 0, 2, 0.05);  // 3rd temp person
	auto temp2 = bank3.get_person("Temp2");
	temp2->share_account(perm_nik, 4);
	bank3.remove_person("Temp2");

	vector<weak_ptr<Account>>acc{ bank3.get_account(1) ,bank3.get_account(2) ,
		bank3.get_account(3),bank3.get_account(4) };

	AccountCollection coll{ acc };
	cout<<coll.calc_boni();
	bank3.print_accounts(cout);
	cout << "\n";


	Bank bank4;
	bank4.create_person("Matteo R", 1, 2000, 0, 1, 0.05);
	auto perm_mat = bank4.get_person("Matteo R");

	bank4.create_person("Temp", 2, 2000, 0, 3, 0.05);  // 1st temp person
	auto temp_b4 = bank4.get_person("Temp");
	temp_b4->share_account(perm_mat, 2);
	bank4.remove_person("Temp");

	bank4.create_person("Temp1", 3, 2000, 0, 0, 0.05);  // 2nd temp person
	auto temp1_b4 = bank4.get_person("Temp1");
	temp1_b4->share_account(perm_mat, 3);
	bank4.remove_person("Temp1");

	bank4.create_person("Temp2", 4, 2000, 0, 2, 0.05);  // 3rd temp person
	auto temp2_b4 = bank4.get_person("Temp2");
	temp2_b4->share_account(perm_mat, 4);
	bank4.remove_person("Temp2");

	vector<weak_ptr<Account>>acc1{ bank4.get_account(1) ,bank4.get_account(2) ,
		bank4.get_account(3),bank4.get_account(4) };

	AccountCollection coll1{ acc1 };
	cout << coll1.calc_boni();
	bank4.print_accounts(cout);

	return 0;
}