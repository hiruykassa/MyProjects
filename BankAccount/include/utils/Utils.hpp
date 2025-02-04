#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

BankAccount* makeAccount();

void statusMessage(std::string msg);

void errorMessage(std::string err);

std::string getOption();

double getDouble(std::string prompt);

std::string getString(std::string prompt);

