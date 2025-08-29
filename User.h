#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

#pragma once
class User {
private:
	unsigned int num;

public:
	long id;
	std::string username;
	std::string password;

	double balance;
	std::vector<std::string> transactions;

	User() : id(0), username(""), password(""), balance(0), num(1 + (std::rand() % 10)) {}
	User(long id, const std::string& uname, const std::string& password) : id(id), username(uname), 
		password(password), balance(0), num(1 + (std::rand() % 10)) {}
	User(long id, const std::string& uname, const std::string& password, double balance) : id(id), username(uname), 
		password(password), balance(balance), num(1 + (std::rand() % 10)) {}
	User(long id, const std::string& uname, const std::string& password, double balance, std::vector<std::string> t) : 
		id(id), username(uname), password(password), balance(balance), num(1 + (std::rand() % 10)), transactions(t) 
	{}

	void add_balance(const double amount);
	void subtract_balance(const double amount);

	void add_transaction(const std::string& trans);

	void check_overdraft();

	std::string to_CSV() const;

	void view_balance();
	void withdraw_balance();
	void deposit_balance();
	void generate_statement();
	void change_username();
	void change_password();
	void fee_policy();
	void wipe();
};

