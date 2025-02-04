#include "CheckingAccount.hpp"
#include <iostream>
#include "BankAccount.hpp"

bool CheckingAccount::writeCheck(BankAccount &a, double amount){
    bool success = withdrawal(amount);

    if(success){
        a.deposit(amount);
        checkLog.push_back(amount);
    }

    return success;
}

std::string CheckingAccount::toString(){
    return "Checking Account Balance: $" + std::to_string(getBalance()) + ", wrote " + std::to_string(checkLog.size()) + " checks\n" + "Loan Balance: $" + std::to_string(getLoanBalance()) + ", " + std::to_string(loanLog.size()) + " Loans taken.";
}

std::list<double> CheckingAccount::getCheckLog(){
    return checkLog;
}

std::string CheckingAccount::serialize() {
    std::string serialized = "checking," + getFirstName() + "," + getLastName() + "," + std::to_string(getBalance())
                            + "," + std::to_string(getLoanBalance());  // Serialize loan balance

    // Serialize each check amount individually
    for (double check : checkLog) {
        serialized += "," + std::to_string(check);  // Serialize the individual check amounts
    }

    // Add a marker indicating the end of the check log
    serialized += ",checks_end";

    // Serialize each loan amount in the loan log
    for (double loan : loanLog) {
        serialized += "," + std::to_string(loan);  // Serialize each loan amount
    }

    return serialized;
}

double CheckingAccount::getLoanBalance(){
    return loanBalance;
}

void CheckingAccount::setLoanBalance(double balance){
    loanBalance = balance;
}

void CheckingAccount::accrueLoanInterest(){
    double loanInterest = (getLoanInterestRate() * getLoanBalance())+ getLoanBalance();
    setLoanBalance(loanInterest);
}

double CheckingAccount::getLoanInterestRate(){
    return loanInterestRate;
}

LoanEligibility CheckingAccount::loanEligibility() {
    LoanEligibility eligibility;
    eligibility.currentBalance = getBalance();
    eligibility.maxLoanAmount = eligibility.currentBalance * 0.5;
    eligibility.currentLoanBalance = getLoanBalance();
    eligibility.remainingEligibility = eligibility.maxLoanAmount - eligibility.currentLoanBalance;

    eligibility.isEligible = eligibility.remainingEligibility > 0;

    return eligibility;
}



bool CheckingAccount::disburseLoan(double loanAmount) {
    if (loanAmount <= 0) {
        errorMessage("Loan amount must be positive.");
        return false;
    }

    LoanEligibility eligibility = loanEligibility();

    if (!eligibility.isEligible || loanAmount > eligibility.remainingEligibility) {
        errorMessage("Loan request exceeds eligibility or account is not eligible for a loan.");
        return false;
    }

    setLoanBalance(getLoanBalance() + loanAmount);
    loanLog.push_back(loanAmount); 
    return true;
}




std::list<double> CheckingAccount::getLoanLog(){
    return loanLog;
}

void CheckingAccount::loanRepayment(double amount) {
    if (amount <= 0) {
        errorMessage("Repayment amount must be positive.");
        return;
    }

    double new_balance = getLoanBalance() - amount;

    if (new_balance < 0) {
        errorMessage("Sorry, you cannot repay more than you owe!");
        return;
    }

    setLoanBalance(new_balance);
    loanLog.push_back(-amount);
}
