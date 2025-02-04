#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP

#include "BankAccount.hpp"
#include "Utils.hpp"
#include <list>

struct LoanEligibility {
    double currentBalance;
    double maxLoanAmount;
    double currentLoanBalance;
    double remainingEligibility;
    bool isEligible;
};


class CheckingAccount : public BankAccount {
public:
    CheckingAccount(std::string first, std::string last, double initBalance, std::list<double> checks, double loanbal, std::list<double> loans) 
        : BankAccount(first, last, initBalance), checkLog(checks), loanBalance(loanbal), loanLog(loans) {};
    CheckingAccount(std::string first, std::string last, double initBalance)
    : BankAccount(first, last, initBalance), loanInterestRate(0.05), loanBalance(0) {}; 

    CheckingAccount(std::string first, std::string last) 
    : BankAccount(first, last), loanInterestRate(0.05), loanBalance(0) {};
    bool writeCheck(BankAccount &a, double amount);

    std::string toString();
    std::string serialize() override;

    std::list<double> getCheckLog();
    double getLoanBalance();
    
    void setLoanBalance(double balance);
    
    void accrueLoanInterest();
    
    double getLoanInterestRate();
    
    LoanEligibility loanEligibility();
    
    bool disburseLoan(double loanAmount);
    
    std::list<double> getLoanLog();
    
    void loanRepayment(double amount);

    ~CheckingAccount() {}

private:
    std::list<double> checkLog;
    const double loanInterestRate = 0.05;
    double loanBalance;
    std::list<double> loanLog;
};


#endif