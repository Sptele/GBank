#include <string>
#include <iostream>
#include <optional>

#include "User.h"
#include "Utility.h"
#include "DatabaseManager.h"

#pragma once
class SignInManager
{
public:
	static std::optional<User> log_in();
	static std::optional<User> sign_up();
};

