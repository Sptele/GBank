#include <string>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>

#include "User.h"
#include "Utility.h"

#pragma once
class BankFunctions
{
private:
	unsigned int num;
public:
	User& SU;

	BankFunctions(User& su) : SU(su) {
		num = 1 + (std::rand() % 10);
	}

	void view_balance(); // #1
	void withdraw_balance();
	void deposit_balance();
	void generate_statement();
	void change_username();
	void change_password();
	void fee_policy();
	void wipe();

};

