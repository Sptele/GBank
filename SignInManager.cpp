#include "SignInManager.h"

std::optional<User> SignInManager::log_in()
{
	while (true) {
		std::string uname = Utility::prompt("Please enter your username: (Type 'cancel' to cancel)");

		if (uname == "cancel") return {};

		std::string password = Utility::prompt("Please enter your password: (Type 'cancel' to cancel)");

		if (password == "cancel") return {};

		if (!DatabaseManager::HASUSER(uname)) {
			std::cout << "That username was not found. Check for typos, or do you want to create an account?" << std::endl;

			continue;
		}

		if (Utility::hash(password) != DatabaseManager::GETPASSH(uname)) {
			std::cout << "Incorrect password! Try again." << std::endl;

			continue;
		}

		std::cout << "Logging you in..." << std::endl;

		return DatabaseManager::READ(uname);
	}
}

std::optional<User> SignInManager::sign_up()
{
	while (true) {
		std::string uname = Utility::prompt("Please enter a username: (Type 'cancel' to cancel)");

		if (uname == "cancel") return {};

		std::string password = Utility::prompt("Please enter a password: (Type 'cancel' to cancel)");

		if (password == "cancel") return {};

		if (uname.find(',') != std::string::npos || password.find(',') != std::string::npos) {
			std::cout << "Usernames and passwords may not contain commas! Try again." << std::endl;

			continue;
		}

		std::cout << "Account created successfully!" << std::endl;

		return DatabaseManager::CREATE(uname, password);
	}
}
