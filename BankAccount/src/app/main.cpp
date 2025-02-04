#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "AccountManager.hpp"
#include "Utils.hpp"
#include <fstream>

#include <stdexcept>

int main(){
    statusMessage("Welcome to the banking software!");

    AccountManager accts;

    // File for saving and loading account data
    const std::string filename = "accounts.csv";

    // Attempt to deserialize from the file
    std::ifstream file(filename);
    if (file.good()) {
        file.close();
        accts.deserialize(filename);
        statusMessage("Accounts loaded successfully from " + filename);
    } else {
        file.close();
        statusMessage("No existing accounts file found. Starting fresh.");
    }

    bool finished = false;

    while(!finished){
        std::string inputString = getOption();
        if(inputString == "0"){
            accts.serialize("accounts.csv");
            statusMessage("Thank you for using the software");
            finished = true;
        }
        else if(inputString == "1"){
            std::string user = getString("Enter the username:");

            accts.addAccount(user);
        }  
        else if(inputString == "2"){
            std::string user = getString("Enter the username:");

            try{
                double deposit_amount = getDouble("Enter amount:");
                accts.makeDeposit(user,deposit_amount);
            }
            catch(std::invalid_argument e){
                errorMessage("I'm sorry, that is not a deposit amount.");
            }
        }
        else if(inputString == "3"){
            std::string user = getString("Enter the username:");

            try{
                double withdrawal_amount = getDouble("Enter amount:");
                accts.makeWithdrawal(user, withdrawal_amount);
            }
            catch(std::invalid_argument e){
                errorMessage("I'm sorry, that is not a withdrawal amount.");
            }
        }
        else if(inputString == "4"){
            std::string user = getString("Enter the username:");

            accts.displayAccount(user);
        }
        else if(inputString == "5"){
            accts.addInterest();
        }
        else if(inputString == "6"){
            std::string user = getString("Enter the username of the account writing the check:");
            std::string target_account = getString("Enter the username of the account cashing the check:");

            try{
                double check_amount = getDouble("Enter amount:");   
                accts.writeCheck(user, target_account, check_amount); 
            }
            catch(std::invalid_argument e){
                errorMessage("I'm sorry, that is not a withdrawal amount.");
            }
        }
        else if (inputString == "7") 
        {
            std::string user = getString("Enter the username:");
            double loanAmount = getDouble("Enter loan amount:");
            accts.disburseLoan(user, loanAmount);
        } 
        else if (inputString == "8") 
        {
            std::string user = getString("Enter the username:");
            double loanAmount = getDouble("Enter loan amount:");
            accts.loanEligibility(user, loanAmount);
        }
        else if (inputString == "9") {
            std::string user = getString("Enter the username:");
            double repaymentAmount = getDouble("Enter repayment amount:");
            accts.repayLoan(user, repaymentAmount);
        }
        else{
            errorMessage("I'm sorry, that is not a valid choice.");
        }
    }

    return 0;
}