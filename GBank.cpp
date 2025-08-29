#include <iostream>
#include <string>
#include <random>

#include "BankFunctions.h"
#include "DatabaseManager.h"
#include "User.h"
#include "SignInManager.h"

int main()
{
	bool suc = DatabaseManager::INITIALIZE();

	if (!suc) {
		std::cout << "[FATAL ERROR] Unable to initialize registry!" << std::endl;

		return 1;
	}

	while (true) {
		std::cout << Utility::BAR_DIVIDER_TM_C << std::endl
			<< "Welcome to the GBank virtual ATM! We value your business."  << std::endl
			<< Utility::BAR_DIVIDER_TM_C << std::endl << std::endl;

		bool has_acc = Utility::prompt("Do you have an account with us? (y/n)") == "y";

		std::optional<User> o_su = has_acc ? SignInManager::log_in() : SignInManager::sign_up();
		bool logged_in = true;

		if (!o_su.has_value()) continue; // retry

		User SU = o_su.value();

		while (logged_in) {
			std::cout << std::endl << Utility::BAR_DIVIDER_TM_C << std::endl
				<< "Welcome " << SU.username << "! What would you like to do today? (Enter as only a number)" 
				<< std::endl << Utility::BAR_DIVIDER_TM_C << std::endl;
			std::string s_op = Utility::prompt(
				std::string("\t1. Check Your Balance\n") +
				"\t2. Withdraw Money\n" +
				"\t3. Deposit Money\n" +
				"\t4. Get an Account Statement\n" +
				"\t5. Change Your Username\n" +
				"\t6. Change Your Password\n" +
				"\t7. View Fee Policy\n" +
				"\t8. Sign Out\n"
			);

			BankFunctions man{ SU };

			if (!Utility::str_isdigit(s_op)) {
				man.wipe();

				continue;
			}

			switch (std::stoi(s_op)) {
			case 1: // Check # of $
				man.view_balance();

				break;
			case 2: // Withdraw $
				man.withdraw_balance();

				break;
			case 3: // Deposit $
				man.deposit_balance();

				break;
			case 4: // Account Statement
				man.generate_statement();

				break;
			case 5: // Change Username
				man.change_username();

				break;
			case 6: // Change Password
				man.change_password();

				break;
			case 7: // View Fee Policy
				man.fee_policy();

				break;
			case 8: // Sign Out
				logged_in = false;

				break;
			default: // troll
				man.wipe();

				break;
			}

			// Update DB
			DatabaseManager::UPDATE(SU);
		}
	}

	return 0;
}