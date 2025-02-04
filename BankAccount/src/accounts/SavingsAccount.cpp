#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(std::string first, std::string last, double initBalance, double interest) : BankAccount(first, last, initBalance){
    interestRate = interest;
}

SavingsAccount::SavingsAccount(std::string first, std::string last, double interest) : BankAccount(first, last){
    interestRate = interest;
}

void SavingsAccount::accrueInterest(){
    double interest = interestRate * getBalance();
    deposit(interest);
}

std::string SavingsAccount::toString(){
    return "Savings Account Balance: $" + std::to_string(getBalance()) + ", Interest Rate: "+std::to_string(interestRate);
}

double SavingsAccount::getInterestRate(){
    return interestRate;
}

void SavingsAccount::setInterestRate(double interest){
    interestRate = interest;
}

std::string SavingsAccount::serialize(){
    return "savings," + getFirstName() + "," + getLastName() + "," + std::to_string(getBalance()) + "," + std::to_string(interestRate);
}