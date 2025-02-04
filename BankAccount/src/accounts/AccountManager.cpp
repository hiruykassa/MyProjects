#include "AccountManager.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>

AccountManager::AccountManager(){
    accts = std::map<std::string, BankAccount*>();
    numAccounts = 0;
}

void AccountManager::addAccount(std::string username){
    if(accts.find(username) == accts.end()){
        BankAccount* b = makeAccount();
        accts[username] = b;
        numAccounts++;
    }
    else {
        errorMessage("Username already exist");
    }
}

void AccountManager::deleteAccount(std::string username){
    if(accts.find(username) != accts.end()){
        delete accts[username];
        accts.erase(username);
        numAccounts--;
    }
    else {
        errorMessage("Username does not exist");
    }
}

AccountManager::~AccountManager(){
    std::map<std::string, BankAccount*>::iterator it;
    
    for (it = accts.begin(); it != accts.end(); it++){
        BankAccount *acct = it->second;
        delete acct;
    }
}

void AccountManager::addInterest(){
    std::map<std::string, BankAccount*>::iterator it;

    for(it = accts.begin(); it != accts.end(); it++){
        if(dynamic_cast<SavingsAccount*>(it->second)){
            SavingsAccount *s = dynamic_cast<SavingsAccount*>(it->second);
            s->accrueInterest();
        }
    }

    for(it = accts.begin(); it != accts.end(); it++){
        if(dynamic_cast<CheckingAccount*>(it->second)){
            CheckingAccount *c = dynamic_cast<CheckingAccount*>(it->second);
            c->accrueLoanInterest();
        }
    }
}

void AccountManager::writeCheck(std::string writer, std::string receiver, double amount){
    if(accts.find(writer) == accts.end()){
        errorMessage("The writer account does not exist");

    }
    else if(accts.find(receiver) == accts.end()){
        errorMessage("The receiver account does not exist");
    }
    else{
        BankAccount *writerB = accts[writer];
        BankAccount *receiverB = accts[receiver];

        CheckingAccount *writerC = dynamic_cast<CheckingAccount*>(writerB);
        if(writerC != nullptr){
            writerC->writeCheck(*receiverB, amount);
            serialize(writer);
        }
        else{
            errorMessage("The account writing the check is not a checking account");
        }

    }
}

void AccountManager::makeDeposit(std::string username, double amount){
    if(accts.find(username) != accts.end()){
        BankAccount* b = accts[username];
        b->deposit(amount);
    }
    else {
        errorMessage("Username doesn't exist");
    }
}

void AccountManager::makeWithdrawal(std::string username, double amount){
    if(accts.find(username) != accts.end()){
        BankAccount* b = accts[username];
        b->withdrawal(amount);
    }
    else {
        errorMessage("Username doesn't exist");
    }
}

void AccountManager::displayAccount(std::string username){
    if(accts.find(username) != accts.end()){
        std::cout<<accts[username]->toString()<<std::endl;
    }
    else {
        errorMessage("Username doesn't exist");
    }
}

int AccountManager::getNumAccounts(){
    return numAccounts;
}

void AccountManager::serialize(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        errorMessage("Unable to open file for writing");
        return;
    }
    for (const auto& [username, account] : accts) {
        file << username << "," << account->serialize() << "\n";
    }

    file.close();
    statusMessage("Accounts successfully serialized to " + filename);
}

void AccountManager::deserialize(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        errorMessage("Unable to open file for reading");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> splitString;

        // Split the line into parts using Boost's split function
        boost::split(splitString, line, boost::is_any_of(","));

        if (splitString.size() < 6) {
            std::cerr << "Error: Invalid line format in file: " << line << std::endl;
            continue; // Skip this line if it doesn't have enough fields
        }

        std::string username = splitString[0];
        std::string accountType = splitString[1];
        std::string firstName = splitString[2];
        std::string lastName = splitString[3];

        char* end;
        double balance = strtod(splitString[4].c_str(), &end);
        if (*end != '\0') {
            std::cerr << "Error: Invalid balance format in line: " << line << std::endl;
            continue;
        }

        BankAccount* account = nullptr;

        if (accountType == "savings") {
            double interestRate = strtod(splitString[5].c_str(), &end);
            if (*end != '\0') {
                std::cerr << "Error: Invalid interest rate format in line: " << line << std::endl;
                continue;
            }
            account = new SavingsAccount(firstName, lastName, balance, interestRate);
        } else if (accountType == "checking") {
            // Deserialize the loan balance
            double loanBalance = strtod(splitString[5].c_str(), &end);
            if (*end != '\0') {
                std::cerr << "Error: Invalid loan balance format in line: " << line << std::endl;
                continue;
            }

            // Deserialize the check log until the "checks_end" marker
            std::list<double> checkLog;
            std::list<double> loanLog;

            size_t i = 6; // Start after loan balance
            while (i < splitString.size() && splitString[i] != "checks_end") {
                checkLog.push_back(std::stod(splitString[i]));
                ++i;
            }

            // Skip the "checks_end" marker
            if (i < splitString.size() && splitString[i] == "checks_end") {
                ++i;
            }

            // Deserialize the loan log
            for (; i < splitString.size(); ++i) {
                loanLog.push_back(std::stod(splitString[i]));
            }

            // Create the CheckingAccount with the checkLog and loanBalance
            account = new CheckingAccount(firstName, lastName, balance, checkLog, loanBalance, loanLog);
        }

        // If an account was created, store it in the map
        if (account) {
            accts[username] = account;
            numAccounts++;
        }
    }

    file.close();
}

void AccountManager::disburseLoan(std::string username, double amount) {
    if (accts.find(username) == accts.end()) {
        errorMessage("Account not found!");
        return;
    }
    CheckingAccount* account = dynamic_cast<CheckingAccount*>(accts[username]);
    if (account) {
        bool success = account->disburseLoan(amount);
        if (success)
        {
            statusMessage("Loan disbursed successfully!");
        }
        else
        {
            errorMessage("Loan disbursement failed.");
        }
    } else {
        errorMessage("Only checking accounts can receive loans.");
    }
}

void AccountManager::loanEligibility(std::string username, double amount) {
    if (accts.find(username) == accts.end()) {
        errorMessage("Account not found!");
        return;
    }

    CheckingAccount* account = dynamic_cast<CheckingAccount*>(accts[username]);
    if (account) {
        LoanEligibility eligibility = account->loanEligibility();

        if (eligibility.isEligible && amount <= eligibility.maxLoanAmount) {
            statusMessage("Loan is eligible.");
        } else if (!eligibility.isEligible) {
            statusMessage("Loan is not eligible for this account.");
        } else {
            statusMessage("Loan exceeds eligibility limit.");
        }
    } else {
        errorMessage("Only checking accounts have loan eligibility.");
    }
}

// This function serves as a 

void AccountManager::repayLoan(std::string username, double amount) {
    if (accts.find(username) == accts.end()) {
        errorMessage("Account not found!");
        return;
    }
    CheckingAccount* account = dynamic_cast<CheckingAccount*>(accts[username]);
    if (account) {
        account->loanRepayment(amount);
    } else {
        errorMessage("Only checking accounts can repay loans.");
        }
}