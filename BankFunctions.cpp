#include "BankFunctions.h"

void BankFunctions::view_balance()
{
	if (num == 6/*7*/) {
		// some trolling

		std::cout << "[ERROR] Unable to retrieve current balance statement. Please try again later." << std::endl;
		std::cout << "[WARNING] DO NOT terminate the Virtual ATM program at this time while internal diagnostics are running in the background." << std::endl;
		std::cout << " -- Premature program termination may result in accidental account withdrawal, termination, or fees!" << std::endl;
	}

	std::cout << "Current Balance: $" << SU.balance << std::endl << std::endl;
	std::cout << " -- Note: You may have had fees applied to your balance. These fees are automatically drafted " <<
		"from your balance. To check, open your transaction statement." << std::endl;

	SU.add_transaction("VIEW Balance $" + std::to_string(SU.balance));
}

void BankFunctions::withdraw_balance()
{
	while (true) {
		std::optional<double> prompted = Utility::prompt_money("How much money would you like to withdraw? Overdraft fees apply where applicable. (Double)");

		if (!prompted.has_value()) continue;

		double v = prompted.value();

		SU.subtract_balance(v);
		SU.add_transaction("WITHDRAW $" + std::to_string(v));

		SU.check_overdraft();

		std::cout << "$" << v << " withdrawn from account. Cash will be mailed within 4-6 business weeks to nearest 7-Eleven Cash Register." << std::endl;

		return;
	}
}

void BankFunctions::deposit_balance()
{
	while (true) {
		std::optional<double> prompted = Utility::prompt_money("How much money would you like to deposit? (Positive Double)");

		if (!prompted.has_value()) continue;

		double v = prompted.value();

		if (v < 0) v *= -1; // Make positive

		SU.add_balance(v);
		SU.add_transaction("DEPOSIT $" + std::to_string(v));

		std::cout << "$" << v << " desposited into account. Cash or Check must be mailed with 2 business days to nearest Mountain Mikes. Credit NOT accepted." << std::endl;

		return;
	}
}

void BankFunctions::generate_statement()
{
	std::cout << "Account Statement Generated In Local Directory...\n";

	std::time_t t_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm tm_now;
	localtime_s(&tm_now, &t_now); // Fills tm_now with local time info

	std::ostringstream oss;
	oss << std::put_time(&tm_now, "%Y-%m-%d");
	std::string formatted = oss.str();

	std::ofstream stmt("Gbank_Statement[" + formatted + "].txt", std::ios::out);

	if (stmt.is_open()) {

		stmt << SU.id << "\t\t\tUser: " << SU.username << "\n\nAccount Summary " << formatted << ":\n\n";

		stmt << "\tTotal Balance: $" << SU.balance << "\n\n";

		stmt << "Transactions:\n";

		if (SU.transactions.empty()) {
			stmt << "\t\t\tNo Statements on Record" << "\n";
		}
		else {
			for (size_t i = 0; i < SU.transactions.size(); i++) {
				stmt << "\t" << (i + 1) << ". " << SU.transactions.at(i) << "\n";
			}
		}

		stmt << "\n\t\tGBank Virtual ATM Interface";

		stmt.close();
	}
}

void BankFunctions::change_username()
{
	while (true) {
		std::string uname = Utility::prompt("Please enter a new username:");

		if (uname.find(',') != std::string::npos) {
			std::cout << "Usernames may not contain commas! Try again." << std::endl;

			continue;
		}

		std::cout << "Username changed to " << uname << "!" << std::endl;

		SU.username = uname;

		return;
	}
}

void BankFunctions::change_password()
{
	while (true) {
		std::string password = Utility::prompt("Please enter current password:");

		if (Utility::hash(password) != std::stoull(SU.password)) {
			std::cout << "Incorrect password! Try again." << std::endl;

			continue;
		}

		if (password.find(',') != std::string::npos) {
			std::cout << "Passwords may not contain commas! Try again." << std::endl;

			continue;
		}

		password = Utility::prompt("Please enter new password:");

		if (password.find(',') != std::string::npos) {
			std::cout << "Passwords may not contain commas! Try again." << std::endl;

			continue;
		}

		std::cout << "Password changed successfully! No confirmation needed :)" << std::endl;

		SU.password = std::to_string(Utility::hash(password));

		return;
	}
}

void BankFunctions::fee_policy()
{
	bool are_you_sureeee = Utility::prompt("Are you sure you want to view the fee policy? Doing so may have unintended consequences! (y/n)") == "y";

	if (!are_you_sureeee) return;

	std::cout << "GBank FEE POLICY" << std::endl << std::endl
		<< "- Monthly Maintenance Fee:\t\t$25" << std::endl
		<< "- ATM Usage (Non-GBank):\t\t$6.50 per transaction" << std::endl
		<< "- Paper Statement Fee:\t\t$9.99 per month" << std::endl
		<< "- Virtual Statement Fee:\t\t$4.99 per week" << std::endl
		<< "- Customer Service Call:\t\t$14.00 per call (hold music included)" << std::endl
		<< "- Account Closure Fee:\t\tNot Available at this Time" << std::endl << std::endl;
		
	std::cout << "GBank Overdraft Policy" << std::endl << std::endl
		<< "- Overdraft Fee:\t\t$35" << std::endl
		<< "  • Automatically deducted from your current balance" << std::endl
		<< "  • Applies per transaction" << std::endl
		<< "  • Applies even if the overdraft is $0.01" << std::endl
		<< "  • Applies even if you didn’t know" << std::endl << std::endl;

	std::cout << "- Transparency Fee:\t\t$19.67" << std::endl
		<< "  • Charged just now to your bank account for view the fee policy" << std::endl;

	std::cout << "GBank Virtual ATM Interface" << std::endl;

	SU.subtract_balance(19.67);

	SU.add_transaction("FEE (Transparency) $19.67");

	SU.check_overdraft();
}

void BankFunctions::wipe()
{
	// W bank
	std::cout << "Invalid option! Default option selected..." << std::endl;
	std::cout << "Balance wiped and donated to the GBank Foundation for Billionaire Tax Evasion & Fraud." << std::endl;

	SU.add_transaction("WITHDRAW (WIPE/DNT GBFBTEF LLC) $" + std::to_string(SU.balance));

	SU.balance = -70;

	SU.add_transaction("FEE (Overdraft) $35");
	SU.add_transaction("FEE (Overdraft) $35");
}
