#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

#include <map>
#include "BankAccount.hpp"

class AccountManager {
public:
    AccountManager();

    void addAccount(std::string username);
    void deleteAccount(std::string username);
    void displayAccount(std::string username);
    void makeDeposit(std::string username, double amount);
    void makeWithdrawal(std::string username, double amount);
    void addInterest();
    void writeCheck(std::string writer, std::string receiver, double amount);
    void serialize(const std::string& filename);
    void deserialize(const std::string& filename);
    void disburseLoan(std::string username, double amount);
    void loanEligibility(std::string username, double amount);
    void repayLoan(std::string username, double amount);

    int getNumAccounts();

    ~AccountManager();
private:
    std::map<std::string, BankAccount*> accts;
    int numAccounts;
};

#endif