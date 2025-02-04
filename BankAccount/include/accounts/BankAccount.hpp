#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <string>

class BankAccount {
public:
    BankAccount(std::string first, std::string last, double initBalance);
    BankAccount(std::string first, std::string last);

    double getBalance();
    std::string getFirstName();
    std::string getLastName();

    void setFirstName(std::string name);
    void setLastName(std::string name);

    bool withdrawal(double amount);
    bool deposit(double amount);

    virtual std::string toString() = 0;
    virtual std::string serialize() = 0;

    virtual ~BankAccount() {};

private:
    std::string firstName;
    std::string lastName;
    double balance;
};

#endif