#include "DatabaseManager.h"

std::string DatabaseManager::REGISTRY_PATH = "REGISTRY.csv";

User DatabaseManager::CREATE(const std::string& uname, const std::string& password)
{
    User user{ std::rand(), uname, password };
    user.password = std::to_string(Utility::hash(password)); // Security measure

    std::ofstream registry(REGISTRY_PATH, std::ios::app);

    if (registry.is_open()) {
        registry << std::to_string(user.id) << "," << user.username << "," << user.password << "," << user.balance << ",[]" << "\n";
        registry.close();
    }
    
    return user;
}

User DatabaseManager::READ(const std::string& uname)
{
    std::ifstream registry(REGISTRY_PATH, std::ios::in);

    User u;

    std::string line;
    if (registry.is_open()) {
        while (std::getline(registry, line)) {
            size_t index_uname = line.find(',') + 1;

            if (line.substr(index_uname, uname.length()) == uname) {
                // Found it!

                std::vector<std::string> s_line = Utility::split(line, ',');

                std::string v = s_line.at(4);

                std::string v_sub = v.substr(1, v.length() - 2); // Remove brackets or quotes as needed
                Utility::replace_all(v_sub, "\"", "");

                u = User{
                    std::stol(s_line.at(0)), // id[0]
                    s_line.at(1), // uname
                    s_line.at(2), // password (as a hash)
                    std::stod(s_line.at(3)), // balance
                    Utility::split(v_sub, ',') // trans
                };

                break;
            }
        }

        registry.close();
    }

    return u;
}

void DatabaseManager::UPDATE(const User& user)
{
    std::vector<std::string> lines;

    std::ifstream i_registry(REGISTRY_PATH, std::ios::in);

    std::string line;
    if (i_registry.is_open()) {

        // Generate copy
        while (std::getline(i_registry, line)) {
            size_t end_id = line.find(',');

            if (line.substr(0, end_id) == std::to_string(user.id)) {
                // Found it!

                line = user.to_CSV();
            }

            lines.push_back(line);
        }

        i_registry.close();
    }

    std::ofstream o_registry(REGISTRY_PATH, std::ios::out);
    
    if (o_registry.is_open()) {
        for (std::string line : lines) {
            o_registry << line << "\n"; // \n NOT included in file
        }

        o_registry.close();
    }

    // Full rewrite


}

User DatabaseManager::DELETE(const User& user)
{
    // TODO: DON'T FINISH THIS!!! NEVER DELETE ACCOUNTS!
    return User();
}



bool DatabaseManager::HASUSER(const std::string& uname)
{
    std::ifstream registry(REGISTRY_PATH, std::ios::in);

    std::string line;
    if (registry.is_open()) {
        while (std::getline(registry, line)) {
            size_t index_uname = line.find(',') + 1;

            if (line.substr(index_uname, uname.length()) == uname) {
                // Found it!
                return true;
            }
        }

        registry.close();
    }

    return false;
}

size_t DatabaseManager::GETPASSH(const std::string& uname)
{
    std::ifstream registry(REGISTRY_PATH, std::ios::in);

    size_t hash{};

    std::string line;
    if (registry.is_open()) {
        while (std::getline(registry, line)) {
            size_t index_uname = line.find(',') + 1;

            if (line.substr(index_uname, uname.length()) == uname) {
                // Found it!

                hash = std::stoull(line.substr(index_uname + uname.length() + 1, line.size() - (index_uname + uname.length() + 1)));

                break;//10
            }

        }

        registry.close();
    }

    return hash;
}

bool DatabaseManager::INITIALIZE() {

    std::ifstream reader(REGISTRY_PATH, std::ios::in);

    bool succ = false;

    if (!reader.is_open()) {

        std::ofstream registry(REGISTRY_PATH, std::ios::out);

        if (registry.is_open() && reader.peek() == std::ifstream::traits_type::eof()) {
            registry << "ID,USERNAME,PASSWORD,BALANCE,TRANSACTIONS" << "\n";
        }

        registry.close();
    }

    if (reader.is_open()) succ = true;

    reader.close();

    return succ;
}
