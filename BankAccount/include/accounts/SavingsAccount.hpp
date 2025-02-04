#ifndef SAVINGSACCOUNT_HPP
#define SAVINGSACCOUNT_HPP

#include "BankAccount.hpp"

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(std::string first, std::string last, double initBalance, double interest);
    SavingsAccount(std::string first, std::string last, double interest);

    double getInterestRate();

    void setInterestRate(double interest);

    void accrueInterest();

    std::string toString();

    std::string serialize() override;

    ~SavingsAccount() {}

private:
    double interestRate;
};

#endif