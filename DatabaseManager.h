#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>

#include "Utility.h"
#include "User.h"

#pragma once
class DatabaseManager // CRUD
{
public:
	static std::string REGISTRY_PATH;

	static User CREATE(const std::string& uname, const std::string& password);
	static User READ(const std::string& uname);
	static void UPDATE(const User& user);
	static User DELETE(const User& user);

	static bool HASUSER(const std::string& uname);
	static size_t GETPASSH(const std::string& uname);

	static bool INITIALIZE();
	
};


