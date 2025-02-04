#include "Utils.hpp"
#include <iostream>
#include <stdexcept>

BankAccount* makeAccount(){
    BankAccount *acct = nullptr;

    std::string first = getString("Enter the first name:");

    std::string last = getString("Enter the last name:");

    std::string choice = getString("Would you like to make a savings (1) or checking (2) account:");
    if(choice == "1"){
        try{
            double interest_rate = getDouble("Enter the interest rate:");
            acct = new SavingsAccount(first, last, interest_rate);
        }
        catch(std::invalid_argument e){
            errorMessage("I'm sorry, that is not a valid interest rate.");
        }
    }
    else if(choice == "2"){
        acct = new CheckingAccount(first, last);
    }
    else{
        errorMessage("I'm sorry, that is not a valid choice.");
    }

    return acct;
}

void statusMessage(std::string msg){
    std::cout << msg << std::endl;
}

void errorMessage(std::string err){
    std::cout << "[ERROR] " << err << std::endl;
}

double getDouble(std::string prompt){
    std::cout << prompt;
    std::string deposit_amount_string;
    std::cin>> deposit_amount_string;

    double deposit_amount;
    
    char *end;
    deposit_amount = strtod(deposit_amount_string.c_str(), &end);
    if(*end == '\0'){
        return deposit_amount;
    }
    else{
        throw std::invalid_argument("Invalid input");
    }
}

std::string getString(std::string prompt){
    std::cout << prompt;
    std::string input;
    std::cin>> input;

    return input;
}

std::string getOption(){
    std::cout<<"Options"<<std::endl;
    std::cout<<"0) Exit"<<std::endl;
    std::cout<<"1) Make account"<<std::endl;
    std::cout<<"2) Deposit to existing account"<<std::endl;
    std::cout<<"3) Withdraw from existing account"<<std::endl;
    std::cout<<"4) Display existing account"<<std::endl;
    std::cout<<"5) Accrue Interest"<<std::endl;
    std::cout<<"6) Write a check"<<std::endl;
    std::cout<<"7) Get Loan"<<std::endl;
    std::cout<<"8) Check loan eligibility"<<std::endl;
    std::cout<<"9) Repay a loan"<<std::endl;
    std::cout<<"What would you like to do (Input single number):"<<std::endl;

    std::string input_string;
    std::cin>> input_string;

    return input_string;
}