#include "User.h"

void User::add_balance(const double amount)
{
    balance += amount;
}

void User::subtract_balance(const double amount)
{
    balance -= amount;
}

// Automatically captures timestamp
void User::add_transaction(const std::string& trans)
{
    std::time_t t_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm_now;
    localtime_s(&tm_now, &t_now); // Fills tm_now with local time info

    std::ostringstream oss;
    oss << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S");
    std::string formatted = oss.str();

    transactions.push_back("GBVAM[" + formatted + "] " + trans);
}

void User::check_overdraft()
{
    if (balance < 0) {
        subtract_balance(35); // Overdraft fee: $35

        add_transaction("FEE (Overdraft) $35");
    }
}

std::string User::to_CSV() const
{
    std::ostringstream oss;

    oss << id << "," << username << "," << password /* Already hashed */ << "," << balance << ",";

    oss << "[";
    for (size_t i = 0; i < transactions.size(); i++) {
        oss << "\"" << transactions[i] << "\"";
        if (i != transactions.size() - 1)
            oss << ", ";
    }
    oss << "]";

    oss << "\n"; // EOL

    return oss.str();
}